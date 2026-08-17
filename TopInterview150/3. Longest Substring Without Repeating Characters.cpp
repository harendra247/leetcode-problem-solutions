class Solution {
public:
    // pwwkew
    int lengthOfLongestSubstring_(string s) {
        vector<int> Map(256, -1);
        int maxLen = 0, start = -1;
        
        for (int i = 0; i != s.length(); i++) {
            if (Map[s[i]] > start)
                start = Map[s[i]];
            Map[s[i]] = i;
            maxLen = max(maxLen, i - start);
        }
        return maxLen;
    }
    
    
   // same as above easy to understand 
   // Time: O(n) Space: O(n) 
   int lengthOfLongestSubstring(string s) {
        if (s.length() == 0)
            return 0;
        unordered_map<char, int> map;// stores the index of char
        int maxlength = 0;
        for (int i = 0, j = 0; i < s.length(); ++i) {
            if (map.count(s[i])) {
                j = max(j, map[s[i]] + 1); // move j to next index
            }
            map[s[i]] = i;
            maxlength = max(maxlength, i - j + 1);
        }
        return maxlength;  
    }
};
