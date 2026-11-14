class Solution {
public:
    // Time: O(n * (r - l + 1))) Space: O(n)
    int minimumSumSubarray_(vector<int>& nums, int l, int r) {
        int n = nums.size(), best = INT_MAX;
        vector<int> pre(n + 1);  // pre[i] = sum(nums[:i])
        partial_sum(nums.begin(), nums.end(), pre.begin() + 1);
        for (int k = l; k <= r; ++k)
            for (int i = 0; i + k <= n; ++i) {
                int s = pre[i + k] - pre[i];
                if (s > 0) best = min(best, s);
            }
        return best == INT_MAX ? -1 : best;
    }

    // Time: O(n * logn) Space: O(n)
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        // Use long long for prefix sums if n is large to prevent integer overflow
        vector<long long> pre(n + 1, 0);
        partial_sum(nums.begin(), nums.end(), pre.begin() + 1);

        multiset<long long> window;
        long long best = LLONG_MAX;

        for (int j = l; j <= n; ++j) {
            // Add the newly valid left endpoint (length l away from j)
            window.insert(pre[j - l]);

            // Remove the left endpoint that falls out of range (length > r away from j)
            if (j - r - 1 >= 0) {
                window.erase(window.find(pre[j - r - 1]));
            }

            // Find the smallest element >= pre[j]
            auto it = window.lower_bound(pre[j]);

            // Step back once to get the largest prefix sum strictly < pre[j]
            if (it != window.begin()) {
                --it;
                best = min(best, pre[j] - *it);
            }
        }

        return best == LLONG_MAX ? -1 : static_cast<int>(best);
    }

};
