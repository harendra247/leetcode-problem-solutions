class Solution {
public:
    
    // Backtracking TLE
    int distinctSubseqII_TLE(string s) {
        unordered_set<string> set;
        string tmp;
        backtracking(s, 0, tmp, set);
        return set.size()-1;
    }
    
    void backtracking(string &s, int index, string tmp, unordered_set<string> &set) {
        set.insert(tmp);    
        
        for (int i = index; i < s.size(); i++) {
            tmp.push_back(s[i]);
            backtracking(s, i+1, tmp, set);
            tmp.pop_back();
        }
    }
    
    // https://www.youtube.com/watch?v=AM4iXc0KPVg
    // dp[i] = number of distinct subsequences that can be formed
    //         using the first i characters of s.
    //
    // The empty subsequence "" is included in dp.
    //
    // Time:  O(n)
    // Space: O(n)
    int distinctSubseqII(string s) {
        const int MOD = 1'000'000'007;
        int n = s.size();

        vector<int> dp(n + 1, 0);

        // There is exactly one subsequence of an empty string:
        // the empty subsequence "".
        dp[0] = 1;

        // last[c] = index of the previous occurrence of character c.
        vector<int> last(26, -1);

        for (int i = 0; i < n; ++i) {
            int x = s[i] - 'a';

            // Every existing subsequence has two choices:
            //
            // 1. Don't use s[i]
            // 2. Append s[i]
            //
            // Therefore, initially we have twice as many subsequences.
            dp[i + 1] = (2LL * dp[i]) % MOD;

            // If this character appeared before, some of the
            // newly created subsequences are duplicates.
            //
            // dp[last[x]] represents the subsequences that existed
            // before the previous occurrence of this character.
            if (last[x] != -1) {
                dp[i + 1] -= dp[last[x]];

                if (dp[i + 1] < 0) {
                    dp[i + 1] += MOD;
                }
            }

            // Current occurrence becomes the latest occurrence.
            last[x] = i;
        }

        // Remove the empty subsequence.
        dp[n]--;

        if (dp[n] < 0) {
            dp[n] += MOD;
        }

        return dp[n];
    }
};
