#include <iostream>
#include "cache_arc.hpp"

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

    cache_arc::cache_t<int> cache(cache_size);

    for (int i = 0, elem; i < count_of_elems; ++i) {
        std::cin >> elem;
        cache.lookup_update(elem, slow_get_elem);

#ifdef DEBUG
        cache.print();
#endif
    }

    std::cout << cache.get_hits() << "\n";
    return 0;
}