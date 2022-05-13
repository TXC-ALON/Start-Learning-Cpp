# Essential C++

## 序

作者除了计算机科学方面的学位，还有艺术硕士的头衔。

在迪士尼的工作，被要求48小时学会perl，于是找到了Randal Schwartz 的learning perl。由此也觉得自己写的c++ primer 写的太厚了，于是准备动手写个薄书。



## 一、C++编程基础 Basic C++ Programming



### 1、如何撰写C++程序 How to Write a C++ Program

函数的参数列表（parameter list）

调用函数（call/invoke）

数据的输入与输出，并非c++程序语言本身定义的一部分（同c，参见K&R 第七章），而是由c++ 的一套面向对象的类层次体系（classes hierarchy）提供支持，并作为C++标准库的一员。

class机制，赋予了我们增加程序内置类型抽象化层次的能力。



#### class的定义

**头文件header file**

声明该class所提供的各种操作行为operation

**程序代码文件program text**

包含	了这些操作行为的实现内容implemention



语句是c++程序的最小独立单元 statement



#### 命名空间namespace

命名空间是一种将库名称封装起来的办法。通过这种方法，可以避免和应用程序发生命名冲突的问题（所谓命名冲突是指在应用程序内两个不同的实体entity具有相同的名称，导致程序无法区分二者，命名冲突发生时，程序必须等到该命名冲突获得解析resolve后，才得以继续执行）。

命名空间像是在诸多名称的可见范围之间竖起的一道道围墙。

### 2、对象的定义与初始化 Defining and Initializing a Date Object

命名不能以数字开头，不能用到关键字

### 两种初始化

一般来说，将每个对象初始化是个好主意，除非类似input那种需要用户的输入加以设定。

初始化在c++有两种方式

```c++
int num_tries = 0;
int num_tries2(0);
```

用assignment（=）初始化，继承自c，如果对象属于内置类型或者对象可以单一值加以初始化，这种方式就没有问题，但如果对象需要多个初值，这种方法就没法完成任务了。所以就引入了处理“多值初始化”的构造函数初始化语法（constructor initialization syntax）

```c++
#include <complex>
complex<double>pure(0,7);
```

### 3、撰写表达式 Writing Expressions

#### 前置prefix与后置postfix

前置：原值先递增或递减，之后才被拿出来使用

后置：原值先供给表达式运算，在递增或递减

翁恺老师建议使用prefix，因为后置运算符在运算时期需要拷贝构造，浪费资源（虽然也没什么）

### 运算符的优先级

| 符号类型   | 符号意义   |
| ---------- | ---------- |
| 逻辑运算符 | NOT        |
| 算术运算符 | *，/，%    |
| 算术运算符 | +，-       |
| 关系运算符 | <.>,<=,>=  |
| 关系运算符 | ==,!=      |
| 逻辑运算符 | AND,OR     |
| 赋值运算符 | assignment |

### 4、条件语句和循环语句 Writing Conditions and Loop Statements

while

if-else

#### switch

switch 之后紧接着一个表达式，该表达式的值必须为整数值，之后跟着的一系列case之后都是一个常量表达式。

当某个标签和switch的表达式值吻合时，该case之后的所有case都会被执行，所以需要break来结束执行。

```c++
switch(num_tries)
{
    case 1:
        cout<<"your grade is A";
        break;
    case 2:
        cout<<"your grade is B";
        break;
    default:
        cout<<"your grade is not so good";
        break;
}
```

#### for

```c++
for（init-statement;condition;expresstion）{
    statement;
}             
```

### 5、数组与变长数组 How to Use Array and Vectors

Array 定长，Vector可变长

### 6、指针带来弹性 Pointers Allow for Flexibility

操作指针（代表某特定内存地址），舍弃以名城指定的方式，间接地访问每个对象，以达到透明化的目的。

```c++
int *p = &val;
//p就是val的内存地址
//*p就是操作val这个对象
```

