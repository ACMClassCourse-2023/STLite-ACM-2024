# A Little Tutorial

这个文档对 C++ 11 中的 type_traits 做一个简短的介绍和实现指导。但主要还是需要同学们自学。

## What is traits in C++ 11?

在 C++11 中，traits 是指一组类型萃取机制（type trait mechanism），用于提取类型信息，并根据这些信息在编译期间进行类型转换和编译期间的决策。它们在头文件 `type_traits` 中。

traits 通常使用**模板元编程**的技术实现，它允许我们在编译期间确定一个类型的属性，如是否是一个指针、是否是一个常量类型、是否是一个类等等。

我们给出若干个使用 C++ 11 type_traits 的代码实例：

```C++
#include <iostream>
#include <type_traits>

template<typename T>
void print_type(const T &x) {
    if (std::is_floating_point<T>::value)
        std::cout << x << " is a floating point number.\n";
    else
        std::cout << x << " is not a floating point number.\n";
}

template<typename T, typename U>
void compare_types(const T &x, const U &y) {
    if (std::is_same<T, U>::value)
        std::cout << x << " and "<< y << " have the same type.\n";
    else
        std::cout << x << " and "<< y << " have different type.\n";
}

struct A {}; // empty class
struct B { int x; }; // non-empty class

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pointer<int>::value << std::endl; // 输出 false
    std::cout << std::is_pointer<int*>::value << std::endl; // 输出 true

    print_type(1.1451); // prints 1.1451 is a floating point number.
    print_type(11451); // prints 11451 is not a floating point number.

    compare_types(1.1451, 11451); // prints 1.1451 and 11451 have different types.
    compare_types('a', 'b'); // prints a and b have the same type.

    std::cout << std::boolalpha;
    std::cout << "Is A an empty class? " << std::is_empty<A>::value << "\n"; // prints true
    std::cout << "Is B an empty class? " << std::is_empty<B>::value << "\n"; // prints false

    return 0;
}
```

以及traits自定义模板类的实现示例：

```C++
// 定义数据 type 类
enum Type {
    TYPE_1,
    TYPE_2,
    TYPE_3
}
// 自定义数据类型
struct Foo {
    static constexpr Type type = TYPE_1; 
};
struct Bar {
    static constexpr Type type = TYPE_2; 
};
// 定义type traits的模板类，所有像这个模板类一样含有Type的类会被萃取出来进行模板化处理
template<typename T>
struct type_traits {
    static constexpr Type type = T::type;
}
// 内置数据类型同样可以进行这种萃取
template<typename int>
struct type_traits {
    static constexpr Type type = Type::TYPE_1;
}
template<typename double>
struct type_traits {
    static constexpr Type type = Type::TYPE_2;
}

// 萃取之后进行统一处理，写统一的编码函数
template<typename T>
void decode(const T& data, char* buf) {
    if (type_traits<T>::type == Type::TYPE_1) {
        // ...
    }
    else if (type_traits<T>::type == Type::TYPE_2) {
        // ...
    }
}
```

当然，不仅可以用 `enum + static constexpr`，我们也可以用 `using/typedef` 来定义类型别名，然后通过 `std::is_same` 来判断类型是否相同，来实现类似的功能。

## Bonus

我们的 Bonus 可以是实现类似于 C++ 11 中的 type_traits 的某些功能，但是不要求完全一致。

这里举一个示例，我们以“迭代器可否被赋值特性”给出一个简单的实现思路：

```C++
//1.定义一个 type_traits 模板类
template<typename T>
struct my_type_traits{
    using iterator_assignable = typename T::iterator_assignable;
};
//2.定义两个类，表示迭代器是否可被赋值的特性(这一步也可以使用枚举变量来实现)
struct my_true_type{
    //todo
};
struct my_false_type{
    //todo
};
//3.分别在可被赋值的迭代器和不可被赋值的迭代器中定义 iterator_assignable 类型
struct iterator{
    using iterator_assignable = my_true_type;
};

struct const_iterator{
    using iterator_assignable = my_false_type;
};
```

