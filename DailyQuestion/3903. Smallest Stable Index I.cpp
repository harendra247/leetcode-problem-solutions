class Solution {
public:
    /*
     * We need the first index i such that:
     *
     *     max(nums[0 ... i]) - min(nums[i ... n-1]) <= k
     *
     * ------------------------------------------------------------
     * Time:  O(n)
     * Space: O(n)
     * ------------------------------------------------------------
     */
    int firstStableIndex(vector<int>& nums, int k) {

        int n = nums.size();

        /*
         * suffixMin[i] stores the minimum value from index i
         * to the end of the array.
         *
         * Example:
         *
         * nums      = [5, 3, 4, 2, 1]
         *
         * suffixMin = [1, 1, 1, 1, 1]
         *
         * For example:
         *
         * suffixMin[2] = min(4, 2, 1) = 1
         */
        vector<int> suffixMin(n);

        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(nums[i], suffixMin[i + 1]);
        }

        /*
         * maxLeft represents:
         *
         *     max(nums[0 ... i])
         *
         * As we move from left to right, we can update it
         * in O(1).
         */
        int maxLeft = nums[0];

        for (int i = 0; i < n; ++i) {

            /*
             * Include nums[i] in the left portion.
             */
            maxLeft = max(maxLeft, nums[i]);

            /*
             * suffixMin[i] gives us:
             *
             *     min(nums[i ... n-1])
             */
            int minRight = suffixMin[i];

            /*
             * Check whether index i is stable.
             */
            if (maxLeft - minRight <= k) {
                return i;
            }
        }

        return -1;
    }
};
