class Solution {
public:
    
    // R = number of rows
    // C = number of columns
    // L = word.length()
    //
    // Time:  O(R * C * 3^L) roughly
    // Space: O(L) recursion stack
    bool exist(vector<vector<char>>& board, string word) {
       if (word.empty()) {
            return true;
        }

        if (board.empty() || board[0].empty()) {
            return false;
        }

        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col) {
                if (dfs(board, word, row, col, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    /*
     * dfs(..., index)
     *
     * means:
     *
     * Can we match word[index ... end]
     * starting from board[row][col]?
     */
    bool dfs(
        vector<vector<char>>& board,
        const string& word,
        int row,
        int col,
        int index
    ) {
        /*
         * Successfully matched every character.
         */
        if (index == word.size()) {
            return true;
        }

        int rows = board.size();
        int cols = board[0].size();

        if (
            row < 0 || row >= rows ||
            col < 0 || col >= cols ||
            board[row][col] != word[index]
        ) {
            return false;
        }

        /*
         * Current cell matches.
         *
         * Temporarily mark it as visited so we
         * cannot reuse it in the SAME word path.
         */
        char original = board[row][col];
        board[row][col] = '#';

        /*
         * Try matching the next character
         * in all four directions.
         */
        bool found =
            dfs(board, word, row - 1, col, index + 1) ||
            dfs(board, word, row + 1, col, index + 1) ||
            dfs(board, word, row, col - 1, index + 1) ||
            dfs(board, word, row, col + 1, index + 1);

        /*
         * BACKTRACK:
         *
         * Restore the cell so another DFS path
         * can use it later.
         */
        board[row][col] = original;

        return found;
    }
};
