class Solution {
public:
    // Time: O(logn) Space: O(logn)
    double myPow_(double x, int n) {
        if (n < 0) 
            return 1 / x * myPow(1 / x, -(n + 1));
        if (n == 0) 
            return 1;
        if (n == 2) 
            return x * x;
        if (n % 2 == 0) 
            return myPow(myPow(x, n / 2), 2);
        else 
            return x * myPow(myPow(x, n / 2), 2);
    }
    
    // Time: O(logn) Space: O(1)
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N *= -1;
        }
        double ans = 1.0;
        double current_product = x;
        for (long long i = N; i > 0 ; i /= 2) {
            if ((i % 2) == 1) {
                ans = ans * current_product;
            }
            current_product = current_product * current_product;
        }
        return ans;  
    }
};
