class MedianFinder {
private:
    /*
    small = smaller half of numbers → MAX heap
    large = larger half of numbers  → MIN heap

    1. Every value in small <= every value in large

    2. Size:
    small.size() == large.size()
            OR
    small.size() == large.size() + 1
   */
    // Smaller half of numbers.
    // top() = largest number in smaller half.
    priority_queue<long> small; // MaxHeap

    // Larger half of numbers.
    // top() = smallest number in larger half.
    priority_queue<long, vector<long>, greater<long>> large; // MinHeap

public:
    MedianFinder() {}

    // Time: O(log n)
    // Space: O(n)
    void addNum(int num) {

        /*
         * Step 1:
         * Temporarily insert into smaller half.
         */
        small.push(num);

        /*
         * Step 2:
         * Move the largest value of the smaller half
         * into the larger half.
         *
         * This maintains:
         *
         * every value in small <= every value in large
         */
        large.push(small.top());
        small.pop();

        /*
         * Step 3:
         * Maintain size invariant:
         *
         * small.size() == large.size()
         *
         * OR
         *
         * small.size() == large.size() + 1
         *
         * large should NEVER have more elements.
         */
        if (small.size() < large.size()) {
            small.push(large.top());
            large.pop();
        }
    }

    // Time: O(1)
    double findMedian() {

        /*
         * Odd number of elements:
         *
         * small contains one extra element.
         */
        if (small.size() > large.size()) {
            return small.top();
        }

        /*
         * Even number:
         *
         * average of the two middle elements.
         */
        return (small.top() + large.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
