#include "queue.h"
#include <cassert>

using namespace std;

int main(){
    Queue queue;
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

    const int test_size = 16;
    for (int i=0;i<test_size;i++)queue.enqueue(i);
    for (int i=0;i<test_size;i++){
        assert(queue.dequeue() == i);
    } 
}