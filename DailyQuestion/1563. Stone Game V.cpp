class Solution {
private:
    /*
     * dp[l][r]:
     * maximum score Alice can obtain from stones[l ... r].
     */
    vector<vector<int>> dp;

    /*
     * bestLeft[l][r]:
     *
     * max over k in [l ... r] of:
     *
     * sum(l ... k) + dp[l][k]
     *
     * Used when the LEFT side of a split is kept.
     */
    vector<vector<int>> bestLeft;

    /*
     * bestRight[l][r]:
     *
     * max over k in [l ... r] of:
     *
     * sum(k ... r) + dp[k][r]
     *
     * Used when the RIGHT side of a split is kept.
     */
    vector<vector<int>> bestRight;

public:
    // Time: O(n^2)
    // Space: O(n^2)
    int stoneGameV_(vector<int>& stoneValue) {
        int n = stoneValue.size();

        dp.assign(n, vector<int>(n, 0));
        bestLeft.assign(n, vector<int>(n, 0));
        bestRight.assign(n, vector<int>(n, 0));

        /*
         * Process intervals by decreasing left endpoint.
         *
         * This ensures smaller required subintervals
         * are already computed.
         */
        for (int left = n - 1; left >= 0; --left) {

            /*
             * Single-element interval.
             *
             * dp[left][left] = 0:
             * no split is possible.
             *
             * But:
             *
             * sum + dp = stoneValue[left]
             */
            bestLeft[left][left] = bestRight[left][left] = stoneValue[left];

            /*
             * totalSum = sum(left ... right)
             *
             * leftSum = sum(left ... splitPoint)
             *
             * splitPoint is represented by 'i'.
             */
            int totalSum = stoneValue[left];
            int leftSum = 0;

            /*
             * i will become the largest index satisfying:
             *
             * sum(left ... i)
             * <=
             * sum(i+1 ... right)
             */
            int i = left - 1;

            for (int right = left + 1; right < n; ++right) {

                totalSum += stoneValue[right];

                /*
                 * Move i right as long as the left portion
                 * remains <= the right portion.
                 *
                 * 2 * leftSum <= totalSum
                 */
                while (
                    i + 1 < right &&
                    (leftSum + stoneValue[i + 1]) * 2
                        <= totalSum
                ) {
                    leftSum += stoneValue[i + 1];
                    ++i;
                }

                /*
                 * ------------------------------------------------
                 * CASE 1:
                 * split at k <= i
                 *
                 * leftSum <= rightSum
                 *
                 * Alice keeps LEFT side:
                 *
                 * score =
                 * sum(left ... k) + dp[left][k]
                 *
                 * bestLeft[left][i] gives the best such choice.
                 * ------------------------------------------------
                 */
                if (left <= i) {
                    dp[left][right] = max(
                            dp[left][right],
                            bestLeft[left][i]
                        );
                }

                /*
                 * ------------------------------------------------
                 * CASE 2:
                 * split after i
                 *
                 * leftSum > rightSum
                 *
                 * Alice keeps RIGHT side.
                 *
                 * For split k = i+1,
                 * right side begins at i+2.
                 *
                 * bestRight[i+2][right] gives the best
                 * right-side choice among these splits.
                 * ------------------------------------------------
                 */
                if (i + 1 < right) {
                    dp[left][right] = max(
                            dp[left][right],
                            bestRight[i + 2][right]
                        );
                }

                /*
                 * ------------------------------------------------
                 * CASE 3:
                 * exact equality:
                 *
                 * leftSum == rightSum
                 *
                 * Alice may choose EITHER side.
                 *
                 * Left choice was already handled above.
                 *
                 * Here we explicitly allow choosing
                 * the right side starting at i+1.
                 * ------------------------------------------------
                 */
                if (leftSum * 2 == totalSum) {
                    dp[left][right] = max(
                            dp[left][right],
                            bestRight[i + 1][right]
                        );
                }

                /*
                 * Update prefix-style maximum.
                 *
                 * Candidate corresponding to the full
                 * interval [left ... right]:
                 *
                 * totalSum + dp[left][right]
                 */
                bestLeft[left][right] = max(
                        bestLeft[left][right - 1],
                        totalSum + dp[left][right]
                    );

                /*
                 * Update suffix-style maximum.
                 */
                bestRight[left][right] = max(
                        bestRight[left + 1][right],
                        totalSum + dp[left][right]
                    );
            }
        }

        return dp[0][n - 1];
    }

private:
    vector<vector<int>> memo;
    vector<int> prefix;
    vector<int> stones;

    // Maximum score Alice can obtain from stones[l ... r].
    int solve(int l, int r) {
        // One stone => cannot split.
        if (l >= r) {
            return 0;
        }

        if (memo[l][r] != -1) {
            return memo[l][r];
        }

        int best = 0;

        /*
         * rightSum initially contains the full interval:
         *
         * stones[l ... r]
         */
        int leftSum = 0;
        int rightSum = prefix[r + 1] - prefix[l];

        /*
         * Try every split:
         *
         * [l ... k] | [k+1 ... r]
         */
        for (int k = l; k < r; ++k) {

            // Move stones[k] from right side to left side.
            leftSum += stones[k];
            rightSum -= stones[k];

            if (leftSum < rightSum) {
                /*
                 * Left side has smaller sum,
                 * so Alice MUST keep the left side.
                 *
                 * Current gain:
                 *     leftSum
                 *
                 * Future gain:
                 *     solve(l, k)
                 */
                best = max(best, leftSum + solve(l, k));
            } else if (leftSum > rightSum) {
                /*
                 * Right side has smaller sum,
                 * so Alice MUST keep the right side.
                 */
                best = max(best, rightSum + solve(k + 1, r));
            } else {
                /*
                 * Equal sums:
                 * Alice may choose either side.
                 */
                best = max({best, leftSum + solve(l, k), rightSum + solve(k + 1, r)});
            }
        }

        return memo[l][r] = best;
    }

public:
    // Time: O(n^3)
    // Space: O(n^2)
    int stoneGameV(vector<int>& stoneValue) {
        stones = stoneValue;

        int n = stones.size();

        // Prefix sums:
        // prefix[i] = sum of stones[0 ... i-1]
        prefix.assign(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + stones[i];
        }

        memo.assign(n, vector<int>(n, -1));

        return solve(0, n - 1);
    }
};
