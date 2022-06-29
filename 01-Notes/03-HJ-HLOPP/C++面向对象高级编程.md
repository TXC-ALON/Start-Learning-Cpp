# C++面向对象高级编程

## 一、C++编程简介

### 面向对象是一种观念

### 学习目标

- 培养正规的、大气的编程习惯

- 以良好的方式编写C++ class  --  Object Based **基于对象**
  - class without pointer members  --  Complex
  - class with pointer members  --  String
- 学习Classes之间的关系  --  Object Oriented **面向对象**
  - 继承 inheritance
  - 复合 composition
  - 委托 delegation

### C++ 由语言 + 标准库组成

现在标准库占据越来越多的比重 

## 二、头文件与类的声明

面向对象将数据和数据之上的操作打包成类。

### 对class的分类

#### 不带指针 -- 复数 complex

#### 带指针  --  字符串 string -- 一个指针



### C++ 代码基本形式

#### 头文件

##### 头文件引入

标准库<>

自己写的 ""

##### :sunny:<font color='#DB4437'>头文件的防卫式声明</font>

```c++
#ifndef __标记__
#define __标记__
...
#endif
```

##### 类

##### 模板

抽出类型

#### 主程序



## complex

## 三、构造函数

### inline 内联函数

函数在class body内定义完成定义，成为inline。

不在body内，需要手动加inline。

具体是否inline ， 由编译器决定。太复杂就没法inline。

### 访问级别

#### public

方法、函数

#### private

数据、私有函数

### 构造函数 constructor (ctor)

构造函数名称一定要和类的名称一样。

参数，可以有默认值。

不需要有返回值

#### 初始化与赋值

数值的设置有两个阶段，初始化与赋值。

:sunny:<font color='#DB4437'>尽量使用初始化，以提高效率。</font>

```c++
complex (double r = 0,double i = 0)
    : re(r),im(i) // 初始列，初值列
    {}

complex (double r = 0,double i = 0)
    { re = r ; im = i;} //赋值，放弃了初始化的环节 ，效率差
```



不带指针的类，多半不用写析构函数。

#### 构造函数可以用很多个 --  overloading 重载

函数名不光是名字，还有参数和返回类型。

#### :sunny:默认函数很容易出错的一点

```c++
//构造函数
complex (double r = 0.double i = 0)
    : re(r),im(i)
    {}
complex () : re(0),im(0){}  

//调用
{
    complex c1;
    complex c2(); // 这里侯捷老师这样写，但是visualstudio 不让将空参这样写。要去掉括号
}
```



因为第一个构造函数提供了所有的默认实参[c++primer 7.5.1]，那么就算不提供参数，也能进行初始化，所以编译器就不知究竟该调用哪个构造函数了。

## 四、参数传递与返回值

### ctor可以放在private

constructor如果放在private区域，则不允许被外界创建对象。

**设计模式 -- Singleton 单例，外界只能用一份**

```c++
class A {
public:
	static A& getInstance();
	void setup(){};
private:
	A();
	A(const A& rhs);

};
A& A::getInstance()
{
	static A a;
	return a;
	// TODO: 在此处插入 return 语句
}

//取得那一份
A::getInstance().setup();
```

### :sunny:常量成员函数

设计接口时候需要考虑好，数据会不会改变，要不要加const

```c++
double real() const {return re;}
double imag() const {return im;}
//不会改变数据，函数后面名加const，表示函数不会改变数据内容。 
```

如果两个函数没加const，函数体里来一个`const complex c2(2,1)`，那么就没法使用这两个函数。本质上还是非常量可以隐式转换为常量，反之则不行。常量不能随意去调用非常量成员函数。

### :sunny:参数传递：传值&传址

引用在底层就是一个const 指针。所以传递效率快。

<font color='#DB4437'>参数传递尽量传reference</font>。

返回值传递尽量传reference。

### 友元

在类里面声明友元，则自动取得其private成员。

:sunny:**相同class 的各个objects 互为友元。**

```c++
#ifndef __COMPLEX_H__
#define  __COMPLEX_H__

#include <iostream>
using namespace std;

class complex {
public:
	complex(double a = 0, double b = 0) :re(a), rs(b)
	{

	}

	//这里直接访问传入参数的private数据
	double func(const complex& param)
	{
		return param.re + param.rs;
	}

private:
	double re, rs;
};


void Test_complex() {
	complex a1(2, 1);
	complex a2;
	std::cout << a2.func(a1);   //输出为3
	//std::cout<<a1.re;	//错误，不能访问
}
#endif
```

### class body 外的各种定义

reference什么时候不可以用？（参数传递&return返回）

- 传递函数生成的临时变量

```c++
inline complex& 
_doapl(complex* ths,const complex& r){
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}
inline complex&
complex::operator += (const complex& r){
    return _doapl (this,r);
}
```



## 五、操作符重载与临时对象

###   操作符重载-1 成员函数

```c++
inline complex&
__doapl(complex* ths,const complex& r){
	ths->re += r.re;
    the->im += r.im;
    return *ths;
}

inline complex& //真正写代码的时候不能写this，实际上是隐含的。指向调用者
complex::operator += (this,const complex& r){
    return __doapl(this,r);
}
```

`doapl`   do assignment plus。 赋值加法。

- 注意，`return *ths` 返回的是指针的值，但是传递者无需知道接受者是以reference的形式来接受。如果返回值，会产生不必要的临时变量。
- 如果是void类型，两个参数也能跑，但是`c3+=c2+=c1;`就过不了关了。

###  操作符重载-2 非成员函数

```c++
inline complex
operator + (const complex& x,const complex& y){
    return complex (real(x) + real (y) ,imag(x) + imag (y));
} 
```

- 成员函数形式和非成员函数只能写一个。

- 全局函数没有this指针。

- 返回值不能是reference，因为他们返回的必定是local reference，不同于成员函数，本身就有左值，而全局函数，离开函数数据就死亡了。所以不能return by reference。
- `类名（）` 创建一个临时对象，生命到下一行就结束了。

- 理论上，下面的取正操作，没有改变传入的对象，可以返回reference，但是标准库没有这么做。

```c++
inline complex
operator + (const complex& x){
	return x;
}
```

- `<<` 只能写成全局函数，因为`cout`这些东西都是老东西。不指望他们能适配成员函数版本的操作符。且不能写成const。
- 乍一看`<<`结果输出到屏幕，数据没用了，可以用void，但是如果迭代使用，那么还是不行。

### 本章总结

设计一个class 要注意

- 构造函数的初始化参数列表要会用，能初始化别赋值
- 函数要不要加`const`一定要考虑

- 尽量考虑传reference
- return 是回reference，还是value要考虑
- 函数大多放在public， 数据放在private



## 第六章 复习Complex 类的实现过程

1. 防卫式的头文件定义
2. 考虑复数类需要什么数据（实部虚部），数据是什么类型。
3. 构造函数（构造函数没有返回类型）
   1. 考虑需不需要默认值
   2. 考虑参数传递是传值还是传引用
   3. 使用初值列语法  
   4. 考虑构造函数还需要做什么 `{ }`
4. 这个类支持哪些操作？
   1. 设计为成员函数 -- 隐含this
   2. 设计为非成员函数
   3. 注意是否需要加const
5. 是否需要加友元（友元可以访问private）
6. 如果你最后返回值不是local object，就可以传引用 时刻注意return type
7. 一些操作不作为成员函数，是为了它具有更多的泛用性，比如“加”，不光是复数可以用，实数加复数等等。





## String

## 第七章 三大函数：拷贝构造、拷贝复制、析构