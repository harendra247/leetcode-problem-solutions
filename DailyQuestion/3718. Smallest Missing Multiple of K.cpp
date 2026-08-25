class Solution {
public:
    // Time: O(n) Space: O(n)
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> seen(nums.begin(), nums.end());
        int ans = k;
        while (seen.count(ans)) {
            ans += k;
        }
        return ans;
    }
};
