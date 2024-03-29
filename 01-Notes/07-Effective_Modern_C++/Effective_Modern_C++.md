# Effective Modern C++

## 一 类型推导

###  Item 1:理解模板类型推导 

```c++
template<typename T>
void f(ParamType param);
f(expr); //从expr中推导T和ParamType
```

T的推导不仅取决于expr的类型，也取决于
ParamType的类型。这⾥有三种情况：

- ParamType是⼀个指针或引用，但不是通用引用（关于通用引用请参⻅Item24。在这⾥你只需要
  知道它存在，而且不同于左值引用和右值引用）
- ParamType⼀个通用引用
- ParamType既不是指针也不是引用

#### 情景⼀：ParamType是⼀个指针或引用但不是通用引用

> 在C++中，所谓的通用引用（Universal Reference）是指一种特殊的引用类型，使用`&&`表示。通用引用只能用于模板类型推导的场景中，并且只能在模板参数类型推导的过程中使用。
>
> 通用引用的特点是能够同时接受左值和右值引用，根据传入的参数类型自动推导为左值引用或右值引用，从而实现了一种更加通用的引用类型。
>
> 通用引用的语法形式是：
>
> ```c++
> template <typename T>
> void func(T&& arg)
> {
>     // ...
> }
> ```
>
> 在这个例子中，`arg`就是一个通用引用，可以接受任何类型的参数，并将其转换为左值引用或右值引用。根据参数的类型，编译器会自动推导出`T`是左值引用类型还是右值引用类型。
>
> 通用引用通常用于完美转发（Perfect Forwarding）场景中，即将一个参数转发到另一个函数中，同时保留其左值或右值属性。例如：
>
> ```c++
> template<typename T>
> void forward(T&& arg)
> {
>     other_function(std::forward<T>(arg));
> }
> ```
>
> 在这个例子中，`forward`函数接受一个通用引用类型的参数`arg`，然后使用`std::forward`函数将`arg`参数完美转发到`other_function`函数中，保留其左值或右值属性。`std::forward`函数根据`T`参数的类型，将`arg`参数转换为左值引用或右值引用，并将其传递给`other_function`函数。

最简单的情况是ParamType是⼀个指针或者引用但非通用引用，也就是我们这个情景讨论的内容。在
这种情况下，类型推导会这样进行：

1. 如果expr的类型是⼀个引用，忽略引用部分
2. 然后剩下的部分决定T，然后T与形参匹配得出最终ParamType

类型推导会如左值引用⼀样对待右值引用。通常，右值只能传递给右值引用，但是在模板类型推导中这种限制将不复存在。

#### 情景二：ParamType是⼀个通用引用

如果ParamType是⼀个通用引用那事情就⽐情景⼀更复杂了。如果ParamType被声明为通用引用（在函数模板中假设有⼀个模板参数T,那么通用引用就是T&&),它们的行为和T&⼤不相同，完整的叙述请参⻅`Item24`，在这有些最必要的你还是需要知道：

- 如果expr是左值，T和ParamType都会被推导为左值引用。这非常不寻常，第⼀，这是模板类型推导中唯⼀⼀种T和ParamType都被推导为引用的情况。第⼆，虽然ParamType被声明为右值引用类型，但是最后推导的结果它是左值引用。
- 如果expr是右值，就使用情景⼀的推导规则

```c++
template<typename T>
void f(T&& param); //param现在是⼀个通用引用类型
int x=27; //如之前⼀样
const int cx=x; //如之前⼀样
const int & rx=cx; //如之前⼀样
f(x); //x是左值，所以T是int& param类型也是int&
f(cx); //cx是左值，所以T是const int &  param类型也是const int&
f(rx); //rx是左值，所以T是const int &  param类型也是const int&
f(27); //27是右值，所以T是int 			param类型就是int&&

```

#### 情景三：ParamType既不是指针也不是引用

当ParamType既不是指针也不是引用时，我们通过传值（pass-by-value）的⽅式处理：
这意味着无论传递什么param都会成为它的⼀份拷⻉——⼀个完整的新对象。事实上param成为⼀个新对象这⼀行为会影响T如何从expr中推导出结果。

1. 和之前⼀样，如果expr的类型是⼀个引用，忽略这个引用部分
2. 如果忽略引用之后expr是⼀个const，那就再忽略const。如果它是volatile，也会被忽略（volatile
  不常⻅，它通常用于驱动程序的开发中。关于volatile的细节请参⻅Item40)

> 在C++中，`volatile`是一个关键字，用于告诉编译器一个变量的值可能在程序的执行过程中被意外的修改，因此编译器不应该对该变量进行某些优化。具体来说，`volatile`可以用来：
>
> 1. 告诉编译器不要对该变量进行寄存器优化，因为该变量的值可能会被外部因素改变（例如硬件中断）。
> 2. 告诉编译器不要对该变量进行某些优化，以确保程序正确处理某些操作（例如多线程访问）。
> 3. 告诉编译器在每次访问该变量时都需要从内存中读取最新的值，而不是使用缓存中的值。
>
> 需要注意的是，使用`volatile`并不能完全解决多线程访问共享变量的问题，因为`volatile`只能确保读取的值是最新的，但无法保证多个线程访问该变量的顺序。如果需要进行多线程编程，建议使用更高级别的同步机制（例如互斥锁或信号量）。

