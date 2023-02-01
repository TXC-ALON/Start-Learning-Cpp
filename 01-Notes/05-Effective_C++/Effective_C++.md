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

- **bitwise constness**（physical constness）

  成员函数只有在不改变对象值任何成员变量（static除外）时，才可以说是const。也就是说不改变对象内的任意一个bit。

  这样好处是编译器方便侦测违反点，但是不幸的是许多函数 不十分具备const性质也能通过bitwise测试。具体的说，就是一个更改了“指针所指物”的成员函数，虽然严格意义上不算是const，但是可以说是bitwise const。

- **logical constness**

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

编译器为你写函数，default构造函数和析构函数主要是给编译器一个地方用来放置“藏身幕后”的代码，比如调用base classes和non-static 成员变量的构造函数和析构函数。注意，编译器产生的析构函数是non-virtual【条款07】，除非这个class的base class 自身声明有virual 析构函数，这时这个函数的虚属性主要来自base class。

至于copying构造函数，编译器创建的版本只是单纯地将来源对象的每一个non-static 成员变量拷贝到目标对象。



不会为类生成默认拷贝赋值运算符的几种情况：

因为编译器生成的拷贝赋值运算符需要对所有的非静态成员变量进行赋值

- 如果你想在一个内含reference成员的class内支持赋值操作，那么就必须自己定义拷贝操作符。
- 对于内含const成员的classes，编译器的反应也一样，更改const成员也是不合法的
- 如果基类将copy assignment 声明为private，那么编译器拒绝为它的子类生成拷贝赋值运算符。因为肯定会涉及到拷贝基类的成员。



#### 总结：

- 编译器可以暗自为class 创建default构造函数，copy构造函数，copy assignment 操作符，以及析构函数。

### 条款06 若不想使用编译器自动生成的函数，就该明确拒绝

Explicitly disallow the use of compiler-generated

通过明确声明一个成员函数，你阻止了编译器暗自创建其专属版本，而令这些函数为private，使得阻止别人调用这些函数。

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

C++ 并不禁止在析构函数吐出异常，但是并不鼓励你这样做，譬如一个vector<tempclass>v，如果v[0]的析构抛出异常，那么v后面的类也应该被销毁。

```c++
class DBConnection
{
public:
    ... 
    static DBConnection create(); // function to return
    // DBConnection objects; params
    // omitted for simplicity
    void close(); // close connection; throw an
};                // exception if closing fails
class DBConn
{             // class to manage DBConnection
public:       // objects ...
    ~DBConn() // make sure database connections
    {         // are always closed
        db.close();
    }

private:
    DBConnection db;
};
// That allows clients to program like this:
{                                       // open a block
    DBConn dbc(DBConnection::create()); // create DBConnection object
    // and turn it over to a DBConn
    // object to manage
    ... // use the DBConnection object
    // via the DBConn interface
} // at end of block, the DBConn
  // object is destroyed, thus
  // automatically calling close on
  // the DBConnection object
```



对于这种问题一般有两种解决方法

- 如果close抛出异常就结束程序，通常通过调用abort来完成

  ```c++
  DBConn::~DBConn()
  {
  try { db.close(); }
  catch (...) {
  make log entry that the call to close failed;
  std::abort();
  }
  }
  ```

  当程序遭遇一个于析构期间发生的错误后无法继续执行，通过调用abort可以抢先致“不明确行为”于死地。

- 吞下因调用close而导致的异常

  ```c++
  DBConn::~DBConn()
  {
  try { db.close(); }
  catch (...) {
  make log entry that the call to close failed;
  }
  }
  ```

  一般而言，将异常吞掉都是一个坏主意，因为它压制了某些动作失败的重要信息，然而有时候吞下异常比“草率结束程序”或“不明确行为带来的风险”好。当程序必须能够继续可靠的运行，即使在遭遇并忽略一个异常后。

但是这两种方法都无法对“导致close抛出异常的情况”作出反应

一种较好的策略是重新设计DBConn接口，将close的权利提供给客户，而DBConn也可也追踪它管理的DBConnection是否已被关闭。并在答案为否的情况下由其析构函数关闭之。但是如果DBConnection析构函数调用close失败，我们又将退回到“强迫结束程序”或“吞下异常”的老路。

```c++
class DBConn {
public:
    ...
    void close() // new function for
    { // client use
    db.close();
    closed = true;
}
~DBConn()
{
    if (!closed) {
    try { // close the connection
    db.close(); // if the client didn’t
}
catch (...) { // if closing fails,
	make log entry that call to close failed; // note that and ... // terminate or swallow
}
}
}
private:
	DBConnection db;
	bool closed;
};
```

将调用close 的责任从析构函数转移到用户手上（但DBConn析构函数中仍有一个双保险调用）可能会给你一种甩锅的感觉，你甚至会认为它违反了【条款18】所说的“让接口易于使用”，但这些污名都不成立。因为如果某个操作可能在失败时抛出异常，而又存在某种需要必须处理该异常，那么这个异常必须来自析构函数以外的函数。因为析构函数吐出异常就是危险。总会带来过早结束程序或发生不明确行为的风险。由客户自己调用close是给他们一个处理错误的机会。



#### 总结：

- 析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，仍然让吞下他们“不传播”或结束程序。
- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么class应该提供一个普通函数（而非在析构函数中）执行该操作。





### 条款09 绝不在构造和析构过程中调用virtual函数

Never call virtual functions during construction or destruction

因为子类中的基类成分会先在子类自身成分被构造前构造妥当，所以你在derived类构造函数里调用virtual函数，这时候调用的版本并非是derived版本，而是base  类版本。

在derived  class对象的base class构造期间，对象的类型是base class而不是derived class。不只是virtual 函数会被编译器解析至base class。若使用运行期类型信息（runtime type information，例如dynamic_cast【条款27】和typeid），也会把对象视为base class类型。

同理也适用于析构函数，一旦derived class 析构函数开始执行，对象内的derived class成员变量便呈现为未定义值。

想要保证Transaction继承体系上的对象被创建，就有适当版本的logTransaction被调用。一种方法就是在class Transaction内将logTransaction改为non-virtual，然后要求derived class构造函数传递必要的信息给Transaction构造函数。

```c++
#include <string>
#include<iostream>
using namespace std;
class Transaction {
public:
    explicit Transaction(const std::string& logInfo);
    void logTransaction(const std::string& logInfo) const; // now a non-virtual func
};

Transaction::Transaction(const std::string& logInfo)
{
    logTransaction(logInfo); // now a non-virtual call
}

void Transaction::logTransaction(const std::string& logInfo) const
{
    cout<<"Transaction"<<"   "<< logInfo<<endl;
}

class BuyTransaction: public Transaction {
public:
    BuyTransaction(int parameters)
            : Transaction(createLogString(parameters)) // pass log info
    {
        cout<<"BuyTransaction"<<endl;
    } // to base class

private:
    static std::string createLogString(int parameters)
    {
// create and return log string based on parameters
        if(parameters > 20){
            return "parameters > 20";
        }
        else{
            return "parameters <= 20";
        }

    }
};

int main()
{
    BuyTransaction bt(42);
    return 0;
}
```

换句话说，你无法使用virtual函数从base classes向下调用，在构造期间，你可以藉由令基类将必要的构造信息向上传递给base classes构造函数来借以弥补。

createLogString 是 BuyTransaction 类的一个私有的、静态的函数，因为此函数为static，也就不可能指向“初期未成熟之BuyTransaction对象内尚未初始化的成员变量”，静态函数不能访问类的非静态数据成员，因为静态函数并不依赖于任何特定的对象。因此，它不能访问类的非静态数据成员，因为这些数据成员是属于对象的，而不是属于类的。



#### 总结：

- 在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class（比起当前指向构造函数和析构函数的那层）[Don’t call virtual functions during construction or destruction, because such calls will never go to a more derived class than that of the currently executing constructor or destructor.]

### 条款10 令operator = 返回一个 reference to *this

Have assignment operators return a reference to *this

在赋值时，我们常常忽视一点，即赋值可以连续赋值，同时采用右结合律。

为了实现这两点，赋值操作符必须返回一个引用指向操作符的左侧实参，这是你为classes实现赋值操作符时应该遵守的条款。

```c++
class Widget {
public:
...
    Widget& operator=(const Widget& rhs) // return type is a reference to
    { // the current class
    ...
    return *this; // return the left-hand object
	}
...
};

class Widget {
public:
    ...
    Widget& operator+=(const Widget& rhs) // the convention applies to
    { // +=, -=, *=, etc.
    	...
        return *this;
	}
	Widget& operator=(int rhs) // it applies even if the
	{ // operator’s parameter type ... // is unconventional
		return *this;
	}
...
};
```



```c++
class MyClass {
private:
    int x;
    int y;

public:
    MyClass() {
        x = 0;
        y = 0;
    }

    MyClass(int x, int y) {
        this->x = x;
        this->y = y;
    }

    MyClass(const MyClass& other) {
        x = other.x;
        y = other.y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    // overload the assignment operator
    MyClass& operator=(const MyClass& other) {
        // check for self-assignment
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    MyClass& operator+=(const MyClass& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    MyClass& operator++() { // prefix
        ++x;
        ++y;
        return *this;
	}
	MyClass operator++(int) { // postfix
        MyClass tmp(*this);
        operator++();
        return tmp;
	}
};

int main() {
    MyClass obj1, obj2(1, 2), obj3(3, 4);
    obj1 = obj2 = obj3; // assigns obj3's value to obj2, then obj2's value to obj1

    obj1.setX(10).setY(20);  // assigns 10 to x and 20 to y
    std::cout << obj1.getX() << ' ' << obj1.getY() << std::endl;
}

```

> 在 C++ 中，一元自增运算符 (++) 有两种形式：前缀形式 (++x) 和后缀形式 (x++)。前缀形式直接改变原来的对象,通常返回 *this 的引用；而后缀形式会先返回原来的对象，再改变对象。
>
> 由于后缀形式的一元自增运算符需要先返回原来的值，因此不能返回 this 的引用。相反，它必须返回一个拷贝，该拷贝包含原始对象的值。这样，在使用后缀形式的一元自增运算符时，可以保留原始对象的值。
>
> 返回拷贝会增加一些额外的开销，因为需要复制一个对象，如果这种设计不是必要的话，应该尽量避免使用。
>
> 需要注意的是，重载运算符需要遵循严格的语义，因此在实现之前应该仔细考虑它的行为和后果。
>
> 在 C++ 中，编译器通过运算符函数的参数个数来识别运算符的前缀和后缀形式。如果一个运算符函数没有参数，那么就是前缀形式；如果有一个参数，那么就是后缀形式。
>
> 这就是为什么在实现后缀形式的自增运算符时，需要添加一个不会被使用的 int 参数，以便区分前缀和后缀形式，使编译器能够正确识别并调用合适的运算符函数。

#### 总结：

- 令赋值（assignment） 操作符返回一个reference to *this

### 条款11 在operator = 中处理“自我赋值”

Handle assignment to self in operator=

“自我赋值“发生在对象被赋值给自己时。

一般而言，如果某段代码操作指针或引用，而他们被用来指向多个相同类型的对象，那么就需考虑这些对象是否为同一个。实际上两个对象只要来自同一个继承体系，他们甚至不需声明为相同类型就可能造成“别名”，因为一个基类的指针或引用可以指向一个子类对象。

如果遵循【条款13】【条款14】，你会使用对象来管理资源，并且你可以确定所谓资源管理对象在copy发生时有着正确的举措。这种情况下，你的赋值操作符或许是“自我赋值安全的”。然而，如果你尝试自行管理资源（如果你打算写一个用于资源管理的类就得这样做），可能会掉进“在停止使用资源之前意外释放了它”的陷阱。

比如建立了一个class用于保存一个指针指向一块动态分配的位图。想用rhs来替换当前的pb指针

但是下面的代码，operator=函数内的*this和rhs可能是同一个对象。那么delete就会销毁当前对象的bitmap。

```c++
class Bitmap { ... };
class Widget {
    ...
    private:
    Bitmap *pb; // ptr to a heap-allocated object
};
Widget&
    Widget::operator=(const Widget& rhs) // unsafe impl. of operator=
    {
    delete pb; // stop using current bitmap
    pb = new Bitmap(*rhs.pb); // start using a copy of rhs’s bitmap
    return *this; // see Item 10
}
```

欲阻止这一错误，传统方法是藉由operator=最前面的一个证同测试(identity)来达到自我赋值的检验目的。

```c++
Widget& Widget::operator=(const Widget& rhs)
{
    if (this == &rhs) return *this; // identity test: if a self-assignment,
    // do nothing
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```

前一版不仅不具备自我赋值安全性，也不具备异常安全性。这个新版本依然有着异常方面的麻烦。【条款29】深入讨论了异常安全性。

下面的代码就比之前的好些（虽然不考虑证同，因为大多数情况下，能保证异常安全基本上可以保证自我赋值安全），在复制pb所指的对象之前，不删除pb。这时，如果new Bitmap发生异常，pb保持原状，这段代码还是能够自我赋值。（？todo）

```c++
Widget& Widget::operator=(const Widget& rhs)
{
    Bitmap *pOrig = pb; // remember original pb
    pb = new Bitmap(*rhs.pb); // point pb to a copy of rhs’s bitmap
    delete pOrig; // delete the original pb
    return *this;
}
```

