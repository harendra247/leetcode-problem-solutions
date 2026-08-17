class Solution {
public:
    
    // Two pointer Time: O(n) Space: O(1)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0;
        int r = numbers.size() - 1;
        vector<int> res;
        while (l < r) {
            if (numbers[l] + numbers[r] == target) {
                res.push_back(l + 1);
                res.push_back(r + 1);
                return res;
            } else if(numbers[l] + numbers[r] > target) {
                r--;
            } else {
                l++;
            }
        }
		return res;
    }
    
    // Binary search Time: O(n) Space: O(1) 
    vector<int> twoSum_(vector<int>& nums, int target) {
        int N = nums.size();
        for(int i = 0; i < N-1; i++){
            int lo = i+1;
            int hi = N;
            while (lo < hi) {
                int mid = lo + (hi-lo) / 2;
                if (nums[mid] == target-nums[i]) 
                    return {i+1, mid+1};
                else if (nums[mid] >= target-nums[i]) 
                    hi = mid;
                else 
                    lo = mid+1;
            }
            if (lo != nums.size() && nums[lo] == target-nums[i]) 
                return {i+1, lo+1};
        }
        return {}; // not found
    }
};
