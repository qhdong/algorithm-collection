#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void print_probability(const int n) {
    if (n < 1) return;

    const int DICE = 6;
    vector<vector<int>> prob = {
        vector<int>(n * DICE + 1, 0),
        vector<int>(n * DICE + 1, 0)
    };
    
    bool flag = false;
    for (int i = 1; i <= DICE; ++i) {
        prob[flag][i] = 1;
    }

    for (int k = 2; k <= n; ++k) {
        for (int i = 1; i < k; ++i) {
            prob[!flag][i] = 0;
        }
        for (int i = k; i <= k * DICE; ++i) {
            for (int j = 1; j < i && j <= DICE; ++j) {
                prob[!flag][i] += prob[flag][i-j];
            }
        }
        flag = !flag;
    }

    double total = pow(static_cast<double>(DICE), n);
    double max_p = 0;
    int sum = 0;
    for (int i = n; i <= n * DICE; ++i) {
        double p = prob[flag][i] / total;
        if (p > max_p) {
            max_p = p;
            sum = i;
        }
        cout << "sum of " << i << ", prob: " << p << "\n";
    }

    cout << "max prob is " << max_p << ", sum is " << sum << endl;
}

int main() {
    int n;
    while (cin >> n) {
        print_probability(n);
    }

    return 0;
}
