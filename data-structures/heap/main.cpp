#include "heap.h"
#include <cassert>

using namespace std;

int main(){
    Heap heap;

    assert(heap.is_empty());
    assert(heap.get_size() == 0);

    heap.insert(4);
    heap.insert(3);
    heap.insert(7);
    heap.insert(9);
    heap.insert(8);
    heap.insert(4);

    assert(!heap.is_empty());
    assert(heap.get_size() == 6);
    assert(heap.get_max() == 9);
    
    assert(heap.extract_max() == 9);
    assert(heap.extract_max() == 8);
    assert(heap.extract_max() == 7);
    assert(heap.extract_max() == 4);
    assert(heap.extract_max() == 4);
    assert(heap.extract_max() == 3);


    vector<int> A;
    int N = 5;
    for (int i=N;i>=0;i--)A.push_back(i);
    Heap::heap_sort(A);
    for (int i=0;i<=N;i++)assert(A[i] == i);
}