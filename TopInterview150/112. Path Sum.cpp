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
    // Recursive Time: O(n) Space: O(n)
    bool hasPathSum_r(TreeNode* root, int sum) {
        if (!root) { 
            return false; 
        }
        sum -= root->val;
        if (0 == sum && root->left == nullptr && root->right == nullptr) 
            return true;
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);        
    }
    
    
    // iterative Time: O(n) Space: O(n)
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) { 
            return false; 
        }
        std::queue<pair<TreeNode*, int>> node_stack;
        node_stack.push({root, sum - root->val});

        int curr_sum;
        while (!node_stack.empty()) {
            auto [node, curr_sum] = node_stack.front(); // TreeNode* node
            node_stack.pop();
            
            if ((node->right == nullptr) && (node->left == nullptr) && (curr_sum == 0))
                return true;

            if (node->right) {
                node_stack.push({node->right, curr_sum - node->right->val});
            }
            
            if (node->left) {
                node_stack.push({node->left, curr_sum - node->left->val});
            }
        }
        return false;        
    }
};
