#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>
using namespace std;

class DynamicArray{
    private:
        const int MIN_SIZE = 4;
        int* bucket;
        int len;
        int cap;
        void resize(int new_cap){
            new_cap = max(new_cap, DynamicArray::MIN_SIZE);
            int* new_bucket = new int[new_cap];
            for (int i=0;i<len;i++)new_bucket[i] = bucket[i];
            bucket = new_bucket;
            cap = new_cap;
        }
    public:
        DynamicArray(): len(0), cap(DynamicArray::MIN_SIZE){
            bucket = new int[cap];
        }

        void debug() const {
            printf("len = %d, cap = %d, bucket: ", len, cap);
            for (int i=0;i<cap;i++){
                cout << bucket[i];
                if (i != cap - 1) cout << ',';
            }
            cout << endl;
        }

        void push(int value){
            if (len == cap) resize(2*cap);
            bucket[len] = value;
            len++;
        }

        int pop() {
            int value = bucket[len-1];
            len--;
            if (4*len <= cap)resize(cap/2);
            return value;
        }

        int at(int index) const {
            return bucket[index];
        }

        int size() const {
            return len;
        }

        int capacity() const {
            return cap;
        }

        bool empty() {
            return len == 0;
        }
};

int main(){
    DynamicArray arr{};
    assert(arr.empty());

    arr.push(1);
    assert(!arr.empty());
    assert(arr.size() == 1);
    assert(arr.pop() == 1);
    assert(arr.empty());

    const int N = 10;

    for (int i=0;i<N;i++){
        arr.push(i);
        assert(arr.size() == i+1);
        assert(arr.at(i) == i);
    }
    arr.debug();

    
    for (int i=N-1;i>=0;i--){
        assert(arr.pop() == i);
        assert(arr.size() == i);
    }
}