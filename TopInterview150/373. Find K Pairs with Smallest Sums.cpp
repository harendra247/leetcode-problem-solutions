class Solution {
public:
    // Let K = min(k, nums1.size() * nums2.size()).
    //
    // Time:  O(K log K)
    // Space: O(K)
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;

        if (nums1.empty() || nums2.empty() || k <= 0) {
            return result;
        }

        /*
         * Heap stores INDEX pairs:
         *
         * {i, j}
         *
         * representing:
         *
         * nums1[i] + nums2[j]
         *
         * Comparator makes this a min-heap by pair sum.
         */
        auto comp = [&nums1, &nums2](const pair<int, int>& a, const pair<int, int>& b) {
                return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
            };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);

        // Smallest possible pair.
        minHeap.push({0, 0});

        while (k-- > 0 && !minHeap.empty()) {

            auto [i, j] = minHeap.top();
            minHeap.pop();

            result.push_back({nums1[i], nums2[j]});

            /*
             * Always move DOWN:
             *
             * (i,j) -> (i+1,j)
             *
             * This generates the remaining pairs
             * in the same column j.
             */
            if (i + 1 < nums1.size()) {
                minHeap.push({i + 1, j});
            }

            /*
             * Move RIGHT only from row 0:
             *
             * (0,j) -> (0,j+1)
             *
             * This is the key trick that prevents duplicates.
             *
             * Row 0 starts each new column.
             */
            if (i == 0 && j + 1 < nums2.size()) {

                minHeap.push({0, j + 1});
            }
        }

        return result;
    }
};
