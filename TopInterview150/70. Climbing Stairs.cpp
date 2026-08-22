class Solution {

public:
    // DP - Space Optimized
    // Time: O(n)
    // Space: O(1)
    int climbStairs(int n) {
        if (n <= 0)
            return 0;

        if (n == 1)
            return 1;

        int twoStepsBefore = 1; // ways(1)
        int oneStepBefore = 2;  // ways(2)

        for (int stair = 3; stair <= n; ++stair) {

            int current = oneStepBefore + twoStepsBefore;

            // Move the window forward
            twoStepsBefore = oneStepBefore;
            oneStepBefore = current;
        }

        return oneStepBefore;
    }
    
    // DP Tabulation
    // Time: O(n)
    // Space: O(n)
    int climbStairs_(int n) {
        vector<int> steps(n + 1, 0);

        steps[0] = 1;
        steps[1] = 1;

        for (int i = 2; i <= n; i++) {
            steps[i] = steps[i - 1] + steps[i - 2];
        }

        return steps[n];
    }
    
private:
    unordered_map<int, int> cache;

public:
    // Top-down DP (Memoization)
    // Time: O(n)
    // Space: O(n)
    int climbStairs_o(int n) {

        // Already calculated
        if (cache.find(n) != cache.end()) {
            return cache[n];
        }

        int result;

        if (n == 0) {
            result = 0;
        }
        else if (n == 1) {
            result = 1;
        }
        else if (n == 2) {
            result = 2;
        }
        else {
            result =
                climbStairs_o(n - 1) +
                climbStairs_o(n - 2);
        }

        cache[n] = result;

        return result;
    }
};
