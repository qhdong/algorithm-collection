#include <iostream>

using namespace std;

void hanio(int n, char A, char B, char C) {
    if (n == 1) {
        cout << "Move from " << A << " to " << C << "\n";
    } else {
        hanio(n-1, A, C, B);
        cout << "Move from " << A << " to " << C << "\n";
        hanio(n-1, B, A, C);
    }
}

int main() {
    int n;
    while (cin >> n) {
        hanio(n, 'A', 'B', 'C');
    }
    return 0;
}
