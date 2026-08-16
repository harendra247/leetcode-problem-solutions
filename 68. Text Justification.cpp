class Solution {
public:
    
    vector<string> fullJustify_(vector<string>& words, int maxWidth) {
        vector<string> res;
        for (int i = 0, k, l; i < words.size(); i += k) {
            for (k = l = 0; i + k < words.size() and l + words[i+k].size() <= maxWidth - k; k++) {
                l += words[i+k].size();
            }
            string tmp = words[i];
            for (int j = 0; j < k - 1; j++) {
                if (i + k >= words.size()) { 
                    tmp += " ";
                } else { 
                    tmp += string((maxWidth - l) / (k - 1) + (j < (maxWidth - l) % (k - 1)), ' ');
                }
                tmp += words[i+j+1];
            }
            tmp += string(maxWidth - tmp.size(), ' ');
            res.push_back(tmp);
        }
        return res;
    }
    
    // Dynamic Programming Time: O(n^2) Space: O(n^2)
    vector<string> fullJustify_dp(vector<string>& words, int maxWidth) {
        vector<vector<int>> cost(words.size(), vector<int> (words.size(), 0));
        
        //next 2 for loop is used to calculate cost of putting words from
        //i to j in one line. If words don't fit in one line then we put
        //INT_MAX there.
        for (int i=0 ; i < words.size(); i++) {
            cost[i][i] = maxWidth - words[i].size();
            for (int j=i+1; j < words.size(); j++) {
                cost[i][j] = cost[i][j-1] - words[j].length() - 1; 
            }
        }
        
        for (int i=0; i < words.size(); i++) {
            for (int j=i; j < words.size(); j++) {
                if (cost[i][j] < 0) {
                    cost[i][j] = INT_MAX;
                } else {
                    cost[i][j] = (int)pow(cost[i][j], 2);
                }
            }
        }
        
        //minCost from i to len is found by trying
        //j between i to len and checking which
        //one has min value
        vector<int> minCost(words.size());
        vector<int> result(words.size());
        for(int i = words.size()-1; i >= 0 ; i--){
            minCost[i] = cost[i][words.size()-1];
            result[i] = words.size();
            for(int j=words.size()-1; j > i; j--){
                if(cost[i][j-1] == INT_MAX){
                    continue;
                }
                if(minCost[i] > minCost[j] + cost[i][j-1]){
                    minCost[i] = minCost[j] + cost[i][j-1];
                    result[i] = j;
                }
            }
        }
        int i = 0;
        int j;
        
        //cout<< "Minimum cost is " << minCost[0] << endl;
        
        //finally put all words with new line added in 
        //string buffer and print it.
        vector<string> builder;
        int id = 0;
        do {
            j = result[i];
            builder.push_back("");
//             int size_l = 0;
//             for(int k=i; k < j; k++){
//                 size_l += words[k].size();
//             }
//             size_l = maxWidth - size_l;
//             int spaces = j - i;
//             spaces = size_l / spaces - 1;
            
            for(int k=i; k < j; k++){
                builder[id] += words[k] + " ";
            }
            i = j; 
            id++;
        } while(j < words.size());
        
        return builder;
    }
    
    
    // Greedy algo Time: O(n^2) Space: O(n^2)
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int left = 0; vector<string> result;
        
        while (left < words.size()) {
            int right = findRight(left, words, maxWidth);
            result.push_back(justify(left, right, words, maxWidth));
            left = right + 1;
        }
        
        return result;
    }
    
    int findRight(int left, vector<string> &words, int maxWidth) {
        int right = left;
        int sum = words[right++].length();
        
        while (right < words.size() && (sum + 1 + words[right].length()) <= maxWidth)
            sum += 1 + words[right++].length();
            
        return right - 1;
    }
    
    string justify(int left, int right, vector<string> &words, int maxWidth) {
        if (right - left == 0) 
            return padResult(words[left], maxWidth);
        
        bool isLastLine = (right == (words.size() - 1));
        int numSpaces = right - left;
        int totalSpace = maxWidth - wordsLength(left, right, words);
        
        string space = isLastLine ? " " : string(totalSpace / numSpaces, ' ');
        int remainder = isLastLine ? 0 : totalSpace % numSpaces;
        //cout << totalSpace << " " << numSpaces << " " << space.size() << " " << remainder << endl;
        
        
        string result = "";
        int i = left;
        for (i = left; i < right; i++) {
            result += words[i];
            result += space;
            if (remainder > 0 ) {
                result += " ";
                remainder -= 1;
            }
        }
        
        result += words[i];
        //cout << maxWidth << " " << result.length() << " " << result << endl;
        return padResult(result, maxWidth);
    }
    
    int wordsLength(int left, int right, vector<string> &words) {
        int wordsLength = 0;
        for (int i = left; i <= right; i++) 
            wordsLength += words[i].length();
        return wordsLength;
    }
    
    string padResult(string result, int maxWidth) {
        if (maxWidth - result.length() > 0)
            return result + string(maxWidth - result.length(), ' ');
        
        return result;
    }
};
