#ifndef SORTING_H_
#define SORTING_H_

#include <vector>
#include <utility>

void bubble_sort(std::vector<int> &A) {
    bool swapped = false;
    size_t n = A.size();
    do {
        swapped = false;
        for (size_t i = 1; i < n; ++i) {
            if (A[i-1] > A[i]) {
                std::swap(A[i-1], A[i]);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

void insertion_sort(std::vector<int> &A) {
    for (int i = 1; i < A.size(); ++i) {
        int tmp = A[i];
        int j = i;
        while (j > 0 && A[j-1] > tmp) {
            A[j] = A[j-1];
            --j;
        }
        A[j] = tmp;
    }
}

void selection_sort(std::vector<int> &A) {
    for (int i = 0; i < A.size(); ++i) {
        int idx = i;
        for (int j = i + 1; j < A.size(); ++j) {
            if (A[j] < A[i]) {
                idx = j;
            }
        }
        if (idx != i) {
            std::swap(A[idx], A[i]);
        }
    }
}

void shell_sort(std::vector<int> &A) {
    size_t n = A.size();
    for (int gap = n >> 1; gap > 0; gap >>= 1) {
        for (int i = gap; i < n; ++i) {
            int tmp = A[i];
            int j = i;
            while (j >= gap && A[j-gap] > tmp) {
                A[j] = A[j-gap];
                j -= gap;
            }
            A[j] = tmp;
        }
    }
}

int partition(std::vector<int> &A, int lo, int hi) {
    int pivot = A[lo];
    --lo, ++hi;
    while (true) {
        while (A[++lo] < pivot) {}
        while (A[--hi] > pivot) {}
        if (lo >= hi) return hi;
        std::swap(A[lo], A[hi]);
    }
}

void quick_sort(std::vector<int> &A, int lo, int hi) {
    if (lo < hi) {
        int p = partition(A, lo, hi);
        quick_sort(A, lo, p);
        quick_sort(A, p + 1, hi);
    }
}

void quick_sort(std::vector<int> &A) {
    quick_sort(A, 0, A.size() - 1);
}

// Left: A[beg, mid-1], right: A[mid, end-1]
void merge(std::vector<int>&A, int beg, int mid, int end, std::vector<int>&B) {
    int i = beg, j = mid;
    for (int k = beg; k < end; ++k) {
        if (i < mid && (j >= end || A[i] <= A[j])) {
            B[k] = A[i++];
        } else {
            B[k] = A[j++];
        }
    }
}

void split_merge(std::vector<int>&B, int beg, int end, std::vector<int>&A) {
    if (end - beg < 2) return;
    int mid = beg + (end - beg) / 2;
    split_merge(A, beg, mid, B);
    split_merge(A, mid, end, B);
    merge(B, beg, mid, end, A);
}

void merge_sort(std::vector<int> &A) {
    std::vector<int> B(A);
    split_merge(B, 0, A.size(), A);
}


#endif
