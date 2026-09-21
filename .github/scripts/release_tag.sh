#!/usr/bin/env bash
# Create local tags only. Pushing an RC starts candidate signing; pushing the
# stable tag does not build and is done only after accepting an RC's exact bytes.
set -euo pipefail
cd "$(dirname "$0")/../.."

if [ -n "$(git status --porcelain --untracked-files=no)" ]; then
  echo "Tracked files must be clean before creating a release tag." >&2
  exit 1
fi

version=$(python3 .github/scripts/release_contract.py version)
case "${1:-}" in
candidate)
  highest=$(git tag --list "v${version}-rc.*" \
    | sed -n "s/^v${version//./\\.}-rc\.\([0-9][0-9]*\)$/\1/p" \
    | sort -n | tail -1)
  tag="v${version}-rc.$(( ${highest:-0} + 1 ))"
  python3 .github/scripts/release_contract.py check-tag candidate "$tag"
  ;;
release)
  tag="v${version}"
  python3 .github/scripts/release_contract.py check-tag stable "$tag"
  ;;
*)
  echo "Usage: bash .github/scripts/release_tag.sh candidate|release" >&2
  exit 1
  ;;
esac
git tag "$tag"
echo "Created $tag locally. Review before pushing: git push origin $tag"
