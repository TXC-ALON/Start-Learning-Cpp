# Object-Oriented Programming

[TOC]

OOP三大特性：封装、继承、多态性

## 二、面向对象

​	台湾翻译：对象导向

### 	对象

​	Object==Entity

​	程序语言中对象就是变量

​	**对象是属性+服务**	Attributes+Services	Data+Operations

​	\****封装**\**

​	对象的建立就是通过对问题的分析建立映射

### 	C++ Class 类

​	Public							Private

​	a.print 通过点号来调用函数

## 三、面向对象基本原理

### 面向对象AOT

- A way to organize
  - Designs
  - Implement
- Objects
- To focus on things , not operations

### Message的行为过程

- Messages are
  - Composed by sender			发信者发令
  - Interpreted by the receiver    接受者自决
  - Implemented by methods      方法来实施

### Object  --  Class

Class将Object归类总结，是某种概念

Object 表达某一种实体

### OOP Characteristics 面向对象五原则

1. Everything is an object.
2. A program is a bunch of objects telling each other **what to do** by sending messages.
3. Each object has its own memory made up of other objects.
4. Every object has a type.
5. All objects of a paricular type can receive the same messages.

### Interface 接口--可拆换--低耦合

​	Communication

​	Protection

### The Hidden Implementation

Class creators  VS  Client programmers

Class creators 封装程序，提供接口

程序员将他们Encapsulation（有机组合）

很像mc，设计者给方块，玩家造世界

<font color='#0F9D58'>（0420）</font>

## 四、自动售票机的例子

### TicketMachine.h

```cpp
class TicketMachine {
public:
    TicketMachine();
    virtual ~TicketMachine();
    void ShowPrompt();
    void insertMoney(int money);
    void showBalance();
    void printTicket();
    void showTotal();
    void printError();
private:
    const int PRICE;
    int balance=0;
    int total=0;
};
```

### TicketMachine.cpp

```cpp
#include <iostream>
#include "TicketMachine.h"


using namespace std;

TicketMachine::TicketMachine() : PRICE(0) {

}
TicketMachine::~TicketMachine()  {

}
void TicketMachine::ShowPrompt() {
    cout << "something" << endl;
}
void TicketMachine::insertMoney(int money) {
    balance += money;
}
void TicketMachine::showBalance() {
    cout << balance << endl;
}

```

### main.cpp

``` cpp
#include<iostream>
#include"TicketMachine.h"

int main() {
	TicketMachine tm;
	tm.insertMoney(100);
	tm.showBalance();
}
```

### :star:::resolver解析符

- <Class Name>::<function name>
- ::<function>        递归调用自己
- ::a                            全局变量a

## 五、头文件

### 声明

通过分离的.h(声明、原型 declaration、prototypes)，.cpp(定义 definition)	来声明一个类

**Header = Interface   类似于某种合同、约定**

头文件在编译预处理期间编入

```shell
g++ a.cpp --save-temps -Wall(输出所有可能的warning)

ls
a.cpp
a.h
a.ii 	//预处理后结果
a.s		//汇编代码
a.o		//目标代码
a.out 	//输出
```

### Declaration vs. Definitions

- A .cpp file is a compile unit
- only declarations are allowed to be in .h
  - extern varibles
  - function prototypes
  - class/struct declastion

### 头文件位置

#include "xx.h" 在当前目录找

#include <xx.h> 在系统目录找

#include <xx>  :same as  #include <xx.h> 



```shell
g++ a.cpp --save-temps -c -D_MY_H_(表示所有文件都有MY_H)
```

###  避免class重复调用，使用标准头文件结构

Class被头文件调用，不能重复出现，声明可以

所以使用标准头文件结构

```c++
#ifndef HEADER_FLAG
#define HEADER_FLAG
// declaration
#endif
```

## 六、时钟的例子

ClockDisplay->NumberDisplay

使用类需要提供良好的接口，来判断bool值

## 七、本地变量

只存在于method内

若本地变量与某个成员变量重名，根据最近覆盖原则，有效的是本地变量



Fields：成员变量	构造在所有methods之外，对象在，它就在	作用域是类的作用域 ，被调用才有效。

parameters：函数参数

local variables：本地变量	函数内部

*parameters和 local variables 本质上是一样的   存储放在栈里面*



## 八、:star:成员变量的秘密(this)

声明：即我不知道它在哪，但是知道有这么个东西

extern int globe 	知道有这么一个全局变量，但是不知道他在哪里。

定义：使得编译器知道它在哪



字段告诉编译器有这么一个成员变量

成员变量存在于class scope ，在整个类里可以访问。

类是虚的、

```cpp
#include<iostream>
using namespace std;
extern int gl = 5;
class A {
public:
	int i;
	void f();
};
struct B {
	int i;
};
void A::f() {
	cout << i << endl;
	i = 20 + gl;
	cout << i  << endl;
}
void f(struct B* p) {
	p->i = 78;
	cout << p->i << endl;
}
int main() {
	A a;
	A aa;
	B b;
	a.i = 8;
	a.f();
	aa.i = 100;
	aa.f();
	f(&b);
}
```

函数是属于类的，不是对象的特指   		在C里面实现就相当于f(&a)

每个对象的变量是对象的

```C++
#include<iostream>
#include<stdio.h>
using namespace std;
extern int gl = 5;
class A {
public:
	int i;
	void f();
};
struct B {
	int i;
};
void A::f() {
	i = 20 + gl;
	printf("A::f()--&i = %p\n", &i);
    printf("this = %p\n", this);
}
void f(struct B* p) {
	p->i = 78;
	cout << p->i << endl;
}
int main() {
	A a;
	A aa;
	B b;
	a.i = 8;
	printf("&a = %p\n", &a);
	printf("&a.i = %p\n", &a.i);
	a.f();
	aa.i = 100;
	printf("&aa = %p\n", &aa);
	printf("&aa.i = %p\n", &aa.i);
	aa.f();
	f(&b);
}


/*
&a = 00B3F6E8
&a.i = 00B3F6E8
A::f()--&i = 00B3F6E8
this = 00B3F6E8
&aa = 00B3F6DC
&aa.i = 00B3F6DC
A::f()--&i = 00B3F6DC
this = 00B3F6DC
可以看到对象的成员和对象本身的地址是和this指针一样的
*/
```

this:	the hidden parameter

this 是C++ 中的一个关键字，也是一个const 指针，它指向当前对象，通过它可以访问当前对象的所有成员。

<font color='#0F9D58'>（0421）</font>

## 九、构造和析构

java 初始化会置零，而C++不会这样做，将内存管理交给程序员。

0xCC0xCC-----烫

### 构造函数

- 与类同名

- 没有返回类型
- 可以加参数

```cpp
#include<iostream>
#include<stdio.h>
using namespace std;
extern int gl = 5;
class A {
public:
	int i;
	A();
	void f();
};
A::A() {
	i = 0;
	printf("A::A()--this = %p\n", this);
}
struct B {
	int i;
};
void A::f() {
	i = 20 + gl;
	printf("A::f()--&i = %p\n", &i);
	printf("this = %p\n", &i);
}
void f(struct B* p) {
	p->i = 78;
	cout << p->i << endl;
}
int main() {
	A a;
	A aa;
	B b;
	a.i = 8;
	printf("************\n");
	printf("&a = %p\n", &a);
	printf("&a.i = %p\n", &a.i);
	a.f();
	aa.i = 100;
	printf("&aa = %p\n", &aa);
	printf("&aa.i = %p\n", &aa.i);
	aa.f();
	f(&b);
}
```

### 析构函数

在对象离开scope时调用

- 没有返回类型
- 没有参数

