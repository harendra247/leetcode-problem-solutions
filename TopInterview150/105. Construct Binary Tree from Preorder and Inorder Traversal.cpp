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
private:
    TreeNode* build(vector<int>& preorder, int & preorderIndex, int inorderStart, int inorderEnd, unordered_map<int, int> &inorderIndex) {
        if (inorderStart > inorderEnd) {
            return nullptr;
        }

        int rootValue = preorder[preorderIndex++];
        TreeNode* root = new TreeNode(rootValue);

        int mid = inorderIndex[rootValue];

        root->left = build(preorder, preorderIndex, inorderStart, mid - 1, inorderIndex);

        root->right = build(preorder, preorderIndex, mid + 1, inorderEnd, inorderIndex);

        return root;
    }

public:
    // Time: O(n)
    // Space: O(n)
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderIndex;
        for (int i = 0; i < inorder.size(); ++i) {
            inorderIndex[inorder[i]] = i;
        }

        int preorderIndex = 0;

        return build(preorder, preorderIndex, 0, inorder.size() - 1, inorderIndex);
    }
};
