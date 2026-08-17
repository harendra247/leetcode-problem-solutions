class Solution {
public:
    // Time: O(m*n) Space: O(1)
    string longestCommonPrefix(vector<string>& strs) {
        string s = "";
        if (strs.size() == 0) 
            return s;
        else if (strs.size() == 1) 
            return strs[0];
            
        for (size_t i = 0; i < strs[0].size(); i++) {
            char c = strs[0][i];
            
            for (size_t j = 1; j < strs.size(); j++) {
                if (i >= strs[j].size()) {
                   return s;
                }
                
                if (c != strs[j][i]) {
                    return s;
                }
            }
            
            s += c;
        }
        
        return s;
    }
};