```c++
#include<iostream>
using namespace std;

class Tree {
	int height;
public:
	Tree(int initialHeight);
	~Tree();
	void grow(int years);
	void printsize();
};
Tree::Tree(int initialHeight) {
	Tree::height = initialHeight;
	cout << "inside Tree::Tree()" << endl;
}
Tree::~Tree(){
	cout << "******" << endl;
	cout << "inside Tree destrutor" << endl;
	printsize();
	cout << "******" << endl;
}
void Tree::grow(int years) {
	Tree::height += years;
}
void Tree::printsize() {
	cout << "Tree height is " << Tree::height << endl;
}

int main() {
	cout << "before opening brace" << endl;
	{
		Tree t(12);
		cout << "after tree creation" << endl;
		t.printsize();
		t.grow(4);
		t.printsize();
		cout << "before closing brace" << endl;
	}
	cout << "after closing brace" << endl;
}

/*
before opening brace
inside Tree::Tree()
after tree creation
Tree height is 12
Tree height is 16
before closing brace
调用析构函数
******
inside Tree destrutor
Tree height is 16
******
after closing brace
*/
```



## 十、对象初始化

编译器会在大括号开始时分配所有变量空间

构造器会在变量定义的地方开始分配

慎用goto

```cpp
struct X{int i;float f;char c;};
X x[3] = {{1,1.1,'a'},{2,2.2,'b'}};

Y y1[] = {Y(1),Y(2),Y(3)};
```

### The default constructor

是一种没有参数的构造函数

**注意，开数组类的时候，构造函数要注意填满**



## 十一、New & Delete--动态内存分配

### Operator 运算符

类似C里面的malloc & free

new 的结果是地址，分配空间的地址

### delete&delete[]	  

new带[]，delete也带[],告诉程序那里有很多对象，如果没有的话，空间还会回收，但析构函数只会析构第一个

```cpp
int *psome new int [10];
delete [] psome;
```

### Tips

- delete要有东西可删，不可以删空，也不可重复删除
- 当使用new[]，需要用delete[]来配合
- 当new一个单独的entity，使用没有[]的delete
- delete空指针是安全的

```c++
#include<iostream>
using namespace std;

class A {
private:
	int i;
public:
	A() {i = 0;cout << "A::A()" << endl;}
	~A(){cout << "A::~A(),i= " <<i<< endl;}
public:
	void set(int i) { this->i = i; }
	void f() { cout << "hello"; }
};
int main()
{
	A* p = new A[10];
	for (int i = 0; i < 10; i++) {
		p[i].set(i);
	}
	delete [] p;
	return 0;
}
/*
A::A()
A::A()
A::A()
A::A()
A::A()
A::A()
A::A()
A::A()
A::A()
A::A()
A::~A(),i= 9
A::~A(),i= 8
A::~A(),i= 7
A::~A(),i= 6
A::~A(),i= 5
A::~A(),i= 4
A::~A(),i= 3
A::~A(),i= 2
A::~A(),i= 1
A::~A(),i= 0
反向析构，应该是和存储方式是栈有关  
*/
```

## 十二、访问限制

对象应该是封装起来的，外界触摸到的应该只是函数。

### :star::star:public/private/protected/friend的具体区别

在说明这四个关键字之前，就class之间的关系做一个简单的定义，对于继承自己的class，base class可以认为他们都是自己的子女，而对于和自己一个目录下的classes，认为都是自己的朋友。

1. public：public表明该数据成员、成员函数是对所有用户开放的，所有用户都可以直接进行调用

2. private：private表示私有，私有的意思就是除了class自己之外，任何人都不可以直接使用，私有财产神圣不可侵犯嘛，即便是子女，朋友，都不可以使用。

   ​	:star:**private是对类来说的，而不是对对象**，

   ​	**private的检查仅仅在编译时刻，在运行时也有可能让你进入别的内存。**

   ​	**C++的OOP仅存在于编译，他生成的.o和c、汇编生成的一样。**

3. protected：protected对于子女、朋友来说，就是public的，可以自由使用，没有任何限制，而对于其他的外部class，protected就变成private。

4. friend: 类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数(没有this指针)。

| 作用域    | 当前类             | 同一package        | 子孙类             | 其他package        |
| --------- | ------------------ | ------------------ | ------------------ | ------------------ |
| public    | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| protected | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :x:                |
| friend    | :heavy_check_mark: | :heavy_check_mark: | :x:                | :x:                |
| private   | :heavy_check_mark: | :x:                | :x:                | :x:                |

注:同一文件下默认friendly，class默认private，struct默认public

但这不意味着private里的东西完全无法碰触。

```c++
#include<iostream>
using namespace std;

class A {
private:
	int i;
	int* p;
public:
	A() { p = 0; cout << "建A::A()" << endl; }
	~A() { if (p) delete p; cout << "拆A::~A()" << i << endl; }
	void set(int ii) { i = ii; }
	void f() { p = new int; }
	void g(A* q) { cout <<"A::g(),q->i=" << q->i << endl; }
    //通过public一个g，调用A里的i
};

int main() {
	A* p = new A[10];
	for (int i = 0; i < 10; i++) {
		p[i].set(i);
	}
	A b;
	b.set(100);
	p[0].g(&b);
	delete[] p;
	return 0;
}

/*
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
建A::A()
A::g(),q->i=100
拆A::~A()9
拆A::~A()8
拆A::~A()7
拆A::~A()6
拆A::~A()5
拆A::~A()4
拆A::~A()3
拆A::~A()2
拆A::~A()1
拆A::~A()0
拆A::~A()100
*/
```

## 十三、构造函数初始化列表

A():p(0) 通过括号给出初始值。

初始化不同于赋值（赋值有两步，初始化只是一步）

这个初始化会早于构造函数执行

```c++
#include<iostream>
using namespace std;
class B {
public:
	B(int k) { cout << "B::b,b = " << k << endl; };
	B() {};//加了这一行才不会报错
};
class A {
private:
	int i;
	int* p;
	B b;
public:
	A() :p(0) { b = 0; cout << "建A::A()" << endl; }
	~A() { if (p) delete p; cout << "拆A::~A()" << i << endl; }
	void set(int ii) { i = ii; }
	void f() { p = new int; }
	void g(A* q) { cout << "A::g(),q->i=" << q->i << endl; }
	//通过public一个g，调用A里的i
};

int main() {
	A* p = new A[10];
	for (int i = 0; i < 10; i++) {
		p[i].set(i);
	}
	A b;
	b.set(100);
	p[0].g(&b);
	delete[] p;
	return 0;
}
```

### :red_circle:建议日后都用初始化来赋初值



## 十四、对象组合

OOP：封装继承多态性

继承：代码重用



Composition 组合，通过已有的对象组合出新的对象。

- Fully ： 别的对象就是我这个对象里的一部分								心脏

- By reference： 我可以调用别的对象，但它不是我的一部分	   书包 

注：这里有一个问题，就是你调用的对象里的构造函数里的数据，应该有他们自己来搞，所以就得用初始化的方式来调用

```cpp
SavingsAccout::SavingsAccount (const char* name,const char* address,int cents) ; m_saver(name,address),b_balance(0,cents){}//初始化

void SavingsAccount::print(){
    m_saver.print();
    m_balance.print();//还是使用它本身的函数，不破坏对象的边界
}
```

当然也可以将他们设置为public，account.m_saver.set_name("Fred");

但是这不符合OOP的编程思想。

<font color='#0F9D58'>（0424）</font>

## 十五、对象继承

继承  **Inheritance** 	：取已有的类，在此基础上做些改造，做个新的类。

共享原先类的function 、 data ...

B继承A，A是B的基类base/超类super/父类parent，B是A的附生类Derived/副类sub/子类child

B对A进行扩充，B是A的superset

 ```c++
 #include<iostream>
 using namespace std;
 class A {
 public://所有人都能看到
 	A() { cout << "A::A()" << endl; }
 	~A() { cout << "A::~A()" << endl; }
 	void print() { cout << "A::print: " << i << endl; }
 protected://照顾儿子，特殊通道来访问private里的东西
 	void set(int ii) { i = ii; }
 private://所有数据都建议为private
 	int i;
 };
 
 class B :public A {//B是A的子类
 public:
 	void f() { 
 		set(20);
 		//不可访问i = 0;
 		print(); }
 }; 
 
 int main() {
 	B b;
 	//protected 话 b.set(50);就用不了 了
 	b.print();
 	b.f();
 	return 0;
 }
 ```



## 十六、子类父类关系

