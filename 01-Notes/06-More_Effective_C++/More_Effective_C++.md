# More Effective C++



## 基础议题 Basics 

这一章描述了

- pointers和reference的差异，并告诉你他们的适当使用时机。
- 介绍了新的C++转型语法，并解释为什么新式转型法比旧式的C转型法优越。
- 检验了C的数组概念和C++的多态概念，并说明为什么混用二者是不智之举。
- 讨论了默认构造函数正反方意见。

### 条款01：仔细区别指针和引用

Item 1: Distinguish between pointers and references.

首先必须明确，没有ull reference，reference必须绑定某个对象。所以你有一个变量，其目的是用来指向（代表）另一个对象，但是也有可能不指向（代表）任何对象，那么就应该使用pointer，因为可以将pointer设为null。（现在建议使用nullptr）。反过来看，如果你设计的变量必须总是代表一个对象，就可以使用reference。

> C++11引入了nullptr关键字，用于表示空指针，其设计目的是为了解决旧的C++代码中出现的NULL指针和0值之间的二义性。nullptr可以明确表示一个空指针，而0值可以表示指针、整数、浮点数等多种类型的值，因此使用nullptr可以更准确地表达代码的意图。
>
> nullptr和NULL的另一个区别是类型安全性。nullptr是一个特殊的空指针类型，可以隐式转换为任何其他指针类型，但不能转换为整数或浮点数类型。而NULL通常被定义为0或者(void*)0，这使得它可以隐式转换为任何类型的指针、整数或浮点数。因此，nullptr提供了更好的类型安全性，可以避免在指针和其他类型之间发生不必要的隐式转换。
>
> 此外，C++11的标准库中也使用了nullptr，比如在STL中的一些函数中，如std::unique_ptr、std::shared_ptr等。
>
> 综上所述，使用nullptr可以提高代码的可读性和可靠性，同时提供更好的类型安全性。

接下来的代码会产生不可预期的结果，因为解引用一个空指针是不可预期的行为。从此我们永不考虑reference成为null的可能性。

```c++
char *pc = 0; // set pointer to null
char& rc = *pc; // make reference refer to dereferenced null pointer
```

#### Pointer和reference的差异

reference必须绑定某个对象，因此必须要有初值。因此比起指针，所以使用reference之前不需要测试其有效性。

Pointer和reference之间的另一个重要差异就是，poiners可以被重新赋值，而reference总是指向它最初获得的那个对象。

```c++
string s1("Nancy");
string s2("Clancy");
string& rs = s1; // rs refers to s1
string *ps = &s1; // ps points to s1
rs = s2; // rs still refers to s1, but s1’s value is now "Clancy"
ps = &s2; // ps now points to s2; s1 is unchanged 
```

对于operator[]，这个操作符必须返回某种"能够被当做assignment赋值对象"的东西。即令operator[]返回一个reference。

> 当我们重载operator[]用于访问一个类的成员变量时，通常希望它返回一个引用，而不是一个值，有以下几个原因：
>
> 1. 方便修改：当我们使用引用来访问一个类的成员变量时，可以直接对这个变量进行修改，而不需要使用其他方法来实现。
> 2. 更高效：返回一个引用比返回一个值更高效。当返回一个引用时，函数只需要返回一个指向已经存在的对象的指针，而不需要创建一个新的对象。因此，使用引用可以减少内存分配和复制的开销，提高程序的效率。
> 3. 符合语义：使用引用可以使代码更符合语义。当我们使用operator[]访问一个类的成员变量时，我们通常是想要访问和修改该成员变量，而不是返回一个副本。
>
> 但在某些特定的情况下，返回一个值而不是引用可能更加合适，例如用于表示"如果这个元素不存在，则返回默认值"。

### 条款02：最好使用C++转型操作符

Item 2: Prefer C++-style casts.

#### 旧式转型的问题

