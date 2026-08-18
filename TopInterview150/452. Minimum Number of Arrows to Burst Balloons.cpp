class Solution {
public:
    // Greedy: sort balloons by their ending coordinate.
    //
    // Time:  O(n log n)
    // Space: O(1) auxiliary, ignoring sorting stack
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }

        /*
         * Sort by END coordinate.
         *
         * Example:
         *
         * [10,16], [2,8], [1,6], [7,12]
         *
         * becomes:
         *
         * [1,6], [2,8], [7,12], [10,16]
         */
        sort(points.begin(), points.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        /*
         * Shoot the first arrow at the end of
         * the first balloon.
         *
         * Since this balloon ends earliest,
         * this is the best greedy position.
         */
        int arrowPos = points[0][1];
        int arrowCnt = 1;

        for (int i = 1; i < points.size(); ++i) {

            /*
             * Current balloon:
             *
             * [points[i][0] -------- points[i][1]]
             *
             * If:
             *
             *     points[i][0] <= arrowPos
             *
             * our existing arrow lies inside this balloon,
             * so this balloon is already burst.
             *
             * No new arrow is needed.
             */
            if (points[i][0] <= arrowPos) {
                continue;
            }

            /*
             * Otherwise:
             *
             *     points[i][0] > arrowPos
             *
             * Current balloon starts AFTER our previous arrow.
             *
             * Previous arrow cannot burst this balloon,
             * so we need another arrow.
             */
            ++arrowCnt;

            /*
             * Greedy choice:
             *
             * Shoot the new arrow at this balloon's END.
             *
             * Because we're sorted by end coordinate,
             * this gives us the best chance of also hitting
             * upcoming balloons.
             */
            arrowPos = points[i][1];
        }

        return arrowCnt;
    }
    
    // Sort by starting coordinate
    // Time: O(n log n)
    // Space: O(1) auxiliary (ignoring sort implementation)
    int findMinArrowShots_(vector<vector<int>>& points) {
        int count = 0;

        // Rightmost possible position for the arrow
        // that can hit the current overlapping group.
        int arrowPos = INT_MAX;

        // Sort primarily by start coordinate.
        sort(points.begin(), points.end());

        for (auto& p : points) {

            /*
            * Current balloon:
            *
            *     [p[0] -------- p[1]]
            *
            * If its start is AFTER arrowPos,
            * the current arrow cannot hit this balloon.
            *
            * Therefore, finish the previous group
            * and start a new arrow group.
            */
            if (p[0] > arrowPos) {
                count++;

                // New overlapping group starts.
                // Initially the arrow can be placed as far
                // right as this balloon's end.
                arrowPos = p[1];
            }
            else {
                /*
                * Current balloon overlaps with our
                * existing group.
                *
                * Restrict the valid arrow position to
                * the intersection of all balloons seen
                * in this group.
                */
                arrowPos = min(arrowPos, p[1]);
            }
        }

        /*
        * count increases when we LEAVE an overlapping group.
        *
        * Therefore the final group hasn't been counted yet.
        */
        return count + !points.empty();
    }
};
