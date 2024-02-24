#!/bin/bash
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

