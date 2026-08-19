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

    // Time: O(n) Sapce: O(n)
    bool isSymmetric(TreeNode* root) {
        return isMirrorIterative(root);
        // return isMirrorR(root, root);
    }

    bool isMirrorR(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) 
            return true;
        if (!t1 || !t2 || (t1->val == t2->val)) 
            return false;
        return isMirrorR(t1->right, t2->left) && isMirrorR(t1->left, t2->right);
    }

    bool isMirrorIterative(TreeNode *root) {
        if (!root)
            return true;
        
        std::queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);

        while (!q1.empty() && !q2.empty()) {
            TreeNode *left = q1.front(); 
            q1.pop();
            
            TreeNode *right = q2.front(); 
            q2.pop();
            
            if (!left && !right)
                continue;
            if (!left || !right || (left->val != right->val))
                return false;
            
            q1.push(left->left);
            q1.push(left->right);
            q2.push(right->right);
            q2.push(right->left);
        }
        
        return true;    
    }
};
