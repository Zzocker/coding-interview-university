#include <bits/stdc++.h>
#include <cassert>

using namespace std;

// 1. https://www.codingninjas.com/studio/problems/frog-jump_3621012
class FrogJump{
    public:
        void solve(){
            vector<int> H{10,20,30,10};
            auto bottom_up_ans = bottom_up(H);
            auto top_down_ans = top_down(H);
            assert(bottom_up_ans == top_down_ans);
        }
    private:
        int dp[100001];
        int _bottom_up(const vector<int>& H, int i){
            if (i == H.size() - 1) return 0;
            if (dp[i] != -1) return dp[i];
            int jump_1 = abs(H[i+1] - H[i]) + _bottom_up(H, i+1);
            int jump_2 = INT_MAX;
            if (i + 2 < H.size())jump_2 = abs(H[i+2] - H[i]) + _bottom_up(H, i+2);
            dp[i] = min(jump_1, jump_2);
            return dp[i];
        }
        int bottom_up(vector<int>& H){
            memset(dp, -1, sizeof(dp));
            return _bottom_up(H,0);
        }

        int top_down(vector<int>& H){
            vector<int> dp(H.size());
            dp[H.size()-1] = 0;
            for (int i=H.size()-2;i>=0;i--){
                int jump_1 = abs(H[i+1] - H[i]) + dp[i+1];
                int jump_2 = INT_MAX;
                if (i + 2 < H.size()) jump_2 = abs(H[i+2] - H[i]) + dp[i+2];
                dp[i] = min(jump_1, jump_2);
            }
            return dp[0];
        }

};

// 2. https://www.codingninjas.com/studio/problems/minimal-cost_8180930
class MinimalCost{
    public:
        void solve(){
            vector<int> H{10,40,30,10};
            int k{2};
            auto bottom_up_ans = bottom_up(H, k);
            auto top_down_ans = top_down(H, k);
            assert(bottom_up_ans == top_down_ans);
        }
    private:
        int dp[10001];
        int _bottom_up(const vector<int>& H, int k, int i){
            if (i == H.size()-1) return 0;
            if (dp[i] != -1) return dp[i];
            int out{INT_MAX};
            for (int p=i+1;p<=i+k && p < H.size();p++){
                out = min(
                    out,
                    abs(H[p] - H[i]) + _bottom_up(H, k, p)
                );
            }
            dp[i] =  out;
            return dp[i];
        }
        int bottom_up(vector<int>& H, int k){
            memset(dp, -1, sizeof(dp));
            return _bottom_up(H, k, 0);
        }

        int top_down(const vector<int>& H, int k){
            vector<int> dp(H.size());
            dp[H.size() -1] = 0;
            for (int i=H.size()-2;i>=0;i--){
                int cost = INT_MAX;
                for (int p=i+1; p<= i+k && p < H.size();p++){
                    cost = min(
                        cost,
                        abs(H[p] - H[i]) + dp[p]
                    );
                }
                dp[i] = cost;
            }
            return dp[0];
        }
};

// https://www.codingninjas.com/studio/problems/maximum-sum-of-non-adjacent-elements_843261
class MaxSumOfNonAdjacentElements{
    public:
        void solve(){
            vector<int> nums{1,2,3,1,3,5,8,1,9};
            auto bottom_up_ans = bottom_up(nums);
            auto top_down_ans = bottom_up(nums);
            assert(bottom_up_ans == top_down_ans);
        }
    private:
        int _bottom_up(const vector<int>& nums, int i, vector<int>& dp){
            if (i >= nums.size()) return 0;
            if (dp[i] != -1) return dp[i];
            return dp[i] = max(
                nums[i] + _bottom_up(nums, i+2, dp), // include
                _bottom_up(nums, i+1, dp) // not-include
            );
        }

        int bottom_up(const vector<int>& nums){
            vector<int> dp(nums.size(), -1);
            return _bottom_up(nums, 0, dp);
        }

