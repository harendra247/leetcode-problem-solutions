class Solution {
private:
    bool isvalid(int i, int j, int m, int n) {
        if (i < 0 || i >= m || j < 0 || j >=n) {
            return false;
        }
        return true;
    }
public:
    
    // Time: O(mn) Space: O(1)
    void gameOfLife(vector<vector<int>>& board) {
        
        vector<pair<int, int>> neib = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
        int livecell = 0;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                livecell = 0;
                for (int k = 0; k < neib.size(); k++) {
                    if (isvalid(i + neib[k].first, j + neib[k].second, board.size(), board[0].size()) && abs(board[i + neib[k].first][j + neib[k].second]) == 1) {
                        livecell++;
                    }
                }
                
                if (board[i][j] == 0 && livecell == 3) {
                    board[i][j] = 2;
                } else if (board[i][j] == 1 && (livecell < 2 || livecell > 3)) {
                    board[i][j] = -1;
                }
            }
        }
        
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] > 0) {
                    board[i][j] = 1;
                } else {
                    board[i][j] = 0;
                }
            }
        }
        
    }
};
