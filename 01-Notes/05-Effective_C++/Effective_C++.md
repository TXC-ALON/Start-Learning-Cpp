# Effective C++

[TOC]

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

好在<u>只有</u>四个次语言(:<)

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

const的一个妙处在于，他允许你指定一个语义约束，而编译器会强制实施这项约束。它允许你告诉编译器和其他程序员某值应该保持不变。只要存在这个事实，那么就应该说出来，这样可以获得编译器的帮助，确保这条约束不被违反。

关键字const多才多艺，你可以用它在classes外部修饰global或namespace作用域中的常量，或修饰文件、函数、或区块作用域中被声明为static的对象。也可以用它修饰classes内部的static和non-static成员变量。面对指针，你也可以指出指针自身、指针所指物，或者两者都（或都不）是const。

const语法虽然变化多端，但是并不复杂。

- 如果关键字const出现在星号左边，表示被指物是常量。如果出现在星号右边，表示指针自身是常量。如果出现在星号两边，表示被指物和指针两者都是常量。

- 如果被指物是常量，const在类型的前后其实没有区别。

  ```c++
  void f1(const Widget *pw); // f1 takes a pointer to a
  // constant Widget object
  void f2(Widget const *pw); // so does f2
  ```


- STL迭代器系以指针为根据塑模出来，所以迭代器的作用就像个T*指针。声明迭代器为const就像声明指针为const一样。表示这个迭代器不得指向不同的东西，但它所指的对象的值是可以改动的。如果想指的东西也不可以改动，那么就需要const_iterator。

  ```c++
  std::vector<int> vec;
  ...
  const std::vector<int>::iterator iter = // iter acts like a T* const
  vec.begin();
  *iter = 10; // OK, changes what iter points to
  ++iter; // error! iter is const
  std::vector<int>::const_iterator cIter = // cIter acts like a const T* vec.begin();
  *cIter = 10; // error! *cIter is const
  ++cIter; // fine, changes cIter
  ```

- const 最具威力的是面对函数声明时的应用。在一个函数声明式内，const可以和函数返回值、各参数、函数自身（如果是成员函数）产生关联。



#### const成员函数

将const用于成员函数的目的，是为了确认该成员函数可作用于const对象身上。

这一类成员函数之所以重要是因为：

- 它们使class接口比较容易被理解。（即知道哪个函数可以改动对象内容，哪个不行，非常重要）
- 它们使”操作const对象“成为可能。如【条款20】所说，改善c++ 程序的一个根本方法就是通过`pass bu reference to const`来传递对象。而该技术的前提就是我们有const成员函数来处理取得（并经过修饰而成）的const对象。

许多人漠视这一事实：两个成员函数如果只是常量性不同，可以被重载。

```c++
#include<iostream>
using namespace std;
class TextBlock {
public:
    TextBlock(std::string _text):text(_text){}
    const char& operator[](std::size_t position) const // operator[] for const objects
        { return text[position]; }
    char& operator[](std::size_t position) // operator[] for non-const objects
        { return text[position]; }
    // 如果把引用去掉会报error: lvalue required as left operand of assignment
private:
    std::string text;
};

int main(){
    TextBlock tb("Hello");
    std::cout << tb[0]; // calls non-const
// TextBlock::operator[]
    const TextBlock ctb("World");
    std::cout << ctb[0]; // calls const TextBlock::operator[]
    std::cout << tb[0]; // fine — reading a
// non-const TextBlock
    tb[0] = 'x'; // fine — writing a
// non-const TextBlock
    std::cout << ctb[0]; // fine — reading a
// const TextBlock
    ctb[0] = 'x'; // error! — writing a const TextBlock
    //error: assignment of read-only location 'ctb.TextBlock::operator[](0)'

    return 0;
}
```

也请注意，non-const operator[] 的返回类型是reference to char，而不是char。如果返回一个char，那么`tb[0] = ‘x'`就无法通过编译

如果函数的返回值是个内置类型，那么改动函数返回值从来就不合法，纵然合法，C++以by value 返回对象这一事实【条款20】意味着被改动的实际上是tb.text[0]的一个副本，不是tb.textp[0]自身，那不会是你想要的行为。

