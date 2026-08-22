class Solution {
public:
    int maxProfit_3(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        
        int n = prices.size();
        vector<int> currentprofits(n, 0);
        vector<int>  prevprofits(n, 0);
        int maxthusfar = INT_MIN;
        
        for (int k = 1; k <= 2; k++)  {
            maxthusfar = INT_MIN;
            
            for (int i = 1; i < prices.size(); i++) {
                maxthusfar = max(maxthusfar, prevprofits[i-1] - prices[i-1]);
                currentprofits[i] = max(currentprofits[i-1], maxthusfar + prices[i]);
            }
            currentprofits.swap(prevprofits);
        }

        return prevprofits[n-1];
    }
    
public:
    // At most 2 transactions
    //
    // State:
    // mem[bought][transactionsLeft][day]
    //
    // Time:  O(n * 2 * 2) = O(n)
    // Space: O(n) for memo + recursion stack
    int maxProfit_2(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();

        /*
         * bought:
         *   0 = currently NOT holding stock
         *   1 = currently holding stock
         *
         * txn:
         *   number of complete transactions still allowed
         *
         * day:
         *   current position in prices
         */
        vector<vector<vector<int>>> memo(2, vector<vector<int>>(3, vector<int>(n, -1)));

        // Start on day 0,
        // with 2 transactions available,
        // and no stock in hand.
        return solve(prices, 0, 2, false, memo);
    }

private:
    int solve(vector<int>& prices, int day, int txn, bool holding, vector<vector<vector<int>>>& memo) {
        /*
         * No more days OR no more transactions.
         */
        if (day >= prices.size() || txn == 0) {
            return 0;
        }

        if (memo[holding][txn][day] != -1) {
            return memo[holding][txn][day];
        }

        /*
         * Choice 1:
         * Do nothing today.
         */
        int best = solve(prices, day + 1, txn, holding, memo);

        if (holding) {
            /*
             * Choice 2:
             * SELL today.
             *
             * We receive prices[day].
             *
             * One complete transaction finishes,
             * so txn decreases by 1.
             */
            best = max(best, prices[day] + solve(prices, day + 1, txn - 1, false, memo));
        }
        else {
            /*
             * Choice 2:
             * BUY today.
             *
             * We pay prices[day],
             * so subtract it from profit.
             *
             * Transaction is NOT completed yet,
             * so txn does NOT decrease.
             */
            best = max(best, -prices[day] + solve(prices, day + 1, txn, true, memo));
        }

        return memo[holding][txn][day] = best;
    }

public:
    //https://www.youtube.com/watch?v=wuzTpONbd-0&list=PL-Jc9J83PIiG8fE6rj9F5a6uyQ5WPdqKy&index=34
    // At most 2 transactions
    //
    // Time: O(n)
    // Space: O(n)
    int maxProfit(const vector<int>& prices) {
        int n = prices.size();

        if (n < 2) {
            return 0;
        }

        /*
         * left[i] =
         * maximum profit using ONE transaction
         * somewhere in prices[0 ... i].
         */
        vector<int> left(n, 0);

        int minPrice = prices[0];

        for (int i = 1; i < n; ++i) {

            // Best buying price seen so far.
            minPrice = min(minPrice, prices[i]);

            /*
             * Either:
             *
             * 1. Keep previous best profit
             *
             * OR
             *
             * 2. Sell today after buying at minPrice.
             */
            left[i] = max(left[i - 1], prices[i] - minPrice);
        }


        /*
         * right[i] =
         * maximum profit using ONE transaction
         * somewhere in prices[i ... n-1].
         */
        vector<int> right(n, 0);

        int maxPrice = prices[n - 1];

        for (int i = n - 2; i >= 0; --i) {

            // Best selling price available in the future.
            maxPrice = max(maxPrice, prices[i]);

            /*
             * Either:
             *
             * 1. Keep the best transaction starting later
             *
             * OR
             *
             * 2. Buy today and sell at maxPrice.
             */
            right[i] = max(right[i + 1], maxPrice - prices[i]);
        }


        /*
         * Try every split:
         *
         * first transaction:
         *     days [0 ... split-1]
         *
         * second transaction:
         *     days [split ... n-1]
         */
        int answer = right[0];

        for (int split = 1; split < n; ++split) {
            answer = max(answer, left[split - 1] + right[split]);
        }

        return answer;
    }
    
public:
    // At most 2 transactions
    // Time: O(n)
    // Space: O(1)
    int maxProfit_1(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        /*
         * dp[k] =
         * maximum profit after completing
         * at most k transactions.
         */
        int dp[3] = {0};

        /*
         * minimum[k] =
         * minimum effective cost of buying stock
         * for transaction k.
         *
         * effective buy cost =
         *
         * price today - profit earned from
         * first k-1 transactions
         */
        int minimum[3] = {prices[0], prices[0], prices[0]};

        for (int price : prices) {

            for (int k = 1; k <= 2; ++k) {

                /*
                 * Suppose we want to begin the kth transaction.
                 *
                 * Before buying, we may already have earned:
                 *
                 * dp[k-1]
                 *
                 * Therefore the effective cost of buying today is:
                 *
                 * price - dp[k-1]
                 */
                minimum[k] = min(minimum[k], price - dp[k - 1]);

                /*
                 * Sell today.
                 *
                 * Profit =
                 *
                 * selling price
                 * -
                 * best effective buying cost
                 */
                dp[k] = max(dp[k], price - minimum[k]);
            }
        }

        return dp[2];
    }
};
