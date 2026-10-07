#!/usr/bin/env python3
"""The release contract and tag helpers, run against a scratch repository."""

import hashlib
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


SCRIPTS = Path(__file__).resolve().parent
sys.path.insert(0, str(SCRIPTS))
from release_contract import ARTIFACT_PREFIX  # noqa: E402

CANDIDATE = "v2.0.0-rc.1"
INSTALLERS = {
    f"{ARTIFACT_PREFIX}-2.0.0-macos.pkg": b"mac",
    f"{ARTIFACT_PREFIX}-2.0.0-windows.exe": b"win",
}


def run(root: Path, *command: str, check: bool = True) -> subprocess.CompletedProcess:
    return subprocess.run(command, cwd=root, check=check, text=True, capture_output=True)


class ReleaseTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="swanky-release-")
        self.root = Path(self.temporary.name) / "repo"
        (self.root / "scripts").mkdir(parents=True)
        for name in ("release_contract.py", "release-tag.sh", "version.sh"):
            shutil.copy2(SCRIPTS / name, self.root / "scripts" / name)
        # Each product reads the one of these it ships.
        (self.root / "assets").mkdir()
        (self.root / "assets" / "artwork.pack").write_bytes(b"artwork")
        (self.root / "assets" / "package.sha256").write_text("0" * 64 + "\n", encoding="utf-8")
        (self.root / "Cargo.lock").write_text("lock\n", encoding="utf-8")
        (self.root / "Cargo.toml").write_text(
            '[package]\nname = "swanky"\nversion = "2.0.0"\n'
            "[package.metadata.release]\nlinux = false\n",
            encoding="utf-8",
        )
        (self.root / "truce.toml").write_text(
            '[vendor]\nid = "com.resonantdsp"\n'
            '[[plugin]]\nname = "Swanky 2"\nbundle_id = "swanky-2"\nfourcc = "SwA2"\n',
            encoding="utf-8",
        )
        (self.root / "vendor" / "cargo-truce").mkdir(parents=True)
        (self.root / "vendor" / "cargo-truce" / "Cargo.toml").write_text(
            '[package]\nname = "cargo-truce"\nversion = "6.3.0"\n', encoding="utf-8"
        )
        (self.root / "rust-toolchain.toml").write_text('[toolchain]\nchannel = "1.97.1"\n', encoding="utf-8")
        (self.root / "CHANGELOG.md").write_text(
            "# Changelog\n\n## Unreleased\n\n## 2.0.0 — 2026-10-30\n\n- First release.\n", encoding="utf-8"
        )
        self.git("init", "-b", "master")
        self.git("config", "user.name", "Release Check")
        self.git("config", "user.email", "release@example.invalid")
        # A record needs the history a full checkout has: 99 commits before
        # this one give it build number 100.
        history = "".join(
            f"commit refs/heads/master\ncommitter R <r@example.invalid> {n} +0000\ndata 0\n\n"
            for n in range(99)
        )
        subprocess.run(
            ["git", "fast-import", "--quiet"], cwd=self.root, input=history, text=True, check=True, capture_output=True
        )
        self.git("add", ".")
        self.git("commit", "-m", "release")
        self.git("tag", CANDIDATE)
        self.candidate = self.root.parent / "candidate"
        self.candidate.mkdir()
        for name, contents in INSTALLERS.items():
            (self.candidate / name).write_bytes(contents)

    def tearDown(self):
        self.temporary.cleanup()

    def git(self, *args: str) -> str:
        return run(self.root, "git", *args).stdout.strip()

    def contract(self, *args: str) -> subprocess.CompletedProcess:
        return run(self.root, "python3", "scripts/release_contract.py", *args, check=False)

    def tag(self, *args: str) -> subprocess.CompletedProcess:
        return run(self.root, "bash", "scripts/release-tag.sh", *args, check=False)

    def tags(self) -> set:
        return set(self.git("tag", "--list").split())

    def commit(self, name: str, text: str) -> None:
        (self.root / name).write_text(text, encoding="utf-8")
        self.git("add", name)
        self.git("commit", "-m", name)

    def record(self) -> str:
        """Record and store the candidate as the candidate workflow does,
        returning the record hash a person accepts."""
        result = self.contract("record", CANDIDATE, str(self.candidate))
        self.assertEqual(result.returncode, 0, result.stderr)
        path = self.candidate / "release-record.json"
        path.write_text(result.stdout, encoding="utf-8")
        accepted = hashlib.sha256(path.read_bytes()).hexdigest()
        (self.candidate / "release-record.sha256").write_text(f"{accepted}  release-record.json\n", encoding="utf-8")
        return accepted

    def fetched(self) -> Path:
        directory = self.root.parent / "fetched"
        result = self.contract("fetch", self.candidate.as_uri(), str(directory))
        self.assertEqual(result.returncode, 0, result.stderr)
        return directory

    def verify(self, accepted: str, directory: Path) -> subprocess.CompletedProcess:
        return self.contract("verify", CANDIDATE, "v2.0.0", accepted, str(directory))

    def add_origin(self) -> None:
        """A remote holding master and the first candidate, as GitHub would."""
        origin = self.root.parent / "origin.git"
        run(self.root, "git", "init", "--bare", "-b", "master", str(origin))
        self.git("remote", "add", "origin", str(origin))
        self.git("push", "origin", "master", CANDIDATE)

    def test_a_fetched_candidate_verifies_against_its_tags_and_accepted_record(self):
        accepted = self.record()
        stored = json.loads((self.candidate / "release-record.json").read_text())
        self.assertEqual(stored["build"], 100)
        self.assertEqual(stored["cargo_truce"], "6.3.0")
        self.assertEqual([item["kind"] for item in stored["artifacts"]], ["macos-pkg", "windows-exe"])
        self.git("tag", "v2.0.0")
        fetched = self.fetched()
        self.assertEqual(self.verify(accepted, fetched).returncode, 0)
        self.assertNotEqual(self.verify("0" * 64, fetched).returncode, 0)

        (fetched / f"{ARTIFACT_PREFIX}-2.0.0-windows.exe").write_bytes(b"changed")
        self.assertNotEqual(self.verify(accepted, fetched).returncode, 0)

    def test_the_release_tag_must_be_on_the_candidates_commit(self):
        accepted = self.record()
        self.commit("later", "later\n")
        self.git("tag", "v2.0.0")
        self.assertNotEqual(self.verify(accepted, self.fetched()).returncode, 0)

    def test_the_checksum_file_must_name_the_record_beside_it(self):
        accepted = self.record()
        (self.candidate / "release-record.sha256").write_text(f"{accepted}  candidate/release-record.json\n")
        self.git("tag", "v2.0.0")
        self.assertNotEqual(self.verify(accepted, self.fetched()).returncode, 0)

    def test_a_record_refuses_a_shallow_history_and_a_missing_installer(self):
        (self.candidate / f"{ARTIFACT_PREFIX}-2.0.0-windows.exe").unlink()
        self.assertNotEqual(self.contract("record", CANDIDATE, str(self.candidate)).returncode, 0)
        (self.candidate / f"{ARTIFACT_PREFIX}-2.0.0-windows.exe").write_bytes(b"win")
        self.git("checkout", "--orphan", "shallow")
        self.git("commit", "-m", "only commit")
        shallow = self.contract("record", CANDIDATE, str(self.candidate))
        self.assertNotEqual(shallow.returncode, 0)
        self.assertIn("full history", shallow.stderr)

    def test_tags_are_checked_against_the_crate_version_and_the_changelog(self):
        self.assertEqual(self.contract("check-tag", "candidate", CANDIDATE).returncode, 0)
        self.assertNotEqual(self.contract("check-tag", "candidate", "v2.0.1-rc.1").returncode, 0)
        self.commit("CHANGELOG.md", "# Changelog\n\n## 2.0.0 — in development\n\n- First.\n")
        self.assertNotEqual(self.contract("check-tag", "candidate", CANDIDATE).returncode, 0)
        self.commit("CHANGELOG.md", "# Changelog\n\n## 2.0.0\n\n- First.\n")
        self.assertEqual(self.contract("check-tag", "candidate", CANDIDATE).returncode, 0)
        self.assertNotEqual(self.contract("check-tag", "stable", "v2.0.0").returncode, 0)

    def test_a_candidate_is_cut_only_from_the_remote_master_and_numbered_past_its_tags(self):
        self.add_origin()
        self.git("push", "origin", "HEAD:refs/tags/v2.0.0-rc.2")

        self.commit("unmerged", "local work\n")
        self.assertNotEqual(self.tag("candidate").returncode, 0)
        self.git("push", "origin", "HEAD:master")
        self.git("reset", "--hard", "HEAD~1")
        self.assertNotEqual(self.tag("candidate").returncode, 0, "a stale master is refused")
        self.git("pull", "--ff-only", "origin", "master")

        cargo = self.root / "Cargo.toml"
        committed = cargo.read_text(encoding="utf-8")
        cargo.write_text(committed + "\n# local edit\n", encoding="utf-8")
        self.assertNotEqual(self.tag("candidate").returncode, 0, "a dirty tree is refused")
        cargo.write_text(committed, encoding="utf-8")

        self.assertEqual(self.tag("candidate").returncode, 0)
        self.assertEqual(self.tags(), {CANDIDATE, "v2.0.0-rc.3"})

        self.git("push", "origin", "HEAD:refs/tags/v2.0.0")
        self.assertNotEqual(self.tag("candidate").returncode, 0, "a released version is refused")

    def test_the_release_tags_the_pushed_candidates_commit(self):
        self.add_origin()
        candidate = self.git("rev-parse", CANDIDATE)
        self.commit("later", "later\n")
        self.git("tag", "v2.0.0-rc.2")
        self.assertNotEqual(self.tag("release", "v2.0.0-rc.2").returncode, 0, "an unpushed candidate is refused")
        self.assertEqual(self.tag("release", CANDIDATE).returncode, 0)
        self.assertEqual(self.git("rev-parse", "v2.0.0^{commit}"), candidate)

    def test_the_version_helper_leaves_the_tree_untouched_when_it_refuses(self):
        self.commit("CHANGELOG.md", "# Changelog\n\n## 2.0.0 — 2026-10-30\n")
        before = (self.root / "Cargo.toml").read_bytes()
        self.assertNotEqual(run(self.root, "bash", "scripts/version.sh", "2.0.1", check=False).returncode, 0)
        self.assertEqual((self.root / "Cargo.toml").read_bytes(), before)

    def test_a_record_holds_exactly_the_downloads_the_release_declares(self):
        cargo = self.root / "Cargo.toml"
        cargo.write_text(cargo.read_text(encoding="utf-8").replace("linux = false", "linux = true"), encoding="utf-8")
        self.assertNotEqual(self.contract("record", CANDIDATE, str(self.candidate)).returncode, 0)
        (self.candidate / f"{ARTIFACT_PREFIX}-2.0.0-linux-x86_64.tar.gz").write_bytes(b"linux")
        result = self.contract("record", CANDIDATE, str(self.candidate))
        self.assertIn("linux-tarball", [item["kind"] for item in json.loads(result.stdout)["artifacts"]])


if __name__ == "__main__":
    unittest.main()
