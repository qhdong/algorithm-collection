#include "trie.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void feed_trie(const char* filename, Trie &trie) {
    ifstream istrm(filename);
    if (!istrm.is_open()) {
        cerr << "failed to open " << filename << '\n';
    } else {
        size_t count = 0;
        string word;
        while (istrm >> word) {
            trie.insert(word);
            ++count;
        }
        cout << "inserted " << count << " words.\n";
    }
}

int main(int argc, char **argv) {

    // feed the trie
    if (argc != 2) {
        cerr << "Usage: ./main filename\n";
        exit(-1);
    }
    Trie trie;
    feed_trie(argv[1], trie);

    string word;
    while (true) {
        cout << "query: ";
        if (!(cin >> word)) break;
        auto suggestions = trie.get_suggestions(word);
        if (suggestions.empty()) {
            cout << "No such word: " << word << '\n';
            trie.insert(word);
        } else {
            cout << "================ Suggestions ================= \n";
            for (size_t i = 0; i != suggestions.size(); ++i) {
                cout << '[' << i+1 << ']' << '\t' << suggestions[i] << '\n';
            }
        }
    }
}
