#!/usr/bin/env bash

# To run the test, provide a path wich contains a "Test.java" file.

MAIN="Test"

if [ ! -f "$1/$MAIN.java" ]; then
  echo "Error: Invalid path. You must provide a path that has a $MAIN.java file."
  exit 1
fi

javac "$1"/*.java && java -cp "$1" "$MAIN"
