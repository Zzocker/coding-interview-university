#include <iostream>
#include <cassert>
#include "linked_list.h"

using namespace std;

int main(){
    LinkedList list;

    // 
    assert(list.get_size() == 0);assert(list.is_empty());

    try {
        list.value_at(0);
        assert(true);
    }catch (const LinkedListException& e){
        assert(e.get_message() == "index out of bound");
    }
    
    // 
    list.push_front(1);assert(list.get_size() == 1);assert(!list.is_empty());

    // 1
    list.push_front(2);list.push_front(3);

    // 3 2 1
    assert(list.front() == 3);assert(list.value_at(0) == 3);assert(list.value_at(1) == 2);assert(list.value_at(2) == 1);

    // 3 2 1
    assert(list.pop_front() == 3);assert(list.get_size() == 2);

    // 2 1
    list.push_back(0);assert(list.get_size() == 3);assert(list.value_at(2) == 0);assert(list.back() == 0);

    // 2 1 0
    assert(list.pop_back() == 0);assert(list.get_size() == 2);assert(list.back() == 1);

    // 2 1
    list.insert(0, 3);assert(list.value_at(0) == 3);assert(list.get_size() == 3);

    // 3 2 1
    list.insert(1, 4);assert(list.value_at(1) == 4);assert(list.get_size() == 4);

    // 3 4 2 1
    list.erase(2);assert(list.get_size() == 3);assert(list.value_at(2) == 1);

    // 3 4 1
    assert(list.value_n_from_end(1) == 1);assert(list.value_n_from_end(2) == 4);assert(list.value_n_from_end(3) == 3);

    // 3 4 1
    list.reverse();
    
    // 1 4 3
    assert(list.value_at(0) == 1);assert(list.value_at(1) == 4);assert(list.value_at(2) == 3);

    // 1 4 3
    list.remove_value(3);

    // 1 4
    assert(list.get_size() == 2);assert(list.value_at(0) == 1);assert(list.value_at(1) == 4);
}