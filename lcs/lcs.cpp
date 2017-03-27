#include <iostream>
#include <vector>
#include <string>

using namespace std;

int lcs(const string& x, const string& y) {
    auto m = x.size(), n = y.size();
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i] == y[j]) c[i][j] = c[i-1][j-1] + 1;
            else if (c[i-1][j] > c[i][j-1]) c[i][j] = c[i-1][j];
            else c[i][j] = c[i][j-1];
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    return c[m][n];
}

int main() {
    string x = "ABCBDAB";    
    string y = "BDCABA";    

    cout << lcs(x, y) << endl;

    return 0;
}
