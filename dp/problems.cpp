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