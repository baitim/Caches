#pragma once

#include <list>
#include <unordered_map>
#include "ANSI_colors.hpp"

namespace cache_arc {

template <typename ElemT, typename KeyT = int> class cache_t final {
    int cache_size_;
    int size_t1_, size_t2_;
    int size_b1_, size_b2_;
    int hits_ = 0;
    int size_factor_1;

    using cache_iter_b = typename std::list<KeyT>::iterator;
    using cache_iter_t = typename std::list<std::pair<KeyT, ElemT>>::iterator;
    using hash_iter_b  = typename std::unordered_map<KeyT, cache_iter_b>::iterator;
    using hash_iter_t  = typename std::unordered_map<KeyT, cache_iter_t>::iterator;

    std::list<KeyT> cache_b1_;
    std::list<KeyT> cache_b2_;
    std::list<std::pair<KeyT, ElemT>> cache_t1_;
    std::list<std::pair<KeyT, ElemT>> cache_t2_;

    std::unordered_map<KeyT, cache_iter_b> ht_b1_;
    std::unordered_map<KeyT, cache_iter_b> ht_b2_;
    std::unordered_map<KeyT, cache_iter_t> ht_t1_;
    std::unordered_map<KeyT, cache_iter_t> ht_t2_;

private:
    bool full_t1() const { 
        return ((int)cache_t1_.size() == size_t1_); 
    }

    bool full_t2() const { 
        return ((int)cache_t2_.size() == size_t2_); 
    }

    bool full_b1() const { 
        return ((int)cache_b1_.size() == size_b1_); 
    }

    bool full_b2() const { 
        return ((int)cache_b2_.size() == size_b2_); 
    }

    void decrease_b1() {
        if (!ht_b1_.empty()) {
            KeyT key_cache_t_pop = cache_b1_.back();
            ht_b1_.erase(key_cache_t_pop);
            cache_b1_.pop_back();
        }
    }

    void decrease_b2() {
        if (!ht_b2_.empty()) {
            KeyT key_cache_t_pop = cache_b2_.back();
            ht_b2_.erase(key_cache_t_pop);
            cache_b2_.pop_back();
        }
    }

    void decrease_t1() {
        if (!ht_t1_.empty()) {
            KeyT key_cache_t_pop = cache_t1_.back().first;
            ht_t1_.erase(key_cache_t_pop);
            cache_t1_.pop_back();
            
            if (full_b1())
                decrease_b1();

            cache_b1_.push_front(key_cache_t_pop);
            ht_b1_.emplace(key_cache_t_pop, cache_b1_.begin());
        }
    }

    void decrease_t2() {
        if (!ht_t2_.empty()) {
            KeyT key_cache_t_pop = cache_t2_.back().first;
            ht_t2_.erase(key_cache_t_pop);
            cache_t2_.pop_back();
            
            if (full_b2())
                decrease_b2();

            cache_b2_.push_front(key_cache_t_pop);
            ht_b2_.emplace(key_cache_t_pop, cache_b2_.begin());
        }
    }

    void delete_old_elem(KeyT key) {
        hash_iter_t hash_it_t = ht_t1_.find(key);
        if (ht_t1_.find(key) != ht_t1_.end()) {
            cache_t1_.erase(hash_it_t->second);
            ht_t1_.erase(hash_it_t);
        }

        hash_it_t = ht_t2_.find(key);
        if (ht_t2_.find(key) != ht_t2_.end()) {
            cache_t2_.erase(hash_it_t->second);
            ht_t2_.erase(hash_it_t);
        }

        hash_iter_b hash_it_b = ht_b1_.find(key);
        if (ht_b1_.find(key) != ht_b1_.end()) {
            cache_b1_.erase(hash_it_b->second);
            ht_b1_.erase(hash_it_b);
        }

        hash_it_b = ht_b2_.find(key);
        if (ht_b2_.find(key) != ht_b2_.end()) {
            cache_b2_.erase(hash_it_b->second);
            ht_b2_.erase(hash_it_b);
        }
    }

    void insert_old_elem(const ElemT& elem, KeyT key) {
        if (size_t2_ <= 0) 
            return;

        if (full_t2())
            decrease_t2();

        cache_t2_.push_front(std::make_pair(key, elem));
        ht_t2_.emplace(key, cache_t2_.begin());
    }

    bool is_in_t(KeyT key) const {
        if (ht_t1_.find(key) != ht_t1_.end())
            return true;

        if (ht_t2_.find(key) != ht_t2_.end())
            return true;

        return false;
    }

    void insert_new_elem(const ElemT& elem, KeyT key) {
        if (size_t1_ <= 0) 
            return;

        if (full_t1())
            decrease_t1();

        cache_t1_.push_front(std::make_pair(key, elem));
        ht_t1_.emplace(key, cache_t1_.begin());
    }

    void move_factor() {
        if (size_factor_1 > (int)cache_t1_.size()) {
            if (full_t2())
                decrease_t2();
            size_t1_++;
            size_t2_--;
        } else if (size_factor_1 < (int)cache_t1_.size()) {
            if (full_t1())
                decrease_t1();
            size_t2_++;
            size_t1_--;
        }
    }

    void update(KeyT key) {
        if (is_old(key) && !is_in_t(key)) {
            if (ht_b1_.find(key) != ht_b1_.end())
                size_factor_1 = std::min(size_factor_1 + 1, cache_size_ - 1);
            else
                size_factor_1 = std::max(size_factor_1 - 1, 1);
        } else {
            move_factor();
        }
    }

    bool is_old(KeyT key) const {
        if (is_in_t(key))
            return true;
        
        if (ht_b1_.find(key) != ht_b1_.end())
            return true;

        if (ht_b2_.find(key) != ht_b2_.end())
            return true;

        return false;
    }

    template <typename SlowGetElemT> 
    ElemT get_elem(KeyT key, SlowGetElemT slow_get_elem) {
        hash_iter_t hash_it1 = ht_t1_.find(key);
        if (hash_it1 != ht_t1_.end())
            return hash_it1->second->second;

        hash_iter_t hash_it2 = ht_t2_.find(key);
        if (hash_it2 != ht_t2_.end())
            return hash_it2->second->second;

        return slow_get_elem(key);
    }

public:
    cache_t(int size) : cache_size_(size),  size_t1_(size / 2), size_t2_(size - size_t1_),
                        size_b1_(size_t1_), size_b2_(size_t2_), size_factor_1(size_t1_){}

    int get_hits() const {
        return hits_;
    }
    
    template <typename SlowGetElemT> ElemT lookup_update(KeyT key, SlowGetElemT slow_get_elem) {
        if (is_in_t(key))
            hits_++;

        update(key);

        ElemT elem = get_elem(key, slow_get_elem);

        if(is_old(key)) {
            delete_old_elem(key);
            insert_old_elem(elem, key);
        } else {
            insert_new_elem(elem, key);
        }

        return elem;
    }

    void print() const {
        std::cout << print_lblue("\nCache:\nkey\telem\n");
        std::cout << print_lblue("size_t1_ = " << size_t1_ << "\tsize_t2_ = "     << size_t2_ << "\n");
        std::cout << print_lblue("size_b1_ = " << size_b1_ << "\tsize_b2_ = "     << size_b2_ << "\n");
        std::cout << print_lblue("hits_ = "    << hits_ <<    "\tsize_factor_ = " << size_factor_1 << "\n");

        for (auto cache_it : cache_b1_)
            std::cout << print_lcyan("(" << cache_it << "),");
        std::cout << print_lcyan("[");
        for (auto cache_it : cache_t1_)
            std::cout << print_lcyan("(" << cache_it.first << ',' << cache_it.second << "),");

        std::cout << print_lcyan("!");

        for (auto cache_it : cache_t2_)
            std::cout << print_lcyan("(" << cache_it.first << ',' << cache_it.second << "),");
        std::cout << print_lcyan("]");
        for (auto cache_it : cache_b2_)
            std::cout << print_lcyan("(" << cache_it << "),");
        
        std::cout << '\n';
    }
};

}