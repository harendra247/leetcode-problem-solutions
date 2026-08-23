class Solution {
public:
    // Time: O(n) Space: O(n)
    int longestConsecutive_(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        unordered_set<int> record(nums.begin(), nums.end());
        int res = 1;
        for (int n : nums) {
            if (record.find(n) == record.end())
                continue;
            record.erase(n);
            int prev = n - 1, next = n + 1;
            while (record.find(prev) != record.end())
                record.erase(prev--);
            while (record.find(next) != record.end())
                record.erase(next++);
            res = max(res, next - prev - 1);
        }
        
        return res; 
    }

    // Time: O(n) Space: O(n)
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> record(nums.begin(), nums.end());
        int longestStreak = 0;
        for (int num : record) {
            if (!record.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;
                while (record.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }
                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return longestStreak;
    }
};
