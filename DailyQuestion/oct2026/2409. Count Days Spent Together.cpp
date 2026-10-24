class Solution {
public:
    // Time: O(1) Space: O(1)
    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        vector<int> datesOfMonths = {31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};
        vector<int> prefixSum(1, 0);
        for (int date : datesOfMonths) {
            prefixSum.emplace_back(prefixSum.back() + date);
        }
        std::function<int(const std::string&, const std::vector<int>&)> calculateDayOfYear;
    
        calculateDayOfYear = [&](const std::string& day, const std::vector<int>& prefixSum) -> int {
            int month = std::stoi(day.substr(0, 2));
            int date = std::stoi(day.substr(3));
            return prefixSum[month - 1] + date;
        };

        int arriveAliceDay = calculateDayOfYear(arriveAlice, prefixSum);
        int leaveAliceDay = calculateDayOfYear(leaveAlice, prefixSum);
        int arriveBobDay = calculateDayOfYear(arriveBob, prefixSum);
        int leaveBobDay = calculateDayOfYear(leaveBob, prefixSum);
        
        int overlapStart = max(arriveAliceDay, arriveBobDay);
        int overlapEnd = min(leaveAliceDay, leaveBobDay);

        return max(0, overlapEnd - overlapStart + 1);
    }
};
