import random
count_tests = 5

for i in range(0, count_tests) :
    file_name = "test_" + f'{i+1:02}' + ".dat"
    file = open(file_name, 'w')

    size_of_cache  = random.randint(1000, 2000)
    count_of_elems = random.randint(5000, 20000)
    test_str = str(size_of_cache) + " " + str(count_of_elems) + "\n"

    print("count: ", count_of_elems / 10000)
    for j in range(count_of_elems) :
        if (j % 10000 == 0) :
            print("elems: ", j / 10000)
        test_str += str(random.randint(1, 10000)) + " "

    file.write(test_str)
    file.close()

    print("test ", i + 1, " generated")