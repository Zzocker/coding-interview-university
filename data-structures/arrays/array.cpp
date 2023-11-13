#include <cstddef>
#include "array.h"

const int MIN_CAPACITY = 16;
const int GROWTH_FACTOR = 2;

Array::Array(): size {0}, capacity {MIN_CAPACITY}, bucket {NULL} {
    bucket = new int[capacity];
}

Array::~Array() {
    delete[] bucket;
}

Array::Array(const Array& a): size{0}, capacity{MIN_CAPACITY}, bucket{NULL} {
    bucket = new int[capacity];
    for (int i=0;i<a.size;i++){
        push(*(a.bucket + i));
    }
}

Array& Array::operator= (const Array& a){
    size = 0;
    capacity = MIN_CAPACITY;
    bucket = new int[capacity];
    for (int i=0;i<a.size;i++){
        push(*(a.bucket + i));
    }
    return *this;
}

int Array::get_size() const {return size;}
int Array::get_capacity() const {return capacity;}
bool Array::is_empty() const {return size == 0;}

int Array::at(int index) const {
    if (index < 0 || index >= size) throw(ArrayException("index out of bound"));
    return *(bucket + index);
}

void Array::push(int item){
    if (size == capacity) resize(GROWTH_FACTOR * capacity);
    *(bucket + size) = item;
    size++;
}

void Array::insert(int index, int item){
    if (index < 0 || index >= size) throw(ArrayException("index out of bound"));
    if (size == capacity) resize(GROWTH_FACTOR * capacity);
    for (int i=size;i > index;i--){
        *(bucket + i) = *(bucket + i -1);
    }
    *(bucket + index) = item;
    size++;
}

void Array::prepend(int item){
    insert(0, item);
}

int Array::pop() {
    if (is_empty()) throw(ArrayException("empty array"));
    int item = *(bucket + size - 1);
    size--;
    return item;
}

void Array::delete_item(int index){
    if (index < 0 || index >= size) throw(ArrayException("index out of bound"));
    for (int i=index;i < size - 1;i++){
        *(bucket + i) = *(bucket + i + 1);
    }
    size--;
}

void Array::remove(int item){
    int index = find(item);
    if (index != -1) delete_item(index);
}

int Array::find(int item){
    for (int i=0;i < size;i++){
        if (*(bucket + i) == item)return i;
    }
    return -1;
}

void Array::resize(int new_capacity){
    int* new_bucket = new int[new_capacity];
    for (int i=0;i<size;i++){
        *(new_bucket + i) = *(bucket + i);
    }
    capacity = new_capacity;
    delete[] bucket;
    bucket = new_bucket;
}