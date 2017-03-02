#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

void _permute(string s, size_t k, vector<string> &result) {
    if (k == s.size() - 1) {
        result.push_back(s);
    }
    sort(s.begin() + k, s.end());
    unordered_set<char> us;
    for (auto i = k; i != s.size(); ++i) {
        if (us.find(s[i]) == us.end()) {
            us.insert(s[i]);
            swap(s[i], s[k]);
            _permute(s, k+1, result);
            swap(s[i], s[k]);
        }
    }
}

vector<string> permutation(string &s) {
    vector<string> result;
    _permute(s, 0, result);
    return result;
}

int main() {
    string str;
    cin >> str;
    auto vs = permutation(str);
    for (auto s : vs) {
        cout << s << " ";
    }

    cout << endl;
}