> 这段代码将 Widget 对象的状态更新为 rhs 对象的状态。首先，它通过 new 关键字分配内存来存储一个新的 Bitmap，并将其初始化为 rhs 对象中 Bitmap 的拷贝。如果在 new Bitmap 操作过程中发生异常，将抛出 std::bad_alloc。
>
> 在这种情况下，程序将无法继续执行。在这段代码中，它没有使用异常安全的内存分配，或者异常处理机制来处理异常情况，导致程序无法继续执行。在 new 操作失败后，delete pOrig并没有执行，所以会造成内存泄漏。
>
> 如果想要正常运行，应该使用异常安全的内存分配，比如std::unique_ptr或std::shared_ptr来管理动态分配的内存,或者使用 try-catch 机制来捕获和处理异常。
>
> ```c++
> Widget& Widget::operator=(const Widget& rhs)
> {
>     try{
>         Bitmap *pOrig = pb; // remember original pb
>         pb = new Bitmap(*rhs.pb); // point pb to a copy of rhs’s bitmap
>         delete pOrig; // delete the original pb
>         return *this;
>     } catch(std::bad_alloc &ex)
>     {
>         std::cout<<ex.what()<<std::endl;
>         throw ex;
>     }
> }
> 
> ```



另外一种替代方案是所谓的copy-swap技术，

```c++
class Widget {
    ...
    void swap(Widget& rhs); // exchange *this’s and rhs’s data; ... // see Item 29 for details
};
Widget& Widget::operator=(const Widget& rhs)
    {
    Widget temp(rhs); // make a copy of rhs’s data
    swap(temp); // swap *this’s data with the copy’s
    return *this;
	}
```

这个一变形采用了以下事实：

* 某class的copy assignment操作符可能被声明为“以by value方式接受实参”
* 以“by value”方式传递东西会造成一份附件【条款20】

```c++
Widget& Widget::operator=(Widget rhs) // rhs is a copy of the object
{ 	// passed in — note pass by val
    swap(rhs); // swap *this’s data with
    // the copy’s
    return *this;
}
```

作者比较忧虑这个做法，他认为它为了伶俐灵巧的修补而牺牲了清晰性，然而将copying操作从函数本体移至函数参数构造阶段，却可令编译器有时生成更高效的代码。

#### 总结：

- 确保当对象自我赋值时，operator= 有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址，精心周到的语句顺序、以及copy-and-swap
- 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。

### 条款12 复制对象时勿忘其每一个成分 

Copy all parts of an object

设计良好的面向对象系统（OO-systems）会将对象的内部封装起来，只留两个函数负责对象拷贝（复制），那就是带着适当名称的copy构造函数和copy assignment 操作符。并称为copying函数。

编译器会在必要时为我们的类创建copying函数，如果你自己声明自己的copying函数，意思就是告诉编译器你并不喜欢缺省实现中的某些行为。编译器就好像被冒犯一样，会以一种奇怪的方式回敬：当你代码几乎必然出错时却不提醒你。

当你新添加新的成员函数时，copying函数也应该同时更新。而编译器不会告诉你这一点。也不会为你补全。

所以，当你编写一个copying函数，请确保：

- 复制所有local成员变量
- 调用所有base class内的适当copying 函数。

同时请注意，令某个copy函数调用另一个copy函数是不合理的：

- 令copying assignment 操作符调用copy构造函数是不合理的，因为这就像试图构造一个已经存在的对象。
- 令copying 构造函数调用copying assignment 操作符也是无意义的，构造函数用来初始化新对象，而assignment操作符只施行于已初始化的对象上。

#### 总结：

- Copying 函数应该确保复制“对象内的所有成员变量”及“所有base-class成分”
- 不要尝试以某个copying函数实现另一个copying函数，应该将共同的机能放进第三个函数中，并由两个copying函数共用。

## 第三章 资源管理

**[Constructors, Destructors, and Assignment Operators]**

所谓资源就是，一旦用了它，将来必须还给系统。如果不这样，糟糕的事情就会发生。C++程序最常用的资源就是动态分配内存（如果你分配内存却从来不曾归还它，就会导致内存泄漏）。但内存只是你必须管理的众多资源之一。其他常见资源还包括文件描述器（file descriptors）、互斥锁（mutex locks）、图形界面中的字型fonts和笔刷、数据库连接、以及网络sockets。不论哪一种资源，重要的是，当你不再使用它时，必须将它还给系统。

本章一开始是一个直接而易懂且基于对象的资源管理办法，建立在C++对构造函数、析构函数、copying函数的基础上，经验表明，经过训练后严守这些做法，几乎可以消除资源管理问题。然后本章的某些条款将专门用来对付内存管理。这些排列在后的专属条款弥补了先前一般化条款的不足，因为管理内存的那个对象必须知道如何适当而正确的工作。

### 条款13 以对象管理资源

Use objects to manage resources

```c++
void f()
{
Investment *pInv = createInvestment(); // call factory function
... // use pInv
delete pInv; // release object
}
```

若是在`...`里面有return或continue类的语句，那么就有可能没有释放调用的资源。

为确保函数返回的资源总会被释放，我们需要将资源放进对象里，当控制流离开f，该对象的析构函数自动调用机制会自动释放那些资源。



用auto_ptr以避免f函数潜在的资源泄漏可能性（但是auto_ptr已经被废弃了）

> auto_ptr是C++标准库中的一个智能指针类型，它能自动释放所指向的内存。在C++11标准中，auto_ptr被废弃了，因为它存在一些问题，如不支持移动语义、不能与其他智能指针类型一起使用等。
>
> 替代auto_ptr的是std::unique_ptr和std::shared_ptr，分别用于表示独占所有权和共享所有权的智能指针。下面是一个使用std::unique_ptr的代码示例：
>
> ```c++
> include <memory>
> 
> int main() {
>     std::unique_ptr<int> p1(new int(5));
>     std::unique_ptr<int> p2 = std::make_unique<int>(6);
>     *p1 = 10;
>     std::cout << *p1 << " " << *p2 << std::endl;
>     return 0;
> }
> ```
>
> std::shared_ptr代码示例
>
> ```c++
> include <memory>
> 
> int main() {
>     std::shared_ptr<int> p1(new int(5));
>     std::shared_ptr<int> p2 = std::make_shared<int>(6);
>     *p1 = 10;
>     std::cout << *p1 << " " << *p2 << std::endl;
>     return 0;
> }
> ```
>
> 这些智能指针类型可以简化内存管理，避免手动释放内存导致的错误，并且支持移动语义，能更好地支持多线程编程。

```c++
void f()
{
std::auto_ptr<Investment> pInv(createInvestment()); // call factory
// function
... // use pInv as
// before
} // automatically
// delete pInv via 
// auto_ptr’s dtor
```



**以对象管理资源的两个关键想法**

- 获得资源后立刻放进管理对象内

  以对象管理资源的观念常被称为“资源取得时机便是初始化时机”***Resource Acquisition Is Initialization (RAII)***“，因为我们几乎总是在获得一笔资源后在同一语句内以它初始化某个管理对象。有时候获得的资源被拿来赋值（而非初始化）某个管理对象，但不论哪一种做法，每一笔资源都在获得的同时立刻被放进管理对象中。
- 管理对象运用析构函数确保资源被释放

  不论控制流如何离开区块，一旦对象被销毁其析构函数自然会被自动调用，于是资源被释放。如果资源释放动作可能导致抛出异常，但是【条款8】已经能够解决这个问题。

由于auto_ptr被销毁时会自动删除它所指之物，多以不要让多个auto_ptr同时指向同一对象。否则，对象可能会被删除一次以上。所以为了预防这个问题，auto_ptr有一个不寻常的性质，即“若通过copying函数复制它们，它们会变成null，而复制所得的指针将获得资源的唯一拥有权”。

```c++
std::auto_ptr<Investment> // pInv1 points to the
pInv1(createInvestment()); // object returned from
// createInvestment
std::auto_ptr<Investment> pInv2(pInv1); // pInv2 now points to the
// object; pInv1 is now null
pInv1 = pInv2; // now pInv1 points to the
// object, and pInv2 is null
```

这一诡异的赋值，加上它的底层条件，导致类似STL容器无法适配。

auto_ptr的替代方案就是引用计数型智慧指针“reference-counting smart pointer (RCSP)”。持续追踪共有多少对象指向某笔资源，并在无人指向它时自动删除该资源。RCSPs提供的行为类似垃圾回收，不同的时RCSP无法打破环状引用（例如两个其实已经没人使用的对象彼此互指，因而好像还处在被使用状态）。

auto_ptr 和shared_ptr 两者都在其析构函数内做delete而不是delete[] 【条款16】对两者的不同有些描述。那意味着动态分配的array身上使用auto_ptr 或 shared_ptr是个馊主意。但是，可叹的是，这么做依然能通过编译。

```c++
std::auto_ptr<std::string> // bad idea! the wrong 
aps(new std::string[10]); // delete form will be used 
std::tr1::shared_ptr<int> spi(new int[1024]); // same problem
```



> 有几种改善方法可以避免这个问题：
>
> 1. 使用 std::unique_ptr 或 std::shared_ptr 代替 std::auto_ptr 和 std::tr1::shared_ptr。这些指针在 C++11 中引入，可以自动调用 delete[] 来释放数组内存。
> 2. 使用 std::vector 或 std::array 代替手动分配的数组。这些容器在被销毁时会自动释放内存。
> 3. 使用 std::shared_ptr[std::string[\]](javascript:void(0)) 或 std::unique_ptr[std::string[\]](javascript:void(0)) 管理字符串数组。这些指针在 C++14 中引入，可以自动调用 delete[] 来释放数组内存
> 4. 如果使用 std::auto_ptr 或 std::tr1::shared_ptr，那么应该使用一个类似 std::shared_ptr<T[]> 的自定义智能指针，这样在析构函数里面可以自定义释放方式。
> 5. 如果你不想使用智能指针, 那么可以手动释放内存，使用 delete[] 来释放内存，而不是 delete.
>
> 
>
> std::shared_ptr 是 C++11 中引入的一种智能指针，它可以在管理动态分配的内存时自动调用 delete[] 来释放数组内存。这是通过在 shared_ptr 类模板中定义一个类型为 T* 的 deleter 成员变量来实现的。
>
> 这个 deleter 成员变量是一个函数指针，指向了一个删除器函数。这个函数会在 shared_ptr 的析构函数中被调用来释放资源。
>
> 默认情况下，shared_ptr 会使用 std::default_delete<T> 作为删除器，它是一个类模板，定义了 operator() 函数，这个函数会调用 delete 运算符来释放内存。
>
> 但是，如果 T 是数组类型，那么 std::default_delete<T> 会被特化为 std::default_delete<T[]>，它定义了 operator() 函数，这个函数会调用 delete[] 运算符来释放内存。
>
> 下面是 std::shared_ptr 的部分源代码，可以看到 shared_ptr 的析构函数会调用 deleter 来释放内存。
>
> ```c++
> Copy codetemplate<class T>
> class shared_ptr {
>     // ...
>     template<class T1> friend class shared_ptr;
>     template<class T1> friend class weak_ptr;
>     T* _ptr;
>     std::shared_ptr<T>* _shared_this;
>     std::atomic<long>* _shared_count;
>     std::function<void(T*)> deleter;
>     // ...
>     ~shared_ptr() {
>         if (_shared_count) {
>             if (_shared_count->fetch_sub(1) == 1) {
>                 if (deleter) deleter(_ptr);
>                 else delete _ptr;
>                 delete _shared_count;
>             }
>         }
>     }
> };
> ```



#### 总结：

- 为防止资源泄漏，请使用RAII对象，它们在构造函数中获得资源并在析构函数中释放资源
- 两个常被使用的RAII classes分别是tr1::shared_ptr 和 auto_ptr。前者通常是更好的选择，因为它copy行为比较直观，若是auto_ptr，复制动作会使被复制物指向null。

### 条款14 在资源管理类中小心copying行为

Think carefully about copying behavior in resource-managing classes

有时候需要我们自己建立自己的资源管理类。

这样的class的基本结构由RAII守则支配，也就是“资源在构造期间获得，在析构期间释放”。

```c++
void lock(Mutex *pm); // lock mutex pointed to by pm
void unlock(Mutex *pm); // unlock the mutex

class Lock {
public:
    explicit Lock(Mutex *pm)
    : mutexPtr(pm)
    	{ lock(mutexPtr); } // acquire resource
    ~Lock() { unlock(mutexPtr); } // release resource
private:
    Mutex *mutexPtr;
};
```

上面是某个一般化问题的特定例子。那么“当一个RAII对象被复制，会发生什么事？”

- 禁止复制

  许多时候允许RAII对象被复制并不合理。对一个像Lock这样的class这是有可能的。因为很少能够合理拥有“同步化基础器物”的副本。(In many cases, it makes no sense to allow RAII objects to be copied. This is likely to be true for a class like Lock, because it rarely makes sense to have “copies” of synchronization primitives. )

  如果复制动作对RAII对象并不合理，那么你便应该禁止之，【条款6】已经说了，将copying操作声明为private。

- 对底层资源祭出“引用计数法”

  类似C++11的智慧指针。但是我们使用Mutex类，我们想要做的释放动作是解除锁定而非删除。幸运的是，tr1::shared_ptr允许指定所谓的“删除器”，那是一个函数或函数对象，当引用次数为0时便被调用（此机能并不存在于auto_ptr–它总是将其指针删除)。删除器对tr1::shared_ptr构造函数是可有可无的第二参数。

  ```c++
  class Lock {
  public:
      explicit Lock(Mutex *pm) // init shared_ptr with the Mutex
      : mutexPtr(pm, unlock) // to point to and the unlock func as the deleter 指定unlock作为删除器
      { 
      	lock(mutexPtr.get()); // see Item 15 for info on “get” 
  	}
  private:
  	std::tr1::shared_ptr<Mutex> mutexPtr; // use shared_ptr
  }; // instead of raw pointer
  ```

  

  注意：本例的Lock class不再声明析构函数。因为没有必要。【条款5】说过，class析构函数（无论是编译器生成的，或用户自定的）会自动调用其non-static成员变量（本例为mutexPtr)。而mutexPtr的析构函数会在互斥器的引用次数为0时自动调用删除器。

