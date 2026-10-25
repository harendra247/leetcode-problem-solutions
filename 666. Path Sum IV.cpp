class Solution {
public:
    
    // Time : O(n) Space : O(n)
    int pathSum_(vector<int>& nums) {
        int m[5][8] = {};
        for (int n : nums) {
            int i = n / 100; // i is 1 based index;
            int j = (n % 100) / 10 - 1; // j used 0 based index;
            int v = n % 10;
            m[i][j] = m[i - 1][j / 2] + v;
        }

        int sum = 0;
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == 4 || m[i][j] && !m[i + 1][j * 2] && !m[i + 1][j * 2 + 1]){
                    sum += m[i][j];
                }
            }
        }
        return sum;
    }
    
    // Time: O(n) Space: O(n)
    int pathSum(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        unordered_map<int, int> tree;
        tree.reserve(nums.size());

        for (int num : nums) {
            tree[num / 10] = num % 10;
        }

        return traverse(nums[0] / 10, 0, tree);
    }

    int traverse(int node, int pathSum,
                const unordered_map<int, int>& tree) {
        int depth = node / 10;
        int position = node % 10;

        int left = (depth + 1) * 10 + 2 * position - 1;
        int right = left + 1;

        pathSum += tree.at(node);

        bool hasLeft = tree.count(left) > 0;
        bool hasRight = tree.count(right) > 0;

        // A leaf contributes one complete root-to-leaf path.
        if (!hasLeft && !hasRight) {
            return pathSum;
        }

        int total = 0;

        if (hasLeft) {
            total += traverse(left, pathSum, tree);
        }

        if (hasRight) {
            total += traverse(right, pathSum, tree);
        }

        return total;
    }
};
