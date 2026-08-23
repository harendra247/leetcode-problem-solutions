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
    // BFS
    // Time: O(n)
    // Space: O(n)
    vector<vector<int>> levelOrder_(TreeNode* root) {
        vector<vector<int>> res;

        if (!root)
            return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            // Number of nodes in current level
            int levelSize = q.size();

            vector<int> level;

            // Process exactly one level
            for (int i = 0; i < levelSize; ++i) {

                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                // These children belong to NEXT level
                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);
            }

            res.push_back(level);
        }

        return res;
    }
    
public:
    // DFS
    // Time: O(n)
    // Space: O(h) recursion stack + output
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;

        dfs(root, 0, result);

        return result;
    }

private:
    void dfs(TreeNode* node, int level, vector<vector<int>>& result) {
        if (node == nullptr) {
            return;
        }

        /*
         * First time reaching this level:
         * create storage for it.
         */
        if (level == result.size()) {
            result.push_back({});
        }

        // Add current node to its level.
        result[level].push_back(node->val);

        // Children belong to next level.
        dfs(node->left, level + 1, result);
        dfs(node->right, level + 1, result);
    }
};
