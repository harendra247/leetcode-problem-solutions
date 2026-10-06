class Solution {
public:
    // Time: O(n) Space: O(n)
    bool checkValidString_(string s) {
        stack<char> st;
        stack<char> asterisk;
        
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == '*') {
                asterisk.push(i);
            } else {
                if (!st.empty()) {
                    st.pop();
                } else if (!asterisk.empty()) {
                    asterisk.pop();
                } else {
                    return false;
                }
            }
        }
        
        while (!st.empty()) {
            if (!asterisk.empty() && st.top() < asterisk.top()) {
                st.pop();
                asterisk.pop();
            } else {
                return false;
            }
        }
        return true;
    }

    // Time: O(n) Space: O(1)
    bool checkValidString(string s) {
        int openCount = 0;
        int closeCount = 0;
        int length = s.length() - 1;
        
        // Traverse the string from both ends simultaneously
        for (int i = 0; i <= length; i++) {
            // Count open parentheses or asterisks
            if (s[i] == '(' || s[i] == '*') {
                openCount++;
            } else {
                openCount--;
            }
            
            // Count close parentheses or asterisks
            if (s[length - i] == ')' || s[length - i] == '*') {
                closeCount++;
            } else {
                closeCount--;
            }
            
            // If at any point open count or close count goes negative, the string is invalid
            if (openCount < 0 || closeCount < 0) {
                return false;
            }
        }
        
        // If open count and close count are both non-negative, the string is valid
        return true;
    }
};
