class Solution {
private:
    // Converts a 1-based square number into the corresponding
    // (row, col) position in the board.
    //
    // The board is numbered in a zig-zag pattern:
    //
    // Example for n = 6:
    //
    // 36 35 34 33 32 31
    // 25 26 27 28 29 30
    // 24 23 22 21 20 19
    // 13 14 15 16 17 18
    // 12 11 10  9  8  7
    //  1  2  3  4  5  6
    //
    // We first calculate the row and column assuming
    // left-to-right numbering, then reverse the column
    // when that row is numbered right-to-left.
    void getCoordinate(int n, int square, int& row, int& col) {
        int index = square - 1;

        // Convert square number into a row.
        // Rows in the board vector are counted from top to bottom,
        // while square numbers start from the bottom.
        row = n - 1 - index / n;

        // Column before considering the zig-zag direction.
        col = index % n;

        // Depending on the board size and row, the numbering
        // direction changes.
        //
        // If the row needs to be traversed from right to left,
        // mirror the column.
        if ((n % 2 == 1 && row % 2 == 1) ||
            (n % 2 == 0 && row % 2 == 0)) {
            col = n - 1 - col;
        }
    }

public:
    // Time: O(n^2) Space: O(n^2)
    int snakesAndLadders(vector<vector<int>>& board) {
        const int n = board.size();
        const int target = n * n;

        // seen[square] tells us whether this square has already
        // been added to the BFS queue.
        //
        // Marking a square when we PUSH it (rather than when we
        // pop it) prevents the same square from being inserted
        // multiple times.
        vector<bool> seen(target + 1, false);

        queue<int> q;

        // BFS always starts from square 1.
        q.push(1);
        seen[1] = true;

        // Each iteration processes one complete BFS level.
        // Therefore, each level represents one dice roll.
        int moves = 0;

        while (!q.empty()) {
            // Number of positions reachable using exactly
            // 'moves' dice rolls.
            int levelSize = q.size();

            while (levelSize--) {
                int square = q.front();
                q.pop();

                // We have reached the final square.
                if (square == target)
                    return moves;

                // Try every possible dice result: 1 through 6.
                for (int dice = 1; dice <= 6; ++dice) {
                    int nextSquare = square + dice;

                    // We cannot move beyond the final square.
                    if (nextSquare > target)
                        break;

                    int row, col;
                    getCoordinate(n, nextSquare, row, col);

                    // If there is a snake or ladder, we must
                    // immediately move to its destination.
                    //
                    // Otherwise, we simply stay on nextSquare.
                    if (board[row][col] != -1) {
                        nextSquare = board[row][col];
                    }

                    // Visit each square only once.
                    if (!seen[nextSquare]) {
                        seen[nextSquare] = true;
                        q.push(nextSquare);
                    }
                }
            }

            // We have finished processing all positions reachable
            // in the current number of moves.
            ++moves;
        }

        // The final square cannot be reached.
        return -1;
    }
};
