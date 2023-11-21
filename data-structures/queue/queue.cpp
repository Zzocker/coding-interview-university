#include "queue.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

Queue::Queue(int s) : r_index{0}, w_index{0},bucket{vector<int> (s + 1)} {}
void Queue::enqueue(int elem){
    if (is_full()) throw(QueueException("Full queue"));
    bucket[w_index] = elem;
    w_index = (w_index + 1)%bucket.size();
}

int Queue::front() const {
    if (is_empty()) throw(QueueException("Empty queue"));
    return bucket[r_index];
}

int Queue::dequeue(){
    if (is_empty()) throw(QueueException("Empty queue"));
    int front = bucket[r_index];
    r_index = (r_index + 1)%bucket.size();
    return front;
}

bool Queue::is_empty() const {
    return r_index == w_index;
}

bool Queue::is_full() const {
    return (w_index + 1)%bucket.size() == r_index;
}