- 复制底部资源

  复制资源管理对象时，进行的是“深拷贝”

- 转移底部资源的拥有权

  某些罕见情况下，你可能希望确保永远只有一个RAII对象指向一个未加工资源。即使RAII对象被复制依然如此。此时资源的拥有权会从被复制物到目标物（一如auto_ptr奉行的复制意义)



Copying函数，有可能被编译器自动创建出来，因此除非编译器所生产的版本做了你想要的事，否则你得自己编写它们。某些情况下你或许也想支持这些函数的一般版本，这样的版本描述于【条款45】。



#### 总结：

- 复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为。
- 普遍而常见的RAII class copying 行为是：抑制copying，施行引用计数法（即1、2）。不过其他行为也可能用。
- 注：C++11提供了新的智能指针，能用那个就用那个。



### 条款15 在资源管理类中提供对原始资源的访问

Provide access to raw resources in resource-managing classes

理论上资源管理类可以有效的对抗资源泄漏，而排除此类泄漏是良好设计系统的根本性质。但是许多API直接指涉资源，所以除非你永远不用这样的API，那么就只能绕过资源管理对象，直接访问原始资源。

```c++
std::tr1::shared_ptr<Investment> pInv(createInvestment()); // from Item 13
int daysHeld(const Investment *pi); // return number of days
// investment has been held
int days = daysHeld(pInv); // error!
```



即需要一个函数将RAII class对象转换为所内含之原始资源。有两个做法可以达成目标 -- 显式转换和隐式转换。

- 显式转换

  tr1::shared_ptr 和 auto_ptr都提供一个get函数(C++11里的智能指针也支持)，用来执行显式转换，也就是返回只能指针内部的原始指针（的复件）

  ```c
  int days = daysHeld(pInv.get()); // fine, passes the raw pointer
  // in pInv to daysHeld
  ```

  

- 隐式转换

   就像几乎所有智能指针一样，tr1::shared_ptr 和 auto_ptr也重载了指针取值操作符，它们允许隐式转换至底部原始指针。

  ```c++
  class Investment { // root class for a hierarchy
  public: // of investment types
      bool isTaxFree() const;
      ...
  };
  Investment* createInvestment(); // factory function
  std::tr1::shared_ptr<Investment> // have tr1::shared_ptr
  pi1(createInvestment()); // manage a resource
  bool taxable1 = !(pi1->isTaxFree()); // access resource
  // via operator->
  ...
  std::auto_ptr<Investment> pi2(createInvestment()); // have auto_ptr
  // manage a
  // resource
  bool taxable2 = !((*pi2).isTaxFree()); // access resource
  // via operator*
  ```

  但有时还是必须取得RAII对象内的原始资源，有的设计者会考虑提供一个隐式转换函数。譬如下面的这个字体类。

  ```c++
  FontHandle getFont(); // from C API — params omitted
  // for simplicity
  void releaseFont(FontHandle fh); // from the same C API
  
  class Font { // RAII class
  public:
  	explicit Font(FontHandle fh) // acquire resource;
  	: f(fh) // use pass-by-value, because the
  	{} // C API does
  	~Font() { releaseFont(f ); } // release resource
  ... // handle copying (see Item 14)
  private:
  	FontHandle f; // the raw font resource
  };
  ```

  如果有大量的处理FontHandle C API，那么将Font对象转换为FontHandle会是很频繁的需求，在这里，Font class可以提供一个类似get的转换函数。但是这使得客户每当想要使用API就必须使用get，会很烦。

  ```c++
  class Font {
  public:
  ...
  	FontHandle get() const { return f; } // explicit conversion function
  ...
  };
  void changeFontSize(FontHandle f, int newSize); // from the C API
  Font f(getFont());
  int newFontSize;
  ...
  changeFontSize(f.get(), newFontSize); // explicitly convert
  // Font to FontHandle
  ```

  所以有些程序员会觉得，那不如给你一个隐式转换。这样调用起来比较自然。

  ```c++
  class Font {
  public:
  ...
  	operator FontHandle() const // implicit conversion function
  	{ return f; }
  ...
  };
  
  Font f(getFont());
  int newFontSize;
  ...
  changeFontSize(f, newFontSize); // implicitly convert Font
  // to FontHandle
  ```

  > changeFontSize(f, newFontSize);是调用一个函数，向函数传递了两个参数，一个是类型为Font的变量f，另一个是int类型的变量newFontSize。由于Font类中定义了隐式转换函数"operator FontHandle()", 这个函数可以将类型为Font的变量f转换为类型为FontHandle的变量，所以changeFontSize函数在调用的时候可以接受Font类型的变量f作为参数，而不需要显式转换。

  但是吧，这个隐式转换又会增加错误发生机会。例如客户可能在需要Font时，意外创建FontHandle。

  ```c++
  Font f1(getFont());
  ...
  FontHandle f2 = f1; // oops! meant to copy a Font 
  // object, but instead implicitly
  // converted f1 into its underlying
  // FontHandle, then copied that
  ```

  > 上述代码中， 先通过调用 getFont()函数创建一个FontHandle类型的变量fh，然后将fh传递给Font类的构造函数，创建一个Font类型的变量f1. 然后将f1赋值给FontHandle类型的变量f2.
  >
  > 这段代码的风险是将一个RAII类型的对象赋值给非RAII类型的变量，可能会导致资源泄露。 因为f1是一个RAII对象，它在构造时通过getFont()获取了资源，而在析构时会释放资源。如果将f1赋值给f2，那么f1的析构函数就不会被调用，资源就不会被释放，造成资源泄露。
  >
  > 比如f1被销毁，字体被释放，而f2就成为虚吊的。
  >
  > 为了避免这个问题，应该在类中重载赋值运算符，并且在赋值运算符中避免这种赋值方式。

是否应该提供一个显式转换函数将RAII class转换为其底部资源，或是应该提供隐式转换。取决于【条款18】，即“让接口更容易被使用，不易被误用”。通常显式转换函数如get是比较受欢迎的方法，因为它将“非故意之类型转换”的可能性最小化了。然而有时候，隐式类型转换所带来的“自然用法”也会引发天秤倾斜。

可能你会认为，RAII class内的那个返回原始资源的函数，与封装发生矛盾。这是真的。但是一般而言算不上什么设计灾难。RAII classes并不是为了封装某物而存在，它们的存在是为了确保一个特殊行为--资源释放--会发生。如果一定要，当然也可以在这基本功能之上再加一层资源封装，但那并非必要。此外也有某些RAII class结合十分松散的底层资源封装，藉以获得真正的封装实现。例如tr1::shared_ptr 将它的所有引用计数机构封装了起来，但还是让外界很容易访问其内含的原始指针。就好像多数设计良好的class一样，它隐藏了客户不需要看的部分，但备妥客户需要的所有东西。

#### 总结：

- API往往要求访问原始资源（raw resources），所以每一个RAII class 应该提供一个“取得其所管理之资源”的方法。
- 对原始资源的访问可能经由显式转换或隐式转换。一般而言显式转换比较安全，但隐式转换对客户比较方便。





### 条款16 成对使用new和delete时要采取相同形式

Use the same form in corresponding uses of new and delete

被删除的指针，得明确所指的单一对象还是对象数组。

typedef很容易令人误解，把对象数组理解成单一对象。

#### 总结：

- 如果你在new表达式中使用[]，必须在相应的delete表达式中也使用[]；如果你在new表达式中不使用[]，一定不要在相应的delete表达式中也使用[]；

### 条款17 以独立语句将newd 的对象置入智能指针

Store newed objects in smart pointers in standalone statements.

假设我们有个函数用来揭示处理程序的优先权，另一个函数用来在某动态分配所得的Widget上进行某些带来优先权的处理：

```c++
int priority();
void processWidget(std::tr1::shared_ptr<Widget> pw, int priority);
```

现在尝试调用 `processWidget`。

```c++
//这种写法不能通过编译，因为tr1::shared_ptr构造函数需要一个原始指针，但该构造函数是个explict构造函数，无法进行隐式转换。
processWidget(new Widget, priority());
//写成这样就可以通过编译
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());
```

令人震惊的是，虽然我们在此使用“对象管理式资源”，上述调用却可能泄露资源。

编译器产出一个processWidget 调用码之前，必须首先核算既将被传递的各个实参。上述的第二实参是一个简单的对priority函数的调用。但是第一实参std::tr1::shared_ptr<Widget>(new Widget)由两部分组成：

- 执行new Widget表达式
- 调用tr1::shared_ptr构造函数

于是在调用processWidget之前，编译器必须创建代码，做以下三件事：

- 调用priority
- 执行new Widget表达式
- 调用tr1::shared_ptr构造函数

C++ 编译器以什么次序完成这些事情呢？弹性很大。可以确定new Widget 一定执行与tr1::shared_ptr构造函数被调用之前，因为这个表达式的结果还要被传递作为tr1::shared_ptr构造函数的一个实参，但对priority的调用则可以排在第一、第二或第三执行。如果对priority的调用导致异常，在此情况下，new Widget返回的指针将会遗失，因为它尚未被置入tr1::shared_ptr内。

总结，即资源被创建和资源被转换为资源管理对象两个时间点之间有可能发生异常干扰。

避免这个问题的办法很简单：使用分离语句。

```c++
std::tr1::shared_ptr<Widget> pw(new Widget); // store newed object
// in a smart pointer in a
// standalone statement
processWidget(pw, priority()); // this call won’t leak
```

以上之所以写的通，因为编译器对于跨越语句的各项操作没有重新排列的自由（只有在语句内它才有那个自由度）。在上述修订后的代码内，newWidget表达式以及对tr1::shared_ptr 构造函数的调用这两个动作，和对priority的调用时分隔开的，位于不同语句内，所以编译器不得在它们之间任意选择执行次序。

#### 总结：

- 以独立语句将newed对象存储于智能指针内。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏。



## 第四章 设计声明

**[Designs and Declarations]**

所谓软件设计，是“令软件做出你希望它做的事”的步骤和做法。通常以颇为一般性的构想开始，最终演变为十足的细节，以允许特殊接口`interfaces`的开发。

我们对良好C++接口和声明的一项基本准则为：“让接口容易被正确使用，不容易被误用”。

这个准则设立了一个舞台，让其他更专精的准则对付一个大范围的题目，包括正确性、高效性、封装性、维护性、延展性，以及协议的一致性。

### 条款18 让接口容易被使用，不易被误用

Make interfaces easy to use correctly and hard to use incorrectly

理想上，如果客户企图使用某个接口而没有获得他所预期的行为，这个代码不应该通过编译；如果代码通过了编译，它的作为就该是客户所想要的。

想开发一个良好的接口，首先必须考虑客户可能做出怎么样的错误。

我们可以

- 通过导入外覆类型(wrapper types)来区别天数、月份和年份。
- 类型定位好后，可以限制其值（比如月份，固定为1-12）
- 限制类型内什么事可以做，什么不能做，最常见的限制是加const。
- 除非有好理由，否则努力使你的type与内置type一致。
- 提供一致的接口（类似STL容器都有size成员函数）
- 使用智能指针，保证合理的释放资源



#### 总结：

- 好的接口很容易被正确使用，不容易被误用。你应该在你的所有接口中努力达成这些性质。
- 促进正确使用的方法包括接口的一致性，以及与内置类型的行为兼容。
- 阻止误用的办法包括建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任。
- 智能指针支撑定制型删除器（custom deleter）。这可防范DLL问题，可被用来自动解除互斥锁（mutexes【条款14】）



### 条款19 设计class犹如设计type

Treat class design as type design

C++ 就像其他OOP语言一样，当你定义一个新class，也就是定义了一个新type。

身为C++ 程序员，你的许多时间主要用来扩张你的类型系统（type system）。这意味着你并不只是class设计者，还是type设计者。重载overloading函数和操作符、控制内存的分配和归还、定义对象的初始化和终结……全都在手上。因此你应该带着和“语言设计者当初设计语言内置类型”时一样的谨慎来研讨class的设计。

> ### c++中的类class和类型type有哪些异同？
>
> C++中的类(class)和类型(type)有一些相似之处，但也有一些明显的区别。
>
> 相似之处:
>
> 1. 都是用于定义一种数据类型。
> 2. 都可以用于定义变量和函数。
>
> 不同之处:
>
> 1. 类是用于定义面向对象编程中的类型，而类型是更广义的概念，包括基本类型和自定义类型。
> 2. 类可以定义私有成员和公有成员，而类型没有这个概念。
> 3. 类可以定义构造函数和析构函数，而类型没有这个概念。
> 4. 类可以继承和重载，而类型没有这个概念。
>
> 总结: 类是一种特殊的类型, 它是面向对象编程中的基本概念, 类型是更广义的概念,包括基本类型和自定义类型.

在设计高效的class，我们往往需要面对以下的自问。

<font color='#DB4437'>淆了</font>

