#!/bin/sh

#Check for correct number of arguments
if [ "$#" -ne 2 ]; then 
    echo "Usage: $0 <write_file> <write_str>"
    exit 1
fi

#Read arguments
write_file=$1
write_str=$2

#Check if filesdir is a directory
if [ ! -d "$write_file" ]; then
    mkdir -p "$(dirname "$write_file")"
fi

if ! (touch "$write_file" && echo "$write_str" > "$write_file"); then 
    echo "Error: failed creation file $write_file"
    exit 1
fi
