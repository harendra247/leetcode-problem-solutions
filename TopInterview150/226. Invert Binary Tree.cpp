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
    // Recursive Time: O(n) Space: O(H)
    TreeNode* invertTree_(TreeNode* root) {
        if (root) {
            invertTree(root->left);
            invertTree(root->right);
            std::swap(root->left, root->right);
        }
        return root;
    }
    
    
    // Iterative Time: O(n) Space: O(D)
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr)
            return nullptr;
        std::queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            std::swap(current->left, current->right);
            
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
        return root;
    }
};
