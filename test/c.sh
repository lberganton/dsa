#!/usr/bin/env bash

# To run the test, provide a path wich contains a "test.c" file.

CC=${CC:-gcc}
FLAGS="-std=c99 -g -Wall -Wextra -Wpedantic -Wshadow -fno-sanitize-recover -fsanitize=address -fsanitize=undefined"
TARGET="test"

if [ ! -f "$1/$TARGET.c" ]; then
  echo "Error: Invalid path. You must provide a path that has a $TARGET.c file."
  exit 1
fi

$CC $FLAGS "$1"/*.c -o "$1"/a.out && ./"$1"/a.out
