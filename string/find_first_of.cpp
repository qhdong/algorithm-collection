#include <sstream>
#include <iostream>
#include <vector>
#include <string>


struct Split {
    enum empties_t { empties_ok, no_empties };
};

template <typename Container>
Container& split(
        Container& result,
        const typename Container::value_type& s,
        const typename Container::value_type& delimiters,
        Split::empties_t empties = Split::empties_ok) {

    result.clear();
    size_t current;
    size_t next = -1;
    do {
        if (empties == Split::no_empties) {
            next = s.find_first_not_of(delimiters, next + 1);
            if (next == Container::value_type::npos) break;
            next -= 1;
        }
        current = next + 1;
        next = s.find_first_of(delimiters, current);
        result.push_back(s.substr(current, next - current));
    } while (next != Container::value_type::npos);
    return result;
}

int main() {
    std::string s = "please, split,, me,";
    std::vector<std::string> fields;
    split(fields, s, ",");
    for (auto s : fields) std::cout << s << "\n";

    split(fields, s, ",", Split::no_empties);
    for (auto s : fields) std::cout << s << "\n";

    return 0;
}