Tips:

- 你可以借助 `std::true_type` 和 `std::false_type` 来实现类似功能。
- 如果 `true/false` 不能满足你的需求，可以试试看模板类  `std::integral_constant` 。

### Subtask 1

在 `C++` 中，`sort` 函数包含在 `algorithm` 头文件中，要求传入的是一对随机访问迭代器。

如果用户传入了错误的迭代器，会导致编译错误。然而，`gcc` 的默认报错信息实在是难以阅读。同时，对于我们的 `map` 类型，其天然就是按照 `key` 进行排序的。因此在我们的 `sort` 中，我们希望能够特判 `map` 类型迭代器，直接返回；对于随机访问迭代器，我们使用 `std::sort`；而对于其他类型的迭代器，我们希望能够给出更加友好的报错信息。

> 如果传入了错误的 `list` 迭代器，报错信息可能如下 (没截完, 大约 100+ 行):

![看看这甜蜜的报错](https://s2.loli.net/2023/07/07/eGMABEJKSi7ahZT.png)

请修改你的 `iterator` 类型，并且完成以下的 `sort` 函数:

Tips:

- 为了避免错误的分支被实例化, 你可能需要用到 `if constexpr` 语句
- 在 C++ 14 及以后, 可以使用 `is_xxx_v` 代替 `is_xxx<>::value`

```C++
#include <iterator>
#include <algorithm>
#include <type_traits>

namespace sjtu {

template <typename _Iter>
void my_sort(_Iter __first, _Iter __last) {
    // Your code here.
    // For random access iterator, use std::sort.
    // For sjtu::map iterator, return directly.
    // For others, static_assert(false, "Not a random access iterator.");
    // You may use std::iterator_traits to get the iterator category.
}

} // namespace sjtu

```

### Subtask 2

在 C++ 中，检测一个类是否存在一个成员函数等等是一个非常麻烦的事情。

在 C++ 20 之前，传统的做法是 [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae) 。然而，这东西写起来非常的麻烦，这里不推荐大家去学习各种抽象的“奇技淫巧”，只需了解大致意图即可。

幸运的是，在 C++ 20 及以后，我们可以用 `requires` 来轻松的检测，其会返回一个编译期 `bool` 常数。

```C++
template <typename _Tp>
static constexpr bool has_value_type = requires() {
    typename _Tp::value_type;
};

template <typename _Tp>
static constexpr bool has_member_dark = requires(const _Tp &x) {
    x.dark;
};
```

其可用于辅助 `type_traits` 的编写，完成类型检测。

现在，我们要实现一个递归输出的函数 `print` ，其可以接受任意一个能用 `std::cout` 输出的元素，或者是一个容器 (比如 `std::vector` ) 且容器的元素也能用 `print` 输出。

对于元素，我们直接输出；对于容器，如果容器里面是元素，我们输出元素，元素间用空格隔开，并且在最后输出一个换行符，前后用 `[]` 包裹；如果容器里面是容器，我们直接先输出单个 `[` 并换行，然后每行递归地输出每个子容器，最后输出一个 `]` 并换行。

当然，以上要求不是必须的，你可以自由发挥，只要好看即可。

保证输入合法，且容器有 `begin()` 和 `end()` ，或者是数组。

Tips:

- 你可以试试 `std::begin` 和 `std::end` 来获取容器的迭代器。
- 感兴趣的同学可以自行去了解一下 `concept`, 可能对你会有帮助。
- 如果使用 `requires`, 记得编译选项加上 `-std=c++20`

```C++
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <vector>

namespace sjtu {

template <typename _Tp>
void print(const _Tp &__val) {
    // Your code here.
}

} // namespace sjtu


void sample() {
    std::vector<int> a[5];
    for (int i = 0 ; i < 5 ; ++i)
        a[i].push_back(i), a[i].push_back(i);
    sjtu::print(a);
}

/*
应当输出类似如下(总之好看即可):
[
  [0 0]
  [1 1]
  [2 2]
  [3 3]
  [4 4]
]
*/

```
