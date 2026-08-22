class Solution {
private:
    int minLen;
    int maxLen;

    int dfs(vector<bool>& visited, vector<vector<int>>& skip, int current, int length) {
        // Pattern is too long.
        if (length > maxLen) {
            return 0;
        }

        /*
         * We are currently using 'current',
         * so mark it visited.
         */
        visited[current] = true;

        /*
         * If current length is already within [m, n],
         * then the current pattern itself is valid.
         */
        int count = (length >= minLen ? 1 : 0);

        /*
         * Try every possible next key.
         */
        for (int next = 1; next <= 9; ++next) {

            // Cannot reuse a key.
            if (visited[next]) {
                continue;
            }

            /*
             * skip[current][next] == 0:
             *     no intermediate key is required
             *
             * OR
             *
             * visited[skip[current][next]]:
             *     required intermediate key
             *     has already been visited.
             */
            int middle = skip[current][next];

            if (middle == 0 || visited[middle]) {
                count += dfs(visited, skip, next, length + 1);
            }
        }

        // Backtrack.
        visited[current] = false;

        return count;
    }

public:
    // Backtracking
    // Time: bounded by permutations of 9 keys, effectively constant
    // Space: O(9) recursion/visited, effectively O(1)
    int numberOfPatterns(int m, int n) {
        minLen = m;
        maxLen = n;

        // skip[a][b] tells you whether moving from a to b requires passing through another key.
        vector<vector<int>> skip(10, vector<int>(10, 0));

        // Moves requiring an intermediate key.
        skip[1][3] = skip[3][1] = 2;
        skip[1][7] = skip[7][1] = 4;
        skip[3][9] = skip[9][3] = 6;
        skip[7][9] = skip[9][7] = 8;

        skip[1][9] = skip[9][1] = 5;
        skip[2][8] = skip[8][2] = 5;
        skip[3][7] = skip[7][3] = 5;
        skip[4][6] = skip[6][4] = 5;

        vector<bool> visited(10, false);

        int result = 0;

        /*
         * Symmetry:
         *
         * Corners:
         * 1,3,7,9 are equivalent.
         *
         * Edges:
         * 2,4,6,8 are equivalent.
         *
         * Center:
         * 5 is unique.
         */
        result += dfs(visited, skip, 1, 1) * 4;
        result += dfs(visited, skip, 2, 1) * 4;
        result += dfs(visited, skip, 5, 1);

        return result;
    }


private:
    int jump[10][10] = {};
    int dp[10][1 << 9];

    int dfs(int current, int length, int m, int n, int visitedMask) {
        if (length > n) {
            return 0;
        }

        /*
         * State at function entry:
         *
         * current is NOT yet present in visitedMask.
         */
        int & ans = dp[current][visitedMask];
        if (ans != -1) {
            return ans;
        }

        int originalMask = visitedMask;

        // Mark current key visited.
        visitedMask |= 1 << (current - 1);

        /*
         * Current pattern itself counts if
         * its length is in [m, n].
         */
        int count = (length >= m ? 1 : 0);

        for (int next = 1; next <= 9; ++next) {
            int nextBit = 1 << (next - 1);

            // Already used.
            if (visitedMask & nextBit) {
                continue;
            }

            int middle = jump[current][next];

            /*
             * Move valid if:
             *
             * no intermediate key required
             *
             * OR
             *
             * required intermediate key
             * has already been visited.
             */
            if (middle == 0 || (visitedMask & (1 << (middle - 1)))) {

                count += dfs(next, length + 1, m, n, visitedMask);
            }
        }

        return ans = count;
    }

public:
    // States: 9 * 2^9
    // For each state, try at most 9 next keys.
    //
    // Time:  O(9 * 2^9 * 9) = O(9^2 * 2^9)
    // Space: O(9 * 2^9)
    //
    // Since Android keypad is fixed at 9 keys,
    // this is effectively O(1).
    int numberOfPatterns_(int m, int n) {
        memset(dp, -1, sizeof(dp));

        jump[1][3] = jump[3][1] = 2;
        jump[1][7] = jump[7][1] = 4;
        jump[3][9] = jump[9][3] = 6;
        jump[7][9] = jump[9][7] = 8;

        jump[1][9] = jump[9][1] = 5;
        jump[2][8] = jump[8][2] = 5;
        jump[3][7] = jump[7][3] = 5;
        jump[4][6] = jump[6][4] = 5;

        int result = 0;

        // Corners are symmetric.
        result += dfs(1, 1, m, n, 0) * 4;

        // Edge-middle keys are symmetric.
        result += dfs(2, 1, m, n, 0) * 4;

        // Center is unique.
        result += dfs(5, 1, m, n, 0);

        return result;
    }
};
