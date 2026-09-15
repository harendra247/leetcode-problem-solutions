class Solution {
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }

            ++left;
            --right;
        }

        return true;
    }

public:
    // Time: O(nk) Space: O(1)
    int maxPalindromes(string s, int k) {
        const int n = s.size();

        int answer = 0;
        int nextStart = 0;

        for (int right = k - 1; right < n; ++right) {

            // First try a palindrome of exactly length k.
            int left = right - k + 1;

            if (left >= nextStart && isPalindrome(s, left, right)) {
                ++answer;
                nextStart = right + 1;
                continue;
            }

            // If length k doesn't work, try length k + 1.
            left = right - k;

            if (left >= nextStart && isPalindrome(s, left, right)) {
                ++answer;
                nextStart = right + 1;
            }
        }

        return answer;
    }
};
