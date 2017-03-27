#include <sstream>
#include <iostream>
#include <vector>
#include <string>


struct Split {
    enum empties_t { empties_ok, no_empties };
};

template <typename Container>
Container& split(
        Container &result,
        const typename Container::value_type& s,
        typename Container::value_type::value_type delim,
        Split::empties_t empties = Split::empties_ok) {
    result.clear();
    std::istringstream ss(s);
    while (!ss.eof()) {
        typename Container::value_type field;
        std::getline(ss, field, delim);
        if ((empties == Split::no_empties) && field.empty()) continue;
        result.push_back(field);
    }
    return result;
}

int main() {
    std::string s = "please, split,, me";
    std::vector<std::string> fields;
    split(fields, s, ',', Split::no_empties);
    for (auto s : fields) std::cout << s << "\n";

    return 0;
}
