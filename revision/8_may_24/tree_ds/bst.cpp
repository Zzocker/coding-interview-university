#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

using namespace std;

class BSTNode{
    public:
        int val;
        BSTNode* left;
        BSTNode* right;
        BSTNode(int v): val{v}, left{NULL}, right{NULL} {}
};

class BST{
    private:
        BSTNode* root;

        BSTNode* insert(BSTNode* node, int value){
            if (node == NULL) return new BSTNode(value);

            if (value < node->val) node->left = insert(node->left, value);
            else if (value > node->val) node->right = insert(node->right, value);
            return node;
        }

        int smallest_value(BSTNode* node){
            if (node->left == NULL) return node->val;
            return smallest_value(node->left);
        }

        BSTNode* remove(BSTNode* node, int value){
            if (node == NULL) return NULL;
            if (node->val == value){
                if (node->left == NULL && node->right == NULL){
                    delete node;
                    return NULL;
                }else if (node->left == NULL){
                    BSTNode* next_node = node->right;
                    delete node;
                    return next_node;
                }else if (node->right == NULL){
                    BSTNode* next_node = node->left;
                    delete node;
                    return next_node;
                }else {
                    int new_value = smallest_value(node->right);
                    node->val = new_value;
                    node->right = remove(node->right, new_value);
                }
            }else if (value < node->val) node->left = remove(node->left, value);
            else node->right = remove(node->right, value);
            return node;
        }

        void pre_order(BSTNode* node, vector<int>& out) const {
            if (node == NULL) return;
            out.push_back(node->val);
            pre_order(node->left, out);
            pre_order(node->right, out);
        }

        void in_order(BSTNode* node, vector<int>& out) const {
            if (node == NULL) return;
            in_order(node->left, out);
            out.push_back(node->val);
            in_order(node->right, out);
        }

        void post_order(BSTNode* node, vector<int>& out) const {
            if (node == NULL) return;
            post_order(node->left, out);
            post_order(node->right, out);
            out.push_back(node->val);
        }

        bool exists(BSTNode* node, int value) const {
            if (node == NULL) return false;
            if (node->val == value) return true;
            else if (value < node->val) return exists(node->left, value);
            return exists(node->right, value);
        }
    public:
        BST() : root{NULL} {}

        void insert(int val){
            root = insert(root, val);
        }

        void remove(int val){
            root = remove(root, val);
        }

        vector<int> pre_order() const {
            vector<int> out;
            pre_order(root, out);
            return out;
        }
        vector<int> in_order() const {
            vector<int> out;
            in_order(root, out);
            return out;
        }
        vector<int> post_order() const {
            vector<int> out;
            post_order(root, out);
            return out;
        }
        vector<int> bfs() const {
            vector<int> out;
            queue<BSTNode*> q;
            q.push(root);
            out.push_back(root->val);
            while (!q.empty()){
                auto node = q.front();q.pop();
                if (node->left != NULL){
                    out.push_back(node->left->val);
                    q.push(node->left);
                }
                if (node->right != NULL){
                    out.push_back(node->right->val);
                    q.push(node->right);
                }
            }
            return out;
        }
        bool exists(int val) const {
            return exists(root, val);
        }
};

int main() {
    // Create a binary search tree
    BST bst;

    // Test insert() function
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(17);

    // Test pre_order() function
    vector<int> preOrderResult = bst.pre_order();
    assert(preOrderResult == vector<int>({10, 5, 3, 7, 15, 12, 17}));

    // Test in_order() function
    vector<int> inOrderResult = bst.in_order();
    assert(inOrderResult == vector<int>({3, 5, 7, 10, 12, 15, 17}));

    // Test post_order() function
    vector<int> postOrderResult = bst.post_order();
    assert(postOrderResult == vector<int>({3, 7, 5, 12, 17, 15, 10}));

    // Test bfs() function
    vector<int> bfsResult = bst.bfs();
    assert(bfsResult == vector<int>({10, 5, 15, 3, 7, 12, 17}));

    // Test exists() function
    assert(bst.exists(5));
    assert(!bst.exists(8));

    bst.remove(5); // Remove node with value 5
    assert(!bst.exists(5)); // Check if 5 is removed
    assert(bst.pre_order() == vector<int>({10, 7, 3, 15, 12, 17}));

    return 0;
}