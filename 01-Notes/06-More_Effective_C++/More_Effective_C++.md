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

异常无法被忽略,想要写出exception safe的代码,需要程序员的精心设计.

### 条款09：利用析构函数避免泄露资源
Item 9: Use destructors to prevent resource leaks. 

我们得对那些操控局部性资源的指针说再见.

 下面举个例子说明:

```c++
void processAdoptions(istream& dataSource)
{
    while (dataSource) { // while there’s data
        ALA *pa = readALA(dataSource); // get next animal
        pa->processAdoption(); // process adoption
        delete pa; // delete object that
    } // readALA returned
}
```

如果`pa->processAdoption`抛出异常,后面的语句也就不会被执行,pa也就不会被删除.processAdoption无法捕捉它,这个exception会传播到调用端.所以每当`pa->processAdoption`抛出异常,processAdoption便发生一次资源泄漏.

要想改进也很简单,通过try-catch语句捕捉异常,释放资源即可.

```c++
void processAdoptions(istream& dataSource)
{
  while (dataSource) {
	ALA *pa = readALA(dataSource);
	try {
	  pa->processAdoption();
	}
	catch (...) { // catch all exceptions
	  delete pa; // avoid resource leak when an exception is thrown
	  throw; // propagate exception to caller
	} 
	delete pa; // avoid resource leak when no exception is thrown
  } 
}
```

但以上的写法太臃肿了,如果我们总要删除pa,那么我们可以集中于一处来做这件事,更准确地说,我们将一定要执行的清理代码移到processAdoption函数的某个局部对象的析构函数即可.而这种思路的实现就是以一个类似指针的对象取代pa.说简单些就是智能指针.

本例你可以用auto_ptr来代替pa(虽然auto_ptr在C++11已经被放弃了,书比较旧,凑活看看),用了智能指针,就不必再费心于析构了.

> auto_ptr 已经被从 C++11 标准中移除了。auto_ptr 是一种智能指针，旨在简化 C++ 程序员的内存管理，但它存在一些潜在的危险和限制。
>
> 首先，auto_ptr 不支持所有的指针语义。它采用了所有权转移的语义，这意味着当 auto_ptr 被赋值或销毁时，它所管理的指针会自动被释放。这可能会导致一些问题，例如在调用函数时，如果不小心将 auto_ptr 对象作为参数传递，就可能会导致意外释放指针，从而导致程序崩溃或不可预料的行为。
>
> 其次，auto_ptr 也不支持数组。它只能管理单个对象的指针，如果尝试使用 auto_ptr 来管理动态数组，则可能会导致内存泄漏或者非法内存访问。
>
> 为了解决这些问题，C++11 引入了 unique_ptr 和 shared_ptr 等更为安全和灵活的智能指针类。unique_ptr 支持所有权转移语义，但限制了指针的复制和赋值，从而避免了一些潜在的问题。而 shared_ptr 则使用引用计数的技术，支持多个智能指针共享同一个对象，并提供了自定义删除器和弱引用等高级特性。
>
> 因此，由于存在诸多的问题和限制，auto_ptr 已经被从 C++11 标准中移除，并且不建议在现代 C++ 程序中使用。如果需要使用智能指针，应该使用更为安全和灵活的 unique_ptr 或 shared_ptr 等智能指针类。

```c++
void processAdoptions(istream& dataSource)
{
    while (dataSource) {
    	auto_ptr<ALA> pa(readALA(dataSource));
    	pa->processAdoption();
    }
}
```

总结:将资源封装在对象内,通常就可以在exception出现时避免泄漏资源.

### 条款10：在构造函数内阻止资源泄露
Item 10: Prevent resource leaks in constructors. 

常见的构造函数可能抛出异常的原因包括：内存分配失败、文件读写错误、参数不合法等。但由于我们的constructor抛出异常并未执行完成,所以析构函数无法被用来正确释放资源.

我们可以通过在构造函数里写好很多try-catch来捕捉异常,释放资源,但**更好的处理方式还是利用RAII的智能指针**,来避免异常发生时的资源泄漏等危机.也增加了代码的可读性和健壮性.

### 条款11：禁止异常流出析构函数之外
Item 11: Prevent exceptions from leaving destructors. 

destructor有两种情况下会被调用:

