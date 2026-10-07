#!/usr/bin/env python3

import hashlib
import json
import re
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


SCRIPT = Path(__file__).with_name("release_contract.py")
REPOSITORY = Path(__file__).resolve().parents[2]
VERSION_SCRIPT = Path(__file__).with_name("version.sh")
TAG_SCRIPT = Path(__file__).with_name("release_tag.sh")


def run(root: Path, *command: str, check: bool = True) -> subprocess.CompletedProcess:
    return subprocess.run(command, cwd=root, check=check, text=True, capture_output=True)


class ReleaseCommandTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="swanky-release-")
        self.root = Path(self.temporary.name)
        scripts = self.root / ".github" / "scripts"
        scripts.mkdir(parents=True)
        shutil.copy2(SCRIPT, scripts / SCRIPT.name)
        shutil.copy2(VERSION_SCRIPT, scripts / VERSION_SCRIPT.name)
        shutil.copy2(TAG_SCRIPT, scripts / TAG_SCRIPT.name)
        (self.root / "assets").mkdir()
        (self.root / "assets" / "artwork.pack").write_bytes(b"artwork")
        (self.root / "Cargo.lock").write_text("lock\n", encoding="utf-8")
        (self.root / "Cargo.toml").write_text(
            '[package]\nname = "swanky-amp"\nversion = "2.0.0"\n'
            'license = "GPL-3.0-or-later"\nrepository = "https://github.com/resonantdsp/SwankyAmp"\n'
            '[package.metadata.release]\nlinux = false\n',
            encoding="utf-8",
        )
        (self.root / "truce.toml").write_text(
            '[vendor]\nid = "com.resonantdsp"\n'
            '[[plugin]]\nname = "Swanky Amp 2"\nbundle_id = "swanky-amp-2"\n'
            'crate = "swanky-amp"\nfourcc = "SwA2"\n',
            encoding="utf-8",
        )
        (self.root / "vendor" / "cargo-truce").mkdir(parents=True)
        (self.root / "vendor" / "cargo-truce" / "Cargo.toml").write_text(
            '[package]\nname = "cargo-truce"\nversion = "6.3.0"\n'
            '[dependencies.truce-core]\nversion = "6.3.0"\n',
            encoding="utf-8",
        )
        (self.root / "rust-toolchain.toml").write_text(
            '[toolchain]\nchannel = "1.97.1"\n', encoding="utf-8"
        )
        (self.root / "CHANGELOG.md").write_text(
            "# Changelog\n\n## Unreleased\n\n## 2.0.0 — 2026-09-20\n\n- First release.\n",
            encoding="utf-8",
        )
        run(self.root, "git", "init", "-b", "master")
        run(self.root, "git", "config", "user.name", "Release Check")
        run(self.root, "git", "config", "user.email", "release@example.invalid")
        # A record needs the history a full checkout has: 99 commits before
        # this one give it build number 100.
        history = "".join(
            f"commit refs/heads/master\ncommitter R <r@example.invalid> {n} +0000\ndata 0\n\n"
            for n in range(99)
        )
        subprocess.run(
            ["git", "fast-import", "--quiet"], cwd=self.root, input=history,
            text=True, check=True, capture_output=True,
        )
        run(self.root, "git", "add", ".")
        run(self.root, "git", "commit", "-m", "release")
        run(self.root, "git", "tag", "v2.0.0-rc.1")
        run(self.root, "git", "tag", "v2.0.0")
        self.artifacts = self.root / "candidate"
        self.artifacts.mkdir()
        for name, contents in (
            ("swanky-amp-2.0.0-macos.pkg", b"mac"),
            ("swanky-amp-2.0.0-windows.exe", b"win"),
        ):
            (self.artifacts / name).write_bytes(contents)

    def tearDown(self):
        self.temporary.cleanup()

    @property
    def command(self) -> tuple[str, str]:
        return ("python3", str(self.root / ".github" / "scripts" / SCRIPT.name))

    def tag_script(self, *args: str) -> subprocess.CompletedProcess:
        return run(
            self.root, "bash", str(self.root / ".github" / "scripts" / TAG_SCRIPT.name),
            *args, check=False,
        )

    def commit(self, name: str, text: str) -> str:
        (self.root / name).write_text(text, encoding="utf-8")
        run(self.root, "git", "add", name)
        run(self.root, "git", "commit", "-m", name)
        return self.rev("HEAD")

    def rev(self, ref: str) -> str:
        return run(self.root, "git", "rev-parse", f"{ref}^{{commit}}").stdout.strip()

    def tags(self) -> set[str]:
        return set(run(self.root, "git", "tag", "--list").stdout.split())

    def remote_tags(self) -> set[str]:
        listing = run(self.root, "git", "ls-remote", "--tags", "--refs", "origin").stdout
        return {line.split("refs/tags/")[1] for line in listing.splitlines()}

    def add_origin(self) -> None:
        """A remote holding master and the release tags, as GitHub would."""
        origin = self.root.parent / f"{self.root.name}-origin.git"
        run(self.root, "git", "init", "--bare", "-b", "master", str(origin))
        self.addCleanup(shutil.rmtree, origin, True)
        run(self.root, "git", "remote", "add", "origin", str(origin))
        run(self.root, "git", "push", "origin", "master", "v2.0.0-rc.1")
        run(self.root, "git", "tag", "-d", "v2.0.0")

    def record(self) -> str:
        result = run(
            self.root, *self.command, "record", "v2.0.0-rc.1", str(self.artifacts)
        )
        record = json.loads(result.stdout)
        path = self.artifacts / "release-record.json"
        path.write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
        record_hash = hashlib.sha256(path.read_bytes()).hexdigest()
        (self.artifacts / "release-record.sha256").write_text(
            f"{record_hash}  release-record.json\n", encoding="utf-8"
        )
        return record_hash

    def test_successful_record_and_promotion_bind_source_identity_and_bytes(self):
        record_hash = self.record()
        record = json.loads((self.artifacts / "release-record.json").read_text())
        self.assertEqual(record["product"]["website_product_id"], "SwankyAmp")
        self.assertEqual(record["product"]["plugin_identity"], "SwankyAmp2")
        self.assertEqual(record["product"]["bundle_id"], "com.resonantdsp.swanky-amp-2")
        self.assertEqual(record["product"]["fourcc"], "SwA2")
        self.assertEqual(record["cargo_truce"], "6.3.0")
        self.assertEqual(record["build"], 100)
        self.assertEqual(
            [artifact["kind"] for artifact in record["artifacts"]],
            ["macos-pkg", "windows-exe"],
        )
        run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", record_hash, str(self.artifacts),
        )

        (self.artifacts / "qualification.md").write_text("Accepted on test hosts.\n")
        published = self.root / "published"
        shutil.copytree(self.artifacts, published)
        run(
            self.root, *self.command, "verify-stable-assets",
            str(self.artifacts), str(published),
        )
        (published / "swanky-amp-2.0.0-macos.pkg").write_bytes(b"different")
        refused = run(
            self.root, *self.command, "verify-stable-assets",
            str(self.artifacts), str(published), check=False,
        )
        self.assertNotEqual(refused.returncode, 0)

    def test_wrong_version_and_different_tag_commit_are_refused(self):
        wrong = run(
            self.root, *self.command, "check-tag", "candidate", "v2.0.1-rc.1",
            check=False,
        )
        self.assertNotEqual(wrong.returncode, 0)

        record_hash = self.record()
        (self.root / "later").write_text("later\n", encoding="utf-8")
        run(self.root, "git", "add", "later")
        run(self.root, "git", "commit", "-m", "later")
        run(self.root, "git", "tag", "-f", "v2.0.0")
        mismatch = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", record_hash, str(self.artifacts), check=False,
        )
        self.assertNotEqual(mismatch.returncode, 0)

    def test_altered_bytes_and_wrong_accepted_record_hash_are_refused(self):
        record_hash = self.record()
        bad_hash = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", "0" * 64, str(self.artifacts), check=False,
        )
        self.assertNotEqual(bad_hash.returncode, 0)

        (self.artifacts / "swanky-amp-2.0.0-windows.exe").write_bytes(b"changed")
        altered = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", record_hash, str(self.artifacts), check=False,
        )
        self.assertNotEqual(altered.returncode, 0)

    def test_record_refuses_a_shallow_history(self):
        run(self.root, "git", "checkout", "--orphan", "shallow")
        run(self.root, "git", "commit", "-m", "only commit")
        shallow = run(
            self.root, *self.command, "record", run(self.root, "git", "rev-parse", "HEAD").stdout.strip(),
            str(self.artifacts), check=False,
        )
        self.assertNotEqual(shallow.returncode, 0)
        self.assertIn("full history", shallow.stderr)

    def test_checksum_file_must_name_the_record_beside_it(self):
        record_hash = self.record()
        (self.artifacts / "release-record.sha256").write_text(
            f"{record_hash}  candidate/release-record.json\n", encoding="utf-8"
        )
        refused = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", record_hash, str(self.artifacts), check=False,
        )
        self.assertNotEqual(refused.returncode, 0)

    def test_record_holds_exactly_the_downloads_the_release_declares(self):
        cargo = self.root / "Cargo.toml"
        cargo.write_text(
            cargo.read_text(encoding="utf-8").replace("linux = false", "linux = true"),
            encoding="utf-8",
        )
        record = (*self.command, "record", "v2.0.0-rc.1", str(self.artifacts))
        self.assertNotEqual(run(self.root, *record, check=False).returncode, 0)
        (self.artifacts / "swanky-amp-2.0.0-linux-x86_64.tar.gz").write_bytes(b"linux")
        kinds = [item["kind"] for item in json.loads(run(self.root, *record).stdout)["artifacts"]]
        self.assertIn("linux-tarball", kinds)

        cargo.write_text(
            cargo.read_text(encoding="utf-8").replace("linux = true", "linux = false"),
            encoding="utf-8",
        )
        self.assertNotEqual(run(self.root, *record, check=False).returncode, 0)

    def test_candidate_is_cut_only_from_the_remote_master_and_numbered_past_remote_tags(self):
        self.add_origin()
        run(self.root, "git", "push", "origin", "HEAD:refs/tags/v2.0.0-rc.2")

        self.commit("unmerged", "local work\n")
        self.assertNotEqual(self.tag_script("candidate").returncode, 0)
        run(self.root, "git", "push", "origin", "HEAD:master")
        run(self.root, "git", "reset", "--hard", "HEAD~1")
        # The remote moved on since this checkout last looked.
        run(self.root, "git", "update-ref", "refs/remotes/origin/master", "HEAD")
        self.assertNotEqual(self.tag_script("candidate").returncode, 0)
        self.assertEqual(self.tags(), {"v2.0.0-rc.1"})

        run(self.root, "git", "pull", "--ff-only", "origin", "master")
        cargo = self.root / "Cargo.toml"
        committed = cargo.read_text(encoding="utf-8")
        cargo.write_text(committed + "\n# local edit\n", encoding="utf-8")
        self.assertNotEqual(self.tag_script("candidate").returncode, 0)
        self.assertEqual(self.tags(), {"v2.0.0-rc.1"})
        cargo.write_text(committed, encoding="utf-8")

        self.assertEqual(self.tag_script("candidate").returncode, 0)
        self.assertEqual(self.tags(), {"v2.0.0-rc.1", "v2.0.0-rc.3"})
        self.assertEqual(self.rev("v2.0.0-rc.3"), self.rev("origin/master"))
        self.assertNotIn("v2.0.0-rc.3", self.remote_tags())

        run(self.root, "git", "push", "origin", "HEAD:refs/tags/v2.0.0")
        self.assertNotEqual(self.tag_script("candidate").returncode, 0)
        self.assertEqual(self.tags(), {"v2.0.0-rc.1", "v2.0.0-rc.3"})

    def test_release_tags_the_pushed_candidate_commit_not_the_checkout(self):
        self.add_origin()
        candidate = self.rev("v2.0.0-rc.1")
        self.commit("later", "later\n")
        run(self.root, "git", "tag", "v2.0.0-rc.2")

        self.assertNotEqual(self.tag_script("release", "v2.0.0-rc.2").returncode, 0)
        self.assertNotIn("v2.0.0", self.tags())

        self.assertEqual(self.tag_script("release", "v2.0.0-rc.1").returncode, 0)
        self.assertEqual(self.rev("v2.0.0"), candidate)
        self.assertNotIn("v2.0.0", self.remote_tags())

    def test_candidate_and_release_refuse_an_undated_changelog_heading(self):
        self.add_origin()
        changelog = "# Changelog\n\n## Unreleased\n\n## 2.0.0{}\n\n- First release.\n"
        for heading in (" — in development", "\n2026-09-20"):
            self.commit("CHANGELOG.md", changelog.format(heading))
            run(self.root, "git", "push", "origin", "HEAD:master")
            self.assertNotEqual(self.tag_script("candidate").returncode, 0)
            self.assertEqual(self.tags(), {"v2.0.0-rc.1"})
        # A candidate tagged by hand on that commit cannot be released either.
        run(self.root, "git", "push", "origin", "HEAD:refs/tags/v2.0.0-rc.2")
        self.assertNotEqual(self.tag_script("release", "v2.0.0-rc.2").returncode, 0)
        self.assertNotIn("v2.0.0", self.tags())

        self.commit("CHANGELOG.md", changelog.format(" — 2026-09-20"))
        run(self.root, "git", "push", "origin", "HEAD:master")
        self.assertEqual(self.tag_script("candidate").returncode, 0)
        run(self.root, "git", "push", "origin", "v2.0.0-rc.3")
        self.assertEqual(self.tag_script("release", "v2.0.0-rc.3").returncode, 0)
        self.assertEqual(self.rev("v2.0.0"), self.rev("HEAD"))

    def test_version_helper_leaves_source_untouched_when_it_refuses(self):
        cargo_before = (self.root / "Cargo.toml").read_bytes()
        (self.root / "CHANGELOG.md").write_text(
            "# Changelog\n\n## 2.0.0 — 2026-09-20\n", encoding="utf-8"
        )
        run(self.root, "git", "add", "CHANGELOG.md")
        run(self.root, "git", "commit", "-m", "remove unreleased heading")
        invalid = run(
            self.root, "bash", str(self.root / ".github" / "scripts" / "version.sh"),
            "2.0.1", check=False,
        )
        self.assertNotEqual(invalid.returncode, 0)
        self.assertEqual((self.root / "Cargo.toml").read_bytes(), cargo_before)


class PinTest(unittest.TestCase):
    def test_justfile_pins_the_vendored_cargo_truce(self):
        sys.path.insert(0, str(SCRIPT.parent))
        from release_contract import cargo_truce_version

        justfile = (REPOSITORY / "Justfile").read_text(encoding="utf-8")
        pinned = re.search(r'^export TRUCE_VERSION := "([^"]+)"$', justfile, re.M).group(1)
        self.assertEqual(pinned, cargo_truce_version(REPOSITORY))


if __name__ == "__main__":
    unittest.main()
