#!/bin/bash
<<<<<<< HEAD

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
=======
if [ "$#" -ne 2 ];then
	exit 1;
fi

writefile="$1"
writestr="$2"


if [ -z "$writefile" ]; then
    exit 1
fi

if [ -z "$writestr" ]; then
    exit 1
fi

mkdir -p "$(dirname "$writefile")"

echo "$writestr" > "$writefile"


if [ "$?" -ne 0 ]; then
    exit 1
fi

>>>>>>> 36427d2c9f66ba46565b46f0221c85349785c4de
