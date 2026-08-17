class Solution {
public:
    // Time: O(mn) Space: O(1)
    int strStr_(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        for (int i = 0; i <= m - n; i++) {
            int j = 0;
            for (; j < n; j++) {
                if (haystack[i + j] != needle[j]) {
                    break;
                }
            }
            if (j == n) {
                return i;
            }
        }
        return -1; 
    }
    
    // Finally comes the KMP algorithm. You may refer to KMP on jBoxer's blog and KMP on geeksforgeeks for some explanations. 

    // Time: O(m+n) KMP pattern matching  Space: O(n)
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (!n) {
            return 0;
        }
        vector<int> lps = kmpProcess(needle);
        int j=0;
        for (int i = 0; i < m; ++i) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = lps[j-1];
            }
            if (haystack[i] == needle[j]) {
                ++j;
            } 
            if (j == n)
                return i - j + 1;
        }
        return -1;
    }
private:
    vector<int> kmpProcess(string needle) {
        int n = needle.size();
        vector<int> lps(n, 0);
        // pre stores the length of longest prefix which
        // is also a suffix for the previous index
        int pre = 0;
        for (int i = 1; i < n; ++i) {
            while (pre > 0 && needle[i] != needle[pre]) {
                pre = lps[pre-1];
            }
            if (needle[i] == needle[pre]) {
                lps[i] = ++pre;
            }
        }
        return lps;
    }
};
