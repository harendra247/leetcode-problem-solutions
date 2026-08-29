class Solution {
public:
    // Time:  O(n log n)
    // Space: O(n)
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        /*
         * Step 1:
         * Sort the numbers.
         *
         * Sorting allows us to identify which numbers belong
         * to the same connected group.
         */
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        /*
         * groupOf[value] = group number of this value.
         *
         * Example:
         *
         * sorted = [1, 3, 5, 8, 9]
         * limit = 2
         *
         * groups:
         *
         * [1, 3, 5] -> group 0
         * [8, 9]    -> group 1
         */
        unordered_map<int, int> groupOf;

        /*
         * valuesInGroup[group] contains all values belonging
         * to that group.
         *
         * Since 'sorted' is already sorted, every group's vector
         * will automatically be sorted.
         */
        vector<vector<int>> valuesInGroup;

        int group = 0;

        valuesInGroup.push_back({sorted[0]});
        groupOf[sorted[0]] = group;

        for (int i = 1; i < n; ++i) {

            /*
             * If the gap is greater than limit, we cannot connect
             * the current number to the previous number.
             *
             * Therefore, start a new group.
             */
            if (sorted[i] - sorted[i - 1] > limit) {
                ++group;
                valuesInGroup.push_back({});
            }

            valuesInGroup[group].push_back(sorted[i]);
            groupOf[sorted[i]] = group;
        }

        /*
         * Keep track of which element from each group should be
         * used next.
         *
         * Since valuesInGroup[group] is sorted, we always take
         * the smallest unused value.
         */
        vector<int> index(valuesInGroup.size(), 0);

        /*
         * Step 3:
         * Process the original array.
         *
         * For each number:
         *
         *   1. Find its group.
         *   2. Take the smallest unused number from that group.
         */
        for (int i = 0; i < n; ++i) {

            int groupId = groupOf[nums[i]];

            nums[i] = valuesInGroup[groupId][index[groupId]++];
        }

        return nums;
    }
};
