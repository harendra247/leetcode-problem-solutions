class Solution {
public:
    /*
    Let n = stones.size().

    Time: O(n)

    partial_sum() → O(n)
    DP loop → O(n)
    Total → O(n)

    Space: O(n)
    */
    int stoneGameVIII(vector<int>& stones) {
        const int n = stones.size();

        // prefix[i] = sum of stones[0 ... i].
        //
        // We need prefix sums because when a player chooses the
        // first i + 1 stones, their score contribution is exactly
        // prefix[i].
        vector<int> prefix(n);
        partial_sum(stones.begin(), stones.end(), prefix.begin());

        // scoreDiff represents the best score difference the current player
        // can achieve from the current state.
        //
        // For the last possible state, the entire remaining prefix
        // has to be taken.
        int scoreDiff = prefix[n - 1];

        // Work backwards because scoreDiff[i] depends only on scoreDiff[i + 1].
        //
        // Recurrence:
        //
        // scoreDiff[i] = max(
        //     scoreDiff[i + 1],              // skip this state
        //     prefix[i] - scoreDiff[i + 1]   // take prefix[i]
        // )
        //
        // Since we only need f[i + 1], we can update a single
        // variable instead of maintaining a DP array.
        for (int i = n - 2; i >= 1; --i) {
            scoreDiff = max(scoreDiff, prefix[i] - scoreDiff);
        }

        // The game starts with the first move forced to take
        // at least two stones, which corresponds to prefix[1].
        return scoreDiff;
    }
};
