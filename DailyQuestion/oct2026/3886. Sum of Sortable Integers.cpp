class Solution {
public:
    /*
        Let τ(n) be the number of divisors of n:
        - Time: O(n log n + n × τ(n)).
        - Space: O(n), for the sorted target.
    */
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> target = nums;
        sort(target.begin(), target.end());

        // Check one block against its sorted target positions.
        auto blockMatches = [&](int left, int length) {
            int pivot = 0;

            // A sorted rotation must start after the first decrease.
            for (int offset = 0; offset + 1 < length; ++offset) {
                if (nums[left + offset] > nums[left + offset + 1]) {
                    pivot = offset + 1;
                    break;
                }
            }

            // Compare the rotated block without constructing it.
            for (int offset = 0; offset < length; ++offset) {
                int source = left + (pivot + offset) % length;

                if (nums[source] != target[left + offset]) {
                    return false;
                }
            }

            return true;
        };

        auto validBlockSize = [&](int length) {
            for (int left = 0; left < n; left += length) {
                if (!blockMatches(left, length)) {
                    return false;
                }
            }

            return true;
        };

        int answer = 0;

        // Process divisors in pairs.
        for (int d = 1; d <= n / d; ++d) {
            if (n % d != 0) {
                continue;
            }

            if (validBlockSize(d)) {
                answer += d;
            }

            int pairedDivisor = n / d;

            if (pairedDivisor != d && validBlockSize(pairedDivisor)) {
                answer += pairedDivisor;
            }
        }

        return answer;
    }
};
