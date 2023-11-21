#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class StackException{
    public:
        StackException(const string& msg) : message {msg} {}
        const string get_message() const {return message;}
    private:
        string message;

};

class Stack{
    private:
        vector<int> bucket;
    public:
        Stack();
        void push(int elem);
        int top() const;
        void pop();
        bool is_empty() const;
        int size() const;
};

#endif