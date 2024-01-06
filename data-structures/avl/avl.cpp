#include <bits/stdc++.h>
#include <queue>
#include <iostream>
#include "avl.h"

using namespace std;

AVL::AVL() : root{NULL}{}

// get balance factor
int get_bf(Node* node){
    int lc = node->left ? node->left->height + 1: 0;
    int rc = node->right ? node->right->height + 1: 0;
    return lc - rc;
}

int get_height(Node* node){
    int child = -1;
    if (node->left) child = max(child, node->left->height);
    if (node->right) child = max(child, node->right->height);
    return 1 + child;
}

Node* ll_rotation(Node* node){
    auto A = node;
    auto B = node->left;
    auto C = node->left->left;
    auto Br = B->right;
    B->right = A;
    A->left = Br;
    A->height = get_height(A);
    B->height = get_height(B);
    return B;
}

Node* lr_rotation(Node* node){
    auto A = node;
    auto B = node->left;
    auto C = node->left->right;
    auto Cl = C->left;
    auto Cr = C->right;
    B->right = Cl;
    B->height = get_height(B);
    A->left = Cr;
    A->height = get_height(A);
    C->left = B;
    C->right = A;
    C->height = get_height(C);
    return C;
}

Node* rl_rotation(Node* node){
    auto A = node;
    auto B = node->right;
    auto C = node->right->left;
    auto Cl = C->left;
    auto Cr = C->right;
    B->left = Cr;
    B->height = get_height(B);
    A->right = Cl;
    A->height = get_height(A);
    C->left = A;
    C->right = B;
    C->height = get_height(C);
    return C;
}

Node* rr_rotation(Node* node){
    auto A = node;
    auto B = node->right;
    auto C = node->right->right;
    auto Bl = B->left;
    A->right = Bl;
    A->height = get_height(A);
    B->left = A;
    B->height = get_height(B);
    return B;
}

Node* balance_tree(Node* node){
    if (get_bf(node) == 2){ // L
        if (get_bf(node->left) == 1){ // LL
            return ll_rotation(node);
        }else { // LR
            return lr_rotation(node);
        }
    }else if (get_bf(node) == -2) { // R
        if (get_bf(node->right) == 1) { // RL
            return rl_rotation(node);
        }else { // RR
            return rr_rotation(node);
        }
    }
    node->height = get_height(node);
    return node;
}

Node* _insert(Node* node, int elem){
    if (node == NULL){
        return new Node(elem);
    }
    if (elem <= node->val) {
        node->left = _insert(node->left, elem);
    }else {
        node->right = _insert(node->right, elem);
    }
    return balance_tree(node);
}

void AVL::insert(int elem){
    root = _insert(root, elem);
}

AVL::~AVL(){
    if (root==NULL)return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()){
        auto node = q.front();q.pop();
        if (node->left)q.push(node->left);
        if (node->right)q.push(node->right);
        delete  node;
    }
}

void in_order(Node* node){
    if (node == NULL)return;
    in_order(node->left);
    cout << (node->val) << " ";
    in_order(node->right);
}

void AVL::print_values() const{
    in_order(root);
    cout << endl;
}

bool AVL::exists(int elem) const {
    Node* node = root;
    while (node!=NULL){
        if (node->val == elem)break;
        else if (elem < node->val) node = node->left;
        else node = node->right;
    }
    return node != NULL;
}

int get_min(Node* node){
    if (node->left == NULL) return node->val;
    return get_min(node->left);
}

Node* _remove(Node* node, int elem){
    if (node == NULL) return node;
    if (node->val == elem){
        if (node->left == NULL && node->right == NULL){
            delete node;
            return NULL;
        }else if (node->left == NULL){
            auto next = node->right;
            delete node;
            return next;
        }else if (node->right == NULL){
            auto next = node->left;
            delete node;
            return next;
        }else {
            int replacement = get_min(node->right);
            node->val = replacement;
            node->right = _remove(node->right, replacement);
            node->height = get_height(node);
            return node;
        }
    }else if (elem < node->val){
        node->left = _remove(node->left, elem);
    }else {
        node->right = _remove(node->right, elem);
    }
    return balance_tree(node);
}

void AVL::remove(int elem){
    root = _remove(root,elem);
}