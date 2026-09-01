class Solution {
public:
    /*
     * State of BFS:
     *
     *     (row, col, remainingEnergy, collectedLitterMask)
     *
     * Why do we need all four?
     *
     * - row, col:
     *       Current position.
     *
     * - remainingEnergy:
     *       How many steps we can still take before needing
     *       to reach a recharge cell 'R'.
     *
     * - collectedLitterMask:
     *       Which litter pieces have already been collected.
     *
     * BFS guarantees that the first time we collect all litter,
     * we have used the minimum number of moves.
     *
     * Time:
     *     O(m * n * energy * 2^L)
     *
     * Space:
     *     O(m * n * energy * 2^L)
     *
     * where:
     *     m = number of rows
     *     n = number of columns
     *     L = number of litter cells
     */

    int minMoves_1(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        /*
         * litterId[r][c] tells us which bit represents the
         * litter at (r, c).
         *
         * Example:
         *
         *     L at (1,2) -> ID 0
         *     L at (2,4) -> ID 1
         *     L at (3,1) -> ID 2
         *
         * Then:
         *
         *     mask = 101
         *
         * means litter 0 and litter 2 have been collected.
         *
         * -1 means this cell is not litter.
         */
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        int startRow = -1;
        int startCol = -1;
        int litterCount = 0;

        /*
         * Find:
         *   1. Starting position S
         *   2. Every litter position L
         *
         * Assign every litter a unique bit.
         */
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {

                if (classroom[r][c] == 'S') {
                    startRow = r;
                    startCol = c;
                } else if (classroom[r][c] == 'L') {
                    litterId[r][c] = litterCount++;
                }
            }
        }

        /*
         * No litter means we are already done.
         */
        if (litterCount == 0) {
            return 0;
        }

        /*
         * If there are L pieces of litter:
         *
         *     1 << L
         *
         * gives the number of possible masks.
         *
         * Example:
         *
         * L = 3
         *
         * masks:
         *
         * 000
         * 001
         * 010
         * 011
         * 100
         * 101
         * 110
         * 111
         *
         * The target mask is all 1s.
         */
        int targetMask = (1 << litterCount) - 1;

        /*
         * Directions:
         *
         *     0 -> up
         *     1 -> right
         *     2 -> down
         *     3 -> left
         */
        int directions[5] = {-1, 0, 1, 0, -1};

        /*
         * BFS queue.
         *
         * Each state contains:
         *
         *     row
         *     col
         *     remaining energy
         *     collected litter mask
         *     number of moves
         */
        queue<tuple<int, int, int, int, int>> q;

        /*
         * Initial state:
         *
         *     position = S
         *     energy   = maximum energy
         *     mask     = 0 (nothing collected)
         *     steps    = 0
         */
        q.push({startRow, startCol, energy, 0, 0});

        /*
         * visited[r][c][e][mask]
         *
         * means:
         *
         * "We have already visited cell (r,c) with exactly
         *  e energy remaining and exactly this litter mask."
         *
         * We MUST include energy and mask in the visited state.
         *
         * Reaching the same cell with different energy or different
         * collected litter is a different state.
         */
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(
                        1 << litterCount,
                        false
                    )
                )
            )
        );

        visited[startRow][startCol][energy][0] = true;

        while (!q.empty()) {

            auto [r, c, currentEnergy, mask, steps] = q.front();
            q.pop();

            /*
             * Try all four possible directions.
             */
            for (int d = 0; d < 4; ++d) {

                int nr = r + directions[d];
                int nc = c + directions[d + 1];

                /*
                 * Ignore:
                 *
                 *   - cells outside the classroom
                 *   - blocked cells X
                 */
                if (nr < 0 || nr >= m ||
                    nc < 0 || nc >= n ||
                    classroom[nr][nc] == 'X') {
                    continue;
                }

                /*
                 * Every move consumes one unit of energy.
                 */
                int nextEnergy = currentEnergy - 1;

                /*
                 * Initially, the collected litter mask does not
                 * change.
                 */
                int nextMask = mask;

                /*
                 * If we move onto litter, collect it.
                 *
                 * Example:
                 *
                 *     litterId[nr][nc] = 2
                 *
                 * Then:
                 *
                 *     1 << 2 = 100
                 *
                 * ORing it with mask marks litter #2 as collected.
                 */
                if (classroom[nr][nc] == 'L') {
                    nextMask |= (1 << litterId[nr][nc]);
                }

                /*
                 * If we have collected ALL litter, this is the
                 * shortest possible answer.
                 *
                 * BFS explores states by increasing number of steps.
                 */
                if (nextMask == targetMask) {
                    return steps + 1;
                }

                /*
                 * Recharge cell.
                 *
                 * Moving onto R immediately restores energy
                 * back to the maximum.
                 */
                if (classroom[nr][nc] == 'R') {
                    nextEnergy = energy;
                }

                /*
                 * If energy becomes zero and this is NOT a recharge
                 * cell, we cannot continue from this state.
                 *
                 * We allow zero energy on R because R immediately
                 * restores it.
                 */
                if (nextEnergy == 0 && classroom[nr][nc] != 'R') {
                    continue;
                }

                /*
                 * Have we already visited this exact state?
                 *
                 * Same position + same energy + same litter mask
                 * means there is no reason to process it again.
                 */
                if (visited[nr][nc][nextEnergy][nextMask]) {
                    continue;
                }

                visited[nr][nc][nextEnergy][nextMask] = true;

                q.push({nr, nc, nextEnergy, nextMask, steps + 1});
            }
        }

        /*
         * BFS finished without collecting all litter.
         */
        return -1;
    }

