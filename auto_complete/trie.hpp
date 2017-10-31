#ifndef TRIE_H
#define TRIE_H
#include <cstring>
#include <cassert>
#include <string>
#include <vector>

constexpr int ALPHA_NUM = 26;

struct TrieNode {
    TrieNode* next[ALPHA_NUM];
    bool isEnd;

    TrieNode(): isEnd(false) {
        std::memset(next, 0, sizeof(TrieNode*) * ALPHA_NUM);
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const std::string &word) {
        auto node = root;
        for (const auto c : word) {
            auto index = char_index(c);
            if (node->next[index] == nullptr) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
        }
        node->isEnd = true;
    }

    bool search(const std::string &word) const {
        auto node = find_prefix(word);
        return node && node->isEnd;
    }

    std::vector<std::string> get_suggestions(const std::string &word,
            int count = 10) const {
        std::vector<std::string> suggestions;
        auto node = find_prefix(word);
        std::string query = word;
        get_suggestions(node, suggestions, query, count);
        return suggestions;
    }

private:
    static size_t char_index(const char c) {
        assert(c >= 'a' && c <= 'z');
        return c - 'a';
    }

    static void get_suggestions(TrieNode *node,
            std::vector<std::string> &suggestions,
            std::string &word,
            size_t count) {

        if (!node || suggestions.size() >= count) return;
        if (node->isEnd) {
            suggestions.push_back(word);
        }

        for (int i = 0; i < ALPHA_NUM; i++) {
            if (node->next[i] == nullptr) {
                continue;
            }
            word.push_back(i+'a');
            get_suggestions(node->next[i], suggestions, word, count);
            word.pop_back();
        }
    }

    TrieNode* find_prefix(const std::string &word) const {
        auto node = root;
        for (const auto c : word) {
            auto index = char_index(c);
            if (node->next[index] == nullptr) {
                return nullptr;
            }
            node = node->next[index];
        }
        return node;
    }

private:

    TrieNode *root;
};

#endif // TRIE_H