        int top_down(const vector<int>& nums){
            // vector<int> dp(nums.size());
            // dp[nums.size()-1] = nums.back();
            int next_next = 0;
            int next = nums.back();
            for (int i=nums.size()-2;i>=0;i--){
                // int option_1 = dp[i+1]; // not-include
                // int option_2 = nums[i] + (i+2 >= nums.size() ? 0 : dp[i+2]); // include
                // dp[i] = max(option_1, option_2);
                int option_1 = next; // not-include
                int option_2 = nums[i] + next_next;
                next_next = next;
                next = max(option_1, option_2);
            }
            // return dp[0];
            return next;
        }
};

// https://www.codingninjas.com/studio/problems/ninja-s-training_3621003
class NinjaTraining{
    public:
        void solve(){
            vector<vector<int>> points{
                    {1, 2, 5}, 
                    {3, 1, 1},
                    {3, 3, 3},
            };
            auto top_down_ans = top_down(points);
            assert(top_down_ans == 11);
            auto bottom_up_ans = bottom_up(points);
            assert(bottom_up_ans == top_down_ans);
        }

        int dp[100001][3];
        // i -> day
        // j -> don't perform jth task
        int _top_down(const vector<vector<int>>& points, int i, int j){
            if (i >= points.size()) return 0;
            if (dp[i][j] != -1) return dp[i][j];
            int out{INT_MIN};
            for (int k=0;k<3;k++){
                if (k != j)out = max(out, points[i][k] + _top_down(points, i+1, k));
            }
            return dp[i][j] = out;
        }

        int top_down(const vector<vector<int>>& points){
            memset(dp, -1, sizeof(dp));
            int option_1 = _top_down(points, 0, 0);
            int option_2 = _top_down(points, 0, 1);
            int option_3 = _top_down(points, 0, 2);
            return max(option_1, max(option_2, option_3));
        }

        int bottom_up(const vector<vector<int>>& points){
            int n = points.size();
            // vector<vector<int>> dp(n, vector<int> (3));
            // dp[n-1][0] = max(points[n-1][1], points[n-1][2]);
            // dp[n-1][1] = max(points[n-1][0], points[n-1][2]);
            // dp[n-1][2] = max(points[n-1][0], points[n-1][1]);
            vector<int> next(3);
            next[0] = max(points[n-1][1], points[n-1][2]);
            next[1] = max(points[n-1][0], points[n-1][2]);
            next[2] = max(points[n-1][0], points[n-1][1]);
            for (int i=n-2;i>=0;i--){
                vector<int> new_next(3);
                for (int j=0;j<3;j++){
                    int out{INT_MIN};
                    for (int k=0;k<3;k++){
                        // if (k != j)out = max(out, points[i][k] + dp[i+1][k]);
                        if (k != j)out = max(out, points[i][k] + next[k]);
                    }
                    // dp[i][j] = out;
                    new_next[j] = out;
                }
                next = new_next;
            }
            return max(next[0], max(next[1], next[2]));
        }
};

class UniquePath{
    public:
        void solve(){
            int m{3}, n{2};
            auto top_down_ans = top_down(m,n);
            auto bottom_up_ans = bottom_up(m,n);
            assert(top_down_ans == 3);
        }
    private:
        int dp[16][16];
        int _top_down(int m,int n, int i, int j){
            if (i == m -1 && j == n - 1) return 1;
            if (dp[i][j] != -1) return dp[i][j];
            int out{0};
            // move down
            if (i + 1 < m) out+=_top_down(m,n,i+1, j);
            // move right
            if (j + 1 < n) out+=_top_down(m,n, i, j+1);
            return dp[i][j] = out;
        }

        int top_down(int m, int n){
            memset(dp, -1, sizeof(dp));
            return _top_down(m,n, 0, 0);
        }

