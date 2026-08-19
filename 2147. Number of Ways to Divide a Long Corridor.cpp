class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int numberOfWays(string corridor) {
        const long long MOD = 1e9 + 7;

        // Store positions of all seats.
        vector<int> seats;

        for (int i = 0; i < corridor.size(); ++i) {
            if (corridor[i] == 'S') {
                seats.push_back(i);
            }
        }

        /*
         * Every section needs exactly 2 seats.
         *
         * Therefore:
         * - no seats => impossible
         * - odd number of seats => impossible
         */
        if (seats.empty() || seats.size() % 2 == 1) {
            return 0;
        }

        long long ways = 1;

        /*
         * Seat groups are:
         *
         * (seats[0], seats[1])
         * (seats[2], seats[3])
         * (seats[4], seats[5])
         * ...
         *
         * Between two groups:
         *
         * previous group's second seat = seats[i - 1]
         * next group's first seat      = seats[i]
         *
         * Number of divider positions:
         *
         * seats[i] - seats[i - 1]
         */
        for (int i = 2; i < seats.size(); i += 2) {
            int choices = seats[i] - seats[i - 1];

            ways = (ways * choices) % MOD;
        }

        return static_cast<int>(ways);
    }
};
