#include "array.h"
#include <cassert>
#include <iostream>

using namespace std;


int main(){
    Array array;
   
    assert(array.is_empty());array.push(1);assert(!array.is_empty());
    array.push(2);assert(array.get_size() == 2);

    assert(array.at(1) == 2);
    array.push(3);array.insert(2,4);assert(array.at(2) == 4);

    array.prepend(0);assert(array.at(0) == 0);assert(array.get_size() == 5);

    assert(array.pop() == 3);assert(array.get_size() == 4);

    array.delete_item(2);assert(array.at(2) == 4);assert(array.get_size() == 3);

    array.push(5);array.push(6);array.push(7);
    array.remove(5);assert(array.get_size() == 5);assert(array.at(3) == 6);

    assert(array.find(5) == -1);assert(array.find(4) == 2);
}