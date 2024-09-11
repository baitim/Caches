import os
import glob
import subprocess

to_curr_dir = os.path.dirname(os.path.realpath(__file__)) + "/tests_dat/"

lfu_exe    = "./lfu"
belady_exe = "./belady"

answer_file = to_curr_dir + "answer.out"
os.system("touch "     + answer_file)
os.system("echo -n > " + answer_file)
ans_file = open(answer_file, 'w')
ans_file.write("file\t\t\tlfu_hits\tbelady_hits\t\tratio\n")

test_num = 0
files = list(map(str, glob.glob(to_curr_dir + "test_*.in")))
files.sort()

for file in files :

    name_of_test_file = file[len(to_curr_dir):]
    test_str = name_of_test_file + "\t\t"

    command = lfu_exe + " < " + file
    lfu_answer = subprocess.check_output(command, shell=True).decode("utf-8")

    command = belady_exe + " < " + file
    belady_answer = subprocess.check_output(command, shell=True).decode("utf-8")

    ratio = round((float)(belady_answer) / (float)(lfu_answer), 2)

    test_str += lfu_answer[:-1] + "\t\t" + belady_answer[:-1] + "\t\t\t" + str(ratio) + "\n"

    ans_file.write(test_str)
    test_num += 1
    print("test",  test_num, "passed")

ans_file.close()