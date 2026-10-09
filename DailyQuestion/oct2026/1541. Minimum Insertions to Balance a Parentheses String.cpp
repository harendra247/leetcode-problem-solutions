class Solution {
public:
    
    // Time: O(n) Space: O(1)
    int minInsertions(const std::string& s) {
        int insertions = 0;
        int closingNeeded = 0;

        for (char c : s) {
            if (c == '(') {
                // Finish an incomplete "))" pair before opening another group.
                if (closingNeeded % 2 != 0) {
                    ++insertions;       // Insert one ')'.
                    --closingNeeded;
                }

                closingNeeded += 2;
            } else {
                --closingNeeded;

                // This ')' has no matching '('.
                if (closingNeeded < 0) {
                    ++insertions;       // Insert one '('.
                    closingNeeded = 1;  // One more ')' completes its pair.
                }
            }
        }

        // Insert any closing parentheses still missing.
        return insertions + closingNeeded;
    }
};
