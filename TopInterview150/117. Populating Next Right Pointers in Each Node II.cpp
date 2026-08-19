/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    // Time: O(n)
    // Space: O(w)
    // w = maximum width of the tree
    Node* connect_it(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            Node* prev = nullptr;

            /*
             * Process exactly one level.
             *
             * Example:
             *
             *        1
             *      /   \
             *     2     3
             *    / \     \
             *   4   5     7
             *
             * Level 2 contains:
             *
             * 2 -> 3 -> nullptr
             */
            for (int i = 0; i < levelSize; ++i) {
                Node* curr = q.front();
                q.pop();

                /*
                 * Connect previous node in this level
                 * to current node.
                 */
                if (prev != nullptr) {
                    prev->next = curr;
                }

                prev = curr;

                /*
                 * Add children for the NEXT level.
                 */
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }

                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }

            /*
             * Last node of every level must point to nullptr.
             */
            prev->next = nullptr;
        }

        return root;
    }
    
    // Time:  O(n)
    // Space: O(1)
    Node* connect(Node* root) {
        /*
        * cur:
        *     Current node we are visiting.
        *
        * head:
        *     First node of the NEXT level.
        *     We need this so that after finishing the current
        *     level, we know where the next level starts.
        *
        * tail:
        *     Last node connected in the NEXT level.
        *     New children are attached after tail.
        */
        Node* cur = root;
        Node* head = nullptr;
        Node* tail = nullptr;

        while (cur != nullptr) {

            /*
            * Process cur->left.
            *
            * We are building the linked list for
            * the NEXT level.
            */
            if (cur->left != nullptr) {

                if (tail != nullptr) {
                    /*
                    * We already have at least one node
                    * in the next level.
                    *
                    * Connect:
                    *
                    * tail -> cur->left
                    */
                    tail->next = cur->left;

                    // cur->left is now the new last node.
                    tail = tail->next;
                }
                else {
                    /*
                    * This is the FIRST node discovered
                    * for the next level.
                    *
                    * Therefore it is both:
                    *
                    * head = first node
                    * tail = last node
                    */
                    head = cur->left;
                    tail = cur->left;
                }
            }


            // Same logic for the right child.
            if (cur->right != nullptr) {

                if (tail != nullptr) {

                    tail->next = cur->right;
                    tail = tail->next;

                } else {

                    head = cur->right;
                    tail = cur->right;
                }
            }


            /*
            * Move horizontally on CURRENT level.
            *
            * These next pointers were created while
            * processing the previous level.
            */
            cur = cur->next;


            /*
            * cur == nullptr means:
            *
            * We reached the end of the current level.
            *
            * Move down to the next level.
            */
            if (cur == nullptr) {

                // head is the first node of the next level.
                cur = head;

                // We are about to build a NEW next level,
                // so reset its head and tail.
                head = nullptr;
                tail = nullptr;
            }
        }

        return root;
    }
};
