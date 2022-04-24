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

Encapsulation（有机组合）

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

### :star:public/private/protected/friend的具体区别

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

:red_circle:建议日后都用初始化来赋初值



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



## 十五、对象继承

继承  Inheritance 取已有的类，在此基础上做些改造，做个新的类。

共享原先类的function 、 data ...

B继承A，A是B的基类/超类/父类，B是A的附生类/副类/子类

B对A进行扩充，B是A的superset

 





















