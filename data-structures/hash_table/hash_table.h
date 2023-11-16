#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <list>
#include <string>

using std::vector;
using std::list;
using std::string;

const int MIN_BUCKET_SIZE = 8;
const int GROWTH_FACTOR = 2;
const int SHRINK_fACTOR = 2;

class HashTableException{
    public:
        HashTableException(const string& msg): message {msg} {}
        const string& get_message() const {return message;}
    private:
        string message;
};

class ChainNode{
    public:
        ChainNode(int k, int v): key{k}, value{v} {}
        int key;
        int value;
};

class HashTable{
    public:
        HashTable();
        void add(int key, int value);
        bool exists(int key) const;
        int get(int key) const;
        void remove(int key);
    private:
        int n;
        int m;
        vector<list<ChainNode>> bucket;
        int hash(int key, int m) const;
        void resize(int new_m);
};

#endif