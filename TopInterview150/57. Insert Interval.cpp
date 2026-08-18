class Solution {
public:
    // Time: O(n)
    // Space: O(n) for the result
    vector<vector<int>> insert(
        vector<vector<int>>& intervals,
        vector<int>& newInterval
    ) {
        vector<vector<int>> result;

        int i = 0;
        int n = intervals.size();

        /*
         * PHASE 1:
         * Add intervals that are completely BEFORE newInterval.
         *
         * No overlap when:
         *
         * intervals[i].end < newInterval.start
         *
         * Example:
         *
         * interval     = [1, 2]
         * newInterval  = [5, 8]
         *
         * 2 < 5
         *
         * So [1,2] can be copied directly.
         */
        while (i < n &&
               intervals[i][1] < newInterval[0]) {

            result.push_back(intervals[i]);
            ++i;
        }

        /*
         * PHASE 2:
         * Merge every interval that overlaps newInterval.
         *
         * Since intervals are sorted, overlap continues while:
         *
         * intervals[i].start <= newInterval.end
         *
         * Example:
         *
         * newInterval = [3, 7]
         * interval    = [5, 9]
         *
         * 5 <= 7
         *
         * They overlap, so merged interval becomes:
         *
         * [min(3,5), max(7,9)]
         * = [3,9]
         */
        while (i < n &&
               intervals[i][0] <= newInterval[1]) {

            newInterval[0] = min(
                newInterval[0],
                intervals[i][0]
            );

            newInterval[1] = max(
                newInterval[1],
                intervals[i][1]
            );

            ++i;
        }

        /*
         * After consuming all overlapping intervals,
         * newInterval now represents the final merged interval.
         */
        result.push_back(newInterval);

        /*
         * PHASE 3:
         * Everything remaining is completely AFTER
         * the merged newInterval.
         *
         * Since the input was sorted and non-overlapping,
         * these intervals can be copied directly.
         */
        while (i < n) {
            result.push_back(intervals[i]);
            ++i;
        }

        return result;
    }
};
