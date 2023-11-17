#include <vector>
#include "hash_table.h"
#include <iostream>

HashTable::HashTable() : n{0}, m{MIN_BUCKET_SIZE}, bucket {vector<ChainNode*> (m)} {}

const int H_2 = 7;

// open address + double hash

void HashTable::add(int key, int value) {
    if (n >= m) resize(GROWTH_FACTOR*m);
    int h = hash(key, m);
    int trail = 0;
    int index = h;
    while (trail < m ){
        index = (h + trail*H_2) % m;
        if (bucket[index] == NULL){
            bucket[index] = new ChainNode(key, value);
            n++;
            break;
        }else if (bucket[index]->key == key && bucket[index]->deleted){
            bucket[index]->value = value;
            bucket[index]->deleted = false;
            n++;
        }else if (bucket[index]->key == key){
            bucket[index]->value = value;
        }
        trail++;
    }
}

bool HashTable::exists(int key) const {
    int h = hash(key, m);
    int trail = 0;
    int index = h;
    while (trail < m){
        index = (h + trail*H_2)%m;
        if (bucket[index] == NULL || (bucket[index]->key == key && bucket[index]->deleted))return false;
        else if (bucket[index]->key == key)return true;
        trail++;
    }
    return false;
}

int HashTable::get(int key) const {
    int h = hash(key, m);
    int trail = 0;
    int index = h;
    while (trail < m){
        index = (h + trail*H_2)%m;
        if (bucket[index] == NULL || (bucket[index]->key == key && bucket[index]->deleted)) throw(HashTableException("key not found"));
        if (bucket[index]->key == key) return bucket[index]->value;
        trail++;
    }
    throw(HashTableException("key not found"));
}

void HashTable::remove(int key){
    int h = hash(key, m);
    int trail = 0;
    int index = h;
    while (trail < m){
        index = (h + trail*H_2)%m;
        if (bucket[index] == NULL || (bucket[index]->key == key && bucket[index]->deleted)) return;
        else if (bucket[index]->key == key) {
            bucket[index]->deleted = true;
            n--;
            return;
        }
        trail++;
    }
}

int HashTable::hash(int key, int m) const {
    // simple division hashing
    return key%m;
}

void HashTable::resize(int new_m) {
    if (new_m <= MIN_BUCKET_SIZE) return;
    vector<ChainNode*> new_bucket(new_m);
    for (int i=0;i<bucket.size();i++){
        if (bucket[i] != NULL){
           if (bucket[i]->deleted) delete bucket[i];
           else {
            int h = hash(bucket[i]->key,new_m);
            int trail = 0;
            int index = h;
            while (trail < new_m){
                int index = (h + trail*H_2)%new_m;
                if (new_bucket[index] == NULL) {
                    new_bucket[index] = bucket[i];
                    break;
                }
                trail ++;
            }
           } 
        }
    }
    m = new_m;
    bucket = new_bucket;
}