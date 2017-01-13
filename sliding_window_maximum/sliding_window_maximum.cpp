#include <iostream>
#include <deque>
#include <vector>

using std::cout;
using std::endl;
using std::deque;
using std::vector;

vector<int> max_sliding_window(const vector<int> &nums, const unsigned k) {
    deque<int> dq;
    vector<int> ans;

    for (decltype(nums.size()) i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(nums[dq.front()]);
    }

    return ans;
}

int main() {
    vector<int> nums {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> ans = max_sliding_window(nums, 3); // 3 3 5 5 6 7
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