- 对象在正常情况下被销毁,也就是当它离开了它的生存空间scope或是被明确的删除.
- 当对象被exception处理机制——也就是exception传播过程中stack-unwinding(栈展开)机制一一销毁.

在对象的析构函数中抛出异常会导致程序处于不确定的状态，无法正确地执行后续的操作。如果在析构函数中抛出异常，而该异常没有被捕获，则 C++ 编译器会调用 `std::unexpected()` 函数，该函数默认行为是调用 `std::terminate()` 函数，终止程序的运行。

因此，C++ 程序员应该确保在析构函数中不抛出异常，或者在析构函数中捕获并处理异常，以确保程序能够正确地执行并终止。需要注意的是，如果一个对象的析构函数抛出了异常并被捕获，那么程序仍然可以继续执行，但是需要注意对象的析构过程可能没有完全执行完毕，可能会导致资源泄漏等问题。

### 条款12：了解"抛出异常"和"传递参数"或"调用虚函数"的区别
Item 12: Understand how throwing an exception differs from passing a parameter or calling a virtual function. 

#### 抛出异常与传递参数的区别

看似catch异常和函数声明很相似,但是它们也有重大的不同点.

```c++
class Widget { ... }; // some class; it makes no
// difference what it is
void f1(Widget w); // all these functions
void f2(Widget& w); // take parameters of
void f3(const Widget& w); // type Widget, Widget&, or
void f4(Widget *pw); // Widget*
void f5(const Widget *pw);
catch (Widget w) ... // all these catch clauses
catch (Widget& w) ... // catch exceptions of
catch (const Widget& w) ... // type Widget, Widget&, or
catch (Widget *pw) ... /
```

##### 相同点

函数参数和exceptions的传递方式有三种:传值 传引用 传指针.

> 在 C++ 中，参数传递主要有三种方式：传值、传指针和传引用。其中，传值是将实参的值复制给形参，在函数内部使用形参的值进行操作；传指针和传引用都是将实参的地址传递给形参，通过形参操作实参。
>
> - 传址这个概念一般指传指针，因为指针是存储地址的变量。因此，传指针也可以称为传地址。但是，传引用和传指针并不是完全相同的概念。
>
> - 传引用是一种特殊的传址方式，它是通过将实参的别名（引用）传递给形参来进行参数传递的。与传指针不同，传引用不需要使用解引用运算符来访问实参，而且引用本身没有指针那样的地址。因此，传引用的语法更加简洁，使用起来更加方便。
>
> 因此，传址一般指的是传指针的方式，而传引用是一种特殊的传址方式，不同于传指针。在实际编程中，应该根据需要选择不同的参数传递方式，以达到更好的效果。

##### 不同点:

###### 控制权

但是视你传递的是参数或exceptions的不同,会导致控制权的变易:

- 调用函数,控制权会回到调用端(除非函数失败以至于无法返回),

- 但是当你抛出一个exception,控制权不会再回到抛出端,而是会在调用堆栈中查找匹配的异常处理程序，并在那里处理异常。这意味着，如果抛出异常后没有合适的异常处理程序，程序可能会崩溃或终止.

###### 复制

在抛出异常时，异常对象通常会被复制一份并传递给异常处理程序。这是因为异常处理程序需要处理异常对象的副本，以防止在处理期间修改原始异常对象。如果不复制异常对象，异常处理程序可能会修改原始异常对象，从而破坏程序的逻辑和正确性.

当抛出异常时，如果异常对象是在函数内部定义的局部变量或者在某个作用域内创建的临时对象，那么在离开该作用域后，该对象将会被析构并销毁。如果这个异常对象没有被复制，那么在异常处理程序尝试访问该对象时就会导致未定义行为，从而可能导致程序崩溃或出现其他问题。因此，在抛出异常时，必须复制异常对象并传递它的副本，以确保在异常处理程序中能够安全地访问该对象。

此外，为了确保异常对象能够在离开作用域后被正确地销毁，可以使用智能指针等资源管理技术来管理异常对象的生命周期。智能指针可以确保异常对象在不再需要时被及时地销毁，并且可以在异常处理程序中安全地访问该对象。

