/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    // DFS
    //
    // n = number of nodes
    // e = number of edges
    //
    // Time:  O(n + e)
    // Space: O(n)
    Node* cloneGraph(Node* node) {

        /*
         * copies maps:
         *
         * original node -> cloned node
         *
         * Example:
         *
         * Original      Clone
         *
         * Node1   ->    Node1'
         * Node2   ->    Node2'
         * Node3   ->    Node3'
         *
         * It also tells us whether a node
         * has already been cloned.
         */
        unordered_map<Node*, Node*> copies;

        return dfs(node, copies);
    }

private:
    Node* dfs(Node* node, unordered_map<Node*, Node*>& copies) {
        /*
         * Empty graph / neighbor.
         */
        if (!node) {
            return nullptr;
        }

        /*
         * If this node was already cloned,
         * don't create another copy.
         *
         * This is especially important for cycles.
         */
        if (copies.find(node) != copies.end()) {
            return copies[node];
        }

        /*
         * Create the cloned node.
         *
         * IMPORTANT:
         * Put it into the map BEFORE recursively
         * cloning its neighbors.
         */
        copies[node] = new Node(node->val, {});

        /*
         * Clone every neighbor of the original node
         * and connect those cloned neighbors to
         * our cloned node.
         */
        for (Node* neighbor : node->neighbors) {

            Node* clonedNeighbor = dfs(neighbor, copies);

            copies[node]->neighbors.push_back(clonedNeighbor);
        }

        return copies[node];
    }
    
public:
    // BFS
    //
    // n = number of nodes
    // e = number of edges
    //
    // Time:  O(n + e)
    // Space: O(n)
    Node* cloneGraph_b(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        /*
         * Map original node -> cloned node.
         *
         * It tells us:
         * 1. whether a node has already been cloned
         * 2. where its clone is
         */
        unordered_map<Node*, Node*> copies;

        /*
         * Clone the starting node first.
         */
        Node* copy = new Node(node->val, {});

        copies[node] = copy;

        /*
         * BFS queue stores ORIGINAL nodes
         * whose neighbors still need to be processed.
         */
        queue<Node*> q;

        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            /*
             * Process every neighbor of current.
             */
            for (Node* neighbor : current->neighbors) {

                /*
                 * If neighbor has not been cloned yet:
                 *
                 * 1. create its clone
                 * 2. save it in the map
                 * 3. push original neighbor into queue
                 *    so its adjacency list gets processed later
                 */
                if (copies.find(neighbor) == copies.end()) {
                    copies[neighbor] = new Node(neighbor->val, {});

                    q.push(neighbor);
                }

                /*
                 * Connect cloned current node
                 * to cloned neighbor.
                 *
                 * Original:
                 *
                 * current ------> neighbor
                 *
                 * Clone:
                 *
                 * copies[current] ------> copies[neighbor]
                 */
                copies[current]->neighbors.push_back(
                    copies[neighbor]
                );
            }
        }

        /*
         * Return clone of original starting node.
         */
        return copy;
    }
};
