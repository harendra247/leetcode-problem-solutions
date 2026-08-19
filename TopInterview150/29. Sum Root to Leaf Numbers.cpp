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
    
    // Recursive Time: O(n) Space: O(h)
    int sumNumbers_(TreeNode* root) {
        int sum = 0, cursum = 0;
        dfs(root, cursum, sum);
        return sum;
    }
    
    void dfs(TreeNode * root, int tmp, int &sum) {
        if (!root) { 
            return;
        } else if (!(root->left) && !(root->right)) {
            sum += tmp * 10 + root->val;
            return;
        }
        
        dfs(root->left, tmp * 10 + root->val, sum);
        dfs(root->right, tmp * 10 + root->val, sum);
    }
    
    // Iterative Time: O(n) Space: O(h)
    int sumNumbers(TreeNode* root) {
        stack<pair<TreeNode*, int>> dfs;

        if (root) {
            dfs.push({root, 0});
        }

        int answer = 0;

        while (!dfs.empty()) {
            const auto [node, value] = dfs.top();
            const int current_value = value * 10 + node->val;
            dfs.pop();

            if (!node->left && !node->right) {
                answer += current_value;
            } else {
                if (node->left) {
                    dfs.push({node->left, current_value});
                }

                if (node->right) {
                    dfs.push({node->right, current_value});
                }
            }
        }

        return answer;
    }
};
