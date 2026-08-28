class Solution {
private:
    /*
     * Build the complete palindrome from its left half.
     */
    string makePalindrome(const string& left, char middle) {
        string right = left;
        reverse(right.begin(), right.end());

        if (middle == '\0') {
            return left + right;
        }

        return left + middle + right;
    }

    /*
     * Construct the lexicographically smallest string from cnt.
     */
    string makeSmallest(const vector<int>& cnt) {
        string result;
        for (int c = 0; c < 26; ++c) {
            result.append(cnt[c], char('a' + c));
        }
        return result;
    }

public:
    // Time: O(n) Space: O(n)
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int half = n / 2;

        /*
         * ---------------------------------------------------------
         * Step 1: Count characters in s and check palindrome validity.
         * ---------------------------------------------------------
         */
        vector<int> freq(26, 0);
        for (char c : s) {
            ++freq[c - 'a'];
        }

        char middle = '\0';
        for (int c = 0; c < 26; ++c) {
            if (freq[c] % 2 == 1) {
                if (middle != '\0') {
                    // More than one odd count => impossible to form a palindrome.
                    return "";
                }
                middle = char('a' + c);
            }
            freq[c] /= 2;
        }

        /*
         * ---------------------------------------------------------
         * Step 2: Try using target's exact left half.
         *
         * If target's left half can be formed and the resulting
         * palindrome is strictly greater than target, this is
         * guaranteed to be the smallest valid palindrome.
         * ---------------------------------------------------------
         */
        vector<int> cnt = freq;
        bool can_match_left = true;
        string exact_left = "";

        for (int i = 0; i < half; ++i) {
            int c = target[i] - 'a';
            if (cnt[c] == 0) {
                can_match_left = false;
                break;
            }
            --cnt[c];
            exact_left.push_back(target[i]);
        }

        if (can_match_left) {
            string candidate = makePalindrome(exact_left, middle);
            if (candidate > target) {
                return candidate;
            }
        }

        /*
         * ---------------------------------------------------------
         * Step 3: Find the smallest left half strictly greater than
         *         target's left half.
         * ---------------------------------------------------------
         */
        cnt = freq;
        for (int i = 0; i < half; ++i) {
            --cnt[target[i] - 'a'];
        }

        for (int i = half - 1; i >= 0; --i) {
            int current = target[i] - 'a';
            ++cnt[current]; // Give target[i] back

            // Check if target[0 ... i-1] can be formed
            bool possible = true;
            for (int c = 0; c < 26; ++c) {
                if (cnt[c] < 0) {
                    possible = false;
                    break;
                }
            }

            if (!possible) {
                continue;
            }

            // Replace target[i] with the smallest available char > target[i]
            for (int c = current + 1; c < 26; ++c) {
                if (cnt[c] == 0) {
                    continue;
                }

                --cnt[c];
                string left = target.substr(0, i);
                left.push_back(char('a' + c));
                left += makeSmallest(cnt);

                return makePalindrome(left, middle);
            }
        }

        return "";
    }
};
