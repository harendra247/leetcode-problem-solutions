class Solution {
public:
    // Let E = number of equations
    // Q = number of queries
    //
    // Building graph: O(E)
    // Each BFS query: O(V + E)
    //
    // Total: O(E + Q * (V + E))
    // Space: O(V + E)
    vector<double> calcEquation_bfs(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries
    ) {
        /*
         * graph[a] contains:
         *
         * {neighbor, multiplication factor}
         *
         * Example:
         *
         * a / b = 2
         *
         * graph[a] -> {b, 2}
         * graph[b] -> {a, 0.5}
         */
        unordered_map<
            string,
            vector<pair<string, double>>
        > graph;

        // Build weighted graph.
        for (int i = 0; i < equations.size(); ++i) {
            string a = equations[i][0];
            string b = equations[i][1];
            double value = values[i];

            graph[a].push_back({b, value});
            graph[b].push_back({a, 1.0 / value});
        }

        vector<double> answer;

        // Process every query independently.
        for (const auto& query : queries) {
            string source = query[0];
            string target = query[1];

            /*
             * If either variable does not exist,
             * query cannot be evaluated.
             */
            if (!graph.count(source) || !graph.count(target)) {

                answer.push_back(-1.0);
                continue;
            }

            /*
             * x / x = 1,
             * provided x exists in the graph.
             */
            if (source == target) {
                answer.push_back(1.0);
                continue;
            }

            /*
             * Queue stores:
             *
             * {currentVariable, accumulatedRatio}
             *
             * accumulatedRatio means:
             *
             * source / currentVariable
             */
            queue<pair<string, double>> q;

            unordered_set<string> visited;

            q.push({source, 1.0});
            visited.insert(source);

            bool found = false;

            while (!q.empty()) {
                auto [current, ratio] = q.front();
                q.pop();

                // Reached target.
                if (current == target) {
                    answer.push_back(ratio);
                    found = true;
                    break;
                }

                /*
                 * Explore neighbors.
                 *
                 * If:
                 *
                 * source / current = ratio
                 *
                 * and:
                 *
                 * current / next = edgeWeight
                 *
                 * then:
                 *
                 * source / next
                 * =
                 * ratio * edgeWeight
                 */
                for (auto [next, edgeWeight] : graph[current]) {

                    if (visited.count(next)) {
                        continue;
                    }

                    visited.insert(next);

                    q.push({next, ratio * edgeWeight});
                }
            }

            if (!found) {
                answer.push_back(-1.0);
            }
        }

        return answer;
    }

public:
    // Let:
    // E = number of equations
    // Q = number of queries
    // V = number of distinct variables
    //
    // Build graph: O(E)
    // Each DFS query: O(V + E)
    //
    // Total: O(E + Q * (V + E))
    // Space: O(V + E)
    vector<double> calcEquation(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries
    ) {
        /*
         * graph[a][b] = value of a / b
         *
         * Example:
         *
         * a / b = 2
         *
         * graph[a][b] = 2
         * graph[b][a] = 0.5
         */
        unordered_map<
            string,
            unordered_map<string, double>
        > graph;

        for (int i = 0; i < values.size(); ++i) {
            string a = equations[i][0];
            string b = equations[i][1];

            graph[a][b] = values[i];
            graph[b][a] = 1.0 / values[i];
        }

        vector<double> result;

        for (const auto& query : queries) {
            string source = query[0];
            string target = query[1];

            /*
             * If either variable doesn't exist,
             * answer is immediately -1.
             */
            if (!graph.count(source) || !graph.count(target)) {

                result.push_back(-1.0);
                continue;
            }

            /*
             * x / x = 1, if x exists.
             */
            if (source == target) {
                result.push_back(1.0);
                continue;
            }

            unordered_set<string> visited;

            /*
             * Mark source visited before DFS
             * to avoid cycling back to it.
             */
            visited.insert(source);

            double value = dfs(source, target, graph, visited);

            result.push_back(value == -1.0 ? -1.0 : value);
        }

        return result;
    }

private:
    double dfs(
        const string& current,
        const string& target,
        unordered_map<
            string,
            unordered_map<string, double>
        >& graph,
        unordered_set<string>& visited
    ) {
        /*
         * If target is directly reachable:
         *
         * current / target is already known.
         */
        if (graph[current].count(target)) {
            return graph[current][target];
        }

        /*
         * Try every neighbor.
         */
        for (auto& [next, weight] : graph[current]) {

            if (visited.count(next)) {
                continue;
            }

            visited.insert(next);

            /*
             * Suppose:
             *
             * current / next = weight
             *
             * and recursively:
             *
             * next / target = subResult
             *
             * Then:
             *
             * current / target
             * =
             * weight * subResult
             */
            double subResult = dfs(next, target, graph, visited);

            if (subResult != -1.0) {
                return weight * subResult;
            }
        }

        // No path found.
        return -1.0;
    }
    
private:
    struct Node {
        /*
         * parent:
         * representative relationship for Union-Find.
         */
        Node* parent;

        /*
         * value:
         * ratio of this variable relative to the
         * representative/component scale.
         *
         * If two variables x and y have the same root:
         *
         * x / y = value[x] / value[y]
         */
        double value = 0.0;

        Node() {
            parent = this;
        }
    };

    /*
     * Find representative of node.
     *
     * Path compression makes future finds faster.
     */
    Node* findParent(Node* node) {
        if (node->parent == node) {
            return node;
        }

        node->parent = findParent(node->parent);

        return node->parent;
    }

    /*
     * Merge the component containing node1
     * with the component containing node2.
     *
     * Equation tells us:
     *
     * node1 / node2 = num
     */
    void unionNodes(
        Node* node1,
        Node* node2,
        double num,
        unordered_map<string, Node*>& nodes
    ) {
        Node* parent1 = findParent(node1);
        Node* parent2 = findParent(node2);

        /*
         * We want to attach parent1 under parent2.
         *
         * Before:
         *
         * node1 value = V1
         * node2 value = V2
         *
         * and:
         *
         * node1 / node2 = num
         *
         * We need to rescale every value in parent1's
         * component so that both components use the
         * same reference system.
         *
         * Required scale factor:
         *
         * ratio = V2 * num / V1
         */
        double ratio = node2->value * num / node1->value;

        /*
         * Every node in parent1's component must
         * now be expressed relative to parent2's scale.
         */
        for (auto& [name, node] : nodes) {
            if (findParent(node) == parent1) {
                node->value *= ratio;
            }
        }

        // Merge the two sets.
        parent1->parent = parent2;
    }

public:
    // N = equations, M = queries, V = unique variables
    // Time: O(N * V * α(V) + M * α(V)) ≈ O(N^2 + M)
    // Space: O(V) ≈ O(N)
    vector<double> calcEquation_uf(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries
    ) {
        /*
         * variable name -> DSU node
         */
        unordered_map<string, Node*> nodes;

        vector<double> result;

        /*
         * Process every equation:
         *
         * s1 / s2 = values[i]
         */
        for (int i = 0; i < equations.size(); ++i) {
            string s1 = equations[i][0];
            string s2 = equations[i][1];
            double ratio = values[i];

            /*
             * CASE 1:
             * Neither variable exists yet.
             *
             * Example:
             *
             * a / b = 2
             *
             * Let:
             *
             * b.value = 1
             * a.value = 2
             *
             * Then:
             *
             * a / b = 2 / 1 = 2
             */
            if (!nodes.count(s1) && !nodes.count(s2)) {

                nodes[s1] = new Node();
                nodes[s2] = new Node();

                nodes[s1]->value = ratio;
                nodes[s2]->value = 1.0;

                nodes[s1]->parent = nodes[s2];
            }

            /*
             * CASE 2:
             * s1 is new, s2 already exists.
             *
             * We know:
             *
             * s1 / s2 = ratio
             *
             * Therefore:
             *
             * s1.value = s2.value * ratio
             */
            else if (!nodes.count(s1)) {
                nodes[s1] = new Node();

                nodes[s1]->value = nodes[s2]->value * ratio;

                nodes[s1]->parent = nodes[s2];
            }

            /*
             * CASE 3:
             * s2 is new, s1 already exists.
             *
             * From:
             *
             * s1 / s2 = ratio
             *
             * we get:
             *
             * s2 = s1 / ratio
             */
            else if (!nodes.count(s2)) {
                nodes[s2] = new Node();

                nodes[s2]->value = nodes[s1]->value / ratio;

                nodes[s2]->parent = nodes[s1];
            }

            /*
             * CASE 4:
             * Both variables already exist.
             *
             * Their components may need to be merged.
             */
            else {
                unionNodes(
                    nodes[s1],
                    nodes[s2],
                    ratio,
                    nodes
                );
            }
        }

        /*
         * Answer queries.
         */
        for (const auto& query : queries) {
            string a = query[0];
            string b = query[1];

            /*
             * Invalid if either variable is unknown
             * or they belong to different components.
             */
            if (!nodes.count(a) || !nodes.count(b) || findParent(nodes[a]) != findParent(nodes[b])) {

                result.push_back(-1.0);
            }
            else {
                /*
                 * Same component:
                 *
                 * a / b =
                 * value[a] / value[b]
                 */
                result.push_back(nodes[a]->value / nodes[b]->value);
            }
        }

        return result;
    }
};
