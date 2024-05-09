#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename T> void print(const vector<T>& A){
    for (auto a: A)cout << a << ' ';
    cout << endl;
}

class Algorithm{
    public:
        // returns prime number <= n
        static vector<int> get_prime(int n){
            vector<bool> is_prime(n+1, true);
            for (int i=2;i<=n;i++){
                if (!is_prime[i])continue;
                for (int j=i*i;j<=n;j+=i)is_prime[j] = false;
            }
            vector<int> list;
            for (int i=2;i<=n;i++){
                if (is_prime[i])list.push_back(i);
            }
            return list;
        }

        static int max_sub_array_sum(const vector<int>& nums){
            int max_so_far{0}; // empty sub_array
            int sum{0};
            for (int i=0;i<nums.size();i++){
                sum+=nums[i];
                if (sum > max_so_far)max_so_far = sum;
                if (sum < 0)sum=0;
            }
            return max_so_far;
        }

        static vector<int> get_lps(const string& pattern){
            int n = pattern.size();
            vector<int> lps(n, 0);
            lps[0] = 0;
            int len = 0;
            for (int i=1;i<n;){
                if (pattern[i] == pattern[len]) {
                    lps[i] = len + 1;
                    len++;
                    i++;
                }else if (len == 0){
                    lps[i] = len;
                    i++;
                }else len = lps[len-1];
            }
            return lps;
        }

        static int search_str(const string& str, const string& pattern){
            auto lps = get_lps(pattern);
            int j{0};
            for (int i=0;i<str.size();){
                if (str[i] == pattern[j]){
                    i++;j++;
                    if (j == pattern.size()) return i - pattern.size();
                }else if (j == 0)i++;
                else j = lps[j-1];
            }
            return -1;
        }
};


int main(){
    {
        int n = 20;
        auto prime_list = Algorithm::get_prime(n);
        print(prime_list);
    }
    {
        vector<int> nums{-2,-3,4,-1,-2,1,5,-3};
        assert(Algorithm::max_sub_array_sum(nums) == 7);
    }
    {
        string str{"this is a string, my name is pritam"};
        string pattern{"name"};
        assert(Algorithm::search_str(str, pattern) == 21);
    }
}