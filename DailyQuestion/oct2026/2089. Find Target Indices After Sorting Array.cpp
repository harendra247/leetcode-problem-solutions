class Solution {
public:
    // Time: O(nlogn) Space: O(n)
    vector<int> targetIndices_(vector<int>& nums, int target) {
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


    // Time: O(n) Space: O(1)
    vector<int> targetIndices(vector<int>& nums, int target) {
        int smaller = 0;
        int equal = 0;

        for (int num : nums) {
            if (num < target) {
                ++smaller;
            } else if (num == target) {
                ++equal;
            }
        }

        vector<int> result(equal);
        iota(result.begin(), result.end(), smaller);
        return result;
    }
};
