# Object-Oriented Programming

[TOC]



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

#### TicketMachine.h

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

#### TicketMachine.cpp

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

#### main.cpp

``` cpp
#include<iostream>
#include"TicketMachine.h"

int main() {
	TicketMachine tm;
	tm.insertMoney(100);
	tm.showBalance();
}
```

### ::resolver解析符

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

parameters和local variables 本质上是一样的   存储放在栈里面



## 八、成员变量的秘密

声明只是说有这么个东西，但是不能指出他的存在位置。









