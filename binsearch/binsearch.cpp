#include <iostream>
#include <vector>

using namespace std;

int bin_search(const vector<int> &arr, const int k) {
    int lo = 0, hi = arr.size() - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] > k) hi = mid - 1;
        else lo = mid + 1;
    }
    return -1;
}

int bin_search_insert(const vector<int> &arr, const int k) {
    int lo = 0, hi = arr.size() - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] > k) hi = mid - 1;
        else lo = mid + 1;
    }
    return -(lo+1);
}

int bin_search_lower_bound(const vector<int> &arr, const int k) {
    int lo = 0, hi = arr.size() - 1, mid = 0;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (k <= arr[mid]) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int bin_search_higher_bound(const vector<int> &arr, const int k) {
    int lo = 0, hi = arr.size() - 1, mid;
    while (lo < hi) {
        mid = 1 + lo + (hi - lo) / 2;
        if (k >= arr[mid]) lo = mid;
        else hi = mid - 1;
    }
    return hi;
}

int bin_search_in_loop(const vector<int> &arr, const int k) {
    int lo = 0, hi = arr.size() - 1, mid = 0;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        if (arr[lo] <= arr[mid]) {
            if (arr[lo] <= k && k < arr[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        if (arr[mid] <= arr[hi]) {
            if (arr[mid] < k && k <= arr[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}

int find_smallest_in_loop(const vector<int> &arr) {
    int lo = 0, hi = arr.size() - 1, mid = 0;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (arr[mid] > arr[hi]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int find_kth_in_loop(const vector<int> &arr, const size_t k) {
    if (k > arr.size()) return -1;
    return (k + find_smallest_in_loop(arr) - 1) % arr.size();
}


int main() {
    // vector<int> arr{0, 1, 1, 1, 3, 5, 7};
    vector<int> arr{4, 5, 6, 1, 2, 3};
    cout << "arr: ";
    for (auto n : arr) { cout << n << " "; }
    cout << endl;

    int k;
    while (cin >> k) {
        // cout << "bin_search(arr, " << k << ") = " << bin_search(arr, k) << endl;
        // cout << "bin_search_insert(arr, " << k << ") = " << bin_search_insert(arr, k) << endl;
        // cout << "bin_search_lower_bound(arr, " << k << ") = " << bin_search_lower_bound(arr, k) << endl;
        // cout << "bin_search_higher_bound(arr, " << k << ") = " << bin_search_higher_bound(arr, k) << endl;
        cout << "bin_search_in_loop(arr, " << k << ") = " << bin_search_in_loop(arr, k) << endl;
        cout << "find_kth_in_loop(arr, " << k << ") = " << find_kth_in_loop(arr, k) << endl;
    }

    return 0;
}