private:
    int dir[5] = {-1, 0, 1, 0, -1};

public:
    /*
     * BFS State:
     *
     *     (row, col, energy, mask)
     *
     * mask tells us which litter pieces have been collected.
     *
     * Instead of:
     *
     *     visited[row][col][energy][mask]
     *
     * we store:
     *
     *     maxEnergy[row][col][mask]
     *
     * which represents the maximum energy with which we have
     * already reached this (row, col, mask) state.
     *
     * If we reach the same state later with LESS or EQUAL energy,
     * that state can be ignored because it can never do better.
     *
     * Time:
     *     O(m * n * 2^L * 4)
     *     = O(m * n * 2^L)
     *
     * Space:
     *     O(m * n * 2^L)
     *
     * where:
     *     m = number of rows
     *     n = number of columns
     *     L = number of litter cells
     */

    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        int startX = -1;
        int startY = -1;

        /*
         * litterId[r][c] stores the bit number corresponding
         * to the litter at (r, c).
         *
         * -1 means this cell is not litter.
         */
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        int litterCount = 0;

        /*
         * Find the starting position and assign a unique ID
         * to every litter cell.
         */
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {

                if (classroom[r][c] == 'S') {
                    startX = r;
                    startY = c;
                } else if (classroom[r][c] == 'L') {

                    /*
                     * Litter #0 -> bit 0
                     * Litter #1 -> bit 1
                     * Litter #2 -> bit 2
                     * ...
                     */
                    litterId[r][c] = litterCount++;
                }
            }
        }

        /*
         * No litter means no movement is required.
         */
        if (litterCount == 0) {
            return 0;
        }

        /*
         * If there are L litter pieces:
         *
         *     targetMask = 111...111
         *
         * Example:
         *
         * L = 3
         *
         *     1 << 3 = 1000
         *     1000 - 1 = 0111
         */
        int targetMask = (1 << litterCount) - 1;

        /*
         * maxEnergy[x][y][mask] =
         *
         * maximum energy with which we have already reached
         * (x, y) after collecting exactly the litter represented
         * by 'mask'.
         *
         * -1 means this state has never been reached.
         */
        vector<vector<vector<int>>> maxEnergy(
            m,
            vector<vector<int>>(
                n,
                vector<int>(1 << litterCount, -1)
            )
        );

        /*
         * Queue contains:
         *
         *     row
         *     col
         *     remaining energy
         *     collected litter mask
         */
        queue<tuple<int, int, int, int>> q;

        q.push({startX, startY, energy, 0});

        /*
         * Initially:
         *
         * position = S
         * energy   = maximum energy
         * mask     = 0 (nothing collected)
         */
        maxEnergy[startX][startY][0] = energy;

        int steps = 0;

        while (!q.empty()) {

            /*
             * Process one complete BFS level.
             *
             * Every state in this level requires exactly 'steps'
             * moves from the starting position.
             */
            int levelSize = q.size();

            while (levelSize--) {

                auto [x, y, currentEnergy, mask] = q.front();
                q.pop();

                /*
                 * We may have collected all litter.
                 *
                 * Because BFS processes states in increasing
                 * number of moves, this is the minimum answer.
                 */
                if (mask == targetMask) {
                    return steps;
                }

                /*
                 * No energy means we cannot make another move.
                 *
                 * Note that a state with zero energy can exist
                 * on an R cell because reaching R immediately
                 * restores energy before the state is pushed.
                 */
                if (currentEnergy == 0) {
                    continue;
                }

                /*
                 * Try all four directions.
                 */
                for (int d = 0; d < 4; ++d) {

                    int nx = x + dir[d];
                    int ny = y + dir[d + 1];

                    /*
                     * Ignore cells outside the classroom
                     * and blocked cells.
                     */
                    if (nx < 0 || nx >= m ||
                        ny < 0 || ny >= n ||
                        classroom[nx][ny] == 'X') {
                        continue;
                    }

                    /*
                     * Every movement consumes one energy.
                     */
                    int nextEnergy = currentEnergy - 1;

                    /*
                     * Initially, assume we haven't collected
                     * any new litter.
                     */
                    int nextMask = mask;

                    /*
                     * Recharge cell.
                     *
                     * After moving onto R, energy becomes full again.
                     */
                    if (classroom[nx][ny] == 'R') {
                        nextEnergy = energy;
                    }

                    /*
                     * Litter cell.
                     *
                     * Turn ON the bit corresponding to this litter.
                     */
                    else if (litterId[nx][ny] != -1) {

                        nextMask |= (1 << litterId[nx][ny]);
                    }

                    /*
                     * ------------------------------------------------
                     * Dominance / pruning:
                     *
                     * Suppose we have already reached:
                     *
                     *     (x, y, mask) with energy = 7
                     *
                     * and now we reach:
                     *
                     *     (x, y, mask) with energy = 5
                     *
                     * The second state is useless.
                     *
                     * From exactly the same position with exactly
                     * the same litter collected, having 7 energy
                     * gives us everything that having 5 energy gives,
                     * and potentially more.
                     *
                     * Therefore we only keep the state if it has
                     * STRICTLY MORE energy than what we've seen.
                     * ------------------------------------------------
                     */
                    if (maxEnergy[nx][ny][nextMask] >= nextEnergy) {
                        continue;
                    }

                    maxEnergy[nx][ny][nextMask] = nextEnergy;

                    q.push({nx, ny, nextEnergy, nextMask});
                }
            }

            /*
             * Move to the next BFS level.
             */
            ++steps;
        }

        return -1;
    }
};
