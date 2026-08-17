class Solution {
public:
    // Time: O(n^2) Space: O(1) 
    void rotate_(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int i = 0;
        int j = n-1;
        while (i<j) {
            for (int k=0;k<(j-i);++k) {
                swap(matrix[i][i+k], matrix[i+k][j]);
                swap(matrix[i][i+k], matrix[j][j-k]);
                swap(matrix[i][i+k], matrix[j-k][i]);
            }
            ++i;
            --j;
        }
    }
    

public:
    // Time: O(n^2)
    // Space: O(1)
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // 1. Transpose across the main diagonal.
        for (int r = 0; r < n; ++r) {
            for (int c = r + 1; c < n; ++c) {
                swap(matrix[r][c], matrix[c][r]);
            }
        }

        // 2. Reverse every row.
        for (auto& row : matrix) {
            reverse(row.begin(), row.end());
        }
    }
};
