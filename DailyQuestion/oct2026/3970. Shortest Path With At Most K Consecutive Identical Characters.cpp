class Solution {
public:
    // Time: O(nk+mklog(mk)) Space: O(nk+mk)
    long long shortestPath(int n, vector<vector<int>>& edges,
                           string labels, int k) {
        if (n == 0 || k < 1) {
            return -1;
        }

        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }

        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, INF)
        );

        // State: (cost, node, consecutive identical labels).
        using State = tuple<long long, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq; // minheap

        dist[0][1] = 0;
        pq.emplace(0, 0, 1);

        while (!pq.empty()) {
            auto [cost, node, count] = pq.top();
            pq.pop();

            if (cost != dist[node][count]) {
                continue;
            }

            // First destination state popped has minimum cost.
            if (node == n - 1) {
                return cost;
            }

            for (const auto& [next, weight] : graph[node]) {
                int nextCount = labels[node] == labels[next]
                                    ? count + 1
                                    : 1;

                if (nextCount > k) {
                    continue;
                }

                long long nextCost = cost + weight;

                if (nextCost < dist[next][nextCount]) {
                    dist[next][nextCount] = nextCost;
                    pq.emplace(nextCost, next, nextCount);
                }
            }
        }

        return -1;
    }
};
