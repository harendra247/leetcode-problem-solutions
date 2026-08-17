class Solution {
public:
     /*
    [1024]. Video Stitching (https://leetcode.com/problems/video-stitching/)
    [45]. Jump Game II (https://leetcode.com/problems/jump-game-ii/)
    [1326]. Minimum Number of Taps to Open to Water a Garden (https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/)
    */

    // https://www.youtube.com/watch?v=dJ7sWiOoK7g
    // BFS Time: O(n) Space: O(1)
    int jump_bfs(vector<int>& nums) {
        int count = 0, start = 0, end = 0;
        while (end < nums.size() - 1) {
            int farCanReach = 0;
            for(int i = start; i <= end; i++) {
                farCanReach = max(farCanReach, i + nums[i]);
            } 
            start = end + 1;
            end = farCanReach;       
            count++;
        }
        return count;
    }

    // Dynamic programming Time: O(n^2) Space: O(n)
    int jump_(vector<int>& nums) {
        int n = nums.size();
        vector<int> minjumps(n, INT_MAX);
        minjumps[0] = 0;
        
        for (int i = 0; i < n-1; ++i) {
           for (int j=i+1; j <= min(i + nums[i], n-1); ++j) {
                minjumps[j] = min(minjumps[j], 1 + minjumps[i]);
            } 
        }
        
        return minjumps[n-1];
    }
    
    // Tushar roy
     int jump_tr(vector<int>& nums) {
        int n = nums.size();
        if (nums.size() == 1) {
            return 0;
        }
        int count = 0;
        int i = 0;
        while (i + nums[i] < n - 1) {
            int maxVal = 0;
            int maxValIndex = 0;
            for (int j = 1; j <= nums[i]; j++) {
                if (nums[j + i] + j > maxVal) {
                    maxVal = nums[j + i] + j;
                    maxValIndex = i + j;
                }
            }
            i = maxValIndex;
            count++;
        }
        return count + 1;
    }
    
    // Greedy Approach Time: O(n) Space: O(1)
    // Greedy / implicit BFS
    // Time: O(n)
    // Space: O(1)
    int jump(vector<int>& nums) {
        int n = nums.size();

        int jumps = 0;

        // End of range reachable using current jumps.
        int currentEnd = 0;

        // Farthest position reachable using one more jump.
        int farthest = 0;

        // No need to process the last index.
        for (int i = 0; i < n - 1; ++i) {

            // Explore possibilities from current BFS level.
            farthest = max(farthest, i + nums[i]);

            // Finished current reachable range.
            if (i == currentEnd) {

                // Must take another jump.
                ++jumps;

                // Next BFS level ends here.
                currentEnd = farthest;

                // Optional early exit.
                if (currentEnd >= n - 1) {
                    break;
                }
            }
        }

        return jumps;
    }
};
