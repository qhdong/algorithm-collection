#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <stack>

using namespace std;

ostream& operator<<(ostream& os, const vector<string>& vec) {
    for (const auto &x : vec) {
        os << x << ' ';
    }
    return os;
}

vector<string> infix_to_postfix(const string& s) {
    static const string ops = "()+-*/";
    vector<string> postfix;
    stack<char> st;
    size_t current;
    size_t next = -1;
    do {
        next = s.find_first_not_of(ops, next + 1);
        if (next == string::npos) break;
        next -= 1;
        current = next + 1;
        next = s.find_first_of(ops, current);

        if (next != string::npos) {
            switch(s[next]) {
                case '(':
                    st.push(s[next]);
                    break;
                case ')':
                    while (!st.empty() && st.top() != '(') {
                        postfix.push_back(string(1, st.top()));
                        st.pop();
                    }
                    if (!st.empty()) st.pop(); // throw away '('
                    break;
                case '+':case'-':
                    while (!st.empty() && st.top() != '(') {
                        postfix.push_back(string(1, st.top()));
                        st.pop();
                    }
                    st.push(s[next]);
                    break;
            }
        }

        postfix.push_back(s.substr(current, next - current));
    } while (next != string::npos);



    return postfix;
}

int calculate(string s) {

    return 0;
}


int main() {
    ifstream input("exp.txt");
    string exp;
    while (getline(input, exp)) {
        cout << "infix:   " << exp << '\n';
        cout << "postfix: " << infix_to_postfix(exp) << '\n';
    }
}
