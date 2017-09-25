#include <iostream>
#include <string>
#include <stdexcept>
#include "lru.h"

using namespace std;

int main() {
    cache::LRUCache<string, string> cache(2);
    cache.put("apple", "apple");
    cache.put("banana", "banana");
    cache.put("apple", "apple");
    cache.put("juice", "juice");
    cout << "cache size: " << cache.size() << endl;
    try {
        cout << cache.get("apple") << endl;
        // cout << cache.get("banana") << endl;
        cout << cache.get("juice") << endl;
    } catch (const range_error& e) {
        cerr << e.what() << endl;
    }
}
