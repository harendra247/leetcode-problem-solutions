class Solution {
public:
    int minDistance_td(string word1, string word2) {
        return go(word1, word2, word1.size(), word2.size());
    }
    
    using VI = vector<int>;
    using VVI = vector<VI>;
    // Time: O(mn) Space: O(mn)
    int minDistance_1(string word1, string word2) {
        auto [M, N] = make_tuple(word1.size(), word2.size());
        VVI dp(M + 1, VI(N + 1)); //represents the min number of operations to transform string A[0...M] -> A[0...N].

        for (auto i = 0; i <= M; ++i) 
            dp[i][0] = i; // base case: we have exhausted B, return "leftover" distance
        for (auto j = 0; j <= N; ++j) 
            dp[0][j] = j; // base case: we have exhausted A, return "leftover" distance
        for (auto i = 1; i <= M; ++i)
            for (auto j = 1; j <= N; ++j)
                dp[i][j] = min({
                    dp[i - 1][j - 1] + int(word1[i - 1] != word2[j - 1]), // ✅ match xor ❌ mismath
                    dp[i - 1][j] + 1, // ❌ insertion 
                    dp[i][j - 1] + 1, // ❌ deletion
                });
        return dp[M][N];
    }
    
    int minDistance(string word1, string word2) {
        auto [M, N] = make_tuple(word1.size(), word2.size());
        VI pre(N + 1); // memo
        iota(pre.begin(), pre.end(), 0);

        for (auto i = 1; i <= M; ++i) {
            auto cur {pre};
            cur[0] = i;
            for (auto j = 1; j <= N; ++j)
                cur[j] = min({
                    pre[j - 1] + int(word1[i - 1] != word2[j - 1]), // ✅ match xor ❌ mismatch
                    pre[j] + 1, // ❌ insertion 
                    cur[j - 1] + 1, // ❌ deletion
                });
            swap(cur, pre);
        }
        return pre[N];
    }
    
private:
    using Map = unordered_map<string, int>;
    int go (string &word1, string &word2, int i, int j, Map && memo = {}) {
        stringstream ss;
        ss << i << "," << j;
        auto key = ss.str();
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        if (!i || !j)
            return memo[key] = i + j;
        
        memo[key] = min(
        go(word1, word2, i-1, j-1, move(memo)) + int(word1[i-1] != word2[j-1]),
          min (go(word1, word2, i-1, j, move(memo)) + 1,
              go(word1, word2, i, j-1, move(memo)) + 1  
        ));
        
        return memo[key];
    }
};
