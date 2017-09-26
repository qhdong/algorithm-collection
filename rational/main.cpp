#include <iostream>
#include "rational.h"

using namespace std;
using namespace rational;

int main() {
    Rational a(2, 12);
    Rational b(4);
    cout << "a: " << a << '\n'
         << "b: " << b << '\n';

    cout << "a + b = " << a + b << '\n'
         << "a - b = " << a - b << '\n'
         << "a * b = " << a * b << '\n'
         << "a / b = " << a / b << '\n';

    try {
        Rational c(3, 0);
    } catch (const denominator_error& e) {
        cout << e.what() << endl;
    }
}
