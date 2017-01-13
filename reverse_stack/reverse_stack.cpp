#include <iostream>
#include <stack>
#include <deque>

using std::cout;
using std::endl;

/**
 * 删除栈底的元素并返回该元素，假设该栈不为空
 */
int pop_last(std::stack<int> &stack) {
    int ret = stack.top();
    stack.pop();
    if (stack.empty()) {
        return ret;
    } else {
        int last = pop_last(stack);
        stack.push(ret);
        return last;
    }
}

/**
 * 将栈逆序
 */
void reverse_stack(std::stack<int> &stack) {
    if (!stack.empty()) {
        int top = pop_last(stack);
        reverse_stack(stack);
        stack.push(top);
    }
}

int main() {
    std::deque<int> deq {1, 2, 3, 4};
    std::stack<int> stack(deq);
    reverse_stack(stack);
    for (int i = 0; i < 4; ++i) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
    return 0;
}
