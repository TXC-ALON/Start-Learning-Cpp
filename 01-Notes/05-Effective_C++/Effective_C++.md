# Effective C++

## 导读

学习程序语言根本大法是一回事，学习如何以某种语言设计并实现高效程序则是另一回事。

本书提供的对C++的导引，是你的软件更易理解、易维护、可移植、可扩充、高效、并且有着你所预期的行为。

本书提出的忠告大致分为两类：一般性的设计策略，以及带有具体细节的特定语言特性。



## 第一章 让自己习惯C++ 

**[Accustoming Yourself to C++]**

### 条款01 视C++为一个语言联邦 

View C++ as a federation of languages



如今C++已经是一个**多重范式编程语**言(multiparadigm programming language)，一个同时支持**过程形式**(procedural)、**面向对象形式**(object-oriented)、**函数形式**(functional)、**泛型形式**(generic)、**元编程形式**(metaprogramming)的语言。

最简单的方法是将C++ 视为一个由相关语言组成的联邦而不是单一语言，在它的某个次语言中，各种守则与通例都倾向简单易懂易记。(*The easiest way is to view C++ not as a single language but as a federation of related languages. Within a particular sublanguage, the rules tend to be simple, straightforward, and easy to remember*.)。

好在只有四个次语言(:<)

- C
- Object-Oriented C++
  - classes
    - 构造函数
    - 析构函数
  - 封装 encapsulation
  - 继承 inheritance
  - 多态 polymorphism
  - 虚函数
- Template C++ 
- STL
  - 容器 containers
  - 迭代器 iterators
  - 算法 algorithms
  - 函数对象 function objects

### 条款02 尽量以const，enum，inline 替换 #define 

Prefer consts,enums,and inlines to #defines   或许说是“宁可以编译器替换预处理器”

因为#define 不被视为是语言的一部分。

```c++
#define ASPECT_RATIO 1.653									//X
const double AspectRatio = 1.653							//√			
```

记号名称(symbolic name) ASPECT_RATIO 也许编译器处理源码之前就被移走，以至于没进入记号表内。而作为一个语言常量(a language constant)，AspectRadio肯定会被编译器看到。

#### Const

使用常量const来替换#defines，有两种特殊情况

- 定义常量指针

  由于常量定义式通常放在头文件内，那么有必要将指针（而不只是指针所指之物）声明为const。

  若要在头文件内定义一个常量char*based字符串，必须写成

  ```c++
  const char* const authorName = "Scott Meyers";
  //不过建议使用标准库的string，下面的更好
  const std::string authotName("Scott Meyers");
  ```

  > **const char * const authorName = "Scott Meyers";**
  >
  > 这行代码定义了一个名为authorName的常量字符串，并将其初始化为"Scott Meyers"。
  >
  > const char * 表示authorName是一个指向常量字符的指针。也就是说，你不能通过这个指针来修改指向的字符。
  >
  > const authorName，表示authorName本身是一个常量。也就是说，你不能通过其他方式来修改authorName的值。
  >
  > 因此，这行代码定义了一个名为authorName的常量字符串，它的值是"Scott Meyers"，并且无论如何都不能被修改。
  >
  > **char * const authorName = "Scott Meyers";**
  >
  > 这行代码定义了一个名为authorName的字符指针常量，并将其初始化为"Scott Meyers"。
  >
  > char * 表示authorName是一个指向字符的指针。
  >
  > const authorName，表示authorName本身是一个常量。也就是说，你不能通过其他方式来修改authorName的值。
  >
  > 因此，这行代码定义了一个名为authorName的指针常量，它指向一个字符串"Scott Meyers"，并且无论如何都不能被修改。你可以通过修改authorName指向的字符串来改变这个字符串的值，但是你不能让authorName指向另一个字符串。

