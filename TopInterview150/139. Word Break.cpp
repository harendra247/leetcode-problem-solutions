class Solution {
public:
    // Related https://leetcode.com/problems/concatenated-words/
    
    //DP //explaination: https://www.youtube.com/watch?v=yr77dVf1RQA
    // n = s.length()
    //
    // Time: O(n^2) substring/prefix checks conceptually
    // Space: O(n + dictionary)
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dictionary(wordDict.begin(), wordDict.end());

        int n = s.size();

        /*
         * dp[i] = whether s[i ... n-1]
         * can be segmented into dictionary words.
         */
        vector<bool> dp(n + 1, false);

        // Empty suffix is valid.
        dp[n] = true;

        // Solve suffixes from right to left.
        for (int i = n - 1; i >= 0; --i) {

            string word;

            // Try every prefix of s[i ... n-1].
            for (int j = i; j < n; ++j) {
                word.push_back(s[j]);

                // Current prefix must be a dictionary word,
                // AND everything after it must also be valid.
                if (dictionary.count(word) && dp[j + 1]) {

                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[0];
    }
    
    bool dp(int i, string s, vector<string>& wordDict, vector<int> &memo) {
        if (i < 0) return true;
        
        if (memo[i] == -1) {
            for (string word: wordDict) {
                if (i >= word.length() - 1 && dp(i - word.length(), s, wordDict, memo)) {
                    if (s.substr(i - word.length() + 1, i + 1).compare(word)) {
                        memo[i] = 1;
                        break;
                    }
                }
            }
        }
        
        if (memo[i] == -1) {
            memo[i] = 0;
        }
        
        return memo[i] == 1;
    }
    
    //Top Down : Time: O(N^2) Space: O(N)
    bool wordBreak_td2(string s, vector<string>& wordDict) {
        if (wordDict.size() == 0 or s.size() == 0) return false;
        
        vector<int> memo(s.size(), -1);
    
        return dp(s.length() - 1, s, wordDict, memo);
    }
        
    //BFS Time: O(N^2) Space: O(N)
    bool wordBreak_bfs(string s, vector<string>& workdict) {
        queue<int> BFS;
        unordered_set<int> visited;
        unordered_set<string> dict(workdict.begin(), workdict.end());

        BFS.push(0);
        while (BFS.size() > 0) {
            int start = BFS.front();
            BFS.pop();
            if (visited.find(start) == visited.end()) {
                visited.insert(start);
                string word;
                for(int j=start; j<s.size(); j++) {
                    word.push_back(s[j]);
                    //string word(s, start, j-start+1); // becasue of this line complexity will be O(n^3) now it is O(n^2)
                    if (dict.find(word) != dict.end()) {
                        BFS.push(j+1);
                        if (j+1 == s.size())
                            return true;
                    }
                }
            }
        }

        return false;
    }
    
    //Topdown + memoization DP: DFS Time: O(N^2) Space: O(N) // becasue of substr() api complexity will be O(n^3) in 1st version of DFS
    bool wordBreak_td(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        
        //unordered_map<string, bool> smap;
        //return dfs(s, dict, smap);
        
        unordered_map<int, bool> map;
        return dfs(s, 0, dict, map);
    }
    
    bool dfs(string s, int start, unordered_set<string> &dict, unordered_map<int, bool> &map) {
        if (start == s.size())
            return true;
        
        if (map.count(start) > 0) return map[start];
        
        string left = "";
        for (int i = start; i < s.length(); i++) {
            left.push_back(s[i]);
            if (dict.count(left) > 0 && dfs(s, i+1, dict, map)) {
                map[start] = true;
                return true;
            }
        }
                
        map[start] = false;
        return false;
    }
    
    bool dfs(string s, unordered_set<string> &dict, unordered_map<string, bool> &map) {
        if (dict.count(s) > 0)
            return true;
        
        if (map.count(s) > 0) return map[s];
        
        string left = "";
        for (int i = 0; i < s.length(); i++) {
            left.push_back(s[i]);
            if (dict.count(left) > 0 && dfs(s.substr(i+1), dict, map)) {
                map[left] = true;
                return true;
            }
        }
                
        map[s] = false;
        return false;   
    }
};