- 旧式的C转型方式几乎允许你将任何类型转为其他类型，这是十分拙劣的。C转型方式也缺少C++面向对象的一些转换（譬如将const指针转为non-const指针，将base指针转为derived指针）。

- 旧式转型难以辨识，旧式转型的语法结构是由一堆小括号加上一个对象名称（标识符）组成。而小括号哪里都可能出现。

  ```c++
  (T) expression  或
  T(expression) //函数风格（Function-style）
  ```

为解决C旧式转型的缺点，C++导入4个新的转型操作符，const_cast、static_cast、reinterpret_cast和dynamic_cast。

```c++
(type) expression
//you should now generally write like this:
static_cast<type>(expression)
```

- static_cast：基本拥有与C旧式转换相同的威力与意义，以及相同的限制。用于基本类型之间的转换，以及用于类之间的转换。static_cast可以执行一些简单的类型转换，例如将一个浮点数转换为整数，或将一个父类指针转换为子类指针。但是不能将struct转为int，或是double转为pointer。甚至不能移除表达式的常量性。

- const_cast：仅用于将一个常量指针或引用转换成非常量的指针或引用。const_cast可以用于去掉const属性，从而可以在不改变对象内容的情况下修改指向它的指针或引用。

- reinterpret_cast：用于将一种类型的指针或引用转换为另一种类型的指针或引用。reinterpret_cast可以执行一些较为底层的类型转换，例如将一个指向对象的指针转换为一个指向整数的指针。因为比较底层，所以与编译平台息息相关，所以不具备移植性。

  转换后的函数指针可能无法正确地调用，从而导致未定义行为。

  ```c++
  #include <iostream>
  #include<string>
  using namespace std;
  
  void readFile(char* fileName) {
      std::cout << "Reading file: " << fileName << std::endl;
  }
  void writeFile(char* fileName, const char* content) {
      std::cout << "Writing file: " << fileName << " with content: " << content << std::endl;
  }
  int main() {
      // 定义两个函数指针，一个指向 readFile，另一个指向 writeFile
      void (*readPtr)(char*);
      void (*writePtr)(char*, const char*);
  
      readPtr = &readFile;
      writePtr = &writeFile;
  
      char fileName[] = "test.txt";
      readPtr(fileName);
      //readPtr = reinterpret_cast<void (*)(char*)>(writePtr);
      readPtr = reinterpret_cast<decltype(readPtr)>(writePtr);
      readPtr(fileName);
      return 0;
  }
  /*
  Reading file: test.txt
  Writing file: test.txt with content: UH��H�� H�MH�UH��8
  */
  ```

  

- dynamic_cast：用来执行继承体系中"安全的向下转型或跨系转型动作"，用于在继承层次结构中进行类型转换。dynamic_cast可以将一个基类指针或引用转换为一个派生类指针或引用，并得知是否成功，如果转型失败，会以null指针（转型对象是指针）或是exception（转型对象是reference）表现出来。它无法应用在缺乏虚函数的类型上（如double）。也无法改变类型的常量性。最常用来转换函数指针类型。



在程序中使用新式转型法，比较容易被解析，编译器也得以诊断转型错误。

### 条款03：绝对不要以多态方式处理数组

Item 3: Never treat arrays polymorphically. 

继承最重要的性质之一就是你可以通过指向基类的指针或引用来操作子类。我们称这种行为叫做多态。

C++也允许你通过基类指针/引用来操作子类对象所形成的数组，但这几乎不会如你所预期的操作。



举例说明，array数组里存放了子类D，D继承自B。尝试用B类型的指针来对其进行处理。

`array[i]`实际上是指针算术表达式的缩写。它代表的实际是`*(array+i)`。那么array 和 array+i 之间距离有多远呢？编译器会以为数组中每一个元素的大小是B的大小，但它实际上是D的大小。所以不管是对其增删查改，都会带来不可预期的结果。

【条款33】建议具体类不要继承自另一个具体类。

