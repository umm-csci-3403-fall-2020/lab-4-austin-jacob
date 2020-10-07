#!/usr/bin/env bash

directory=$1

numFiles=$(find "$directory" -type f -print | wc -l | xargs)
numDirs=$(find "$directory" -type d -print | wc -l | xargs)

echo "There were $numDirs directories."
echo "There were $numFiles regular files."
