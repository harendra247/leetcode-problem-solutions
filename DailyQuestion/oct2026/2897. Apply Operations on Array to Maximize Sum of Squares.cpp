class Solution {
public:
    // Time: O(n+k) Space: O(1)
    int maxSum(vector<int>& nums, int k) {
        constexpr int MOD = 1'000'000'007;
        constexpr int BITS = 30;
        int bitCount[BITS] = {};

        for (int num : nums) {
            for (int bit = 0; bit < BITS; ++bit) {
                if (num & (1 << bit)) {
                    ++bitCount[bit];
                }
            }
        }

        long long answer = 0;

        for (int i = 0; i < k; ++i) {
            long long value = 0;

            for (int bit = 0; bit < BITS; ++bit) {
                if (bitCount[bit] > 0) {
                    value |= 1LL << bit;
                    --bitCount[bit];
                }
            }

            // All later constructed values would also be zero.
            if (value == 0) {
                break;
            }

            answer = (answer + value * value) % MOD;
        }

        return static_cast<int>(answer);
    }
};
