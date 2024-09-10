#include <iostream>
#include <vector>
#include "cache_belady.hpp"

int hash_func(int elem) {
    return elem;
}

int slow_get_elem(int key) {
    return key;
}

int main()
{
    int cache_size = 0, count_of_elems = 0;
    std::cin >> cache_size >> count_of_elems;

    if (cache_size <= 0 || count_of_elems <= 0) {
        std::cout << "Incorrect input\n";
        return 0;
    }

    std::vector<int> keys;
    for (int i = 0, elem; i < count_of_elems; ++i) {
        std::cin >> elem;
        keys.push_back(hash_func(elem));
    }

    cache_belady::cache_t<int> cache(cache_size, keys.begin(), keys.end());
    for (int i = 0; i < count_of_elems; ++i) {
        cache.lookup_update(keys[i], slow_get_elem);

#ifdef DEBUG
        cache.print();
        cache.print_indexes();
#endif
    }

    std::cout << cache.get_hits() << "\n";
    return 0;
}