        int bottom_up(int m, int n){
            vector<int> next_row(n);
            for (int i=m-1;i>=0;i--){
                vector<int> new_next_row(n);
                for (int j=n-1;j>=0;j--){
                    if (i == m - 1 && j == n-1)new_next_row[j]=1;
                    else {
                        int out{0};
                        // move down
                        if (i + 1 < m) out+=next_row[j];
                        // move right
                        if (j + 1 < n) out+=new_next_row[j+1];
                        new_next_row[j] = out;
                    }
                }
                next_row = new_next_row;
            }
            return next_row[0];
        }
};

class MinPathSum{
    public:
        void solve(){
            vector<vector<int>> grid{
                    {5, 9, 6},
                    {11, 5, 2},
            };
            auto top_down_ans = top_down(grid);
            assert(top_down_ans == 21);
            int bottom_up_ans = bottom_down(grid);
        }
    
    private:

        int dp[101][101];
        int _top_down(const vector<vector<int>>& grid, int i, int j){
            if (i == grid.size() - 1 && j == grid[0].size() - 1) return grid[i][j];
            if (dp[i][j] != -1) return dp[i][j];
            int best_option{INT_MAX};
            if (i + 1 < grid.size()) best_option = min(best_option, _top_down(grid, i+1, j));
            if (j + 1 < grid[0].size()) best_option = min(best_option, _top_down(grid, i, j+1));
            return dp[i][j] = grid[i][j] + best_option;
        }

        int top_down(const vector<vector<int>>& grid){
            memset(dp, -1, sizeof(dp));
            return _top_down(grid, 0, 0);
        }

        int bottom_down(const vector<vector<int>>& grid){
            int n = grid.size();
            int m = grid[0].size();
            // vector<vector<int>> dp(n, vector<int> (m));
            vector<int> next_row(m);
            for (int i=n-1;i>=0;i--){
                vector<int> new_next_row(m);
                for (int j=m-1;j>=0;j--){
                    if (i == n - 1 && j == m - 1){
                        new_next_row[j] = grid[i][j];
                    }else {
                        int best_option{INT_MAX};
                        if (i + 1 < n) best_option = min(best_option, next_row[j]);
                        if (j + 1 < m) best_option = min(best_option, new_next_row[j+1]);
                        new_next_row[j] = grid[i][j] + best_option;
                    }
                }
                next_row = new_next_row;
            }
            // return dp[0][0];
            return next_row[0];
        }
};

class SubsetSumEqualToK{
    public:
        void solve(){
            vector<int> arr{4,3,2,1};
            int k{5};
            auto top_down_ans = top_down(arr, k);
            assert(top_down_ans == true);
            auto bottom_up_ans = bottom_up(arr, k);
            assert(bottom_up_ans == top_down_ans);
        }
    private:

        int dp[1001][1002];
        bool _top_down(const vector<int>& arr, int target, int i){
            if (target == 0) return true;
            else if (i >= arr.size()) return false;
            else if (arr[i] == target) return true;

            if (dp[i][target] != -1) return dp[i][target];
        
            bool not_take = _top_down(arr, target, i+1);
            bool take = false;
            if (arr[i] < target) take = _top_down(arr, target - arr[i], i+1);
            return dp[i][target] = not_take || take;
        }

        // top_down
        // i: 0 -> 1 -> 2 -> n-1
        // target: k -> k-1 -> ... 0

        bool top_down(const vector<int>& arr, int k){
            memset(dp, -1, sizeof(dp));
            return _top_down(arr, k, 0);
        }

        bool bottom_up(const vector<int>& arr, int k){
            int n = arr.size();
            // vector<vector<bool>> dp(n, vector<bool> (k+1));
            // for (int i=0;i<n;i++)dp[i][0] = true;
            vector<bool> next_row(k+1);

            for (int i=n-1;i>=0;i--){
                vector<bool> new_next_row(k+1);
                new_next_row[0] = true;
                for (int target=1;target<=k;target++){
                    if (arr[i] == target){
                        new_next_row[target] = true;
                    }else if (i + 1 < n) {
                        bool not_take = next_row[target];
                        bool take = false;
                        if (arr[i] < target) take = next_row[target - arr[i]];
                        new_next_row[target] = not_take || take;
                    }
                }
                next_row = new_next_row;
            }

            return next_row[k];
        }
};

