class Solution {
public:
    // Time: O(n) Space: O(1)
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size(); i-- != 0; digits[i] = 0)
            if (digits[i]++ < 9)
                return digits;
        
        digits[0]++;
        digits.push_back(0); // handles case 9999 + 1 = 10000
        return digits;
    }
};
