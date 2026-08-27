class Solution {
private:
    // Build the lexicographically smallest string using
    // the characters represented by cnt.
    //
    // Example:
    // cnt[a] = 2, cnt[c] = 1, cnt[d] = 1
    // => "aacd"
    string getMinString(const vector<int>& cnt) {
        string result;

        for (int c = 0; c < 26; ++c) {
            result.append(cnt[c], 'a' + c);
        }

        return result;
    }

public:
    // Time:  O(26 * n) = O(n) Space: O(26 + n) = O(n)
    string lexGreaterPermutation(string s, string target) {
        const int n = s.size();

        /*
         * cnt[c] represents:
         *
         *     frequency of character c in s
         *     -
         *     frequency of character c in target
         *
         * Initially, target is considered completely matched.
         *
         * If cnt[c] < 0, we don't have enough occurrences of
         * character c in s to match the corresponding prefix.
         */
        vector<int> cnt(26, 0);

        for (char c : s) {
            ++cnt[c - 'a'];
        }

        for (char c : target) {
            --cnt[c - 'a'];
        }

        /*
         * We want the answer to be as close to target as possible.
         *
         * Therefore, try to make the answer greater at the
         * RIGHTMOST possible position.
         *
         * Example:
         *
         * target = "abcd"
         *
         * Prefer changing:
         *
         *        abcX
         *        abXd
         *        aXcd
         *        Xbcd
         *
         * in that order.
         */
        for (int i = n - 1; i >= 0; --i) {

            /*
             * We are no longer trying to match target[i].
             *
             * Put target[i] back into our available character pool.
             *
             * This means:
             *
             *     prefix = target[0 ... i-1]
             *
             * is still required to match exactly.
             */
            int currentChar = target[i] - 'a';
            ++cnt[currentChar];

            /*
             * Check whether target[0 ... i-1] can be constructed
             * from the characters available in s.
             *
             * If any count is negative, we don't have enough
             * of that character, so this position cannot be used.
             */
            bool prefixPossible = true;

            for (int c = 0; c < 26; ++c) {
                if (cnt[c] < 0) {
                    prefixPossible = false;
                    break;
                }
            }

            if (!prefixPossible) {
                continue;
            }

            /*
             * The prefix can be matched.
             *
             * Now we need to make the answer GREATER than target.
             *
             * Therefore, replace target[i] with the SMALLEST
             * available character that is greater than target[i].
             */
            for (int c = currentChar + 1; c < 26; ++c) {

                if (cnt[c] == 0) {
                    continue;
                }

                /*
                 * Use this character at position i.
                 */
                --cnt[c];

                /*
                 * We now have:
                 *
                 *     target[0 ... i-1]
                 *     + character greater than target[i]
                 *
                 * Since the answer is already greater than target,
                 * everything after i should be as small as possible.
                 *
                 * Therefore, sort/use all remaining characters
                 * in ascending order.
                 */
                string answer = target.substr(0, i);
                answer += char('a' + c);
                answer += getMinString(cnt);

                return answer;
            }
        }

        /*
         * No position could be increased while still forming
         * a valid permutation of s.
         *
         * Therefore, no permutation of s is greater than target.
         */
        return "";
    }
};