> ### **这里非常量版本的operator[]返回值是引用 ，为什么？**
>
> 这样做的原因是使用引用可以提高效率。当你使用 operator[] 访问 TextBlock 对象中的某个字符时，你希望能够直接获取到该字符，而不是复制一份副本。
>
> 如果 operator[] 返回值是一个普通的 char 类型，那么就会复制一份副本。如果 TextBlock 对象中的文本非常大，复制的过程就会变得很慢。
>
> 但是如果 operator[] 返回值是 char& 类型的引用，就能直接获取到原始的字符。这样做可以大大提高访问速度。
>
> 另外，返回值是引用还允许修改原始的字符。例如，你可以这样做：
>
> TextBlock tb; tb[0] = 'a'; // 这样做就是修改了 tb 中的第一个字符
>
> 如果 operator[] 返回值是 char 类型，就不能这样做了。你必须这样做：
>
> TextBlock tb; char c = tb[0]; c = 'a'; // 这样做并不会修改 tb 中的字符
>
> TextBlock tb; char c = tb[0]; // 这样做就是将 tb 中的第一个字符复制到 c 中
>
> 在这个例子中，tb[0] 这个表达式的值就是 tb 中的第一个字符。但是这个值不是一个变量，而是一个普通的 char 类型的值，它存储在临时变量中。
>
> 因此，你不能把一个 char 类型的值赋值给一个函数的返回值。相当于`‘a’=tb[0]`，这样做是非法的，编译器会报错。
>
> 这就意味着你必须复制一份副本，然后再修改副本。这样做虽然也能完成修改操作，但是效率要低得多。



成员函数为const意味着什么？

- bitwise constness（physical constness）

  成员函数只有在不改变对象值任何成员变量（static除外）时，才可以说是const。也就是说不改变对象内的任意一个bit。

  这样好处是编译器方便侦测违反点，但是不幸的是许多函数 不十分具备const性质也能通过bitwise测试。具体的说，就是一个更改了“指针所指物”的成员函数，虽然严格意义上不算是const，但是可以说是bitwise const。

- logical constness

  一个const成员函数可以修改它所处理的对象内的某些bits，但只有在客户端侦测不出的情况下才得如此。

  这时候就需要使用`mutable`，mutable会释放掉non-static成员变量的bitwise constness约束。（take advantage of C++’s const-related wiggle room known as mutable. mutable frees non-static data members from the constraints of bitwise constness:）,

  ```c++
  class CTextBlock {
  public:
  ...
  std::size_t length() const;
  private:
  char *pText;
  std::size_t textLength; // last calculated length of textblock
  bool lengthIsValid; // whether length is currently valid
  };
  std::size_t CTextBlock::length() const
  {
  if (!lengthIsValid) {
  textLength = std::strlen(pText); // error! can’t assign to textLength
  lengthIsValid = true; // and lengthIsValid in a const 
  } // member function
  return textLength;
  }
  
  class CTextBlock {
  public:
  ...
  std::size_t length() const;
  private:
  char *pText;
  mutable std::size_t textLength; // these data members may
  mutable bool lengthIsValid; // always be modified, even in 
  }; // const member functions
  std::size_t CTextBlock::length() const
  {
  if (!lengthIsValid) {
  textLength = std::strlen(pText); // now fine
  lengthIsValid = true; // also fine
  }
  return textLength;
  }
  ```



#### 在const 和  non-const成员函数中避免重复

```c++
class TextBlock {
public:
...
const char& operator[](std::size_t position) const
{
... // do bounds checking 边界检查
... // log access data	日志数据访问
... // verify data integrity //检验数据完整性
return text[position];
}
char& operator[](std::size_t position) 
{
... // do bounds checking
... // log access data
... // verify data integrity
return text[position];
}
private:
 std::string text;
};
```

这样会重复大量的代码，你真正应该做的是实现operator[]的机能，并令一个调用另外一个。这促使我们将常量性移除（casting away constness)

一般来说，转型(casting)是一个糟糕的想法【条款27】。但是代码重复也令人厌烦。本例中，常量版本做到了非常量版本的一切功能，只是多了个const修饰。这样把返回值的const去除就是安全的。

