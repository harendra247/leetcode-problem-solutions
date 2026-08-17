class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        // Only remainder modulo 3 matters.
        for (int stone : stones) {
            ++cnt[stone % 3];
        }

        /*
         * Case 1: Even number of remainder-0 stones.
         *
         * Alice needs at least one remainder-1 stone
         * AND one remainder-2 stone.
         */
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        /*
         * Case 2: Odd number of remainder-0 stones.
         *
         * Alice wins only when one of the remainder
         * groups significantly outnumbers the other.
         */
        return abs(cnt[1] - cnt[2]) > 2;
    }
};
