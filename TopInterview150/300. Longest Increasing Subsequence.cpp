class Solution {
public:
    int lengthOfLIS_1(vector<int>& nums) {
        vector<int> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
            if (it==res.end()) res.push_back(nums[i]);
            else *it = nums[i];
        }
        return res.size();
    }

    // DP 
    int lengthOfLIS_dp(vector<int>& nums) {
        // dp[i] represents the length of the longest increasing subsequence 
        // that ends with the i th element.
        vector<int> dp(nums.size(), 1);
        
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        int longest = 0;
        for (int c: dp) {
            longest = max(longest, c);
        }
        
        return longest;
    }
    
    int lengthOfLIS_2(vector<int>& nums) {
        vector<int> tails(nums.size());
        int size = 0;
        for (int x : nums) {
            int i = 0, j = size;
            while (i != j) {
                int m = (i + j) / 2;
                if (tails[m] < x)
                    i = m + 1;
                else
                    j = m;
            }
            tails[i] = x;
            if (i == size) ++size;
        }
        return size;
    }
    
    // Binary search (note boundaries in the caller)
    int CeilIndex(std::vector<int>& v, int l, int r, int key) {
        while (r - l > 1) {
            int m = l + (r - l) / 2;
            if (v[m] >= key)
                r = m;
            else
                l = m;
        }

        return r;
    }
    
    // Time: O(nlogn) Space: O(n)
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;

        std::vector<int> tail(nums.size(), 0);
        tail[0] = nums[0];

        int length = 1; // always points empty slot in tail

        for (size_t i = 1; i < nums.size(); i++) {

            // new smallest value
            if (nums[i] < tail[0])
                tail[0] = nums[i];

            // nums[i] extends largest subsequence
            else if (nums[i] > tail[length - 1])
                tail[length++] = nums[i];

            // nums[i] will become end candidate of an existing
            // subsequence or Throw away larger elements in all
            // LIS, to make room for upcoming greater elements
            // than nums[i] (and also, nums[i] would have already
            // appeared in one of LIS, identify the location
            // and replace it)
            else {
                //auto a = CeilIndex(tail, -1, length - 1, nums[i]); // this is also working
                auto idx = lower_bound(tail.begin(), tail.begin() + length, nums[i]) - tail.begin();
                tail[idx] = nums[i];
            }
        }

        return length;  
    }
};