### 条款04：非必要不提供默认构造函数

Item 4: Avoid gratuitous default constructors. 

default constructors的意思是在没有任何外来信息的情况下将对象初始化，一些数值会被合理置为0或者null。一些容器会被置为空容器。

但是不是所有对象都如此，有一些类"必须有一些外来信息才能生成对象" 。

#### 类没有默认构造函数可能存在的问题

- 在产生数组时，无法为数组中的对象指定constructor自变量。

  解决方法有三种，但都有些繁琐

  1. 使用non-heap数组，non-heap 数组是指在栈上分配的数组，与在堆上分配的数组（heap 数组）相对。栈上分配的数组是指在函数内部定义的局部数组，它们的生命周期与函数的生命周期相同，当函数执行完毕时，数组将被自动销毁。注意的是，栈的大小是有限制的，如果在栈上分配的数组太大，可能会导致栈溢出。因此，在需要分配大量内存的情况下，应该考虑使用堆上分配的数组。

  2. 使用指针数组而非对象数组

     ```c++
     typedef EquipmentPiece* PEP; // a PEP is a pointer to
     // an EquipmentPiece
     PEP bestPieces[10]; // fine, no ctors called
     PEP *bestPieces = new PEP[10]; // also fine
     for (int i = 0; i < 10; ++i)
     	bestPieces[i] = new EquipmentPiece( ID Number );
     ```

     这个方式有两个缺点

     - 你必须记得将该指针数组指向的所有元素删除
     - 因为你需要额外的空间存放指针以及指针指向的对象。

  3. placement new

     为避免过度使用内存，先为此数组分配raw memory，然后使用placement【条款8】在这块内存上构造对象。

     ```c++
     // allocate enough raw memory for an array of 10
     // EquipmentPiece objects; see Item 8 for details on
     // the operator new[] function
     	void * rawMemory =
     		operator new[](10 * sizeof(EquipmentPiece));
     // make bestPieces point to it so it can be treated as an
     // EquipmentPiece array
     	EquipmentPiece *bestPieces =
     	static_cast<EquipmentPiece*>(rawMemory);
     // construct the EquipmentPiece objects in the memory 
     // using "placement new" (see Item 8)
     	for (int i = 0; i < 10; ++i){
     	  new(bestPieces + i) EquipmentPiece(IDNumber);
     	}
     ```

     placement new的缺点是，大部分程序员不熟悉它，且在数组内对象结束生命时，你得以手动的方式调用destructors，还得用delete[]来销毁raw memory。

- 类里缺少了默认构造函数，它们将不适用于许多template-based container classes。对模板而言，被实例化的模板类型必须要有一个default constructor。因为大多数的template内部几乎都是有一个基于类型参数而架构起来的数组。

  ```c++
  template<class T>
  class Array {
   public:
    Array(int size);
    ...
   private:
    T *data;
  };
  template<class T>
  Array<T>::Array(int size) {
    data = new T[size]; // calls T::T() for each element of the array
    ... 
  }
  ```

  通过谨慎设计template，我们可以消除对dctor的要求（vector就可以），但是不能考虑别人都为你设计的很好。

- 最后一个考虑点与virtual base classes【条款E43】有关。如果一个虚基类（virtual base class）没有默认构造函数（default constructor），那么它会给开发者带来很多麻烦。因为虚基类的构造函数参数必须由正在构造的对象的最终派生类提供。因此，如果一个虚基类没有默认构造函数，那么所有从该类派生的类（无论距离多远）都必须知道、理解并提供虚基类构造函数的参数。这样的要求对派生类的作者来说非常不合理。

#### 类里设定了默认构造函数的问题

如果为default constructor 没有足够信息（不符合要求）的对象做完整的初始化，那么这几乎肯定会造成class内的其他成员函数变得复杂。

