#include <iostream>
#include <vector>
using namespace std;

int matrixChainOrder(vector<int>& p, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < dp[i][j])
                    dp[i][j] = q;
            }
        }
    }

    return dp[1][n - 1];
}

int main() {
    vector<int> arr = {1, 2, 3, 4}; // Dimensões das matrizes
    int n = arr.size();

    cout << "Mínimo número de multiplicações = " << matrixChainOrder(arr, n) << endl;

    return 0;
}
