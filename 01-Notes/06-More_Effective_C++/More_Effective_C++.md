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

对于operator[]，这个操作符必须返回某种“能够被当做assignment赋值对象”的东西。即令operator[]返回一个reference。

> 当我们重载operator[]用于访问一个类的成员变量时，通常希望它返回一个引用，而不是一个值，有以下几个原因：
>
> 1. 方便修改：当我们使用引用来访问一个类的成员变量时，可以直接对这个变量进行修改，而不需要使用其他方法来实现。
> 2. 更高效：返回一个引用比返回一个值更高效。当返回一个引用时，函数只需要返回一个指向已经存在的对象的指针，而不需要创建一个新的对象。因此，使用引用可以减少内存分配和复制的开销，提高程序的效率。
> 3. 符合语义：使用引用可以使代码更符合语义。当我们使用operator[]访问一个类的成员变量时，我们通常是想要访问和修改该成员变量，而不是返回一个副本。
>
> 但在某些特定的情况下，返回一个值而不是引用可能更加合适，例如用于表示“如果这个元素不存在，则返回默认值”。

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

  

- dynamic_cast：用来执行继承体系中“安全的向下转型或跨系转型动作”，用于在继承层次结构中进行类型转换。dynamic_cast可以将一个基类指针或引用转换为一个派生类指针或引用，并得知是否成功，如果转型失败，会以null指针（转型对象是指针）或是exception（转型对象是reference）表现出来。它无法应用在缺乏虚函数的类型上（如double）。也无法改变类型的常量性。最常用来转换函数指针类型。



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

但是不是所有对象都如此，有一些类“必须有一些外来信息才能生成对象” 。

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

现在我们的对象里有一个“无意义值”，而类似检查指针非空，我们现在可能需要在成员函数里检查它是否有意义。并针对结果进行处理，往往会造成时空资源的额外开销。

所以还是一个选择题：如果你确定默认构造函数可以保证对象所有的字段都被正确初始化，上述的成本开销也可以避免。否则，你就得放弃“产生的对象都已完全被初始化”这一声明，得花功夫做检查和处理。

## 操作符 Operators 

### 条款05：对定制的”类型转换函数“保持警觉。

Item 5: Be wary of user-defined conversion functions. 

### 条款06：区别好前置后置的递增递减符

Item 6: Distinguish between prefix and postfix forms of increment and decrement operators. 

### 条款07：永远不要重载`&&`、`||`、`,`操作符

Item 7: Never overload &&, ||, or ,. 

### 条款08：了解new delete的不同意义

Item 8: Understand the different meanings of new and delete. 

## 异常 Exceptions 
### 条款09：利用析构函数避免泄露资源
Item 9: Use destructors to prevent resource leaks. 
### 条款10：在构造函数内阻止资源泄露
Item 10: Prevent resource leaks in constructors. 
### 条款11：禁止异常流出析构函数之外
Item 11: Prevent exceptions from leaving destructors. 
### 条款12：了解“抛出异常”和“传递参数”或“调用虚函数”的区别
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