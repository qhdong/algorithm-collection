#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::strlen;

void kmp_table(const char *W, int *T) {
    int len = strlen(W);
    int pos = 2;
    int cnd = 0;
    T[0] = -1;
    T[1] = 0;

    while (pos < len) {
        if (W[pos-1] == W[cnd]) {
            T[pos++] = ++cnd;
        } else if (cnd > 0) {
            cnd = T[cnd];
        } else {
            T[pos++] = 0;
        }
    }
}

/**
 * KMP search
 */
int kmp_search(const char *S, const char *W) {
    const int len_w = strlen(W);
    int T[len_w];
    kmp_table(W, T);

    int m = 0;
    int i = 0;

    const int len_s = strlen(S);

    while (m + i < len_s) {
        if (W[i] == S[m+i]) {
            if (i == len_w - 1) {
                return m;
            }
            ++i;
        } else {
            if (T[i] > -1) {
                m = m + i - T[i];
                i = T[i];
            } else {
                ++m;
                i = 0;
            }
        }
    }
    return -1;
}

void test(const char *test_name, const char *text, const char *pattern,
          int expect_index) {
    if (test_name != nullptr) {
        cout << test_name << " begins...";
    }
    if (expect_index == kmp_search(text, pattern)) {
        cout << "passed." << endl;
    } else {
        cout << "failed." << endl;
    }
}

void testcase_1() {
    const char *pattern = "ABCDABD";
    const char *text = "ABC ABCDAB ABCDABCDABDE";
    test("Test1", text, pattern, 15);
}

void testcase_2() {
    const char *pattern = "ABCDABD";
    const char *text = "ABC ABCDAB ABCDABCDABEE";
    test("Test2", text, pattern, -1);
}

void testcase_3() {
    const char *pattern = "ABCABAD";
    const char *text = "ABC ABCDAB ABCDABCDABEE";
    test("Test2", text, pattern, -1);
}


int main() {
    testcase_1();
    testcase_2();
    testcase_3();

    return 0;
}

