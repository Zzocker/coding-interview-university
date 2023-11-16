#include <vector>
#include "hash_table.h"
#include <iostream>

list<ChainNode>::iterator find(list<ChainNode>& list, int key){
    auto itr = list.begin();
    while (itr != list.end()){
        if (itr->key == key) break;
        itr++;
    }
    return itr;
}

list<ChainNode>::const_iterator find(const list<ChainNode>& list, int key){
    auto itr = list.begin();
    while (itr != list.end()){
        if (itr->key == key) break;
        itr++;
    }
    return itr;
}

HashTable::HashTable() : n{0}, m{MIN_BUCKET_SIZE}, bucket {vector<list<ChainNode>> (m)} {}

void HashTable::add(int key, int value) {
    if (n >= m) resize(GROWTH_FACTOR*m);
    int index = hash(key, m);
    auto node = find(bucket[index], key);
    if (node != bucket[index].end()){
        node->value = value;
    }else {
        bucket[index].push_front(ChainNode(key, value));
        n++;
    }
}

bool HashTable::exists(int key) const {
    int index = hash(key, m);
    auto node = find(bucket[index], key);
    return node != bucket[index].end();
}

int HashTable::get(int key) const {
    int index = hash(key, m);
    auto node = find(bucket[index], key);
    if (node == bucket[index].end()) throw(HashTableException("key not found"));
    return node->value;
}

void HashTable::remove(int key){
    int index = hash(key, m);
    auto node = find(bucket[index], key);
    if (node == bucket[index].end()) return;
    bucket[index].erase(node);
    n--;
    if (4*n <= m) resize(m/SHRINK_fACTOR);
}

int HashTable::hash(int key, int m) const {
    // simple division hashing
    return key%m;
}

void HashTable::resize(int new_m) {
    if (new_m <= MIN_BUCKET_SIZE) return;
    vector<list<ChainNode>> new_bucket(new_m);
    for (int i=0;i<bucket.size();i++){
        auto itr = bucket[i].begin();
        while (itr != bucket[i].end()){
            int index = hash(itr->key, new_m);
            new_bucket[index].push_front(ChainNode(itr->key, itr->value));
            itr++;
        }
    }
    m = new_m;
    bucket = new_bucket;
}