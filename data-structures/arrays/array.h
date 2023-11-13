#ifndef ARRAY_H
#define ARRAY_H

#include <string>
using std::string;

class ArrayException{
    public:
        ArrayException(const string& msg): message{msg} {}
        const string& get_message() {return message;}
    private:
        string message;
};


class Array{
    private:
        int size;
        int capacity;
        int* bucket;
        void resize(int new_capacity);
    public:
        Array();
        ~Array();
        Array(const Array& a);
        Array& operator = (const Array& a);
        int get_size() const;
        int get_capacity() const;
        bool is_empty() const;
        int at(int index) const;
        void push(int item);
        void insert(int index, int item);
        void prepend(int item);
        int pop();
        void delete_item(int index);
        void remove(int item);
        int find(int item);
};

#endif