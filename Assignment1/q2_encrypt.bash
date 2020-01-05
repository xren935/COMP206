#!/bin/bash
#create two variables for the first and second line of the codebook
codebook=$1
test_input1=$2

line1=$(sed -n '1p' $1)
line2=$(sed -n '2p' $1)
#variable $2 for the original message

cat $2 | tr 'a-z' "$line1" | tr 'A-Z' "$line2" > encrypted.txt
cat encrypted.txt




