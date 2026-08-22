class Solution {
public:
    // bottom-up Time: O(n^2) Space: O(n)
    int minimumTotal_bu(vector<vector<int>>& triangle) {
        vector<int> res = triangle.back();
        for (int i = triangle.size() - 2; i >= 0; i--) 
            for (unsigned int j = 0; j <= i; j++) 
                res[j] = triangle[i][j] + min(res[j], res[j+1]);
        return res[0];
    }
    
    
    // DP bottom-up Time: O(n^2) Space: O(1)
    int minimumTotal(vector<vector<int>>& triangle) {
        for (int i = triangle.size() - 2; i >= 0; i--) 
            for (unsigned int j = 0; j <= i; j++) 
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
        return triangle[0][0];
    }
};
