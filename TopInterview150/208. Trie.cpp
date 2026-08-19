class TrieNode
{
public:
    TrieNode *next[26];
    bool is_word;
    
    // Initialize your data structure here.
    TrieNode(bool b = false) {
        for (int i = 0; i < 26; ++i) {
            next[i] = nullptr;
        }
        is_word = b;
    }
};

class Trie
{
    TrieNode *root;
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    // Time: O(m) Space: O(m)
    void insert(string s) {
        TrieNode *p = root;
        for (int i = 0; i < s.size(); ++ i) {
            if (p -> next[s[i] - 'a'] == nullptr)
                p -> next[s[i] - 'a'] = new TrieNode();
            p = p -> next[s[i] - 'a'];
        }
        p -> is_word = true;
    }

    // Returns if the word is in the trie.
    // Time: O(m) Space: O(1)
    bool search(string key) {
        TrieNode *p = find(key);
        return p && p -> is_word;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    // Time: O(m) Space: O(1)
    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
    TrieNode* find(string key) {
        TrieNode *p = root;
        for (int i = 0; i < key.size() && p; ++ i)
            p = p -> next[key[i] - 'a'];
        return p;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
