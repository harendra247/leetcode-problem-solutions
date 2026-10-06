class Solution {
public:
    /*
    //Stack problems
    1130. Minimum Cost Tree From Leaf Values
    907. Sum of Subarray Minimums
    901. Online Stock Span
    856. Score of Parentheses
    503. Next Greater Element II
    496. Next Greater Element I
    84. Largest Rectangle in Histogram
    42. Trapping Rain Water
    */
    
    // Time: O(n) Space: O(n)
    int scoreOfParentheses_(string s) {
        stack<int> stack;
        int cur = 0;
        for (char i : s) {
            if (i == '(') {
                stack.push(cur);
                cur = 0;
            } else {
                cur += stack.top() + max(cur, 1);
                stack.pop();
            }
        }
        return cur; 
    }
    // Time: O(n) Space: O(1)
    int scoreOfParentheses(string s) {
        int score = 0;
        int balance = 0;

        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                ++balance;
            } else {
                --balance;

                if (s[i - 1] == '(') {
                    score += 1 << balance;
                }
            }
        }

        return score;
    }
};
