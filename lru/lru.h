#ifndef LRU_CACHE
#define LRU_CACHE

#include <unordered_map>
#include <list>
#include <utility>
#include <stdexcept>

namespace cache {

template<typename key_t, typename value_t>
class LRUCache {
public:
    typedef typename std::pair<key_t, value_t> key_value_t;
    typedef typename std::list<key_value_t>::iterator list_iterator_t;

    LRUCache(size_t max_size): _max_size(max_size) {}

    size_t size() const {
        return _cache_item_map.size();
    }

    void put(const key_t& key, const value_t& value) {
        auto it = _cache_item_map.find(key);
        _cache_item_list.emplace_front(key, value);
        if (it != _cache_item_map.end()) {
            _cache_item_list.erase(it->second);
            _cache_item_map.erase(it);
        }
        _cache_item_map[key] = _cache_item_list.begin();

        if (_cache_item_map.size() > _max_size) {
            auto last = _cache_item_list.back();
            _cache_item_map.erase(last.first);
            _cache_item_list.pop_back();
        }
    }

    value_t get(const key_t& key) {
        auto it = _cache_item_map.find(key);
        if (it == _cache_item_map.end()) {
            throw std::range_error("There is no such key in cache");
        } else {
            _cache_item_list.splice(_cache_item_list.begin(), _cache_item_list,
                    it->second);
            return it->second->second;
        }
    }

    bool exists(const key_t& key) const {
        return _cache_item_map.find(key);
    }

private:
    size_t _max_size;
    std::unordered_map<key_t, list_iterator_t> _cache_item_map;
    std::list<key_value_t> _cache_item_list;
};

}

#endif // LRU_CACHE
