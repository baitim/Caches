#pragma once

#include <map>
#include <unordered_map>
#include "ANSI_colors.hpp"

namespace cache_lfu {

template <typename ElemT, typename KeyT = int> class cache_t final {
    int size_;
    int hits_ = 0;

    using cache_iter = typename std::multimap<int, std::pair<KeyT, ElemT>>::iterator;
    using hash_iter  = typename std::unordered_map<KeyT, cache_iter>::iterator;
    std::multimap<int, std::pair<KeyT, ElemT>> cache_; // frequency - element
    std::unordered_map<KeyT, cache_iter>       hash_;

private:
    bool full() const { 
        return ((int)hash_.size() == size_); 
    }

    void delete_elem() {
        cache_iter cache_it = cache_.begin();
        KeyT key = cache_it->second.first;

        hash_.erase(key);
        cache_.erase(cache_it);
    }

    void insert_elem(const ElemT& elem, KeyT key) {
        cache_iter cache_it = cache_.emplace(1, std::make_pair(key, elem));
        hash_.emplace(key, cache_it);
    }

    void update_elem(hash_iter hash_it, KeyT key) {
        cache_iter cache_it_old = hash_it->second;
        int frequency_old = cache_it_old->first;
        ElemT elem = cache_it_old->second.second;

        cache_.erase(cache_it_old);
        hash_.erase(key);

        cache_iter cache_it_new = cache_.emplace(frequency_old + 1, std::make_pair(key, elem));
        hash_.emplace(key, cache_it_new);
    }

public:
    cache_t(int size) : size_(size) {}

    int get_hits() {
        return hits_;
    }
    
    template <typename SlowGetElemT> bool lookup_update(const KeyT& key, SlowGetElemT slow_get_elem) {
        hash_iter hash_it = hash_.find(key);
        if(hash_it == hash_.end()) {

            if (full()) 
                delete_elem();
            
            ElemT elem = slow_get_elem(key);
            insert_elem(elem, key);

            return elem;
        }
        
        update_elem(hash_it, key);
        hits_++;

        hash_it = hash_.find(key);
        cache_iter cache_it = hash_it->second;
        ElemT elem = cache_it->second.second;
        return elem;
    }

    void print() const {
        std::cout << print_lblue("\nCache:\nfreq\telem\n");
        for (auto cache_it : cache_) {
            std::cout << print_lcyan(cache_it.first) << '\t' << print_lcyan(cache_it.second) << '\n';
        }
        std::cout << '\n';
    }
};

}