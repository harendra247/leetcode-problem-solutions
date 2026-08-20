class NumMatrix {
private:
    /*
     * tree[i][j]:
     * Fenwick tree storage.
     *
     * Each cell stores the sum of a certain rectangular
     * region determined by its lowbit values.
     *
     * Uses 1-based indexing.
     */
    vector<vector<int>> tree;

    /*
     * nums[i][j]:
     * current actual matrix value.
     *
     * Also uses 1-based indexing.
     *
     * We need this so update(row,col,val) can compute:
     *
     * delta = newValue - oldValue
     */
    vector<vector<int>> nums;

    int rows = 0;
    int cols = 0;

    /*
     * Returns prefix sum:
     *
     * sum of rectangle:
     *
     * (0,0) -> (row-1,col-1)
     *
     * because row/col parameters are already
     * in 1-based Fenwick coordinates.
     */
    int prefixSum(int row, int col) {
        int result = 0;

        /*
         * Move upward through Fenwick ancestors:
         *
         * i -= lowbit(i)
         *
         * lowbit(i) = i & -i
         */
        for (int i = row; i > 0; i -= i & -i) {

            for (int j = col; j > 0; j -= j & -j) {
                result += tree[i][j];
            }
        }

        return result;
    }

public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }

        rows = matrix.size();
        cols = matrix[0].size();

        /*
         * Fenwick tree uses indices:
         *
         * 1 ... rows
         * 1 ... cols
         *
         * Therefore allocate rows+1 and cols+1.
         */
        tree.assign(
            rows + 1,
            vector<int>(cols + 1, 0)
        );

        nums.assign(
            rows + 1,
            vector<int>(cols + 1, 0)
        );

        /*
         * Build the Fenwick tree by inserting
         * every matrix value.
         */
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                update(r, c, matrix[r][c]);
            }
        }
    }

    // Time: O(log rows * log cols)
    void update(int row, int col, int val) {
        if (rows == 0 || cols == 0) {
            return;
        }

        /*
         * Convert from normal 0-based coordinates
         * to Fenwick's 1-based coordinates.
         */
        int r = row + 1;
        int c = col + 1;

        /*
         * Fenwick tree stores SUMS, so we don't directly
         * replace values in tree.
         *
         * Instead, calculate how much the cell changed.
         *
         * Example:
         *
         * old = 3
         * new = 8
         *
         * delta = +5
         *
         * Every Fenwick region containing this cell
         * must increase by 5.
         */
        int delta = val - nums[r][c];

        // Store new actual matrix value.
        nums[r][c] = val;

        /*
         * Update all Fenwick nodes whose rectangular
         * ranges contain (r,c).
         *
         * Moving forward:
         *
         * i += lowbit(i)
         * j += lowbit(j)
         */
        for (int i = r; i <= rows; i += i & -i) {
            for (int j = c; j <= cols; j += j & -j) {
                tree[i][j] += delta;
            }
        }
    }

    // Time: O(log rows * log cols)
    int sumRegion(
        int row1,
        int col1,
        int row2,
        int col2
    ) {
        if (rows == 0 || cols == 0) {
            return 0;
        }

        /*
         * Use 2D prefix-sum inclusion/exclusion.
         *
         * Desired rectangle:
         *
         * (row1,col1) -------- (row1,col2)
         *      |                    |
         *      |                    |
         * (row2,col1) -------- (row2,col2)
         *
         *
         * Formula:
         *
         * whole top-left rectangle
         *
         * - area above
         * - area left
         * + area removed twice
         */

        return
            prefixSum(row2 + 1, col2 + 1)
            - prefixSum(row1, col2 + 1)
            - prefixSum(row2 + 1, col1)
            + prefixSum(row1, col1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
