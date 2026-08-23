class Solution {
    // 127.Word Ladder https://leetcode.com/problems/word-ladder/
    // 433. Minimum Genetic Mutation  https://leetcode.com/problems/minimum-genetic-mutation/
private:
    // Generates all valid one-character mutations of 'word'.
    //
    // For each position, we try replacing the current character
    // with A, C, G, and T.
    //
    // Any mutation that exists in 'dict' is a valid next state,
    // so we add it to the BFS queue and remove it from the dict
    // immediately to prevent visiting it again.
    void addWord(string& word, unordered_set<string>& dict, queue<string>& toVisit) {

        // 'word' has already been processed, so remove it from
        // the set of unvisited genes.
        dict.erase(word);

        for (int i = 0; i < word.size(); ++i) {
            char original = word[i];

            // A gene contains only these four possible characters.
            for (char mutation : string("ACGT")) {
                if (mutation == original)
                    continue;
                word[i] = mutation;

                // If this mutation exists in the bank and hasn't
                // been visited yet, add it to the next BFS level.
                if (dict.count(word)) {
                    toVisit.push(word);

                    // Mark it visited immediately when it is pushed.
                    // This prevents the same gene from entering
                    // the queue multiple times.
                    dict.erase(word);
                }
            }

            // Restore the original character before moving to
            // the next position.
            word[i] = original;
        }
    }

public:
    // BFS is used because every valid mutation has the same cost:
    // exactly one mutation.
    //
    // Time:  O(N * L^2) average
    // Space: O(N * L)
    //
    // N = number of genes in bank
    // L = length of each gene (8 for this problem)
    int minMutation(string startGene, string endGene, vector<string>& bank) {

        unordered_set<string> dict(bank.begin(), bank.end());

        // If the target isn't in the bank, it can never be reached.
        if (!dict.count(endGene))
            return -1;

        queue<string> toVisit;
        toVisit.push(startGene);

        // Mark startGene as visited so that it isn't added again
        // if another mutation leads back to it.
        dict.erase(startGene);

        int mutations = 0;

        // BFS processes one level at a time.
        // Each level represents one additional mutation.
        while (!toVisit.empty()) {
            int levelSize = toVisit.size();

            while (levelSize--) {
                string current = toVisit.front();
                toVisit.pop();

                // Since BFS explores states in increasing order of
                // mutation count, the first time we reach endGene
                // is guaranteed to be the minimum number of mutations.
                if (current == endGene)
                    return mutations;

                addWord(current, dict, toVisit);
            }

            ++mutations;
        }

        // No sequence of valid mutations can reach endGene.
        return -1;
    }
};
