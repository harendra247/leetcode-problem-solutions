class Solution {
public:
    // Backtracking
    //
    // Let:
    // N = number of candidates
    // T = target
    // M = minimum candidate value
    //
    // Maximum recursion depth is about T / M.
    //
    // Time: exponential in the worst case
    // Space: O(T / M) recursion/path space
    // Backtracking
    // N = candidates.size()
    // T = target
    // M = minimum candidate
    //
    // Time:  O(N^(T/M + 1))  // loose exponential bound
    // Space: O(T/M)          // excluding output
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;

        backtrack(candidates, target, 0, current, result);

        return result;
    }

private:
    void backtrack(vector<int>& candidates, int remaining, int start, vector<int>& current, vector<vector<int>>& result) {
        /*
         * Successfully formed the target.
         *
         * Example:
         *
         * target = 7
         * current = [2,2,3]
         *
         * remaining = 0
         */
        if (remaining == 0) {
            result.push_back(current);
            return;
        }

        /*
         * Sum has exceeded target.
         *
         * Since all candidates are positive,
         * adding more numbers can never fix it.
         */
        if (remaining < 0) {
            return;
        }

        /*
         * Try candidates starting from 'start'.
         *
         * This prevents duplicate permutations.
         *
         * For example, we allow:
         *
         * [2,2,3]
         *
         * but avoid separately generating:
         *
         * [2,3,2]
         * [3,2,2]
         */
        for (int i = start; i < candidates.size(); ++i) {

            // Choose candidate.
            current.push_back(candidates[i]);

            /*
             * Recurse with i, NOT i + 1.
             *
             * Why?
             *
             * Because candidates[i] can be reused
             * unlimited times.
             */
            backtrack(candidates, remaining - candidates[i], i, current, result);

            // Undo choice.
            current.pop_back();
        }
    }
};
