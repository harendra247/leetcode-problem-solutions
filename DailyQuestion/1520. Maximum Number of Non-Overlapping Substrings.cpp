class Solution {
public:
    // Time: O(n) Space: O(n)
    vector<string> maxNumOfSubstrings(string s) {
        const int ALPHABET_SIZE = 26;
        const int n = s.size();

        // first[c] = first occurrence of character c
        // last[c]  = last occurrence of character c
        vector<int> first(ALPHABET_SIZE, n);
        vector<int> last(ALPHABET_SIZE, -1);

        // --------------------------------------------------
        // Step 1: Find first and last occurrence of each char.
        // --------------------------------------------------
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';

            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // --------------------------------------------------
        // Step 2: Build the smallest valid interval for
        //          every character.
        // --------------------------------------------------
        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            if (last[c] == -1) {
                continue;  // Character does not exist in s.
            }

            int left = first[c];
            int right = last[c];

            bool valid = true;

            /*
                Expand [left, right] whenever we find a
                character whose complete range lies outside it.
            */
            for (int i = left; i <= right; ++i) {
                int currentChar = s[i] - 'a';

                // This character has an occurrence before
                // our current interval.
                if (first[currentChar] < left) {
                    valid = false;
                    break;
                }

                // This character has an occurrence after
                // our current interval.
                if (last[currentChar] > right) {
                    right = last[currentChar];
                }
            }

            if (valid) {
                intervals.push_back({left, right});
            }
        }

        // --------------------------------------------------
        // Step 3: Greedily choose intervals that finish
        //          earliest.
        // --------------------------------------------------
        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) {
                 return a.second < b.second;
             });

        vector<string> answer;

        int previousEnd = -1;

        for (auto [left, right] : intervals) {
            /*
                The current substring must start after the
                previously selected substring ends.
            */
            if (left > previousEnd) {
                answer.push_back(s.substr(left, right - left + 1));

                previousEnd = right;
            }
        }

        return answer;
    }
};
