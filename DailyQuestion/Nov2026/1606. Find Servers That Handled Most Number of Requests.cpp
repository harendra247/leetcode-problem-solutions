class Solution {
public:
    // n = number of requests
    // Time: O((n + k) * log(k + 1))
    // Auxiliary space: O(k)
    vector<int> busiestServers(
        int k, vector<int>& arrival, vector<int>& load
    ) {
        vector<int> handled(k, 0);

        // Available server indices in sorted order.
        set<int> available;
        for (int server = 0; server < k; ++server) {
            available.insert(server);
        }

        // Entries: (finish time, server index).
        using Entry = pair<long long, int>;
        priority_queue<Entry, vector<Entry>, greater<Entry>> busy;

        for (int request = 0; request < arrival.size(); ++request) {
            long long start = arrival[request];

            // Servers finishing exactly at 'start' are also available.
            while (!busy.empty() && busy.top().first <= start) {
                int server = busy.top().second;
                busy.pop();
                available.insert(server);
            }

            // Unlike a waiting queue, this problem drops the request.
            if (available.empty()) {
                continue;
            }

            // Start searching at the request's preferred server.
            auto it = available.lower_bound(request % k);

            // Wrap around if no available index is large enough.
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;
            available.erase(it);

            ++handled[server];
            busy.emplace(start + load[request], server);
        }

        int maximum = *max_element(handled.begin(), handled.end());

        vector<int> answer;
        for (int server = 0; server < k; ++server) {
            if (handled[server] == maximum) {
                answer.push_back(server);
            }
        }

        return answer;
    }
};
