class Solution {
public:
    // Time: O(n) Space: O(1)
    int singleNumber(vector<int>& nums) {
        int singleNum = 0;
        for (const int & num : nums) {
            singleNum ^= num;
        }

        return singleNum;
    }
};
