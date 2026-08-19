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
    // Recur Time: O(logn * logn) Sapce: O(logn)
    int countNodes(TreeNode* root) {
        if (!root) 
            return 0;

        int hl = 0, hr = 0;

        TreeNode *l = root, *r = root;

        while (l) { 
            hl++;
            l = l->left;
        }

        while (r) {
            hr++;
            r = r->right;
        }

        if (hl == hr) 
            return (1 << hl) - 1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    // Iterative Time: O(logn * logn) Sapce: O(1)
    int countNodes_i(TreeNode* root) {
        if (!root) return 0;
        TreeNode *temp = root;
        int height = 0, count = 0, level;
        while (temp) {
            temp = temp->left;
            height ++;
        }
        temp = root;
        level = height - 2;
        while (level >= 0) {
            TreeNode *left = temp->left;
            for (int i = 0; i < level; ++i) {
                left = left->right;
            }
            if (left) {
                temp = temp->right;
                count += (1 << level);
            } else  { 
                temp = temp->left; 
            }
            level--;
        }
        if (temp) 
            count ++;
        return (1 << (height - 1)) + count - 1;
    }
    
    // Return tree depth in O(d) time.
    int computeDepth(TreeNode* node) {
        int d = 0;
        while (node->left) {
            node = node->left;
            ++d;
        }
        return d;
    }

    // Last level nodes are enumerated from 0 to 2**d - 1 (left -> right).
    // Return True if last level node idx exists. 
    // Binary search with O(d) complexity.
    bool exists(int idx, int d, TreeNode* node) {
        int left = 0, right = pow(2, d) - 1;
        int pivot;
        for (int i = 0; i < d; ++i) {
            pivot = left + (right - left) / 2;
            if (idx <= pivot) {
                node = node->left;
                right = pivot;
            } else {
                node = node->right;
                left = pivot + 1;
            }
        }
        return node != nullptr;
    }

    int countNodes_b(TreeNode* root) {
        // if the tree is empty
        if (!root) return 0;

        int d = computeDepth(root);
        // if the tree contains 1 node
        if (d == 0) return 1;

        // Last level nodes are enumerated from 0 to 2**d - 1 (left -> right).
        // Perform binary search to check how many nodes exist.
        int left = 1, right = pow(2, d) - 1;
        int pivot;
        while (left <= right) {
            pivot = left + (right - left) / 2;
            if (exists(pivot, d, root)) left = pivot + 1;
            else right = pivot - 1;
        }

        // The tree contains 2**d - 1 nodes on the first (d - 1) levels
        // and left nodes on the last level.
        return pow(2, d) - 1 + left; 
    }
};
