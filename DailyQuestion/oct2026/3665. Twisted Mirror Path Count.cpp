class Solution {
public:
    // Time: O(rows * cols) Space: O(cols)
    int uniquePaths(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        constexpr int MOD = 1'000'000'007;
        int rows = grid.size();
        int cols = grid[0].size();

        // ways[col][0]: paths entering from above.
        // ways[col][1]: paths entering from the left.
        vector<array<long long, 2>> ways(cols, {0, 0});

        // Seed the starting path; the starting cell is assumed normal.
        ways[0][0] = 1;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                // ways[col] still contains the previous row's counts.
                long long fromAbove = 0;
                long long fromLeft = 0;

                if (row == 0 && col == 0) {
                    continue;
                }

                if (row > 0) {
                    if (grid[row - 1][col] == 0) {
                        fromAbove = (ways[col][0] + ways[col][1]) % MOD;
                    } else {
                        // Mirror turns rightward movement downward.
                        fromAbove = ways[col][1];
                    }
                }

                // ways[col - 1] contains the current row's counts.
                if (col > 0) {
                    if (grid[row][col - 1] == 0) {
                        fromLeft = (ways[col - 1][0] + ways[col - 1][1]) % MOD;
                    } else {
                        // Mirror turns downward movement rightward.
                        fromLeft = ways[col - 1][0];
                    }
                }

                ways[col] = {fromAbove, fromLeft};
            }
        }

        return static_cast<int>(
            (ways[cols - 1][0] + ways[cols - 1][1]) % MOD
        );
    }
};
