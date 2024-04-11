#pragma once
#include <map>

namespace sjtu {

template<class T1, class T2, class Cmp = std::less<T1>>
using map = ::std::map<T1, T2, Cmp>;

} // namespace sjtu
