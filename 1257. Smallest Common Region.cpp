class Solution {
private:
    /*
     * Returns path:
     *
     * root -> ... -> currNode
     *
     * Example:
     *
     * Earth -> North America -> USA -> New York
     */
    vector<string> fetchPathForRegion(string currNode, unordered_map<string, string>& parent) {
        vector<string> path;

        /*
         * Start from current region and move upward.
         *
         * Initially path is built backwards:
         *
         * current -> parent -> grandparent -> ... -> root
         */
        path.push_back(currNode);

        while (parent.find(currNode) != parent.end()) {
            currNode = parent[currNode];
            path.push_back(currNode);
        }

        /*
         * Convert:
         *
         * node -> ... -> root
         *
         * into:
         *
         * root -> ... -> node
         */
        reverse(path.begin(), path.end());

        return path;
    }

public:
    // Let R = total number of region relationships.
    //
    // Time:  O(R + H)
    // Space: O(R + H)
    //
    // H = tree height
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
        /*
         * child -> parent
         *
         * Example:
         *
         * USA -> North America
         * Canada -> North America
         */
        unordered_map<string, string> parent;

        /*
         * Build parent relationships.
         *
         * Each regionArray looks like:
         *
         * [parent, child1, child2, ...]
         */
        for (auto& group : regions) {
            string parentRegion = group[0];

            for (int i = 1; i < group.size(); ++i) {
                parent[group[i]] = parentRegion;
            }
        }

        /*
         * Build root-to-node paths.
         */
        vector<string> path1 = fetchPathForRegion(region1, parent);

        vector<string> path2 = fetchPathForRegion(region2, parent);

        string lca;

        /*
         * Both paths start at the same root.
         *
         * Keep moving while they are equal.
         *
         * The last common region is the LCA.
         */
        int i = 0;

        while (i < path1.size() && i < path2.size() && path1[i] == path2[i]) {

            lca = path1[i];
            ++i;
        }

        return lca;
    }
};
