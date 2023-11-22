#include <vector>
#include <cassert>

using namespace std;

class MergeSort{
    public:
        void test(){
            const int test_size = 16;
            vector<int> A;
            for (int i=test_size;i>0;i--)A.push_back(i);
            solution(A);
            for (int i=1;i<=test_size;i++)assert(A[i-1]==i);
        }
    private:
        void merge_sort(vector<int>& A, int lo, int hi, vector<int>& aux){
            if (lo >= hi) return;
            int mid = (hi - lo)/2 + lo;
            merge_sort(A, lo, mid, aux);
            merge_sort(A, mid + 1, hi, aux);
            merge(A, lo, mid, hi, aux);
        }
        void merge(vector<int>& A, int lo, int mid, int hi, vector<int>& aux){
            for (int i=lo;i<=hi;i++)aux[i]=A[i];
            int i=lo,j=mid+1;
            int k=lo;
            while (i <= mid && j <= hi){
                if (aux[i]<= aux[j]){
                    A[k] = aux[i];
                    i++;
                }else {
                    A[k] = aux[j];
                    j++;
                }
                k++;
            }
            while (i <= mid){
                A[k] = aux[i];
                i++;k++;
            }
            while (j <= hi){
                A[k] = aux[j];
                j++;k++;
            }
        }
        void solution(vector<int>& A){
            vector<int> aux(A.size(), 0);
            merge_sort(A, 0 , A.size() - 1, aux);
        }


};

class QuickSort{
    public:
        void test(){
            const int test_size = 16;
            vector<int> A;
            for (int i=test_size;i>0;i--)A.push_back(i);
            solution(A);
            for (int i=1;i<=test_size;i++)assert(A[i-1]==i);
        }
    private:
        void solution(vector<int>& A){
            quick_sort(A, 0, A.size() -1);
        }
        void quick_sort(vector<int>& A, int lo, int hi){
            if (lo >= hi)return;
            int k = partition(A, lo, hi);
            quick_sort(A, lo, k-1);
            quick_sort(A, k+1, hi);
        }

        int partition(vector<int>& A, int lo, int hi) {
            int smaller = lo - 1;
            for (int i=lo;i<=hi-1;i++){
                if (A[i] <= A[hi]){
                    swap(A[i], A[smaller + 1]);
                    smaller++;
                }
            }
            swap(A[hi], A[smaller + 1]);
            return smaller+1;
        }
};

class BinarySearch{
    public:
        void test(){
            const int test_size = 16;
            vector<int> A;
            for (int i=0;i<test_size;i++)A.push_back(i);

            for (int i=0;i<test_size;i++){
                assert(solution(A, A[i]) == i);
            }

            assert(solution(A, test_size) == -1);
        }
    private:
        int solution(const vector<int>& A, int elem){
            int lo=0,hi=A.size() -1;
            while (hi >= lo){
                int mid = (hi - lo)/2 + lo;
                if (A[mid] == elem)return mid;
                else if (elem < A[mid]) hi = mid - 1;
                else lo = mid + 1;
            }
            return -1;
        }
};