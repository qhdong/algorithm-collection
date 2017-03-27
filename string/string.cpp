#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

vector<string> split(const string &s, const char* delim) {
    vector<string> res;
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    char *p = strtok(cstr, delim);
    while (p != nullptr) {
        res.push_back(p);
        p = strtok(nullptr, delim);
    }
    return res;
}

int main() {
    auto res = split("please, split,, me,", ",");
    for (auto s : res) cout << s << "\n";

    return 0;
}
