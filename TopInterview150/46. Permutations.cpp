class Solution {
public:
    
    // Time: O(N*N!) Space: O(N!)
    vector<vector<int>> permute_hps(vector<int>& nums) {
        int n = nums.size(), k = 0;
        vector<vector<int>> res;
        if (0 == n) return res;
        permutation(nums, n, k, res);
        return res;
    }
    
    void permutation(vector<int>& nums, int n, int k, vector<vector<int>> & res) {
        if (n <= k) {
            res.push_back(nums);
            return;
        }
        
        for (int i = k; i < n; ++i) {
            swap(nums[i], nums[k]);
            permutation(nums, n , k + 1, res);
            swap(nums[i], nums[k]);
        }
        
    }
    
    // Time: O(N*N!) Space: O(N!)
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        
        if (0 == n) 
            return res;
        
        vector<int> tmplist;
        vector<bool> visited(n, false);
        
        backtracking(nums, tmplist, res, visited);
        return res;
    }
    
    void backtracking(vector<int>& nums, vector<int> tmplist, vector<vector<int>>& res, vector<bool> & visited) {
        if (tmplist.size() == nums.size()) {
            res.push_back(tmplist);
            return;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (visited[i]) 
                continue;
            visited[i] = true;
            tmplist.push_back(nums[i]);
            backtracking(nums, tmplist, res, visited);
            visited[i] = false;
            tmplist.pop_back();
        }     
    }
};
