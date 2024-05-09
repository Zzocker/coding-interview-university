#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

class MaxHeap{
    private:
        vector<int> bucket;
        void move_up(int i){
            int value = bucket[i];
            int child = i;
            int parent = (child-1)/2;
            while (child > 0 && value > bucket[parent]){
                bucket[child] = bucket[parent];
                child = parent;
                parent = (child-1)/2;
            }
            bucket[child] = value;
        }

        void move_down(int i){
            int n = bucket.size();
            int value = bucket[i];
            int parent = i;
            int left_child = 2*parent + 1;
            int right_child = 2*parent + 2;
            while (left_child < n){
                if (right_child < n){
                    if (value < bucket[left_child] && value < bucket[right_child]){
                        if (bucket[left_child] > bucket[right_child]){
                            bucket[parent] = bucket[left_child];
                            parent = left_child;
                        }else {
                            bucket[parent] = bucket[right_child];
                            parent = right_child; 
                        }
                    }else if (value < bucket[left_child]) {
                        bucket[parent] = bucket[left_child];
                        parent = left_child;
                    }else if (value < bucket[right_child]) {
                        bucket[parent] = bucket[right_child];
                        parent = right_child;
                    }break;
                }else if (bucket[left_child] > value) {
                    bucket[parent] = bucket[left_child];
                    parent = left_child;
                }else break;
                left_child = 2*parent + 1;
                right_child = 2*parent + 2;
            }
            bucket[parent] = value;
        }

    public:
        MaxHeap(): bucket() {}
        MaxHeap(const vector<int>& vec){
            for (const int& v: vec)bucket.push_back(v);
            for (int i=1;i<bucket.size();i++)move_up(i);
        }

        void push(int value){            
            bucket.push_back(value);
            move_up(bucket.size()-1);
        }

        void pop(){
            int value = bucket.back();
            bucket.pop_back();
            bucket[0] = value;
            move_down(0);
        }

        int top() const {
            return bucket[0];
        }

        bool empty() const {
            return bucket.empty();
        }
};

int main(){
    MaxHeap heap{};
    assert(heap.empty());
    heap.push(1);
    assert(!heap.empty());
    assert(heap.top() == 1);

    heap.push(5);assert(heap.top() == 5);
    heap.push(2);assert(heap.top() == 5);
    heap.push(9);assert(heap.top() == 9);
    heap.push(12);assert(heap.top() == 12);
    heap.push(7);assert(heap.top() == 12);

    heap.pop();assert(heap.top() == 9);
    heap.pop();assert(heap.top() == 7);
    heap.pop();assert(heap.top() == 5);
    heap.pop();assert(heap.top() == 2);
    heap.pop();assert(heap.top() == 1);

    MaxHeap heap2{vector<int> {1,5,2,9,12,7}};
    assert(heap2.top() == 12);
    heap2.pop();assert(heap2.top() == 9);
    heap2.pop();assert(heap2.top() == 7);
    heap2.pop();assert(heap2.top() == 5);
    heap2.pop();assert(heap2.top() == 2);
    heap2.pop();assert(heap2.top() == 1);

}