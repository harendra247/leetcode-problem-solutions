class SegmentTree {
private:
    static constexpr int MAX_K = 5;

    struct Node {
        // prefixCount[r] =
        // number of prefixes whose product % k == r
        array<int, MAX_K> prefixCount{};

        // Product of the entire segment modulo k.
        int product = 0;
    };

    int k;
    int n;
    vector<Node> tree;

    Node makeLeaf(int value) {
        Node node;

        int remainder = value % k;

        // The single element itself is one prefix.
        node.prefixCount[remainder] = 1;

        // Product of the entire segment.
        node.product = remainder;

        return node;
    }

    Node merge(const Node& left, const Node& right) {
        Node result;

        /*
            Case 1:
            Prefix lies completely inside the left segment.

            Example:

            LEFT = [2, 3]
            Prefix = [2]
                     [2, 3]
        */
        for (int remainder = 0; remainder < k; ++remainder) {
            result.prefixCount[remainder] =
                left.prefixCount[remainder];
        }

        /*
            Case 2:
            Prefix contains the entire left segment and
            then takes a prefix of the right segment.

            Product:

            product(left) * product(rightPrefix)
        */
        for (int remainder = 0; remainder < k; ++remainder) {
            int newRemainder =
                (long long)left.product * remainder % k;

            result.prefixCount[newRemainder] +=
                right.prefixCount[remainder];
        }

        // Product of the entire combined segment.
        result.product =
            (long long)left.product * right.product % k;

        return result;
    }

    void build(const vector<int>& nums,
               int node,
               int left,
               int right) {

        if (left == right) {
            tree[node] = makeLeaf(nums[left]);
            return;
        }

        int mid = left + (right - left) / 2;

        build(nums, node * 2, left, mid);
        build(nums, node * 2 + 1, mid + 1, right);

        tree[node] =
            merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node,
                int left,
                int right,
                int index,
                int value) {

        if (left == right) {
            tree[node] = makeLeaf(value);
            return;
        }

        int mid = left + (right - left) / 2;

        if (index <= mid) {
            update(node * 2, left, mid, index, value);
        } else {
            update(node * 2 + 1, mid + 1, right, index, value);
        }

        tree[node] =
            merge(tree[node * 2], tree[node * 2 + 1]);
    }

    Node query(int node,
               int left,
               int right,
               int queryLeft,
               int queryRight) {

        if (queryLeft <= left && right <= queryRight) {
            return tree[node];
        }

        int mid = left + (right - left) / 2;

        if (queryRight <= mid) {
            return query(
                node * 2,
                left,
                mid,
                queryLeft,
                queryRight
            );
        }

        if (queryLeft > mid) {
            return query(
                node * 2 + 1,
                mid + 1,
                right,
                queryLeft,
                queryRight
            );
        }

        Node leftResult =
            query(
                node * 2,
                left,
                mid,
                queryLeft,
                queryRight
            );

        Node rightResult =
            query(
                node * 2 + 1,
                mid + 1,
                right,
                queryLeft,
                queryRight
            );

        return merge(leftResult, rightResult);
    }

public:
    SegmentTree(const vector<int>& nums, int k)
        : k(k), n(nums.size()) {

        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    void update(int index, int value) {
        update(1, 0, n - 1, index, value);
    }

    Node query(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};


class Solution {
public:
    // Time: O((n+q)klogn) Space: O(nk)
    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        SegmentTree tree(nums, k);

        vector<int> answer;

        for (const auto& query : queries) {
            int index = query[0];
            int value = query[1];
            int start = query[2];
            int remainder = query[3];

            // nums[index] = value
            tree.update(index, value);

            // Get prefix information for nums[start ... n-1].
            auto node = tree.query(start, nums.size() - 1);

            // Number of prefixes whose product % k == remainder.
            answer.push_back(node.prefixCount[remainder]);
        }

        return answer;
    }
};
