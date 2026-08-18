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
    // Inorder traversal
    //
    // Time:  O(n)
    // Space: O(H) recursion stack
    //
    // H = height of tree
    bool isValidBST(TreeNode* root) {

        /*
         * prev stores the previously visited node
         * in inorder traversal.
         *
         * Since inorder of a valid BST must be
         * strictly increasing:
         *
         * prev->val < current->val
         */
        TreeNode* prev = nullptr;

        return validate(root, prev);
    }

private:
    bool validate(TreeNode* node, TreeNode*& prev) {
        // Empty tree/subtree is valid.
        if (node == nullptr) {
            return true;
        }

        /*
         * STEP 1:
         * Validate left subtree first.
         *
         * Inorder:
         *
         * LEFT -> NODE -> RIGHT
         */
        if (!validate(node->left, prev)) {
            return false;
        }


        /*
         * STEP 2:
         * Visit current node.
         *
         * 'prev' is the immediately previous node
         * in inorder traversal.
         *
         * For a valid BST:
         *
         * prev->val < node->val
         *
         * If:
         *
         * node->val <= prev->val
         *
         * then inorder is not strictly increasing,
         * so this cannot be a valid BST.
         */
        if (prev != nullptr && node->val <= prev->val) {

            return false;
        }


        /*
         * Current node becomes the previous node
         * for the next inorder element.
         */
        prev = node;


        /*
         * STEP 3:
         * Validate right subtree.
         */
        return validate(node->right, prev);
    }

private:
    bool validate(TreeNode* root, TreeNode* low, TreeNode* high) {
        // Empty subtree is a valid BST.
        if (root == nullptr) {
            return true;
        }

        /*
         * Check LOWER bound.
         *
         * If low exists:
         *
         *      root->val > low->val
         *
         * must be true.
         */
        if (low != nullptr && root->val <= low->val) {
            return false;
        }

        /*
         * Check UPPER bound.
         *
         * If high exists:
         *
         *      root->val < high->val
         *
         * must be true.
         */
        if (high != nullptr && root->val >= high->val) {
            return false;
        }

        /*
         * RIGHT subtree:
         *
         * Everything must be:
         *
         *      root->val < value < high->val
         *
         * Therefore current root becomes
         * the new LOWER bound.
         */
        bool rightValid = validate(root->right, root, high);

        if (!rightValid) {
            return false;
        }

        /*
         * LEFT subtree:
         *
         * Everything must be:
         *
         *      low->val < value < root->val
         *
         * Therefore current root becomes
         * the new UPPER bound.
         */
        bool leftValid = validate(root->left, low, root);

        return leftValid;
    }

public:
    // Time:  O(n)
    // Space: O(H)
    bool isValidBST_(TreeNode* root) {
        // Root initially has no lower or upper bound.
        return validate(root, nullptr, nullptr);
    }

    // Iterative inorder traversal
    //
    // Time:  O(n)
    // Space: O(H)
    // H = height of the tree
    bool isValidBST_itr_inorder(TreeNode* root) {

        // Stack manually simulates the recursion stack.
        stack<TreeNode*> st;

        // Previous node visited during inorder traversal.
        TreeNode* prev = nullptr;

        while (root != nullptr || !st.empty()) {

            /*
             * STEP 1: Go as far LEFT as possible.
             *
             * Inorder traversal:
             *
             *      LEFT -> NODE -> RIGHT
             *
             * We cannot process the current node until
             * its entire left subtree has been processed.
             */
            if (root != nullptr) {
                st.push(root);
                root = root->left;
                continue;
            }

            /*
             * STEP 2: Visit the node.
             *
             * We reached nullptr on the left,
             * so the stack top is the next node
             * in inorder order.
             */
            root = st.top();
            st.pop();

            /*
             * For a valid BST, inorder values must be
             * STRICTLY increasing:
             *
             * prev->val < root->val
             *
             * Therefore:
             *
             * root->val <= prev->val
             *
             * means the BST is invalid.
             */
            if (prev != nullptr &&
                root->val <= prev->val) {
                return false;
            }

            // Current node becomes previous node
            // for the next inorder element.
            prev = root;

            /*
             * STEP 3: Process the RIGHT subtree.
             */
            root = root->right;
        }

        return true;
    }
};
