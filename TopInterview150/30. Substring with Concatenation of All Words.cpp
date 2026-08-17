class Solution {
private:
    
    bool checkSubstring(unordered_map<string, int> wordMap, string s, int wordLen) {
        for (int j = 0; j < s.size(); j += wordLen) {
            string w = s.substr(j, wordLen);
            if (wordMap.find(w) != wordMap.end()) {
                if (--wordMap[w] == -1) {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    void slidingWindow(
        const unordered_map<string, int>& required,
        int wordLen,
        int totalWords,
        int windowLen,
        int startOffset,
        const string& s,
        vector<int>& answer
    ) {
        unordered_map<string, int> found;

        int left = startOffset;

        // Number of valid word occurrences currently counted.
        int wordsUsed = 0;

        /*
         * true means some word currently appears more
         * times than allowed by 'required'.
         */
        bool hasExcessWord = false;

        /*
         * Move right one whole word at a time.
         */
        for (int right = startOffset; right + wordLen <= s.size(); right += wordLen) {

            string word = s.substr(right, wordLen);

            /*
             * Case 1:
             * Current chunk is not one of the required words.
             *
             * Then no valid concatenation can cross this point,
             * so reset the entire window.
             */
            if (!required.count(word)) {
                found.clear();
                wordsUsed = 0;
                hasExcessWord = false;

                // Next possible window starts after this bad word.
                left = right + wordLen;
                continue;
            }

            /*
             * Before adding 'word', shrink if:
             *
             * 1. window already has total required length, OR
             * 2. some word is currently overused.
             */
            while (right - left == windowLen || hasExcessWord) {
                string leftWord = s.substr(left, wordLen);

                --found[leftWord];
                left += wordLen;

                /*
                 * If after removal its count is still >= required,
                 * then the removed copy was an extra occurrence.
                 *
                 * Otherwise we removed a needed occurrence.
                 */
                if (found[leftWord] >= required.at(leftWord)) {
                    hasExcessWord = false;
                } else {
                    --wordsUsed;
                }
            }

            /*
             * Add current word to the window.
             */
            ++found[word];

            if (found[word] <= required.at(word)) {
                // This occurrence was needed.
                ++wordsUsed;
            } else {
                // Too many copies of this word.
                hasExcessWord = true;
            }

            /*
             * If exactly all required words are represented
             * and there is no overused word, this is valid.
             */
            if (wordsUsed == totalWords && !hasExcessWord) {
                answer.push_back(left);
            }
        }
    }

public:
    // n = s.length()
    // a = number of words
    // b = word length
    //
    // Time: O(n * b) in practice due to substring creation/hashing
    // Space: O(a)
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> answer;

        if (s.empty() || words.empty()) {
            return answer;
        }

        int wordLen = words[0].size();
        int totalWords = words.size();
        int windowLen = totalWords * wordLen;

        unordered_map<string, int> required;

        for (const string& word : words) {
            ++required[word];
        }

        // int i = 0;
        // while (i + wordsWindow <= sLen) {
        //     if (checkSubstring(required, s.substr(i, windowLen), wordLen)) {
        //         res.push_back(i);
        //     }
        //     i++;
        // }/*
      
         * Run one sliding window for each possible alignment.
         *
         * Example wordLen = 3:
         *
         * offset 0: 0,3,6,9,...
         * offset 1: 1,4,7,10,...
         * offset 2: 2,5,8,11,...
         */
        for (int offset = 0; offset < wordLen; ++offset) {
            slidingWindow(required, wordLen, totalWords, windowLen, offset, s, answer);
        }

        return answer;
    }
};
