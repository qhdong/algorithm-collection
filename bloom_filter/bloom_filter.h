#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace bf {

class BloomFilter {
public:
    BloomFilter(int m, int k);
    void insert(const std::string& key);
    bool get(const std::string& key) const;
    void print_state() const;

private:
    int _m;
    int _k;
    std::vector<int> seeds;
    std::vector<bool> bitmap;

    uint32_t bldr_hash(const std::string&, int) const;
    
    void fill_seeds() {
        uint32_t seed = 131;
        for (int i = 0; i < _k; i++) {
            seeds[i] = seed;
            seed = seed * 10 + ((i % 2 == 0) ? 3 : 1);
        }
    }
};

BloomFilter::BloomFilter(int m, int k): _m(m), _k(k), 
    seeds(std::vector<int>(k)),
    bitmap(std::vector<bool>(m, false)) 
{
    fill_seeds();
}

uint32_t BloomFilter::bldr_hash(const std::string& key, int seed) const {
    uint32_t hash = 0;
    for (const char c : key) {
        hash = hash * seed + c;
    }
    return hash % _m;
}

void BloomFilter::insert(const std::string& key) {
    for (int i = 0; i < _k; i++) {
        uint32_t index = bldr_hash(key, seeds[i]);
        bitmap[index] = true;
    }
}

bool BloomFilter::get(const std::string& key) const {
    for (int i = 0; i < _k; i++) {
        uint32_t index = bldr_hash(key, seeds[i]);
        if (!bitmap[index]) {
            return false;
        }
    }
    return true;
}

void BloomFilter::print_state() const {
    std::cout << "m(bitmap size) = " << _m << '\n'
              << "k(hash functions) = " << _k << '\n';

    std::cout << "seeds: ";
    for (auto seed : seeds) {
        std::cout << seed << " ";
    }
    std::cout << '\n';

    size_t n = std::count(bitmap.cbegin(), bitmap.cend(), true);
    std::cout << "bitmap state: "
              << "set bits = " << n
              << " , usage = " << 100 * static_cast<double>(n) / bitmap.size()
              << "%\n";

    if (bitmap.size() < 100) {
        for (int i = 0; i < _m; i++) {
            if (i % 10 == 0) std::cout << '\n';
            std::cout << bitmap[i] << ' ';
        }
    }
    std::cout << '\n';
}

} // namespace bf

#endif // BLOOM_FILTER

