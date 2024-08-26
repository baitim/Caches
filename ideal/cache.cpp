#include <iostream>
#include <vector>
#include "cache.hpp"

int main()
{
    int cache_size = 0, count_of_elems = 0;
    std::cin >> cache_size >> count_of_elems;

    if (cache_size <= 0 || count_of_elems <= 0) {
        std::cout << "Incorrect input\n";
        return 0;
    }

    std::vector<int> elems;
    for (int i = 0, elem; i < count_of_elems; ++i) {
        std::cin >> elem;
        elems.push_back(elem);
    }

    cache::cache_t<int> cache(cache_size, elems, int2int);
    int hits = 0;
    for (int i = 0; i < count_of_elems; ++i) {
        if (cache.lookup_update(elems[i], int2int))
            hits++;

#ifdef DEBUG
        cache.print();
        cache.print_indexes();
#endif
    }

    std::cout << hits << "\n";
}