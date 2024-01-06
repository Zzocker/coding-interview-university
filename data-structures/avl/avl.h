#ifndef AVL_H
#define AVL_H

#include <cstddef>

class Node{
    public:
        Node* left;
        int val;
        Node* right;
        int height;

        Node(int v): left{NULL}, val{v}, right{NULL}, height{0} {}
};

class AVL{
    private:
        Node* root;
    public:
        AVL();
        ~AVL();
        void insert(int elem);
        void print_values() const;
        bool exists(int elem) const;
        void remove(int elem);
};


#endif