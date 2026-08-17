class Solution {
public:
    
    // Time: O(n) Space: O(1)
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int i = 0, j = 0, n = s.length();
        while (i < n && s[i] == ' ')
            i++;
        while (i < n) {
            int c = 0;
            while (s[i] != ' ' && i < n) {
                s[j++] = s[i++];
                c++;
            }
            reverse(s.begin() + j - c, s.begin() + j);
            while (i < n && s[i] == ' ')
                i++;
            if (i >= n)
                break;
            s[j++] = ' ';
        }
        return s.substr(0, j);
    }
};
