class Solution {
public:
    // Time: O(n) Space: O(1)
    string removeOuterParentheses(string S) {
        string result;
        int depth = 0;

        for (char c : S) {
            if (c == '(' && depth++ > 0) {
                result += c;
            }

            if (c == ')' && depth-- > 1) {
                result += c;
            }
        }

        return result;
    }
};
