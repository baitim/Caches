#!/bin/bash

lfu_exe="../build/lfu"
ideal_exe="../build/ideal"
answer_file="answer.dat"

touch $answer_file
echo -n > $answer_file

printf "file\t\t\tlfu_hits\tideal_hits\t\tratio\n" >> $answer_file

for file in test_*.dat
do
    run_file="./${file}"
    lfu_hits=$($lfu_exe < $run_file)
    ideal_hits=$($ideal_exe < $run_file)
    ratio=$((10**4 * ideal_hits/lfu_hits))e-4

    echo $file
    echo "LFU   hits:    " $lfu_hits
    echo "Ideal hits:    " $ideal_hits
    printf "Ratio:\t\t%.2f" $ratio
    echo

    printf "$file\t\t$lfu_hits\t\t\t$ideal_hits\t\t\t%.2f\n" $ratio >> $answer_file
done