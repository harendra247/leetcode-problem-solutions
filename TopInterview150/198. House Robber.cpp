class Solution {
public:
    // DP tabulation: Time: O(n) Space: O(n)
    int rob_(vector<int>& nums) {
        const int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; ++i)
            dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
        return dp[n-1];
    }
    
    // Bottom-up DP, space optimized
    // Time: O(n)
    // Space: O(1)
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 0)
            return 0;

        int twoBack = 0;       // dp[i - 2]
        int oneBack = nums[0]; // dp[i - 1]

        for (int i = 1; i < n; ++i) {

            // Choice 1: skip current house
            // Choice 2: rob current house
            int current = max(oneBack, twoBack + nums[i]);

            // Shift DP states
            twoBack = oneBack;
            oneBack = current;
        }

        return oneBack;
    }
    
    // DP recurstion + memoization : Time: O(n) Space: O(n)
    int rob_r(vector<int>& nums) {
        vector<int> memo(nums.size() + 1, -1);
        return rob(nums, nums.size() - 1, memo);
    }

     int rob(vector<int>& nums, int i, vector<int> &memo) {
        if (i < 0) {
            return 0;
        }
        if (memo[i] >= 0) {
            return memo[i];
        }
        int result = max(rob(nums, i - 2, memo) + nums[i], rob(nums, i - 1, memo));
        memo[i] = result;
        return result;  
    }
};
