#include <iostream>
#include <vector>
using namespace std;

int rodCutting(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int max_val = INT_MIN;
        for (int j = 0; j < i; j++) {
            max_val = max(max_val, price[j] + dp[i - j - 1]);
        }
        dp[i] = max_val;
    }

    return dp[n];
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20}; // Preços
    int n = price.size();

    cout << "Valor máximo que pode ser obtido = " << rodCutting(price, n) << endl;

    return 0;
}