```c++
class EquipmentPiece {
	public:
	 EquipmentPiece(int IDNumber = UNSPECIFIED);
...
	private:
	 static const int UNSPECIFIED; // magic ID number value
// meaning no ID was
}; // specified
```

现在我们的对象里有一个"无意义值"，而类似检查指针非空，我们现在可能需要在成员函数里检查它是否有意义。并针对结果进行处理，往往会造成时空资源的额外开销。

所以还是一个选择题：如果你确定默认构造函数可以保证对象所有的字段都被正确初始化，上述的成本开销也可以避免。否则，你就得放弃"产生的对象都已完全被初始化"这一声明，得花功夫做检查和处理。

## 操作符 Operators 

可被重载的操作符，它让你定义的类型有着和C++内建类型一样的语法，可以在看似简单的操作符背后放置威力巨大的手段。

但是稍有不慎，便向下沉沦。

- 单自变量constructor及隐式类型转换操作符尤其麻烦，因为它们可以在没有任何外在迹象的情况下被调用。
- 如果你重载了`||` `&&`等操作符后可能会导致各类问题，因为从内建操作符转移到用户定制函数而带来的各种语义的敏感变化，很容易被忽略。
- 许多操作符和其他操作符之间有某种标准关系，重载可能会破坏之。

所以我们需要关注：

- 重载运算符被调用的时机
- 重载运算符被调用的方法
- 重载运算符的行为
- 重载运算符如何与其他操作符产生关系
- 如何夺取重载运算符的控制权

### 条款05：对定制的"类型转换函数"保持警觉。

Item 5: Be wary of user-defined conversion functions. 

C++如C一样，可以进行隐式转换和（可能遗失信息的）转型。对于内建类型我们无能为力，这是语言的一部分，但是对于我们自己写的类型，我们可以通过控制函数来决定是否让编译器拿去做隐式类型转换之用。

两种函数允许编译器执行这样的转换：

- 单自变量constructor

  能以单一自变量成功调用的constructor，可能拥有单一参数，也可能声明中有多个参数，且除了第一参数外都有默认值

- 隐式类型转换操作符

  它的名称比较奇怪：operator+`类型()`,你不能为其指定返回值类型，因为函数名称已经体现了它的返回值类型。

```c++
#include <iostream>
#include<string>
#include <vector>
using namespace std;
class Name { // for names of things
 public:
  Name(const string &s); // converts string to Name
 private:
  string name;
};
Name::Name(const string &s) {
  this->name = s;
}
class Rational { // for rational numbers
 public:
  Rational(int _numerator = 0, // converts int to
		   int _denominator = 1); // Rational
  operator double() const;
 private:
  int numerator;
  int denominator;
};
Rational::Rational(int _numerator, int _denominator) {
  numerator = _numerator;
  denominator = _denominator;
}
Rational::operator double() const {
  return static_cast<double >(numerator) / denominator;
}

int main() {
  Rational r(1, 2); // r has the value 1/2
  double d = 0.5 * r; // converts r to a double, then does multiplication
  cout<<d<<endl;
  return 0;
}
/*
0.25
*/
```

但是呢，这里为你提供的建议是：**最好不要提供任何类型转换函数！**

根本原因在于，在你从未打算也为预期的情况下，此类函数可能会被调用，而结果可能是不正确、不直观的程序行为，也很难调试。

比如我们`cout<<Rational(1,2);`，我们原本期待它输出`1/2`，但是我们忘记写重载`<<`了，而编译器会找到隐式转换，最终输出0.5，而这不是我们期望的。

所以尽量不要提供类型转换函数，类似现在的double转换，我们可以通过提供一个asdouble函数来取代它。

大部分时候，"必须明白调用类型转换函数"虽然带来些许不便，却可因为"不再调用那些并不打算调用的函数"而获得弥补。



相比之下,单自变量constructor却不那么容易去除

