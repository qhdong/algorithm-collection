#include <iostream>
#include <vector>

using namespace std;

// 使用递归方式求解 硬币找零问题

int count(const vector<int>& s, int m, int n) {
    if (n == 0) return 1; // 找到了一种方案
    if (n < 0) return 0;
    if (m <= 0) return 0; // 没有硬币可用了
    return count(s, m - 1, n) + count(s, m, n - s[m - 1]);
}

int count_dp(const vector<int>& s, int m, int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i != m; ++i) {
        for (int j = s[i]; j <= n; ++j) {
            dp[j] += dp[j-s[i]];
        }
    }
    return dp[n];
}

int main() {
    vector<int> coins{1, 2, 5};
    int n;
    while (cin >> n) {
        cout << "There are " << count_dp(coins, coins.size(), n)
            << " ways to get $" << n << "\n";
    }

    return 0;
}
