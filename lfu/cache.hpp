#pragma once

#include <list>
#include <map>
#include <unordered_map>
#include "ANSI_colors.hpp"

int int2int(int elem) {
    return elem;
}

template <typename ElemT, typename KeyT = int> class cache_t {
    int size_;
    using map_iter   = typename std::multimap<int, ElemT>::iterator;
    using cache_iter = typename std::unordered_map<KeyT, map_iter>::iterator;
    std::multimap<int, ElemT> freq_map_;       // frequency - element
    std::unordered_map<KeyT, map_iter> cache_;

public:
    cache_t(int size) : size_(size) {};

    bool full() const { 
        return (cache_.size() == size_); 
    }

    template <typename HashFuncT> void delete_elem(HashFuncT hash_func) {
        map_iter map_it = freq_map_.begin();
        ElemT elem      = map_it->second;
        KeyT key        = hash_func(elem);

        cache_.erase(key);
        freq_map_.erase(map_it);
    }

    void insert_elem(ElemT elem, KeyT key) {
        map_iter map_it = freq_map_.emplace(1, elem);
        cache_.emplace(key, map_it);
    }

    void update_elem(cache_iter cache_it, ElemT elem, KeyT key) {
        map_iter map_it = cache_it->second;
        int new_frequency = map_it->first + 1;
        freq_map_.erase(map_it);

        map_iter map_it_new = freq_map_.emplace(map_it->first + 1, elem);
        cache_.emplace(key, map_it);
    }
    
    template <typename HashFuncT> bool lookup_update(ElemT elem, HashFuncT hash_func) {
        KeyT key = hash_func(elem);
        cache_iter cache_it = cache_.find(key);
        if(cache_it == cache_.end()) {

            if (full()) 
                delete_elem(hash_func);
            
            insert_elem(elem, key);
            return false;
        }
        
        update_elem(cache_it, elem, key);
        return true;
    }

    void print() const {
        std::cout << print_lblue("\nCache:\n");
        for (auto cache_it : cache_) {
            map_iter map_it = cache_it.second;
            std::cout << print_lcyan(map_it->first) << '\t' << print_lcyan(map_it->second) << '\n';
        }
        std::cout << '\n';
    }
};