class Solution {
public:
    // DFS + memoization Time : O(m*n) Space : O(m*n)
    bool isInterleave_dfs(string s1, string s2, string s3) {
       if (s1.length() + s2.length() != s3.length()) return false;
        unordered_set<int> cache;
        return isInterleave0(s1, s2, s3, 0, 0, cache);
    }

    bool isInterleave0(string s1, string s2, string s3, int p1, int p2, unordered_set<int> &cache) {
        if (p1 + p2 == s3.length())
            return true;
        if (cache.count(p1 * s3.length() + p2))
            return false;
        // no need to store actual result.
        // if we found the path, we have already terminated.
        cache.insert(p1 * s3.length() + p2);
        bool match1 = p1 < s1.length() && s3[p1 + p2] == s1[p1];
        bool match2 = p2 < s2.length() && s3[p1 + p2] == s2[p2];
        if (match1 && match2)
            return isInterleave0(s1, s2, s3, p1 + 1, p2, cache) ||
                   isInterleave0(s1, s2, s3, p1, p2 + 1, cache);
        else if (match1)
            return isInterleave0(s1, s2, s3, p1 + 1, p2, cache);
        else if (match2)
            return isInterleave0(s1, s2, s3, p1, p2 + 1, cache);
        else
            return false; 
    }
    
    //bfs Time: O(m*n) Space: O(m*n)
    bool isInterleave_bfs(string s1, string s2, string s3) {
        int len1 = s1.length(),
            len2 = s2.length(),
            len3 = s3.length();
        if (len1 + len2 != len3) return false;
        queue<int> queue;
        int matched = 0;
        queue.push(0);
        unordered_set<int> set;
        while (queue.size() > 0 && matched < len3) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int p1 = queue.front() / len3,
                    p2 = queue.front() % len3;
                queue.pop();
                if (p1 < len1 && s1[p1] == s3[matched]) {
                    int key = (p1 + 1) * len3 + p2;
                    if (!set.count(key)) {
                        set.insert(key);
                        queue.push(key);
                    }
                }
                if (p2 < len2 && s2[p2] == s3[matched]) {
                    int key = p1 * len3 + (p2 + 1);
                    if (!set.count(key)) {
                        set.insert(key);
                        queue.push(key);
                    }
                }
            }
            matched++;
        }
        return queue.size() > 0 && matched == len3;
    }
    
    // DP Time: O(m*n) Space: O(m*n)
    bool isInterleave_2d(string s1, string s2, string s3) {
        int len1 = s1.length(),
            len2 = s2.length(),
            len3 = s3.length();
        if (len1 + len2 != len3)
            return false;
        // dp[i][j] == true means first i + j + 2 chars are matched by
        // first i+1 chars from s1 and first j+1 chars from s2
        vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
        for (int i = 0; i <= s1.length(); i++) {
            for (int j = 0; j <= s2.length(); j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = true;
                } else if (i == 0) {
                    // dp[i][j] = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
                    dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
                } else if (j == 0) {
                    // dp[i][j] = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
                    dp[i][0] = dp[i-1][0] && s1[i - 1] == s3[i - 1];
                } else {
                    dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }
        }
        return dp[s1.length()][s2.length()];
    }

    // DP Time: O(m*n) Space: O(n)
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length(), l = s3.length();
        if (m + n != l) 
            return false;
        
        if (m < n) 
            return isInterleave(s2, s1, s3);

        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] && s2[j - 1] == s3[j - 1];
        }

        for (int i = 1; i <= m; ++i) {
            dp[0] = dp[0] && s1[i - 1] == s3[i - 1];
            for (int j = 1; j <= n; ++j) {
                dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) || (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        
        return dp[n];
    }
};
