class Solution {
public:
    // Time: O(n^3) Space: O(1)
    int totalNumbers(vector<int>& digits) {
        bool seen[1000] = {};
        int ans = 0;
        int n = digits.size();

        for (int i = 0; i < n; ++i) {
            // Hundreds digit cannot be zero.
            if (digits[i] == 0) {
                continue;
            }

            for (int j = 0; j < n; ++j) {
                // Cannot reuse the same digit occurrence.
                if (j == i) {
                    continue;
                }

                for (int k = 0; k < n; ++k) {
                    // k must be a different occurrence
                    // and the last digit must be even.
                    if (k == i || k == j || digits[k] % 2 != 0) {
                        continue;
                    }

                    int number = digits[i] * 100
                               + digits[j] * 10
                               + digits[k];

                    // Count each distinct number only once.
                    if (!seen[number]) {
                        seen[number] = true;
                        ++ans;
                    }
                }
            }
        }

        return ans;
    }
};
