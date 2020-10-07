#!/usr/bin/env bash

directory=$1

numFiles=$(find $directory -type f | wc -l)
numDirs=$(find $directory -type d | wc -l)

echo "Processed all the files from $directory."
echo "There were $numDirs directories."
echo "There were $numFiles regular files."
