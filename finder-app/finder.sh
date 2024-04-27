<<<<<<< HEAD
#!/bin/sh

writefile=$1
writestr=$2

if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Two arguments are required. Usage: $0 <directory> <search_string>"
    exit 1
fi

if [ ! -d "$writefile" ]; then
    echo "Error: The specified directory '$writefile' does not exist."
    exit 1
fi

num_files=$(find "$writefile" -type f | wc -l)
num_matching_lines=$(grep -r "$writestr" "$writefile" | wc -l)

echo "The number of files are $num_files and the number of matching lines are $num_matching_lines"
=======
#!/bin/bash

if [ "$#" -ne 2 ]; then
    exit 1
fi

filesdir="$1"
searchstr="$2"

if [ ! -d "$filesdir" ]; then
    exit 1
fi

file_count=$(find "$filesdir" -type f | wc -l)
match_count=$(grep -r "$searchstr" "$filesdir" | wc -l)
echo "The number of files are $file_count and the number of matching lines are $match_count"
>>>>>>> 36427d2c9f66ba46565b46f0221c85349785c4de
