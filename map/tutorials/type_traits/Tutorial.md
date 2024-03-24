# A Little Tutorial
这个文档对 C++ 11 中的 type_traits 做一个简短的介绍和实现指导。但主要还是需要同学们自学。
## What is traits in C++ 11？
在 C++11 中，traits 是指一组类型萃取机制（type trait mechanism），用于提取类型信息，并根据这些信息在编译期间进行类型转换和编译期间的决策。它们在头文件 `type_traits` 中。

traits 通常使用**模板元编程**的技术实现，它允许我们在编译期间确定一个类型的属性，如是否是一个指针、是否是一个常量类型、是否是一个类等等。

我们给出若干个使用 C++ 11 type_traits 的代码实例：
```C++
#include <iostream>
#include <type_traits>

template<typename T>
void print_type(T x)
{
    if (std::is_floating_point<T>::value)
        std::cout << x << " is a floating point number.\n";
    else
        std::cout << x << " is not a floating point number.\n";
}

template<typename T, typename U>
void compare_types(T x, U y)
{
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
```
// 定义数据 type 类
enum Type {
  TYPE_1,
  TYPE_2,
  TYPE_3
}
// 自定义数据类型
class Foo {
public:
  Type type = TYPE_1; 
};
class Bar {
public:
  Type type = TYPE_2; 
};
// 定义type traits的模板类，所有像这个模板类一样含有Type的类会被萃取出来进行模板化处理
template<typename T>
struct type_traits {
  Type type = T::type;
}
// 内置数据类型同样可以进行这种萃取
template<typename int>
struct type_traits {
  Type type = Type::TYPE_1;
}
template<typename double>
struct type_traits {
  Type type = Type::TYPE_3;
}
// 萃取之后进行统一处理，写统一的编码函数
template<typename T>
void decode<const T& data, char* buf) {
  if(type_traits<T>::type == Type::TYPE_1) {
    ...
  }
  else if(type_traits<T>::type == Type::TYPE_2) {
    ...
  }
}
```
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
class iterator{
    using iterator_assignable = my_true_type;
};

class const_iterator{
    using iterator_assignable = my_false_type;
};
```
这部分我们不会提供提示数据，所以你需要自己设计测试代码，并且在 code review 时向助教展示。

如果想了解更多关于type traits，可以参考 https://en.cppreference.com/w/cpp/header/type_traits，或许其中的一些做法会给你一些思路的启发。

我们鼓励大家多去尝试，但不建议大家在这个作业中花费太多时间。
