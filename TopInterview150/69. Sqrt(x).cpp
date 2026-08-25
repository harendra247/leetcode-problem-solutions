class Solution {
public:
    // Binary Search Time: O(logn) Sapce: O(1)
    int mySqrt_(int x) {
        long int left = 0, right = x / 2, mid;
        
        while (left <= right) {
            mid = left + (right - left) / 2; 
            
            if (mid * mid < x) {
                left = mid + 1;
            } else if (mid * mid == x) {
                return mid;
            } else {
                right = mid - 1;
            }
        }
        
        return x < 2 ? x : left - 1;
    }
    
    
    // Newton's Method Time: O(logn) Sapce: O(1)
    int mySqrt(int x) {
        long long r = x;
        while (r * r > x)
            r = (r + x / r) / 2;
        return r;  
    }
};
