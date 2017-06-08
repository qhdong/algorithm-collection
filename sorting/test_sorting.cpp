#include <vector>
#include <iostream>
#include <random>
#include <string>
#include "sorting.h"

using namespace std;

vector<int> get_random_data(size_t n = 10, int min = 0, int max = 100) {
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> uniform_dist(min, max);
    vector<int> data;

    for (size_t i = 0; i != n; ++i) {
        data.push_back(uniform_dist(engine));
    }
    return data;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> &vec) {
    for (auto n : vec) {
        os << n << ", ";
    }
    return os;
}

bool is_sorted(vector<int> &A) {
    for (int i = 1; i < A.size(); ++i) {
        if (A[i-1] > A[i]) return false;
    }
    return true;
}

void test_sort(string algo_name, vector<int>& data,
        void (*sort_func)(vector<int>&)) {
    vector<int> tmp(data);
    cout << "================================================\n"
        << "Test Sorting Algorithm: " << algo_name << "\n"
        << "================================================\n"
        << "Before sorting:\n" << tmp << "\n";

    sort_func(tmp);

    cout << "After sorting:\n" << tmp << "\n";
    cout << (is_sorted(tmp)
            ? "\e[32mPASSED\e[0m"
            : "\e[31mFAILED\e[0m") << "\n";
}

int main() {
    auto data = get_random_data();
    test_sort("Bubble Sort", data, bubble_sort);
    test_sort("Insertion Sort", data, insertion_sort);
    test_sort("Selection Sort", data, insertion_sort);
    test_sort("Shell Sort", data, shell_sort);
    test_sort("Quick Sort", data, quick_sort);
    test_sort("Merge Sort", data, merge_sort);
}
