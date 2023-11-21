#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class QueueException{
    public:
        QueueException(const string& msg): message {msg} {}
        const string get_message() const {return message;}
    private:
        string message;
};

class Queue{
    public:
        Queue(int s);
        void enqueue(int elem);
        int dequeue();
        int front() const;
        bool is_empty() const;
        bool is_full() const;
    private:
        vector<int> bucket;
        int r_index;
        int w_index;
};

#endif