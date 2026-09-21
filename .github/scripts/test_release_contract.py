#!/usr/bin/env python3

import hashlib
import json
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


SCRIPT = Path(__file__).with_name("release_contract.py")
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
            'license = "GPL-3.0-or-later"\nrepository = "https://github.com/resonantdsp/SwankyAmp"\n',
            encoding="utf-8",
        )
        (self.root / "truce.toml").write_text(
            '[vendor]\nid = "com.resonantdsp"\n'
            '[[plugin]]\nname = "Swanky Amp 2"\nbundle_id = "swanky-amp-2"\n'
            'crate = "swanky-amp"\nfourcc = "SwA2"\n',
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

    def record(self) -> str:
        result = run(
            self.root, *self.command, "record", "v2.0.0-rc.1", str(self.artifacts)
        )
        record = json.loads(result.stdout)
        path = self.artifacts / "release-record.json"
        path.write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
        record_hash = hashlib.sha256(path.read_bytes()).hexdigest()
        (self.artifacts / "release-record.sha256").write_text(
            f"{record_hash}  candidate/release-record.json\n", encoding="utf-8"
        )
        return record_hash

    def test_successful_record_and_promotion_bind_source_identity_and_bytes(self):
        record_hash = self.record()
        record = json.loads((self.artifacts / "release-record.json").read_text())
        self.assertEqual(record["product"]["website_product_id"], "SwankyAmp")
        self.assertEqual(record["product"]["plugin_identity"], "SwankyAmp2")
        self.assertEqual(record["product"]["bundle_id"], "com.resonantdsp.swanky-amp-2")
        self.assertEqual(record["product"]["fourcc"], "SwA2")
        self.assertEqual(
            [artifact["kind"] for artifact in record["artifacts"]],
            ["macos-pkg", "windows-exe"],
        )
        verified = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", record_hash, str(self.artifacts),
        )
        self.assertIn("2 recorded artifacts", verified.stdout)

        (self.artifacts / "qualification.md").write_text("Accepted on test hosts.\n")
        published = self.root / "published"
        shutil.copytree(self.artifacts, published)
        resumed = run(
            self.root, *self.command, "verify-stable-assets",
            str(self.artifacts), str(published),
        )
        self.assertIn("exactly match", resumed.stdout)
        (published / "swanky-amp-2.0.0-macos.pkg").write_bytes(b"different")
        refused = run(
            self.root, *self.command, "verify-stable-assets",
            str(self.artifacts), str(published), check=False,
        )
        self.assertNotEqual(refused.returncode, 0)
        self.assertIn("asset differs", refused.stderr)

    def test_wrong_version_and_different_tag_commit_are_refused(self):
        wrong = run(
            self.root, *self.command, "check-tag", "candidate", "v2.0.1-rc.1",
            check=False,
        )
        self.assertNotEqual(wrong.returncode, 0)
        self.assertIn("Cargo.toml is 2.0.0", wrong.stderr)

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
        self.assertIn("must be identical", mismatch.stderr)

    def test_altered_bytes_and_wrong_accepted_record_hash_are_refused(self):
        record_hash = self.record()
        bad_hash = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", "0" * 64, str(self.artifacts), check=False,
        )
        self.assertNotEqual(bad_hash.returncode, 0)
        self.assertIn("accepted SHA-256", bad_hash.stderr)

        (self.artifacts / "swanky-amp-2.0.0-windows.exe").write_bytes(b"changed")
        altered = run(
            self.root, *self.command, "verify-candidate", "v2.0.0-rc.1",
            "v2.0.0", record_hash, str(self.artifacts), check=False,
        )
        self.assertNotEqual(altered.returncode, 0)
        self.assertIn("recorded bytes", altered.stderr)

    def test_release_helpers_preserve_invalid_or_uncommitted_source(self):
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
        self.assertIn("no '## Unreleased' section", invalid.stderr)
        self.assertEqual((self.root / "Cargo.toml").read_bytes(), cargo_before)

        (self.root / "Cargo.toml").write_text(
            (self.root / "Cargo.toml").read_text(encoding="utf-8") + "\n# local edit\n",
            encoding="utf-8",
        )
        dirty = run(
            self.root, "bash", str(self.root / ".github" / "scripts" / "release_tag.sh"),
            "candidate", check=False,
        )
        self.assertNotEqual(dirty.returncode, 0)
        self.assertIn("Tracked files must be clean", dirty.stderr)


if __name__ == "__main__":
    unittest.main()
