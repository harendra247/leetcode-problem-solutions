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
    // Time: O(n) Space: O(D)
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            long sum = 0;
            int s = q.size();
            for(int i = 0; i < s; i++) {
                TreeNode* t = q.front();
                q.pop();
                if(t->left) 
                    q.push(t->left);
                if(t->right) 
                    q.push(t->right);
                sum += t->val;
            }
            res.push_back((double)sum / s);
        }
        return res;        
    }
};
