#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <iterator>

#define DEBUG

using namespace std;

void print_vector(const vector<int> &v) {
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}

vector<vector<int>> split(vector<int> arr) {
    sort(arr.begin(), arr.end(), greater<int>());
    auto sum = accumulate(arr.begin(), arr.end(), 0);
    auto target = sum / 2;
    vector<int> a, b;
    int sum_a = 0;
    for (auto x : arr) {
        if (sum_a + x <= target) {
            a.push_back(x);
            sum_a += x;
        } else {
            b.push_back(x);
        }
    }

#ifdef DEBUG
    cout << "input data sum: " << sum << endl;
    print_vector(arr);
    cout << endl;

    cout << "subset #1 sum: " << sum_a << endl;
    print_vector(a);
    cout << endl;

    cout << "subset #2 sum: " << sum - sum_a << endl;
    print_vector(b);
    cout << endl;
#endif

    return {a, b};
}

bool test(const vector<int> &a, const vector<int> &b,
          const vector<int> &ea, const vector<int> &eb) {
    return (a == ea && b == eb) || (a == eb && b == ea);
}

int main() {
    cout << "please input the data: " << endl;
    istream_iterator<int> in(cin), eof;
    vector<int> input(in, eof);
    split(input);

    return 0;
}
