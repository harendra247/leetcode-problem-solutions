class Solution {
public:

    // BFS Time: O(m*n) Space: O(min(m,n))
    int numIslands_bfs(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0;
        int islands = 0, offsets[] = {0, 1, 0, -1, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    grid[i][j] = '0';
                    queue<pair<int, int>> todo;
                    todo.push({i, j});
                    while (!todo.empty()) {
                        pair<int, int> p = todo.front();
                        todo.pop();
                        for (int k = 0; k < 4; k++) {
                            int r = p.first + offsets[k];
                            int c = p.second + offsets[k + 1];
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1') {
                                grid[r][c] = '0';
                                todo.push({r, c});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
    
    // DFS Time: O(m*n) Space: O(m)
    int numIslands_dfs(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    eraseIslands(grid, i, j);
                }
            }
        }
        return islands;
    }
private:
    void eraseIslands(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i == m || j < 0 || j == n || grid[i][j] == '0') {
            return;
        }
        grid[i][j] = '0';
        eraseIslands(grid, i - 1, j);
        eraseIslands(grid, i + 1, j);
        eraseIslands(grid, i, j - 1);
        eraseIslands(grid, i, j + 1);
    }
    
public:  
    
    // Union Find Time: O(m*n) Space: O(m*n)
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0)
            return 0;
        
        int n = grid.size(), m = grid[0].size();
        vector<int> parent(m*n, -1);
        vector<int> rank(m*n, 1);
        // Why only top and left?
        // its top and left are the only already-processed neighbors.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    parent[i*m+j] = i*m+j; // note, that `parent` was filled witn -1 values
                    if (i > 0 && grid[i-1][j] == '1')
                        union_(i*m+j, (i-1)*m+j, parent, rank); // union current+top
                    if (j > 0 && grid[i][j-1] == '1')
                        union_(i*m+j, i*m+(j-1), parent, rank); // union current+left
                }
            }
        }
        
        unordered_set<int> set;
        for (int k = 0; k < parent.size(); k++) {
            if (parent[k] != -1)
                set.insert(find(k, parent));
        }
        return set.size();
    }
    
    int find(int x, vector<int>& parent){
        if (parent[x] == x)
            return x;
        parent[x] = find(parent[x], parent);
        return parent[x];
    }    
    
    void union_(int x, int y, vector<int>& parent, vector<int>& rank){
        int px = find(x, parent);
        int py = find(y, parent);

        if (px != py) {
            if (rank[px] > rank[py])
                parent[py] = px;
            else if (rank[px] < rank[py])
                parent[px] = py;
            else {
                parent[py] = px; 
                rank[px] += 1;
            }
        }
    }
};
