class Solution {
public:
    
    /*Let's explain it in a clear and short manner:
    suppose there're k elements, the sum of original array is s, the minimum move is m, eventually all the elements become e, we know each move contributes (k-1) to the sum, so we have:
    s + (k-1)*m = k*e
    for the minimum element min, it must be added m times, i.e.
    min + m = e
    The two equations above would give us m = s - k*min
    */
    // Time: O(n) Space: O(1)
    int minMoves(vector<int>& nums) {
        int n = nums.size();
       if(n <= 1)
          return 0;
       int mn = nums[0];
       long sum = nums[0];
       for(int i = 1; i < n; ++i) {
           mn = min(mn, nums[i]);
           sum += nums[i];
       }
       return sum -long(mn)*long(n); 
    }
};
