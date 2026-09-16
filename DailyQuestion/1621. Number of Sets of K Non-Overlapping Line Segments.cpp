const int MOD = 1'000'000'007;

class Solution {
public:
    // Time: O(nk) Space: O(n)
    int numberOfSets(int n, int k) {

        // dp[j] = number of ways for the current number of
        // segments where the last segment ends at point j.
        vector<int> dp(n, 0);

        // prefixSums[i] = dp[0] + dp[1] + ... + dp[i - 1]
        vector<int> prefixSums(n + 1, 0);

        /*
            Initially, we have chosen 0 segments.

            There is one empty configuration associated with
            every possible ending point.
        */
        for (int j = 0; j < n; ++j) {
            dp[j] = 1;

            prefixSums[j + 1] = (prefixSums[j] + dp[j]) % MOD;
        }

        /*
            Add one segment at a time.
        */
        for (int segments = 1; segments <= k; ++segments) {

            // No non-empty segment can end at point 0.
            dp[0] = 0;

            /*
                Calculate the number of ways for each possible
                right endpoint of the new segment.

                dp[j - 1]: ways where the new segment starts at j.

                prefixSums[j]: ways where the new segment starts before j.
            */
            for (int j = 1; j < n; ++j) {
                dp[j] = (dp[j - 1] + prefixSums[j]) % MOD;
            }

            // Rebuild prefix sums for the new dp array.
            for (int j = 0; j < n; ++j) {
                prefixSums[j + 1] = (prefixSums[j] + dp[j]) % MOD;
            }
        }

        // After k iterations, dp[n - 1] contains the
        // number of valid ways.
        return dp[n - 1];
    }
};
