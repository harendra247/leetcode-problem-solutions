class Solution {
public:
    
    // Greedy Time: O(n) Space: O(1)
    bool canJump_(vector<int>& arr) {
        int reachable = 0;
        
        for (int i = 0; i < arr.size(); ++i) {
            if (reachable < i) { 
                return false;
            }
            reachable = max (reachable, i + arr[i]);
        }
        
        return true;
    }

    // https://www.youtube.com/watch?v=Yan0cv2cLy8
    // Greedy Time: O(n) Space: O(1)
    bool canJump(vector<int>& arr) {
        int goal = arr.size()-1; //start from end and move the goal post to left
        
        for (int i = arr.size()-2; i >= 0; i--) {
            if (i + arr[i] >= goal) { 
                goal = i;
            }
        }
        
        return goal == 0 ? true: false;
    }
};
