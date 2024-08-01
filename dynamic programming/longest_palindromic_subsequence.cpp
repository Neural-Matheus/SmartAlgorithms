#include <iostream>
#include <vector>
#include <string>
using namespace std;

int longest_palindromic_subsequence(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int cl = 2; cl <= n; cl++) {
        for (int i = 0; i < n - cl + 1; i++) {
            int j = i + cl - 1;
            if (s[i] == s[j] && cl == 2)
                dp[i][j] = 2;
            else if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
        }
    }

    return dp[0][n - 1];
}

int main() {
    string s = "BBABCBCAB";
    cout << "The length of the longest palindromic subsequence is " << longest_palindromic_subsequence(s) << endl;
    return 0;
}
