class Solution {
public:
    int rangeBitwiseAnd_(int left, int right) {
        int trans = 0;
        while(left != right) {
            ++ trans;
            left >>= 1;
            right >>= 1;
        }
        return left << trans;
    }
    
    // Brian Kernighan's Algorithm
    //
    // Key idea:
    // The bitwise AND of a range keeps only the bits that are
    // identical in every number from left to right.
    //
    // x & (x - 1) removes the rightmost set bit of x.
    //
    // By repeatedly removing the rightmost set bit from 'right'
    // until left == right, we remove every bit that cannot remain
    // set throughout the entire range.
    //
    // Time:  O(log(right))
    // Space: O(1)
    int rangeBitwiseAnd(int left, int right) {
        while (left < right) {
            // Remove the rightmost set bit.
            right &= (right - 1);
        }

        return right;
    }
};
