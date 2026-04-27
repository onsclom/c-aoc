#!/usr/bin/env bash
set -euo pipefail

if [ $# -lt 1 ]; then
  echo "Usage: build-and-run.sh <source.c> [args...]" >&2
  exit 1
fi

SRC="$1"
shift
OUT="${SRC%.c}"

CFLAGS=(
  -std=c99 -I. -g -O0
  -Wall -Wextra -Wshadow -Wcast-align -Wpointer-arith
  -Wno-unused-parameter -Wno-unused-function
  -fno-omit-frame-pointer -fstack-protector-strong
)

cc "${CFLAGS[@]}" "$SRC" -o "$OUT"
"./$OUT" "$@"
