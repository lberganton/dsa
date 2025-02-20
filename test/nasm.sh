#!/usr/bin/env bash

# To run the test, provide a path wich contains a "test.c" file.

FLAGS="-std=c99 -g -Wall -Wextra -Wpedantic -Wshadow -fno-sanitize-recover -fsanitize=address -fsanitize=undefined"
TARGET="test"

if [[ ! -d "$1" || ! -f "$1/$TARGET.c" ]]; then
  echo "Error: Invalid path. You must provide a path that has a $TARGET.c file."
  exit 1
fi

cd "$1"

files=*.asm
for i in ${files[*]}; do
  nasm -felf64 $i
done

gcc $FLAGS $TARGET.c *.o -o a.out && ./a.out
