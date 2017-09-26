#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cstdlib>

template<typename Key, typename Value, size_t MAXLEVEL = 16>
class SkipList {
public:
    SkipList(Key min_key, Key max_key, double p = 0.5):
        _min_key(min_key), _max_key(max_key), _probability(p)
    {
        _head = new SkipListNode(_min_key);
        _tail = new SkipListNode(_max_key);
        std::fill(_head->forwards.begin(), _head->forwards.end(), _tail);
    }

    ~SkipListNode() {
        auto curr_node = _head->forwards[0];
        while (curr_node != _tail) {
            auto tmp = curr_node;
            curr_node = curr_node->forwards[0];
            delete tmp;
        }
        delete _head;
        delete _tail;
    }

    bool empty() const {
        return _head->forwards[1] == _tail;
    }

    void insert(Key search_key, Value new_value) {
        auto curr_node = find(search_key);
        if (curr_node) {
            curr_node->value = new_value;
            return;
        }

        vector<node_t*> update(MAXLEVEL, nullptr);
        size_t new_level = random_level();
        if (new_level > _max_curr_level) {
            for (size_t level = _max_curr_level + 1; level <= new_level; ++level) {
                update[level] = _head;
            }
            _max_curr_level = new_level;
        }

        curr_node = new node_t(search_key, new_value);
        for (size_t level = 1; level <= _max_curr_level; ++level) {
            curr_node->forwards[level] = update[level]->forwards[level];
            update[level]->forwards[level] = curr_node;
        }
    }

    void erase(const Key& search_key) {
        vector<node_t*> update(MAXLEVEL, nullptr);
        auto curr_node = _head;
        for (size_t level = _max_curr_level; level >= 1; --level) {
            while (curr_node->forwards[level]->key < search_key) {
                curr_node = curr_node->forwards[level];
            }
            update[level] = curr_node;
        }

        curr_node = curr_node->forwards[1];
        if (curr_node == search_key) {
            for (size_t level = 1; level <= _max_curr_level; ++level) {
                if (update[level]->forwards[level] != curr_node) {
                    break;
                }
                update[level]->forwards[level] = curr_node->forwards[level];
            }
            delete curr_node;
            while (_max_curr_level > 1 && _head->forwards[_max_curr_level] == nullptr) {
                --_max_curr_level;
            }
        }
    }

    Value* find(const Key& search_key) const {
        Value *res = nullptr;
        auto x = lower_bound(search_key);
        if (x->key == search_key && x != tail) {
        }
    }

private:

    struct Node {
        Key key;
        Value value;
        std::array<Node*, MAXLEVEL> forwards;

        Node(const Key& key, const Value& val):
            key(key), value(val), forwards(MAXLEVEL, nullptr) {}
    };

    static double uniform_random() const {
        return std::rand() / static_cast<double>(RAND_MAX);
    }

    size_t random_level() const {
        size_t level = 1;
        while (uniform_random() < _probability && level < MAXLEVEL) {
            ++level;
        }
        return level;
    }

    size_t node_level(const Node* node) const {
        int level = 1;
        for (int i = 0; i < node->forwards.size(); i++) {
            if (node->forwards[i] && node->forwards[i]->key != tail) {
                ++level;
            } else {
                break;
            }
        }
        return level;
    }

    Node* lower_bound(const Key& search_key) const {
        auto curr = _head;
        for (size_t i = node_level(_head); i-- > 0;) {
            while (curr->forwards[i]->key < search_key) {
                curr = curr->forwards[i];
            }
        }
        return curr->forwards[0];
    }

    std::array<Node*, MAXLEVEL> predecessors(const Key& search_key) const {
        std::array<Node*, MAXLEVEL> res(MAXLEVEL, nullptr);
        auto curr = _head;
        for (size_t i = node_level(_head); i-- > 0; ) {
            while (curr->forwards[i]->key < search_key) {
                curr = curr->forwards[i];
            }
            res[i] = curr;
        }
        return res;
    }

    Key _min_key;
    Key _max_key;
    node_t *_head; // pointer to first node
    node_t *_tail; // pointer to last node
    const double _probability;
};

template<typename Key, typename Value, size_t MAXLEVEL = 16>
SkipList<Key, Value, MAXLEVEL>::


#endif // SKIP_LIST_H