- **<font color='#DB4437'>新type的对象应该如何被创建和销毁？</font>**              <font color='#4285F4'>构造析构</font>

  这牵扯到你的class的构造函数和析构函数以及内存分配函数和释放函数（(operator new, operator new[], operator delete, and operator delete[] 【第八章】 ）

- **对象的初始化和对象的赋值该有什么样的差别？**

  这决定你的构造函数和赋值操作符的行为，以及其间的差异。很重要的的是别混淆了初始化和“赋值”，因为它们对应于不同的函数调用【条款4】

- **新type的对象如果被passed by value 意味着什么？**

  copy构造函数用来定义一个type的 pass-by-value该如何实现

- **什么是新type的“合法值”？**

  对class的成员变量而言，通常只有某些数值集是有效的。那些数值集决定了你的class必须维护的约束条件（invariants），也就决定了你的成员函数（特别是构造函数、赋值操作符和所谓的setter函数）必须进行的错误检查工作。它也影响函数抛出的异常、以及（极少被使用的）函数异常明细列（exception specifications）。

- **<font color='#DB4437'>你的新type需要配合某个继承图系（inheritance graph）吗？</font>**             <font color='#4285F4'>继承</font>

  如果你继承自某些既有的classes，那么你就会受到哪些classes设计的束缚，特别是受到它们的函数是virual或non-virtual的印象【条款34】【条款36】。如果你运行其他class，那会影响你所声明的函数--尤其是析构函数--是否为virual【条款7】。

- **你的新type需要什么样的转换？**

  你新写的type 生存在很多types之中，那么彼此之间需要进行转换吗？

  - 如果你想T1可以隐式转换为T2，那么就必须在T1内写一个类型转换函数或者在T2内写一个non-explicit-argument（可被单一实参调用）的构造函数。
  - 如果你只允许explicit构造函数存在，就得写出专门负责执行转换的函数，且不得为类型转换操作符（type conversion operators）或non-explicit-one-argument构造函数。

- **<font color='#DB4437'>什么样的操作符和函数对此新type而言是合理的？</font>**                           <font color='#4285F4'> 定义函数</font>

  你需要为你的类重载哪些操作符（譬如你的类会放入map，那你得写个`<`的重载）？

  这个回答将会决定你将为你的class声明哪些函数。其中哪些应该是memberr函数，哪些不是？【条款23、24、46】

- **什么样的标准函数应该驳回？**

  哪些就是你需要设定为private的。

  - **<font color='#DB4437'>谁该取用新type的成员？</font>**															<font color='#4285F4'>资源分配</font>

  这个提问可以帮助你决定哪个成员为public，哪些为protected的，哪些是private的。他也帮助你决定哪一个classes和/或functions应该是friends，以及将它们嵌套于另一个之内是否合理。

- **什么是新type的“未声明接口（undeclared interface)”？**

  它对效率、异常安全性【条款29】以及资源运用（例如多任务锁定和动态内存）提供何种保证？你在这些方面提供的保证将为你的class实现代码加上相应的约束条件。

- **你的type 有多么一般化？**

  如果你定义的并非一个type，而是一整个type家族，那么你应该定义一个新的class template而不是简单一个type。

- **你真的需要一个新type吗？**

  如果只是定义新的derived class 以便为既有的class添加机能，那么说不定单纯定义一或多个non-member函数或templates，更能够达到目标。



#### 总结：

- class的设计就是type的设计，在定义一个新type之前，请确定你已经考虑过本条款覆盖的所有主题。

### 条款20 宁以pass-by-reference-to-const替换pass-by-value

Prefer pass-by-reference-to-const to pass-by-value

缺省情况下C++以 by value（一个继承自C的方式）传递对象至（或来自）函数。除非指定，否则函数参数都是以实参的复件为初值，而调用端所获得的亦是函数返回值的一个复件。这些复件是由对象的copy构造函数产出，这可能使得传值成为昂贵费事的操作。

参数的传递成本是“一次copy构造函数调用，一次析构函数调用”。但是！如果这个类有若干父类等等，那么每一次调用动作都回调用构造析构，成本很大。

想要回避这些操作，那就可以采用pass by reference to const。

这种传递方式效率高得多：因为没有任何新对象被创造。修订后的这个参数声明中的const是重要的。因为这确保函数不会改变传入的参数的值。

以by reference方式传递参数也可以避免slicing（对象切割）问题。当子类对象以传值方式传递并被视为base class对象时，base class的构造函数会被调用，而它的子类部分都被切割掉了。

```c++
class Window {
public:
    ...
    std::string name() const; // return name of window
    virtual void display() const; // draw window and contents
};
class WindowWithScrollBars: public Window {
public:
...
	virtual void display() const;
};

void printNameAndDisplay(Window w) // incorrect! parameter
{ // may be sliced!
    std::cout << w.name();
    w.display();
}
//解决切割的方法
void printNameAndDisplay(const Window& w) // fine, parameter won’t
{ // be sliced
std::cout << w.name();
w.display();
}
```

不过如果你想传的对象是内置类型，传值可能比传址更快。而STL容器习惯上也被设定为传值。迭代器和函数对象的实践者有责任看看它们是否高效且不受切割问题影响。这就是【条款1】里所说的，规则改变取决于你使用了哪一部分的C++。

#### 总结:

- 尽量以pass-by-reference-to-const替换pass-by-value。前者通常比较高效（避免了反复的拷贝构造&析构），并可避免切割问题。
- pass-by-value开销并不昂贵的唯一对象就是内置类型和STL的迭代器和函数对象。对他们而言，传值可能比较恰当



### 条款21 必须返回对象时，别妄想返回其reference

Don’t try to return a reference when you must return an object

看完【条款20】，很多人会坚定追求pass-by-reference的纯度。但是有时传递一些references指向实际并不存在的对象，未必是件好事。

```c++
#include<iostream>
using namespace std;
using namespace std;
class Rational {
public:
    Rational(int numerator = 0, // see Item 24 for why this
             int denominator = 1):n(numerator),d(denominator){}; // ctor isn’t declared explicit
    void print(){
        cout<< "Rational is "<< this->d <<" "<<this->n<<endl;
    }

private:
    int n, d; // numerator and denominator
    friend
    const Rational operator*(const Rational& lhs, // 如果这里是const Rational& operator*，c.print就不会输出。
              const Rational& rhs)
              {
                Rational result(lhs.d*rhs.d,lhs.n*rhs.n);
                return result;
                };
};

int main(){
    Rational a(1,2);
    a.print();
    Rational b = Rational(3,5);
    b.print();
    Rational c = a*b;
    c.print();
}

/*
编译器会告警但不会报错。
C:/Users/Administrator/CLionProjects/1109/main.cpp: In function 'const Rational& operator*(const Rational&, const Rational&)':
C:/Users/Administrator/CLionProjects/1109/main.cpp:19:24: warning: reference to local variable 'result' returned [-Wreturn-local-addr]
   19 |                 return result;
      |                        ^~~~~~
C:/Users/Administrator/CLionProjects/1109/main.cpp:18:26: note: declared here
   18 |                 Rational result(lhs.d*rhs.d,lhs.n*rhs.n);
      |                          ^~~~~~
[2/2] Linking CXX executable 1109.exe

*/
```

上段代码是通过传值来进行的，如果你采用传reference，那么就不需要付出任何代价。但是，任何时候看到一个reference声明式，你都一个立刻问自己，它的另一个名称是什么？上述operator* ，如果它返回一个reference，那么后者一定指向某个既有的Rational对象，内含两个Rational对象的乘积。

我们当然不可能期望这样的内含乘积的Rational对象在调用`operator*`之前就存在。所以如果`operator*`要返回一个reference并指向此数值，那么就必须自己创建那个Rational对象。

函数创建新对象的方法有二：

- stack

  ```c++
  const Rational& operator*(const Rational& lhs, const Rational& rhs)
         {
          Rational result(lhs.d*rhs.d,lhs.n*rhs.n);
          return result;
         };
  ```

  这是一个糟糕的代码，因为local对象在函数退出前就被销毁。这个版本的`operator*`指向一个已经死去的Rational，任何对此函数做的调用，都会坠入无定义行为的深渊。

- heap

  ```c++
  const Rational& operator*(const Rational& lhs, // warning! more bad
  const Rational& rhs) // code!
  {
  	Rational *result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
  	return *result;
  }
  ```

  new是new了，但是什么时候delete呢？所以这种方法也很糟糕。而且在使用`x*y*z`这样的表达式时，没有办法合理的delete。

上述两种方法都行不通的情况下，可能会想到使用static来避免构造函数的开销。但是这也是会引起譬如多线程安全性的问题。以及譬如`if (operator==(operator*(a, b), operator*(c, d)))`这样的操作，也会引起歧义。



#### 总结：

