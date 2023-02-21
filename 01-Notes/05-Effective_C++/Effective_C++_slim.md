# Effective C++ 精华版

## 第一章 让自己习惯C++ 

**[Accustoming Yourself to C++]**

### 条款01 视C++为一个语言联邦 

View C++ as a federation of languages

C++ 有四大部分，分别是C、面对对象的C++、模板C++、STL。

### 条款02 尽量以const，enum，inline 替换 #define 

Prefer consts,enums,and inlines to #defines

#define可能会带来诸多不便。

- 定义常量指针以及在类内定义常量–const
- enum hack（暂时不用考虑）
- 利用inline或者template inline来实现宏

### 条款03 尽可能使用const 

Use const whenever possible

关键字const多才多艺，你可以用它在classes外部修饰global或namespace作用域中的常量，或修饰文件、函数、或区块作用域中被声明为static的对象。也可以用它修饰classes内部的static和non-static成员变量。面对指针，你也可以指出指针自身、指针所指物，或者两者都（或都不）是const。

```c++
char greeting[] = ”Hello”;
char *p = greeting;//non-const pointer non-const data 
const char *p = greeting; //non-const pointer const data
char *const p = greeting;//const pointer non-const data
const char *const p = greeting;//const pointer const data.
```

在指针中const的位置说明

- 如果关键字const出现在星号左边，表示被指物是常量。

- 如果出现在星号右边，表示指针自身是常量。如果出现在星号两边，表示被指物和指针两者都是常量。

- 如果被指物是常量，const在类型的前后其实没有区别。



在 C++ 中，mutable 关键字可以用来修饰类的成员变量。使用 mutable 修饰的成员变量可以在常量成员函数中被修改。（常量成员函数是指在函数声明中使用 const 关键字修饰的成员函数，这类函数不会修改对象的状态。）

### 条款04 确定对象被使用前已先被初始化 

Make sure that objects are initialized before they're used

使用成员初值列(member initialization list)来替换赋值动作

为免除“跨编译单元之初始化次序”问题，请以local static对象替换non-local static对象。

## 第二章 构造/析构/赋值运算

 **[Constructors, Destructors, and Assignment Operators]**

### 条款05 了解C++默默编写并调用哪些函数

Know what functions C++ silently writes and calls

如果你自己没有声明，编译器就会为它声明（编译器版本的）一个copy构造函数，一个拷贝操作符，一个析构函数。如果你连构造函数，编译器也会为你声明一个default构造函数。所有这些函数都是public且inline的【条款30】

### 条款06 若不想使用编译器自动生成的函数，就该明确拒绝

Explicitly disallow the use of compiler-generated

通过明确声明一个成员函数，你阻止了编译器暗自创建其专属版本

而令这些函数为private，使得阻止别人调用这些函数。

### 条款07 为多态基类声明virtual析构函数

Declare destructors virtual in polymorphic

作为基类的类都应该有一个virtual析构函数。如果这个类不会被继承，那就不必这么做。

### 条款08 别让异常逃离析构函数

Prevent exceptions from leaving destructors

析构函数绝不应该吐出异常。

### 条款09 绝不在构造和析构过程中调用virtual函数

Never call virtual functions during construction or destruction

在基类的构造函数中，虚函数永远不会下降到派生类中。

确定你在创建和销毁对象的时候，你的构造函数和虚构函数不会去调用虚函数，并且它们调用的所有函数也需要遵守这个约定。

### 条款10 令operator = 返回一个 reference to *this

Have assignment operators return a reference to *this

为了满足赋值可以连续赋值，同时满足右结合律。

### 条款11 在operator = 中处理“自我赋值”

Handle assignment to self in operator=

两个对象只要来自同一个继承体系，他们甚至不需声明为相同类型就可能造成“别名”，因为一个基类的指针或引用可以指向一个子类对象。那么就需考虑这些对象是否为同一个。

确保当对象自我赋值时，operator= 有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址，精心周到的语句顺序、以及copy-and-swap

### 条款12 复制对象时勿忘其每一个成分 

Copy all parts of an object

当你编写一个copying函数，请确保：