```c++
template<typename T>
void f(T param); //以传值的⽅式处理param

int x=27; //如之前⼀样
const int cx=x; //如之前⼀样
const int & rx=cx; //如之前⼀样
f(x); //T和param都是int
f(cx); //T和param都是int
f(rx); //T和param都是int

```

注意即使cx和rx表⽰const值，param也不是const。这是有意义的。param是⼀个拷⻉⾃cx和rx且现在独⽴的完整对象。具有常量性的cx和rx不可修改并不代表param也是⼀样。这就是为什么expr的常量性或易变性（volatileness)在类型推导时会被忽略：因为expr不可修改并不意味着他的拷⻉也不能被修改。
认识到只有在传值给形参时才会忽略常量性和易变性这⼀点很重要.⼀个常量指针指向const字符串，在类型推导中这个指针指向的数据的常量性将会被保留，但是指针⾃⾝的常量性将会被忽略。



#### 数组实参

在模板类型推导中指针不同于数组，虽然它们两个有时候是完全等价的。关于这个等价最常⻅的例⼦是在很多上下文中数组会退化为指向它的第⼀个元素的指针.

因为数组形参会视作指针形参，所以传递给模板的⼀个数组类型会被推导为⼀个指针类型。

虽然函数不能接受真正的数组，但是可以接受指向数组的引用.使用引用,T会被正确推导,包括数组的大小.

当然作为⼀个现代C++程序员，你⾃然应该想到使用std::array而不是内置的数组.



#### 函数实参

在C++中不⽌是数组会退化为指针，函数类型也会退化为⼀个函数指针.

这⾥你需要知道：auto依赖于模板类型推导，正如我在开始谈论的，在⼤多数情况下它们的行为很直接。在通用引用中对于左值的特殊处理使得本来很直接的行为变得有些污点，然而，数组和函数退化为指针把这团⽔搅得更浑浊。有时你只需要编译器告诉你推导出的类型是什么。这种情况下，翻到item4,它会告诉你如何让编译器这么做。



#### 总结:

- 在模板类型推导时，有引用的实参会被视为无引用，他们的引用会被忽略

- 对于通用引用的推导，左值实参会被特殊对待

  > 对于左值实参，编译器会对其进行特殊处理，以避免出现歧义。具体来说，如果通用引用的实参是一个左值，那么它会被视为一个左值引用，并且类型推导过程中会忽略掉右值引用的候选项。这种特殊处理称为“左值引用折叠”。

- 对于传值类型推导，实参如果具有常量性和易变性会被忽略

- 在模板类型推导时，数组或者函数实参会退化为指针，除非它们被用于初始化引用

###  Item 2:理解auto类型推导

###  Item 3:理解decltype

###  Item 4:学会查看类型推导结果

## 二 auto

###  Item 5:优先考虑auto而非显式类型声明

###  Item 6:auto推导若非⼰愿，使用显式类型初始化惯用法

## 三 移步现代C++

###  Item 7:区别使用()和{}创建对象 

###  Item 8:优先考虑nullptr而非0和NULL

###  Item 9:优先考虑别名声明而非typedefs

###  Item 10:优先考虑限域枚举而非未限域枚举

###  Item 11:优先考虑使用deleted函数而非使用未定义的私有声明

###  Item 12:使用override声明重载函数

###  Item 13:优先考虑const_iterator而非iterator

###  Item 14:如果函数不抛出异常请使用noexcept

###  Item 15:尽可能的使用constexpr

###  Item 16:让const成员函数线程安全

###  Item 17:理解特殊成员函数函数的⽣成

## 四 智能指针

###  Item 18:对于独占资源使用std::unique_ptr

###  Item 19:对于共享资源使用std::shared_ptr

###  Item 20:像std::shared_ptr⼀样使用std::weak_ptr可能造成dangle

###  Item 21:优先考虑使用std::make_unique和std::make_shared而非new 

###  Item 22:当使用Pimpl惯用法，请在实现文件中定义特殊成员函数 

## 五 右值引用，移动语意，完美转发

###  Item 23:理解std::move和std::forward 

###  Item 24:区别通用引用和右值引用

###  Item 25:对于右值引用使用std::move，对于通用引用使用std::forward

###  Item 26:避免重载通用引用

###  Item 27:熟悉重载通用引用的替代品由

###  Item 28:理解引用折叠

###  Item 29:认识移动操作的缺点

###  Item 30:熟悉完美转发失败的情况

## 六 Lambda表达式

###  Item 31:避免使用默认捕获模式

###  Item 32:使用初始化捕获来移动对象到闭包中

###  Item 33:对于std::forward的auto&&形参使用decltype

###  Item 34:优先考虑lambda表达式而非std::bind

## 七 并发API

###  Item 35:优先考虑基于任务的编程而非基于线程的编程

###  Item 36:如果有异步的必要请指定std::launch::threads

###  Item 37:从各个⽅⾯使得std::threads unjoinable

###  Item 38:关注不同线程句柄析构行为 

###  Item 39:考虑对于单次事件通信使用void

###  Item 40:对于并发使用std::atomic，volatile用于特殊内存区

## 八 微调

###  Item 41:对于那些可移动总是被拷⻉的形参使用传值⽅式

###  Item 42:考虑就地创建而非插⼊