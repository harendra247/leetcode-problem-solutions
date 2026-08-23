class Solution {
public:
    
    // Time: O(m+n) Space: (m)
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> arr(26, 0);
        if (ransomNote.size() > magazine.size()) 
            return false;
        for (int i = 0; i < magazine.length(); i++) {
            arr[magazine[i] - 'a']++;
        }
        for (int i = 0; i < ransomNote.length(); i++) {
            if (--arr[ransomNote[i]-'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};