**注意：要记得初始化每一个指针，并确保他们不是乱指的**

### 7、文件的读写 Writing and Reading Files

```c++
#include <fstream>
ofstream outfile ("seq_data.txt",ios_base::app);
```

利用ios_base::app 以追加模式打开文件

```c++
// EssentialC++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <fstream>
using namespace std;

int main()
{
	ifstream in_file("text.t");
	if (!in_file)
	{
		cerr << "oops! unable to open input file\n"; return -1;
	}

	ofstream out_file("text.sort");
	if (!out_file)
	{
		cerr << "oops! unable to open output file\n"; return -2;
	}

	string word;
	vector< string > text;
	while (in_file >> word)
		text.push_back(word);

	int ix;
	cout << "unsorted text: \n";
	for (ix = 0; ix < text.size(); ++ix)
		cout << text[ix] << ' ';
	cout << endl;

	sort(text.begin(), text.end());
	cout << "sorted text: \n";
	for (ix = 0; ix < text.size(); ++ix)
		cout << text[ix] << ' ';
	cout << endl;
	out_file << "sorted text: \n";
	for (ix = 0; ix < text.size(); ++ix)
		out_file << text[ix] << ' ';
	out_file << endl;
	std::cout << "Hello World!\n";
	return 0;
    
}
```



## 二、面向过程的编程风格 Procedural Programming

### 1、如何编写函数 How to Write a Function

#### 函数定义四部分

1. 返回类型：返回用户指定位置的值的类型
2. 函数名：命名要能帮助我们理解函数操作的实际内涵
3. 参数列表：函数参数扮演者占位符placeholder的角色
4. 函数体：操作本身的工具逻辑的实现内容

<font color='#DB4437'>函数必须先被声明，然后才能被调用</font>，以让编译器检查后续出现的使用方式是否正确，函数声明不必提供函数体，但必须指明返回类型、函数名，以及参数列表，此即所谓的函数原型function prototype

#### 考虑异常

不要相信用户绝不犯错，所以当他输入一个不合理的位置值，程序最极端的方式是终止整个程序，可以传一个值给标准库exit()

或者可以抛出异常exception。 第七章再说

### 2、调用函数 Invoking a Function

#### 传参方式

两种参数传递方式：传址by reference和传值by value

最简单的传址方式就是将参数声明为reference

**这里其实是传引用，而reference是用const *p实现的**

#### 作用域及范围

除了一个必要的static，函数内定义的对象，只存在于函数执行期间。如果返回这些所谓局部对象local object 的地址返回

为对象分配的内存，其存活时间称为存储器storage duration或范围extent。

对象在程序内的存活区域称为该对象的scope（作用域）

对象如果具有file scope，从其声明点至文件末尾都是可见的。file scope 内的对象也具备所谓的static extent。意思是对象的内存在main开始执行前就分配好了，可以一直存在直到程序结束。

内置类型的对象（void int这些），如果定义在file scope 之内，作为全局变量，必定被初始化为0，但如果被定义于local scope之内，那么除非程序员指定其初值，否则不会被初始化。

#### 动态内存管理

无论local scope 和file scope，其内存分配都是由系统操刀，而动态范围dynamic extent，其内存是来自于空闲空间free store。有时候也被称为heap memory，这种内存必须由c++程序员自己管理，分配new，删除delete。

C++没有提供任何语法让我们在从heap分配内存时设定初值。

