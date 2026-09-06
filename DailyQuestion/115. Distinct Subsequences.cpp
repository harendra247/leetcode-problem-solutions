class Solution {
public:
    
    // Time: O(S*T) Space: O(S*T)
    int numDistinct(string s, string t) {
        int S = s.size();
        int T = t.size();
        // dp[i][j]: number of ways to form t(0..i-1) from s(0..j-1)
        vector<vector<unsigned int>> dp(T+1, vector<unsigned int>(S+1, 0));
        
        // Number of ways to form an empty string "" using the first i characters of s.
        // There is exactly one way: choose nothing.
        for (int i = 0; i <= S; ++i) {
            dp[0][i] = 1;
        }
        
        for (int i = 1; i <= T; ++i) {
            for (int j = 1; j <= S; ++j) {
                if (s[j - 1] == t[i - 1]) {
                    // Two choices: 
                    // 1. Skip s[j - 1] 
                    // -> dp[i][j - 1] 
                    //
                    // 2. Use s[j - 1] to match t[i - 1] 
                    // -> dp[i - 1][j - 1]
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[T][S];
    }


    // Time: O(S*T) Space: O(S)
    int numDistinct_(string s, string t) {
        int S = s.size();
        int T = t.size();

        vector<unsigned long long> previous(S + 1, 1);
        vector<unsigned long long> current(S + 1, 0);

        for (int i = 1; i <= T; ++i) {
            current[0] = 0;

            for (int j = 1; j <= S; ++j) {
                current[j] = current[j - 1];

                if (t[i - 1] == s[j - 1]) {
                    current[j] += previous[j - 1];
                }
            }

            previous.swap(current);
        }

        return static_cast<int>(previous[S]);
    }
};
