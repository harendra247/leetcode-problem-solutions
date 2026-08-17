class Solution {
public:
    // DP Time: O(n) Space: O(n)
    int trap_dp(vector<int>& height) {
        if (height.empty())
            return 0;
        int water = 0;
        int size = height.size();
        vector<int> left_max(size), right_max(size);
        
        left_max[0] = height[0];
        for (int i = 1; i < size; i++) {
            left_max[i] = max(height[i], left_max[i - 1]);
        }

        right_max[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            right_max[i] = max(height[i], right_max[i + 1]);
        }
        
        for (int i = 1; i < size - 1; i++) {
            water += min(left_max[i], right_max[i]) - height[i];
        }
        return water;
    }
    
    // Two pointer Time: O(n) Space: O(1)
    int trap_(vector<int>& height) {
        int l = 0, r = height.size() - 1, water = 0, minHeight = 0;
        while (l < r) {
            while (l < r && height[l] <= minHeight) {
                water += minHeight - height[l++];
            }
            while (l < r && height[r] <= minHeight) {
                water += minHeight - height[r--];
            }
            minHeight = min(height[l], height[r]);
        }
        return water;
    }
    /*
    1130. Minimum Cost Tree From Leaf Values
    907. Sum of Subarray Minimums
    901. Online Stock Span
    856. Score of Parentheses
    503. Next Greater Element II
    496. Next Greater Element I
    84. Largest Rectangle in Histogram
    42. Trapping Rain Water
    */
    
    // Monotonic stack approach Time: O(n) Space: O(n)
    int trap(vector<int>& height) {
        int water = 0;
        stack<int> st;
        for(int i = 0; i < height.size(); i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int top = st.top();
                st.pop();
                if (st.empty())
                    break;
                int distance = i - st.top() - 1;
                int bounded_height = min(height[i], height[st.top()]) - height[top];
                water += distance * bounded_height;
            }
            st.push(i);
        }
        return water;  
    }
};
