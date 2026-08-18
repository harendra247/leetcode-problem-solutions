class Solution {
public:
    // Time: O(n) Space: O(1)
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        
        if (nums.size() == 0) 
            return res;
        string tmp = to_string(nums[0]);
        int count = 1, i = 1;
        for (i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i-1] + 1) {
                if (count > 1) {
                    tmp += "->" + to_string(nums[i-1]);
                }
                count = 0;
                res.push_back(tmp);
                tmp = to_string(nums[i]);
            }
            
            count++; 
        }
        
        if (count > 1) {
            tmp += "->" + to_string(nums[i-1]);
        }
        res.push_back(tmp);
        return res;
    }
};
