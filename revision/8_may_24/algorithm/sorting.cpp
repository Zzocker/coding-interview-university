#include <any>
#include <bits/stdc++.h>
#include <optional>
#include <stack>
#include <vector>
#include <cassert>
using namespace std;

class Sorting{
    private:
        static void merge(vector<int>& arr, vector<int>& aux, int left, int mid, int right){
            for (int i=0;i<=right;i++)aux[i] = arr[i];
            int i=left,j=mid+1;
            int k = left;
            while (i <= mid && j <= right){
                if (aux[i] < aux[j]){
                    arr[k] = aux[i];
                    i++;
                }else {
                    arr[k] = aux[j];
                    j++;
                }
                k++;
            }
            while (i <= mid){
                arr[k] = aux[i];
                i++;k++;
            }
            while (j <= right){
                arr[k] = aux[j];
                j++;k++;
            }
        }
        static void __merge_sort(vector<int>& arr, vector<int>& aux, int left, int right){
            if (left >= right){
                return;
            }
            int mid = (right - left)/2 + left;
            __merge_sort(arr, aux, left, mid);
            __merge_sort(arr, aux, mid + 1, right);
            merge(arr, aux, left, mid, right);
        }

        static int quick_sort_partition(vector<int>& arr, int left, int right){
            int value = arr[right];
            int smaller{left - 1};
            for (int i=left;i<right;i++){
                if (arr[i] <= value){
                    swap(arr[smaller + 1], arr[i]);
                    smaller++;
                }
            }
            swap(arr[smaller+1], arr[right]);
            return smaller+1;
        }

        static void __quick_sort(vector<int>& arr, int left, int right){
            if (left >= right) return;
            int k = quick_sort_partition(arr, left, right);
            __quick_sort(arr, left, k-1);
            __quick_sort(arr, k+1, right);
        }

        static void heap_sort_move_up(vector<int>& arr, int i){
            int value = arr[i];
            int child = i;
            int parent = (child - 1)/2;
            while (child > 0 && value > arr[parent]){
                arr[child] = arr[parent];
                child = parent;
                parent = (child - 1)/2;
            }
            arr[child] = value;
        }

        static void heap_sort_move_down(vector<int>& arr, int n){
            int value = arr[0];
            int parent = 0;
            int left_child = 2*parent + 1;
            int right_child = 2*parent + 2;
            while (left_child < n){
                if (right_child < n){
                    if (arr[left_child] > value && arr[right_child] > value){
                        if (arr[left_child] > arr[right_child]){
                            arr[parent] = arr[left_child];
                            parent = left_child;
                        }else {
                            arr[parent] = arr[right_child];
                            parent = right_child;
                        }
                    }else if (arr[left_child] > value){
                        arr[parent] = arr[left_child];
                        parent = left_child;
                    }else if (arr[right_child] > value){
                        arr[parent] = arr[right_child];
                        parent = right_child;
                    }else break;
                }else if (arr[left_child] > value){
                    arr[parent] = arr[left_child];
                    parent = left_child;
                }else break;
                left_child = 2*parent + 1;
                right_child = 2*parent + 2;
            }
            arr[parent] = value;
        }
    public:
        static void merge_sort(vector<int>& arr){
            vector<int> aux(arr.size());
            __merge_sort(arr, aux, 0, arr.size()-1);
        };

        static void quick_sort(vector<int>& arr){
            __quick_sort(arr, 0, arr.size()-1);
        }

        static void heap_sort(vector<int>& arr){
            for (int i=1;i<arr.size();i++)heap_sort_move_up(arr, i);
            for (int i=0;i<arr.size();i++){
                swap(arr[0], arr[arr.size() - 1 - i]);
                heap_sort_move_down(arr, arr.size()-i-1); // 1 element removed
            }
        }

        static int search(const vector<int>& arr, int value){
            int lo = 0,hi = arr.size();
            while (hi >= lo){
                int mid = (hi - lo)/2 + lo;
                if (arr[mid] == value) return mid;
                else if (value < arr[mid]) hi = mid -1;
                else lo = mid + 1;
            }
            return -1;
        }
};

int main(){
    {
        int N = 20;
        vector<int> arr;
        for (int i=N-1;i>=0;i--)arr.push_back(i);
        Sorting::merge_sort(arr);
        for (int i=0;i<N;i++)assert(arr[i] == i);
    }

    {
        int N = 20;
        vector<int> arr;
        for (int i=N-1;i>=0;i--)arr.push_back(i);
        Sorting::quick_sort(arr);
        for (int i=0;i<N;i++)assert(arr[i] == i);
    }

    {
        int N = 20;
        vector<int> arr;
        for (int i=N-1;i>=0;i--)arr.push_back(i);
        Sorting::heap_sort(arr);
        for (int i=0;i<N;i++){
            assert(arr[i] == i);
            assert(Sorting::search(arr, i) == i);
        }
        assert(Sorting::search(arr, N+1) == -1);
    }
}