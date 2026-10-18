class Solution {
private:
    static constexpr long long MOD = 1'000'000'007;

    long long countWays(const vector<int>& values, vector<vector<long long>> &combinations) {
        const int nodeCount = values.size();

        if (nodeCount <= 2) {
            return 1;
        }

        vector<int> leftValues;
        vector<int> rightValues;

        const int rootValue = values[0];

        for (int i = 1; i < nodeCount; ++i) {
            if (values[i] < rootValue) {
                leftValues.push_back(values[i]);
            } else {
                rightValues.push_back(values[i]);
            }
        }

        long long leftWays = countWays(leftValues, combinations);

        long long rightWays = countWays(rightValues, combinations);

        long long interleavings = combinations[nodeCount - 1][leftValues.size()];

        return (((interleavings * leftWays) % MOD) * rightWays) % MOD;
    }

public:
    // Time: O(n^2) Space: O(n^2)
    int numOfWays(vector<int>& nums) {
        const int n = nums.size();

        // Build Pascal's triangle:
        // combinations[i][j] = C(i, j)
        vector<vector<long long>> combinations(n + 1, vector<long long>(n + 1, 0));

        for (int i = 0; i <= n; ++i) {
            combinations[i][0] = 1;
            combinations[i][i] = 1;

            for (int j = 1; j < i; ++j) {
                combinations[i][j] = (combinations[i - 1][j - 1] + combinations[i - 1][j]) % MOD;
            }
        }

        return static_cast<int>((countWays(nums, combinations) - 1 + MOD) % MOD);
    }
};
