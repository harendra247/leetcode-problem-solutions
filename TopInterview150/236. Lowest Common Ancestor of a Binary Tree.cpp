/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    // Time: O(n) Space: O(n)
    TreeNode* lowestCommonAncestor_(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) 
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        return !left ? right : !right ? left : root;
    }
    
    
    struct Frame {
        TreeNode* node;
        Frame* parent;
        vector<TreeNode*> subs;
    };
    
public:
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        Frame answer;
        stack<Frame> Stack;
        Stack.push({root, &answer});
        while (Stack.size()) {
            Frame *top = &Stack.top(), *parent = top->parent;
            TreeNode *node = top->node;
            if (!node || node == p || node == q) {
                parent->subs.push_back(node);
                Stack.pop();
            } else if (top->subs.empty()) {
                Stack.push({node->right, top});
                Stack.push({node->left, top});
            } else {
                TreeNode *left = top->subs[0], *right = top->subs[1];
                parent->subs.push_back(!left ? right : !right ? left : node);
                Stack.pop();
            }
        }
        return answer.subs[0];    
    }
};
