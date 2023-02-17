# Effective C++ 精华版

## 第一章 让自己习惯C++ 

**[Accustoming Yourself to C++]**

### 条款01 视C++为一个语言联邦 

View C++ as a federation of languages

### 条款02 尽量以const，enum，inline 替换 #define 

Prefer consts,enums,and inlines to #defines

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