- class专属常量

  为了讲常量的作用域限制于class内，必须让它成为class的一个成员；而为了确保此常量最多只有一份，那么必须让它成为一个static成员。

  ```c++
  class GamePlayer{
  public:
      static const int NumTurns = 5;
      int scores[NumTurns];
  };
  ```

  这是一个声明式，一般来说C++需要为你所使用的任何东西提供一个定义式，**尤其是常量**。但如果它是个class专属常量又是static且为整型(ints，chars，bools)，则需特殊处理。只要不取他们的地址，你可以声明并使用它们而无需提供定义式。但如果你取某个class专属常量的地址，或者你的编译器一定坚持要看到一个定义式，你就必须另外提供定义式如下，并将它放在一个实现文件而非头文件。

  ```c++
  const int GamePlayer::NumTurns;
  ```

  >测试代码
  >
  >```c++
  >//test.h
  >class GamePlayer{
  >public://为了测试我改成了public
  >    static const int NumTurns = 5;
  >    int scores[NumTurns];
  >};
  >
  >//main.cpp
  >#include<iostream>
  >#include"test.h"
  >using namespace std;
  >const int GamePlayer::NumTurns;
  >int main(){
  >GamePlayer A;
  >const int *ptr = &A.NumTurns; //不加定义的话是错误，NumTurns没有被定义
  >cout<<A.NumTurns<<endl;
  >cout<< *ptr<<endl;
  >return 0;
  >}
  >
  >```
  >如果没有那行代码会报错`undefined reference to GamePlayer::NumTurns`
  
  我们无法用#define来创建一个class专属常量，因为#defines并不重视作用域，一旦宏被定义，它就在其后的编译过程中有效（除非被#undef），这就使得它无法提供封装性，也就是没有private #define这样的东西。
  
  有的旧式编译器不支持static成员在声明式获得初值，那么就可以把初值放在定义式（我个人觉得这样也更好，不然感觉定义式很累赘），唯一例外就是class编译期间需要一个class常量值。例如上例的数组声明式。这时候如果编译器又不认static整数型class常量完成“in class初值设定”，可改用所谓的“the enum hack”补偿做法。即一个属于枚举类型的数值可权充ints被使用。
  
  ```c++
  class GamePlayer{
  public:
      enum{NumTurns = 5};
      int scores[NumTurns];
  };
  ```
  
#### enum

有必要认识enum hack

- enum hack的行为比较像#define而不是const。比如取enum的地址不合法，而取一个#define的地址通常也不合法。如果你不想让别人活得一个pointer或reference指向你的某个常数，enum可以帮你实现这个约束。【条款18对于“通过撰码时的决定实施设计上的约束条件”谈得更多】
- 实用主义，事实上`enum back` 是模板元编程【条款48】的基础技术。

#### inline

另一个误用#define的情况就是用它来实现宏(macros)，宏看起来像函数，但不会导致函数调用带来的额外开销。但是有的宏的写法有着诸多缺点。

```c++
#include<iostream>
using namespace std;
void f(int x)
{
    std::cout << "The value is: " << x << std::endl;
}
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))
int main(){
    int a = 5, b = 0;
    CALL_WITH_MAX(++a, b); // a is incremented twice
    CALL_WITH_MAX(++a, b+8); // a is incremented once
    return 0;
}
```

首先所有的实参都带加括号，另外还是会有些问题，比如上面的代码，a的递增次数取决于它和谁比较。

> 在这段代码中，你定义了一个名为CALL_WITH_MAX的宏，它接受两个参数a和b，并调用函数f，将a和b的最大值作为参数传递给f。
>
> 在main函数中，你调用了两次CALL_WITH_MAX宏。在第一次调用中，a被自增了两次。这是因为在宏定义的参数列表中，a的前面有两个自增运算符（++）。
>
> 例如，假设你调用CALL_WITH_MAX宏如下：
>
> CALL_WITH_MAX(++a, b);
>
> 在编译时，这行代码会被替换为：
>
> f((++a) > (b) ? (++a) : (b));
>
> 这意味着a会被自增两次，因为它出现在条件判断中两次。
>
> 这是因为，在C++中，宏定义的参数会被直接嵌入到宏定义中，所以会发生这种情况。
>
> 如果你希望避免这种情况，你可以使用C++中的inline函数代替宏定义。inline函数可以在编译时被展开，但是它会进行类型检查和参数传递的复制。因此，inline函数在代码质量和性能方面都比宏定义更优。

这时候template inline就可以解决问题了

```c++
template<typename T> // because we don’t
inline void callWithMax(const T& a, const T& b) // know what T is, we
{ // pass by reference-tof(a > b ? a : b); // const — see Item 20
}
```

这个模板会产出一整群函数，接受两个同类型对象，并以其中较大者调用f。

这种写法的好处多多：不要加一堆括号，不要操心参数被反复核算，而且callWithMax作为真正的函数遵守作用域和访问规则，而宏一般做不到。



#### 总结：

* 对于单纯常量，使用const对象或者enums替换#defines。
* 对于形似函数的宏macros，最好改用inline函数替换#defines。

### 条款03 尽可能使用const 

Use const whenever possible

### 条款04 确定对象被使用前已先被初始化 

Make sure that objects are initialized before they're used

## 第二章 构造/析构/赋值运算

 **[Constructors, Destructors, and Assignment Operators]**

### 条款05 了解C++默默编写并调用哪些函数

Know what functions C++ silently writes and calls

### 条款06 若不想使用编译器自动生成的函数，就该明确拒绝

Explicitly disallow the use of compiler-generated

### 条款07 为多态基类声明virtual析构函数

Declare destructors virtual in polymorphic

### 条款08 别让异常逃离析构函数

Prevent exceptions from leaving destructors

### 条款09 绝不在构造和析构过程中调用virtual函数

