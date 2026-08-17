class Solution {
public:
    // Time: O(n^2) Space: O(n^2)
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<string> seen;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char number = board[i][j];
                if (number != '.') {
                    string row = string(1, number) + " in row " + to_string(i);
                    string col = string(1, number) + " in column " + to_string(j);
                    string block = string(1, number) + " in block " + to_string(i/3) + "-" + to_string(j/3);
                    if (seen.count(row) || seen.count(col) || seen.count(block))
                        return false;
                    else {
                        seen.insert(row);
                        seen.insert(col);
                        seen.insert(block);
                    }
                }
            }
        }
        return true;
    }
};
