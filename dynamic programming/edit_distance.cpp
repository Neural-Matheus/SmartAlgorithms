#include <iostream>
#include <vector>
#include <string>
using namespace std;

int edit_distance(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }

    return dp[m][n];
}

int main() {
    string s1 = "sunday";
    string s2 = "saturday";
    cout << "Edit distance between " << s1 << " and " << s2 << " is " << edit_distance(s1, s2) << endl;
    return 0;
}
