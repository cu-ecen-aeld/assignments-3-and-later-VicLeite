#!/bin/sh

#Check for correct number of arguments
if [ "$#" -ne 2 ]; then 
    echo "Usage: $0 <files_dir> <search_str>"
    exit 1
fi

#Read arguments
files_dir=$1
search_str=$2

#Check if filesdir is a directory
if [ ! -d "$files_dir" ]; then
    echo "Error $files_dir is not a directory"
    exit 1
fi

#Read the number of files in the directory
num_files=$(find "$files_dir" -type f | wc -l)

#Read the number of matching lines
num_matching_lines=$(grep -r "$search_str" "$files_dir" | wc -l)

echo "The number of files are $num_files and the number of matching lines are $num_matching_lines"