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
    TreeNode* build(vector<int>& postorder, int &postIndex, int inorderStart, int inorderEnd, unordered_map<int, int> &inorderIndex) {
        if (inorderStart > inorderEnd) {
            return nullptr;
        }

        /*
         * In postorder, current root is taken
         * from the END.
         */
        int rootValue = postorder[postIndex--];

        TreeNode* root = new TreeNode(rootValue);

        int mid = inorderIndex[rootValue];

        /*
         * IMPORTANT:
         *
         * Since we consume postorder from RIGHT to LEFT:
         *
         * postorder reversed looks like:
         *
         * root -> right subtree -> left subtree
         *
         * So we MUST build RIGHT before LEFT.
         */
        root->right = build(postorder, postIndex, mid + 1, inorderEnd, inorderIndex);

        root->left = build(postorder, postIndex, inorderStart, mid - 1, inorderIndex);

        return root;
    }

public:
    // Time: O(n)
    // Space: O(n)
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        unordered_map<int, int> inorderIndex;

        for (int i = 0; i < n; ++i) {
            inorderIndex[inorder[i]] = i;
        }

        int postIndex = n - 1;

        return build(postorder, postIndex, 0, n - 1, inorderIndex);
    }
};
