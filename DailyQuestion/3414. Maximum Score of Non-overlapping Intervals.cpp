class Solution {
public:
    // Time: O(nlogn) Space: O(n)
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<int, 4>> arr;

        for (int i = 0; i < n; ++i) {
            arr.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint.
        sort(arr.begin(), arr.end(),
             [](const auto& a, const auto& b) {
                 return a[1] < b[1];
             });

        const long long NEG_INF = -(1LL << 60);

        /*
            dp[i][j] =
            maximum weight using the first i intervals
            while selecting exactly j intervals.
        */
        vector<vector<long long>> dp(
            n + 1,
            vector<long long>(5, NEG_INF)
        );

        // Store the original indices for each state.
        vector<vector<vector<int>>> chosen(
            n + 1,
            vector<vector<int>>(5)
        );

        // Selecting 0 intervals gives weight 0.
        dp[0][0] = 0;

        for (int i = 0; i < n; ++i) {
            int left = arr[i][0];
            int weight = arr[i][2];
            int index = arr[i][3];

            /*
                Find the number of previous intervals whose
                right endpoint is strictly less than 'left'.

                Those intervals can safely be combined with
                the current interval.
            */
            int k = lower_bound(
                arr.begin(),
                arr.begin() + i,
                left,
                [](const array<int, 4>& interval, int value) {
                    return interval[1] < value;
                }
            ) - arr.begin();

            // Option 1: don't take the current interval.
            for (int j = 0; j <= 4; ++j) {
                dp[i + 1][j] = dp[i][j];
                chosen[i + 1][j] = chosen[i][j];
            }

            // Option 2: take the current interval.
            for (int j = 1; j <= 4; ++j) {
                if (dp[k][j - 1] == NEG_INF) {
                    continue;
                }

                long long newWeight = dp[k][j - 1] + weight;

                vector<int> newIndices = chosen[k][j - 1];
                newIndices.push_back(index);

                // Required for lexicographical comparison.
                sort(newIndices.begin(), newIndices.end());

                if (newWeight > dp[i + 1][j] ||
                    (newWeight == dp[i + 1][j] &&
                     newIndices < chosen[i + 1][j])) {

                    dp[i + 1][j] = newWeight;
                    chosen[i + 1][j] = newIndices;
                }
            }
        }

        /*
            We can select AT MOST 4 intervals.

            Therefore, compare the answers for:
                1 interval
                2 intervals
                3 intervals
                4 intervals

            and choose the maximum weight.
        */
        long long bestWeight = 0;
        vector<int> answer;

        for (int j = 1; j <= 4; ++j) {
            if (dp[n][j] > bestWeight ||
                (dp[n][j] == bestWeight &&
                 chosen[n][j] < answer)) {

                bestWeight = dp[n][j];
                answer = chosen[n][j];
            }
        }

        return answer;
    }
};
