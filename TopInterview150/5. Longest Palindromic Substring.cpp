class Solution {
public:
    // extension of https://leetcode.com/problems/palindromic-substrings/
    // Expand Around Center
    // Time: O(n^2)
    // Space: O(1) auxiliary
    string longestPalindrome(string s) {
        int n = s.size();

        if (n == 0) {
            return "";
        }

        string answer = s.substr(0, 1);

        /*
         * Expand outward from a possible palindrome center.
         *
         * left == right:
         *     odd-length palindrome
         *
         * right == left + 1:
         *     even-length palindrome
         */
        auto expand = [&](int left, int right) {

            /*
             * Keep expanding while:
             *
             * 1. indices are valid
             * 2. characters on both sides match
             */
            while (left >= 0 && right < n && s[left] == s[right]) {
                int length = right - left + 1;

                if (length > answer.size()) {
                    answer = s.substr(left, length);
                }

                --left;
                ++right;
            }
        };

        /*
         * Every position can be an odd center,
         * and every gap can be an even center.
         */
        for (int i = 0; i < n; ++i) {
            expand(i, i);       // odd
            expand(i, i + 1);   // even
        }

        return answer;
    }
    
private:
    vector<vector<int>> memo;
    string ans;

    bool go(const string& s, int i, int j) {
        if (i > j) {
            return true;
        }

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        if (i == j) {
            if (ans.size() < 1) {
                ans = s.substr(i, 1);
            }
            return memo[i][j] = true;
        }

        // Explore smaller substrings so all candidates are considered.
        go(s, i + 1, j);
        go(s, i, j - 1);

        bool isPalindrome =
            s[i] == s[j] &&
            (j - i == 1 || go(s, i + 1, j - 1));

        if (isPalindrome && ans.size() < j - i + 1) {
            ans = s.substr(i, j - i + 1);
        }

        return memo[i][j] = isPalindrome;
    }

public:
    // Time: O(n²), Space: O(n²)
    string longestPalindrome_r(const string& s) {
        if (s.size() <= 1) {
            return s;
        }

        int n = static_cast<int>(s.size());
        memo.assign(n, vector<int>(n, -1));

        go(s, 0, n - 1);
        return ans;
    }
};
