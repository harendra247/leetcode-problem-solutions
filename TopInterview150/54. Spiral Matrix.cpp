class Solution {
public:
    // Time: O(n^2) Space: O(n^2)
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<int>  res;
        int l = 0, r = n-1;
        int t = 0, b = m-1;
        
        int dir = 0; //0 - left to right, 1 - top to bottom, 2 - right to left, 3 - bottom to top
        
        while (res.size() < m*n) {
            // left to right
            if (dir == 0) {
                for (int i = l; i <= r; i++) {
                   res.push_back(matrix[t][i]); 
                }
                
                t++;
            } else if (dir == 1) { // top to bottom
                for (int i = t; i <= b; i++) {
                   res.push_back(matrix[i][r]); 
                }
                
                r--;
            } else if (dir == 2) { // rigth to left
                for (int i = r; i >= l; i--) {
                   res.push_back(matrix[b][i]); 
                }
                
                b--;
            } else if (dir == 3) { // bottom to top
                for (int i = b; i >= t; i--) {
                   res.push_back(matrix[i][l]); 
                }
                
                l++;
            }
            
            dir++;
            dir = dir%4;
        }
        return res; 
    }
};