复制时,其行为视有对象的拷贝构造函数执行,而且相应于对象的静态类型而不是动态类型.[条款25]展现了一种技术(虚构造函数),可以让你以动态类型为本进行复制.

```c++
catch (Widget& w) // catch Widget exceptions
{
... // handle the exception
throw; // rethrow the exception so it
} // continues to propagate
catch (Widget& w) // catch Widget exceptions
{
... // handle the exception
throw w; // propagate a copy of the
} // caught exception
```

一般而言,你需要使用`throw;`才能重新抛出当前的exception,期间你不会改变被传播的exception的类型.而且为exception所做的复制动作,其结果是一个临时变量,如[条款19]所言,这给予编译器进行优化的权利.



###### 传递参数

```c++
catch (Widget w) ... // catch exception by value
catch (Widget& w) ... // catch exception by
// reference
catch (const Widget& w) ... // catch exception by
// reference-to-const
```

这里我们注意到,一个被抛出的(必为临时对象)对象可以简单使用by reference的方式捕捉,不需要by reference-to-const的方式捕捉.函数调用过程中将一个临时对象传递给一个non-const reference参数是不允许的[条款19],但对exceptions则属合法.

`catch (Widget w) `会复制所得参数.也就是说如果之前是`throw w;`,那么就会造成两次复制,造成资源开销.

千万不要抛出一个指向局部对象的指针,因为该局部对象会在exception传离其scope时被销毁而导致虚吊.这就是copy正要避免的地方.

try-catch中不会随意发生类型转换,只有类型匹配的对象才能被捕捉到。

在匹配过程中只有两种转换可以发生：

- 派生类到基类的转换

- 有型指针转为无型指针(`void*`)

  const/volatile限定符的增加(针对`const void*` 设计的catch,可以捕捉让任何指针类型的exception)。

> 需要注意的是，使用`catch (const void* ex)`来捕捉异常对象的方法是不安全的，因为该语句可以捕捉任何指针类型的异常，包括指向无效内存地址的指针，这可能会导致程序崩溃或者产生不可预测的行为。建议在代码中谨慎使用这种捕捉异常的方法。

传递参数和传递异常最后一个不同是catch语句总是按顺序来做匹配尝试.

#### 传递异常与调用虚函数的比较

传递异常是顺序匹配,first-fit,最先吻合策略.所以绝不要将针对base class设计的catch放在derived class设计的catch之前.

调用虚函数是所谓best-fit,最佳吻合策略

#### 总结

把一个对象传递给函数或使用该对象调用虚函数，与将该对象作为异常抛出有三种主要区别。

- 首先，异常对象总是被复制；当按值捕获时，它们甚至会被复制两次。传递给函数参数的对象根本不需要被复制。
- 其次，作为异常抛出的对象受到比传递给函数的对象更少的类型转换形式的限制。
- 最后，catch子句按照它们在源代码中出现的顺序进行检查，并选择可以成功执行的第一个。当使用对象调用虚函数时，选择的函数是提供最佳匹配对象类型的函数，即使它不是源代码中列出的第一个函数。

> 总结:
>
> 1. 抛出异常和传递参数是函数调用时主动发起的，而调用虚函数是通过对象的指针或引用间接地发起的。抛出异常和传递参数都可以在函数调用前或函数调用过程中指定参数的值，而调用虚函数则需要先创建对象，然后通过对象的指针或引用调用虚函数。
> 2. 抛出异常和传递参数是函数调用时向函数传递信息的方式，而调用虚函数是向对象发送消息的方式。抛出异常和传递参数可以用于向函数传递任意类型的数据，而调用虚函数只能用于向对象发送特定的消息，即调用该对象的虚函数。
> 3. 抛出异常和传递参数通常是同步调用，即调用方会等待函数返回或抛出异常后再继续执行。而调用虚函数通常是异步调用，即调用方在调用虚函数后不需要等待对象的响应，而是可以立即执行下一条语句。
>
> 总的来说，抛出异常和传递参数是向函数传递信息的方式，适用于函数和函数之间的交互；而调用虚函数是向对象发送消息的方式，适用于对象和对象之间的交互。



### 条款13：以传引用方式来捕捉异常
Item 13: Catch exceptions by reference. 

写catch子句时,你需要指定异常对象如何被传递过来,你可以选择传值,传指针,传引用.

#### 传指针

