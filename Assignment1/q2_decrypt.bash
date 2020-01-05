#!/bin/bash
codebook=$1
secret_message=$2
line1=$(sed -n '1p' $1)
line2=$(sed -n '2p' $1)
cat $2 | tr "$line1" 'a-z' | tr "$line2" 'A-Z' > origin.txt
cat origin.txt



