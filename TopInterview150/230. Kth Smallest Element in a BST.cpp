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
    // Time: O(n) worst case
    // Space: O(H) recursion stack
    int kthSmallest(TreeNode* root, int& k) {
        if (root == nullptr) {
            return 0;
        }

        // STEP 1:
        // Search smaller values first.
        int leftAnswer = kthSmallest(root->left, k);

        /*
         * If k became 0 somewhere in the left subtree,
         * the kth smallest element was already found.
         *
         * So simply propagate that answer upward.
         */
        if (k == 0) {
            return leftAnswer;
        }

        // STEP 2:
        // Visit current node.
        //
        // Since inorder traversal is sorted,
        // this is the next smallest element.
        --k;

        // If k becomes 0, current node is
        // exactly the kth smallest.
        if (k == 0) {
            return root->val;
        }

        // STEP 3:
        // kth element hasn't been found yet,
        // so search larger values.
        return kthSmallest(root->right, k);
    }

    // Time: O(H + k) average, O(n) worst case
    // Space: O(H)
    int kthSmallest_i(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* p = root;

        while (p || !st.empty()) {

            // Step 1: go as far LEFT as possible.
            if (p) {
                st.push(p);
                p = p->left;
                continue;
            }

            // Step 2: no more left nodes.
            // The top of the stack is the next node
            // in inorder traversal.
            p = st.top();

            // Visiting this node means we've found
            // one more smallest element.
            if (--k == 0) {
                return p->val;
            }

            st.pop();

            // Step 3: after visiting the node,
            // explore its RIGHT subtree.
            p = p->right;
        }

        return 0;
    }
};
