class Solution {
public:
    // Time: O(n) Space: O(1)
    int sortPermutation(vector<int>& nums) {
        int n = nums.size();
        int res = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (nums[i] == i) {
                continue;
            }
            res &= nums[i];
        }
        return res == INT_MAX ? 0 : res;
    }
};