- 复制所有local成员变量
- 调用所有base class内的适当copying 函数。

## 第三章 资源管理

**[Constructors, Destructors, and Assignment Operators]**

### 条款13 以对象管理资源

Use objects to manage resources

使用智能指针来管理资源

### 条款14 在资源管理类中小心copying行为

Think carefully about copying behavior in resource-managing classes

使用智能指针来管理资源

### 条款15 在资源管理类中提供对原始资源的访问

Provide access to raw resources in resource-managing classes

- API往往要求访问原始资源（raw resources），所以每一个RAII class 应该提供一个“取得其所管理之资源”的方法。
- 对原始资源的访问可能经由显式转换或隐式转换。一般而言显式转换比较安全，但隐式转换对客户比较方便。

### 条款16 成对使用new和delete时要采取相同形式

Use the same form in corresponding uses of new and delete

如果你在new表达式中使用[]，必须在相应的delete表达式中也使用[]；如果你在new表达式中不使用[]，一定不要在相应的delete表达式中也使用[]；

### 条款17 以独立语句将newd 的对象置入智能指针

Store newed objects in smart pointers in standalone statements

编译器对于跨越语句的各项操作没有重新排列的自由（只有在语句内它才有那个自由度）。

独立语句将newed对象存储于智能指针内。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏。

## 第四章 设计声明

**[Designs and Declarations]**

### 条款18 让接口容易被使用，不易被误用

Make interfaces easy to use correctly and hard to use incorrectly

### 条款19 设计class犹如设计type

Treat class design as type design

### 条款20 宁以pass-by-reference-to-const替换pass-by-value

Prefer pass-by-reference-to-const to pass-by-value

- 按值传递参数会有效率问题

- 按const引用传递会更高效

- 按const引用传递能避免切片问题

  当子类对象以传值方式传递并被视为base class对象时，base class的构造函数会被调用，而它的子类部分都被切割掉了

### 条款21 必须返回对象时，别妄想返回其reference

Don’t try to return a reference when you must return an object

任何时候看到一个reference声明式，你都一个立刻问自己，它的另一个名称是什么？

绝不要返回指向一个local stack对象的指针或引用，或返回指向一个heap-allocated对象的引用，或返回指向一个可能被多个需求需要的local static对象的指针或引用。

从函数中返回新对象的正确方法是返回对象。这是因为返回对象会通过值传递的方式将对象的副本返回给调用者，而不是返回对象的引用或指针。这种方式可以确保调用者获得一个新的、独立的对象，而不是与函数内部创建的对象共享相同的内存地址。

### 条款22 将成员变量声明为private

Declare data members private

- 切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者以充分的实现弹性。
- Protected并不比public更具有封装性。

### 条款23 宁以non-member、non-friend替换member函数

Prefer non-member non-friend functions to member functions

宁可拿同一命名空间下的non-member non-friend函数替换member函数，这一做可以增加封装性、包裹弹性和机能扩充性。

### 条款24 若所有参数皆需类型转换、请为此采用non-member函数

Declare non-member functions when type conversions should apply to all parameters

在导读里曾经提过，令class支持隐式类型转换通常是一个糟糕的主意，但是也得视情况而定。比如把整数隐式转换为有理数就很自然。

如果你需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member。

### 条款25 考虑写出一个不抛异常的swap函数

Consider support for a non-throwing swap

- 首先、如果swap的默认版本对你的class或class template提供可接受的效率，那么你不需要做什么。
- 其次，如果swap默认版本的效率不足（一般来说都是因为类或模板使用了pimpl手法），试着做以下事情：
  - 提供一个public swap成员函数，让它高效地置换你的类型的两个对象值。这个函数绝不应该抛出异常。
  - 在你的class或template所在的命名空间内提供一个non-member swap，并令它调用上述swap函数。
  - 如果你正编写一个class而非类模板，为你的类特化std::swap，并令它调用你的swap成员函数
- 最后，如果你调用swap，请确定包含一个using 声明式，以便让std::swap在你的函数内曝光可见，然后不加任何namespace修饰符，赤裸裸地调用swap。

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