```c++
template<class T>
class Array {
public:
    Array(int lowBound, int highBound);
    Array(int size);
    T& operator[](int index);
    ...
};
bool operator==( const Array<int>& lhs, const Array<int>& rhs);
Array<int> a(10);
Array<int> b(10);
...
for (int i = 0; i < 10; ++i)
    if (a == b[i]) { // oops! "a" should be "a[i]"
    	do something for when
    	a[i] and b[i] are equal;
    }
    else {
    	do something for when they’re not;
}
```

因为可以单自变量构造函数,所以利用`Array<int>`,将int转为Array,可以通过编译,但是实际上不是我们预期的代码!

只要不声明隐式类型转换操作符,便可将它所带来的害处避免,但是单自变量constructor却不那么容易去除.因为你可能真的需要一个提供单自变量的constructor.

有两种方法可以避免这个问题:

- 较简单,使用最新的C++特性:explicit.只要将构造函数声明为explicit,编译器就不能因隐式类型转换的需要而调用它们.显式类型转换还是允许的.

- 关于隐式类型转换的合法性,有一条规则,即**没有一个转换程序sequence of conversion可以内含一个以上的用户定制转换行为(即单自变量constructor或隐式类型转换操作符)** 所以我们可以利用这项规则,让你希望的对象构造行为合法化,不希望的隐式构造非法化.

  这里Array里内嵌了一个ArraySize,ArraySize这种类被称为proxy class ,它的每一个对象都是为了其他对象而存在的.Proxy Objects让你得以超越外观形式,进而控制你的软件行为.[条款30]就是一个开始.

  ```c++
  template<class T>
  class Array {
   public:
    class ArraySize { // this class is new
     public:
  	ArraySize(int numElements) : theSize(numElements) {}
  	int size() const { return theSize; }
     private:
  	int theSize;
    };
    Array(int lowBound, int highBound);
    Array(ArraySize size); // note new declaration
    ...
  };
  ```

  本质上就是套一层壳,我觉得这种方式不是很优雅.

总之,允许编译器进行隐式类型转换,害处将多于好处.除非明确好需求,不要使用它.

### 条款06：区别好前置后置的递增递减符

Item 6: Distinguish between prefix and postfix forms of increment and decrement operators. 

为了区分前置和后置运算符,让后置式有一个int自变量,并在被调用时由编译器默默地给这个int置一个0;

```c++
class UPInt { // "unlimited precision int"
public:
    UPInt& operator++(); // prefix ++
    const UPInt operator++(int); // postfix ++
    UPInt& operator--(); // prefix --
    const UPInt operator--(int); // postfix --
    UPInt& operator+=(int); // a += operator for UPInts
    // and ints
    ...
};
UPInt i;
++i; // calls i.operator++();
i++; // calls i.operator++(0);
--i; // calls i.operator--();
i--; // calls i.operator--(0);
```

这样做的还有一个重点,就是**这些操作符的前置会返回一个reference,后置会返回一个const对象.** 

这很好理解,**前置是累加后取出,后置是取出后累加(返回的是原值的拷贝)**.下面是它们的实现.

```c++
// prefix form: increment and fetch
UPInt& UPInt::operator++()
{
    *this += 1; // increment
    return *this; // fetch
}
// postfix form: fetch and increment
const UPInt UPInt::operator++(int)
{
    const UPInt oldValue = *this; // fetch
    ++(*this); // increment
    return oldValue; // return what was
}
```

至于为什么后置返回是const,

1. 因为与内建类型的逻辑统一

   ```c++
   UPInt i;
   i++++; // apply postfix increment twice
   //This is the same as
    
   
   int i;
   i++++; // error!
   ```

   而int型是不会允许的.

2. 与实际逻辑不符

   即使你写成`i++++`,得到的结果也只会使i加1后的值而已,因为第二个operator++改变的是第一个operator++返回的对象.这样的结果是违背直觉的,也容易引起混淆.所以最好禁止将其合法化.

   加了const后,在准备被第二次调用时,因为operator++是个non-const成员函数,所以const对象无法调用.

