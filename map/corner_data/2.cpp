#include "src.hpp"
#include <iostream>

struct no_default_constructor {
    int x = 0;
    template <typename T>
    no_default_constructor(const T &) {}
    no_default_constructor(const no_default_constructor &) = default;
#if __cplusplus >= 202002L
    friend auto operator <=>
        (no_default_constructor, no_default_constructor) = default;
#else
    bool operator < (const no_default_constructor &t) const { return x < t.x; }
#endif
};

signed main() {
    // There may not be default constructor for the value type.
    sjtu::map <no_default_constructor, no_default_constructor> map;
    for (int i = 0; i < 10; ++i) map.insert({"42", 42});
    std::cout << (--map.end())->second.x << '\n';
    map.erase(--map.end());
}
