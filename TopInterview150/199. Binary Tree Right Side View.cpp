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
    // BFS Time: O(n) Space: O(D) (diameter of tree) 
    vector<int> rightSideView_(TreeNode* root) {
        if (!root) 
            return {};
        
        queue<TreeNode*> q;
        vector<int> res;
        q.push(root);
        
        while (!q.empty()) {
            int n = q.size();
            TreeNode* t = q.front();
            res.push_back(t->val);
            while (n > 0) {
                t = q.front();
                q.pop();
                
                if (t->right) 
                    q.push(t->right);
                if (t->left) 
                    q.push(t->left);
                n--;
            }
        }
        
        return res;
    }
    
    // DFS  Time: O(n) Space: O(H) (height of tree) 
    void recursion(TreeNode *root, int level, vector<int> &res) {
        if (!root) 
            return;
        if (res.size() < level) 
            res.push_back(root->val);
        recursion(root->right, level + 1, res);
        recursion(root->left, level + 1, res);
    }
    
    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        recursion(root, 1, res);
        return res;  
    }
};
