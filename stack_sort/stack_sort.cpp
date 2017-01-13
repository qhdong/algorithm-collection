#include <iostream>
#include <stack>
#include <deque>

using std::cout;
using std::endl;
using std::stack;
using std::deque;

void sort(stack<int> &s) {
    stack<int> tmp;
    int cur;
    while (!s.empty()) {
        cur = s.top();
        s.pop();
        if (tmp.empty() || cur <= tmp.top()) {
            tmp.push(cur);
        } else { // cur > tmp.top()
            while (!tmp.empty() && cur > tmp.top()) {
                s.push(tmp.top());
                tmp.pop();
            }
            tmp.push(cur);
        }
    }

    while (!tmp.empty()) {
        s.push(tmp.top());
        tmp.pop();
    }
}

int main() {
    deque<int> dq {1, 7, 3, 5, 0};
    stack<int> s(dq);

    sort(s);

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}
