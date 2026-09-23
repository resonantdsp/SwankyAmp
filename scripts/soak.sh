#!/usr/bin/env bash
# Starts the release soak as detached processes and reads their verdict, so a
# multi-hour run survives the shell that started it.
#
# SOAK_DIR chooses the output directory (default target/soak). SOAK_RUNS
# replaces the release set with ";"-separated "path|preset|oversampling"
# entries, for example "corrected|level 11|1x;corrected|init|auto".
set -euo pipefail

dir=${SOAK_DIR:-target/soak}
IFS=';' read -r -a runs <<<"${SOAK_RUNS:-corrected|clean|auto;corrected|level 11|auto;corrected|init|auto;legacy|level 11|auto}"

running() {
    local pidfile
    for pidfile in "$dir"/*.pid; do
        [ -e "$pidfile" ] || continue
        if kill -0 "$(cat "$pidfile")" 2>/dev/null; then
            echo "$pidfile"
        fi
    done
}

case "${1:-}" in
start)
    hours=${2:-4}
    mkdir -p "$dir"
    if [ -n "$(running)" ]; then
        echo "a soak is still running in $dir:" >&2
        running >&2
        exit 1
    fi
    rm -f "$dir"/*.csv "$dir"/*.log "$dir"/*.pid "$dir"/commit
    # Run a private copy so a later release build cannot replace the binary
    # under hours of running processes, and record what it was built from.
    cp target/release/soak "$dir/soak"
    {
        git rev-parse HEAD
        git status --porcelain --untracked-files=no | sed 's/^/modified: /'
    } >"$dir/commit"
    for run in "${runs[@]}"; do
        IFS='|' read -r path preset oversampling <<<"$run"
        oversampling=${oversampling:-auto}
        name="$path-${preset// /-}"
        [ "$oversampling" = auto ] || name="$name-$oversampling"
        nohup "$dir/soak" run --path "$path" --preset "$preset" \
            --oversampling "$oversampling" --hours "$hours" \
            --csv "$dir/$name.csv" >"$dir/$name.log" 2>&1 &
        echo $! >"$dir/$name.pid"
        echo "$name: pid $! csv $dir/$name.csv log $dir/$name.log"
    done
    ;;
check)
    shopt -s nullglob
    csvs=("$dir"/*.csv)
    if [ ${#csvs[@]} -eq 0 ]; then
        echo "no soak results in $dir; start one with just soak" >&2
        exit 1
    fi
    [ -e "$dir/commit" ] && echo "built from $(head -n 1 "$dir/commit")"
    "$dir/soak" check "${csvs[@]}"
    ;;
*)
    echo "usage: $0 start [HOURS] | check" >&2
    exit 2
    ;;
esac
