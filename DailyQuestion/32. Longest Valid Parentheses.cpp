class Solution {
public:
    
    // Time: O(n) Space: O(n)
    int longestValidParentheses_(string s) {
        stack<int> stk;
        stk.push(-1);
        int maxL = 0;
        for (int i = 0;i < s.size(); i++) {
            int t = stk.top();
            if (t != -1 && s[i] == ')' && s[t] == '(') {
                stk.pop();
                maxL = max(maxL, i - stk.top());
            } else {
                stk.push(i);
            }
        }
        return maxL;
    }
    
    // Time: O(n) Space: O(1)
    int longestValidParentheses(string s) {
        int left = 0, right = 0, maxlength = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxlength = max(maxlength, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        
        left = right = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxlength = max(maxlength, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        return maxlength;
    }
    
    
    // Dynamic programming  Time: O(n) Space: O(n)
    int longestValidParentheses_8(string s) {
        int maxans = 0;
        vector<int> dp(s.length(), 0); // dp[i] represents the length of the longest valid substring ending at ith index.
        for (int i = 1; i < s.length(); i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    // s[i]=‘)’ and s[i−1]=‘(’, i.e. string looks like ‘.......()" 
                    // ⇒ dp[i]=dp[i−2]+2
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    // s[i]=‘)’ and s[i−1]=‘)’, i.e. string looks like ‘.......))"⇒
                    // if s[i−dp[i−1]−1]=‘(’ then dp[i]=dp[i−1]+dp[i−dp[i−1]−2]+2
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                maxans = max(maxans, dp[i]);
            }
        }
        return maxans;
    }
};