```c++
class TextBlock {
public:
...
const char& operator[](std::size_t position) const // same as before
{
...
...
...
return text[position];
}
char& operator[](std::size_t position) // now just calls const op[]
{
return
const_cast<char&>( // cast away const on
// op[]’s return type;
static_cast<const TextBlock&>(*this) // add const to *this’s type;
[position] // call const version of op[]
);
}
...
};
```

这里有两个转型动作，首先是为this添加const，这样在调用operator[]时得以调用const版本。第二则是从const operator[]的返回值中移除const。

添加const使用static_cast做了一次安全转型，而移除const的动作只能由const_cast完成（C-style的转型也行，不过【条款27】会说，这种转型很少是正确的选择）。

另外注意，使用const生成non-const版本是可以的，但是反之不行，因为non-const成员函数不承诺绝不改变对象的逻辑状态。



#### 总结：

- 将某些东西声明为const可帮助编译器侦测出错误用法，const可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体
- 编译器强制实施bitwise constness。但你编写程序时，应该使用概念上的常量性(conceptual constness)
- 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复

### 条款04 确定对象被使用前已先被初始化 

Make sure that objects are initialized before they're used

读取为初始化的值会导致不明确的行为。所以永远在使用对象之前将它初始化。

至于内置类型之外的，初始化责任落在构造函数身上，即确保每个构造函数都将对象的每个成员初始化。

**使用成员初值列(member initialization list)来替换赋值动作。**哪怕你想要用default构造一个成员变量，都用，只需要指定无物就行。

```c++
ABEntry::ABEntry()
: theName(), // call theName’s default ctor;
theAddress(), // do the same for theAddress;
thePhones(), // and for thePhones;
numTimesConsulted(0) // but explicitly initialize
{} // numTimesConsulted to zero
```

如果成员变量是const或references，它们就一定需要初值，而不能被赋值【条款05】。

C++有着十分固定的“成员初始化次序”：

- base classes更早于其derived classes被初始化【条款12】
- class的成员变量总是以其声明的次序被初始化（即使它们在成员初始列中以不同的次序出现）。

最后需要考虑的是**不同编译单元内定义之 non-local static 对象的初始化次序**

这句话很长，我们一步步来分析

首先是static对象，它的寿命从被构造出来直到程序结束为止，因此栈、堆对象都被排除。这种对象包括global对象、定义于namespace作用域内的对象、在classes内、在函数内、以及在file作用域内被声明为static的对象。函数内的static对象被称为local static对象。其他的static被称作non-local static。程序结束时static对象会被自动销毁，也就是它们的析构函数会在main()结束时被自动调用。

所谓编译单元(translation unit)是指产出单一目标文件的那些源码，基本上它是单一源码文件加上其所含入的头文件。

现在我们关系的问题至少涉及到两个源码文件，每一个内含至少一个non-local static对象。真正的问题是，如果某编译单元内的谋改革non-local static对象的初始化动作使用了另一编译单元内的某个non-local static 对象，它所用到的对象可能尚未被初始化。因为**C++对定义于不同编译单元内的non-local static对象的初始化次序并无明确定义**。为了解决这个问题，一种解决方法就是将每个non-local static对象搬到自己的专属函数内（该对象在此函数内被设定为static）。这种手法是单例模式（singleton）的一个常见生成手法。

内含static对象会让它在多线程下运行时有不确定性，解决方法是在程序的单线程启动阶段手动调用所有reference-returning 函数。这就会消除与初始化有关的竞速形式。