​	inline 内联

​	**overload 重载函数**：函数名相同，参数不同，编译器会根据你函数的声明进行判断

1. 构造子类时候，父类的构造函数先被调用
2. 如果没有给父类赋值，那么父类按照默认初始化
3. 析构函数是按照反顺序来的

### 	:red_circle:父类的调用也放在初始化的位置

```c++
#include<iostream>
using namespace std;
class A {
public://所有人都能看到
	A(int ii):i(ii) { cout << "A::A()" << endl; }
	~A() { cout << "A::~A()" << endl; }
	void print(int a) { cout << "A::print() " << a << endl; }
	void set(int ii) { i = ii; }
private://所有数据都建议为private
	int i;
};

class B :public A {//B是A的子类
public:
	B() : A(15) { cout << "B::B()" << endl; }
	~B() { cout << "B::~B()" << endl; }
	void print() { cout << "B::print()" << endl; }
	void f() { 
		set(20);
		//不可访问i = 0;
		print(); 
	}
}; 

int main() {
	B b;
	//protected 话 b.set(50);就用不了 了
	b.set(10);
	b.print();
	b.print(35);//这里报错了，覆盖了。namehiding
	return 0;
}
/*
A::A()
B::B()
A::print: 10
B::~B()
A::~A()
*/
```



### namehiding 

父类子类出现重载函数，父类的函数被隐藏，只有子类的函数。

只有C++这样做。

而且这两个同名函数完全没关系。这和别的OOP语言也不一样。



## 十七、函数重载与默认参数

重载声明是指一个与之前已经在该作用域内声明过的函数或方法具有相同名称的声明，但是它们的参数列表和定义（实现）不相同。

默认参数一定要是从右往左写

```c++
int wrong(int n,int m=5,int j); // 这样写是不对的
```

**注：这个默认参数是写在.h里面（函数原型），在.cpp里面不能复写**

编译器辨认default argument

翁帆老师建议：不要使用default argument；不易读，不安全（别人可以改）

<font color='#0F9D58'>（0426）</font>

## 十八、内联函数



调用函数：

1. push parameters 推参数
2. push return address 推返回地址
3. prepare return values 准备返回值
4. pop all pushed 清栈

```c++
//int f(int i) {
00C41A50  push        ebp  
00C41A51  mov         ebp,esp  
00C41A53  sub         esp,0C0h  
00C41A59  push        ebx  
00C41A5A  push        esi  
00C41A5B  push        edi  
00C41A5C  mov         edi,ebp  
00C41A5E  xor         ecx,ecx  
00C41A60  mov         eax,0CCCCCCCCh  
00C41A65  rep stos    dword ptr es:[edi]  
00C41A67  mov         ecx,offset _17C591A2_main@cpp (0C4F029h)  
00C41A6C  call        @__CheckForDebuggerJustMyCode@4 (0C413C0h)  //return i * 2;
00C41A71  mov         eax,dword ptr [i]  
00C41A74  shl         eax,1  
}
//int a = 4;
00C41AD5  mov         dword ptr [a],4  
//int b = f(a);
00C41ADC  mov         eax,dword ptr [a]  
00C41ADF  push        eax  
00C41AE0  call        f (0C412D0h)  //00C412D0  jmp         f (0C41A50h) 
00C41AE5  add         esp,4  
00C41AE8  mov         dword ptr [b],eax  

```



### inline 内联

在 c/c++ 中，为了解决一些频繁调用的小函数大量消耗栈空间（栈内存）的问题，特别的引入了 **inline** 修饰符，表示为内联函数

当我们调用inline函数，会将lnline函数嵌入调用的位置（直接嵌汇编代码，而不是push，jump什么的调用），同时保持自己空间的独立性。

```c++
//inline int f(int i) {
00221A50  push        ebp  
00221A51  mov         ebp,esp  
00221A53  sub         esp,0C0h  
00221A59  push        ebx  
00221A5A  push        esi  
00221A5B  push        edi  
00221A5C  mov         edi,ebp  
00221A5E  xor         ecx,ecx  
00221A60  mov         eax,0CCCCCCCCh  
00221A65  rep stos    dword ptr es:[edi]  
00221A67  mov         ecx,offset _17C591A2_main@cpp (022F029h)  
00221A6C  call        @__CheckForDebuggerJustMyCode@4 (02213C0h)  
//return i * 2;
00221A71  mov         eax,dword ptr [i]  
00221A74  shl         eax,1  
}	
//int a = 4;
00221AD5  mov         dword ptr [a],4  
	//int b = f(a);
00221ADC  mov         eax,dword ptr [a]  
00221ADF  push        eax  
00221AE0  call        f (02212D0h)  //  002212D0  jmp         f (0221A50h)  
00221AE5  add         esp,4  
00221AE8  mov         dword ptr [b],eax 
```

我这里反汇编的结果不如翁老师的。

哪天有空直接gcc -o试试

**inline** 的使用是有所限制的，inline 只适合涵数体内代码简单的涵数使用，不能包含复杂的结构控制语句例如 while、switch，并且**内联函数本身不能是直接递归函数**（即，自己内部还调用自己的函数）。

**inline** 函数仅仅是一个对编译器的建议，所以最后能否真正内联，看编译器的意思，它如果认为函数不复杂，能在调用点展开，就会真正内联，并不是说声明了内联就会内联，声明内联只是一个建议而已。

### inline 在.h和.cpp都要出现。

其次，因为内联函数要在调用点展开，所以**编译器必须随处可见内联函数的定义**，要不然就成了非内联函数的调用了。所以，这要求每个调用了内联函数的文件都出现了该**内联函数的定义**。

因此，将**内联函数的定义**放在**头文件**里实现是合适的，省却你为每个文件实现一次的麻烦。

**定义**在类中的**成员函数**默认都是**内联的**，如果在类定义时就在类内给出函数定义，那当然最好。如果在类中未给出成员函数定义，而又想内联该函数的话，那在类外要加上 **inline**，否则就认为不是内联的。

### inline建议把函数的body也放在头文件里面。

比c里面的宏要好，作为函数可以类型检查。 

#### 建议写法：

这样保持class比较干净

```cpp
class Rectangle{
    int width,height;
    public:
    Rectangle(int w=0,int h =0);
    int getWidth() const;
    void setWidth(int w);
    int getHeight() const;
    void setHeight(int h);
};
inline Rectangle::Rectangle(int w ,int h)
    :width(w),height(h){}
inline int Rectangle::getWidth() const{
    return width;
}
...
```



## 十九、const

初始化之后不能被修改

注：const依然是变量，遵循scoping rules（进函数存在出函数消亡）

extern const int bufsize；声明，不可变量。

### const与指针的问题

```cpp
char * const q = "abc";		//q is const
// *q = 'c';    OK
//	q++;		   ERROR
const char *p = "ABCD";		//*p is const
//	*p = 'b';	ERROR
//	p++			OK
//不能通过p去修改内存单元

//作形象比喻的话，q就像是固定位置的任意门，开门去的地方随意，门不能动
//p就像身上带的传送点，你可以跑到很多地方，但是传送终点还是老家
```

具体谁是const看它在*前面还是后面。



```cpp
#include<iostream>
using namespace std;

int main() {
    char* s = "hello world";
    cout << s << endl;
    s[0] = 'B';
    cout << s << endl;

    return 0;
}
//会报错
/*
s是个指针，指向一段内存
数据放在三种地方
	本地变量-栈
	new-堆
	全局变量-全局数据区
		常量-代码段里面
MMU 内存保护                            
*/

#include<iostream>
using namespace std;

int main() {
    char s[] = "hello world";
    cout << s << endl;
    s[0] = 'B';
    cout << s << endl;

    return 0;
}

//s[]是开了一个数组堆栈
//注意，这里的=，实际上是拷贝

#include<iostream>
using namespace std;

int main() {
    const char* s1 = "hello world";
    char s2[] = "hello world";
    printf("main = %p\n", main);
    printf("s1 = %p\n", s1);
    printf("s2 = %p\n", s2);
    return 0;
}
/*
main = 005E1375
s1 = 005E9B3C	这在代码区
s2 = 00AFFC1C	这里是在堆栈区
*/

```

