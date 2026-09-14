class Solution {
public:
    
    /*
    Before we do it in 2D plane, let's try it in 1D.
    Given 2 segment (left1, right1), (left2, right2), how can we check whether they overlap?
    If these two intervals overlap, it should exist an number x,

    left1 < x < right1 && left2 < x < right2

    left1 < x < right2 && left2 < x < right1

    left1 < right2 && left2 < right1

    This is the sufficient and necessary condition for two segments overlap.

    */
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        int x1 = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];
        int x3 = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];
        return (x1 < x4 && x3 < x2 && y1 < y4 && y3 < y2);
    }
};
