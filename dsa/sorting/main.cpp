#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(int* A, int n){
    for (int i=1;i<n;i++){
        int cur = A[i];
        int j = i-1;
        while (j >= 0 && cur < A[j]){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = cur;
    }
}

int main(){
    int A[] = {5,4,3,2,1};
    int n = 5;
    insertion_sort(A, n);
    for (int i=0;i<n;i++){
        cout << A[i] << ' ';
    }
}