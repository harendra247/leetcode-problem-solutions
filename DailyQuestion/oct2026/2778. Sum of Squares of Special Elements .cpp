class Solution {
public:
    // Time: O(n^.5) Space: O(1)
    int sumOfSquares(vector<int>& nums) {
        int n = nums.size();
        int answer = 0;

        for (int divisor = 1; divisor <= n / divisor; ++divisor) {
            if (n % divisor != 0) {
                continue;
            }

            int pairedDivisor = n / divisor;

            answer += nums[divisor - 1] * nums[divisor - 1];

            // Count the paired index only when it is different.
            if (pairedDivisor != divisor) {
                answer += nums[pairedDivisor - 1]
                        * nums[pairedDivisor - 1];
            }
        }

        return answer;
    }
};
