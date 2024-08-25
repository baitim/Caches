#!/bin/bash

answer_file="answer.dat"
touch $answer_file
echo -n > $answer_file

for file in test_*.dat
do
    run_file="./${file}"
    lfu_hits=$(../build/lfu < $run_file)

    echo $file
    echo "LFU hits:    " $lfu_hits
    echo

    printf "$file\t$lfu_hits\n" >> $answer_file
done