> # 单例模式
>
> 作者：培风而图南
> 链接：https://www.zhihu.com/question/34850977/answer/2440350126
> 来源：知乎
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
>
> 
>
> ## 0. 理解单例模式
>
> 什么是单例模式？为什么要使用单例模式？单例模式是保证类只有一个实例，并提供一个访问该实例的全局节点。该实例被所有[程序模块](https://www.zhihu.com/search?q=程序模块&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})共享。
>
> 单例模式是为了解决如下两个问题：
>
> （1）**控制类实例的个数，保证类只有一个实例**，例如对于数据库或者文件这种共享资源，保证资源类只有一个实例实际上就是控制了访问权限，同时时间只能有一个应用程序去访问；
>
> （2）有时候我们会使用全局变量去存储一些信息，但是很不安全，而且不方便管理，因为任何代码、任何地点都有可能改变全局变量的内容。可以利用单例模式为代替全局变量**提供一个全局访问的节点**，而不是将解决同一个问题的代码分散在程序各处。
>
> ![img](Effective_C++.assets/v2-7df5f1b254818e089ef123a32f5aa9b6_720w.webp)
>
> 如上图所示，我们看到的都是同一个对象。政府就是单例模式最好的示例。所有单例的实现都包含以下两个相同的步骤：
>
> - 将[默认构造函数](https://www.zhihu.com/search?q=默认构造函数&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})设为私有，防止其他对象使用单例类的构造函数创建实例。
> - 新建一个静态构建方法作为“构建”函数（作为获取实例的唯一接口）。该函数会“偷偷”调用[私有构造函数](https://www.zhihu.com/search?q=私有构造函数&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})来创建对象，并将其保存在一个[静态成员](https://www.zhihu.com/search?q=静态成员&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})变量中。此后所有对于该函数的调用都将返回这一缓存对象。
>
> 如果你的代码能够访问单例类，那它就能调用单例类的静态方法。无论何时调用该方法，它总是会返回相同的对象。单例模式分为如下三种：
>
> - 饿汉式（Eager Singleton）（[线程安全](https://www.zhihu.com/search?q=线程安全&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})，但是存在潜在风险）
> - 懒汉式（Lazy Singleton）（需要枷锁保证线程安全）
> - Meyers' Singleton （线程不安全，最优雅）
>
> 接下来，我们来看一下上述三种单例模式的代码实现。
>
> ------
>
> ## 1. 三种单例模式的实现
>
> ### **懒汉式（Lazy Singleton）**
>
> 如下图所示即为懒汉式单例模式的结构图，懒汉式单例实例是在第一次使用时才进行初始化，这叫做延时初始化。
>
> ![img](Effective_C++.assets/v2-11096ce2f1cdf4d80ac8001f24322259_720w.webp)
>
> 代码如下：
>
> ```cpp
> struct Singleton
> {
> public:
>     static Singleton* getInstance()
>     {
>       if(instance == nullptr)
>       {
>           instance = new Singleton;
>       }
>       return instance;
>     }
> 
>     Singleton(const Singleton&) = delete;
>     Singleton& operator=(const Singleton&) = delete;
> 
> private:
>     Singleton() = default;
>     
> private:
>     static Singleton* instance;
> };
> Singleton* Singleton::instance = nullptr;
> ```
>
> **首先**，上面的懒汉式单例模式存在内存泄漏的问题。有两种解决办法：
>
> 1. 使用独占式[智能指针](https://www.zhihu.com/search?q=智能指针&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})std::unique_ptr;
> 2. 使用静态的嵌套类对象；
>
> 使用智能指针的代码示例：
>
> ```cpp
> struct Singleton
> {
> public:
>     static Singleton* getInstance()
>     {
>         if(instance.get() == nullptr)
>         {
>             instance.reset(new Singleton);
>         }
>         return instance.get();
>     }
> 
>     Singleton(const Singleton_2&) = delete;
>     Singleton& operator=(const Singleton_2&) = delete;
> 
> private:
>     Singleton() = default;
> 
> private:
>     static std::unique_ptr<Singleton> instance;
> };
> std::unique_ptr<Singleton> Singleton::instance;
> ```
>
> 使用静态的嵌套类对象的代码示例：
>
> ```cpp
> // 使用静态的嵌套类对象
> struct Singleton
> {
> public:
>     static Singleton* getInstance()
>     {
>         if(instance == nullptr)
>         {
>             instance = new Singleton;
>         }
>         return instance;
>     }
> 
>     Singleton(const Singleton&) = delete;
>     Singleton& operator=(const Singleton&) = delete;
> 
> private:
>     struct Delector
>     {
>       ~Delector()
>       {
>           if(Singleton::instance != nullptr)
>           {
>               delete Singleton::instance;
>           }
>       }
>     };
>     static Delector delector;
> 
> private:
>     Singleton() = default;
> 
> private:
>     static Singleton* instance;
> };
> Singleton* Singleton::instance = nullptr;
> Singleton::Delector Singleton::delector;
> ```
>
> 在程序运行结束时，系统会调用静态成员delector的析构函数，该析构函数会删除单例的唯一实例。使用这种方法释放单例对象有以下特征：
>
> - 在单例类内部定义专有的嵌套类。
> - 在单例类内定义私有的专门用于释放的静态成员。
> - 利用程序在结束时析构全局变量的特性，选择最终的释放时机。
>
> **另外**，懒汉式单例模式是线程不安全的，因此上述的代码示例都是线程不安全的，在多线程情况下会出现race condition。要使其线程安全，能在多线程环境下实现单例模式，我们首先想到的是利用同步机制来正确的保护我们的shared data。可以使用双检测锁模式（DCL: Double-Checked Locking Pattern）。
>
> ```cpp
> static Singleton* getInstance()
> {
>     if(instance == nullprt)
>     {
>         Lock lock;  // 基于作用域的加锁，超出作用域，自动调用析构函数解锁
>         if(instance == nullptr)
>         {
>             instance = new Singleton();
>         }
>     }
>     return instance;
> }
> ```
>
> 注意，线程安全问题仅出现在第一次初始化（new）过程中，而在后面获取该实例的时候并不会遇到，也就没有必要再使用lock。双检测锁很好地解决了这个问题，它通过加锁前检测是否已经初始化，避免了每次获取实例时都要首先获取锁资源。
>
> 加入DCL后，其实还是有问题的，关于[memory model](https://www.zhihu.com/search?q=memory model&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})。在某些内存模型中（虽然不常见）或者是由于编译器的优化以及运行时优化等等原因，使得instance虽然已经不是nullptr但是其所指对象还没有完成构造，这种情况下，另一个线程如果调用getInstance()就有可能使用到一个不完全初始化的对象。换句话说，就是代码中第3行：if(instance == nullprt)和第8行instance = new Singleton();没有正确的同步，在某种情况下会出现new返回了地址赋值给instance变量而Singleton此时还没有构造完全，当另一个线程随后运行到第3行时将不会进入if从而返回了不完全的实例对象给用户使用，造成了严重的错误。
>
> 在C++11没有出来的时候，只能靠插入两个[memory barrier](https://www.zhihu.com/search?q=memory barrier&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})（内存屏障）来解决这个错误，但是C++11引进了memory model，提供了Atomic实现内存的同步访问，即不同线程总是获取对象修改前或修改后的值，无法在对象修改期间获得该对象。
>
> 因此，在有了C++11后就可以正确的跨平台的实现DCL模式了，利用atomic，代码如下：
>
> ```cpp
> atomic<Singleton*> Singleton::pInstance{ nullptr };
> Singleton* Singleton::getInstance() {
>     if (pInstance == nullptr) { 
>         lock_guard<mutex> lock{ mutW }; 
>         if (pInstance == nullptr) { 
>             pInstance = new Widget(); 
>         }
>     } 
>     return pInstance;
> }
> ```
>
> C++11中的atomic类的默认memory_order_seq_cst保证了3、6行代码的正确同步，由于上面的atomic需要一些性能上的损失，因此我们可以写一个优化的版本：
>
> ```cpp
> atomic<Singleton*> Singleton::pInstance{ nullptr };
> Singleton* Singleton::getInstance() {
>     Singleton* p = pInstance;
>     if (p == nullptr) { 
>         lock_guard<mutex> lock{ mutW }; 
>         if ((p = pInstance) == nullptr) { 
>             pInstance = p = new Widget(); 
>         }
>     } 
>     return p;
> }
> ```
>
> C++11规定了[local static](https://www.zhihu.com/search?q=local static&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。在C++11标准下，《Effective C++》提出了一种更优雅的单例模式实现，使用函数内的 local static 对象。这样，只有当第一次访问getInstance()方法时才创建实例。这种方法也被称为**Meyers' Singleton**。C++0x之后该实现是线程安全的，C++0x之前仍需加锁。
>
> ```cpp
> class Singleton
> {
> private:
>     Singleton() { };
> public:
>     static Singleton& getInstance()
>     {
>         static Singleton instance;
>         return instance;
>     }
>     Singleton(const Singleton&) = delete;
>     Singleton& operator=(const Singleton&) = delete;
> };
> ```
>
> ### **饿汉式（Eager Singleton）**
>
> 饿汉式单例模式是指单例实例在程序运行时被立即执行初始化。
>
> ```cpp
> class Singleton
> {
> private:
>     static Singleton instance;
> private:
>     Singleton() = default;
> public:
>     static Singleton& getInstance() {
>         return instance;
>     }
>     
>     Singleton(const Singleton&) = delete;
>     Singleton& operator=(const Singleton&) = delete ;
> }
> Singleton Singleton::instance;
> ```
>
> 由于在main函数之前初始化，所以没有线程安全的问题。但是潜在问题在于no-local static对象（函数外的static对象）在不同编译单元中的初始化顺序是未定义的。也即，static Singleton instance;和static Singleton& getInstance()二者的初始化顺序不确定，如果在初始化完成之前调用 getInstance() 方法会返回一个未定义的实例。
>
> 
>
> **附：C++静态对象的初始化**
> **non-local static对象（函数外）**
>
> C++规定，non-local static 对象的初始化发生在main函数执行之前，也即main函数之前的单线程启动阶段，所以不存在线程安全问题。但C++没有规定多个non-local static 对象的初始化顺序，尤其是来自多个编译单元的non-local static对象，他们的初始化顺序是随机的。
>
> **local static 对象（函数内）**
>
> 对于local static 对象，其初始化发生在控制流第一次执行到该对象的初始化语句时。多个线程的控制流可能同时到达其初始化语句。
>
> 在C++11之前，在多线程环境下local static对象的初始化并不是线程安全的。具体表现就是：如果一个线程正在执行local static对象的初始化语句但还没有完成初始化，此时若其它线程也执行到该语句，那么这个线程会认为自己是第一次执行该语句并进入该local static对象的构造函数中。这会造成这个local static对象的重复构造，进而产生[内存泄露](https://www.zhihu.com/search?q=内存泄露&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2440350126"})问题。所以，local static对象在多线程环境下的重复构造问题是需要解决的。
>
> 而C++11则在语言规范中解决了这个问题。C++11规定，在一个线程开始local static 对象的初始化后到完成初始化前，其他线程执行到这个local static对象的初始化语句就会等待，直到该local static 对象初始化完成。



> ### **如果有多个 non-local static 对象定义在不同的编译单元内，并且这些对象之间存在依赖关系，那么可以使用以下方法来解决这种弊端：**
>
> 1. 使用全局函数或者静态成员函数来初始化这些对象。例如：
>
> ```c++
> Copy codeint x = 42;
> int y = x + 1;
> 
> int getX() { return x; }
> int getY() { return y; }
> 
> class A {
> public:
>   static int x;
>   static int y;
>   static void init() {
>     x = ::x;
>     y = ::y;
>   }
> };
> 
> int A::x = getX();
> int A::y = getY();
> ```
>
> 这样可以保证 x 和 y 的初始化次序。
>
> 2.使用单例模式或者全局对象来初始化这些对象。例如：
>
> ```c++
> Copy codeclass X {
> public:
>   X() {
>     // 初始化代码
>   }
> };
> 
> X x;
> 
> int main() {
>   // 使用 x
> }
> ```
>
> 这样可以保证 x 的初始化次序。
>
> 3.使用懒惰初始化模式来初始化这些对象。例如：
>
> ```c++
> Copy codeint x;
> int y;
> 
> int getX() {
>   if (!x) {
>     x = 42;
>   }
>   return x;
> }
> 
> int getY() {
>   if (!y) {
>     y = getX() + 1;
>   }
>   return y;
> }
> 
> int main() {
>   // 使用 x 和 y
> }
> ```
>
> 这样可以在第一次使用 x 和 y 时才进行初始化，从而保证初始化次序。
>
> 4.使用 C++11 中的静态变量初始化模型来初始化这些对象。例如：
>
> ```c++
> Copy codeint x = 42;
> int y = x + 1;
> 
> class A {
> public:
>   static int x;
>   static int y;
> };
> 
> int A::x = ::x;
> int A::y = ::y;
> ```
>
> 这样可以保证 x 和 y 的初始化次序。
>
> 5.使用编译器特定的方法来解决这个问题。
>
> 每个编译器都有不同的方法来处理这种情况，可以查看编译器文档或者使用编译器提供的工具来解决这个问题



> ### **使用 reference-returning 函数来防止多个non-local static 对象初始化次序问题**
>
> 在 C++ 中，使用静态对象的初始化顺序可能会导致问题，因为它们的初始化顺序是未定义的。这意味着，在编译器的不同版本之间，或者在同一版本的编译器的不同执行之间，静态对象的初始化顺序可能会有所不同。
>
> 一种常见的解决方案是使用 reference-returning 函数，这样可以避免多个静态对象初始化次序问题。在这种方法中，每个静态对象都有一个函数，该函数返回该对象的引用。这样，就可以通过调用函数来访问静态对象，而不是直接访问它们。
>
> 举个例子，假设我们有两个静态对象 `A` 和 `B`，并且我们希望在使用这些对象之前对它们进行初始化。我们可以使用以下代码来实现：
>
> ```c++
> #include <iostream>
> 
> struct A {
>   A() { std::cout << "A" << std::endl; }
> };
> 
> struct B {
>   B() { std::cout << "B" << std::endl; }
> };
> 
> A& getA() {
>   static A a;
>   return a;
> }
> 
> B& getB() {
>   static B b;
>   return b;
> }
> 
> int main() {
>   A& a = getA();
>   B& b = getB();
>   return 0;
> }
> ```
>
> 在这段代码中，我们定义了两个结构体 `A` 和 `B`，并为它们分别定义了一个构造函数。我们定义了两个函数 `getA()` 和 `getB()`，这两个函数分别返回静态对象 `a` 和 `b` 的引用。最后，在 `main()` 函数中，我们通过调用 `getA()` 和 `getB()` 函数来获取这两个对象的引用。
>
> 这样做的好处是，我们可以确保在使用静态对象之前，它们已经被正确地初始化了。因为在使用静态对象之前，必须先调用返回它们的引用的函数，这就保证了静态对象的初始化次序。
>
> 此外，使用 reference-returning 函数还有另一个好处，即可以避免复制静态对象的开销。因为返回的是引用，所以不需要进行复制操作。这在某些情况下可能会带来性能提升。
>
> 总的来说，使用 reference-returning 函数来访问静态对象可以帮助我们避免多个静态对象初始化次序问题，同时也可以带来性能提升。

#### 总结：

- 为内置型对象进行手工初始化，因为C++不保证初始化它们
- 构造函数最好使用成员初值列，而不要在构造函数本体内使用赋值操作。初值列列出的成员变量，其排列次序应该和它们在class中的声明次序相同。
- 为免除“跨编译单元之初始化次序”问题，请以local static对象替换non-local static对象。

## 第二章 构造/析构/赋值运算

 [Constructors, Destructors, and Assignment Operators]

几乎你写的每一个类都会有一个或多个构造函数，一个析构函数，一个 copy assignment操作符。如果这些函数犯错，会导致深远且令人不快的影响。

### 条款05 了解C++默默编写并调用哪些函数

Know what functions C++ silently writes and calls

当C++ 处理过它后，是的，如果你自己没有声明，编译器就会为它声明（编译器版本的）一个copy构造函数，一个拷贝操作符，一个析构函数。如果你连构造函数，编译器也会为你声明一个default构造函数。所有这些函数都是public且inline的【条款30】

```c++
class Empty{};
//it’s essentially the same as if you’d written this:
class Empty {
public:
Empty() { ... } // default constructor
Empty(const Empty& rhs) { ... } // copy constructor
~Empty() { ... } // destructor — see below
// for whether it’s virtual
Empty& operator=(const Empty& rhs) { ... } // copy assignment operator
};
```

惟有当这些函数被调用，它们才会被编译创建出来。不过这些函数被需要是很常见的事。

```c++
Empty e1; // default constructor;
// destructor
Empty e2(e1); // copy constructor 
e2 = e1; // copy assignment operator 
```

编译器产出的析构是non-virtual【条款07】，除非这个class的base class 自身声明有virual 析构函数，这时这个函数的虚属性主要来自base class。



不会为类生成默认拷贝赋值运算符的几种情况：

因为编译器生成的拷贝赋值运算符需要对所有的非静态成员变量进行赋值

- 如果你想在一个内含reference成员的class内支持赋值操作，那么就必须自己定义拷贝操作符。
- 对于内含const成员的classes，编译器的反应也一样，更改const成员也是不合法的
- 如果基类将copy assignment 声明为private，那么编译器拒绝为它的子类生成拷贝赋值运算符。因为肯定会涉及到拷贝基类的成员。



#### 总结：

- 编译可以暗自为class 创建default构造函数，copy构造函数，copy assignment 操作符，以及析构函数。

### 条款06 若不想使用编译器自动生成的函数，就该明确拒绝

Explicitly disallow the use of compiler-generated

通过明确声明一个生源函数，你阻止了编译器暗自创建其专属版本，而令这些函数为private，使得阻止别人调用这些函数。

一般来说，这样做并不是完全安全。因为成员函数和友元函数还是可以调用你的private 函数。除非你不去定义它们。

不过这个伎俩是如此为大家接受，以至于标准库都是这样用的。不过在c++11后，程序员只需在函数声明后加上 `=delete;`，就可将该函数禁用。

```c++
class ios_base
  {
    ...
#if __cplusplus < 201103L
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 50.  Copy constructor and assignment operator of ios_base
  private:
    ios_base(const ios_base&);

    ios_base&
    operator=(const ios_base&);
#else
  public:
    ios_base(const ios_base&) = delete;

    ios_base&
    operator=(const ios_base&) = delete;

  protected:
    void
    _M_move(ios_base&) noexcept;

    void
    _M_swap(ios_base& __rhs) noexcept;
#endif
};
```

更进一步，可以将copy构造函数和copy assignment操作符写在一个专门为了阻止copying动作而设计的base类里，且声明为private

```c++
class Uncopyable {
protected: // allow construction
Uncopyable() {} // and destruction of
~Uncopyable() {} // derived objects...
private:
Uncopyable(const Uncopyable&); // ...but prevent copying
Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale: private Uncopyable { // class no longer
... // declares copy ctor or
}; // copy assign. operator
```

这样，即使是member或friend函数尝试拷贝HomeForSale对象，编译器边试着生成一个copy构造函数和一个copy assignment操作符。正如【条款12】所说，在这些函数的编译器生成版会尝试调用对应的基类，但是会被拒绝，因为基类的拷贝函数是private。

#### 总结：

- 为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为private且不予实现。
- 像使用Uncopyable这样写进基类里，也是一种方法（不过我觉得有些杀鸡用牛刀了）

### 条款07 为多态基类声明virtual析构函数

Declare destructors virtual in polymorphic

实际情况中，常常会发生一种灾难，即derived class对象经由一个base class指针被删除，而base class带着一个non-virtual析构函数。实际执行结果就是对象的derived部分没有被销毁。

解决方法也很简单，给基类设置一个virtual析构函数，之后就会调用derived自己客制化的析构函数。

当类里有virtual函数，对象必须携带vptr指针，指向一个由函数指针指向的vtbl（virtual table），每一个带有virtual函数的class都有一个相应的vtbl。因此，对象的体积会增加。不足以直接塞入指定bit的缓存器，也不再能和别的语言直接互通（除非明确补偿vptr）。

因此一般的心得，除非当类里含有至少一个virtual函数，才会为它声明virtual析构函数。

令一个类带一个pure virtual析构函数，但是你也得为证析构函数提供一份定义。因为析构函数的运作方式是，最深层派生类的那个类的析构函数最先被调用，然后是每一个base class的析构函数被调用，编译器会在AWOV的子类的析构函数中创建对~AWOV的调用动作，所以你必须为这个函数提供给一个定义。

```c++
class AWOV { // AWOV = “Abstract w/o Virtuals”
public:
virtual ~AWOV() = 0; // declare pure virtual destructor
};
AWOV::~AWOV() {} // definition of pure virtual dtor
```



#### 总结：

- polymorphic（带多态性质的） base classes 应该声明一个virtual析构函数，如果class带有任何virtual函数，它就应该拥有一个virtual析构函数。
- Classes的设计如果不是作为base classes使用（譬如【条款06】的Uncopyable），或是不是为了具有多态性，那么就不该声明virtual 析构函数。

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