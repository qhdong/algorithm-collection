#include <iostream>
#include <string>

using std::cout;
using std::endl;

/**
 * 枚举 text 的所有可能位置，挨个测试，O(mn)
 */
int search(const char *text, const char *pattern) {
    int i, j;
    for (i = 0; text[i] != '\0'; ++i) {
        for (j = 0; text[i+j] != '\0' && pattern[j] != '\0'
                        && text[i+j] == pattern[j]; ++j) ;
        if (pattern[j] == '\0') return i;
    }
    return -1;
}

void test(const char *test_name, const char *text, const char *pattern,
          int expect_index) {
    if (test_name != nullptr) {
        cout << test_name << " begins...";
    }
    if (expect_index == search(text, pattern)) {
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

int main() {
    testcase_1();
    testcase_2();

    return 0;
}
    

