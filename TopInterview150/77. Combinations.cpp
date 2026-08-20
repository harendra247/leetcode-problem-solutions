class Solution {
private:
    void backtrack(int start, int n, int k, vector<int>& current, vector<vector<int>>& result) {
        // We selected exactly k numbers.
        if (current.size() == k) {
            result.push_back(current);
            return;
        }

        /*
         * Try every possible next number.
         *
         * start ensures combinations stay increasing,
         * so we avoid duplicates like:
         *
         * [1,2] and [2,1]
         */
        for (int num = start; num <= n; ++num) {
            // Choose
            current.push_back(num);

            // Explore
            backtrack(num + 1, n, k, current, result);

            // Undo choice
            current.pop_back();
        }
    }

public:
    // Time: O(C(n,k) * k)
    // Space: O(k) recursion/path space
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;

        backtrack(1, n, k, current, result);

        return result;
    }
    
public:
    // Iterative backtracking
    // Time: O(C(n, k) * k)
    // Space: O(k) excluding output
    vector<vector<int>> combine_1(int n, int k) {
        vector<vector<int>> result;

        /*
         * p holds the current combination.
         *
         * Example for k = 3:
         *
         * p = [1, 2, 4]
         */
        vector<int> p(k, 0);

        /*
         * i tells us which position in p
         * we are currently trying to fill.
         */
        int i = 0;

        while (i >= 0) {

            /*
             * Try the next possible value
             * at position i.
             */
            p[i]++;

            /*
             * If p[i] becomes greater than n,
             * this position has no more choices.
             *
             * Backtrack to the previous position.
             */
            if (p[i] > n) {
                --i;
            }

            /*
             * If we successfully filled the last
             * position, we have a complete combination.
             */
            else if (i == k - 1) {
                result.push_back(p);
            }

            else {
                /*
                 * Move forward to fill the next position.
                 *
                 * We want strictly increasing values:
                 *
                 * p[i + 1] > p[i]
                 *
                 * Since the loop begins by doing p[i]++,
                 * initialize the next position to the
                 * current value.
                 *
                 * Then on the next iteration:
                 *
                 * p[i]++
                 *
                 * makes it current + 1.
                 */
                ++i;

                p[i] = p[i - 1];
            }
        }

        return result;
    }
};
