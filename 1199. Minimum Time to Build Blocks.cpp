class Solution {
public:
    // Greedy + Min Heap
    //
    // Time:  O(n log n)
    // Space: O(n)
    int minBuildTime(vector<int>& blocks, int split) {
        /*
         * Min-heap of task completion times.
         *
         * Initially every block is an independent task.
         */
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int block : blocks) {
            minHeap.push(block);
        }

        /*
         * Repeatedly combine the two smallest tasks.
         *
         * Suppose:
         *
         * x <= y
         *
         * One worker first splits:
         *
         *      cost = split
         *
         * Then the two workers execute x and y
         * simultaneously.
         *
         * Parallel completion time:
         *
         *      max(x, y) = y
         *
         * Therefore the combined abstract task costs:
         *
         *      split + y
         */
        while (minHeap.size() > 1) {
            int x = minHeap.top();
            minHeap.pop();

            int y = minHeap.top();
            minHeap.pop();

            int combinedTime = split + max(x, y);

            // Since x <= y:
            // combinedTime = split + y

            minHeap.push(combinedTime);
        }

        /*
         * The final heap element represents
         * the time needed for the entire build.
         */
        return minHeap.top();
    }

public:
    /*
        States:
        b = 0..n-1
        w = 1..n

        => O(n^2) states

        Each state does O(1) work

        Time:  O(n^2)
        Space: O(n^2)
    */
    int minBuildTime_dp(vector<int>& blocks, int split) {
        // Put larger blocks first.
        sort(blocks.begin(), blocks.end(), greater<int>());

        int n = blocks.size();

        // dp[b][w]:
        // minimum time to finish blocks[b ... n-1]
        // when we currently have w workers.
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        // Initially:
        // block index = 0
        // workers = 1
        return solve(blocks, split, 0, 1, dp);
    }

private:
    int solve(vector<int>& blocks, int split, int b, int w, vector<vector<int>>& dp) {
        int n = blocks.size();

        // No blocks left.
        if (b == n) {
            return 0;
        }

        // No worker available but blocks remain.
        if (w == 0) {
            return INT_MAX;
        }

        /*
         * If we already have at least one worker
         * for every remaining block, then all remaining
         * blocks can be built simultaneously.
         *
         * Since blocks are sorted descending,
         * blocks[b] is the longest remaining block.
         *
         * Therefore total remaining time is just blocks[b].
         */
        if (w >= n - b) {
            return blocks[b];
        }

        if (dp[b][w] != -1) {
            return dp[b][w];
        }

        /*
         * Choice 1: BUILD one block now.
         *
         * One worker takes blocks[b] time.
         *
         * At the same time, the other w-1 workers can
         * continue working on remaining blocks.
         *
         * Therefore the total finishing time is the MAX
         * of:
         *
         *   blocks[b]
         *
         * and
         *
         *   time needed for remaining blocks.
         */
        int remainingTime = solve(blocks, split, b + 1, w - 1, dp);

        int workHere = INT_MAX;

        if (remainingTime != INT_MAX) {
            workHere = max(blocks[b], remainingTime);
        }

        /*
         * Choice 2: SPLIT all current workers.
         *
         * Each worker can split into two workers.
         *
         * So:
         *
         * w -> 2*w
         *
         * This costs 'split' time.
         *
         * No block is completed yet,
         * so b stays unchanged.
         */
        int newWorkers = min(2 * w, n - b);

        int splitHere = split + solve(blocks, split, b, newWorkers, dp);

        return dp[b][w] = min(workHere, splitHere);
    }
};
