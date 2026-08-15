class Solution {
public:
    // Time: O(n) Space: O(1)
    int removeDuplicates(vector<int>& nums) {
        int pivot = 0, i = 0;

        while(i < nums.size()) {
            if (i == 0 || (i == 1 && nums[0] == nums[i])) {
                nums[pivot++] = nums[i++];
                continue;
            }
            if ((nums[pivot-1] < nums[i]) || (nums[pivot-2] < nums[i]) ) {
                nums[pivot++] = nums[i];
            }
            i++;
        }
        return pivot;
    }
};
