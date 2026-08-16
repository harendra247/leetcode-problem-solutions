class Solution {
public:
    
    // Time: O(n) Space: O(1)
    int maxProfit_(vector<int>& prices) {
        int profit = 0;
        for (size_t p = 1; p < prices.size(); ++p) 
           profit += max(prices[p] - prices[p - 1], 0);    
        return profit;
    }
};
