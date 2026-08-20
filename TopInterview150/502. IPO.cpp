class Solution {
public:
    // n = number of projects
    //
    // Sorting: O(n log n)
    // Each project enters/leaves heap at most once: O(n log n)
    //
    // Time:  O(n log n + k log n)
    // Space: O(n)
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();

        /*
         * Store:
         *
         * {requiredCapital, profit}
         */
        vector<pair<int, int>> projects;

        for (int i = 0; i < n; ++i) {
            projects.push_back({capital[i], profits[i]});
        }

        // Process projects in increasing capital requirement.
        sort(projects.begin(), projects.end());

        /*
         * Max-heap of PROFITS for all currently
         * affordable projects.
         */
        priority_queue<int> available;

        int projectIndex = 0;

        // We can complete at most k projects.
        while (k-- > 0) {

            /*
             * Add every project that our current
             * capital allows us to start.
             */
            while (projectIndex < n && projects[projectIndex].first <= w) {
                available.push(projects[projectIndex].second);

                ++projectIndex;
            }

            /*
             * No affordable project remains.
             *
             * Capital cannot increase anymore,
             * so we're done early.
             */
            if (available.empty()) {
                break;
            }

            /*
             * Greedy:
             *
             * Choose the most profitable project
             * among all currently affordable ones.
             */
            w += available.top();
            available.pop();
        }

        return w;
    }
};
