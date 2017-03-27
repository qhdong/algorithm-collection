#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

int foo(int x, int k) {
    int y = ~x;
    int tmp = x;
    while (tmp & (tmp - 1)) {
        tmp = tmp & (tmp - 1);
    }
    tmp = (tmp << 1) - 1;
    y &= tmp;

    int i = 0;
    int mask = 1;
    while (k >> i++) {
        while (!(y & mask)) mask <<= 1;
        if (!(k & 1)) {
            y ^= mask;
        }
    }

    return y;
}

int main() {
    int x, k, y;
    while (cin >> x >> k) {
        y = foo(x, k);
        if ((x + y) == (x | y)) {
            cout << "foo(" << x << ", " << k << ") = " << y << endl;
        }
    }

    return 0;
}
