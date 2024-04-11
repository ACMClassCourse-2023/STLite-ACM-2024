#include "src.hpp"
#include <iostream>

signed main() {
    sjtu::map <int, int> mp;
    auto x = mp.insert({666, 1}).first;
    for (int i = 0 ; i <= 114514 ; ++i) mp.insert({i, i});

    // Iterator should never go invalid.
    // This is map, not vector.
    while (x != ++ -- mp.end()) mp.erase(x++);
    std::cout << mp.size() << '\n';

    // Multiple clear should be safe.
    for (int i = 0 ; i < 10 ; ++i) mp.clear();

    // In the reverse direction, again.
    x = mp.insert({19198, 1}).first;
    for (int i = 114514 ; i >= 0 ; --i) mp.insert({i, i});

    // Iterator should never go invalid.
    // This is map, not vector.
    while (x != -- ++ mp.begin()) mp.erase(x--);

    std::cout << mp.size() << '\n';
}
