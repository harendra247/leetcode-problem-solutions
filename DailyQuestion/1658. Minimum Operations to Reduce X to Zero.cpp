class Solution {
public:
    
    /*
    918. Maximum Sum Circular Subarray
    1423. Maximum Points You Can Obtain from Cards
    */
    
    // Time: O(n) Space: O(n)
    int minOperations_(vector<int>& nums, int x) {
        unordered_map<int, int> left;
        
        left.emplace(0, -1);
        for (int l = 0, sum = 0; l < nums.size() && sum + nums[l] <= x; ++l) {
            sum += nums[l];
            left.emplace(sum, l);
        }
        
        int res = INT_MAX;
        for (int r = nums.size()-1, sum = 0; r >= 0 && sum <= x; --r) {
            auto it = left.find(x-sum);
            if (it != end(left) && r >= it->second)
                res = min(res, (int)nums.size() - r + it->second);
            sum += nums[r];
        }
        return res == INT_MAX ? -1 : res;
    }
    
    
    // Time: O(n) Space: O(n)
    int _minOperations(vector<int>& nums, int x) {
        int target = -x;
        for (int num : nums)
            target += num;

        if (target == 0)
            return nums.size();  // since all elements are positive, we have to take all of them

        unordered_map<int, int> left;
        left[0] = -1;
        int sum = 0;
        int res = INT_MIN;

        for (int i = 0; i < nums.size(); ++i) {

            sum += nums[i];
            if (left.count(sum - target)) {
                res = max(res, i - left[sum - target]);
            }

            // no need to check containsKey since sum is unique
            left[sum] = i;
        }

        return res == INT_MIN ? -1 : nums.size() - res;
    }

    // Time: O(n) Space: O(1)
    int minOperations(std::vector<int>& nums, int x) {
        int total = std::accumulate(nums.begin(), nums.end(), 0);
        int target = total - x;
        int left = 0;
        int n = nums.size();
        int maxLength = -1;
        int runningSum = 0;

        for (int right = 0; right < n; right++) {
            runningSum += nums[right];

            while (runningSum > target && left <= right) {
                runningSum -= nums[left];
                left++;
            }

            if (runningSum == target) {
                maxLength = std::max(maxLength, right - left + 1);
            }
        }

        return maxLength != -1 ? n - maxLength : -1;
    }
};
