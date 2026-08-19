class TrieNode {
public:
    vector<TrieNode*> children;
    string word;

    TrieNode() : children(26, nullptr), word("") {}
};

class Solution {
private:
    TrieNode* buildTrie(const vector<string>& words) {
        TrieNode* root = new TrieNode();

        for (const string& word : words) {
            TrieNode* node = root;

            for (char ch : word) {
                int index = ch - 'a';

                if (node->children[index] == nullptr) {
                    node->children[index] = new TrieNode();
                }

                node = node->children[index];
            }

            // Store the whole word at the terminal Trie node.
            node->word = word;
        }

        return root;
    }

    void dfs(vector<vector<char>>& board, int row, int col, TrieNode* node, vector<string>& result) {
        int rows = board.size();
        int cols = board[0].size();

        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] == '#') {
            return;
        }

        char ch = board[row][col];
        int index = ch - 'a';

        TrieNode* next = node->children[index];

        // Current path is not a prefix of any dictionary word.
        if (next == nullptr) {
            return;
        }

        // Found a complete word.
        if (!next->word.empty()) {
            result.push_back(next->word);

            // Avoid returning the same word again.
            next->word.clear();
        }

        // Mark this cell as used for the current DFS path.
        board[row][col] = '#';

        dfs(board, row + 1, col, next, result);
        dfs(board, row - 1, col, next, result);
        dfs(board, row, col + 1, next, result);
        dfs(board, row, col - 1, next, result);

        // Restore board.
        board[row][col] = ch;
    }

public:
    /*
    R = rows
    C = columns
    L = maximum word length
    W = total number of characters across all dictionary words
    */
    // Time: O(R * C * 4 * 3^(L-1) + W) Space: O(W + L)
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;

        if (board.empty() || board[0].empty()) {
            return result;
        }

        TrieNode* root = buildTrie(words);

        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col) {
                dfs(board, row, col, root, result);
            }
        }

        return result;
    }
};
