class Solution {
public:
    //  method to remove invalid parenthesis
    vector<string> removeInvalidParentheses_(string str) {
        vector<string> res;
       
        if (str.empty())
            return res;
        vector<char> par = {'(', ')'};
        remove(str, res, 0, 0, par);
        return res;
    }
   
    // DFS Time: O(n*2^n) Space: O(n)
    void remove(string s, vector<string> &ans, int last_i, int last_j, vector<char> par) {
        for (int stack = 0, i = last_i; i < s.length(); ++i) {
            if (s[i] == par[0]) stack++;
            if (s[i] == par[1]) stack--;
            if (stack >= 0) continue;
            for (int j = last_j; j <= i; ++j)
                if (s[j] == par[1] && (j == last_j || s[j - 1] != par[1]))
                    remove(s.substr(0, j) + s.substr(j + 1, s.length()), ans, i, j, par);
            return;
        }
        string reversed(s.rbegin(), s.rend());
        if (par[0] == '(') // finished left to right
            remove(reversed, ans, 0, 0, {')', '('});
        else // finished right to left
            ans.push_back(reversed);
    }
    
    // BFS Time: O(n*2^n) Space: O(n*2^n)
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;

        // sanity check
        if (s.size() == 0) 
            return res;

        unordered_set<string> visited;
        queue<string> queue;

        // initialize
        queue.push(s);
        visited.insert(s);

        bool found = false;

        while (!queue.empty()) {
            s = queue.front();
            queue.pop();

            if (isValid(s)) {
                // found an answer, add to the result
                res.push_back(s);
                found = true;
            }

            if (found) 
                continue;

            // generate all possible states
            for (int i = 0; i < s.length(); i++) {
                // we only try to remove left or right parantheses
                if (s[i] != '(' && s[i] != ')')
                    continue;

                string t = s.substr(0, i) + s.substr(i + 1);

                if (!visited.count(t)) {
                    // for each state, if it's not visited, add it to the queue
                    queue.push(t);
                    visited.insert(t);
                }
            }
        }

        return res;
    }
    
    // helper function checks if string s contains valid parantheses
    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(') {
                ++balance;
            }
            else if (c == ')') {
                if (balance == 0) {
                    return false;
                }
                --balance;
            }
        }

        return balance == 0;
    }
};
