
#!/bin/bash

YEAR=2024

# Find the last directory with the specified scheme
last_dir=$(ls -d [0-9][0-9] 2>/dev/null | sort -n | tail -n 1)


# Extract the number from the last directory, or set it to 0 if no directory is found
last_num=${last_dir:-00}
new_dir=$(printf "%02d" $((10#$last_num + 1)))


# Create the new directory
mkdir $new_dir

# https://github.com/GreenLightning/advent-of-code-downloader
./aocdl -year $YEAR -day $new_dir -output $new_dir/input.txt


# Create puzzle1.cpp and puzzle2.cpp within the new directory
cp templates/puzzle.cpp $new_dir/puzzle1.cpp
cp templates/puzzle.cpp $new_dir/puzzle2.cpp


touch $new_dir/test.txt

cp templates/Makefile $new_dir/Makefile

# Display the created directory
echo "Created directory: $new_dir"