理论上,将异常从抛出段搬到捕捉端,必然是个缓慢的过程[条款15],而传指针应该是最有效率的做法,因为不需要复制对象.

但是使用指针需要保证异常对象在离开抛出指针的那个函数之后依然存在.static对象和global对象都没问题,但是程序员很容易忘记这项约束.

另外会存在`throw new exception;`这样在heap上分配资源的语句.那么就带来一个问题.即catch语句不知道是否要删除自己获得指针所指向的资源.这个问题没有回答.因为没法确定到底指针指向的是什么.

此外,catch-by-pointer与语言本身建立起来的惯例有所矛盾:

四个标准的exception(bad_malloc,bad_cast,bad_typeid,bad_exception)统统都是对象,而不是对象指针.所以我们必须用by-value或by-reference的方式捕捉它们.

> 1. `bad_alloc`：当使用 `new` 操作符分配内存失败时抛出，通常表示内存不足或无法分配所需大小的内存。
> 2. `bad_cast`：在使用 C++ 类型转换时，如果转换失败则抛出该异常。例如，当试图将一个基类对象转换为其派生类对象时，如果对象实际上不是该派生类的实例，则会抛出 `bad_cast` 异常。
> 3. `bad_typeid`：在使用 C++ 运行时类型识别 (RTTI) 功能时，如果 `typeid` 运算符作用于一个空指针或者一个不包含多态类的对象，则会抛出 `bad_typeid` 异常。
> 4. `bad_exception`：在使用 C++ 异常机制时，如果出现不允许的异常类型或未捕获的异常，则会抛出 `bad_exception` 异常。

#### 传值

catch-by-value固然可以消除上述exception是否要删除以及与标准exception不一致等问题,但这种方式每当exception对象被抛出就会被复制两次,而且也会导致切割问题(子类被基类的异常捕捉到,会失去其派生成分.析构时也会用base的析构函数,导致派生类资源无法正确释放).

#### 传引用

传引用避免了上述提到的所有问题,不会类似传指针导致空悬,也容易捕捉标准异常;不类似传值,不会有切割问题,每次也只会复制一次.



所以用catch by reference!

### 条款14：明智运用异常规范(已经过时)
Item 14: Use exception specifications judiciously. 

异常规范明确指出一个函数可以抛出什么样的exception.如果函数抛出一个违背列于exception specification 的exception,这个错误在运行期会被检验出来,于是特殊函数unexpected会被自动调用,所以说exception specification不但是一种文档式的辅助,也是一种实践式的机制,用来规范exception的运用.

但是unexpected的默认行为是terminate,terminate的默认函数是调用abort.所以程序如果违反异常规范,默认结果就是程序被中止,没机会指向此类清理工作.

但是，在 C++11 标准中，已经移除了 dynamic exception specification，也就是使用 `throw(type1, type2, ...)` 的方式指定函数可能抛出的异常。因为 dynamic exception specification 会导致代码变得复杂和不可移植，同时也无法完全确保程序的正确性。因此，在 C++11 及以后的标准中，不应该使用 dynamic exception specification。

另外，您提到了 `unexpected` 函数，这是在早期的 C++ 标准中提供的一个函数，用于处理因未处理的异常而导致程序终止的情况。当程序运行时遇到未处理的异常时，如果没有提供专门的异常处理代码来处理该异常，就会自动调用 `unexpected` 函数。默认情况下，`unexpected` 函数会调用 `std::terminate` 函数，从而导致程序终止。

需要注意的是，在 C++11 及以后的标准中，`unexpected` 函数已经被废弃，取而代之的是 `std::unexpected_handler` 类型和 `std::set_unexpected` 函数。这些新的异常处理机制提供了更加灵活和可靠的方式来处理未处理的异常。

### 条款15：了解异常处理的成本
Item 15: Understand the costs of exception handling. 

为了能够在运行时期处理exceptions,程序必须做大量簿记工作.exception的处理需要成本.

你可以选择放弃使用异常处理,但前提你知道自己的程序不能任何一处使用try,throw,catch,而且你所链接的程序库也没有一个使用到这些.这样编译器会做某些性能优化.

try语句一般会带来5%-10%的代码膨胀和执行速度下降.为了将此成本最小化,避免非必要的try语句.

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