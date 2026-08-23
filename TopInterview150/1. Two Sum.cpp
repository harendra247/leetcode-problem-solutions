class Solution {
public:
    // Time: O(n) Space: O(n)
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash; // item, index
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (hash.find(complement) != hash.end()) {
                return {hash[complement], i};
            }
            
            hash[nums[i]] = i;
        }
        
        return {};
    }
};
