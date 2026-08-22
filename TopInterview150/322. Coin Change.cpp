class Solution {
private:
    const int INF = 1e5;
    int go(vector<int>& coins, int amount, int i, vector<vector<int>> & dp) {
        if (!amount)
            return 0;
        if (i == coins.size())
            return INF;
        if (dp[i][amount] != -1) 
            return dp[i][amount];
        
        int ans = INF; 
        if (amount - coins[i] >= 0) {
            ans = min(ans, 1 + go(coins, amount - coins[i], i, dp)); // include current coin
        }
        
        dp[i][amount] = min(ans, go(coins, amount, i+1, dp)); //exclude curent coin
        return dp[i][amount];
    }

public:
    // Time: O(T*n) Space: O(T*n) where T is the amount, n is denomination count.
    int coinChange_TD(vector<int>& coins, int amount) {
        // Minimum number of coins needed to make amount using coin denominations from index i onward.
        vector<vector<int>> dp(coins.size()+1, vector<int>(amount+1, -1));
        auto ans = go(coins, amount, 0, dp);
        return ans < INF ? ans : -1;
    }
    
    using VI = vector<int>;
    using VVI = vector<VI>;
    
    // Unbounded Knapsack style DP
    //
    // dp[i][t] = minimum coins to make amount t
    //            using first i denominations
    //
    // include = 1 + dp[i][t - coin]   // same row: reuse allowed
    // exclude = dp[i - 1][t]
    //
    // Time:  O(N*T)
    // Space: O(N*T)
    int coinChange_BU1(vector<int>& coins, int T) {
        int N = coins.size();
        // Minimum number of coins required to make amount t using the first i coin denominations.
        VVI dp(N + 1, VI(T + 1, INF));
        for (auto i = 0; i <= N; ++i)
            dp[i][0] = 0;
        
        for (auto i = 1; i <= N; ++i)
            for (auto t = 1; t <= T; ++t) {
                auto ans = INF;
                if (t - coins[i - 1]>=0) {
                    ans = 1 + dp[i][t - coins[i - 1]]; //include
                }
                dp[i][t] = min(ans, dp[i - 1][t]); // exclude
            }
        return dp[N][T] < INF ? dp[N][T] : -1;
    }
    
    // Time: O(T*n) Space: O(T) // where T is the amount, n is denomination count. 
    int coinChange(vector<int>& coins, int T) {
        int N = coins.size();
        const int INF = T + 1;

        vector<int> previous(T + 1, INF);
        vector<int> current(T + 1, INF);

        previous[0] = 0;

        for (int i = 1; i <= N; ++i) {
            current[0] = 0;

            for (int amount = 1; amount <= T; ++amount) {
                int exclude = previous[amount];
                int include = INF;

                if (amount >= coins[i - 1] &&
                    current[amount - coins[i - 1]] != INF) {
                    include = 1 + current[amount - coins[i - 1]];
                }

                current[amount] = min(include, exclude);
            }

            swap(previous, current);
        }

        return previous[T] == INF ? -1 : previous[T];
    }
    
    // Time: O(T*n) Space: O(T) // where T is the amount, n is denomination count. 
    int coinChange_BU3(vector<int>& coins, int T) {
        const int INF = T + 1;

        vector<int> dp(T + 1, INF);
        dp[0] = 0;

        for (int coin : coins) {
            for (int amount = coin; amount <= T; ++amount) {
                dp[amount] = min(dp[amount], 1 + dp[amount - coin]);
            }
        }

        return dp[T] == INF ? -1 : dp[T];
    }
};
