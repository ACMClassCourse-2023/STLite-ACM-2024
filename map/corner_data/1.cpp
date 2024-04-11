#include "src.hpp"
#include <iostream>

signed main() {
    sjtu::map <int, int> map;
    auto iter = map.find(0); // iter = End iterator
    for (int i = 0; i < 10; ++i) map.insert({i, i});
    auto temp = iter;
    // First, iterator will never go invalid unless erased.
    // End iterator is still valid for decrement.
    std::cout << (--temp)->first << '\n';
}
