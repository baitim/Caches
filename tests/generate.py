import random
count_tests = 20

for i in range(0, count_tests) :
    file_name = "test_" + f'{i+1:02}' + ".dat"
    file = open(file_name, 'w')

    size_of_cache  = random.randint(50, 200)
    count_of_elems = random.randint(10000, 30000)
    test_str = str(size_of_cache) + " " + str(count_of_elems) + "\n"

    for j in range(count_of_elems) :
        test_str += str(random.randint(1, 5000)) + " "

    file.write(test_str)
    file.close()

    print("test ", i + 1, " generated")