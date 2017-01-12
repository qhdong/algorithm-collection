#include <iostream>
#include <stack>
#include <vector>
#include <climits>

using std::cout;
using std::endl;
using std::stack;
using std::vector;

class MinStack {
private:
    stack<int> s;
    int min = INT_MAX;
public:
    void push(int x) {
        if (x <= min) {
            s.push(min);
            min = x;
        }
        s.push(x);
    }

    void pop() {
        if (s.top() == min) {
            s.pop();
            min = s.top();
            s.pop();
        } else {
            s.pop();
        }
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min;
    }
};

int main() {
    MinStack s;
    vector<int> v{9, 8, 7, 6, 1, 2, 3, 4}; // 1 1 1 6 7 8 9
    for (auto x : v) s.push(x);
    for (decltype(v.size()) i = 0; i < v.size(); ++i) {
        cout << "top: " << s.top() << ", min: " << s.getMin() << endl;
        s.pop();
    }

    return 0;
}
