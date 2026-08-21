class Solution {
public:
    // Kahn's Algorithm / Topological Sort
    //
    // N = number of courses
    // E = number of prerequisite relationships
    //
    // Time:  O(N + E)
    // Space: O(N + E)
    vector<int> findOrder(
        int numCourses,
        vector<vector<int>>& prerequisites
    ) {
        /*
         * prerequisite [a, b] means:
         *
         * b -> a
         *
         * To take course a, course b must be completed first.
         */
        vector<vector<int>> graph(numCourses);

        /*
         * indegree[i] =
         * number of prerequisites course i still has.
         */
        vector<int> indegree(numCourses, 0);

        for (const auto& p : prerequisites) {
            int course = p[0];
            int prerequisite = p[1];

            graph[prerequisite].push_back(course);
            ++indegree[course];
        }

        /*
         * Courses with indegree 0 can be taken immediately.
         */
        queue<int> q;

        for (int course = 0; course < numCourses; ++course) {
            if (indegree[course] == 0) {
                q.push(course);
            }
        }

        vector<int> order;

        while (!q.empty()) {
            int course = q.front();
            q.pop();

            // This course can now be taken.
            order.push_back(course);

            /*
             * Completing this course removes one prerequisite
             * from every course that depends on it.
             */
            for (int nextCourse : graph[course]) {
                --indegree[nextCourse];

                /*
                 * If all prerequisites are now completed,
                 * this course becomes available.
                 */
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }

        /*
         * If we processed all courses,
         * we found a valid topological ordering.
         *
         * Otherwise, a cycle exists.
         */
        if (order.size() == numCourses) {
            return order;
        }

        return {};
    }
};
