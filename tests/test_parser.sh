#!/bin/sh
set -eu

ROOT=$(CDPATH='' cd -- "$(dirname -- "$0")/.." && pwd)
cd "$ROOT"

run_case() {
    label=$1
    shift
    printf 'running %s\n' "$label"
    if ./push_swap "$@" >/tmp/push_swap_out 2>/tmp/push_swap_err; then
        status=0
    else
        status=$?
    fi
    if [ "$status" -ne 0 ]; then
        echo "push_swap failed for $label" >&2
        cat /tmp/push_swap_err >&2
        exit 1
    fi
}

run_case_fail() {
    label=$1
    shift
    printf 'running %s\n' "$label"
    if ./push_swap "$@" >/tmp/push_swap_out 2>/tmp/push_swap_err; then
        status=0
    else
        status=$?
    fi
    if [ "$status" -eq 0 ]; then
        echo "push_swap unexpectedly succeeded for $label" >&2
        exit 1
    fi
}

run_case 'simple' 3 2 1
run_case 'spaces' '3 2 1'
run_case 'tabs' "3	2	1"
run_case 'mixed' "3 2	1"
run_case 'negative' -3 -2 -1
run_case_fail 'duplicate' 1 1
run_case_fail 'overflow' 2147483648
run_case_fail 'negative_overflow' -2147483649
run_case_fail 'invalid_flag' --unknown 1 2
run_case_fail 'empty_arg' ''
run_case_fail 'empty_spaces' '   '

printf 'parser regression tests passed\n'
