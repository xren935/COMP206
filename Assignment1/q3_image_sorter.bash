#!/bin/bash
find $1 -name "*.jpg" > findPhotos.txt
ls -t -r $(cat findPhotos.txt) > listPhotos.txt
echo "$1" | tr "/" "_" > fileName.txt
fileName=$(cat fileName.txt)
convert -append $(cat listPhotos.txt) "$fileName".jpg

