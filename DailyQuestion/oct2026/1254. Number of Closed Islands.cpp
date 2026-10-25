class Solution {
public:
    
    // Time: O(n^2) Space: O(n^2)
    int closedIsland_(vector<vector<int>>& grid) {
        for (int i=0; i < grid[0].size(); i++) {
            fill(0, i, grid);
            fill(grid.size()-1, i, grid);
        }
        
        for (int i=1; i < grid.size(); i++) {
            fill(i, grid[0].size()-1, grid);
            fill(i, 0, grid);
        }
        
        int count = 0;
        for (int i=1; i < grid.size(); i++) {
            for (int j=1; j< grid[0].size(); j++) {
                if (grid[i][j] == 0) {
                    count++;
                    fill(i, j, grid);
                }
            }
        }
        
        return count;
    }
    
    void fill(int i, int j, vector<vector<int>>& grid) {
        if (i<0 or i>=grid.size() or j<0 or j>=grid[0].size() or grid[i][j] == 1) {
            return;
        } 
        grid[i][j] = 1;
        fill(i, j+1, grid);
        fill(i+1, j, grid);
        fill(i, j-1, grid);
        fill(i-1, j, grid);
    }

    int closedIsland_dfs(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        vector<vector<bool>> visit(m, vector<bool>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && !visit[i][j] && dfs(i, j, grid, visit)) {
                    count++;
                }
            }
        }
        return count;
    }

    bool dfs(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& visit) {
        int m = grid.size();
        int n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n) {
            return false;
        }
        if (grid[x][y] == 1 || visit[x][y]) {
            return true;
        }

        visit[x][y] = true;
        bool isClosed = true;
        vector<int> dir {0, 1, 0, -1, 0};

        for (int i = 0; i < 4; i++) {
            int r = x + dir[i];
            int c = y + dir[i+1];
            if (!dfs(r, c, grid, visit)) {
                isClosed = false;
            }
        }

        return isClosed;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && !visit[i][j] && bfs(i, j, grid, visit)) {
                    count++;
                }
            }
        }
        return count;
    }

    bool bfs(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& visit) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        q.push({x, y});
        visit[x][y] = true;
        bool isClosed = true;

        vector<int> dir{0, 1, 0, -1, 0};

        while (!q.empty()) {
            x = q.front().first;   // row nnumber
            y = q.front().second;  // column number
            q.pop();

            for (int i = 0; i < 4; i++) {
                int r = x + dir[i];
                int c = y + dir[i+1];
                if (r < 0 || r >= m || c < 0 || c >= n) {
                    // (x, y) is a boundary cell.
                    isClosed = false;
                } else if (grid[r][c] == 0 && !visit[r][c]) {
                    q.push({r, c});
                    visit[r][c] = true;
                }
            }
        }

        return isClosed;
    }
};
