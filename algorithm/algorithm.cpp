#include <vector>
#include <cassert>
#include <limits.h>
#include <string>

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

// Non-comparing sorting
class RadixSort{
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
            int biggest = INT_MIN;
            for (int i=0;i<A.size();i++)biggest = max(biggest, A[i]);
            int digits = to_string(biggest).size();
            vector<string> aux;
            for (int i=0;i<A.size();i++){
                string num = to_string(A[i]);
                while (num.size() < digits)num = '0' + num;
                aux.push_back(num);
            }
            for (int i=digits-1;i>=0;i--){
                vector<vector<string>> bucket(10, vector<string> ());
                for (int j=0;j<aux.size();j++){
                    bucket[aux[j][i] - '0'].push_back(aux[j]);
                }
                int k=0;
                for (int a=0;a<10;a++){
                    for (int b=0;b<bucket[a].size();b++){
                        aux[k] = bucket[a][b];
                        k++;
                    }
                }
            }
            for (int i=0;i<aux.size();i++){
                A[i] = stoi(aux[i]);
            }
        }
};


// Non-comparing sorting
class CountingSort{
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
            int smallest = INT_MAX;
            int largest = INT_MIN;
            for (int i=0;i<A.size();i++){
                smallest = min(smallest, A[i]);
                largest = max(largest, A[i]);
            }
            vector<int> bucket(largest-smallest+1, 0);
            for (int i=0;i<A.size();i++){
                bucket[A[i]-smallest]++;
            }
            A.clear();
            for (int i=0;i<bucket.size();i++){
                int count = bucket[i];
                while (count > 0){
                    A.push_back(i+smallest);
                    count--;
                }
            }
        }
};

class KMP{
    public:
        void test(){
            string str{"mississippi"};
            {
                string pattern{"issip"};
                auto ans = solution(str, pattern);
                assert(ans==4);
            }
            {
                string pattern{"sab"};
                auto ans = solution(str, pattern);
                assert(ans==-1);
            }
        }
    private:
        // lps: longest proper prefix suffix
        vector<int> get_lps(const string& pattern){
            int n = pattern.size();
            vector<int> lps(n);
            int len = 0;
            lps[0] = 0;
            int i = 1;
            while (i < n){
                if (pattern[i] == pattern[len]){
                    len++;
                    lps[i] = len;
                    i++;
                }else if (len == 0){
                    lps[i] = 0;
                    i++;
                }else len = lps[len-1];
            }
            return lps;
        }

        int solution(string str, string pattern){
            int n = str.size();
            auto lps = get_lps(pattern);
            int i = 0;
            int j = 0;
            while (i < n){
                if (str[i] == pattern[j]){
                    i++;j++;
                    if (j >= pattern.size()) return i - pattern.size();
                }else if (j == 0)i++;
                else j = lps[j-1];
            }
            return -1;
        }
};