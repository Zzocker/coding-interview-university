#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class CyclicQueue{
    private:
        vector<int> bucket;
        int read;
        int write;
    public:
        CyclicQueue(int n) : read{0}, write{0}, bucket(n+1) {}
        bool empty(){
            return read == write;
        }

        bool full(){
            return (write + 1)%bucket.size() == read;
        }

        void push(int value){
            if (full()) return;
            bucket[write] = value;
            write = (write + 1)%bucket.size(); 
        }

        int front(){
            return bucket[read];
        }

        void pop(){
            if (empty()) return;
            read = (read + 1)%bucket.size();
        }
};

int main() {
    // Create a cyclic queue with capacity 5
    CyclicQueue queue(3);

    // Push some elements into the queue
    queue.push(1);
    queue.push(2);
    queue.push(3);

    assert(queue.full());
    assert(!queue.empty());
    assert(queue.front() == 1);

    queue.pop();assert(queue.front() == 2);
    queue.pop();assert(queue.front() == 3);
    queue.pop();assert(queue.empty());

    return 0;
}