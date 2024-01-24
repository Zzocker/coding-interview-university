#include "algorithm.cpp"

int main(){
    {
        MergeSort algo;
        algo.test();
    }

    {
        QuickSort algo;
        algo.test();
    }

    {
        BinarySearch algo;
        algo.test();
    }

    {
        RadixSort algo;
        algo.test();
    }

    {
        CountingSort algo;
        algo.test();
    }
    {
        KMP kmp;
        kmp.test();
    }
}