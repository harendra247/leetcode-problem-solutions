class Solution {
public:
    // Time: O(n log n)
    // Space: O(n) for the output
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        // Sort by start, then by end.
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> result;

        // First interval starts the first merged group.
        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {

            /*
             * Last merged interval:
             *
             * result.back() = [start, end]
             *
             * Current:
             *
             * intervals[i] = [currentStart, currentEnd]
             *
             * If:
             *
             * end >= currentStart
             *
             * they overlap.
             */
            if (result.back()[1] >= intervals[i][0]) {

                // Extend the merged interval if needed.
                result.back()[1] = max(
                    result.back()[1],
                    intervals[i][1]
                );

            } else {

                // No overlap -> begin a new merged interval.
                result.push_back(intervals[i]);
            }
        }

        return result;
    }
};
