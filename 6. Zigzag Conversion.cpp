class Solution {
public:
    
    // Time: O(n) Space: O(n)
    string convert_(string s, int numRows) {
        if (numRows <= 1 || numRows >= s.size()) 
            return s;
        vector<string> str(numRows, "");
        for (int i = 0, row = 0, step = 1; i < s.size(); i++) {
            str[row] += s[i];
            if (row == 0) 
                step = 1;
            if (row == numRows - 1) 
                step = -1;
            row += step;
        }
        string ret;
        for (auto d : str) 
            ret += d;
        return ret;
    }
    
    // Time: O(n) Space: O(n)
    string convert(string s, int numRows) {
        vector<string> vs(numRows, "");
        int n = s.length(), i = 0;
        while (i < n) {
            for (int j = 0; j < numRows && i < n; j++)
                vs[j].push_back(s[i++]);
            for (int j = numRows - 2; j >= 1 && i < n; j--)
                vs[j].push_back(s[i++]);
        }
        string zigzag;
        for (string v : vs) 
            zigzag += v;
        return zigzag;
    } 
};
