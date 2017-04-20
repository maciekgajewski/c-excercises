#!/bin/bash

in=$1

grep RAND $in |awk -F , '{print $3}' > rand.txt
grep SEQ $in |awk -F , '{print $3}' > seq.txt