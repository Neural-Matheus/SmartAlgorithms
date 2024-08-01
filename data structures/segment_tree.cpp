#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, value);
            } else {
                update(2 * node + 2, mid + 1, end, idx, value);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int sum_left = query(2 * node + 1, start, mid, left, right);
        int sum_right = query(2 * node + 2, mid + 1, end, left, right);
        return sum_left + sum_right;
    }

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
    }

    void update(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }

    int query(int left, int right) {
        return query(0, 0, n - 1, left, right);
    }
};

int main() {
    vector<int> data = {1, 3, 5, 7, 9, 11};
    SegmentTree st(data);

    cout << "Sum of values in given range = " << st.query(1, 3) << endl;

    st.update(1, 10);

    cout << "Updated sum of values in given range = " << st.query(1, 3) << endl;

    return 0;
}
