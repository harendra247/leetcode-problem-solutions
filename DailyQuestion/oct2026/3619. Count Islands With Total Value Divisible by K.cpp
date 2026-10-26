class Solution {
public:
    // Time: O(m*n) Space: O(1)
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        function<void(int, int, int &)> dfs;
        dfs = [&](int i, int j, int &sum) -> void {
            if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0)
                return;
        
            sum = (sum + grid[i][j]) % k;
            grid[i][j] = 0;
            dfs(i, j + 1, sum);
            dfs(i, j - 1, sum);
            dfs(i + 1, j, sum);
            dfs(i - 1, j, sum);
            
            return;
        };

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int sum = 0;
                if (grid[i][j]) {
                    dfs(i, j, sum);
                    ans += (sum % k == 0);
                }
            }
        }
        return ans;
    }
};
