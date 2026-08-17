class Solution {
public:
    // Time: O(|S|+|T|) Space: O(|S|+|T|)
    string minWindow(string s, string t) {
        vector<int> map(128, 0);
        for (auto c: t) 
            map[c]++;
        
        int counter = t.size(), begin = 0, end = 0, len = INT_MAX, head = 0;
        while (end < s.size()) {
            if (map[s[end]] > 0)  {
                counter--; // in t
            }
            map[s[end]]--;
            end++;
            while (counter == 0) { // valid
                if (end - begin < len) {
                    len = end - begin;
                    head = begin;
                }
                if (map[s[begin]] == 0) {
                    counter++;  // make it invalid
                }
                map[s[begin]]++;
                begin++;
            }  
        }
        return len == INT_MAX? "" : s.substr(head, len);
    }
};