Never call virtual functions during construction or destruction

### 条款10 令operator = 返回一个 reference to *this

Have assignment operators return a reference to *this

### 条款11 在operator = 中处理“自我赋值”

Handle assignment to self in operator=

### 条款12 复制对象时勿忘其每一个成分 

Copy all parts of an object

## 第三章 资源管理

**[Constructors, Destructors, and Assignment Operators]**

### 条款13 以对象管理资源

Use objects to manage resources

### 条款14 在资源管理类中小心copying行为

Think carefully about copying behavior in resource-managing classes

### 条款15 在资源管理类中提供对原始资源的访问

Provide access to raw resources in resource-managing classes

### 条款16 成对使用new和delete时要采取相同形式

Use the same form in corresponding uses of new and delete

### 条款17 以独立语句将newd 的对象置入智能指针

Store newed objects in smart pointers in standalone statements

## 第四章 设计声明

**[Designs and Declarations]**

### 条款18 让接口容易被使用，不易被误用

Make interfaces easy to use correctly and hard to use incorrectly

### 条款19 设计class犹如设计type

Treat class design as type design

### 条款20 宁以pass-by-reference-to-const替换pass-by-value

Prefer pass-by-reference-to-const to pass-by-value

### 条款21 必须返回对象时，别妄想返回其reference

Don’t try to return a reference when you must return an object

### 条款22 将成员变量声明为private

Declare data members private

### 条款23 宁以non-member、non-friend替换member函数

Prefer non-member non-friend functions to member functions

### 条款24 若所有参数皆需类型转换、请为此采用non-member函数

Declare non-member functions when type conversions should apply to all parameters

### 条款25 考虑写出一个不抛异常的swap函数

Consider support for a non-throwing swap

## 第五章 实现

**[Implementations]**

### 条款26 尽可能延后变量定义式的出现时间

Postpone variable definitions as long as possible

### 条款27 尽量少做转型动作

Minimize casting

### 条款28 避免返回handles指向对象内部成分

Avoid returning “handles” to object internals

### 条款29 为”异常安全“而努力是值得的

Strive for exception-safe code

### 条款30 透彻了解inlining的里里外外

Understand the ins and outs of inlining

### 条款31 将文件间的编译依存关系降至最低

Minimize compilation dependencies between files

## 第六章 继承与面向对象设计

**[Inheritance and Object-Oriented Design]**

### 条款32 确定你的public继承塑模出is-a关系

Make sure public inheritance models “is-a.”

### 条款33 避免遮掩继承而来的名称

Avoid hiding inherited names

### 条款34 区分接口继承和实现继承

Differentiate between inheritance of interface and inheritance of implementation

### 条款35 考虑virtual函数以外的其他选择

Consider alternatives to virtual functions

### 条款36 绝不重新定义继承而来的non-virtual函数

Never redefine an inherited non-virtual function

### 条款37 绝不重新定义继承而来的缺省参数值

Never redefine a function’s inherited default parameter value

### 条款38 通过复合塑模出has-a 或“根据某物实现出“

Model “has-a” or “is-implemented-in-terms-of” through composition

### 条款39 明智而审慎地使用private继承

Use private inheritance judiciously

### 条款40 明智而审慎地使用多重继承

Use multiple inheritance judiciously

## 第七章 模板与泛型编程

**[Templates and Generic Programming]**

### 条款41 了解隐式接口和编译期多态

Understand implicit interfaces and compile-time polymorphism

### 条款42 了解typename的双重意义

Understand the two meanings of typename

### 条款43 了解处理模板化基类内的名称

Know how to access names in templatized base classes

### 条款44 将与参数无关的代码抽离templates

Factor parameter-independent code out of templates

### 条款45 运用成员函数模板接受所有兼容类型

Use member function templates to accept “all compatible types.”

### 条款46 需要类型转换时请为定义非成员函数

Define non-member functions inside templates when type conversions are desired

### 条款47 请使用traits classes表现类型信息

Use traits classes for information about types

### 条款48 认识template元编程 

Be aware of template metaprogramming

## 第八章 定制new 和delete

**[Customizing new and delete]**

### 条款49 了解new-handler的行为

Understand the behavior of the new-handler

### 条款50 了解new和delete的合理替换时机

Understand when it makes sense to replace new and delete

### 条款51 编写new和delete时需固守常规

Adhere to convention when writing new and delete

### 条款52 写了placement new也要写placement delete

Write placement delete if you write placement new

## 第九章 杂项讨论

**[Miscellany]**

### 条款53 不要轻忽编译器的警告

Pay attention to compiler warnings

### 条款54 让自己熟悉包括TR1在内的标准程序库

Familiarize yourself with the standard library, including TR1

### 条款55 让自己熟悉Boost

Familiarize yourself with Boost