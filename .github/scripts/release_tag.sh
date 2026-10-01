#!/usr/bin/env bash
# Create local tags only. Pushing an RC starts candidate signing; pushing the
# stable tag does not build and is done only after accepting an RC's exact bytes.
# Both read the remote first, so neither a stale checkout nor a tag that only
# exists locally decides what is built or released.
set -euo pipefail
cd "$(dirname "$0")/../.."

remote=origin
contract=.github/scripts/release_contract.py

usage() {
  echo "Usage: bash .github/scripts/release_tag.sh candidate | release vX.Y.Z-rc.N" >&2
  exit 1
}

case "${1:-}" in
candidate)
  if [ -n "$(git status --porcelain --untracked-files=no)" ]; then
    echo "Tracked files must be clean before creating a candidate tag." >&2
    exit 1
  fi
  git fetch --quiet --no-tags "$remote" "+refs/heads/master:refs/remotes/$remote/master"
  master=$(git rev-parse "$remote/master")
  if [ "$(git rev-parse HEAD)" != "$master" ]; then
    echo "A candidate is cut from $remote/master ($master); check it out first." >&2
    exit 1
  fi
  version=$(python3 "$contract" version)
  remote_tags=$(git ls-remote --tags --refs "$remote" | sed 's#^.*refs/tags/##')
  highest=$({ git tag --list; printf '%s\n' "$remote_tags"; } \
    | sed -n "s/^v${version//./\\.}-rc\.\([0-9][0-9]*\)$/\1/p" \
    | sort -n | tail -1)
  tag="v${version}-rc.$(( ${highest:-0} + 1 ))"
  python3 "$contract" check-tag candidate "$tag"
  git tag "$tag"
  ;;
release)
  candidate=${2:-}
  [[ $candidate =~ ^v([0-9]+\.[0-9]+\.[0-9]+)-rc\.[1-9][0-9]*$ ]] || usage
  tag="v${BASH_REMATCH[1]}"
  # The accepted bytes were built from the candidate tag the remote holds,
  # whatever is checked out or tagged locally.
  if ! git fetch --quiet --no-tags "$remote" "refs/tags/$candidate"; then
    echo "$remote has no $candidate; only a pushed candidate can be released." >&2
    exit 1
  fi
  commit=$(git rev-parse "FETCH_HEAD^{commit}")
  python3 "$contract" check-tag stable "$tag" --commit "$commit"
  git tag "$tag" "$commit"
  ;;
*)
  usage
  ;;
esac
echo "Created $tag locally at $(git rev-parse --short "$tag^{commit}"). Review before pushing: git push origin $tag"
