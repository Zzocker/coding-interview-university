#ifndef BST_H
#define BST_H

#include <cstddef>

class Node{
    private:
        int data;
        Node* left;
        Node* right;
    public:
        Node();
        Node(int d); 

        void set_data(int data);
        void set_left(Node* node);
        void set_right(Node* node);

        int get_data() const;
        Node* get_left() const;
        Node* get_right() const;
};

class BST{
    private:
        Node* root;
    public:
        BST();
        ~BST();
        void insert(int elem);
        int get_node_count() const;
        void print_values() const;
        bool exists(int elem) const;
        int get_height(int elem) const;
        int get_min() const;
        int get_max() const;
        void remove(int elem);
        int get_successor(int elem) const;
};

#endif