### 传递const指针来代替传对象

对于对象而言，传整个对象耗费太大资源了，最好是传指针，但是传地址会让人担心地址被误用。所以我们应该传一个const 指针。

### const 对象

对象里的值不能被修改



### c++ 函数前面和后面 使用const 的作用：

前面使用const 表示返回值为const

后面加 const表示函数不可以修改class的成员 （原型，定义都要加）



## 二十、不可修改的变量

### 函数后面加const ， 实际上也就是const A*，改变了参数表

```c++
#include<iostream>
using namespace std;
class A {
    int i;
public:
    A() : i(0){}
    void f() { cout << "f()" << endl; }//void f(A* this)
    void f() const { cout << "f() const" << endl; }//void f(const A* this)
};
int main() {
    const A a;
    a.f();
    A b;
    b.f();
    return 0;
}

```

### 成员变量是const

要在初始化时候赋值



### 不能用const变量做数组大小

除非

1. Make the const value static

   ```c++
   static const int size =  100;
   int a[size];
   ```

   static indicates only one per class (not one per object)

2. use anonymous enum

   ```cpp
   calss Hasarray{
       enum {size = 100};
       int array[size]; //ok
   }
   ```

   

## 二十一、引用

c++ 复杂在提供了太多的内存模型

或者说c++提供了太多的可以放对象的地方（栈、堆、全局数据），提供了太多了访问对象的方式（对象调用，指针，引用） 3*3 = 9

### **Reference** 

​	**declares a new name for an existing object**

引用一般在定义时需要初始化，它的初始值一般是变量或者可以做左值的东西

参数表和成员变量可以不初始化（参数表在调函数初始化，成员变量在构造函数初始化）

```c++
const int&z = x; //z是x的别名，但是你不能通过z来修改x，z不能做左值
const int*p = x；//类似
```

reference 绑定的对象必须有有名字的地址

```c++
#include<iostream>
using namespace std;
int* f(int* x) {
    (*x)++;
    return x;
}
int& g(int& x) {
    x++;
    return x;
}
int x=1;
int& h() {
    int q;
    return x;
}
int main() {
    int a = 0; 
    cout << *f(&a) << endl;//Ugly but explicit
    cout << g(a) << endl;// Clean but hidden
    h() = 16;//引用可以做左值，返回return，reference直接赋值给x
    cout << x << endl;
    return 0;
}

```

### :star:reference 与pointer对比

| References                                                   | Pointers                                   |
| ------------------------------------------------------------ | ------------------------------------------ |
| can't be null                                                | can be set to null                         |
| are deppendent on an existing variable,they are an alias for an variable | pointer is independent of existing objects |
| can't change to a new "address" location                     | can change to point to a different address |

**一言以蔽之，reference是绑定在变量上的**

而实际上，reference是用const pointer来实现的

BS当年创reference为了少看到些*

- 没有references to reference
- 没有pointers to reference          int &* p    不可行，否则可以取到reference的地址
  - 有 reference to pointer       void f（int*& p）;
- 没有引用的数组                reference没有实体，自然没有数组

```c++
#include<iostream>
using namespace std;
int* f(int* x) {
    (*x)++;
    return x;
}
int& g(int& x) {
    x++;
    return x;
}
int x=1;
int& h() {
    int q;
    return x;
}
int main() {
    int x = 8;
    int y = 100;
    int& a = x;
    int& b = y;
    
    cout << x << " " << y << endl;
    a = b; //相当于x=y;
    cout << a << " " << b << endl;
    return 0;
}
/*
8 100
100 100
*/
```

<font color='#0F9D58'>（0427）</font>

## 二十二、向上造型 

### Upcast

把子类当做父类看

Public 继承有暗指代替的意思：

​	如果B 是 A的子  类, A 能用的地方B都可以用。

把子类的对象当做父类来看待，那么多出来的东西不看就是喽。

```c++
#include<iostream>
using namespace std;
class A {
public:
	int i;
public:
	A() :i(10) {}
};
class B : public A {
private:
	int j;
public:
	B() :j(30) {}
	void f() { cout << "B.j = " <<j<< endl; }
};
int main() {
	A a;
	B b ;
	cout << a.i << " " << b.i << endl;
	cout << sizeof(a) << " " << sizeof(b) << endl;
	int* p = (int*)&a;
	cout << p << " " << *p << endl;
	*p = 20;
	cout << a.i << " " << b.i << endl;
	p = (int*)&b;
	cout << p << " " << *p << endl;
	p++;
	*p = 50;
	b.f();
	return 0;
}
/*
10 10
4 8  B里面没有函数，只有成员变量
007AF8EC 10
20 10
007AF8DC 10
B.j = 50 通过指针，访问到了B的private值
*/
```

注：<font color='#4285F4'>Upcast是安全的，downcast是有风险的</font>

原本c++把这叫做类型转换，但是与传统意义上的转换不同，当你的double转为int，实际上double就不存在了，数据有所丢失。



现在叫做向上造型，只是我们看待对象的眼光不一样了，数据并没有丢失。

## 二十三、多态性

### Polymorphism

简单地概括为“一个接口，多种方法”

C++支持两种多态性：编译时多态性，运行时多态性。

1. 编译时多态性（静态多态）：通过重载函数实现：先期联编 early binding
2. 运行时多态性（动态多态）：通过虚函数实现 ：滞后联编 late binding

#### Polymorphism 的实现

* **Upcast**：用子类当父类
* **Dynamic binding**：动态绑定
  * Binding：which function to be called
    * Static binding：call the function as the code
    * Dynamic binding: call the function of the project 运行时才知道该怎么绑，根据指针所指对象决定

https://zhuanlan.zhihu.com/p/37340242

C++运行时多态性是通过虚函数来实现的，虚函数允许子类重新定义成员函数，而子类重新定义父类的做法称为覆盖(Override)，或者称为重写。

多态与非多态的实质区别就是函数地址是早绑定还是晚绑定。如果函数的调用，在编译器编译期间就可以确定函数的调用地址，并生产代码，是静态的，就是说地址是早绑定的。而如果函数调用的地址不能在编译器期间确定，需要在运行时才确定，这就属于晚绑定。

多态的目的：封装可以使得代码模块化，继承可以扩展已存在的代码，他们的目的都是为了代码重用。而多态的目的则是为了“接口重用”。也即，不论传递过来的究竟是类的哪个对象，函数都能够通过同一个接口调用到适应各自对象的实现方法。

多态最常见的用法就是声明基类类型的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，可以根据指向的子类的不同而实现不同的方法。如果没有使用虚函数的话，即没有利用C++多态性，则利用基类指针调用相应的函数的时候，将总被限制在基类函数本身，而无法调用到子类中被重写过的函数。因为没有多态性，函数调用的地址将是固定的，因此将始终调用到同一个函数，这就无法实现“一个接口，多种方法”的目的了。

### virtual 虚函数

使子类和父类同名的函数有联系

virtual只用声明一次，编译器就知道父子类之间同名函数都设置为virtual，但是为了保持良好的编程规范，还是写明为好。

对virtual函数的调用，如果是指针或者引用，那么不能相信它一定是什么类型，得到运行时候，指针所指对象是什么类型，那么就调取那个类型的函数。（编译原理里的dynamic dispatch）



## 二十四、多态的实现



```c++
#include<iostream>
using namespace std;
class A {
public:
	A() :i(65472) {}
	int i;
	virtual void f() { cout << "A::f()" << i << endl; }
	virtual void sf() { i = 56; cout << "A::f()" << i << endl; }
};
int main() {
	A a, b;
	a.f();
	cout << sizeof(a) << endl;
	int* p = (int*)&a;
	int* q = (int*)&b;
	cout << *p << " " << *q << endl;
	p++;
	cout << *p << endl;
	int* m = (int*)*p;
	cout << m << endl;
	p++;
	cout << *p << endl;
	return 0;
}
//、。，Ctrl + K + Ctrl + D 格式化排版
/*
A::f()65472
8
695108 695108 //vtable指针表，包含很多隐藏的vptr
65472		  //不管你i放的位置，vtable指针表在上面
0000FFC0	  // 
-858993460

10591028	
65472		
*/
```



