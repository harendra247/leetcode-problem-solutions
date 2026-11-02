class Solution {
public:
    
    // Time: O(nlogn) Space: O(1)
    int minMoves2(vector<int>& nums) {
        int l = 0, r = nums.size() - 1, sum = 0;
        sort(nums.begin(), nums.end());
        while (l < r) {
            sum += nums[r] - nums[l];
            l++;
            r--;
        }
        return sum;
    }
};
