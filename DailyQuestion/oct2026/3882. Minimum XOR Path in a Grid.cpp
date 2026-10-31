class Solution {
public:
    // Time: O(m*n) Space: O(n)
    int minCost(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Before updating column c: dp[c] represents the cell above.
        // After updating: dp[c] represents the current cell.
        vector<unordered_set<int>> dp(cols);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (r == 0 && c == 0) {
                    dp[c].insert(grid[r][c]);
                    continue;
                }

                unordered_set<int> reachable;

                // Arrive from above.
                if (r > 0) {
                    for (int previous : dp[c]) {
                        reachable.insert(previous ^ grid[r][c]);
                    }
                }

                // Arrive from the left.
                if (c > 0) {
                    for (int previous : dp[c - 1]) {
                        reachable.insert(previous ^ grid[r][c]);
                    }
                }

                dp[c] = std::move(reachable);
            }
        }

        return *min_element(dp.back().begin(), dp.back().end());
    }
};