所以在处理多态的时候，运行时，也并不是真的判断指针的类型，而且根据指针指向的vtable里面的虚函数来调用

```c++
#include<iostream>
using namespace std;
class A {
public:
	A() :i(12) {}
	int i;
	virtual void f() { cout << "A::f()" << i << endl; }
};
class B :public A {
public:
	int j;
	B() : j(20){}
	virtual void f() { cout << "B::f()" << j<<endl; }
	
};
int main() {
	A a;
	B b;
	A* p = &b;
	p->f();
	a = b;
	a.f();
	p = &a;
	p->f();
	cout<<"********"<<endl;

	A* q = &a;
	q->f();
	int* r = (int*) &a;//&a是class A 类型，所以要强制类型转换
	//https://blog.csdn.net/weixin_33775572/article/details/93291792?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_paycolumn_v3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_paycolumn_v3&utm_relevant_index=1
    
	int* t = (int*)&b;
	*r = *t;//将a的vtable换成b的vtable，执行a的虚函数会索引到b的虚函数
	//为了找 j 会找到下一块内存
	q->f();
	return 0;
	
}
//、。，Ctrl + K + Ctrl + D 格式化排版
/*
B::f()20
A::f()12
A::f()12
********
A::f()12
B::f()-858993460
*/
```

析构也是虚函数

是为了避免父类指针指向子类对象的时候，销毁父指针时，如果不是virtual，那么这里的绑定是静态绑定，这意味着父类的析构会被调用，子类析构被丢掉，没有析构。

**所以你的类里有一个虚函数，那么你的析构函数就得是虚函数。**

所有的OOP语言，默认动态绑定，C++默认静态绑定。



## 二十五、引用再研究

如果一个类的成员或参数是reference，那么在声明时期不知道怎么捆绑。

 那么在构造时候必须写明（唯一方式)



如果要从一个函数里面返回reference，类似于返回一个指针（不能用本地变量的引用返回），返回的是一个直接的变量，到未来会和别的reference绑定。

 返回值在左边做左值。



直接传递参数到函数很复杂，所以送指针。

 但是送指针就使得函数内部获得对外部对象的控制

所以推荐在指针前面加const，这样无法对指针指向的对象做修改。

const reference也推荐，，，几乎c++函数传值唯一的方法。这样我们就无法对其修改，比如说放在左边做左值。

 

### reference做参数

那么传入的参数必须要是能做左值的。

```cpp
#include<iostream>
using namespace std;
void f(const int& i) {
	cout << i << endl;
}
int main() {
	int i = 3;
	f(i * 3);
	return 0;	
}
//error
严重性	代码	说明	项目	文件	行	禁止显示状态
错误	C2664	“void f(int &)”: 无法将参数 1 从“int”转换为“int &”	ZJU_CPP	C:\Users\Administrator\source\repos\ZJU_CPP\main.cpp

#include<iostream>
using namespace std;
void f(const int& i) {
	cout << i << endl;
}
int main() {
	int i = 3;
	f(i * 3);
	return 0;	
}
```

可以理解为函数为引用创造了个暂时的const变量

```cpp
void func(int &);
const int temp@ = i*3;
func(temp@)  // 这里把一个const值传给变量，就有问题了，在void加上const即可
```

todo

这段代码我不管是在linux还是window都跑不通，但是翁教授的能过。不知道是什么版本问题

```c++
#include<iostream>
using namespace std;
class A {
public:
        int i;
        A() : i(0) {}
};
A f()
{
        A a;
        return a;
}

int main() {
        f().i = 10;
        return 0;
}

```



## 二十六、拷贝构造

### Copy 

创造了一个已存在对象的新复制

**C++里的初始化和赋值区别非常重要**

```c++
#include<iostream>
using namespace std;
static int objectCount = 0;
class Howmany {
public:
	Howmany() { objectCount++; print("Howmany()"); }
	void print(const string& msg = "") {//msg是windows程序中的结构体，用于保存windows消息
		if (msg.size() != 0)	cout << msg << "; ";
		cout << "objectCount = " << objectCount << endl;
	}

	~Howmany() {
		objectCount--;
		print("~Howmany()");
	}
};
Howmany f(Howmany x) {
	cout << "begin of f" << endl;
	x.print("x argument inside f()");
	cout << "end of f" << endl;
	return x;//对象入对象出
}

int main() {
	Howmany h;
	h.print("after construction of h");
	Howmany h2 = f(h);
	h.print("after call to f()");
	return 0;	
}
/*
直接编译
Howmany(); objectCount = 1
after construction of h; objectCount = 1
begin of f
x argument inside f(); objectCount = 1
end of f
~Howmany(); objectCount = 0
after call to f(); objectCount = 0
~Howmany(); objectCount = -1
~Howmany(); objectCount = -2
*/
//应该是构造了x和h2，但是并没有通过howmany来构造，但是析构还是算。
```



```c++

#include<iostream>
using namespace std;
static int objectCount = 0;
class Howmany {
public:
	Howmany() { objectCount++; print("Howmany()"); }
	Howmany(int i) { objectCount++; print("Howmany(int i)"); }
	Howmany(const Howmany& o) { objectCount++; print("Howmany(Howmany &o)"); }
	void print(const string& msg = "") {//msg是windows程序中的结构体，用于保存windows消息
		if (msg.size() != 0)	cout << msg << "; ";
		cout << "objectCount = " << objectCount << endl;
	}

	~Howmany() {
		objectCount--;
		print("~Howmany()");
	}
};
Howmany f(Howmany x) {
	cout << "begin of f" << endl;
	x.print("x argument inside f()");
	cout << "end of f" << endl;
	return x;//对象入对象出
}

int main() {
	Howmany h;
	h.print("after construction of h");
	//Howmany h2(55);//平衡
	//Howmany h2 = 55;//有一个构造函数要一个int，所以可以这么写，与上一个运行结果一样
	//Howmany h2 = h;//也是平衡
	Howmany h2 = f(h);
	h.print("after call to f()");
	return 0;	
}


/*
Howmany(); objectCount = 1
after construction of h; objectCount = 1
Howmany(Howmany &o); objectCount = 2
begin of f
x argument inside f(); objectCount = 2
end of f
Howmany(Howmany &o); objectCount = 3
~Howmany(); objectCount = 2
after call to f(); objectCount = 2
~Howmany(); objectCount = 1
~Howmany(); objectCount = 0
*/
```

### copy constructor

T::T(const T&);

如果没有给拷贝构造，c++自动给你构造，但是不调用的你的。那样会拷贝每一个成员变量。（是成员层面的拷贝，而不是字节 层面的拷贝。如果有指针或引用，也会拷贝过去，这样会有两个指针指向同一个对象，两个引用捆绑到一个对象。

这样析构函数会析构两遍。会有内存报错。 

Howmany(Howmany o);  这样会递归下去。

## 二十七：拷贝构造二

### 为什么情况下会被调用？

1. 调用函数的参数，是对象本身。
2. 函数需要返回一个对象



**编译器可能会将不必要的拷贝构造优化掉**



```cpp
Person copy_func(char *who){
    Person local (who);
    local.print();
    return local;//copy ctor called
}
Person nocopy_func(char *who){
    return Person(who); //no copy needed
}
```



初始化  只能第一次

assignment 后面的

构造的都会有析构



### c++中尽量用string类不是（*char）



### **总结**

1. 写了一个类，先写三个函数：**默认构造，虚拟析构，拷贝构造**

2. 如果你真的不需要被拷贝，就声明一个private的拷贝构造
   1. prevents creation of a default copy constructor
   2. generates a compiler errot if try to pass-by-value
   3. don't need a defintion

(0429)

## 二十八、静态对象

### static

在c里就具有**二义性**，在c++还得考虑成员变量等等

- Static storage		在哪里
  - allocated once at a fixed address
- Visibility of a name   看到你
  - internal linkage
