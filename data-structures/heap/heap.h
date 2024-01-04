#ifndef HEAP_H
#define HEAP_H
#include <vector>

class Heap{
    private:
        std::vector<int> bucket;
        int size;

        void shift_up(int index);
        void shift_down(int index);
        void heapify();
    public:
        Heap();
        Heap(std::vector<int>& b);
        
        void insert(int elem);
        int get_max() const;
        int get_size() const;
        bool is_empty() const;
        int extract_max();
        static void heap_sort(std::vector<int>& A);
};

#endif