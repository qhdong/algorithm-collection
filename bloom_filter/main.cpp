#include <iostream>
#include <fstream>
#include <string>
#include "bloom_filter.h"

using namespace std;

int main(int argc, char **argv) {
    bf::BloomFilter bloom(10000000, 10);

    if (argc < 2) {
        string word;
        while (cin >> word) {
            bloom.insert(word);
        }
    } else {
        int count = 0;
        for (int i = 1; i < argc; i++) {
            cout << "reading file " << argv[i] << '\n';
            ifstream f(argv[i]);
            if (!f.is_open()) {
                cerr << "Error open file " << argv[1] << '\n';
                continue;
            }

            string word;
            while (f >> word) {
                cout << "insert word: " << word << endl;
                bloom.insert(word);
                ++count;
            }
        }
        cout << "total words inserted: " << count << '\n';
    }

    bloom.print_state();
    cout << "Now input the word you want to query\n";
    string word;
    do {
        cout << "query: ";
        cin >> word;
        if (bloom.get(word)) {
            cout << "probably have \"" << word << "\"\n";
        } else {
            cout << "definitely not exist \"" << word << "\"\n";
        }
    } while (cin);
}
