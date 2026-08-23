class Solution {
public:
    int digitSquareSum(int n) {
        int sum = 0, tmp;
        while (n) {
            tmp = n % 10;
            sum += tmp * tmp;
            n /= 10;
        }
        return sum;
    }

    // Floyd's Cycle-Finding Algorithm Time: O(n) Space: O(1)
    bool isHappy(int n) {
        int slow, fast; // Example 89 will go in endless loop
        slow = fast = n;
        do {
            slow = digitSquareSum(slow);
            fast = digitSquareSum(fast);
            fast = digitSquareSum(fast);
        } while(slow != fast);
        return slow == 1 ? true : false;
    }
};
