class Solution {
public:
    // Time: O(n)
    // Space: O(n) here because substr creates temporary strings
    // Can be made O(1) extra space by scanning directly.
    bool sumGame(string num) {
        int n = num.size();

        int leftSum = 0;
        int rightSum = 0;

        int leftQ = 0;
        int rightQ = 0;

        for (int i = 0; i < n / 2; ++i) {
            if (num[i] == '?') {
                ++leftQ;
            } else {
                leftSum += num[i] - '0';
            }
        }

        for (int i = n / 2; i < n; ++i) {
            if (num[i] == '?') {
                ++rightQ;
            } else {
                rightSum += num[i] - '0';
            }
        }

        /*
         * Odd number of '?' means Alice gets one extra move,
         * so she can force the sums to differ.
         */
        if ((leftQ + rightQ) % 2 == 1) {
            return true;
        }

        /*
         * Bob can force a tie only when:
         *
         * leftSum - rightSum
         *
         * exactly matches the amount that can be compensated
         * by the imbalance in '?' counts.
         */
        int sumDifference = leftSum - rightSum;

        int questionDifference = rightQ - leftQ;

        return sumDifference != questionDifference * 9 / 2;
    }
};
