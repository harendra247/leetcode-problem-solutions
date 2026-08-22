class Solution {
public:
    // DP BU Time: O(m*n) Space: O(m*n)
    int minPathSum_o(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size(); 
        vector<vector<int> > sum(m, vector<int>(n, grid[0][0]));
        for (int i = 1; i < m; i++)
            sum[i][0] = sum[i - 1][0] + grid[i][0];
        for (int j = 1; j < n; j++)
            sum[0][j] = sum[0][j - 1] + grid[0][j];
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                sum[i][j]  = min(sum[i - 1][j], sum[i][j - 1]) + grid[i][j];
        return sum[m - 1][n - 1];
    }
    
    //DP Improved : Time: O(n*m) Space: O(m)
    int minPathSum_(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> cur(m, grid[0][0]);
        for (int i = 1; i < m; i++)
            cur[i] = cur[i - 1] + grid[i][0]; 
        for (int j = 1; j < n; j++) {
            cur[0] += grid[0][j]; 
            for (int i = 1; i < m; i++)
                cur[i] = min(cur[i - 1], cur[i]) + grid[i][j];
        }
        return cur[m - 1];
    }
    
    //DP Improved : Time: O(n*m) Space: O(1)
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size(); 
        for (int i = 1; i < m; i++)
            grid[i][0] += grid[i - 1][0];
        for (int j = 1; j < n; j++)
            grid[0][j] += grid[0][j - 1];
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
        return grid[m - 1][n - 1];    
    }
};
