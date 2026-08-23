class Solution {
public:
    // Time: O(n) Space: (min(n, k))
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> uSet;
       
        if (k <= 0) 
            return false;
        if (k >= nums.size()) 
            k = nums.size() - 1;
       
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) 
                uSet.erase(nums[i - k - 1]); // sliding window
            if (uSet.find(nums[i]) != uSet.end()) 
                return true;
            uSet.insert(nums[i]);
        }
       
        return false;
    }
};
