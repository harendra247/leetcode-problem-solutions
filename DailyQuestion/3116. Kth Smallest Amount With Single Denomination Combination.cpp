class Solution {
public:
    // optimized binary search + inclusion-exclusion + precomputed LCMs
    // Precompute subset LCMs: O(2^n)
    // Each countValid():      O(2^n)
    // Binary search:          O(log(coins[0] * k))

    // Total:
    // O(2^n * log(coins[0] * k))

    // Space:
    // O(2^n)
    using ll = long long;

    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());

        /*
         * Remove redundant coins.
         *
         * If x is divisible by some smaller kept coin y,
         * then every multiple of x is already counted
         * as a multiple of y.
         */
        vector<int> filtered;

        for (int x : coins) {
            bool redundant = false;

            for (int y : filtered) {
                if (x % y == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant) {
                filtered.push_back(x);
            }
        }

        coins = filtered;

        int n = coins.size();
        int subsets = 1 << n;

        /*
         * lcm[mask] =
         * LCM of all coins included in this subset.
         */
        vector<ll> lcm(subsets, 1);

        /*
         * Search range.
         *
         * Upper bound:
         * kth multiple of the smallest coin.
         */
        ll left = k;
        ll right = 1LL * coins[0] * k + 1;

        /*
         * Precompute LCM of every subset.
         */
        for (int mask = 1; mask < subsets; ++mask) {

            // Remove lowest set bit.
            int previousMask = mask & (mask - 1);

            // Index of lowest set bit.
            int bit = __builtin_ctz(mask);

            /*
             * LCM(a,b) = a / gcd(a,b) * b
             */
            ll reduced = lcm[previousMask] / std::gcd(lcm[previousMask], (ll)coins[bit]);

            /*
             * Avoid overflow and unnecessary huge LCMs.
             */
            if (reduced <= right / coins[bit]) {
                lcm[mask] = reduced * coins[bit];
            } else {
                lcm[mask] = right + 1;
            }
        }

        /*
         * Count numbers <= x divisible by at least
         * one coin using inclusion-exclusion.
         */
        auto countValid = [&](ll x) -> ll {
            ll count = 0;

            for (int mask = 1; mask < subsets; ++mask) {
                if (lcm[mask] > x) {
                    continue;
                }

                ll multiples = x / lcm[mask];

                if (__builtin_popcount(mask) & 1) {
                    count += multiples;
                } else {
                    count -= multiples;
                }
            }

            return count;
        };

        /*
         * Binary search for the smallest x with
         * at least k valid numbers <= x.
         */
        while (left < right) {
            ll mid = left + (right - left) / 2;

            if (countValid(mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};
