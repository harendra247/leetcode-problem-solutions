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
    // Rec Time: O(n) Space: O(logn)
    int maxDepth_rec(TreeNode* root) {
        if (root == nullptr) 
            return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(left, right) + 1;
    }
    
    // Time: O(n) Space: O(logn)
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        vector<pair<int, TreeNode*>> my_stack;
        my_stack.push_back({1, root});
        int max_depth = 0;
        while (!my_stack.empty()) {
            auto my_pair = my_stack.back();
            int c_depth = my_pair.first;
            TreeNode* c_node = my_pair.second;
            max_depth = max(max_depth, c_depth);
            my_stack.pop_back();
            if (c_node->left) {
                my_stack.push_back({c_depth + 1, c_node->left});
            }
            if (c_node->right) {
                my_stack.push_back({c_depth + 1, c_node->right});
            }
        }
        return max_depth;
    }
};
