class Solution {
public:
    // Time: O(rows * cols)
    // Space: O(rows * cols)
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int rows = matrix.size();
        int cols = matrix[0].size();

        /*
         * dp[r][c] =
         * side length of largest square ending at
         * matrix[r-1][c-1].
         *
         * Extra first row/column of zeros avoids
         * boundary checks.
         */
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));

        int largestSide = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {

                if (matrix[i][j] == '1') {
                    dp[i + 1][j + 1] =
                        1 + min({
                            dp[i][j],       // top-left
                            dp[i][j + 1],   // top
                            dp[i + 1][j]    // left
                        });

                    largestSide = max(largestSide, dp[i + 1][j + 1]);
                }
            }
        }

        // Problem asks for area, not side length.
        return largestSide * largestSide;
    }
};
