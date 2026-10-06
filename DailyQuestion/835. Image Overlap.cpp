class Solution {
public:
    // A = number of 1s in img1 B = number of 1s in img2 
    // Time  = O(n² + A × B) Space = O(A + B)
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        int n = img1.size();

        vector<pair<int, int>> ones1;
        vector<pair<int, int>> ones2;

        // Store the coordinates of all 1s in both images.
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (img1[row][col] == 1) {
                    ones1.push_back({row, col});
                }

                if (img2[row][col] == 1) {
                    ones2.push_back({row, col});
                }
            }
        }

        /*
            For every pair of 1s, calculate the translation needed
            to move the 1 in img2 onto the 1 in img1.

            If the same translation occurs multiple times, all those
            pixels can overlap after applying that translation.
        */
        unordered_map<int, int> shiftCount;

        int maxOverlap = 0;

        for (auto [row1, col1] : ones1) {
            for (auto [row2, col2] : ones2) {

                int rowShift = row1 - row2;
                int colShift = col1 - col2;

                /*
                    Encode (rowShift, colShift) into a single integer.

                    Shifts are in the range:
                        -(n - 1) ... (n - 1)

                    So 2 * n + 1 is enough to uniquely encode
                    both coordinates.
                */
                int key = (rowShift + n) * (2 * n + 1)
                        + (colShift + n);

                ++shiftCount[key];

                maxOverlap = max(maxOverlap, shiftCount[key]);
            }
        }

        return maxOverlap;
    }
};
