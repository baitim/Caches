#pragma once

#include <list>
#include <unordered_map>
#include "ANSI_colors.hpp"

namespace cache_belady {

template <typename ElemT, typename KeyT = int> class cache_t final {
    int size_;

    using HashFuncT = KeyT (*)(ElemT elem);
    HashFuncT hash_func_;

    using cache_iter = typename std::list<std::pair<KeyT, ElemT>>::iterator;
    using hash_iter  = typename std::unordered_map<KeyT, cache_iter>::iterator;
    using ind_iter   = typename std::unordered_map<KeyT, std::list<int>>::iterator;
    std::list<std::pair<KeyT, ElemT>>        cache_;
    std::unordered_map<KeyT, cache_iter>     hash_;
    std::unordered_map<KeyT, std::list<int>> indexes;

public:
    cache_t(int size, const std::vector<int>& elems, HashFuncT hash_func) : size_(size), hash_func_(hash_func) {
        for (int i = 0, count = elems.size(); i < count; ++i) {
            KeyT key = hash_func_(elems[i]);

            ind_iter ind_it = indexes.find(key);
            if(ind_it == indexes.end())
                indexes.emplace(key, std::list<int> (1, i));
            else
                ind_it->second.push_back(i);
        }
    }

    bool full() const { 
        return ((int)cache_.size() == size_); 
    }

    void delete_elem(KeyT key) {
        ind_iter ind_it = indexes.find(key);
        if (ind_it->second.empty())
            return;

        KeyT key_pop = key;
        int dist_pop = ind_it->second.front();

        for (cache_iter cache_it = cache_.begin(), end = cache_.end(); cache_it != end; ++cache_it) {
            KeyT elem_key = cache_it->first;

            ind_iter ind_it = indexes.find(elem_key);

            if (ind_it->second.empty()) {
                key_pop = elem_key;
                break;
            }

            int dist_to_next_meet = ind_it->second.front();
            if (dist_to_next_meet > dist_pop) {
                key_pop = elem_key;
                dist_pop = dist_to_next_meet;
            }
        }

        if (key_pop == key)
            return;

        cache_iter cache_it = hash_.find(key_pop)->second;
        hash_.erase(key_pop);
        cache_.erase(cache_it);
    }

    void insert_elem(const ElemT& elem, KeyT key) {
        cache_.push_front(std::make_pair(key, elem));
        hash_.emplace(key, cache_.begin());
    }

    void update_elem(KeyT key) {
        ind_iter ind_it = indexes.find(key);
        ind_it->second.pop_front();
    }
    
    bool lookup_update(const ElemT& elem) {
        KeyT key = hash_func_(elem);
        update_elem(key);

        hash_iter hash_it = hash_.find(key);
        if(hash_it == hash_.end()) {

            if (full()) 
                delete_elem(key);
            
            if (!full())
                insert_elem(elem, key);

            return false;
        }
        return true;
    }

    void print() const {
        std::cout << print_lblue("\nCache:\nkey\telem\n");
        for (auto cache_it : cache_) {
            std::cout << print_lcyan(cache_it.first) << '\t' << print_lcyan(cache_it.second) << '\n';
        }
        std::cout << '\n';
    }

    void print_indexes() const {
        std::cout << print_lblue("\nIndexes:\nkey\tlen\tindexes\n");
        for (auto ind_it : indexes) {
            std::cout << print_lcyan(ind_it.first) << '\t' << print_lcyan(ind_it.second.size()) << '\t';
            for (auto ind : ind_it.second)
                std::cout << print_lcyan(ind) << "  ";
            std::cout << '\n';

        }
        std::cout << '\n';
    }
};

}