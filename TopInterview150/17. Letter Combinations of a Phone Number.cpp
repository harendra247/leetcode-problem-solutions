class Solution {
public:
    //BFS Time: O(4^N*N) Space: O(1)  if we dont consider result space
    vector<string> letterCombinations_b(string digits) {
        vector<string> result;
       
        if (digits.empty()) 
            return vector<string>();
        
        static const vector<string> v = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        
        result.push_back("");   // add a seed for the initial case
        
        for (int i = 0; i < digits.size(); ++i) {
            int num = digits[i]-'0';
            if (num < 0 || num > 9) break;
            
            const string& candidate = v[num];
            
            if (candidate.empty()) 
                continue;
            
            vector<string> tmp;
            for(int j = 0 ; j < candidate.size() ; ++j) {
                for(int k = 0 ; k < result.size() ; ++k) {
                    tmp.push_back(result[k] + candidate[j]);
                }
            }
            result.swap(tmp);
        }
        return result;
    }
    
    
    //DFS//Backtracking Time: O(4^N*N) Space: O(N)
    vector<string> letterCombinations_r(string digits) {
        vector<string> ret;
        if (digits.size() == 0)
            return ret;
        combination("", digits, 0, ret);
        return ret;
    }

   void combination(string prefix, string digits, int index, vector<string> &res) {
         static const vector<string> KEYS = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        if (index >= digits.size()) {
            res.push_back(prefix);
            return;
        }
        string letters = KEYS[(digits[index] - '0')];
        for (int i = 0; i < letters.size(); i++) {
            //combination(prefix + letters[i], digits, offset + 1, res); // this line can be broken in to 3 below lines
            prefix.push_back(letters[i]); // add
            combination(prefix, digits, index + 1, res);
            prefix.pop_back();    //Backtrack
        }
    }
    
    
    
    //DFS//Backtracking Time: O(4^N*N) Space: O(N)
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        if (digits.size() == 0)
            return ret;
        
        ret = combination(digits);
        return ret;
    }

    vector<string> combination(string digits) {
        static const vector<string> KEYS = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        if (0 == digits.size()) {
            return {""};
        }

        char ch = digits[0];
        string subdigits = digits.substr(1);
        vector<string> ret = combination(subdigits);
        vector<string> res;
        
        string letters = KEYS[ch - '0'];
        for (int i = 0; i < letters.size(); i++) {
            for (auto a: ret) {
                res.push_back(letters[i] + a);
            }
        }
        
        return res;
    }
};
