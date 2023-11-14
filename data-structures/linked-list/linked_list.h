#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include "node.h"

using std::string;

class LinkedListException{
    public:
        LinkedListException(const string& msg): message{msg} {}
        string get_message() const {return message;}
    private:
        string message;
};

class LinkedList{
    public:
        LinkedList();
        ~LinkedList();

        int get_size() const;
        bool is_empty() const;
        int value_at(int index) const;
        void push_front(int item);
        int pop_front();
        void push_back(int item);
        int pop_back();
        int front() const;
        int back() const;
        void insert(int index, int elem);
        void erase(int index);
        int value_n_from_end(int n) const;
        void reverse();
        void remove_value(int value);
    private:
        int size;
        Node* head;
};

#endif