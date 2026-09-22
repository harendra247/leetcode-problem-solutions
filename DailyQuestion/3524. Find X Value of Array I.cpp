class Solution {
public:
    // Time: O(nk) Space: O(k)
    vector<long long> resultArray(vector<int>& nums, int k) {
        const int n = nums.size();

        /*
            dp[r] =
            Number of non-empty subarrays ending at the
            previous index whose product % k == r.
        */
        vector<long long> dp(k, 0);

        /*
            result[r] =
            Total number of non-empty subarrays seen so far
            whose product % k == r.
        */
        vector<long long> result(k, 0);

        for (int i = 0; i < n; ++i) {
            vector<long long> nextDp(k, 0);

            /*
                Option 1:
                Start a new subarray containing only nums[i].
            */
            int singleRemainder = nums[i] % k;
            ++nextDp[singleRemainder];

            /*
                Option 2:
                Extend every subarray that ended at i - 1.
            */
            for (int remainder = 0; remainder < k; ++remainder) {
                if (dp[remainder] == 0) {
                    continue;
                }

                int newRemainder =
                    (long long)remainder * nums[i] % k;

                nextDp[newRemainder] += dp[remainder];
            }

            /*
                Move the current layer into dp.

                Now dp represents all subarrays ending at i.
            */
            dp = move(nextDp);

            /*
                Every subarray has exactly one ending index,
                so adding dp to result counts every subarray
                exactly once.
            */
            for (int remainder = 0; remainder < k; ++remainder) {
                result[remainder] += dp[remainder];
            }
        }

        return result;
    }
};
