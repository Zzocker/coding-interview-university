#include "bst.h"
#include <queue>
#include <iostream>

using namespace std;

Node::Node() : left{NULL}, right{NULL} {}
Node::Node(int d) : data{d}, left{NULL}, right{NULL} {}

void Node::set_data(int d) { data = d;}
void Node::set_left(Node* node) { left = node;}
void Node::set_right(Node* node) { right = node;}


int Node::get_data() const { return data;}
Node* Node::get_left() const { return left;}
Node* Node::get_right() const { return right;}

void pre_order(const Node* node){
    if (node == NULL)return;
    pre_order(node->get_left());
    cout << node->get_data() << " ";
    pre_order(node->get_right());
}

BST::BST(): root{NULL} {}
BST::~BST() {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()){
        auto node = q.front();q.pop();
        if (node->get_left()) q.push(node->get_left());
        if (node->get_right())q.push(node->get_right());
        delete node;
    }
}

Node* insert_in_tree(Node* node, int elem){
    if (node == NULL) {
        return new Node(elem);
    }
    if (elem <= node->get_data()){
        node->set_left(insert_in_tree(node->get_left(), elem));
    }else if (elem > node->get_data()){
        node->set_right(insert_in_tree(node->get_right(), elem));
    }
    return node;
}

void BST::insert(int elem){
    root = insert_in_tree(root, elem);
}

const Node* search(const Node* node, int elem){
    if (node == NULL) return node;
    if (node->get_data() == elem) return node;
    else if (elem < node->get_data()) return search(node->get_left(), elem);
    return search(node->get_right(), elem);
}


bool BST::exists(int elem) const {
    return search(root, elem) != NULL;
}

void BST::print_values() const {
    pre_order(root);
}

int BST::get_min() const {
    auto node = root;
    while (node != NULL && node->get_left() != NULL)node = node->get_left();
    return node->get_data();
}

int BST::get_max() const {
    auto node = root;
    while (node != NULL && node->get_right() != NULL)node = node->get_right();
    return node->get_data();
}

int __get_height(const Node* node) {
    if (node == NULL) return -1;
    return 1 + max(
        __get_height(node->get_left()),
        __get_height(node->get_right())
    );
}

int BST::get_height(int elem) const {
    auto node = search(root, elem);
    return __get_height(node);
}

int BST::get_successor(int elem) const {
    auto node = search(root, elem);
    if (node == NULL || node->get_right() == NULL) return -1;
    auto successor = node->get_right();
    while (successor->get_left() != NULL)successor=successor->get_left();
    return successor->get_data(); 
}

int node_count(const Node* node){
    if (node == NULL) return 0;
    return 1 + node_count(node->get_left()) + node_count(node->get_right());
}

int BST::get_node_count() const {
    return node_count(root);
}

Node* get_successor(Node* node){
    node = node->get_right();
    while (node != NULL && node->get_left() != NULL)node=node->get_left();
    return node;
}

Node* __remove(Node* node, int elem){
    if (node == NULL) return NULL;
    if (node->get_data() == elem){
        if (node->get_left() == NULL && node->get_right() == NULL){
            delete node;
            return NULL;
        }else if (node->get_left() == NULL){
            auto next = node->get_right();
            delete node;
            return next;
        }else if (node->get_right() == NULL){
            auto next = node->get_left();
            delete node;
            return next;
        }else {
            auto successor = get_successor(node);
            node->set_data(successor->get_data());
            successor->set_data(elem);
            node->set_right(__remove(node->get_right(), elem));
            return node;
        }
    }else if (elem < node->get_data()) {
        node->set_left(__remove(node->get_left(), elem));
    }else {
        node->set_right(__remove(node->get_right(), elem));
    }
    return node;
}

void BST::remove(int elem) {
    __remove(root, elem);
}