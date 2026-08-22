class Solution {
public:
    using VI = vector<int>;
    using VVI = vector<VI>;
        
    // Time: O(m*n) Space: O(m*n)
    int uniquePathsWithObstacles_dp(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0 || obstacleGrid[0].size() == 0)
            return 0;
        int n = obstacleGrid[0].size();
        
        VVI dp(m+1, VI(n+1, 0)); // 1 based index
        dp[0][1] = 1;
        for (int i = 1; i < m + 1; ++i) {
            for (int j = 1; j < n + 1; ++j) {
                if (!obstacleGrid[i-1][j-1]) { // obstacleGrid is 0 based index
                    dp[i][j] = dp[i-1][j] + dp[i][j-1]; // dp is 1 based index
                } 
            } 
        }
        return dp[m][n];
    }
    
    // Time: O(m*n) Space: O(1)
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int R = obstacleGrid.size();
        if (R == 0 || obstacleGrid[0].size() == 0)
            return 0;
        int C = obstacleGrid[0].size();
       
        // If the starting cell has an obstacle, then simply return as there would be
        // no paths to the destination.
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }

        // Number of ways of reaching the starting cell = 1.
        obstacleGrid[0][0] = 1;

        // Filling the values for the first column
        for (int i = 1; i < R; i++) {
            obstacleGrid[i][0] = (obstacleGrid[i][0] == 0 && obstacleGrid[i - 1][0] == 1) ? 1 : 0;
        }

        // Filling the values for the first row
        for (int i = 1; i < C; i++) {
            obstacleGrid[0][i] = (obstacleGrid[0][i] == 0 && obstacleGrid[0][i - 1] == 1) ? 1 : 0;
        }

        // Starting from cell(1,1) fill up the values
        // No. of ways of reaching cell[i][j] = cell[i - 1][j] + cell[i][j - 1]
        // i.e. From above and left.
        for (int i = 1; i < R; i++) {
            for (int j = 1; j < C; j++) {
                if (obstacleGrid[i][j] == 0) {
                    obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
                } else {
                    obstacleGrid[i][j] = 0;
                }
            }
        }

        // Return value stored in rightmost bottommost cell. That is the destination.
        return obstacleGrid[R - 1][C - 1];
    }
    
    
    int uniquePathsWithObstacles_2(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0 || obstacleGrid[0].size() == 0)
            return 0;
        
        int n = obstacleGrid[0].size();
        bool swap = false;
        if (n > m) {
            std::swap(m, n);
            swap = true;
        }
            
        vector<vector<long long>> dp(2, vector<long long>(n, 0));        
        for (int i = 0; i < m; ++i) {
            // ensure dp[1] is all 0 since we have +=, otherwise we might include the previous non-zero value
            std::fill(dp[1].begin(), dp[1].end(), 0);
            for (int j = 0; j < n; ++j) {
                if ((!swap && obstacleGrid[i][j] == 1) || (swap && obstacleGrid[j][i] == 1)) {
                    continue;
                }
                
                if (i == 0 && j == 0)
                    dp[1][0] = 1;
                    
                if (i > 0) 
                    dp[1][j] += dp[0][j];
    
                if (j > 0)
                    dp[1][j] += dp[1][j - 1];
            }
            std::swap(dp[0], dp[1]);
        }
        return dp[0][n - 1];
    }
    
    //By Harendra Working DFS+Memoization
    // Time: O(mn) Space: O(mn)
    int uniquePathsWithObstacles_1(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>> memo(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), -1));
        return dfs(obstacleGrid, 0, 0, memo);
    }
    
    int dfs(vector<vector<int>>& obstacleGrid, int i, int j, vector<vector<int>> &memo) {
        if (i < 0 || i >= obstacleGrid.size() || j < 0 || j >= obstacleGrid[0].size() || obstacleGrid[i][j] == 1) {
            return 0;
        }
        if (memo[i][j] > 0) return memo[i][j];
        
        if (i == obstacleGrid.size()-1 && j == obstacleGrid[0].size()-1) {
            return 1;
        }
        
        memo[i][j] = dfs(obstacleGrid, i+1, j, memo) + dfs(obstacleGrid, i, j+1, memo);
        return memo[i][j];
    }
};
