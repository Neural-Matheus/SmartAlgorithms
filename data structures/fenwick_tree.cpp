#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
private:
    vector<int> bit; // Binary Indexed Tree
    int n;

public:
    FenwickTree(int size) {
        n = size + 1;
        bit.resize(n, 0);
    }

    void update(int index, int delta) {
        for (++index; index < n; index += index & -index) {
            bit[index] += delta;
        }
    }

    int query(int index) {
        int sum = 0;
        for (++index; index > 0; index -= index & -index) {
            sum += bit[index];
        }
        return sum;
    }

    int query(int left, int right) {
        return query(right) - query(left - 1);
    }
};

int main() {
    vector<int> data = {1, 7, 3, 0, 7, 8, 3, 2, 6, 2, 1, 4, 5, 2, 7, 0, 2, 1, 6, 3};
    FenwickTree ft(data.size());

    for (int i = 0; i < data.size(); ++i) {
        ft.update(i, data[i]);
    }

    cout << "Sum of first 10 elements: " << ft.query(9) << endl;
    cout << "Sum of elements from index 3 to 8: " << ft.query(3, 8) << endl;

    ft.update(5, 5); // Increase value at index 5 by 5
    cout << "Updated sum of first 10 elements: " << ft.query(9) << endl;

    return 0;
}
