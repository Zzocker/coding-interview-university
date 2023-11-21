#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <list>

using std::string;
using std::list;

class QueueException{
    public:
        QueueException(const string& msg): message {msg} {}
        const string get_message() const {return message;}
    private:
        string message;
};

class Queue{
    public:
        Queue();
        void enqueue(int elem);
        int dequeue();
        int front() const;
        bool is_empty() const;
    private:
        list<int> bucket;
};

#endif