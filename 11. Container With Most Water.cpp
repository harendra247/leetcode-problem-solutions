class Solution {
public:
    
    // Time: O(n) Space: O(1)
    int maxArea(vector<int>& height) {
        int water = 0;
        int i = 0, j = height.size() - 1;
        while (i < j) {
            int h = min(height[i], height[j]);
            water = max(water, (j - i) * h);
            while (height[i] <= h && i < j) 
                i++;
            while (height[j] <= h && i < j) 
                j--;
        }
        return water;
    } 
    
    // Time: O(n) Space: O(1)
    int maxArea_(vector<int>& height) {
        int water = 0, l = 0, r = height.size() - 1;
        while (l < r) {
            int h = min(height[l], height[r]);
            water = max(water, (r - l) * h);
            if (height[l] < height[r])
                l++;
            else
                r--;
        }
        return water;
    }
};
