#!/bin/bash

directory="./test-files"

program="./parser"

for file in "$directory"/*.caff; do
  filename=$(basename "$file")
  echo "Running test for file: $filename"

  if [[ $filename == invalid-* ]]; then
    expected_return_code=255
  elif [[ $filename == valid-* ]]; then
    expected_return_code=0
  else
    echo "Invalid file name: $filename"
    continue
  fi

  "$program" "-caff" "$directory/$filename"

  echo "Returned: $?, expected: $expected_return_code."
  echo "---------------------------"
done