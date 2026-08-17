class Solution {
public:
    // Time: O(rows * cols)
    // Space: O(1)
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        /*
         * firstColHasZero:
         * Was there originally any zero in column 0?
         *
         * firstRowHasZero:
         * Was there originally any zero in row 0?
         *
         * We need these because row 0 and column 0
         * are going to be reused as marker storage.
         */
        bool firstColHasZero = false;
        bool firstRowHasZero = false;


        /*
         * Step 1:
         * Check whether the FIRST COLUMN originally
         * contains any zero.
         */
        for (int row = 0; row < rows; ++row) {
            if (matrix[row][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }


        /*
         * Step 2:
         * Check whether the FIRST ROW originally
         * contains any zero.
         */
        for (int col = 0; col < cols; ++col) {
            if (matrix[0][col] == 0) {
                firstRowHasZero = true;
                break;
            }
        }


        /*
         * Step 3:
         * Use first row and first column as markers.
         *
         * If matrix[row][col] == 0:
         *
         * matrix[row][0] = 0
         *      means entire 'row' must become zero.
         *
         * matrix[0][col] = 0
         *      means entire 'col' must become zero.
         *
         * We start from index 1 because row 0 and column 0
         * are being used as marker storage.
         */
        for (int row = 1; row < rows; ++row) {
            for (int col = 1; col < cols; ++col) {

                if (matrix[row][col] == 0) {
                    matrix[row][0] = 0;
                    matrix[0][col] = 0;
                }
            }
        }


        /*
         * Step 4:
         * Use the markers to zero the inner matrix.
         *
         * If either:
         *
         * matrix[row][0] == 0  -> row marked
         * OR
         * matrix[0][col] == 0  -> column marked
         *
         * then matrix[row][col] must become zero.
         */
        for (int row = 1; row < rows; ++row) {
            for (int col = 1; col < cols; ++col) {

                if (matrix[row][0] == 0 ||
                    matrix[0][col] == 0) {

                    matrix[row][col] = 0;
                }
            }
        }


        /*
         * Step 5:
         * Restore the first column requirement.
         *
         * If column 0 originally contained a zero,
         * zero the entire first column.
         */
        if (firstColHasZero) {
            for (int row = 0; row < rows; ++row) {
                matrix[row][0] = 0;
            }
        }


        /*
         * Step 6:
         * Restore the first row requirement.
         *
         * If row 0 originally contained a zero,
         * zero the entire first row.
         */
        if (firstRowHasZero) {
            for (int col = 0; col < cols; ++col) {
                matrix[0][col] = 0;
            }
        }
    }
};
