class Solution {
public:
    bool checkDivisibility(int n) {
        int sum = 0, prod = 1, num = n;

        while(n) {
            sum += n % 10;
            prod *= n % 10;
            n = n / 10;
        } 
        sum += prod;
        return (num % sum == 0);
    }
};
