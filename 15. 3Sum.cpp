class Solution {
public:
    
    // Time: O(nlogn + n^2) Space: O(n)
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        
        if (nums.size() < 3) 
            return res;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size() - 2; ++i) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }

            int start = i + 1;
            int end = nums.size() - 1;

            while (start < end) {
                int target = 0;
                int sum = nums[i] + nums[start] + nums[end];
                if (sum == target) {
                    //Add 
                    res.push_back({nums[i], nums[start], nums[end]});
                    
                    do {
                        start++;
                    } while (start < end && nums[start] == nums[start-1]); 

                    do {
                        end--;
                    } while (start < end && nums[end] == nums[end+1]); 
                } else if (sum < target) {
                    ++start;
                } else {
                    --end;
                }
            } 
        }
        
        return res;
    }
};
