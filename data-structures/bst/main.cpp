#include <iostream>
#include "bst.h"
#include <cassert>

using namespace std;

int main(){
    BST tree;
    tree.insert(10);
    tree.insert(4);
    tree.insert(9);
    tree.insert(14);
    tree.insert(3);
    tree.insert(11);
    tree.insert(16);
    tree.print_values();cout << endl;

    assert(tree.exists(10));
    assert(!tree.exists(0));

    assert(tree.get_min() == 3);
    assert(tree.get_max() == 16);

    assert(tree.get_height(10) == 2);
    assert(tree.get_height(4) == 1);
    assert(tree.get_height(14) == 1);
    assert(tree.get_height(3) == 0);

    assert(tree.get_successor(10) == 11);
    assert(tree.get_successor(4) == 9);

    assert(tree.get_node_count() == 7);

    tree.insert(17);
    tree.remove(3);assert(!tree.exists(3));
    tree.remove(17);assert(!tree.exists(17));
    tree.remove(14);assert(!tree.exists(14));
    tree.print_values();cout << endl;
}