这里我们还注意到,后置存在拷贝操作,会有构造和析构带来的资源浪费,所以在**处理用户定制类型时,尽量使用前置式.**

另外,我们发现前置后置做了相同的事情,为了确保后置式的行为永远与前置保持一致,我们就可以让后置的实现以前置为基础,如上面的代码演示的一样.代码复用是一种很好的开发技巧,可以帮你降低开发的难度,维护代码的一致性.

### 条款07：永远不要重载`&&`、`||`、`,`操作符

Item 7: Never overload &&, ||, or ,. 

类似C,C++对于真假值表达式,采用的是"骤死式"评估方式.意思是一旦该表达式的真假值确定,即使表达式中还有部分尚未检验,整个评估过程仍告结束.

C++允许你重载`&&`和`||`,但一旦用了这一点,你就是用"函数调用 语义"来取代"骤死式 语义".

```c++
if (expression1 && expression2) ...
looks to compilers like one of these:
if (expression1.operator&&(expression2))  ...// when operator&& is a member function
if (operator&&(expression1, expression2)) ...// when operator&& is a global function
```



函数调用语义与骤死式语义有两大区别

1. 当函数调用动作被执行,所有参数值都必须评估完成.也就不再存在骤死式语义
2. C++语言规范并未规定函数调用动作中各参数的评估顺序,所以无法知道expression1和expression2哪个先被评估.而骤死式总是从左往右评估其自变量.



逗号操作符也与之类似.

逗号操作符用来构成表达式

```c++
for (int i = 0, j = strlen(s)-1;i < j;++i, --j) // aha! the comma operator!
```

表达式如果内含逗号,那么逗号左侧会先被评估,然后再评测逗号右边,最后,整个逗号表达式的结果以逗号右侧的值为代表.

无论你将逗号操作符写成成员函数或是非成员函数,你都不能保证左侧表达式一定比右侧表达式先被评估.所以不要轻易重载逗号运算符.

### 条款08：了解new delete的不同意义

Item 8: Understand the different meanings of new and delete. 

#### 千奇百怪的new

##### `new operator` 和`operator new`.

C++ 常常给我们带来一些困惑(不止一些),譬如`new operator` 和`operator new`.

我们日常使用的new是 new operator.这是一个内建操作符,它总是做两件事:分配足够的内存;在分配的内存上对要构建的对象设定初值.

我们可以改变的是用来容纳对象的那块内存的分配行为,new operator 调用的函数我们可以重写或重载,这个函数就是operator new.

operator new 类似malloc, 唯一的任务就是分配内存,取得分配的内存而将其转为一个对象,是new operator 的责任.

`string *ps = new string("Memory Management");`
实际上等于

```c++
void *memory = operator new (sizeof(string)); // get raw memory for a string  object
call string::string("Memory Management") on *memory; // initialize the object in the memory
string *ps = static_cast<string*>(memory); // make ps point to the new object
```

这里第二部设计调用构造函数,这是程序员无法涉足的,属于编译器的权力.这也是为什么你想要做一个heap-based object,一定要使用new operator的原因,你无法直接调用"对象初始化必需的constructor"(尤其是它可能为vtbl设定初值[条款24])

> `operator new`是C++中的内存分配函数，它负责在堆上分配指定大小的内存块并返回一个指向该内存块的指针。`operator new`函数是一个全局函数，可以在类内部和外部使用。
>
> 而`new operator`是C++中的一个表达式，用于在堆上分配内存并构造对象。它会调用类的构造函数来初始化内存块，并返回一个指向新分配的对象的指针。
>
> 它们的区别在于，`operator new`是一个函数，负责分配指定大小的内存块；而`new operator`是一个表达式，负责在这个内存块上构造对象。在使用`new`表达式时，实际上是先调用`operator new`函数来分配内存，然后再调用类的构造函数来初始化对象。
>
> 在C++中，我们可以重载`operator new`函数来改变内存分配的方式。例如，我们可以实现自己的内存池来提高内存分配的效率。而`new operator`不可以重载，因为它不是一个函数，而是一个表达式。
>
> `operator new`函数的原型如下：
>
> ```
> void* operator new(std::size_t size);
> ```
>
> `new operator`函数的原型如下：
>
> ```
> void* operator new(std::size_t size, void* ptr);
> ```
>
> 需要注意的是，`new operator`函数通常不需要手动调用，而是在使用`new`表达式时自动调用。

