class Solution {
private:
    static constexpr int MOD = 1'000'000'007;
    static constexpr int MAX_HATS = 40;

    int allPeopleMask;

    // peopleForHat[hat] = people who like this hat.
    vector<vector<int>> peopleForHat;

    int solve(int hat, int mask, vector<vector<int>> &memo) {
        // Every person has received a hat.
        if (mask == allPeopleMask) {
            return 1;
        }

        // We have processed all 40 hats but not everyone
        // has received a hat.
        if (hat > MAX_HATS) {
            return 0;
        }

        // Return the already computed result.
        if (memo[hat][mask] != -1) {
            return memo[hat][mask];
        }

        // Option 1:
        // Don't use the current hat.
        int ways = solve(hat + 1, mask, memo);

        // Option 2:
        // Give the current hat to one person who likes it.
        for (int person : peopleForHat[hat]) {

            // Check whether this person already has a hat.
            if (mask & (1 << person)) {
                continue;
            }

            // Give the current hat to this person.
            int newMask = mask | (1 << person);

            ways = (ways + solve(hat + 1, newMask, memo)) % MOD;
        }

        return memo[hat][mask] = ways;
    }

public:
    /*
    Complexity

    Let:

    N = number of people
    H = number of hats (40)
    P = total number of hat preferences

    There are at most:

    H × 2^N

    DP states.

    For each state we potentially iterate through people who like the current hat.

    So a reasonable upper bound is:

    Time: O(H × 2^N × N)
    Space: O(H × 2^N + P)
    */
    int numberWays(vector<vector<int>>& hats) {
        int personCount = hats.size();

        // If there are n people:
        //
        // 1 << n gives 2^n.
        // Subtracting 1 gives a mask with all n bits set.
        //
        // Example for 3 people:
        // 1 << 3 = 1000
        //           - 1
        //           ----
        //             111
        allPeopleMask = (1 << personCount) - 1;

        // Convert:
        //
        // person -> hats they like
        //
        // into:
        //
        // hat -> people who like that hat
        //
        // We use index 1..40 because hats are numbered 1..40.
        peopleForHat.resize(MAX_HATS + 1);

        for (int person = 0; person < personCount; ++person) {
            for (int hat : hats[person]) {
                peopleForHat[hat].push_back(person);
            }
        }

        /*
         * There are 41 possible hat positions:
         *
         * 0, 1, 2, ..., 40
         *
         * We don't use index 0.
         *
         * There are 2^n possible masks.
         */
        // memo[hat][mask] =
        // number of ways to assign hats starting from 'hat'
        // when people represented by 'mask' already have a hat.
        vector<vector<int>> memo(MAX_HATS + 1, vector<int>(1 << personCount, -1));

        return solve(1, 0, memo);
    }

public:
    
    // Similar problems
    // 1986, 1434, 1994, 1125

    // Time:  O(40 * 2^n * n)
    // Space: O(2^n + total hat preferences)
    int numberWays_itr(vector<vector<int>>& hats) {
        static constexpr int MOD = 1'000'000'007;
        static constexpr int HAT_COUNT = 40;

        const int personCount = hats.size();
        const int allPeopleMask = (1 << personCount) - 1;

        /*
         * peopleForHat[hat] contains all people who like
         * that hat.
         */
        vector<vector<int>> peopleForHat(HAT_COUNT);

        for (int person = 0; person < personCount; ++person) {

            for (int hat : hats[person]) {
                peopleForHat[hat - 1].push_back(person);
            }
        }

        /*
         * ways[mask] =
         * number of assignments using hats processed so far,
         * where people represented by mask already have hats.
         */
        vector<int> ways(1 << personCount, 0);
        ways[0] = 1;

        for (int hat = 0; hat < HAT_COUNT; ++hat) {
            /*
             * Iterate backward so the current hat cannot be
             * assigned more than once.
             */
            for (int mask = allPeopleMask; mask >= 0; --mask) {

                if (ways[mask] == 0) {
                    continue;
                }

                for (int person : peopleForHat[hat]) {
                    // This person already has a hat.
                    if (mask & (1 << person)) {
                        continue;
                    }

                    int newMask = mask | (1 << person);

                    ways[newMask] = (ways[newMask] + ways[mask]) % MOD;
                }
            }
        }

        return ways[allPeopleMask];
    }
};
