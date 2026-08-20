class Solution {
public:
    int totalNQueens(int n) {
        vector<string> board(n, string(n, '.'));

        int count = 0;

        solve(board, 0, n, count);

        return count;
    }

private:
    void solve(vector<string>& board, int row, int n, int& count) {
        /*
         * Successfully placed one queen
         * in every row.
         */
        if (row == n) {
            ++count;
            return;
        }

        /*
         * Try placing the queen in every column
         * of the current row.
         */
        for (int col = 0; col < n; ++col) {

            if (!isValid(board, row, col, n)) {
                continue;
            }

            // Choose
            board[row][col] = 'Q';

            // Explore next row
            solve(board, row + 1, n, count);

            // Backtrack
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col, int n) {
        /*
         * Check same column above.
         *
         * No need to check current row because
         * we place exactly one queen per row.
         */
        for (int r = 0; r < row; ++r) {
            if (board[r][col] == 'Q') {
                return false;
            }
        }

        /*
         * Check upper-left diagonal.
         *
         * Example:
         *
         * Q
         *   Q
         *     X
         */
        for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {

            if (board[r][c] == 'Q') {
                return false;
            }
        }

        /*
         * Check upper-right diagonal.
         *
         *     Q
         *   Q
         * X
         */
        for (int r = row - 1, c = col + 1; r >= 0 && c < n; --r, ++c) {

            if (board[r][c] == 'Q') {
                return false;
            }
        }

        return true;
    }

public:
    // Backtracking
    //
    // Time: roughly O(n!)
    // Space: O(n)
    int totalNQueens_(int n) {
        vector<bool> columns(n, false);

        // row - col ranges from -(n-1) to +(n-1)
        // Shift by n-1 to make it non-negative.
        vector<bool> diag1(2 * n - 1, false);

        // row + col ranges from 0 to 2n-2.
        vector<bool> diag2(2 * n - 1, false);

        int count = 0;

        solve(0, n, columns, diag1, diag2, count);

        return count;
    }

private:
    void solve(int row, int n, vector<bool>& columns, vector<bool>& diag1, vector<bool>& diag2, int& count ) {
        if (row == n) {
            ++count;
            return;
        }

        for (int col = 0; col < n; ++col) {
            int d1 = row - col + n - 1;
            int d2 = row + col;

            // Column or either diagonal already occupied.
            if (columns[col] || diag1[d1] || diag2[d2]) {
                continue;
            }

            // Choose
            columns[col] = true;
            diag1[d1] = true;
            diag2[d2] = true;

            // Explore
            solve(row + 1, n, columns, diag1, diag2, count);

            // Backtrack
            columns[col] = false;
            diag1[d1] = false;
            diag2[d2] = false;
        }
    }
};
