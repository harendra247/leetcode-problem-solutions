class Solution {
public:
    
    // Time: O(n) Space: O(1)
    void rotate(vector<int>& nums, int k) {
        if (nums.size() == 0) {
            return;
        }
        
        k %= nums.size();
        rotate(nums, 0, nums.size()-1);
        rotate(nums, 0, k-1);
        rotate(nums, k, nums.size()-1);
        return; 
    }
    
    
    void rotate(vector<int>& nums, int l, int r) {
        int t;
        while (l < r) {
            t = nums[l];
            nums[l] = nums[r];
            nums[r] = t;
            l++, r--;
        }
    }
};
