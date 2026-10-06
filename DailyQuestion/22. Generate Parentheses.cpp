class Solution {
public:
    // Backtracking
    //
    // open  = number of '(' still available
    // close = number of currently unmatched '(',
    //         therefore how many ')' we are allowed to place
    //
    // Time:  O(Cn * n), where Cn is the nth Catalan number
    // Space: O(n) recursion depth, excluding output
    vector<string> generateParenthesis_(int n) {
        vector<string> res;
        backtrack(res, "", n, 0);
        return res;
    }
    
    void backtrack(vector<string> &result, string current, int open, int close){
        /*
         * No '(' left to place
         * and no unmatched '(' left to close.
         *
         * Therefore current is a complete
         * valid parentheses string.
         */
        if (open == 0 && close == 0) {
            result.push_back(current);
            return;
        }
        /*
         * OPTION 1: Add ')'
         *
         * We can add ')' only if there is
         * an unmatched '(' available.
         *
         * close > 0 means:
         *
         * there is at least one '(' waiting
         * to be matched.
         */
        if (close > 0) { 
            backtrack(result, current + ")", open, close - 1); 
        }

        /*
         * OPTION 2: Add '('
         *
         * If we still have an opening parenthesis
         * available, use it.
         *
         * Using '(':
         *
         * open  decreases by 1
         * close increases by 1
         *
         * because we now have one more unmatched '('.
         */
        if (open > 0) { 
            backtrack(result, current + "(", open - 1, close + 1);
        }
    }
    
    // DP: f[i] = (f[0])f[i-1], ...., (f[j])f[i-j-1]. ....., (f[i-1])f[0]
    vector<string> generateParenthesis_f(int n) {
        if (n < 0) return vector<string>();
        vector<vector<string>> f(n + 1);
        f[0] = {""};
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                for (string &s1 : f[j])
                    for (string &s2 : f[i - 1 - j])
                        f[i].push_back('(' + s1 + ')' + s2);
        return f[n];
    }
    
    //Closure Number Time: (4^n/sqrtn) Space: O(4^n/sqrtn)
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        if (n == 0) {
            ans.push_back("");
        } else {
            for (int c = 0; c < n; ++c)
                for (string left: generateParenthesis(c))
                    for (string right: generateParenthesis(n-1-c))
                        ans.push_back("(" + left + ")" + right);
        }
        return ans; 
    }
};
