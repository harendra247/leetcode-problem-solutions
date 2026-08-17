class Solution {
public:
    
    // counting sort: Time: O(n) Space: O(n)
    int hIndex1(vector<int>& citations) {
        if (citations.empty())
            return 0;
        int n = citations.size();
        vector<int> papers(n + 1, 0);
        // counting papers for each citation number
        for (int i = 0; i < n; ++i) {
            if (citations[i] >= n)
                papers[n]++;
            else
                papers[citations[i]]++;
        }
        int hindex = 0;
        for (int i = n; i >= 0; --i) {
            hindex += papers[i];
            if (hindex >= i)
                return i;
        }
        return 0;
    }
    
    
    // Time: O(nlogn) Space: O(1)
    int hIndex_(vector<int>& citations) {
        // sorting the citations in ascending order
        sort(citations.begin(), citations.end());
        // finding h-index by linear search
        // int i = 0;
        // while (i < citations.size() && citations[citations.size() - 1 - i] > i) {
        //     i++;
        // }
        // return i; // after the while loop, i = i' + 1
        
        int n = citations.size();
        int left = 0, right = n - 1;

        while (left <= right) {
            int h = left + (right - left) / 2;
            if (citations[h] == n-h) {
                return citations[h];
            } else if (citations[h] > n-h) {
                right = h - 1;
            } else {
                left = h + 1;
            }
        }

        return n - left;
    }


    // Time: O(nlogn) Space: O(1)
    int hIndex(vector<int>& citations) {
        // sorting the citations in ascending order
        sort(citations.begin(), citations.end());
        // finding h-index by linear search
        int n = citations.size();
        for (int i = 0; i < n; ++i) {
            int hindex = n - i;
            if (hindex <= citations[i])
                return hindex;
        }
        return 0;
    }
};
