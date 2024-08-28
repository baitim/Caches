import random
count_tests = 10

for i in range(0, count_tests) :
    file_name = "test_" + f'{i+1:02}' + ".dat"
    file = open(file_name, 'w')

    size_of_cache  = random.randint(50, 150)
    count_of_elems = random.randint(50000, 100000)
    test_str = str(size_of_cache) + " " + str(count_of_elems) + "\n"

    print("count: ", count_of_elems / 10000)
    for j in range(count_of_elems) :
        if (j % 10000 == 0) :
            print("elems: ", j / 10000)
        test_str += str(random.randint(1, 2000)) + " "

    file.write(test_str)
    file.close()

    print("test ", i + 1, " generated")