- Don't use static except inside functions and classes.

| 表达                    | 特点                                                         |
| ----------------------- | ------------------------------------------------------------ |
| Static free functions   | ~~Internal linkage~~ (deprecated过时)                        |
| Static global variables | ~~Internal linkage~~ (deprecated过时)                        |
| Static local variables  | Persisted storage持久存储                                    |
| Static member variables | Shared by all instances所有对象共享                          |
| Static member function  | Shared by all instances, can only access static member variables静态成员函数，在所有对象之间共享，只能访问静态变量或静态函数 |



static 只能在当前文件使用，就算你在别的文件extern ，也只能骗过编译器，骗不过linker

函数里的static ，static 的本地变量就是全局变量，但是在访问上只在函数内部能调用它

#### 如果static 一个本地变量，其类型是一个类的话，

```c++
class X{
    X(int , int );
    ~X();
    ...
};
void f(){
    static X my_x(10,20);
    ...
}
```

* 它在哪？									 全局数据区，link时候分配好了
* 它何时被构造（初始化）？      第一次进函数时

直接思考就是有个记号位，记录static变量是否被初始化过。但目前c++还没有直接的框架可以实现，vptr也不行

#### 如果static 一个对象

- Construction occurs when definition is encountered
  - constructor called at-most once   构造只发生一次
  - The construct arguments must be satisfied
- Destruction takes place on exit from program
  - compiler assures LIFO order of destructors析构按照顺序

#### 如果存在条件构造（满足某个条件再static）

- 只在满足条件的情况下被构造
- 保持值
- 有构造才有析构



#### Global objects 对象是全局

```c++
#include "x.h"
X global_x(12,23);
X global_x2(33,44);
```



- Construcors are called before main() is entered
  - Order controlled by appearance in file
  - In this case , global_x before global_x2
  - main() is no longer the first function called
- Destructions called when 
  - main() exists
  - exit() is called



多个文件之间的全局变量初始化，没有固定顺序可言，

解决方法：

​	别这么干；

​	逻辑允许的话，将全局变量定义放在一个文件



## 二十九、静态成员

类的成员是静态的

https://blog.csdn.net/u011041241/article/details/51148257?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.pc_relevant_aa&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.pc_relevant_aa&utm_relevant_index=1

### Static means

