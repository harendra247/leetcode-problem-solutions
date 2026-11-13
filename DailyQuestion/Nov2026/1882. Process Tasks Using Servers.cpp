class Solution {
public:
    // n = servers.size(), m = tasks.size()
    // Time: O((n + m) * log(n + 1))
    // Auxiliary space: O(n), excluding the O(m) result.
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        // Available servers ordered by (weight, index).
        using FreeServer = pair<int, int>;
        priority_queue<FreeServer, vector<FreeServer>,
                       greater<FreeServer>> available;

        // Busy servers ordered by (finish time, index).
        using BusyServer = pair<long long, int>;
        priority_queue<BusyServer, vector<BusyServer>,
                       greater<BusyServer>> busy;

        for (int index = 0; index < n; ++index) {
            available.emplace(servers[index], index);
        }

        vector<int> answer(m);
        long long time = 0;

        for (int task = 0; task < m; ++task) {
            // Task 'task' arrives at second 'task'.
            time = max(time, static_cast<long long>(task));

            // If necessary, wait until a server finishes.
            if (available.empty()) {
                time = max(time, busy.top().first);
            }

            // Release every server available at this time.
            while (!busy.empty() && busy.top().first <= time) {
                auto [finishTime, index] = busy.top();
                busy.pop();

                available.emplace(servers[index], index);
            }

            // Select the lowest weight, then lowest index.
            auto [weight, index] = available.top();
            available.pop();

            answer[task] = index;
            busy.emplace(time + tasks[task], index);
        }

        return answer;
    }
};
