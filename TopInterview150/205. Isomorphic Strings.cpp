class Solution {
public:
    // Time: O(n) Space: O(min(m, n))
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length())
            return false;
        
        unordered_map<char, char> m1; //mapping chars from s and t 
        unordered_map<char, bool> m2; //mapping to show chars in t are used or no
        
        for (int i = 0; i < s.length(); i++) {
            auto key = m1.find(s[i]);
            if (key != m1.end()) {
                if (key->second != t[i]) {
                    return false;
                }
           } else {
               if (m2.count(t[i])) {
                   return false; 
               } else {
                   m1[s[i]] = t[i];
                   m2[t[i]] = true;
               }
           }
        }
        return true;
    }
};
