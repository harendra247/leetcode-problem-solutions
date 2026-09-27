class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    string reverseParentheses(string s) {
        const int n = s.size();

        stack<int> open;
        vector<int> matching(n);

        // Step 1: Find the matching parenthesis for every '(' and ')'.
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                open.push(i);
            }
            else if (s[i] == ')') {
                int j = open.top();
                open.pop();

                matching[i] = j;
                matching[j] = i;
            }
        }

        // Step 2: Traverse the string.
        // Whenever we hit a parenthesis, jump to its pair
        // and reverse the traversal direction.
        string result;

        int index = 0;
        int direction = 1;

        while (index < n) {
            if (s[index] == '(' || s[index] == ')') {
                index = matching[index];
                direction = -direction;
            } else {
                result.push_back(s[index]);
            }

            index += direction;
        }

        return result;
    }
};
