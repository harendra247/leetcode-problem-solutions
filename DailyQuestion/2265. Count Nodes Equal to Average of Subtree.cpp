/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        int ans = 0;
        postOrder(root, ans);
        return ans;
    }

    pair<int, int> postOrder(TreeNode* root, int & count) {
        if (!root) {
            return {0, 0};
        } else if(!(root->left || root->right)) {
            count++;
            return {root->val, 1};
        } else {
            auto [leftsum, leftcount] =  postOrder(root->left, count);
            auto [rightsum, rightcount] =  postOrder(root->right, count);

            int sum = leftsum + rightsum + root->val;
            int nodecount = leftcount + rightcount + 1;
            int avg = sum / nodecount;
            if (avg == root->val) {
                count++;
            }
            return {sum, nodecount};
        }
    }
};