> 链接：https://www.nowcoder.com/questionTerminal/678248be18a24a7cae301db0ef5c1c24
> 来源：牛客网
>
> \1) malloc 函数： void *malloc(unsigned int size)
>
> ​     在内存的动态分配区域中分配一个长度为size的连续空间，如果分配成功，则返回所分配内存空间的首地址，否则返回NULL，申请的内存不会进行初始化。
>
>  2）calloc 函数： void *calloc(unsigned int num, unsigned int size)
>
> ​     按照所给的数据个数和数据类型所占字节数，分配一个 num * size 连续的空间。
>
> ​    calloc申请内存空间后，会自动初始化内存空间为 0，但是malloc不会进行初始化，其内存空间存储的是一些随机数据。      
>  3）realloc 函数： void *realloc(void *ptr, unsigned int size)
>
> ​    动态分配一个长度为size的内存空间，并把内存空间的首地址赋值给ptr，把ptr内存空间调整为size。
>
> ​    申请的内存空间不会进行初始化。
> ​    4）new是动态分配内存的运算符，自动计算需要分配的空间，在分配类类型的内存空间时，同时调用类的构造函数，对内存空间进行初始化，即完成类的初始化工作。动态分配内置类型是否自动初始化取决于变量定义的位置，在函数体外定义的变量都初始化为0，在函数体内定义的内置类型变量都不进行初始化。

如果程序员没有使用delete释放内存，就会造成内存泄漏memory leak。

### 3、提供默认参数值Providing Default Parameter Values

我们不仅需要了解函数的工作逻辑，也得了解定义与file scope中的那些对象的工作逻辑。函数如果过于依赖于定义于file scope 内的对象，比较难以在其他环境中重用，也难以查找修改。



```c++
//这样输出可以通过传参，未必是cout，也可以设成文件
void display(const vector<int>&vec,ostream &os = cout){
    for (int ix = x;ix < vec.size();++ix){
        os << vec[ix]<< ' ';
    }
    os <<endl;
}
```

#### 默认参数两规则

关于默认参数值的提供，有两个不很直观的规则。

第一个规则是，默认值的解析resolve操作从最右边开始执行，如果我们为某个参数提供了默认值，那么这一参数右侧的所有参数都必须也具有默认参数值才行。下面这种不行。

~~void display(ostream &os = cout, const vector<int>&vec);~~

第二个规则是，默认值只能够指定一次，可以在函数声明处，也可以在函数定义处，但是不能够两个地方都指定。为了更高的可见性，我们决定将默认值，放在函数声明处而非定义处，一般会在头文件里定义了参数的默认值。

### 4、使用局部静态对象 Using Local Static Objects

局部静态对象处的空间，即使在不同的函数调用过程中，依然持续存在。由此也可以安全地返回elems的地址。

### 5、声明inline 函数 Declaring a Function Inline

将函数声明为inline，表示要求编译器在每个函数调用点上，将函数的内容展开。

面对一个inline函数，编译器可将该函数的调用操作改为以一份函数代码副本以代替。



注：将函数指定为inline，只是对编译器提出的一种要求，编译器是否执行这项请求，视具体的编译器而定。具体要参考bs老爷子的教材书7.1.1



一般来说，最适合声明为inline的函数是体积小，计算不复杂的函数。

另外由于编译器在调用inline的时候必须展开，所以这个定义必须是有效的。

### 6、提供重载函数 Providing Overloaded Functions

我们可以通过传入不同类型甚至不同数量的参数，使有相同函数名的函数有着不同的效果。而相反的，编译器无法判断返回类型不同的同名函数。

### 7、定义并使用模板函数 Defining and Using Template Functions

function template 将参数列表中指定的全部（或部分）参数的类型抽离了出来，除了类型信息。

```c++
template <typename elemType>
void display_message(const string &msg,const vector<elemType> &vec)
{
    cout <<msg;
    for (int ix = 0;ix<vec.size();++ix){
        elemType t = vec[ix];
        cout << t<<' ';
    }
}
```

很像种子，编译器对其进行绑定bind，产生一份函数实例进行后续的操作。

### 8、函数指针带来更大的弹性 Pointers to Functions Add Flexibility

```c++
const vector<int>* (*seq_ptr)(int);

```





## 三、泛型编程风格 Generic Programming

## 四、基于对象的编程风格 Object-Based Programming

## 五、面向对象编程风格 Object-Oriented Programming

## 六、以template进行编程 Programming with Templates

## 七、异常处理 Exception Handling