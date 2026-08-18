class Solution {
private:
    void inorder(TreeNode* node, TreeNode*& prev, int& minDiff) {
        if (node == nullptr) {
            return;
        }

        // 1. Visit smaller values first.
        inorder(node->left, prev, minDiff);

        /*
         * Inorder traversal of a BST is sorted.
         *
         * So 'prev' is the immediately previous
         * value in sorted order.
         *
         * Example:
         *
         * inorder = [1, 3, 6, 10]
         *
         * We only need:
         *
         * 3 - 1
         * 6 - 3
         * 10 - 6
         *
         * The minimum difference must occur
         * between two adjacent sorted values.
         */
        if (prev != nullptr) {
            minDiff = min(minDiff, node->val - prev->val);
        }

        // Current node becomes previous node
        // for the next inorder element.
        prev = node;

        // 3. Visit larger values.
        inorder(node->right, prev, minDiff);
    }

public:
    // Time: O(n)
    // Space: O(h) recursion stack
    int getMinimumDifference(TreeNode* root) {
        TreeNode* prev = nullptr;
        int minDiff = INT_MAX;

        inorder(root, prev, minDiff);

        return minDiff;
    }
};
