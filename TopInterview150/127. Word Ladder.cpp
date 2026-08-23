class Solution {
public:
    // 127.Word Ladder https://leetcode.com/problems/word-ladder/
    // 433. Minimum Genetic Mutation  https://leetcode.com/problems/minimum-genetic-mutation/
    
    // N = number of words
    // L = word length
    //
    // Time: O(N * L * 26)
    // Space: O(N)
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dictionary(wordList.begin(), wordList.end());

        // endWord must be available.
        if (!dictionary.count(endWord)) {
            return 0;
        }

        queue<string> q;
        q.push(beginWord);

        // Avoid revisiting beginWord if it happens
        // to be present in wordList.
        dictionary.erase(beginWord);

        int ladderLength = 1;

        while (!q.empty()) {
            int levelSize = q.size();

            while (levelSize-- > 0) {
                string word = q.front();
                q.pop();

                if (word == endWord) {
                    return ladderLength;
                }

                // Try changing each position.
                for (int i = 0; i < word.size(); ++i) {
                    char original = word[i];

                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        if (ch == original) {
                            continue;
                        }

                        word[i] = ch;

                        auto it = dictionary.find(word);

                        if (it == dictionary.end()) {
                            continue;
                        }

                        q.push(word);

                        // Mark visited immediately when enqueued.
                        dictionary.erase(it);
                    }

                    // Restore original character.
                    word[i] = original;
                }
            }

            ++ladderLength;
        }

        return 0;
    }
};