##### placement new

有时你会想在一些已经分配好的原始内存上构建对象,那么`placement new`就是来满足这种需求的.

`placement new`是通过使用`new`操作符的另一种形式来实现的，它不会分配新的内存，而是在指定的一块内存上直接构造对象。`placement new`需要传入一个指针作为第一个参数，指向我们要构造对象的内存块，例如：

```cpp
void* mem = malloc(sizeof(MyClass));  // 分配一块内存
MyClass* obj = new (mem) MyClass();  // 在该内存块上构造 MyClass 对象
```

在这个例子中，我们首先使用`malloc`函数分配了一块大小为`sizeof(MyClass)`的内存。然后我们使用`new`操作符的另一种形式来在该内存块上构造一个`MyClass`对象。注意，我们需要将分配的内存块的指针作为第一个参数传递给`new`操作符。

```c++
void* operator new (std::size_t size, void* ptr);
```

其中，第一个参数 `size` 表示需要分配的内存块大小（实际上这个参数在使用 placement new 的时候不需要），第二个参数 `ptr` 是一个指针，表示分配内存的起始地址，即在哪块内存上构造对象。

在使用`placement new`时，我们需要手动管理内存的分配和释放，需要确保在构造对象后，我们正确地释放了内存，例如：

```c++
obj->~MyClass();  // 调用对象的析构函数
free(mem);        // 释放内存
```

在释放内存之前，我们需要先调用对象的析构函数，确保对象的资源被正确地释放。然后我们使用`free`函数释放分配的内存。

总之，`placement new`是一种非常有用的内存分配方式，可以在一些特殊情况下优化内存分配和释放的效率。但是需要注意的是，它需要手动管理内存的分配和释放，使用时需要非常小心，以避免内存泄漏和其他问题。



总结一下就是:

- 如果你想将对象构建在heap,那么就用new operator.它会分配内存还会自动调用构造函数.
- 如果你只打算分配内存,那么就调用operator new,不会有构造函数被调用.
- 如果你打算在heap objects产生时自己决定内存分配方式,自己写一个operator new.
- 如果你打算在已分配并拥有指针的内存中构建对象,使用placement new.

用比喻就是new operator就是买精装修的房.operator new是毛坯,自己写就是自己指定毛坯位置,placement new就是在已经有门牌号(指针)的毛坯房装修.

#### delele

为避免资源泄漏,每一个动态分配内存行为都要有对应的释放动作.

内存释放动作由operator delete执行.

因此delete ps(ps指向string),会让编译器删除下面的代码.

```c++
ps->~string();
operator delete(ps);
```

这里有一个暗示,如果你想处理一块原始的内存,那么就应该直接用operator delete将其还给系统.

如果你使用了placement new，在某个内存地址上手动构造了一个对象，那么你不应该使用delete opeartor,因为使用placement new构造的对象的内存是手动分配的，而不是由`new`操作符分配的，因此使用`delete`释放该内存是不正确的。

你需要手动调用这个对象的析构函数，并在不再需要该内存时释放它。

示例如下：

```c++
// 在指针p指向的内存位置上使用placement new构造了一个对象
T* p = new (address) T(args);

// 调用对象的析构函数 但未释放内存
p->~T();

// 释放内存
operator delete(p);
```

