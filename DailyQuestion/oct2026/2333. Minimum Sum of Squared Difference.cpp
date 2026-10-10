class Solution {
public:
    // Time: O(n+m) Space: O(m)
    long long minSumSquareDiff(vector<int>& nums1,
                              vector<int>& nums2,
                              int k1, int k2) {
        long long operations = 1LL * k1 + k2;
        long long totalDifference = 0;
        int maxDifference = 0;

        for (int i = 0; i < nums1.size(); ++i) {
            int difference = abs(nums1[i] - nums2[i]);
            totalDifference += difference;
            maxDifference = max(maxDifference, difference);
        }

        // Each operation can reduce one difference by one.
        if (operations >= totalDifference) {
            return 0;
        }

        vector<int> frequency(maxDifference + 1, 0);

        for (int i = 0; i < nums1.size(); ++i) {
            ++frequency[abs(nums1[i] - nums2[i])];
        }

        // Reduce the largest differences first.
        for (int d = maxDifference; d > 0 && operations > 0; --d) {
            int reduced = static_cast<int>(
                min(static_cast<long long>(frequency[d]), operations)
            );

            frequency[d] -= reduced;
            frequency[d - 1] += reduced;
            operations -= reduced;
        }

        long long answer = 0;
        for (int d = 1; d <= maxDifference; ++d) {
            answer += 1LL * frequency[d] * d * d;
        }

        return answer;
    }
};
