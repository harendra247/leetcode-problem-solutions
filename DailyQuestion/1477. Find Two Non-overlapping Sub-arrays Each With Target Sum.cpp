class Solution {
public:
    // Average Time: O(n) Space: O(n)
    int minSumOfLengths(vector<int>& arr, int target) {
        const int n = arr.size();

        // prefixSum -> latest index having this prefix sum
        unordered_map<int, int> prefixIndex;

        prefixIndex[0] = -1;

        int prefixSum = 0;

        // Build the prefix-sum map.
        for (int i = 0; i < n; ++i) {
            prefixSum += arr[i];
            prefixIndex[prefixSum] = i;
        }

        int bestLeftLength = INT_MAX;
        int answer = INT_MAX;

        prefixSum = 0;

        for (int i = 0; i < n; ++i) {
            prefixSum += arr[i];

            /*
                Find a target-sum subarray ending at i.

                prefixSum[i] - prefixSum[p] = target

                Therefore:

                prefixSum[p] = prefixSum[i] - target
            */
            auto leftIt = prefixIndex.find(prefixSum - target);

            if (leftIt != prefixIndex.end()) {
                int currentLength = i - leftIt->second;

                // Best target-sum subarray found so far.
                bestLeftLength = min(bestLeftLength, currentLength);
            }

            /*
                Find a target-sum subarray starting at i + 1.

                prefixSum[j] - prefixSum[i] = target

                Therefore:

                prefixSum[j] = prefixSum[i] + target
            */
            auto rightIt = prefixIndex.find(prefixSum + target);

            if (rightIt != prefixIndex.end() && bestLeftLength != INT_MAX) {

                int rightLength = rightIt->second - i;

                answer = min(answer, bestLeftLength + rightLength);
            }
        }

        return answer == INT_MAX ? -1 : answer;
    }
};
