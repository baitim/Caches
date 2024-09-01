#pragma once

#include <map>
#include <unordered_map>
#include "ANSI_colors.hpp"

namespace cache_lfu {

template <typename ElemT, typename KeyT = int> class cache_t final {
    int size_;
    using cache_iter = typename std::multimap<int, ElemT>::iterator;
    using hash_iter  = typename std::unordered_map<KeyT, cache_iter>::iterator;
    std::multimap<int, ElemT>            cache_; // frequency - element
    std::unordered_map<KeyT, cache_iter> hash_;

public:
    cache_t(int size) : size_(size) {}

    bool full() const { 
        return (hash_.size() == size_); 
    }

    template <typename HashFuncT> void delete_elem(HashFuncT hash_func) {
        cache_iter cache_it = cache_.begin();
        ElemT elem      = cache_it->second;
        KeyT key        = hash_func(elem);

        hash_.erase(key);
        cache_.erase(cache_it);
    }

    void insert_elem(const ElemT& elem, KeyT key) {
        cache_iter cache_it = cache_.emplace(1, elem);
        hash_.emplace(key, cache_it);
    }

    void update_elem(hash_iter hash_it, const ElemT& elem, KeyT key) {
        cache_iter cache_it_old = hash_it->second;
        int new_frequency = cache_it_old->first + 1;
        cache_.erase(cache_it_old);
        hash_.erase(key);

        cache_iter cache_it_new = cache_.emplace(new_frequency, elem);
        hash_.emplace(key, cache_it_new);
    }
    
    template <typename HashFuncT> bool lookup_update(const ElemT& elem, HashFuncT hash_func) {
        KeyT key = hash_func(elem);
        hash_iter hash_it = hash_.find(key);
        if(hash_it == hash_.end()) {

            if (full()) 
                delete_elem(hash_func);
            
            insert_elem(elem, key);
            return false;
        }
        
        update_elem(hash_it, elem, key);
        return true;
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