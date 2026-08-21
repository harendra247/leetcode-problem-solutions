class Solution {
public:
    void DFS(vector<vector<char>>& board, int i, int j, int m, int n) {
        if (i<0 or j<0 or i>=m or j>=n or board[i][j] != 'O') return;
        board[i][j] = '#';
        DFS(board, i-1, j, m, n);
        DFS(board, i+1, j, m, n);
        DFS(board, i, j-1, m, n);
        DFS(board, i, j+1, m, n);
    }
    
    // Time: O(m*n) Space: O(m*n)
    void solve_dfs(vector<vector<char>>& board) {
      
        //We will use boundary DFS to solve this problem

        // Let's analyze when an 'O' cannot be flipped,
        // if it has atleast one 'O' in it's adjacent, AND ultimately this chain of adjacent 'O's is connected to some 'O' which lies on boundary of board

        //consider these two cases for clarity :
        /*
        O's won't be flipped          O's will be flipped
        [X O X X X]                   [X X X X X]     
        [X O O O X]                   [X O O O X]
        [X O X X X]                   [X O X X X] 
        [X X X X X]                   [X X X X X]

        So we can conclude if a chain of adjacent O's is connected some O on boundary then they cannot be flipped

        */

        //Steps to Solve :
        //1. Move over the boundary of board, and find O's 
        //2. Every time we find an O, perform DFS from it's position
        //3. In DFS convert all 'O' to '#'      (why?? so that we can differentiate which 'O' can be flipped and which cannot be)   
        //4. After all DFSs have been performed, board contains three elements,#,O and X
        //5. 'O' are left over elements which are not connected to any boundary O, so flip them to 'X'
        //6. '#' are elements which cannot be flipped to 'X', so flip them back to 'O'
        //7. finally, Upvote the solution\U0001f60a   


        int m = board.size();

        if(m == 0) return;  

        int n = board[0].size();

        //Moving over first and last column   
        for (int i=0; i<m; i++) {
            if (board[i][0] == 'O')
                DFS(board, i, 0, m, n);
            if (board[i][n-1] == 'O')
                DFS(board, i, n-1, m, n);
        }


        //Moving over first and last row   
        for (int j=0; j<n; j++) {
            if(board[0][j] == 'O')
                DFS(board, 0, j, m, n);
            if(board[m-1][j] == 'O')
                DFS(board, m-1, j, m, n);
        }

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == '#')
                    board[i][j] = 'O';
            }
    }
    
 
  int ROWS = 0;
  int COLS = 0;

    // Time: O(m*n) Space: O(m*n)
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0) {
            return;
        }
        ROWS = board.size();
        COLS = board[0].size();

        vector<pair<int, int>> borders;
        // Step 1). construct the list of border cells
        for (int r = 0; r < ROWS; ++r) {
            borders.push_back({r, 0});
            borders.push_back({r, COLS - 1});
        }
        for (int c = 0; c < COLS; ++c) {
            borders.push_back({0, c});
            borders.push_back({ROWS - 1, c});
        }

        // Step 2). mark the escaped cells
        for (auto pair : borders) {
            BFS(board, pair.first, pair.second);
        }

        // Step 3). flip the cells to their correct final states
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (board[r][c] == 'O')
                    board[r][c] = 'X';
                if (board[r][c] == 'E')
                    board[r][c] = 'O';
            }
        }
    }

    void BFS(vector<vector<char>> &board, int r, int c) {
        queue<pair<int, int>> q;
        q.push({r, c});

        while (!q.empty()) {
            auto pair = q.front();
            q.pop();
            int row = pair.first, col = pair.second;
            if (board[row][col] != 'O')
                continue;

            board[row][col] = 'E';
            if (col < COLS - 1)
                q.push({row, col + 1});
            if (row < ROWS - 1)
                q.push({row + 1, col});
            if (col > 0)
                q.push({row, col - 1});
            if (row > 0)
                q.push({row - 1, col});
        }  
    }
};
