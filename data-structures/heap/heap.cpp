#include <vector>
#include "heap.h"

using std::vector;

Heap::Heap(): size{0}, bucket{} {}

bool Heap::is_empty() const {return size == 0;}
int Heap::get_size() const {return size;}
int Heap::get_max() const {return bucket[0];}

void Heap::shift_up(int index){
    int value = bucket[index];
    int parent = (index-1)/2;
    while (parent < index && bucket[parent] < value){
        bucket[index] = bucket[parent];
        index = parent;
        parent = (index - 1)/2;
    }
    bucket[index] = value;
}

void Heap::insert(int elem){
    if (size == bucket.size()) bucket.push_back(0);
    bucket[size] = elem;
    size++;
    shift_up(size-1);
}

void Heap::shift_down(int index){
    int value = bucket[index];
    int left_child = 2*index + 1;
    int right_child = 2*index + 2;
    while (right_child < size || left_child < size){
        if (right_child < size){
            if (bucket[left_child] > value && bucket[right_child] > value){
                if (bucket[left_child] > bucket[right_child]){
                    bucket[index] = bucket[left_child];
                    index = left_child;
                }else {
                    bucket[index] = bucket[right_child];
                    index = right_child;
                }
            }else if (bucket[left_child] > value){
                bucket[index] = bucket[left_child];
                index = left_child;
            }else if (bucket[right_child] > value){
                bucket[index] = bucket[right_child];
                index = right_child;
            }else break;
        }else if (left_child < size){
            if (bucket[left_child] > value){
                bucket[index] = bucket[left_child];
                index = left_child;
            }else break;
        }else break;
        left_child = 2*index + 1;
        right_child = 2*index + 2;
    }
    bucket[index] = value;
}

int Heap::extract_max() {
    int value = bucket[0];
    bucket[0] = bucket[size-1];
    bucket[size-1] = value;
    size--;
    shift_down(0);
    return value;
}

void Heap::heapify(){
    for (int i=1;i<size;i++)shift_up(i);
}

Heap::Heap(vector<int>& b){
    bucket = b;
    size = bucket.size();
    heapify();
}

void Heap::heap_sort(vector<int>& A){
    Heap heap(A);
    while (!heap.is_empty()){
        heap.extract_max();
    }
    A = heap.bucket;
}