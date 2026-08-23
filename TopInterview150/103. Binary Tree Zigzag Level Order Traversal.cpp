class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;

        if (!root) {
            return result;
        }

        queue<TreeNode*> q;
        q.push(root);

        // true  -> fill row left to right
        // false -> fill row right to left
        bool leftToRight = true;

        while (!q.empty()) {
            int levelSize = q.size();

            // Preallocate current level.
            vector<int> level(levelSize);

            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();

                /*
                 * Normal level:
                 *
                 * i = 0,1,2...
                 *
                 * store at:
                 *
                 * 0,1,2...
                 *
                 *
                 * Reverse level:
                 *
                 * i = 0,1,2...
                 *
                 * store at:
                 *
                 * size-1, size-2, ...
                 */
                int index =
                    leftToRight
                    ? i
                    : levelSize - 1 - i;

                level[index] = node->val;

                /*
                 * IMPORTANT:
                 * We still push children normally:
                 *
                 * left first
                 * right second
                 *
                 * Only the output position changes.
                 */
                if (node->left) {
                    q.push(node->left);
                }

                if (node->right) {
                    q.push(node->right);
                }
            }

            result.push_back(level);

            // Reverse direction for next level.
            leftToRight = !leftToRight;
        }

        return result;
    }
};