- 绝不要返回指向一个local stack对象的指针或引用，或返回指向一个heap-allocated对象的引用，或返回指向一个可能被多个需求需要的local static对象的指针或引用。(Never return a pointer or reference to a local stack object, a reference to a heap-allocated object, or a pointer or reference to a local static object if there is a chance that more than one such object will be needed. (Item 4 provides an example of a design where returning a reference to a local static is reasonable, at least in single-threaded environments.)

### 条款22 将成员变量声明为private

Declare data members private

将成员变量隐藏在函数接口的背后，可以为“所有可能的实现”提供弹性。例如这可以使得成员变量被读或被写时轻松通知其他对象、可以验证class的约束条件以及函数的前提和事后状态、可以在多线程环境中执行同步控制……等等。

封装的重要性比你最初见到它时还要重要。如果你隐藏了成员变量，那么可以确保class的约束条件总是会获得维护，因为只有成员函数可以影响它们。

Public意味着不封装，不封装的另一层意思就是（为了安全性）几乎就意味着不可改变。特别是用的特别广泛的class。假设我们有一个public的成员变量，而我们最终取消了它，可能会有不可估量的代码会被破坏。而protected和public一样缺乏封装性。所以在实际操作中，请记住只有两种访问权限：private和其他。



#### 总结：

- 切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者以充分的实现弹性。
- Protected并不比public更具有封装性。



### 条款23 宁以non-member、non-friend替换member函数

Prefer non-member non-friend functions to member functions

```c++
class WebBrowser {
public:
...
    void clearCache();
    void clearHistory();
    void removeCookies();
    ...
    void clearEverything();//调用上面三个函数。
};

void clearBrowser(WebBrowser& wb)
{
	wb.clearCache();
	wb.clearHistory();
	wb.removeCookies();
}

```



面向对象守则要求，数据以及操作数据的那些函数应该被捆绑在一起。但实际上这是一种对面向对象真实意义的一种误解。面向对象守则要求尽可能的被封装。而与直觉相悖的是，成员函数cleareverything 带来的封装性比非成员函数clearBrowser低。因为它并不增加“能够访问class内private成分”的函数数量。此外，提供非成员函数可允许对WebBrowser相关机能有较大的包裹弹性(packaging flexibility)，而那将导致较低的编译相依度，增加了WebBrowser的可延伸性。

这里有两点需要注意：

* 这个论述这适用于non-member 和non-friend函数。所以从封装的角度来看，选择关键是在member和non-membernon-friend函数之间。
* 只因在意封装性而让函数成为class的non-member，不意味着它不可以是另一个class的member。比如我们可以让clearBrowser成为某工具类（utility class）的一个static member函数。

在C++中，比较自然的做法是将clearBrowser成为一个非成员函数，并和WebBrowser处于同一个命名空间内。

```c++
namespace WebBrowserStuff {
class WebBrowser { ... };
void clearBrowser(WebBrowser& wb);
...
}
```

namespace与class不同，前者可以跨越多个文件，而后者不能。clearBrowser实际上是一个便利函数，将所有便利函数放在多个头文件，但隶属于同一个命名空间，意味着客户可以轻松拓展这一组便利函数。



#### 总结：

- 宁可拿non-member non-friend函数替换member函数，这一做可以增加封装性、包裹弹性和机能扩充性。

但是这不绝对。

> C++中，封装性和自包含是两个相互关联的概念。封装性是指对于类的实现细节进行隐藏，使得类的用户不需要了解这些细节就可以使用类。而自包含是指将数据和操纵数据的函数放在一起，使得类更加简洁，并且更容易维护。
>
> 封装性和自包含在很大程度上是相互依存的，因为自包含可以帮助类更好地封装实现细节，而封装性又可以帮助类更好地达到自包含。
>
> 在实际开发中，应该根据具体情况来决定哪个更重要。在一些情况下，类的封装性可能更重要，因为它可以帮助类更好地隐藏实现细节，使得类更加稳定和可靠。在另一些情况下，类的自包含性可能更重要，因为它可以帮助类更好地管理数据，使得类更加简洁和易于维护。

### 条款24 若所有参数皆需类型转换、请为此采用non-member函数

Declare non-member functions when type conversions should apply to all parameters

在导读里曾经提过，令class支持隐式类型转换通常是一个糟糕的主意，但是也得视情况而定。比如把整数隐式转换为有理数就很自然。

但是在重载运算符时，我们往往会遇到各种问题。

```c++
#include<iostream>
using namespace std;
using namespace std;
class Rational {
public:
    Rational(int numerator = 0, // see Item 24 for why this
             int denominator = 1):n(numerator),d(denominator){}; // ctor isn’t declared explicit
    void print(){
        cout<< "Rational is "<< this->d <<" "<<this->n<<endl;
    }
    const Rational operator*(const Rational& rhs) const;

private:
    int n, d; // numerator and denominator

};

const Rational Rational::operator*(const Rational &rhs) const {
    { return Rational(this->d*rhs.d,this->n*rhs.n);}
}

int main(){
    Rational oneEighth(1, 8);
    Rational oneHalf(1, 2);
    Rational result = oneHalf * oneEighth; // fine
    result = result * oneEighth; // fine

    result = oneHalf * 2; // fine
    result.print();
    result = 2 * oneHalf; // error!
    result.print();
}

/*
C:/Users/Administrator/CLionProjects/1109/main.cpp:30:16: error: no match for 'operator*' (operand types are 'int' and 'Rational')
   30 |     result = 2 * oneHalf; // error!
      |              ~ ^ ~~~~~~~
      |              |   |
      |              int Rational
ninja: build stopped: subcommand failed.
*/
```

错误的原因是因为

```c++
result = oneHalf * 2; // fine
result = 2 * oneHalf; // error!
//理解成下面的
result = oneHalf.operator*(2); //2可以被隐式转换为Rational
result = 2.operator*(oneHalf);//2本身没有重载运算符
```

这种情况下，编译器会尝试寻找可以被这样调用的非成员函数，但是这里没有提供。

我们自己加一个即可。

```c++
const Rational operator*(const Rational& lhs, const Rational& rhs) // 
{
	return Rational(lhs.numerator() * rhs.numerator(),lhs.denominator() * rhs.denominator());
}
```



#### 总结：

- 如果你需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member。

### 条款25 考虑写出一个不抛异常的swap函数

Consider support for a non-throwing swap

swap是一个有趣的函数。原本只是STL的一部分，而后成为异常安全性编程【条款29】的脊柱，以及用来处理自我赋值可能性【条款11】的一个常见机制。

所谓swap，就是将两对象的值彼此赋予给对方。

标准库的swap典型实现如下：

```c++
namespace std {
template<typename T> // typical implementation of std::swap;
    void swap(T& a, T& b) // swaps a’s and b’s values
    {
        T temp(a);
        a = b;
        b = temp;
    }
}
/*
swap(_Tp& __a, _Tp& __b)
    _GLIBCXX_NOEXCEPT_IF(__and_<is_nothrow_move_constructible<_Tp>,
				is_nothrow_move_assignable<_Tp>>::value)
    {
#if __cplusplus < 201103L
      // concept requirements
      __glibcxx_function_requires(_SGIAssignableConcept<_Tp>)
#endif
      _Tp __tmp = _GLIBCXX_MOVE(__a);
      __a = _GLIBCXX_MOVE(__b);
      __b = _GLIBCXX_MOVE(__tmp);
    }
*/
```

只要类型T支撑copying函数，缺省的swap实现代码就会帮你置换类型为T的对象。你不需要为此另外再做任何工作。

这一种swap设计三个对象的复制，但是对于某些类型（最主要的就是以指针指向一个对象，内含真正数据）。

这种类型的设计手法常常是pimpl手法（pointer to implementation）【条款31】。

```c++
#include<iostream>
#include <vector>
static int num = 0;
using namespace std;
class WidgetImpl { // class for Widget data;
public: // details are unimportant
    WidgetImpl(){ num++;cout<<"WidgetImpl construct times is "<<num<<endl;}
    WidgetImpl(const WidgetImpl& rhs){ num++;cout<<"WidgetImpl copy times is "<<num<<endl;}
private:
    int a, b, c; // possibly lots of data —
    std::vector<double> v; // expensive to copy!

};
class Widget {
public:
    Widget() : pImpl(new WidgetImpl) {num++;cout<<"construct times is "<<num<<endl;}; //default constructor
    Widget(const Widget& rhs) : pImpl(new WidgetImpl(*rhs.pImpl)) {num++;cout<<"copy times is "<<num<<endl;}; //copy constructor
    Widget& operator=(const Widget& rhs) {
        if (this != &rhs) {
            *pImpl = *(rhs.pImpl);
            num++;cout<<"=== times is "<<num<<endl;//copy constructor
        }
        return *this;
    } //overloaded assignment operator
    ~Widget(){
        delete pImpl; //释放pImpl指向的堆上内存
        num++;cout<<"delete times is "<<num<<endl;
    }
private:
    WidgetImpl *pImpl;
};



int main(){
    Widget A;
    Widget B;
    std::swap(A,B);
    cout<<"hello world"<<endl;
    A = B;
    cout<<"hello world 2"<<endl;
    return 0;
}



/*
WidgetImpl construct times is 1
construct times is 2
WidgetImpl construct times is 3
construct times is 4


WidgetImpl copy times is 5
copy times is 6
=== times is 7
=== times is 8
delete times is 9


hello world
=== times is 10
hello world 2
delete times is 11
delete times is 12

进程已结束,退出代码0

*/
```

这种实现下，置换两个widget值，实际上只需要置换其pimpl指针即可。但缺省的swap操作不知道这一点，它不只复制三个widgets，还复制三个WidgetImpl对象，非常缺乏效率。

为此我们需要告诉std::swap针对Widget进行特化。

```c++
namespace std {
    template<> // this is a specialized version
    void swap<Widget>(Widget& a, // of std::swap for when T is
    Widget& b) // Widget
    {
    	swap(a.pImpl, b.pImpl); // to swap Widgets, swap their
    } // pImpl pointers; this won’t compile
}
```

一开始我们可能会想到上面的版本，但是因为pImpl是private的，所以我们访问不到。一般来说我们可以将这个特化版本声明为friend，但和以往的规矩不太一样：我们令Widget声明一个名为swap的public成员函数来做真正的置换工作，然后将std::swap特化，令他调用成员函数。

```c++
class Widget { // same as above, except for the
public: // addition of the swap mem func
...
void swap(Widget& other)
{
	using std::swap; // the need for this declaration is explained later in this Item
	swap(pImpl, other.pImpl); // to swap Widgets, swap their pImpl pointers
} 
...
};
namespace std {
	template<> // revised specialization of
	void swap<Widget>(Widget& a, // std::swap
	Widget& b)
	{
		a.swap(b); // to swap Widgets, call their
	} // swap member function
}
/*
这段代码定义了一个名为 "Widget" 的类，并为这个类的对象定义了 std::swap 模板函数的特化版本。类中有一个名为 "swap" 的成员函数，它会交换类的 "pImpl" 指针的值与另一个 Widget 对象的值。

Widget 类的 std::swap 特化版本在 std 命名空间中定义，它调用类的 swap 成员函数。这意味着当标准的 swap 函数在两个 Widget 对象之间调用时，它会使用 swap 成员函数来执行交换操作。

这段代码的一个主要特点是在成员函数 swap 中使用 "using std::swap" 语句。这是为了确保在交换 pImpl 指针时使用标准 swap 函数而不是成员函数 swap。这样做是为了防止无限递归并确保交换正确执行。
*/
```

这种做法不仅能够通过编译，还与STL容器有一致性。因为所有STL容器也都提供有public swap成员函数和std::swap特化版本（用以调用前者）

> 这是 std::vector<T> 中的 swap 成员函数的实现：
>
> ```c++
> codetemplate<class T, class Alloc>
> inline void vector<T, Alloc>::swap(vector<T, Alloc>& x)
> {
>     std::swap(this->impl_, x.impl_);
> }
> ```
>
> 这是 std::swap 的 vector 特化版本的实现：
>
> ```c++
> codetemplate<class T, class Alloc>
> inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
> {
>     x.swap(y);
> }
> ```
>
> 可以看到, vector中的swap成员函数调用了 std::swap,而std::swap特化版本又调用了vector中的swap成员函数。 它们两个配合使用，可以使得 vector 与其它容器具有一致性，且保证了vector中数据交换的高效性。

然而假设Widget和WidgetImpl都是模板而非类的话，或许我们可以试试将WidgetImpl内的数据类型加以参数化（模板）：但是结果是过不了编译

```c++
template<typename T>
class WidgetImpl { ... };
template<typename T>
class Widget { ... };


//下面的代码是不合法的。
namespace std {
    template<typename T>
    void swap<Widget<T> >(Widget<T>& a, // error! illegal code!
    Widget<T>& b)
    { a.swap(b); }
}
```

上面的代码之所以有误，是因为我们企图偏特化一个函数模板。但是C++只允许我们对类进行偏特化，所以上面的代码通不过编译。

当你打算偏特化一个函数模板时，惯常做法是简单地为它添加一个重载版本。

```c++
namespace std {
    template<typename T> // an overloading of std::swap 
    void swap(Widget<T>& a, // (note the lack of “<...>” after
    Widget<T>& b) // “swap”), but see below for
    { a.swap(b); } // why this isn’t valid code
}
```

一般而言，重载函数模板没有问题，但是std是个特殊的命名空间，用户可以全特化std里的templates，但是不可以添加新的template过去。

为解决这种问题，我们还是声明一个非成员函数让它调用成员函数，但不再将那个non-member swap 声明为std::swap的特化版本或重载版本。假设Widget的所有相关机能都被置于命名空间WidgetStuff内，整个结果看起来就像这样：

```c++
namespace WidgetStuff {
... // templatized WidgetImpl, etc.
    template<typename T> // as before, including the swap
    class Widget { ... }; // member function
    ...
    template<typename T> // non-member swap function;
    void swap(Widget<T>& a, // not part of the std namespace
    Widget<T>& b)
    {
    	a.swap(b);
    }
}
```

现在， 任何地点的任何代码如果打算置换两个Widget对象，因而调用swap，C++的名称查找法则（name lookup rules；更具体地说是所谓argument-dependent lookup 法则（实参取决之查找规则））会找到WidgetStuff内的Widget专属版本。

> C++ 的名称查找法则是指编译器查找符号（例如变量、函数、类、模板等）的过程。这些规则决定了编译器如何确定符号的含义，以便在编译时进行类型检查和代码生成。
>
> 在 C++ 中，argument-dependent lookup (ADL) 法则是指，当调用一个函数时，如果该函数的所有参数类型都在某个命名空间内定义，则编译器会在该命名空间内查找该函数。如果该命名空间内没有找到该函数，则会继续在全局空间中查找该函数。
>
> 因此，在上面的代码中，如果任何代码调用 "swap(a, b)"，其中 "a" 和 "b" 的类型都是 "Widget<T>"，那么编译器会首先在 "WidgetStuff" 命名空间中查找 "swap" 函数，因为 "Widget<T>" 和 "swap" 函数都在该命名空间内定义。如果在该命名空间内找到了 "swap" 函数，则编译器会使用该函数。因此，编译器会使用 "WidgetStuff" 命名空间内的 "swap" 函数版本。

现在我们已经对default swap、member swaps、non-member swaps、std::swap特化版本、以及对swap的调用，现在来做个总结：

- 首先、如果swap的默认版本对你的class或class template提供可接受的效率，那么你不需要做什么。
- 其次，如果swap默认版本的效率不足（一般来说都是因为类或模板使用了pimpl手法），试着做以下事情：
  - 提供一个public swap成员函数，让它高效地置换你的类型的两个对象值。这个函数绝不应该抛出异常。
  - 在你的class或template所在的命名空间内提供一个non-member swap，并令它调用上述swap函数。
  - 如果你正编写一个class而非类模板，为你的类特化std::swap，并令它调用你的swap成员函数
- 最后，如果你调用swap，请确定包含一个using 声明式，以便让std::swap在你的函数内曝光可见，然后不加任何namespace修斯副，赤裸裸地调用swap。



注：成员版的swap决不可抛出异常，因为swap的一个最好应用是帮助class和class template提供强烈的异常安全性保障。【条款29】详细描述了细节。但这有一个前提，即成员版swap不抛出异常。这个约束只要求成员版，因为默认swap是以copying函数为基础的，而两者（copy构造函数，copy assignment）都允许抛出异常。



#### 总结：

- 当std::swap 对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常。
- 如果你提供一个member swap，也该提供一个non-member swap 用来调用前者。对于class（而非templates），也请特化std::swap。
- 调用swap时应针对std::swap使用using 声明式，然后调用swap并且不带任何命名空间资格修饰。
- 为用户定义类型进行std templates全特化是好的，但是不要尝试在std内乱加东西。

## 第五章 实现

**[Implementations]**

For the most part, coming up with appropriate definitions for your classes (and class templates) and appropriate declarations for your functions (and function templates) is the lion’s share of the battle. 大多数情况下，适当地提出你的class(template)和function(template)声明是花费心力最多的两件事。

Once you’ve got those right, the corresponding implementations are largely straightforward. Still, there are things to watch out for. 一旦正确完成这些，相应的实现大多直接了当，但是还有些需要小心。

- Defining variables too soon can cause a drag on performance.  太快定义变量可能导致效率上的拖延。
- Overuse of casts can lead to code that’s slow, hard to maintain, and infected with subtle bugs. 过度使用转型可能导致代码变慢且难以维护。
- Returning handles to an object’s internals can defeat encapsulation and leave clients with dangling handles.返回对象内部的句柄可能会破坏封装并可能引起虚吊。
-  Failure to consider the impact of exceptions can lead to leaked resources and corrupted data structures. 未考虑异常带来的冲击可能导致资源泄漏和崩坏的数据结构。
- Overzealous inlining can cause code bloat. 过分的inline可能会引起代码膨胀。
- Excessive coupling can result in unacceptably long build times. 过渡耦合则可能导致让人不可接受的建构时间。

### 条款26 尽可能延后变量定义式的出现时间

Postpone variable definitions as long as possible

在你定义了变量而其类型带有构造函数和析构函数，那么你就会承担构造和析构的成本。因此应该尽可能避免这一点。尤其是牵扯到异常导致程序中断时。

```c++
// this function defines the variable "encrypted" too soon
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    string encrypted;
    if (password.length() < MinimumPasswordLength) {
     throw logic_error("Password is too short");
    }
    ... // do whatever is necessary to place an
    // encrypted version of password in encrypted
    return encrypted;
}
//上面的代码中， 万一出现异常，encrypted这个变量就没有用到。
// this function postpones encrypted’s definition until it’s truly necessary
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    if (password.length() < MinimumPasswordLength) {
    throw logic_error("Password is too short");
    }
    string encrypted;
    ... // do whatever is necessary to place an
    // encrypted version of password in encrypted
    return encrypted;
}
```

但是上面第二段代码也并非尽善尽美，因为encrypted虽获得定义但是没有赋初值。这就意味着其调用的是default构造函数。【条款4】说过，通过default构造函数构造出一个对象然后对它赋值比直接在构造时指定初值效率差。改正后的代码如下：

```c++
std::string encryptPassword(const std::string& password)
{
	using namespace std;
    if (password.length() < MinimumPasswordLength) {
    throw logic_error("Password is too short");
    } 
    string encrypted(password); // define and initialize via copy
    // constructor
    encrypt(encrypted);
    return encrypted;
}
```



在循环里，声明变量也有考究。

```c++
// Approach A: define outside loop 				// Approach B: define inside loop
Widget w;
for (int i = 0; i < n; ++i) 					{ for (int i = 0; i < n; ++i) { 
w = some value dependent on i; 					Widget w(some value dependent on i);
... 											...
} 												}
```

- 方法A：一个构造函数，一个析构函数，n个赋值函数
- 方法B：n个构造函数，n个析构函数

如果class的赋值成本低于一组构造+析构成本，做法A比较高效，尤其是n比较大的时候。

否则B更好，此外考虑B的另一个理由是，做法A可能会使得w的作用域（覆盖整个循环）比做法B更大，有时候会对程序的可理解性和易维护性造成冲突。

作者推荐，除非你知道赋值成本比构造+析构更低或者你特别需要效率，不然建议使用做法B。、

***但是我习惯A诶。。。因为这种很多时候就是一个参数跑一边循环，然后看看被折腾成什么样，B的话我还是得在循环过程中吐出来一个参数。。。还是看实际操作情况吧，只要赋值不是很大，一般来说影响不大，，，吧？***

#### 总结：

- 尽可能延后变量定义式的出现，这样做可以增加程序的清晰度并改善程序效率。

### **条款27 尽量少做转型动**作

Minimize casting

C++规则的设计目标之一是，保证“类型错误”绝不可能发生。理论上，如果你的程序很“干净地”通过编译，那就表示它并不企图在任何对象身上执行任何不安全、无意义、愚蠢的操作。这是一个很有价值的保证，不要草率地放弃。

但是转型这一操作破坏了类型系统。不同于别的语言，C++中的映射带来风险的可能性更大，需要审慎地对待。

转型语法通常有三种形式：

- 旧式转型
  - C风格的转型动作
    - (T)expression
  - 函数风格的转型动作
    - T(expression)
- 新式转型（C++ style）
  - const_cast<T>(expression)
  - dynamic_cast<T>(expression)
  - reinterpret_cast<T>(expression)
  - static_cast<T>(expression)



- const_cast<T>(expression) 通常被用来将对象的常量性转除，他也是唯一有此能力的C++-style的转型操作符
- dynamic_cast<T>(expression) 主要用来执行安全向下转型，也就是用来决定某个对象是否归属继承体系中的某个类型。它是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作。
- reinterpret_cast<T>(expression) 意图执行低级转型，实际动作可能取决于编译器，这就意味着它不可移植。【条款50】
- static_cast<T>(expression) 用来强迫隐式转换（implicit conversions）。可以把non-const转化为const（但是反过来不行），可以将point-to-base转化为point-to-derived。

> 四种新式转换，最明显的区别是安全性和目的：
>
> - `const_cast` 和 `reinterpret_cast` 很不安全，它们没有任何类型检查，所以易出错。
> - `dynamic_cast` 和 `static_cast` 更安全，它们进行了类型检查，可以保证转换后的类型是正确的。
> - `dynamic_cast` 用于多态类型转换，它检查类型转换是否可行。
> - `static_cast` 用于简单的类型转换，它不进行任何类型检查，但它可以在编译时发现错误。

> ### reinterpret_cast
>
> `reinterpret_cast` 是一种不安全的强制类型转换，它用于重新解释类型的二进制表示。
>
> 它实现以下功能：
>
> - 将指针或引用转换为不同类型的指针或引用。
> - 将整数转换为指针或者反之。
> - 将类的对象的地址转换为其他类型的指针。
>
> 它不安全是因为它不进行任何类型检查，所以很容易出错。它是有可能造成数据损坏，程序崩溃或其他不可预期的后果。
>
> 尽管不安全，但有些情况下仍然会使用 `reinterpret_cast`，例如：
>
> - 在编写驱动程序和其他低级代码时，有时需要重新解释类型。
> - 在编写平台特定的代码时，有时需要强制转换类型以访问硬件或其他底层资源。
>
> 但总的来说，在大多数情况下，应该避免使用 `reinterpret_cast`。如果需要进行类型转换，应该使用 `static_cast` 或 `dynamic_cast`。

> ### `dynamic_cast` 和 `static_cast` 
>
> `dynamic_cast` 和 `static_cast` 都是用于类型转换，但它们有以下不同点：
>
> 1. 检查：`dynamic_cast` 会在运行时进行类型检查，如果转换不可行，则会返回 `nullptr`，而 `static_cast` 不会进行类型检查，它相当于强制类型转换。
> 2. 继承关系：`dynamic_cast` 只能用于向下转换，也就是说，它只能在继承关系中用于从基类转换为派生类，而 `static_cast` 可以用于向上和向下转换。
> 3. 速度：因为 `dynamic_cast` 需要进行类型检查，所以速度略慢于 `static_cast`。
>
> 代码示例：
>
> ```c++
> #include <iostream>
> 
> class Base {};
> 
> class Derived : public Base {};
> 
> int main() {
>     Base *b = new Base;
>     Derived *d = static_cast<Derived *>(b);  // 未安全的强制类型转换
>     d = dynamic_cast<Derived *>(b);  // 返回 nullptr
>     if (d) {
>         std::cout << "转换成功" << std::endl;
>     } else {
>         std::cout << "转换失败" << std::endl;
>     }
>     return 0;
> }
> 
> /*
> cannot 'dynamic_cast' 'b' (of type 'class Base*') to type 'class Derived*' (source type is not polymorphic)
> 使用 dynamic_cast 进行类型转换时，源类型必须是多态类型，即它必须至少有一个虚函数。在这种情况下，必须先在 Base 类中定义虚函数，然后才能使用 dynamic_cast 进行类型转换。
> */
> #include <iostream>
> 
> class Base {
> public:
>     virtual void func() {}
> };
> 
> class Derived : public Base {};
> 
> int main() {
> 
>     Base *b = new Base;
>     //Derived *d = static_cast<Derived *>(b);  // 未安全的强制类型转换
>     d = dynamic_cast<Derived *>(b);  // 返回 nullptr
>     if (d) {
>         std::cout << "Cast from b to d is successful\n";
>     } else {
>         std::cout << "Cast from b to d is not successful\n";
>     }
>     return 0;
> }
> 
> ```
>
> 总的来说，如果需要进行继承关系中的类型转换，应该使用 `dynamic_cast`，因为它安全且灵活，如果确定类型转换是安全的，则可以使用 `static_cast`。

许多程序员认为，转型实际上什么都没有做，只是告诉编译器把某种类型视为另一种类型，这是一种错误的观念。哪怕是最简单的`int x, y;double d = static_cast<double>(x)/y;`将int x转型为double也肯定会产生一些代码。因为在大部分计算机体系结构中，int的底层表述不同于double的底层表述。

```c++
#include <iostream>

class Base {
public:
    int m = 1;
};

class Derived : public Base {
public:
    int a  = 1;
    double b = 2.0;
};
using namespace std;
int main() {

    Derived d;
    Derived *pd = &d;
    Base *pb = &d; // implicitly convert Derived* ⇒ Base*
    cout<<pd<<endl;
    cout<<pb<<endl;
    cout<<sizeof(*pd)<<endl;
    cout<<sizeof(*pb)<<endl;
    return 0;
}
/*
0xf8337ff880
0xf8337ff880
16
4
*/
```

书里说单一对象可能用于一个以上的地址，例如以`Base*`指向它时的地址以及以`Derived*`指向它的地址。***（但是我自己跑没出现诶）***

> C、Java和C#不支持这种情况是因为它们使用了隐式指针类型转换，并且不支持从派生类指针到基类指针的显式转换。因此，一个对象只有一个地址，无论它是什么类型。与C++不同，C++允许显式指针类型转换，因此一个对象可能有多个地址，具体取决于它的类型和如何被访问。但是不同编译器可能实现的方法不同。

todo 这里回头研究一下吧，应该牵扯到编译器了。



另一件有关转型的事情是，我们很容易写出似是而非的代码。

譬如想在子类的虚函数代码中调用基类的对于函数。下面的代码看起来对，实际上错。

```c++
#include<iostream>
using namespace std;
class Window { // base class
public:
    int m = 2;
    virtual void onResize() {m = 9;cout<<"Window"<<endl;} // base onResize impl
};

class SpecialWindow : public Window { // derived class
public:
    int n = 0;
    virtual void onResize() { // derived onResize impl;
        cout<<"Special Window"<<endl;
        n = 4;
        static_cast<Window>(*this).onResize(); // cast *this to Window,
    } // specific stuff
};
int main(){
    SpecialWindow A;
    cout<<A.m<<endl;
    cout<<A.n<<endl;
    A.onResize();
    cout<<A.m<<endl;
    cout<<A.n<<endl;
}

/*
2
0
Special Window
Window
2
4
可以看出基类的部分没有改变
*/
```

这段代码确实将`*this`转型为Window，也调用的是Window::onResize。但是它调用的不是当前对象上的函数，而是稍早转型动作所建立的`*this`对象上base class成分的暂时副本上的onResize。函数就是函数，成员函数只有一份，但是问题是成员函数都有一个隐藏的this指针，会因此影响函数操作的数据。

> 当调用`static_cast<Window>(*this).onResize()`时，它会创建当前对象的基类部分的一个新的临时副本，然后在该副本上调用`onResize`函数。 这是因为静态转换会创建一个新的临时副本，并从当前对象中选择基类部分，并以这个副本为接收者调用该函数。 这意味着在该副本上执行的任何更改都不会影响到当前对象。

解决方法是拿掉转型动作，说老实话。你只是想调用base class版本的函数，那就好好写。

```c++
#include<iostream>
using namespace std;
class Window { // base class
public:
    int m = 2;
    virtual void onResize() {m = 9;cout<<"Window"<<endl;} // base onResize impl
};

class SpecialWindow : public Window { // derived class
public:
    int n = 0;
    virtual void onResize() { // derived onResize impl;
        cout<<"Special Window"<<endl;
        n = 4;
        Window::onResize(); // cast *this to Window,
    } // specific stuff
};
int main(){
    SpecialWindow A;
    cout<<A.m<<endl;
    cout<<A.n<<endl;
    A.onResize();
    cout<<A.m<<endl;
    cout<<A.n<<endl;
}

/*
2
0
Special Window
Window
9
4
*/
```



至于dynamic_cast，它的许多实现版本非常慢。之所以需要它，通常是因为你想在一个你认定为derived class对象身上执行derived class函数，但是你手上只有一个”指向base“的指针或引用。

一般来说有两种方法避免这个问题：

1. 使用容器并在其中存储直接指向derived class对象的指针，从而消除通过base class接口处理对象的需要。
2. 在base class内提供虚函数以便各个派生类重载。



优秀的C++的代码很少使用转型，我们应该尽量避免并隔离他们，通常是把它们隐藏在某个函数内。

#### 总结：

- 如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_cast。如果有个设计需要转型，试着发展无需转型的替代设计。
- 如果转型是必要的，试着将它隐藏在某个函数背后，客户可以调用这个函数而无需将转型放进他们自己的代码中。
- 尽量使用C++新式转型。

### 条款28 避免返回handles指向对象内部成分

Avoid returning “handles” to object internals

通过两个点定义矩形，同时为了让Rectangle对象尽可能小，将这些点放在一个辅助的struct内再让Rectangle去指它。

```c++
class Point { // class for representing points
public:
    Point(int x, int y);
    ...
    void setX(int newVal);
    void setY(int newVal);
    ...
};

struct RectData { // Point data for a Rectangle
    Point ulhc; // ulhc = “ upper left-hand corner”
    Point lrhc; // lrhc = “ lower right-hand corner”
};
class Rectangle {
    ...
    private:
    std::tr1::shared_ptr<RectData> pData; // see Item 13 for info on
}; // tr1::shared_ptr


```

Rectangle的客户必须能够计算 Rectangle的范围，这个class提供了upperLeft和lowerRight函数，又根据【条款20】(传引用比传值更高效)，这些函数返回reference。

```c++
class Rectangle {
public:
    ...
    Point& upperLeft() const { return pData->ulhc; }
    Point& lowerRight() const { return pData->lrhc; }
    ...
};

```

以上的代码可以通过编译，但是是错误的，因为一方面upperLeft和lowerRight函数设置为const，意思是只提供告知坐标点，并不希望修改内部值。但是这两个函数都返回指向private内部数据的reference，调用者可以通过这些reference修改内部数据。

这就带给我们两个教训：

1. 成员变量的封装性最多只等于“返回其reference”的函数的访问级别。本例中ulhc和lrhc虽然都被设置为private，但是public函数传出了它们的引用，所以它们实际上是public的。
2. 如果const成员函数传出一个reference，后者所指数据与对象自身有关联，而它又被储存于对象之外，那么这个函数的调用者可以修改这个数据，二者正是bitwise constness的一个附带结果。【条款3】

```c++
Point coord1(0, 0);
Point coord2(100, 100);
const Rectangle rec(coord1, coord2); // rec is a const rectangle from
// (0, 0) to (100, 100)
rec.upperLeft().setX(50); // now rec goes from
// (50, 0) to (100, 100)!

```

以上我们说的是返回引用，实际上，返回指针或是迭代器，类似的情况也会发生，因为引用、指针、迭代器都是所谓句柄（handle），用于取得某个对象，而返回一个代表对象内部数据的handle，随之而来的便是降低对象封装性的风险。同时，他也可能导致“虽然调用const成员函数却造成对象状态被更改”的情况。

通常我们认为，对象的“内部”就是指它的成员变量，而实际上，不被公开的（非public）的成员函数也是对象内部的一部分。因此，也要留心不要返回它们的handles。

对于之前的代码，想弥补这个问题也很简单，在之前加上const即可。

```c++
class Rectangle {
public:
    ...
    const Point& upperLeft() const { return pData->ulhc; }
    const Point& lowerRight() const { return pData->lrhc; }
    ...
};

//第一个const在方法upperLeft()前面，表示该方法不会修改调用它的对象。
//第二个const在方法upperLeft()后面，表示该方法返回一个常量Point对象的引用。返回值不能被修改。
```

但即使如此，这两个函数还是返回了“返回对象内部”的handle，可能会在其他地方带来问题。比如虚吊的handle。最常见的来源就是函数返回值。

譬如某个函数返回GUI对象的外框，客户在调用时获得一个新的、暂时的Rectangle对象，对boundingBox的调用，我们得到的是一个临时的Rectangle对象，权且称为temp。然后是upperLeft，返回一个reference指向temp中的一个内部成分，但是在这句语句结束后，temp就被销毁了，而pUpperLeft就虚吊了。

```c++
class GUIObject { ... };
const Rectangle boundingBox(const GUIObject& obj); 


GUIObject *pgo; 
const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft()); 

/*
可以改为
  GUIObject go;
  GUIObject *pgo = &go; 
  const Rectangle bounding_box = boundingBox(*pgo);
  const int *pUpperLeft = &(bounding_box.upperLeft());
  std::cout << *pUpperLeft << std::endl;
这样可以避免上面提到的两个问题：
pgo被初始化为指向合法的GUIObject对象的指针。
bounding_box是一个合法的Rectangle对象，pUpperLeft指向的内存在整个程序执行期间都是合法的
*/
```



以上就是为什么函数如果返回一个handle代表对象内部成分总是危险的原因。无论这个handle是指针、迭代器、引用，也不论这个handle是否为const，也不论哪个返回handle的成员函数是否为const。这里的唯一关键是有个handle被传出去了，一旦如此，你就是暴露在“handle比其所指对象更加长寿”的风险下。

不过，这也不意味着你绝对不会不能让成员函数返回handle。又是你还必须这么做。例如operator[]就允许你得到string和vector里的个别元素，而这些operator[]就是返回reference指向容器内的数据。这些数据会随着容器被销毁而销毁。但是这样的函数毕竟是例外，不是常态。

```c++
#include<iostream>
using namespace std;
#include<vector>

int main(){
    vector<int> *vec = new vector<int>({1,2,3,4});
    cout<<sizeof((*vec))<<endl;
    cout<<(*vec).size()<<endl;
    cout<<(*vec)[1]<<endl;
    delete vec;
    cout<<sizeof((*vec))<<endl;
    cout<<(*vec).size()<<endl;
    cout<<(*vec)[1]<<endl;
}
/*
24
4
2
24//当使用 sizeof 求对象的内存大小时，返回的值表示的是内存占用的字节数，而不是对象是否存在。因此，在删除对象后使用该对象的内存大小是安全的。在这种情况下，在调用 delete vec 后，内存仍然占用了 24 个字节，但内存中的内容不再可靠，因此访问该内存会导致未定义行为（UB）。因此，不建议在程序中访问已经删除的对象。
18446744073709516032 //虚吊了，每次不一样
550//虚吊了，每次不一样
*/
```



#### 总结：

- 避免返回handles（包括references、指针、迭代器）指向对象内部。遵守这个条款可增加封装性，帮助const成员函数的行为像个const，并且将虚吊号码牌的可能性降至最低。

### 条款29 为”异常安全“而努力是值得的

Strive for exception-safe code

异常安全性有些像怀孕，你要么怀孕，要么没有，不存在部分怀孕的说法，而且在我们完成求偶前，也无法确实地讨论生育。

下面是从异常安全性来看非常糟糕的一段代码，这个class意图用来表现夹带背景图案的GUI菜单，并工作在多线程环境下，利用互斥器来作为并发控制。

```c++
class PrettyMenu {
public:
    ...
    void changeBackground(std::istream &imgSrc); // change background
    ... // image
private:
    Mutex mutex; // mutex for this object
    Image *bgImage; // current background image
    int imageChanges; // # of times image has been changed
};

void PrettyMenu::changeBackground(std::istream &imgSrc) {
    lock(&mutex); // acquire mutex (as in Item 14)
    delete bgImage; // get rid of old background
    ++imageChanges; // update image change count
    bgImage = new Image(imgSrc); // install new background
    unlock(&mutex); // release mutex
}
```

**异常安全有两个条件**，以上函数没有满足任何一个。

- 不泄露任何资源。

  一旦new Image(imaSrc)导致异常，对unlock的调用就不会被执行，而互斥器就永远被把持住了。

- 不允许数据结构被破坏（Don’t allow data structures to become corrupted）

  如果new Image(imaSrc)导致异常，bgImage就是指向一个已被删除的对象，imageChanges也被累加，而实际上并没有新的正确的图像被成功安装。

**解决资源泄露**的问题很容易，因为【条款13】讨论过如何以对象管理资源，而【条款14】也导入了lock class作为一种确保互斥器被即使释放的方法。

```c++
//条款14里的Lock
class Lock {
public:
    explicit Lock(Mutex *pm) // init shared_ptr with the Mutex
    : mutexPtr(pm, unlock) // to point to and the unlock func as the deleter 指定unlock作为删除器
    { 
    	lock(mutexPtr.get()); // see Item 15 for info on “get” 
	}
private:
	std::tr1::shared_ptr<Mutex> mutexPtr; // use shared_ptr
}; // instead of raw pointer

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Lock ml(&mutex); // from Item 14: acquire mutex and
    // ensure its later release
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
}
```

对于如Lock这样的资源管理类，有一个很棒的事情，就是它们通常会使代码更短，这里我们就不需要调用unlock了（因为Lock会自动释放资源）。

一个简单常识，少做少错。（As a general rule, less code is better code, because there’s less to go wrong and less to misunderstand when making changes.）

下面我们来研究**数据结构的败坏**

首先我们来了解一下异常安全函数（Exception-safe function） 提供以下三个保证之一：

- 基本承诺：如果抛出异常，程序内的任何事物仍然保持在有效状态下，没有任何对象或数据结构会因此而败坏，所有对象都处于一种内部前后一致的状态（例如所有class约束条件都继续获得满足），然而程序的显式状态恐怕不可预料。举例，我们可以撰写changeBackground使得当抛出异常是，PrettyMenu对象可以继续拥有原背景图像，或是令它拥有某个缺省背景图像，但客户无法预期哪一种情况。
- 强烈保证：如果异常被抛出。程序状态不改变。调用这样的函数需有这样的认识：如果函数成功，就是完全成功。如果函数失败，程序会回复到调用函数之前的状态。（强烈保证比起基本承诺，让人放心多了，因为只有两种可能，而基本承诺下玩意出现异常，程序可能处于任何合法但不合理的状态）
- 不抛保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能，作用于内置类型身上所有操作都提供nothrow保证。这是异常安全码中一个必不可少的关键基础材料。

异常安全码必须提供以上三种保证之一。我们的抉择是，我们应该为我们所写的函数提供哪一种保证？

一般而言你应该会想提供可实施的最强烈的保证。一般而言，no-throw函数很棒，但还是一般来说很难做到，抉择往往在基本保证和强烈保证内。

对于changeBackground，我们提供强烈保证并不困难。

首先，用智能指针来管理资源。避免泄漏。

第二，重新排列changeBackground里的顺序，在更换图像后在累加imageChanges。

```c++
class PrettyMenu {
    ...
    std::tr1::shared_ptr<Image> bgImage;
    ...
};
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Lock ml(&mutex);
    bgImage.reset(new Image(imgSrc)); // replace bgImage’s internal
    // pointer with the result of the
    // “new Image” expression
    ++imageChanges;
}
```

这里不再需要手动删除旧图像，因为智能指针会处理好资源释放。

这样看上去似乎可以提供强烈的异常安全保证了，但是美中不足的是参数imgSrc。如果Image构造函数出现异常，有可能输入流input stream的读取记号read marker被移走，而这样的搬移对程序其他部分是一种可见的状态改变。所以changeBackground在解决这个问题之前只提供基本的异常安全保证。

有一个一般性的设计策略很典型地可以做到强烈保证，即copy and swap。

原则很简单：为你打算修改的对象作出一份副本，然后再副本上作出一切必要修改，然后若有任何修改动作抛出异常，原对象仍保持未改变状态。待所有改变都成功后，再将修改过的那个副本和原对象在一个不抛出异常的操作中置换swap。

实现上，通常是采用pimpl idiom手法【条款31】，即将所有隶属对象的数据从原对象放进另一个对象内，然后赋予原对象一个指针，指向那个所谓的实现对象（即副本）。

> copy-and-swap 是一种拷贝构造函数和赋值运算符的实现策略，它使用交换技巧以避免资源泄漏，同时保证强烈的异常安全性。该策略的基本流程如下：
>
> 1. 创建该类的一个临时对象的拷贝。
> 2. 使用 std::swap 交换该类的成员变量和临时对象的成员变量。
> 3. 销毁临时对象。
>
> 因为 std::swap 保证不抛出异常，因此 copy-and-swap 策略提供了强烈的异常安全性。同时，如果拷贝构造函数或赋值运算符引发了异常，则临时对象的析构函数会被调用，因此不会发生资源泄漏。
>
> copy-and-swap 策略非常适用于实现拷贝构造函数和赋值运算符，并且通常会比其他实现方法更简单，更具可读性。

```c++
struct PMImpl { // PMImpl = “PrettyMenu
    std::tr1::shared_ptr<Image> bgImage; // Impl.”; see below for
    int imageChanges; // why it’s a struct
};
class PrettyMenu {
    ...
private:
    Mutex mutex;
    std::tr1::shared_ptr<PMImpl> pImpl;
};
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    using std::swap; // see Item 25
    Lock ml(&mutex); // acquire the mutex
    std::tr1::shared_ptr<PMImpl> // copy obj. data
    pNew(new PMImpl(*pImpl));
    pNew->bgImage.reset(new Image(imgSrc)); // modify the copy
    ++pNew->imageChanges;
    swap(pImpl, pNew); // swap the new
// data into place
} // release the mutex
```

这里让PMImpl成为一个struct而不是class，是因为pImpl 为private 使得PrettyMenu获得数据封装性，如果你想，也可以把PMImpl嵌套于PrettyMenu里。但打包问题（packaging，例如独立撰写异常安全码）是我们这里挂虑的事情。

> 这是一个嵌套类的演示。
>
> ```c++
> class Window {
>  public:
>   Window(const std::string& title, int width, int height);
>   ~Window();
>   void Show();
> 
>  private:
>   class Impl;
>   std::unique_ptr<Impl> pImpl;
> };
> 
> class Window::Impl {
>  public:
>   Impl(const std::string& title, int width, int height);
>   ~Impl();
>   void Show();
>   // ...其他窗口系统的实现细节...
> };



> 这里还有一个pimpl的例子
>
> ```c++
> #include <iostream>
> #include <memory>
> 
> class WindowImpl {
> public:
>     WindowImpl() = default;
>     WindowImpl(int width, int height) : width_(width), height_(height) {}
> 
>     int width() const { return width_; }
>     int height() const { return height_; }
> 
>     void resize(int width, int height) {
>         width_ = width;
>         height_ = height;
>     }
> 
> private:
>     int width_ = 0;
>     int height_ = 0;
> };
> 
> class Window {
> public:
>     Window() : impl_(std::make_unique<WindowImpl>()) {}
>     Window(int width, int height) : impl_(std::make_unique<WindowImpl>(width, height)) {}
> 
>     int width() const { return impl_->width(); }
>     int height() const { return impl_->height(); }
> 
>     void resize(int width, int height) { impl_->resize(width, height); }
> 
> private:
>     std::unique_ptr<WindowImpl> impl_;
> };
> 
> int main() {
>     Window w(800, 600);
>     std::cout << "Width: " << w.width() << ", Height: " << w.height() << std::endl;
> 
>     w.resize(1024, 768);
>     std::cout << "Width: " << w.width() << ", Height: " << w.height() << std::endl;
> 
>     return 0;
> }
> 
> ```
>
> 在这个代码中，我们有两个类：`Window` 和 `WindowImpl`。`WindowImpl` 包含窗口的实际实现，而 `Window` 仅保留一个指向实现的指针。这样做可以隐藏实现细节

copy-and-swap 策略是对对象状态做出“全有或全无”改变的一个很好办法。但一般而言，他也无法保证整个函数又强烈的异常安全性。

比如这样的一个函数

```c++
void someFunc()
{
    ... // make copy of local state
    f1();
    f2();
    ... // swap modified state into place
}
```

如果f1或f2的异常安全性比“强烈保证”低，那么someFunc就很难成为“强烈保证”。即使f1、f2都是强烈异常安全，情况也不会因此好转。如果f1圆满结束，程序状态很有可能有所改变，因此如果f2随后抛出异常，函数装填和someFunc被调用之前不同，哪怕f2什么都没有改变。

问题就出在连带影响。如果函数只操作局部性状态，那么提供强烈保证相对而言就简单些。但一旦函数对非局部性数据有连带影响，比如删增某条数据库数据，一旦操作送出，别的客户很可能已经看到了。

另一个会阻止你提供强烈保证的原因是效率，毕竟譬如copy-swap这种方式耗费太多资源了。

所以，在提供强烈保证比较困难时，提供基本保证，也是个自然的决定。但是如果你写的函数完全不提供异常安全保证，别人也会合理假设你在这方面有缺失。

#### 总结：

- 异常安全函数 即使发生异常不会泄露资源或允许任何数据结构败坏。这样的函数区分为三种保证。
- 强烈保证往往可以通过copy-and-swap实现出来，但强烈保证 并非对所有函数都可实现或具备现实意义。
- 函数提供的异常安全保证通常最高只等于其所调用值各个函数的异常安全保证中的最弱者。

### 条款30 透彻了解inlining的里里外外

Understand the ins and outs of inlining

Inline函数，它们看起来像函数，动作像函数，比宏好得多，可以调用它们而又不需要蒙受函数调用所招致的额外开销。

好处不止于此，编译器最优化机制通常被设计用来浓缩那些不含函数调用的代码。所以当你inline某个函数，或许编译器就有能力对它执行语境相关最优化。而大部分编译器绝不会对一个outlined函数调用动作执行如此之最优化。

但是凡事都是有代价的，inline函数背后的整体观念，就是对函数的每个调用都以函数本体来替换他。这几乎肯定会增加目标码的大小。内存有限的机器上，过于热衷inlining会造成程序体积太大（对可用空间而言）。即使拥有虚内存，inline造成的代码膨胀也会导致额外的换页行为，降低指令高度缓存装置的集中率，以及伴随这些而来的效率损失。

换个角度说，如果inline函数的本体很小，编译器针对函数本体产出的码可能比函数调用产出的码更小。那么就不会有以上的弊端。

记住，inline只是对编译器的一个申请，不是强制命令。这项申请可以隐喻提出，也可以明确提出。

- 隐喻提出是将函数**定义**于class定义式内。

  ```c++
  class Person {
  public:
      ...
      int age() const { return theAge; } // an implicit inline request: age is
      ... // defined in a class definition
  private:
  	int theAge;
  };
  ```

  这样的函数通常是成员函数，但【条款46】说friend函数也可以被定义在class内，若如此，那么也是被隐喻声明为inline。

- 明确声明inline函数的做法是在其定义式前加上关键字inline。例如标准的max template 往往是这样实现的。

  ```c++
  template<typename T> // an explicit inline
  inline const T& std::max(const T& a, const T& b) // request: std::max is
  	{ return a < b ? b : a; } // preceded by “inline”
  ```

Inline函数通常一定被置于头文件内，因为大多数build environment在编译过程中进行inlining，尽管有的环境可以在运行期完成inlining，不过毕竟是少数。

template通常被置于头文件内，其具现化与inlining无关。如果你正在写一个template而你认为所有根据此template生成的函数都应该inlined，那么就将这个template设为inline。否则就应该避免将模板设为inline。这对template尤其是如此，【条款44】会详细讲。

编译器会拒绝inline太过复杂（比如带有递归和循环）的函数。绝大多数的virtual函数的inline也会落空，因为从逻辑上来说，virual意味着“等待，知道运行期才确定调用哪个函数”，而inline意味着“执行前，先将调用动作替换为函数的本体”。



有时候虽然编译器有意愿inlining某个函数，还是可能为该函数生成一个函数本体。比如函数想要取某个inline函数的地址，编译器通常得为这个函数生成一个outlined本体，不然编译器不能提出一个函数指向不存在的函数。于此并提的是，编译器通常部队“通过函数指针而进行的调用”实施inlining，这意味着对inline函数的调用有可能被inline，也可能不被。取决于调用方式。

```c++
inline void f() {...} // assume compilers are willing to inline calls to f
void (*pf )() = f; // pf points to f
...
f(); // this call will be inlined, because it’s a “normal” call
pf(); // this call probably won’t be, because it’s through a function pointer
```



即使你从未使用函数指针，”未被成功inlined“的inline函数还是会困扰你。因为有时候编译器会生成构造函数和析构函数的outlined版本，如此一来它们就可以获得指针指向那些函数，在array内部元素的构造和析构中使用。

实际上构造函数和析构函数是inlining的糟糕候选人。因为C++对于对象被创建以及被销毁时会发生什么做了各式各样的保证，因此编译器实际上会自己构建很多代码安插到你的代码里。看似空白的类，可能有着很多异常处理的代码，更不必提基类子类的继承了。

程序员必须评估将函数设定为inline的代价，因为inline函数无法随着程序库的升级而升级。比如说f是程序库内的一个inline函数，一旦决定改变f，所有用到f的客户端程序都必须重新编译。然而如果是non-inline函数，一旦它有任何修改，客户端只需要重新链接就好了。如果程序块采取动态链接，升级版函数甚至可以不知不觉地被应用程序吸纳。

其实吧，上面讨论这么多，还有一个因素影响我们是否运用inline，即大部分调试器面对inline函数都无能为力，因为你无法在一个不存在的函数上设定断点。

现在我们总结出一个策略，即一开始先不要将任何函数声明为inline，或至少将inlining施行范围限制在那些一定会成为inline【条款46】的函数或类似` int age() const { return theAge; }`这样非常平淡的函数。

#### 总结：

- 将大多数inlining限制在小型、被频繁调用的函数身上。这可使日后的调试过程和二进制升级更容易。也可以使得潜在的代码膨胀问题降低到最小，使程序的速度提升机会最大化。
- 不要只因为function template出现在头文件，就把它们设定为inline。

### 条款31 将文件间的编译依存关系降至最低

Minimize compilation dependencies between files



```c++
class Person {
public:
    Person(const std::string& name, const Date& birthday,
    const Address& addr);
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
...
private:
    std::string theName; // implementation detail
    Date theBirthDate; // implementation detail
    Address theAddress; // implementation detail
};
```

看似简单的这样一个class，它也包含了诸多头文件，如果这些头文件或这些头文件依存的头文件有任何改变，那么每一个含有Person class的文件就得重新编译，每一个使用Person class的文件也得重新编译。

我们可以学习类似Java这些语言，试试将对象实现隐藏在指针背后的把戏。比如说对于Person我们可以这么做，将Person分裂成两个class，一个负责提供接口，一个负责实现接口。

```c++
#include <string> // standard library components shouldn’t be forward-declared
#include <memory> // for tr1::shared_ptr; see below
class PersonImpl; // forward decl of Person impl. class
class Date; // forward decls of classes used in
class Address; // Person interface
class Person {
public:
    Person(const std::string& name, const Date& birthday,
    const Address& addr);
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
    ...
private: // ptr to implementation;
	std::tr1::shared_ptr<PersonImpl> pImpl; // see Item 13 for info on
}; // std::tr1::shared_ptr
```

这里，Person只含有一个指针成员指向其实现类的设计常被称为“pimpl idiom”（pointer to Implemention）。这种class内的指针往往就是pImpl。

这样的设计下，Person的客户就完全与Date，Address，以及Person的实现细目分离了。那些class的任何实现修改都不需要Person客户端重新编译。此外，由于客户无法看到Person的实现细节，也就不可能写出取决于那些细节的代码。这就是真正的接口与实现分离。

这个分离的关键就是在于用“声明的依存性”替换“定义的依存性”。那正式编译依存性最小化的本质。现实中让头文件尽可能自我满足，万一做不到，则让它与其他文件内的声明式（而非定义式）相依存。

- 如果使用object references 或object pointers可以完成任务，就不要使用objects。你可以只靠一个类型声明式就定义处指向该类型的references和pointers；但是如果定义某类型的objects，就需要用到该类型的定义式。
- 如果能够，尽量使用class声明式来替换class定义式。即使它以传值方式传递该类型的参数也亦然。
- 为声明式和定义式提供不同的头文件（Provide separate header files for declarations and definitions.[我觉得作者的意思应该是将一个头文件拆成声明hpp和定义cpp，不是指将定义也放在头文件里，不然就和总结的规则2冲突了]）。当然这些文件得保持一致性，一改俱改。例如`<iosfwd>`内含iostream各组件的声明式，其对应定义则分布在若干不同的头文件内。

`<iosfwd>`非常有启发意义的是，它分外彰显本条款适用于templates也适用于non-templates。【条款30】说过Template定义式通常被放在头文件内，不过也有些build environment允许template放在非头文件内，这么一来就可以将只含声明式的头文件给templates，类似`<iosfwd>`。



像Person这样使用pimpl的class，往往被称为Handle classes。这种类想做事，方法之一就是将它们所有函数转交给相应的实现类。

```c++
#include "Person.h" // we’re implementing the Person class,so we must #include its class definition
#include "PersonImpl.h" // we must also #include PersonImpl’s class
// definition, otherwise we couldn’t call 
// its member functions; note that 
// PersonImpl has exactly the same public
// member functions as Person — their
// interfaces are identical
Person::Person(const std::string& name, const Date& birthday,const Address& addr): pImpl(new PersonImpl(name, birthday, addr)){}
std::string Person::name() const
{
	return pImpl->name();
}
```

注意，Person构造函数是以new的方式调用PersonImpl构造函数，以及在Person::name 里调用` pImpl->name()`。 让Person变成一个Handle class并不会改变它所做的事，只会改变它做事的方法。

另一个制作Handle class的方法是，令Person成为一种特殊的抽象基类，称为Interface class。这种class的目的是详细一一描述derived class的接口【条款34】，因此它**通常**不带成员变量（Java禁止interface里含有成员变量或成员函数，但是C++不禁止），也没用构造函数，只有一个virtual析构函数【条款7】以及一组pure virtual函数，用来叙述整个接口。

Interface class 的客户必须有办法为这种class创建新对象，他们通常调用一个特殊函数，这个函数扮演“真正将被具现化”的那个derived classes的构造函数的角色，这样的函数被称为factory函数 或 virtual函数，它们返回(智能)指针，指向动态分配的对象，而对象支持interface class的接口。这样的函数往往在interface class内被声明为static.

> #### 工厂函数？
>
> 工厂函数是一种创建对象的静态函数，它为客户端代码提供了一种简单的方法来创建对象，而不需要直接调用对象的构造函数。这种设计模式经常用于隐藏对象的实现细节，并使得客户端代码更加简单和灵活。
>
> #### 为什么不直接在子类里实现它自己的构造函数呢？用这个工厂函数不是有些多此一举吗
>
> 在某些情况下，通过使用工厂函数而不是直接在子类中实现构造函数，可以更好地抽象实现，并且有助于更好地隐藏实现细节，提高代码的可维护性和可读性。
>
> 例如：当您有多个子类，而且它们都需要在构造函数中执行相同的初始化操作时，工厂函数可以在一个地方处理它们，这样可以避免在每个子类中都实现一次相同的代码，从而降低代码的冗长性。
>
> 另外，工厂函数还可以隐藏构造实际实例所需的复杂性，这对于使用子类的代码来说是透明的。在某些情况下，可以使用工厂函数动态创建不同类型的实例，从而使代码更加灵活和可扩展。
>
> 因此，在某些情况下，使用工厂函数可以使代码更简洁，更易于维护和扩展，从而使您的代码更具可读性和可维护性。



```c++
#include <iostream>
#include <memory>
#include<vector>
using namespace std;
class Person {
public:
    virtual ~Person();
    virtual std::string name() const = 0;
    virtual int birthDate() const = 0;
    virtual std::string address() const = 0;
    static std::shared_ptr<Person> create(const std::string& name,const int& birthday,const string& addr);
};

class RealPerson: public Person {
public:
    RealPerson(const std::string& name, const int& birthday,
               const string& addr)
            : theName(name), theBirthDate(birthday), theAddress(addr)
    {}
    virtual ~RealPerson() {}
    std::string name() const; // implementations of these
    int birthDate() const; // functions are not shown, but
    std::string address() const; // they are easy to imagine
private:
    std::string theName;
    int theBirthDate;
    string theAddress;
};

std::string RealPerson::name() const {
    return this->theName;
}

int RealPerson::birthDate() const {
    return this->theBirthDate;
}

std::string RealPerson::address() const {
    return this->theAddress;
}

std::shared_ptr<Person> Person::create(const std::string& name,
                                            const int& birthday,
                                            const string & addr)
{
    return std::shared_ptr<Person>(new RealPerson( name, birthday,addr));
}

Person::~Person() {
    cout<<"\ngood"<<endl;
}

int main() {

    std::string name = "TXCALON";
    int dateOfBirth = 20220108;
    string address = "China Beijing";

// create an object supporting the Person interface
    std::shared_ptr<Person> pp(Person::create(name, dateOfBirth, address));
    std::cout << pp->name() // use the object via the
              << " was born on " // Person interface
              << pp->birthDate()
              << " and now lives at "
              << pp->address();
    return 0;
}

```

RealPerson 示范了Interface class两个最常见的机制之一：从Interface class(person)继承接口规格，然后实现出接口所覆盖的函数。

Interface class的第二个实现方法设计多重继承。那是【条款40】探索的主题。



Handle classes 和 Interface classes解除了接口和实现之间的耦合关系，从而降低文件间的编译依存度（compilation dependence）。那么代价是什么呢？

在Handle classes身上，成员函数必须通过implementation pointers来取得对象数据，这为每一次访问增加一层间接性。而每一个对象消耗的内存数量必须增加implementation pointers的大小。最后，implementation pointers必须初始化（在Handle class构造函数内)，指向一个动态分配的implementation object。所以你会蒙受动态内存分配以及其后的释放动作带来的开销，以及遭遇内存不足的可能。

而interface classes，由于每个函数都是virtual，所以你必须为每次函数调用付出一个indirect jump的成本【条款7】。此外Interface class派生的对象必须含有一个虚函数表。这个指针可能会增加存放对象所需的内存数量。

最后，无论Handle函数还是inline函数，都无法通过inline函数获得太大提升。【条款30】解释过函数本体为了被inlined必须典型地置于头文件内，而前两者正是为了隐藏实现细节（比如函数本体）。（Finally, neither Handle classes nor Interface classes can get much use out of inline functions. Item 30 explains why function bodies must typically be in header files in order to be inlined, but Handle and Interface classes are specifically designed to hide implementation
 details like function bodies.）

> 因为它们不太可能被频繁调用，因此使用内联函数的性能提升是有限的。句柄类和接口类的主要目的是为底层对象提供抽象接口，它们的实现很可能是复杂的，并包含大量的函数调用，这可能导致显著的性能开销。在这些情况下，不必使用内联函数。

**todo，，，这回算是找到一个翻译错误了**

#### 总结：

- 支持“编译依存性最小化”的一般构想是：相依于声明式，不要相依与定义式。基于此构想的两个手段是Handle classes 和Interface classes。
- 程序库头文件应该以“完全且仅有声明式”的形式存在，这种方法不论是否涉及templates都适用。

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