在这个示例中，`address`是你指定的内存地址，`args`是构造函数的参数列表。在使用完这个对象后，我们需要首先手动调用对象的析构函数`p->~T()`，然后再使用`operator delete`释放内存。请注意，我们使用了全局的`operator delete`函数，因为我们手动指定了内存地址，所以无法使用类的成员函数`operator delete`。

需要注意的是，如果你在一个已分配的内存地址上使用了placement new，那么你也需要手动管理该内存，包括手动调用对象的析构函数和手动释放内存。这是因为，使用placement new只是在指定的内存位置上构造了一个对象，但并没有为该对象分配内存，也没有自动管理该内存的生命周期。因此，在使用placement new时，需要格外小心，确保手动管理内存的正确释放。

#### 数组带来的麻烦

数组略有不同,我们需要使用operator new[]来分配内存.operator delete[]来释放内存.`delete[]`函数会依次析构数组中的每个元素，然后释放整个数组内存.

总结一下:

new opeartor 和 delete opeartor都是内建操作符,我们无法控制,但是它们调用的内存分配/释放函数我们可以重载.

## 异常 Exceptions 
### 条款09：利用析构函数避免泄露资源
Item 9: Use destructors to prevent resource leaks. 
### 条款10：在构造函数内阻止资源泄露
Item 10: Prevent resource leaks in constructors. 
### 条款11：禁止异常流出析构函数之外
Item 11: Prevent exceptions from leaving destructors. 
### 条款12：了解"抛出异常"和"传递参数"或"调用虚函数"的区别
Item 12: Understand how throwing an exception differs from passing a parameter or calling a virtual function. 
### 条款13：以传引用方式来捕捉异常
Item 13: Catch exceptions by reference. 
### 条款14：明智运用异常规范
Item 14: Use exception specifications judiciously. 
### 条款15：了解异常处理的成本
Item 15: Understand the costs of exception handling. 

## 效率 Efficiency 
### 条款16：谨记80-20法则
Item 16: Remember the 80-20 rule.
### 条款17：考虑使用缓式评估
Item 17: Consider using lazy evaluation.
### 条款18：分期摊还预期的计算成本
Item 18: Amortize the cost of expected computations. 
### 条款19：了解临时对象的来源
Item 19: Understand the origin of temporary objects. 
### 条款20：协助完成返回值优化RVO1
Item 20: Facilitate the return value optimization. 
### 条款21：利用重载机制来避免类型转换
Item 21: Overload to avoid implicit type conversions. 
### 条款22：考虑以操作符复合形式来取代其独身形式
Item 22: Consider using op= instead of stand-alone op. 
### 条款23：考虑使用其他程序库
Item 23: Consider alternative libraries. 
### 条款24：了解虚函数、多重继承、虚基类和RTTI的成本
Item 24: Understand the costs of virtual functions, multiple inheritance, virtual base classes, and RTTI. 

## 技术 Techniques 
### 条款25：将构造函数和非成员函数虚化
Item 25: Virtualizing constructors and non-member functions. 
### 条款26：限制某个class所能产生的对象数量
Item 26: Limiting the number of objects of a class. 
### 条款27：要求（或禁止）对象产生于heap中
Item 27: Requiring or prohibiting heap-based objects. 
### 条款28：智能指针
Item 28: Smart pointers.
### 条款29：引用计数
Item 29: Reference counting. 
### 条款30：替身/代理类
Item 30: Proxy classes. 
### 条款31：让函数根据一个以上的对象类型来决定如何虚化
Item 31: Making functions virtual with respect to more than one object. 

## 杂项讨论 Miscellany 
### 条款32：在未来时态下发展程序
Item 32: Program in the future tense. 
### 条款33：将非尾端类设计为抽象类
Item 33: Make non-leaf classes abstract. 
### 条款34：理解如何在一个程序中结合C++和C
Item 34: Understand how to combine C++ and C in the same program. 
### 条款35：让自己熟悉标准C++语言
Item 35: Familiarize yourself with the language standard. 