- Hidden
  -  当我们同时编译多个文件时，所有未加static前缀的[全局变量](https://so.csdn.net/so/search?q=全局变量&spm=1001.2101.3001.7020)和函数都具有全局可见性。利用这一特性可以在不同的文件中定义同名函数和同名变量，而不必担心命名冲突。
  - A static member is a member obey usual access rules
- Persistent
  - 保持变量内容的持久。存储在静态数据区的变量会在程序刚开始运行时就完成初始化，也是唯一的一次初始化。共有两种变量存储在静态存储区：全局变量和static变量，只不过和全局变量比起来，static可以控制变量的可见范围，说到底static还是用来隐藏的。
  - persisitent在c里还有malloc出来的东西，离开了函数，东西还在
  - independent of instances
- static的第三个作用是默认初始化为0。其实全局变量也具备这一属性，因为全局变量也存储在静态数据区。在静态数据区，内存中所有的字节默认值都是0x00，某些时候这一特点可以减少程序员的工作量。比如初始化一个稀疏矩阵，我们可以一个一个地把所有元素都置0，然后把不是0的几个元素赋值。如果定义成静态的，就省去了一开始置0的操作。再比如要把一个字符数组当字符串来用，但又觉得每次在字符数组末尾加’\0’太麻烦。如果把字符串定义成静态的，就省去了这个麻烦，因为那里本来就是’\0’。



在c++里 hidden我们用class 类的方法去做

persistent我们还需要借助static，成为不依赖于某一个特定对象的东西。



### 类的写法演变

一开始我们写类，要有.h  .cpp

后来我们了解了内联，允许我们把body写在.h里，这样甚至允许我只有一个.h

到现在，我们如果有了静态成员变量，那么必须有对应的.cpp，不然它无处安身



```c++
#include<iostream>
using namespace std;
class A {
public:
	A() { i = 0; }
	void print() { cout << i << endl; }
	void set(int ii) { i = ii; }
	static void say(int ii) { cout << ii <<" "<< i << endl; }
	static int good;
private:
	static int i;//函数的静态本地变量，实际是在全局数据区，
	//类里也同理，但是class是声明而不是定义
	//类似于extern int i;
};
int A::i;//静态的成员变量得多做这么一件事情，即找一个cpp，放置这个变量。不然只是声明，没有定义
int A::good = 44;
int main() {
	A a, b;
	a.set(10);
	b.print();
	a.say(65);
	A::say(77);
	cout << a.good << endl;
	//cout<<A::i<<endl;还是不能访问。
	cout << A::good << endl;//不想牵扯具体的类名，也可以这样写
	return 0;
}

```

顺便一提，i是静态成员，只能在自己定义的地方（line15）被初始化

```cpp
	A():i(0) {} //这样是不行的
	void set(int i) { this->i = i }// ok
```



### 静态成员的一些注意点

静态的成员函数/变量提供一种手段：建立这个类的任何对象之前，就能访问它的成员函数/变量。

静态成员函数只能调取静态的函数和静态的变量

静态成员函数有一个类范围，他们不能访问类的 this 指针。因为我们想实现没对象也能调用函数的功能。



## 三十、运算符重载--基本规则

### Overloaded operators

允许用户自定义几乎所有的运算符，并且优先使用按照你设计的运算符



除了常见的，C++ 支持的其他一些重要的运算符可以被重载。

| 运算符     | 描述                                                         |
| :--------- | :----------------------------------------------------------- |
| ,          | [逗号运算符](https://www.runoob.com/cplusplus/cpp-comma-operator.html)会顺序执行一系列运算。整个逗号表达式的值是以逗号分隔的列表中的最后一个表达式的值。 |
| ->（箭头） | [成员运算符](https://www.runoob.com/cplusplus/cpp-member-operators.html)用于引用类、结构和共用体的成员。 |
| ->*        |                                                              |
| ()         |                                                              |
| []         |                                                              |
| new        |                                                              |
| new[]      |                                                              |
| delete     |                                                              |
| delete[]   |                                                              |

### 不能重载的运算符

| .                |              |
| ---------------- | ------------ |
| .*               |              |
| ::               |              |
| ?:               |              |
| sizeof           |              |
| typeid           | 给出类型的id |
| static_cast      |              |
| dynamic_cast     |              |
| const_cast       |              |
| reinterpret_cast |              |

### 重载运算符的规定

1. 只有已经存在的运算符可以被重载。

> 比如^，在c++中表示异或，但是日常理解为乘幂，但是不能这么改

2. 只能对一个类，或是枚举类型，进行重载运算符
3. 重载操作符必须保持他操作数的个数，以及优先级



所谓重载运算符，不过是将有着运算符名字的函数（继承了他的入口和优先级）

重载运算符可以成为一个成员函数：

​	implicit first argument （因为已经有this了）

也可以成为一个全局的函数，不是任何类的成员，那么该有几个参数都得写了。



### 如何重载？

#### 作为成员函数

1. implicit first argument
2. no type conversion performed on receiver
3. must have access to class definition

一定要有const，不能让a+b = 6，不能让表达式成为左值

```c++
class Interger{
public:
	Integer(int n = 0) : i(n){}
    const Integer operator+(const Integer& n) const{
        return Integer(i+n.i);
    }
private:
    int i;
};

//使用
Interger x(1),y(5),z;
x+y;//=> x.operator+(y);编译器发现+左边的算子叫做receiver，决定+的性质

z= x + y;//ok
z = x + 3 ;//可以，3会被匿名构造
z = x + 3.5 ;//不可以，3.5无法被匿名构造，类型转换只能做一次
z = 3 + y;//不行，除非你可以通过手段将integer类变成int
```

二元的需要一个参数

一元的不需要参数，会产生一个新的

```c++
const Integer operator-() const{
    retur nInteger(-i);
}
...
z = -x;//z,operator = (x.operator-());拿i的值制造一个新的值交给别人
```



#### 作为全局函数

算子都写上去（一般两个），这样就可以不修改类的代码，增加overload，前提是接触到内部变量。

这时候 3+y 也可以了 



### Members vs Free Funtions

- Unary op should be members   单目应该做成成员
- = () [] -> ->* must be members   这些必须是成员
- assignment op should be members   
- All other binary op as non-members   二元的倾向于做成非成员的。



## 三十一、运算符重载--原型



### Argument Passing传参（针对对象，传的引用）

不会修改算子：必须加const

会修改算子：不能用const  ++ -- += -= ...



### return value

- 自己修改自己(=)还是做了一个新的对象（+）
- 新的对象，可不可以继续做左值



### 原型

```c++
+-*/%^&|~基础运算符
    const T operatorX(const T& l,const T& r) const;
! && || < <= > >= == 逻辑运算符
    bool operatorX(const T& l,const T& r) const;
[]  
	T&T::operator[](int index);
++ -- 得区分前缀后缀
class Integer{
public:
    ...
    const Integer& operator++(); //prefix++
    //++a 返回a加了之后的结果    
    const Integer operator++(int); //postfix++ 这个int不会真的起作用，只是告诉编译器这个是后缀
    //a++ 返回a加之前，原本a的结果，所以得新建一个对象
    const Integer& operator--(); //prefix--
    const Integer operator--(int); //postfix--
    ...
        
   
};
```

#### ++函数的实现

```c++
const Integer& Integer::operator++(){
    *this += 1;
    return *this;
}
const Integer Integer::operator++(int){
    Integer old(*this);// 拷贝构造
    ++(*this);//调用上面的++操作符函数
    return old;//返回一个变量  
}
```

#### 逻辑运算的实现

```c++
bool Integer::operator==(const Integer& rhs) const{
    return i== rhs.i;
}
bool Integer::operator!=(const Integer& rhs) const{
    return !(*this == rhs);//利用第一个函数的等于定义。
}
bool Integer::operator<(const Integer& rhs) const{
    return i<rhs.i;
}
bool Integer::operator>(const Integer& rhs) const{
    return rhs <*this;//利用第三个函数小于函数
}
bool Integer::operator<=(const Integer& rhs) const{
    return !(rhs <*this);//利用第三个函数小于函数
}
bool Integer::operator>=(const Integer& rhs) const{
    return !(*this<rhs);//利用第三个函数小于函数
}
```

只定义了两个原函数，

好处在于日后修改方便，且所有的函数都是inline，性能好些、



## 三十二、运算符重载--赋值

拷贝构造是做了一个新的对象出来，

赋值是将另一个对象的值赋给已有的对象。





### Automatic operator

如果没有创建type：operator=（type），编译器将自动创建一 个。这个运算符行为模仿自动创建的拷贝构造函数的行为：如果类包含 对象（或是从别的类继承的），对于这些对象，operator=被递归调用。 

这被称为成员赋值（memberwise assignment）。

```c++
#include <iostream>
using namespace std;

class Cargo {
public:
    Cargo& operator=(const Cargo&) {
        cout << "inside Cargo::operator=()" << endl;
        return *this;
    }
};

class Truck {
    Cargo b;
};

int main() {
    Truck a, b;
    a = b; // Prints: "inside Cargo::operator=()"
} ///:~

```



####   赋值的骨架 check for self assignment

```c++
T &T::operator = (const T&rhs){
    //check for self assignment
    if(this != &rhs){
        //peform assignment
    }
    return *this;
}
```

- 有动态分配内存的，比如指针之类的，需要写assignment op，要检查有没有自我赋值，没有的话，可以用系统的安排。
- 为了防止这类情况，声明为private。但是代价很大。



## 三十三、运算符重载--类型转换

我们希望一些类是用来表示一些值的，叫做value classes

### 类型转换

```c++
class One {
public:
  One() {}
};

class Two {
public:
  Two(const One&) {}
};

void f(Two) {}

int main() {
  One one;
  f(one); // Wants a Two, has a One
} ///:~
```

编译器用two的构造函数，用one 构造了一个two，送给f

```c++
class One {
public:
  One() {}
};

class Two {
public:
  explicit Two(const One&) {}
};

void f(Two) {}

int main() {
  One one;
//!  f(one); // No auto conversion allowed
  f(Two(one)); // OK -- user performs conversion
} ///:~

```

使用explicit 可以限制类型转换



### 转换符号

Operator conversion

* function will be called automatically
* return type is same as function name

```c++
class Rational{
public:
...
    operator double() const; // Rational to double
}
Rational::operator double() const{
    return numerator_/(double) denominator_;
}
Rational r(1,3); double d = 1.3*r;//r=> double
```

没有返回类型和参数

### X::operator T()

- Operator name is any type descriptor

- No explicit arguments
- no return type
- Compiler will use it as a type conversion from X=>T

### C++ type conversions

* Built-in conversions

  * primitive

    char-short-int-float-double

    ​					int-double

  * implicit(for ant type T)

    * T => T&
    * T& => T
    * T* => void*      只是看待指针指向对象的眼光不同
    * T[] => T*
    * T* => T[]
    * T => const T

* User-defined T => C

  * if C(T) is a valid constructor call for C  如果c类有一个用t做c的构造函数
  * if operator C() is defined for T              如果t类有一个op c 将t变c

* BUT 如果两个都有

```c++
class Orange; // Class declaration

class Apple {
public:
  operator Orange() const; // Convert Apple to Orange
};

class Orange {
public:
  Orange(Apple); // Convert Apple to Orange
};

void f(Orange) {}

int main() {
  Apple a;
//! f(a); // Error: ambiguous conversion
} ///:~

```

编译器会混淆

可以加一个explicit 限制转换

```c++
class Orange {
public:
  explicit Orange(Apple); // Convert Apple to Orange
};
```

### **explicit关键字**

[C++ 参考手册如下解释](https://link.zhihu.com/?target=https%3A//zh.cppreference.com/w/cpp/language/explicit)

1. 指定构造函数或转换函数 (C++11起)为显式, 即它不能用于[隐式转换](https://link.zhihu.com/?target=https%3A//zh.cppreference.com/w/cpp/language/implicit_conversion)和[复制初始化](https://link.zhihu.com/?target=https%3A//zh.cppreference.com/w/cpp/language/copy_initialization).
2. explicit 指定符可以与常量表达式一同使用. 函数若且唯若该常量表达式求值为 true 才为显式. (C++20起)

 **能用就用**

如果我们能预料到某种情况的发生, 就不要把这个情况的控制权交给编译器. 之前的代码, 以前我都觉得它无法通过编译. 在不知道`explicit`关键字的情况下, 我也是每次都使用`Point(1)`做一个类型转换再传入给`displayPoint`函数.

Effective C++中也写:

> 被声明为`explicit`的构造函数通常比其 non-explicit 兄弟更受欢迎, 因为它们禁止编译器执行非预期 (往往也不被期望) 的类型转换. 除非我有一个好理由允许构造函数被用于隐式类型转换, 否则我会把它声明为`explicit`. 我鼓励你遵循相同的政策.





## 三十四、模板 template



类型成为template的参数

function template

class template

template function

template class



### 函数模板

```c++
template <class T>
void swap(T& X,T& y){
    T temp = x;
    x= y;
    y =temp;
}
```

template 是一个声明而不是定义。告诉编译器替我们做出配套的函数



#### Interaction

- only exact match on types is used 

- No conversion operations are applied 用模板不做类型转换

- even implict conversion（int-> double） are ignored

  

#### Overloading rules

出现重载，先检查有没有唯一的函数匹配，再检查有没有唯一的函数模板匹配



#### function instantiation函数实例化



```c++
template <class T>
void foo (void){ /* */}
foo<int>();			//T is int
foo<float>();		//T is float
```

虽然foo 是void，但是你可以通过<> 来explicit它，但是低级编译器可能不支持



### 类模板 Class templates



example ：vector

```c++
template <class T>
class Vector {
public:
	Vector(int);
	~Vector();
	Vector(const Vector&);
	Vector& operator = (const Vector&);
	T& operator[](int);
private:
	T* m_elements;
	int m_size;
};
```

这还是个声明，在这个声明里，用T做某个成员变量的类型，用T做某个函数的返回类型

**类模板里的每一个函数都是函数模板，并且函数名称类的名称也得加< >**

 （0507）

## 三十五、模板二



```c++
 template<class T>
 void sort(vector<T>& arr) {
	 const size_t last = arr.size() - 1;
	 for (int i = 0; i < last; i++) {
		 for (int i = last; i < j; j--) {
			 if (arr[j] < arr[j - 1]) {
				 swap(arr[j], arr[j - 1]);
			 }
		 }
	 }
 }
```

这个arr的类型是T



### 模块的一些特定

#### 模板可以有多个参数

```c++
 template<class Key,class Value>
 class Hashtable {
	 const Value& lookup(const Key&) const;
	 void install(const Key&, const Value);
};
```



#### 模块也可以有嵌套

```c++
Vector<Vector<double *> >
```

注意最后面的 两个大于号，有的编译器会把它当成右移，建议加空格

#### 模块的参数也可以超复杂

```c++
Vector<int (*) (Vector<double>&,int)>
```

这是一个函数指针的vector，函数指针返回int，它的参数表有两项，一个是放着double的vector的引用，第二项是int。

#### 模块其他的一些参数

可以是常量值。可以实现default value

```c++
 template<class T,int bounds = 100>
 class FixedVector {
 public:
	 FixedVector();
	 T& operator[](int);
 private:
	 T elements[bounds];
 };
```



### 模板遇到继承

```c++
template <class A>
class Derived : public Base{}
父类可以是template种出来的那个类·
template <class A>
class Derived : public List<A>{}
```



## 三十六、异常

### Exceptions

The basic philosophy of C++ is that "badly formed code will not be run"

所以c++的一些检查比起c更加严格

另外在运行过程中判断是否出错也很重要

### Run-time error

read a file

| 行为                      | 问题                                                         |
| ------------------------- | ------------------------------------------------------------ |
| open this file            | 文件不存在；文件被别的进程独占；……                           |
| determine its size        | 文件是一个网络数据流；另一个进程打开文件往里写数据；文件是一个设备 |
| allocate that much memory | 文件大到超出内存                                             |
| read the file into memory | 存储介质坏盘；                                               |
| close the file            | 别的进程还在使用                                             |

用try catch，来提高可读性

## 三十七、异常的抛出与捕捉

### 以vector容器举例

```c++
template<class T>
T& Vector<T>::operator[](int indx)
```

如果indx越界（<0或>=n)

| 解决方法                                               | 问题                 |
| ------------------------------------------------------ | -------------------- |
| return random memory object 不解决，返回一个random对象 | 会访问错误内存       |
| return a special error value                           | 不能直接返回参与运算 |
| just die                                               |                      |
| die gracefully with autopsy                            |                      |

所以应该使用exception抛出异常

### 抛出异常 turf the problem

throw<<something>> 扔的东西没有限制。



### throw 后怎么处理？

1. Doesn't Care 

   code never even suspects a problem 

2. Cares deeply

   进入try 到catch，不在进行try底下的函数

3. Mildly interested

   不带任何东西的throw 

4. Doesn't care about the partculars

   catch(...) 异常的万能捕捉器



## 三十八、异常语句

### Try blocks

try 后面至少要有一个catch

catch 很像函数。

```c++
catch(someType v){
    //handler code
}
catch(...){ //虽然可以处理所有异常，但是拿不到异常对象
    //handler code
}
```

### 异常匹配

handlers are checked in order of apperance

1. check for exact match

2. apply base class conversions 子类的异常能不能被父类的catch

   reference and pointer types，only

3. Ellipse(...) match all

注：如果将精确匹配的报错放在父类报错之后，或是第一个就是catch(...)编译器会报错



### 异常的详细说明

- declare which exceptions function might raise
- part of function prototypes

```c++
void abc(int a) : throw(MathErr){//throw里可以有多个报错类，表示这个函数最多有这些报错,用来约束abc，如果你抛出别的异常，会抛出unexpected。
    ...
}
```

- Not checked at compiler time

- At run time

  - if an exception not in the list propagates out,

    the unexpected exception is raised

### 构造函数出现异常

最好还是throw。但是存在很大风险，造成内存垃圾

```c++
 class A {
 public:
	 A() {
		 cout<<"good"<<endl;
		 throw 0;
	 }
};
 int main() {
	 A* p = new A();
	 delete p;
	 return 0;
 }
```

改进但不完全

```c++
 class A {
 public:
	 A() {
         buf = new char[1024];
		 cout<<"good"<<endl;
		 delete this;
         throw 0;
	 }
     ~A(){delete buf;}//虽然解决了部分，但是buf的内存又变成垃圾了
};
 int main() {
	 A* p = new A();
	 delete p;
	 return 0;
 }
```



如果你throw的是new出来的对象，那么catch他的指针，但是不要忘记删除指针

## 三十九、流的概念

Stream

Unix  将一切视为文件来操作

文件有文本和二进制两种形式

### 以流做输入输出的优点

- 更好的类型安全

- 更好的延展性

- 更符合面向对象的特性

### 以流做输入输出的缺点

- 更verbose
- 经常会慢，但是现在社会不在乎程序运转的快慢，而是写程序的快慢

### c++与c相比

can overload inserters  << and extractors >>



### 流的特点

一维单方向

流过去就没法回头，不同于c不能任意读写，类似于磁带



### 流的操作符

- Extractors
  - read a value from the stream
  - overload the >> operator
- Inserters
  - insert a value into a stream
  - overload the << operator
- Manipulators
  - change the stream state

### C++中“流”的分类

C++中流主要分为三类：

- . **IO流：** 输入输出流，iostream
- . **文件流：** 对于文件的操作，fstream
- . **字符串流：** 主要实现对于字符串的操作，stringstream

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210218110056288.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzQ1MDU2NA==,size_16,color_FFFFFF,t_70)



## 四十、流的运算符

### 预先定义的流运算符

- cin
- cout
- cerr
- clog



### 读取

#### 预定义的读入

- istream >> value

extractors 会自动跳过空格

#### 定义一个流输入运算符

对自己的类型，做成一个全局的函数

- first argument is an istream&
- second argument is a reference to a value

```c++
istream&
operator>>(istream& is, T& obj){
    //specific code to read obj
    return is;
}
```

- 一定要注意返回&istream

  因为>>存在重载



#### 用函数的方式来读取

- int get()

  - return the next charactor in the stream
  - return EOF if no charactors left
  - example: copy input to output

  ```c++
  int ch;
  while ((ch = cin.get()) != EOF)
      cout.put(ch);
  ```

- istream& get(char& ch)  Manipulators

  - puts the next charactor into argument
  - similar to int get();

  这个是可以嵌入进流的

- get

- getline

- ignore

- int gcount 

- void   putback 看过再放回

- char peek  

### 输出

#### 预定义的输出

```c++
-ostream<<expression
```

#### 定义一个流输出运算符

对自己的类型，做成一个全局的函数

- first argument is an ostream&
- second argument is any value

```c++
ostream&
operator<<(ostream& is, const T& obj){
    //specific code to write obj
    return os;
}
```

- 一定要注意返回ostream &

  因为<<也存在重载

#### 用函数的方式来读取

- put(char)

  - print a single charactor
  - example: 

  ```c++
  cout.put('a');
  cerr.put('!');
  ```

- flush() 刷新缓冲区

  -[C++ 中如何区分std::endl、std::ends、std::flush的差异性](https://blog.csdn.net/Aliven888/article/details/111184891?spm=1001.2101.3001.6650.9&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-9-111184891-blog-106086783.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-9-111184891-blog-106086783.pc_relevant_default&utm_relevant_index=14)

  - force output of stream contents

  - example:

    ```c++
    cout<<"Enter a number";
    cout.flush();
    ```

    

- Manipulators modify the state of the stream

  - #include<iomanip>

  - Effects hold(usually)

    


## 四十一、STL简述









































