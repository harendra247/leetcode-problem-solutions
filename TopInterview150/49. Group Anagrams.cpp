class Solution {
public:
    // N = number of strings
    // K = average/max length of each string
    //
    // Time:  O(N * K)
    // Space: O(N * K)
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {

            int freq[26] = {0};

            // Count each character.
            for (char ch : s) {
                ++freq[ch - 'a'];
            }

            /*
             * Build a unique signature from frequencies.
             *
             * Example:
             *
             * "eat":
             * a=1, e=1, t=1
             *
             * key could look like:
             *
             * "#1#0#0#0#1...#1..."
             *
             * The '#' separator is important.
             * Without separators:
             *
             * [1,11] and [11,1]
             *
             * could otherwise become ambiguous.
             */
            string key;

            for (int count : freq) {
                key += '#';
                key += to_string(count);
            }

            groups[key].push_back(s);
        }

        vector<vector<string>> result;

        for (auto& [key, group] : groups) {
            result.push_back(move(group));
        }

        return result;
    }
};
