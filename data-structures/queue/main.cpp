#include "queue.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(){
    const int test_size = 16;
    Queue queue(test_size);
    assert(queue.is_empty());

    try {
        queue.dequeue();
        assert(false);
    }catch (const QueueException& e){
        assert(e.get_message() == "Empty queue");
    }


    queue.enqueue(1);
    assert(!queue.is_empty());
    assert(queue.front() == 1);

    assert(queue.dequeue() == 1);

    for (int i=0;i<test_size;i++) queue.enqueue(i);
    assert(queue.is_full());

    try {
        queue.enqueue(16);
        assert(false);
    }catch (const QueueException& e){
        assert(e.get_message() == "Full queue");
    }

    for (int i=0;i<test_size;i++){
        assert(queue.dequeue() == i);
    } 
}