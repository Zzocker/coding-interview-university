#include <cassert>
#include "avl.h"

using namespace std;

int main(){
    AVL tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(9);
    tree.insert(7);
    tree.insert(4);

    tree.print_values();

    assert(!tree.exists(10));
    assert(tree.exists(9));

    // tree.remove(1);
    tree.remove(2);assert(!tree.exists(2));
    tree.remove(7);assert(!tree.exists(7));
    tree.remove(1);assert(!tree.exists(1));
}