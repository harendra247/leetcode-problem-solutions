class Solution {
public:
    // Time: O(log n) Space: O(1)
    int trailingZeroes_(int n) {
        return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
    }

    // Time: O(log n) Space: O(1)
    int trailingZeroes(int n) {
        int zeroCount = 0;
        while (n > 0) {
            n /= 5;
            zeroCount += n;
        }
        return zeroCount;
    }
};
