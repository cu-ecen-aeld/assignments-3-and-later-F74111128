#!/bin/bash

writefile=$1
writestr=$2

if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Two arguments are required. Usage: $0 <file_path> <text_string>"
    exit 1
fi

dirpath=$(dirname "$writefile")
if ! mkdir -p "$dirpath"; then
    echo "Error: Failed to create directory path '$dirpath'."
    exit 1
fi

if ! echo "$writestr" > "$writefile"; then
    echo "Error: Failed to write to file '$writefile'."
    exit 1
else
    echo "Successfully wrote to '$writefile'."
fi
