class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int lb = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        int ub = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin();

        vector<int> result;

        // Matching indices are in [lb, ub); ub is excluded.
        for (int i = lb; i < ub; ++i) {
            result.push_back(i);
        }

        return result;
    }
};
