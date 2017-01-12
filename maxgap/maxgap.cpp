#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::max;
using std::min;
using std::max_element;
using std::min_element;
using std::ceil;

int maximumGap(vector<int>& nums) {
    const int n = nums.size();
    if (n <= 1) return 0;
    int max_e = *max_element(nums.begin(), nums.end());
    int min_e = *min_element(nums.begin(), nums.end());

    int gap = ceil(double(max_e - min_e) / (n - 1));
    vector<int> vmax(n - 1, INT_MIN);
    vector<int> vmin(n - 1, INT_MAX);

    for (auto i : nums) {
        int index = (i - min_e) / gap;
        vmax[index] = max(vmax[index], i);
        vmin[index] = min(vmin[index], i);
    }

    int max_gap = 0, prev = vmax[0];
    for (int i = 1; i < n - 1; ++i) {
        if (vmin[i] == INT_MAX) continue;
        max_gap = max(max_gap, vmin[i] - prev);
        prev = vmax[i];
    }

    return max(max_gap, max_e - prev);
}

int main() {
    // vector<int> nums{7778,9763,347,8793,4297};
    // vector<int> nums{1, 10000000};
    vector<int> nums{1, 2, 5, 6, 9};
    cout << maximumGap(nums) << endl;

    return 0;
}
