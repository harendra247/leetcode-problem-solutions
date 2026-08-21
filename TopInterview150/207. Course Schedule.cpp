class Solution {
public:
    // Kahn's Algorithm / BFS Topological Sort
    //
    // N = number of courses
    // E = number of prerequisite relations
    //
    // Time:  O(N + E)
    // Space: O(N + E)
    bool canFinish(
        int numCourses,
        vector<vector<int>>& prerequisites
    ) {
        /*
         * graph[u] contains all courses that depend on u.
         *
         * prerequisite [a,b] means:
         *
         * b -> a
         *
         * You must complete b before a.
         */
        vector<vector<int>> graph(numCourses);

        /*
         * indegree[i] =
         * number of prerequisites still required
         * before course i can be taken.
         */
        vector<int> indegree(numCourses, 0);

        for (const auto& p : prerequisites) {
            int course = p[0];
            int prerequisite = p[1];

            graph[prerequisite].push_back(course);
            ++indegree[course];
        }

        /*
         * Start with every course having
         * no prerequisites.
         */
        queue<int> q;

        for (int course = 0; course < numCourses; ++course) {
            if (indegree[course] == 0) {
                q.push(course);
            }
        }

        int coursesTaken = 0;

        while (!q.empty()) {
            int course = q.front();
            q.pop();

            ++coursesTaken;

            /*
             * Completing this course removes one prerequisite
             * from every dependent course.
             */
            for (int nextCourse : graph[course]) {
                --indegree[nextCourse];

                /*
                 * All prerequisites completed:
                 * this course can now be taken.
                 */
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }

        /*
         * If we processed every course,
         * no cycle exists.
         *
         * Otherwise some courses are stuck in a cycle.
         */
        return coursesTaken == numCourses;
    }

private:
    bool dfs(
        int node,
        vector<vector<int>>& graph,
        vector<int>& state
    ) {
        // Currently in recursion path -> cycle.
        if (state[node] == 1) {
            return false;
        }

        // Already checked successfully.
        if (state[node] == 2) {
            return true;
        }

        // Mark as currently visiting.
        state[node] = 1;

        for (int next : graph[node]) {
            if (!dfs(next, graph, state)) {
                return false;
            }
        }

        // Fully processed.
        state[node] = 2;

        return true;
    }

public:
    // Time: O(N + E)
    // Space: O(N + E)
    bool canFinish_(
        int numCourses,
        vector<vector<int>>& prerequisites
    ) {
        vector<vector<int>> graph(numCourses);

        for (auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
        }

        vector<int> state(numCourses, 0);

        for (int i = 0; i < numCourses; ++i) {
            if (!dfs(i, graph, state)) {
                return false;
            }
        }

        return true;
    }
};
