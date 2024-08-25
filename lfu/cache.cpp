#include <iostream>
#include "cache.hpp"

int main()
{
    int cache_size = 0, count_of_elems = 0;
    std::cin >> cache_size >> count_of_elems;

    if (cache_size <= 0 || count_of_elems <= 0) {
        std::cout << "Incorrect input\n";
        return 0;
    }

    cache_t<int> cache(cache_size);

    int hits = 0;
    for (int i = 0, elem; i < count_of_elems; ++i) {
        std::cin >> elem;

        if (cache.lookup_update(elem, int2int))
            hits++;

        // cache.print();
    }

    std::cout << hits << "\n";
}