class PrintLCS{
    public:
        void solve(){
            string s{"abc"};
            string t{"adbc"};
            auto top_down_ans = top_down(s,t);
            assert(top_down_ans == "abc");
            auto bottom_up_ans = bottom_up(s,t);
        }

    private:
        string _top_down(const string& s, const string& t, int i, int j){
            if (i >= s.size() || j >= t.size()) return "";

            if (s[i] == t[j]) return s[i] + _top_down(s,t,i+1,j+1);
            auto s_dec = _top_down(s,t,i+1,j);
            auto t_dec = _top_down(s,t,i,j+1);
            if (s_dec.size() > t_dec.size()) return s_dec;
            return t_dec; 
        }
        string top_down(const string& s, const string& t){
            return _top_down(s, t, 0,0);
        }

        string bottom_up(const string& s, const string& t){
            int n = s.size();
            int m = t.size();
            vector<vector<int>> dp(n+1, vector<int> (m+1));
            for (int i=0;i<=n;i++)dp[i][m] = 0;
            for (int j=0;j<=m;j++)dp[n][j] = 0;

            for (int i=n-1;i>=0;i--){
                for (int j=m-1;j>=0;j--){
                    if (s[i] == s[j]) dp[i][j] = 1 + dp[i+1][j+1];
                    else dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
                }
            }

            string ans{};
            int i{0},j{0};
            while (i < n && j < m){
                if (s[i] == t[j]) {
                    ans.push_back(s[i]);
                    i++;j++;
                }else {
                    if (dp[i+1][j] >= dp[i][j+1])i++;
                    else j++;
                }
            }
            return ans;
        }
};

template <typename T> void print(const vector<T>& A){
    for (auto a: A)cout << a << " ";
    cout << endl;
}

class PrintLIS{
    public:
        void solve(){
            vector<int> A{5,4,11,1,16,8};
            auto ans = top_down(A);
            vector<int> expect{5, 11, 16};
            assert(ans.size() == expect.size());
            for (int i=0;i<ans.size();i++)assert(ans[i] == expect[i]);
        }

    private:
        vector<int> top_down(const vector<int>& A){
            int n = A.size();
            // dp[i]: represents largest lis
            // ending at i
            // hash[i]: represents prev element in LIS
            vector<int> dp(n, 1);
            vector<int> hash(n);
            for (int i=0;i<n;i++)hash[i] = i;
            for (int i=1;i<n;i++){
                for (int j=0;j<i;j++){
                    if (A[i] > A[j] && dp[i] < 1 + dp[j]){
                        dp[i] = 1 + dp[j];
                        hash[i] = j;
                    }
                }
            }

            int maxi{0};
            for (int i=0;i<n;i++){
                if (dp[i] > dp[maxi]) maxi = i;
            }
            vector<int> ans;
            for (int i=maxi;;i = hash[i]){
                ans.push_back(A[i]);
                if (i == hash[i])break;
            }
            reverse(ans.begin(), ans.end());
            return ans;
        }
};

class GetLIS{
    public:
        void solve(){
            vector<int> A{1,4,5,4,2,8};
            auto ans = solution(A);
            assert(ans == 4);
        }
    private:
        int get_upper_bound(const vector<int>& A, int val){
            int lo = 0,hi = A.size()-1;
            int ans{0};
            while (hi >= lo){
                int mid = (hi - lo)/2 + lo;
                if (A[mid] == val) return mid;
                else if (val < A[mid]) {
                    ans = mid;
                    hi = mid - 1;
                }
                else {
                    lo = mid + 1;
                }
            }
            return ans;
        }
        int solution(const vector<int>& A){
            vector<int> b;
            b.push_back(A[0]);
            for (int i=1;i<A.size();i++){
                if (A[i] > b.back())b.push_back(A[i]);
                else {
                    int upper_bound = get_upper_bound(b, A[i]);
                    b[upper_bound] = A[i];
                }
            }
            return b.size();
        }
};