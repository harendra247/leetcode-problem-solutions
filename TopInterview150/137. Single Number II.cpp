class Solution {
public:
    
    // Time: O(n) Space: O(1)
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for(int i = 0; i < 32; i++) {
            int bitSum = 0;
            for(int num : nums) {
                bitSum += ((num >> i) & 1);
            }
            if(bitSum % 3) {
                ans = ans | (1 << i);
            }
        }
        return ans;
    }
    
    // Time: O(n) Space: O(1)
    // Every number appears 3 times except one.
    // We track the occurrence count of every bit modulo 3.
    //
    // For each bit:
    //
    // ones = 1, twos = 0 -> appeared once
    // ones = 0, twos = 1 -> appeared twice
    // ones = 0, twos = 0 -> appeared 0 or 3 times
    //
    // Time:  O(n)
    // Space: O(1)

    int singleNumber_(vector<int>& nums) {
        int ones = 0;
        int twos = 0;

        for (int num : nums) {

            // Move bits to their next occurrence state.
            //
            // XOR toggles the bit in 'ones'.
            // & ~twos removes bits that have already appeared twice.
            ones = (ones ^ num) & ~twos;

            // Same idea for the 'twos' state.
            //
            // & ~ones ensures that a bit cannot be present
            // in both 'ones' and 'twos' at the same time.
            twos = (twos ^ num) & ~ones;
        }

        // Bits that appeared exactly once remain in 'ones'.
        return ones;
    }
};
