#!/bin/bash

lfu_exe="../build/lfu"
belady_exe="../build/belady"
answer_file="answer.dat"

touch $answer_file
echo -n > $answer_file

printf "file\t\t\tlfu_hits\tbelady_hits\t\tratio\n" >> $answer_file

for file in test_*.dat
do
    run_file="./${file}"
    lfu_hits=$($lfu_exe < $run_file)
    belady_hits=$($belady_exe < $run_file)
    ratio=$((10**4 * belady_hits/lfu_hits))e-4

    echo $file
    echo "LFU   hits:    " $lfu_hits
    echo "Belady hits:   " $belady_hits
    printf "Ratio:\t\t%.2f\n" $ratio
    echo

    printf "$file\t\t$lfu_hits\t\t\t$belady_hits\t\t\t%.2f\n" $ratio >> $answer_file
done