#include "queue.h"
#include <string>
#include <list>

using std::string;
using std::list;

Queue::Queue() : bucket{list<int> ()} {}
void Queue::enqueue(int elem){
    bucket.push_back(elem);
}

int Queue::front() const {
    if (is_empty()) throw(QueueException("Empty Queue"));
    return bucket.front();
}

int Queue::dequeue(){
    if (is_empty()) throw(QueueException("Empty Queue"));
    int front = bucket.front();
    bucket.pop_front();
    return front;
}

bool Queue::is_empty() const {
    return bucket.empty();
}