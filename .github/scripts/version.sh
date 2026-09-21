#!/usr/bin/env bash
# Move Cargo.toml, Cargo.lock and the changelog together. This helper prepares
# the working tree; the operator runs the repository gate before committing.
set -euo pipefail
cd "$(dirname "$0")/../.."

version=${1:-}
if ! [[ $version =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
  echo "Usage: bash .github/scripts/version.sh <x.y.z>" >&2
  exit 1
fi
if [ -n "$(git status --porcelain Cargo.toml Cargo.lock CHANGELOG.md)" ]; then
  echo "Cargo.toml, Cargo.lock or CHANGELOG.md has uncommitted changes." >&2
  exit 1
fi
if grep -qE "^## ${version//./\\.}( |$)" CHANGELOG.md; then
  echo "CHANGELOG.md already has a '## $version' section." >&2
  exit 1
fi

python3 - "$version" <<'PY'
import datetime
import pathlib
import re
import sys

version = sys.argv[1]
cargo = pathlib.Path("Cargo.toml")
cargo_text, count = re.subn(
    r'(?m)^(version = ")[^"]*(")', rf"\g<1>{version}\g<2>", cargo.read_text(), count=1
)
if count != 1:
    raise SystemExit("Cargo.toml [package] has no version to set.")

changelog = pathlib.Path("CHANGELOG.md")
changelog_text = changelog.read_text()
heading = "## Unreleased\n"
if heading not in changelog_text:
    raise SystemExit("CHANGELOG.md has no '## Unreleased' section.")
changelog_text = changelog_text.replace(
    heading, f"## Unreleased\n\n## {version} — {datetime.date.today().isoformat()}\n", 1
)

cargo.write_text(cargo_text)
changelog.write_text(changelog_text)
PY

cargo metadata --format-version 1 --offline >/dev/null
echo "Prepared version $version. Run just, review the diff, then commit Cargo.toml, Cargo.lock and CHANGELOG.md together."
