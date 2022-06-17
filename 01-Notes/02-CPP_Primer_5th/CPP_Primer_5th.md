# C++ Primer 5th

[TOC]

# Preface

C++ 是一门虽以十分成熟但仍不断进步的语言，而C++ 11标准的颁布延续了对编程效率的强调，而新标准的出发点是：

* 使语言更加统一，更加易学
* 使标准库更简单，更安全，使用起来更高效
* 使编写高效的抽象和库更加简单

一些普适的特性，诸如auto，使代码更加易读，程序员也可以更关注编程的意图。

一些诸如smart pointers 和 可变(move-enabled)容器，也让我们可以编写更加复杂的类，而不必纠结于复杂的资源管理。

## 为什么要读这本书？

现代C++语言可以看做是由三部分组成

- 低级语言，大部分继承inherited自C语言
- 现代高级语言特性，允许我们定义自己的类型以及组织大规模的程序和系统
- 标准库，它使用了这些高级特性来提供有用的数据结构和算法



- 不同于大多数教科书将C++的子集先进行讲述，而当学生陷于继承自C的细节时（一方面带来挫败感，一方面学到一些旧的坏习惯），随后又需要忘记这部分内-容。本书在一开始就介绍一些C++的高级语言特性，并连接标准库进行学习。
- 贯穿全书，作者都在强调好的风格，养成好的习惯。并特别强调那些棘手的问题，并对常见的错误想法和陷阱提出警告。
- 注意解释规则背后的基本原理。知其然，也知其所以然。 explaining the why not just the what!



## 本书的结构

第一部分和第二部分介绍C++语言和标准库的**基础内容**

第三部分会介绍拷贝控制的问题，一些使**类**也能像内置类型一样容易使用的技术

第四部分是介绍一些在**组织大型复杂系统**时非常有用的语言特性



## 本书的一些图标



|                             图标                             |                             意义                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| ![image-20220523153600549](CPP_Primer_5th.assets/image-20220523153600549.png) |            基础知识，构成语言的核心人人都应该掌握            |
| ![image-20220523153717260](CPP_Primer_5th.assets/image-20220523153717260.png) | 涉及高级主题或图书目的，初次看可以跳过，在实际用到之前没必要关注这部分 |
| ![image-20220523153728364](CPP_Primer_5th.assets/image-20220523153728364.png) |         特别复杂的概念，但是值得花些时间对其进行研究         |



# Start

## Chapter 1 Getting Started

### 1.1 Writing a Simple C++ Program

#### 函数的定义

函数的定义由四部分组成，返回值，函数名，一个被括号 (parantheses) 包着的（可能为空）的参数列表，以及以大括号(curly brace) 包着的函数体。

#### 返回值

正常情况下返回值为0代表程序正常运行，非零值暗示某种错误发生。

#### 关键概念：类型

类型是编程中最重要的基础概念之一，类型定义了数据元素的内容，以及这类数据可能用的运算。

#### 1.1.1 Compiling and Executing Our Program

先不要用ide入门，从命令行开始。

#### 编译，执行

```shell
g++ filename
g++ -o tofilename sourcefilename  // 指定输出文件名
./a.exe   ./a.out
```

执行完后通过echo可以获取上一次执行的返回值

```shell
$echo $?			//UNIX
$echo %ERRORLEVEL%  //windows
```



### 1.2 A First Look at Input/Output

C++并未定义任何输入输出语句，而是以一个全面的标准库来提供IO机制。

#### iostream

iostream库，包含两个基础类型 istream和ostream。表示输入输出流，而一个流就是一个字符序列，流的意义在于它一去不返，随着时间顺序生成或消耗。

#### 标准输入输出对象

cin		标准输入

cout		标准输出

cerr	输出警告和错误消息

clog	输出程序运行时的一般消息

#### 向流进行写

<<  和 >> 都有两个操作元，

对于 << 来说，它的左侧对象必须是一个ostream 对象，右侧对象可以是值。这个运算符，返回的是左边的对象，所以支持嵌套操作。

```c++
(std::cout<<"Hello world!")<<std::endl;
```

想象一下std::cout是个悬崖，后面的跟着瀑布流向下滑

##### 注意

操纵符(manipulator) endl的作用是结束当前行并刷新缓存区，在调试时我们往往需要插入许多打印，这时候应当在所有打印中一直刷新缓存区。不然很有可能对问题作出错误判断。

#### 命名空间

$3.1节详解

#### 从流进行读

对于 >> 来说，它的左侧对象必须是一个istream对象，右侧是待存数据的对象，它从给定的istream流读取数据，存入给定对象中。此运算符也是分会左侧对象，也支持嵌套操作。

```c++
(std::cin >> v1) >> v2;
```

想象一下std::cin 是个矿泉水灌水器，从左向右将瓶子吸在口子上，注入水。【这个比喻我觉得很绝诶，水是一样过来，水瓶可大可小，类比不同的类型】

### 1.3 A Word about Comments

两种注释：单行和定界符对注释

一般最好将定界符内每一行都加上*

```c++
#include <iostream>
/*
* Simple main function:
* Read two numbers and write their sum
*/
int main()
{
    int sum = 0, val = 1;
    // keep executing the while as long as val is less than or equal to 10
    while (val <= 10)
    {
        sum += val;  // assigns sum + val to sum
        ++val;       // add 1 to val
    }
    std::cout << "Sum of 1 to 10 inclusive is "<< sum << std::endl;
    return 0;
}
```

界定符对不能嵌套使用

```c++
#include<iostream>
using namespace std;

/*
/* 界定符对不能嵌套使用*/
*/
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
/*
PS E:\00Learning\C++\Start learing C++\02-Testcode> g++ .\1-3testcommentserror.cpp
.\1-3testcommentserror.cpp:6:2: error: expected unqualified-id before '/' token
.\1-3testcommentserror.cpp:6:2: error: expected constructor, destructor, or type conversion before '/' token
*/
```



我们在实际debug时，注释了一些包含界定符对形式的代码，导致嵌套错误。所以最好的注释方式是用单行注释注释掉代码段的每一行。

```c++
// /*
// * 单行注释中任何内容都会被忽略
// * 包括嵌套的注释对也一样会被忽略
// */
```

### 1.4 Flow of Control

#### 1.4.1 The while Statement

交替判断condition和执行关联代码，直到condition判断为假。

#### 1.4.2 The for Statement

for 循环包含两部分，循环头和循环体。循环头控制循环体的执行次数。

循环头由初始化语句init-statement,循环条件 condition，表达式expression组成。

#### 1.4.3 Reading an Unknown Number of Inputs

当我们使用一个istream对象作为对象时，其效果是检测流的状态，当遇到文件结束符end-of-file，或遇到一个无效输入时，istream对象的状态会变为无效。使条件为假。

>  在window系统中，输入文件结束符的方法是Ctrl+Z，然后按Enter或return键
>
> 在Unix系统中，则是Ctrl+D

### 编译器的报错

编译器的工作是检查程序文本中的错误，即form错误。

一些常见的编译错误如下：

#### Syntax error 语法错误

C++文法方面的错误

#### Type error 类型错误

比如讲int类型传给string

#### Declaration error 声明错误

C++ 中每个每个名字都必须先声明再使用，常见的错误比如用标准库里的名字却没加std::，或者标识符名字拼写错误。

单个错误往往具有传递效应，导致编译器报告的错误比实际数量多得多。

也就是edit - compile - debug 周期。

#### 1.4.4 The if Statement

判断语言的真假

**常见错误，将 == 和 = 搞混**

### 1.5 Introducing Classes

C++中用类来定义自己的数据结构，以便于程序员可以像使用内置类型一样使用类

#### 类的三个要点

- 类名是什么
- 它是在哪里被定义的
- 它支持什么操作

#### 1.5.1 The Sales_item Class

#### 文件重定向

大多数的操作系统都支持文件重定向，以避免反复手动输入输出数据

大多数Unix系统的文件重定向方法如下：

```c++
program.exe <infile >outfile
//头一个是已经编译好的exe，infile即为输入数据的文件和outfile可以指定名称名称，< > 前面需要有空格，并不是将infile包裹起来，而是表示某种输入输出方向。
```

VS Code终端实际上是使用Windows PowerShell。PowerShell支持“>”，不支持“<”。故需要通过“Get-Content”获取输入文件的内容。

```c++
.\add_item2.exe <add_item >output_add
               ~
The '<' operator is reserved for future use.
    
//直接使用他会和你说 < 运算符另有他用
```
```c++
//应该这样用
//PowerShell重定向命令
//Get-Content infile | ./***.exe >outfile

Get-Content .\data\add_item | ./add_item2.exe >.\data\outfile
```

#### 1.5.2 A First Look at Member Functions

成员函数是定义为类的一部分的函数，也被称为method方法。

```c++
item1.isbn()
```

使用.运算符来表达我们需要一个名为item1的对象的一个isbn成员。点运算符只能用于类型为类的对象。其左侧运算对象必须是一个类类型的对象，右侧运算对象必须是该类型的一个成员名，运算结果为右侧运算对象指定的成员。

当.运算符访问一个成员函数时，通常我们是想调用该函数，我们使用调用运算符()来调用一个函数，括号内放置实参列表（可能为空）

#### 附赠：利用vscode 里的code-runner来跑程序。

需要调整一些东西，主要是让它支持C++11

- [vscode折腾记1——把vscode打造成趁手的刷题工具](https://zhuanlan.zhihu.com/p/261982416)
- [将环境设置为C++11](https://zhuanlan.zhihu.com/p/269244754)

### 1.6 The Bookstore Program

### Chapter Summary  

本章介绍了基本的C++知识，可以编译简单的C++程序

个人觉得有些C基础的大多都了解类型、变量、控制流这些

而类、成员函数、重载运算符这些还需要多多了解。

文件重定向也挺有用的

### Defined Terms

- argument 实参
- parameter 形参
- manipulator 操纵符
- edit - compile - debug

# Part I The Basics

- 第二章  详述内置类型，并逐步介绍自定义数据类型的方法
- 第三章 介绍了string和vector，以及array
- 第四到六章 一次介绍了表达式、语句和函数
- 第七章 描述了怎么构建我们自己的类

## Chapter 2 Variables and Basic Types

数据类型是程序的基础，它告诉我们数据的意义以及能在数据上执行的操作。

### 2.1 Primitive Built-in Types 基本内置类型

#### 2.1.1 Arithmetic Types 算术类型

算术类型分为两类：整型 integral types（包括字符型和布尔型）和浮点型 floating-point types

##### 算术类型的大小

![](CPP_Primer_5th.assets/2-1.png)

这里需要注意一些，这里是最小大小，现在基本上int 都是4个字节，也就是32位的数据了

c++ 里规定，一个int至少和一个short一样大，一个long至少和一个int一样大，一个long long至少和一个long一样大

```c++
#include<iostream>
using namespace std;
int main() {
	cout << "bool's size is " << sizeof(bool) << endl;
	cout << "char's size is " << sizeof(char) << endl;
	cout << "wchar_t's size is " << sizeof(wchar_t) << endl;
	cout << "char16_t's size is " << sizeof(char16_t) << endl;
	cout << "char32_t's size is " << sizeof(char32_t) << endl;
	cout << "short's size is " << sizeof(short) << endl;
	cout << "int's size is " << sizeof(int) << endl;
	cout << "long's size is " << sizeof(long) << endl;
	cout << "long long's size is " << sizeof(long long) << endl;
	cout << "float's size is " << sizeof(float) << endl;
	cout << "double's size is " << sizeof(double) << endl;
	cout << "long double's size is " << sizeof(long double) << endl;
    return 0;
}

/*
//在win10 vs2019下
bool's size is 1
char's size is 1
wchar_t's size is 2
char16_t's size is 2
char32_t's size is 4
short's size is 2
int's size is 4
long's size is 4
long long's size is 8
float's size is 4
double's size is 8
long double's size is 8
*/
```

在[ubuntu](https://so.csdn.net/so/search?q=ubuntu&spm=1001.2101.3001.7020) 18.04，64位 环境下测试，long占据8个字节。

![image-20220531102256714](CPP_Primer_5th.assets/image-20220531102256714.png)

注意，这里的wchar_t, long, long double 有一定区别



> 网上搜索发现，long占据的字节数还和编译器的数据模型相关，具体如下：
>
> | Datetype  | LP64 | ILP64 | LLP64 | ILP32 | LP32 |
> | :-------- | :--- | :---- | :---- | :---- | :--- |
> | char      | 8    | 8     | 8     | 8     | 8    |
> | short     | 16   | 16    | 16    | 16    | 16   |
> | int       | 32   | 64    | 32    | 32    | 16   |
> | long      | 64   | 64    | 32    | 32    | 32   |
> | long long | 64   |       |       |       |      |
> | pointer   | 64   | 64    | 64    | 32    | 32   |
>
> 另外一般情况下windows64位一般使用LLP64模型，64位Unix，Linux使用的是LP64模型
>
> > https://blog.csdn.net/weixin_40997360/article/details/79948968

细节的部分在于内置类的的机械实现

在内存中，数据以0-1存储，那么取多大尺寸的数据，就首先要知道数据的类型。类型决定了数据所占的比特数以及该如何解释这些比特的内容。

##### 带符号类型和无符号类型

无符号类型仅能表示大于0的值，同时会比同类型的带符号的类型多一位存储数据，显得多些,实际一样。

比如unsigned char [0-255]。char [-128(10000000) -- 127(01111111)]

##### 选择类型的一些原则

1. 当你明确知道类型不可能为负时，使用unsigned类型
2. 整数运算，使用int，int不够大，直接上long long
3. 算术表达式中，不要用char或bool值。因为类型char是否有符号在不同的机器上可能不一样。非要用它来表达一个不大的整数的话，那么要标明是否带符号。
4. 执行浮点数运算用double。float常不够用，且有时候double比float更快，而long double就没啥必要，损耗也不容忽视。

#### 2.1.2 Type Conversions

对象的类型定义了对象能包含的数据和能参与的运算（加减乘除也是需要定义的），其中一种运算被大多数类型支持，也就是将对象从一种给定的类型转换（convert) 为另一种类型。

##### 类型转换的一些规则

|                转换类型                |                           转换方法                           |
| :------------------------------------: | :----------------------------------------------------------: |
|          非布尔值 -> 布尔类型          |                   0 -> false ; 非0 -> true                   |
|         布尔类型 -> 非布尔类型         |                   false -> 0  ; true -> 1                    |
|           浮点数 -> 整数类型           |                      仅保留小数点前部分                      |
|           整数值 -> 浮点类型           | 小数部分记为0，如果该整数空间超过浮点类型的容量，精度会有所损失 |
| 给一个无符号类型一个超出它表示范围的值 |               结果为对其进行取余(%容量)的余数                |
| 给一个带符号类型一个超出它表示范围的值 |        结果是未定义的，此时程序可能崩溃，可能继续工作        |

直接cout输出，由于无法正确识别类型，所以在终端输出结果也就不如预期，

![image-20220531105908646](CPP_Primer_5th.assets/image-20220531105908646.png)

debug可以看出值是按照书中类型变化了

![image-20220531105813758](CPP_Primer_5th.assets/image-20220531105813758.png)

其实加上int强制类型转换就好了

![image-20220531110140366](CPP_Primer_5th.assets/image-20220531110140366.png)

注意：切勿混用带符号类型和无符号类型，因为无符号类型很容易被搞成负值，带符号的负数被当成无符号数，那么也会产生意料之外的结果。

##### 2.1.2小练习

```c++
#include<iostream>
using namespace std;
int main() {
	unsigned u = 10, u2 = 42;
	cout << u2 - u << endl;//32
	cout << UINT32_MAX << endl;
	cout << u - u2 << endl;//-32 转化为 INT32MAX -31  4294967264 11111111 11111111 11111111 11100000
	int i = 10, i2 = 42;
	cout << i2 - i << endl;//32
	cout << i - i2 << endl;//-32
	cout << i - u << endl;//0
	cout << u - i << endl;//0
    return 0;
}
```

题解：

> 计算机内的数据是以补码形式存储的，负数的补码为按位取反后加1
>
> 那么-32为
>
> 10000000000000000000000000100000
>
> 取反后
>
> 01111111111111111111111111011111
>
> 加1
>
> 11111111111111111111111111100000



#### 2.1.3 Literals

字面值常量，即那种值一望而知的数据，每个字面值常量都对应一种数据类型。字面值常量的形式和值决定了他的数据类型。

##### 整型字面值

这里需要考虑一点，就是进制

decimal	十进制			20

octal	八进制				024

hexadecimal	十六进制		0x24

```c++
#include <iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	int a = 20;
	int b = 020;
	int c = 0x20;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
    return 0;
}
```



这里要注意一点，整型字面值具体的数据类型是由它的值和符号决定。默认情况下，十进制字面值是带符号数，八进制和十六进制可能带也可能不带。

十进制字面值的类型是int，long，long long中尺寸最小的那个。

八进制和十六进制字面值的类型是能容纳其数值的int，unsigned int，long，unsignedlong，long long，unsigned long long中尺寸最小者。

类型short没有与之对应的字面值。

注意：严格来说，十进制字面值不会是负数，-42，那个符号并不在字面值之内。

##### 浮点型字面值

默认浮点型字面值是一个double

##### 字符和字符串字面值

单括号括起来的一个字符，被称为char型字面值，

双括号括起来的0-多个字符构成字符串型字面值。

**字符串字面值实际上是由常量字符构成的一个数组，编译器在每个字符串结尾加上\0**

'A' = 'A'

"A" = 'A' + '\0'

**两个字符串字面值位置紧邻且仅由空格、缩进、和换行符分隔，那么他们实际上是一个字符串**

```c++
#include <iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	cout << "hello world " "this is a space "	"this is a tab "
		"this is a enter" << endl;
	return 0;

}
```

##### 转义序列 Escape Sequences

有一些字符是不可打印的，有一些字符是在C++中有特殊含义的字符，这些都需要使用到转义序列。

C++中规定的转义序列：

|          含义          | 转义字符 |
| :--------------------: | :------: |
|        newline         |   `\n`   |
| 横向制表horizontal tab |   `\t`   |
|      alert (bell)      |   `\a`   |
|  纵向制表vertical tab  |   `\v`   |
|       backspace        |   `\b`   |
|   双引号double quote   |   `\"`   |
|    反斜线backslash     |   `\\`   |
|     question mark      |   `\?`   |
|      single quote      |   `\'`   |
| 回车符carriage return  |   `\r`   |
|     进纸符formfeed     |   `\f`   |

```c++
std::cout << '\n';      // prints a newline
std::cout << "\tHi!\n"; // prints a tab followd by "Hi!" and a newline
```

泛化转义序列的形式是

- `\x`后紧跟1个或多个十六进制数字，

- 或者`\`后紧跟1个、2个或3个八进制数字，其中数字部分表示字符对应的数值。

  如果`\`后面跟着的八进制数字超过3个，则只有前3个数字与`\`构成转义序列。相反，`\x`要用到后面跟着的所有数字。

```c++
std::cout << "Hi \x4dO\115!\n"; // prints Hi MOM! followed by a newline
std::cout << '\115' << '\n';    // prints M followed by a newline
```



>**进一步研究了一些\后面跟着八进制超过3个后的情况**
>
>```c++
>#include <iostream>
>#include<string>
>#include<fstream>
>using namespace std;
>int main()
>{
>	char a = '\1156';
>	string b = "\1156";
>	std::cout << '\115' << endl;    // prints M followed by a newline
>	std::cout << '\1156' << endl;
>	std::cout << '\000' << endl;
>	std::cout << '\0000' << endl;
>	std::cout << '\001' << endl;
>	std::cout << '\0010' << endl;
>	std::cout << '\00000' << endl;
>	std::cout << '\11500' << endl;
>	std::cout << '\11500' - '\00000' << endl;5046272 = 77 * 256 * 256
>	std::cout << '\21500' << endl;
>	std::cout << '\12500' << endl;
>	std::cout << '\11510' << endl;
>	std::cout << '\11610' << endl;
>	std::cout << '\11520' << endl;
>	std::cout << a << '\n';   
>	std::cout << b << '\n';   
>	return 0;
>}
>```
>
>![image-20220601112806676](CPP_Primer_5th.assets/image-20220601112806676.png)
>
>可以看到当你直接输出'\1156'时，会输出19766，而这实际上是77*256+48(‘0’)+6，而77的八进制就是115。
>
>而你将这个数赋给char类型时，会进行识别截断，得到可用的字符'6'。
>
>当你输入'\11500时' 数据为5058608 = 5046272（77\*256\*256）+ 12336(256*48+48)
>
>当你输入'\11566时' 数据为5060150 = 5046272（77\*256\*256）+ 13878(256\*48+48+256*6+6)
>
>当你输入'\115777'时 数据为1295464247 = 1291845632（77\*256\*256）+ 3618615(256\*256\*48+256\*48+48+256\*256\*7+256\*7+7)
>
>这里就可以看出来，这里的组织形式是\115作为八进制参与数的组合，每一位进256。同时在后面的位数上，先预置了48。
>
>![image-20220601111456459](CPP_Primer_5th.assets/image-20220601111456459.png)
>
>

##### 指定字面值的类型

添加特定的前缀和后缀，可以改变整型、浮点型和字符型字面值的默认类型。

![](CPP_Primer_5th.assets/2-2.png)

使用一个长整型字面值时，最好使用大写字母`L`进行标记，小写字母`l`和数字`1`容易混淆。

然后nullptr，和true/false 分别为指针和布尔的字面值。

### 2.2 Variable

C++ 中的每个变量都有其数据类型，数据类型决定着变量所占内存空间的大小和布局方式、该空间能存储值的范围，以及变量能参与的运算。

#### 2.2.1 Variable Definitions

变量定义是一个类型说明符（type specifier）， 随后紧跟一个或多个变量名组成的列表，变量名以逗号分隔，最后以分号结束。

> **什么是对象？**
>
> 对象是一块能存储数据并具有某种类型的内存空间。
>
> 本书对对象的定义比较泛化，并不严格区分是类还是内置类型，也不区分是否命名或是否可读。

##### 初始值 initializers

初始化与赋值并不相同。

初始化的含义是创建变量是赋予其一个初始值

赋值的含义是将对象的当前值擦除，而以一个新值来代替

##### 列表初始化

C++ 支持很多种初始化的方式。

```c++
int num = 0;
int num = {0};
int num{0};
int num(0);
```

C++ 11 标准下，用花括号来初始化变量得到了全面应用

而用花括号初始化变量称为列表初始化（list initialization）。当用于内置类型的变量时，如果使用了列表初始化并且初始值存在丢失信息的风险，则编译器会报错。

```c++
long double ld = 3.1415926536;
int a{ld}, b = {ld};    // error: narrowing conversion required
int c(ld), d = ld;      // ok: but value will be truncated
```

这样编译器在赋值时就会进行检查，避免丢失信息的风险。

##### 默认初始化

如果定义变量时未指定初值，则变量被默认初始化（default initialized）。

如果是内置类型的变量未被显式初始化，它的值由定义的位置决定：

- 定义于任何函数体之外的变量被初始化为0；
- 定义于函数体内部的变量将不被初始化； 一个未被初始化的内置类型变量的值是未定义的，如果试图拷贝或以其他形式访问此类值将引发错误。

每个类各自决定其初始化对象的方式。

**建议初始化每一个内置类型的变量**。

#### 2.2.2 Variable Declarations and Definitions

C++支持分离式编译(separate compilation)，这就要求需要有在文件间共享代码的方法，特别是文件间变量的互用。

为了支持这一点，C++ 语言将声明和定义分开。声明 declaration 使得名字为程序所知。 定义 definition 负责创建与名字关联的实体(associated entity)。

如果想声明一个变量而不定义它，就在变量名前添加关键字`extern`，并且不要显式地初始化变量。

```c++
extern int i; // declares but does not define i
int j;      // declares and defines j
extern double pi = 3.1416; // definition
```

**`extern`语句如果包含了初始值就不再是声明了，而变成了定义。**

变量能且只能被定义一次，但是可以被声明多次。

如果要在多个文件中使用同一个变量，就必须将声明和定义分开。此时变量的定义必须出现且只能出现在一个文件中，其他使用该变量的文件必须对其进行声明，但绝对不能重复定义。

#### 静态类型 statically typed

C++ 是一种静态类型语言，其含义是在编译阶段检查变量。

程序越复杂，静态类型检查越有助于发现问题。然而，前提是编译器必须知道每一个实体对象的类型，这就要求我们在使用某个变量之前必须声明其类型。

#### 2.2.3 Identifiers 标识符

C++ 的标识符由字母、数字和下划线组成。必须以字母或下划线开头，长度没有限制，对大小写字母敏感。

##### 命名规范：

- 要能体现现实实际意义
- 变量名一般使用小写字母，不要用大写开头
- 用户自定义的类名，一般以大写字母开头， 如 Sales_items
- 如果标识符由多个单词组成，则单词间应有明显区分。
- 避免C++ 关键字

![C++ 关键字](CPP_Primer_5th.assets/2-3.png)

#### 2.2.4 Scope of a Name 作用域

作用域 scope 是程序的一部分，在其中名字有其特定的含义。C++语言中大多数作用域都以花括号分隔。

同一个名字在不同的作用域中可能指向不同的实体。名字的有效区域始于名字的声明语句，以声明语句所在的作用域末端为结束。

全局作用域 global scope	一次声明，整个程序范围都可使用

块作用域 block scope	仅仅在那块可以使用

> 一般来说，杂对象第一次被使用的地方附近定义它是一种好的选择。

##### 嵌套的作用域 Nested Scopes

作用域中一旦声明了某个名字，它所嵌套着的所有作用域中都能访问该名字，同时，允许在内层作用域中重新定义外层作用域已有的名字。

不过函数内部不宜定义与全局变量同名的新变量。

```c++
#include <iostream>
// Program for illustration purposes only: It is bad style for a function
// to use a global variable and also define a local variable with the same name
int reused = 42;    // reused has global scope
int main()
{
    int unique = 0; // unique has block scope
    // output #1: uses global reused; prints 42 0
    std::cout << reused << " " << unique << std::endl;
    int reused = 0; // new, local object named reused hides global reused
    // output #2: uses local reused; prints 0 0
    std::cout << reused << " " << unique << std::endl;
    // output #3: explicitly requests the global reused; prints 42 0
    std::cout << ::reused << " " << unique << std::endl;
    return 0;
}
```

可以用作用域操作符`::`来覆盖默认的作用域规则。因为全局作用域本身并没有名字，所以当作用域操作符的左侧为空时，会向全局作用域发出请求获取作用域操作符右侧名字对应的变量。

### 2.3 Compound Types 复合类型

复合类型指基于其他类型定义的定义，这里介绍两种，即引用和指针。

声明语句的通用描述是：**一条声明语句由一个基本数据类型 base type 和紧随其后的一个声明符 declarator列表组成。**

#### 2.3.1 References

> C++ 支持了右值引用，rvalue reference 在【13.6.1】 中会讲,这种引用主要用于内置类，一般来说我们使用“引用”这个词，是指左值引用。

简而言之，引用为对象起了另一个名字(alternative name)。

定义引用时，程序把引用和它的初始值绑定（bind）在一起，而不是将初始值拷贝给引用。

一旦初始化完成，将无法再令引用重新绑定到另一个对象，因为无法将引用重新绑定到另一个对象，因此**引用必须初始化。**

引用不是对象，仅仅是别名，所以不能定义引用的引用。

#### 2.3.2 Pointers

类似引用，指针也实现了对其他变量的间接访问。

而不同于引用的是：

* 指针本身就是一个对象，允许对指针赋值和拷贝，在指针的生命周期，他可以被指向几个不同的对象。
* 指针无须在定义时赋初值。和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值。



通过将声明符写成`*d`的形式来定义指针类型，其中`d`是变量名称。如果在一条语句中定义了多个指针变量，则每个量前都必须有符号`*`。

```c++
int *ip1, *ip2;     // both ip1 and ip2 are pointers to int
double dp, *dp2;    // dp2 is a pointer to double; dp is a double
```

指针存放某个对象的地址，要想获取对象的地址，需要使用取地址符`&`。

```c++
int ival = 42;
int *p = &ival; // p holds the address of ival; p is a pointer to ival
```

因为引用不是对象，没有实际地址，所以不能定义指向引用的指针。



大部分情况下，指针的类型要和它指向的对象严格匹配。

有两个例外，一是允许令一个指向常量的指针指向一个非常量对象【2.4.2】；二是存在继承关系的类，可以将基类的指针或引用绑定到派生类对象上【15.2.3】。



##### 指针的值（即地址）

应属于下列状态之一：

- 指向一个对象。
- 指向紧邻对象所占空间的下一个位置。
- 空指针，即指针没有指向任何对象。
- 无效指针，即上述情况之外的其他值。

试图拷贝或以其他方式访问无效指针的值都会引发错误。

##### 解引用

如果指针指向一个对象，可以使用解引用（dereference）符`*`来访问该对象。

```c++
int ival = 42;
int *p = &ival; // p holds the address of ival; p is a pointer to ival
cout << *p;     // * yields the object to which p points; prints 42
```

给解引用的结果赋值就是给指针所指向的对象赋值。

解引用操作仅适用于那些确实指向了某个对象的有效指针。

##### 空指针

空指针（null pointer）不指向任何对象，在试图使用一个指针前代码可以先检查它是否为空。得到空指针最直接的办法是用字面值`nullptr`（c++11最新支持）来初始化指针。

旧版本程序通常使用`NULL`（预处理变量，定义于头文件`cstdlib`中，值为0）给指针赋值，但在C++11中，最好使用`nullptr`初始化空指针。

老程序还会用NULL，这是一个在cstdlib头文件里定义的预处理变量(preprocessor variable)。

关于预处理器，2.6.3会稍微介绍一些。简单说它运行于编译之前，不属于命名空间std。

```c++
int *p1 = nullptr;  // equivalent to int *p1 = 0;
int *p2 = 0;        // directly initializes p2 from the literal constant 0
// must #include cstdlib
int *p3 = NULL;     // equivalent to int *p3 = 0;
```

建议初始化所有指针。

注意，不能用int变量直接赋给指针，哪怕这个int变量为0；

##### 赋值和指针

指针和引用的最大区别就在于引用只是别名，而指针是真实存在的对象，可以改变指向的对象。

给指针赋值就是令它存放一个新的地址，从而指向一个新的对象。

具体分清楚到底改变的是指针还是指针指向的对象，可以通过看表达式等式左边是什么。



指针非空，参与条件表达式，则为true，空指针为false。



##### void*指针

`void*`是一种特殊的指针类型，可以存放任意对象的地址，**但不能直接操作`void*`指针所指的对象**。只能拿它和别的指针进行比较，作为函数的输入输出，或是赋给另一个void*指针。

概括说来，从void* 的视角来看，内存空间仅仅是内存空间，没办法访问内存空间中的对象。  【19.1.1】节会详细描述。【4.11.3】 会描述获取void*指针的方法。

#### 2.3.3 Understanding Compound Type Declarations

##### 基本数据类型和类型修饰符的关系

变量的定义包括一个基本数据类型和一组声明符。

```c++
int i = 1024, *p = &i, &r = i;
```

> 很多程序员会迷惑于基本数据类型和类型修饰符的关系，其实后者不过是声明符的一部分罢了。
>
> 特别是因为我们可以写成int*
>
> 比如
>
> ```c++
> int* a,b;
> //其中a是指针，b是int型变量。
> ```
>
> > 当声明符包含未修改的标识符时，正在声明的项将具有基类型。 如果星号 (**`\*`**) 显示在标识符的左侧，则将类型修改为指针类型。 如果标识符后跟方括号 (**`[ ]`**)，则将类型修改为数组类型。 如果标识符后跟圆括号，则将类型修改为函数类型。 若要详细了解如何解释声明中的优先级，请查看[解释更复杂的声明符](https://docs.microsoft.com/zh-cn/cpp/c-language/interpreting-more-complex-declarators?view=msvc-170)。
> >
> > ```c++
> > int i;
> > int a[];
> > int print();
> > ```
> >
> > 每个声明符至少声明一个标识符。 声明符必须包含一个类型说明符才能成为完整声明。 类型说明符显示：数组类型的元素的类型、指针类型寻址的对象的类型，或者函数的返回类型。
>
> > http://www.morecpp.cn/cpluspluc-declarations/

##### 

##### 指向指针的指针（Pointers to Pointers）：

一般来说，声明符中修饰符的个数没有限制。

```c++
int ival = 1024;
int *pi = &ival;    // pi points to an int
int **ppi = &pi;    // ppi points to a pointer to an int
```

![2-4](CPP_Primer_5th.assets/2-4.png)

##### 指向指针的引用（References to Pointers）：

```C++
int i = 42;
int *p;         // p is a pointer to int
int *&r = p;    // r is a reference to the pointer p
r = &i;         // r refers to a pointer; assigning &i to r makes p point to i
*r = 0;         // dereferencing r yields i, the object to which p points; changes i to 0
```

面对一条比较复杂的指针或引用的声明语句时，从右向左阅读有助于弄清它的真实含义。

**离变量名最近的符号对变量的类型有最直接的影响。**其余部分用来确定这个类型是什么。

### 2.4 const Qualifier

有时候我们想要定义一个不会被轻易改变的常量，那么就可以在变量前面添加const。

**const常量必须被初始化。**

任何对const对象进行赋值（擦写）都会引发错误。

对象的类型决定了其能做什么操作，所以只能在const类型的对象上执行不改变其内容的操作。

##### const变量的作用范围

默认情况下，`const`对象被设定成**仅在文件内有效**。当多个文件中出现了同名的`const`变量时，其实等同于在不同文件中分别定义了独立的变量。

如果想在多个文件间共享`const`对象：

- 若`const`对象的值在编译时已经确定，则应该定义在头文件中。其他源文件包含该头文件时，不会产生重复定义错误。

- 若`const`对象的值直到运行时才能确定，则应该在头文件中声明，在源文件中定义。此时`const`变量的声明和定义前都应该添加`extern`关键字。

  ```c++
  // file_1.cc defines and initializes a const that is accessible to other files
  extern const int bufSize = fcn();
  // file_1.h
  extern const int bufSize;   // same bufSize as defined in file_1.cc
  ```

#### 2.4.1 References to const

把引用绑定在`const`对象上即为对常量的引用（reference to const）。对常量的引用不能被用作修改它所绑定的对象。

```c++
const int ci = 1024;
const int &r1 = ci;     // ok: both reference and underlying object are const
r1 = 42;        // error: r1 is a reference to const
int &r2 = ci;   // error: non const reference to a const object
```

> 常量引用
>
> const Reference is a reference to Const
>
> 有些人会将const类型的引用叫做常量引用，这是有些歧义的。
>
> 因为引用不是一个对象，我们没法让它本身const。而且C++语言并不允许随意改变引用所绑定的对象，所以这层意义上所有的引用都算是常量。

##### 初始化和对const的引用

大部分情况下，引用的类型要和与之绑定的对象严格匹配。但是有两个例外：

- 初始化常量引用时允许用任意表达式作为初始值，只要该表达式的结果能转换成引用的类型即可。

  ```c++
  int i = 42;
  const int &r1 = i;      // we can bind a const int& to a plain int object
  const int &r2 = 42;     // ok: r1 is a reference to const
  const int &r3 = r1 * 2;     // ok: r3 is a reference to const
  int &r4 = r * 2;        // error: r4 is a plain, non const reference
  ```

- 允许为一个常量引用绑定非常量的对象、字面值或者一般表达式。

  ```c++
  double dval = 3.14;
  const int &ri = dval;
  ```



> 当一个常量引用被绑定到另外一个类型时，
> ```c++
> double dval = 3.14;
> const int &ri = dval;
> ```
>
> 发生的其实是
>
> ```c++
> double dval = 3.14;
> const int temp = dval;
> const int &ri = temp;
> ```
>
> 这种情况下，ri绑定了一个临时量。这玩意是编译器生成的,为了确保ri绑定一个整数。
>
> 如果ri不是常量，那么就会让ri绑定上temp，而我们ri引用想绑定的是dval，于是c++就禁止将非常量引用绑定到类型不同的对象上。
>
> > ```c++
>> #include <iostream>
> > using namespace std;
> > int main()
> > {
> >     double dval = 3.14;
> >     int &ri = dval;
> >     cout<<ri<<endl;
> >    }
> >    /*
> > PS C:\Users\Administrator\Desktop> g++ .\Untitled-1.cpp
> > .\Untitled-1.cpp: In function 'int main()':
> > .\Untitled-1.cpp:9:16: error: invalid initialization of reference of type 'int&' from expression of type 'double

常量引用仅对引用可参与的操作做了限定，但是对于引用的对象本身是不是一个常量未做限定。由于对象可能是非常量，那么允许通过其他方式修改它的值。

```c++
#include <iostream>
using namespace std;
int main()
{
    int i = 42;
    int &r1 = i;      // we can bind a const int& to a plain int object
    const int &r2 = i;     // ok: r1 is a reference to const
    cout << r1 <<endl;
    cout << r2 <<endl;
    r1 = 0;
    cout<<"change"<<endl;
    cout << r1 <<endl;
    cout << r2 <<endl;
}
/*
42
42
change
0
0
*/
```

#### 2.4.2 Pointers and const

指向常量的指针(pointer to const) 不能用于改变其所指对象的值。

要想存放常量对象的地址，只能使用指向常量的指针。

```c++
const double pi = 3.14;     // pi is const; its value may not be changed
double *ptr = &pi;          // error: ptr is a plain pointer
const double *cptr = &pi;   // ok: cptr may point to a double that is const
*cptr = 42;         // error: cannot assign to *cptr
double dval = 3.14; // dval is a double; its value can be changed
cptr = &dval;       // ok: but can't change dval through cptr
```

常量指针（const pointer）必须初始化，而放在指针中的那个地址也就不能再改变了。

定义语句中把`*`放在`const`之前用来说明指针本身是一个常量。这也暗示了不变得是指针而不是指向的那个值。

```c++
int errNumb = 0;
int *const curErr = &errNumb;   // curErr will always point to errNumb
const double pi = 3.14159;
const double *const pip = &pi;  // pip is a const pointer to a const object
```

指针本身是常量并不代表不能通过指针修改其所指向的对象的值，能否这样做完全依赖于其指向对象的类型。

> 举个例子，就好像你把钱存银行定期，从你这边你规定了自己的行为，这笔钱是const的，你不去动它，而在银行那边，钱是有可能会被动的，甚至说动是应该的（变量）。但银行不应该影响我的取款，可是一些无良的银行甚至会挪用（糟糕的操作），在你要取回定期是发现没钱了，这就不好了。
>
> 当然如果你存的东西也是个const，比如一些很难动的东西，比如古董啊，雕像啊什么的，那么两边都不会动了。

```c++
#include <iostream>
using namespace std;
int main()
{
    int i2 = 5;
    int *const p2 = &i2;
    cout<<*p2<<endl;
    *p2 = 6;
    cout<<*p2<<endl;
    cout<<i2<<endl;
    const int * const p3 = &i2;
    //*p3 = 7;
    cout<<*p3<<endl;
    return 0;
}
/*
PS C:\Users\Administrator\Desktop> g++ .\Untitled-1.cpp
PS C:\Users\Administrator\Desktop> .\a.exe
5
6
6
6
如果把注释去掉，可以看到
.\Untitled-1.cpp: In function 'int main()':
.\Untitled-1.cpp:12:11: error: assignment of read-only location '*(const int*)p3'
*/
```

所以说 p2是一个指向变量的常量指针，可以改变i2，而p3 是一个指向常量的常量指针。



> ![2-4-2-PointersWithConstants-1024x535](CPP_Primer_5th.assets/2-4-2-PointersWithConstants-1024x535.png)
>
> https://www.geeksforgeeks.org/difference-between-const-int-const-int-const-and-int-const/
>
> | 语句                  | 含义                                                         | 介绍                                                         | 备注                                               |
> | --------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | -------------------------------------------------- |
> | const int \*ptr       | const int \* is pointer to constant integer                  |                                                              |                                                    |
> | int const\* ptr       | **int const\*** is pointer to constant integer               | This means that the variable being declared is a pointer, pointing to a constant integer. Effectively, this implies that the pointer is pointing to a value that shouldn’t be changed. Const qualifier doesn’t affect the pointer in this scenario so the pointer is allowed to point to some other address.<br/>The first const keyword can go either side of data type, hence **int const\*** is equivalent to **const int\***. | 更推荐这种，可以很容易读出 ptr is a * to const int |
> | const int * const ptr | **const int\* const** is a constant pointer to constant integer | This means that the variable being declared is a constant pointer pointing to a constant integer. Effectively, this implies that a constant pointer is pointing to a constant value. Hence, neither the pointer should point to a new address nor the value being pointed to should be changed.<br/>The first const keyword can go either side of data type, hence **const int\* const** is equivalent to **int const\* const**. | ptr is a const * to const int                      |
> | int* const ptr        | **int \*const** is **const** **pointer** to **int**          | This means that the variable being declared is a constant pointer pointing to an integer. Effectively, this implies that the pointer shouldn’t point to some other address. Const qualifier doesn’t affect the value of integer in this scenario so the value being stored in the address is allowed to change. | ptr is a const * to int                            |
>
> 这种从右向左读的方法很有用
>
> Using this rule, even complex declarations can be decoded like,
>
> - **int \** const** is a **const** **pointer** to **pointer** to an **int**.
> - **int \* const \*** is a **pointer** to **const** **pointer** to an **int**.
> - **int const \**** is a **pointer** to a **pointer** to a **const** **int**.
> - **int \* const \* const** is a **const** **pointer** to a **const** **pointer** to an **int**.

#### 2.4.3 Top-Level const

由于指针是个对象，那么它本事是不是常量，和它指的对象是不是常量，这是两个问题。

所以用名词顶层来表示指针是const。而用名词底层表示指针所指的对象是const。

类似的，顶层可以表示任意对象是常量。

底层则与一些复合类型的基本类型有关。

```c++
int i = 0;
int *const p1 = &i;     // we can't change the value of p1; const is top-level
const int ci = 42;      // we cannot change ci; const is top-level
const int *p2 = &ci;    // we can change p2; const is low-level
const int *const p3 = p2; // right-most const is top-level, left-most is not
const int &r = ci;      // const in reference types is always low-level
```

当执行拷贝操作时，常量是顶层`const`还是底层`const`区别明显：

- 顶层`const`没有影响。拷贝操作不会改变被拷贝对象的值，因此拷入和拷出的对象是否是常量无关紧要。

  ```c++
  i = ci;     // ok: copying the value of ci; top-level const in ci is ignored
  p2 = p3;    // ok: pointed-to type matches; top-level const in p3 is ignored
  ```

- 拷入和拷出的对象必须具有相同的底层`const`资格。或者两个对象的数据类型可以相互转换。一般来说，非常量可以转换成常量，反之则不行。

  ```c++
  int *p = p3;    // error: p3 has a low-level const but p doesn't
  p2 = p3;        // ok: p2 has the same low-level const qualification as p3
  p2 = &i;        // ok: we can convert int* to const int*
  int &r = ci;    // error: can't bind an ordinary int& to a const int object
  const int &r2 = i;  // ok: can bind const int& to plain int
  ```

> 这个讲的很好。https://blog.csdn.net/TeFuirnever/article/details/103011514

#### 2.4.4 constexpr and Constant Expressions

常量表达式（constant expressions）指值不会改变并且在**编译过程**就能得到计算结果的表达式。

字面值显然是常量表达式。

一个对象是否为常量表达式由它的数据类型和初始值共同决定。

```c++
const int max_files = 20;           // max_files is a constant expression
const int limit = max_files + 1;    // limit is a constant expression
int staff_size = 27;        // staff_size is not a constant expression
const int sz = get_size();  // sz is not a constant expression 它的值要到运行时才能得到。
```

##### constexpr变量

C++11允许将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量表达式。

```c++
constexpr int mf = 20;          // 20 is a constant expression
constexpr int limit = mf + 1;   // mf + 1 is a constant expression
constexpr int sz = size();      // ok only if size is a constexpr function
```

声明为constexpr类型一定是一个常量，且必须用常量表达式初始化。6.5.2节会介绍constexpr函数。

##### 字面值类型

目前接触的类型中，算术类型、引用和指针都属于字面值类型。

自定义类，IO库，string类型则不属于字面值类型。

【7.5.6】 【19.3】 会进一步介绍其他字面值类型

##### 指针与constexpr

指针和引用都能定义成`constexpr`，但是初始值受到严格限制。`constexpr`指针的初始值必须是0、`nullptr`或者是存储在某个固定地址中的对象。

函数体内定义的普通变量一般并非存放在固定地址中，因此`constexpr`指针不能指向这样的变量。相反，函数体外定义的变量地址固定不变，可以用来初始化`constexpr`指针。

在`constexpr`声明中如果定义了一个指针，限定符`constexpr`仅对指针本身有效，与指针所指的对象无关。`constexpr`把它所定义的对象置为了顶层`const`。

```c++
constexpr int *p = nullptr;     // p是指向int的const指针
constexpr int i = 0;
constexpr const int *cp = &i;   // cp是指向const int的const指针
```

`const`和`constexpr`限定的值都是常量。但`constexpr`对象的值必须在编译期间确定，而`const`对象的值可以延迟到运行期间确定。

建议使用`constexpr`修饰表示数组大小的对象，因为数组的大小必须在编译期间确定且不能改变。

### 2.5 Dealing with Types

#### 2.5.1 Type Aliases 类型别名

类型别名是某种类型的同义词，传统方法是使用关键字`typedef`定义类型别名。

```c++
typedef double wages;   // wages is a synonym for double
typedef wages base, *p; // base is a synonym for double, p for double*
```

C++11新规定可以使用关键字`using`进行别名声明（alias declaration），作用是把等号左侧的名字规定成等号右侧类型的别名。

##### ！易错点

```c++
typedef char *pstring;	//pstring 实际上是指向char的指针
const pstring cstr = 0; // 指向char类型的常量指针
const char *cstr = 0;	//指向const char 的指针。数据类型不是char* ，*成为声明符的一部分，而是char
//所以不能直接将类型别名替换成原来的样子来理解他。
```

#### 2.5.2 The auto Type Specifier

C++11新增`auto`类型说明符，能让编译器自动分析表达式所属的类型。

`auto`定义的变量必须有初始值。

```c++
// the type of item is deduced from the type of the result of adding val1 and val2
auto item = val1 + val2;    // item initialized to the result of val1 + val2
```

使用auto也能在一条语句中声明多个变量，但因为一个声明语句只能有一个基本类型，所以该语句中所有变量的初始基本数据类型必须一样。

##### 复合类型、常量和auto

编译器推断出来的`auto`类型有时和初始值的类型并不完全一样。

- 当引用被用作初始值时，编译器以引用对象的类型作为`auto`的类型。

  ```c++
  int i = 0, &r = i;
  auto a = r;     // a is an int (r is an alias for i, which has type int)
  ```

- `auto`一般会忽略顶层`const`。

  ```c++
  const int ci = i, &cr = ci;
  auto b = ci;    // b is an int (top-level const in ci is dropped)
  auto c = cr;    // c is an int (cr is an alias for ci whose const is top-level)
  auto d = &i;    // d is an int*(& of an int object is int*)
  auto e = &ci;   // e is const int*(& of a const object is low-level const)
  ```

  如果希望推断出的`auto`类型是一个顶层`const`，需要显式指定`const auto`。

  ```C++
  const auto f = ci;  // deduced type of ci is int; f has type const int
  ```


设置类型为`auto`的引用时，原来的初始化规则仍然适用，初始值中的顶层常量属性仍然保留。

```c++
auto &g = ci;   // g is a const int& that is bound to ci
auto &h = 42;   // error: we can't bind a plain reference to a literal
const auto &j = 42;     // ok: we can bind a const reference to a literal
```

还需要注意，在一个语句定义多个变量时，& * 都只从属于某个声明符，而不是基本数据类型的一部分。因此初始值必须是同一类型。

```c++
int  i = 0;
const int ci = i; 

auto k = ci,&l = i;		// k是整数，l是整型引用
auto &m = ci,*p = &ci;//m 是整型常量的引用， p是指向整型常量的指针
auto &n = i, *p2 = &ci;//错误  i的类型是int，&ci的类型是const int
```



#### 2.5.3 The decltype Type Specifier

C++11新增`decltype`类型指示符，作用是选择并返回操作数的数据类型，此过程中编译器不实际计算表达式的值。

```c++
decltype(f()) sum = x;  // sum has whatever type f returns
```

`decltype`处理顶层`const`和引用的方式与`auto`有些不同，如果`decltype`使用的表达式是一个变量，则`decltype`返回该变量的类型（包括顶层`const`和引用）。

```c++
const int ci = 0, &cj = ci;
decltype(ci) x = 0;     // x has type const int
decltype(cj) y = x;     // y has type const int& and is bound to x
decltype(cj) z;     // error: z is a reference and must be initialized
```

因为cj是一个引用，所以z也是引用，那么z必须被初始化。

引用从来都是作为其所指对象的同义词出现，只有用在decltype处是一个例外。



如果`decltype`使用的表达式不是一个变量，则`decltype`返回表达式结果对应的类型。

如果表达式的内容是解引用操作，则`decltype`将得到引用类型。

如果`decltype`使用的是一个不加括号的变量，则得到的结果就是该变量的类型；

如果给变量加上了一层或多层括号，则`decltype`会得到引用类型，因为**变量是一种可以作为赋值语句左值的特殊表达式。**

**`decltype((var))`的结果永远是引用，而`decltype(var)`的结果只有当`var`本身是一个引用时才会是引用。**

### 2.6 Defining Our Own Data Structures

在C++中，我们以类的形式定义数据结构。C++对类的支持甚多，本书三四部分都将大幅介绍类的知识。Sales_item看似简单，但是要实现它得在14章介绍自定义运算符之后。

#### 2.6.1 Defining the Sales_data Type

C++11规定可以为类的数据成员（data member）提供一个类内初始值（in-class initializer）。创建对象时，类内初始值将用于初始化数据成员，没有初始值的成员将被默认初始化。

**类内初始值不建议使用圆括号。**(不过目前我还是这样用) 参考【2.2.1】

> https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2628.html
>
> 因为我们无法避免这样的情况
>
> ```cpp
> class Widget 
> {
> private: 
>   typedef int x;
>   int z(x);
> };
> ```
>
> 这样的话，就会变为函数声明。

类定义的最后应该加上分号。（很多人会犯错）

> 另外个人经验，构造函数，参数表最后一个,不要有

#### 2.6.2 Using the Sales_data Class

#### 2.6.3 Writing Our Own Header Files

19.7 将会讲在函数体内定义类，但是这种类毕竟受了一些限制，所以类一般都不定义在函数体内。

头文件（header file）通常包含那些只能被定义一次的实体，如类、`const`和`constexpr`变量。

头文件一旦改变，相关的源文件必须重新编译以获取更新之后的声明。

##### 预处理器概述

头文件保护符（header guard）依赖于预处理变量（preprocessor variable）(2.3.2)。

预处理变量有两种状态：已定义和未定义。

`#define`指令把一个名字设定为预处理变量。

`#ifdef`指令当且仅当变量已定义时为真，

`#ifndef`指令当且仅当变量未定义时为真，一旦检查结果为真，则执行后续操作直至遇到`#endif`指令为止。

```c++
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
#endif
```

在高级版本的IDE环境中，可以直接使用`#pragma once`命令来防止头文件的重复包含。

预处理变量无视C++语言中关于作用域的规则。

整个程序中的预处理变量，包括头文件保护符必须唯一。预处理变量的名字一般均为大写。

头文件即使目前还没有被包含在任何其他头文件中，也应该设置保护符。

### Chapter Summary  

​	类型是C++编程的基础。

​	类型规定了其对象的存储要求和所能执行的操作。C++语言提供了一套基础内置类型，这些类型与机器硬件密切相关。类型还分为非常量和常量，一个常量对象必须初始化，而且一旦初始化就不能再改变。此外还可以定义复合类型，比如指针和引用等。复合类型的定义以其他类型为基础。

​	C++语言允许用户以类的形式自定义类型。C++库通过类提供了一套高级抽象类型。如输入输出和string等。

### Defined Terms

| 中文                 | 英文             | 含义                                                |
| -------------------- | ---------------- | --------------------------------------------------- |
| 常量表达式           | const expression | 能在编译时计算并获得结果的表达式                    |
|                      | constexpr        | 一种函数，用于代表一条常量表达式  6.5.2节会详细介绍 |
| preprocessor         | 预处理器         | 在C++编译过程中执行的一段程序                       |
| separate compilation | 分离式编译       | 把程序分割为多个单独文件的能力                      |
|                      |                  |                                                     |
|                      |                  |                                                     |
|                      |                  |                                                     |



## Chapter 3 Strings, Vectors, and Arrays

除了内置类型，标准库提供了一些具有更高级性质的类型。

string 表示可变长的字符序列。

vector 存放的是某种给定类型对象的可变长序列。

array（内置数组类） 数组的实现与硬件密切相关

### 3.1 Namespace using Declarations

命名空间

最安全的方法就是使用using 声明，18.2.2 会介绍另一种方法。

使用`using`声明后就无须再通过专门的前缀去获取所需的名字了。

```c++
using std::cout;
```

程序中使用的每个名字都需要用独立的`using`声明引入。

头文件中通常不应该包含`using`声明。因为头文件里有了这个声明，所有含有这个头文件的文件都会有，可能会造成命名冲突。

### 3.2 Library string Type

#### 3.2.1 Defining and Initializing strings

初始化`string`最常见的的方式：

![](CPP_Primer_5th.assets/3-1.png)

##### 直接初始化和拷贝初始化

如果使用等号初始化一个变量，实际上执行的是拷贝初始化（copy initialization），编译器把等号右侧的初始值拷贝到新创建的对象中去。

如果不使用等号，则执行的是直接初始化（direct initialization）。

初始值只有一个时，使用两种方法都可以，但是如果初始化的参数有多个，那么一般来说只能用直接初始化的形式。非要用拷贝初始化也得显式地创建一个临时对象用于拷贝。

```c++
string s7(10,'c');
string s8 = string (10,'d'); //可读性差，也没什么优势
```



#### 3.2.2 Operations on strings

`string`的大多数操作：

![](CPP_Primer_5th.assets/3-2.png)

##### 读写string

在执行读取操作时，`string`对象会自动忽略开头的空白（空格符、换行符、制表符等）并从第一个真正的字符开始读取，直到遇见下一处空白为止。

##### 使用getline读取一整行

使用`getline`函数可以读取一整行字符（包括输入时的空白符）。该函数只要遇到**换行符**就结束读取并返回结果，如果输入的开始就是一个换行符，则得到空`string`。触发`getline`函数返回的那个换行符实际上被丢弃掉了，得到的`string`对象中并不包含该换行符。

##### string的empty和size操作

`empty`会返回一个字符串是否为空的bool值。

`size`函数返回`string`对象的长度，返回值是`string::size_type`类型，这是一种无符号类型。要使用`size_type`，必须先指定它是由哪种类型定义的。

如果一个表达式中已经有了`size`函数就不要再使用`int`了，这样可以避免混用`int`和`unsigned int`可能带来的问题。因为负数会被转化为很大的无符号值。

##### 比较string

逐位比较，且大小写敏感。

- 长度不同，且短的字符每个字符都与长字符对应位置长度相同，那么短的string小于较长string
- 如果两个string对象在某些对应的位置上不一致，则string对象比较的结果其实是string对象中第一对相异字符比较结果

![image-20220609143926654](CPP_Primer_5th.assets/image-20220609143926654.png)

##### string 的加法

- 两个string相加

- 字面值和string相加

  编译器允许我们使用并非所需类型来实现同样的效果，前提是这种类型可以自动转换为所需的类型。因为标准库允许把字符字面值和字符串字面值转换为string对象。所以可以在用字符串的地方用这些字面值。

当把`string`对象和字符字面值及字符串字面值混合在一条语句中使用时，必须确保每个加法运算符两侧的运算对象中至少有一个是`string`。

```c++
string s4 = s1 + ", ";          // ok: adding a string and a literal
string s5 = "hello" + ", ";     // error: no string operand
string s6 = s1 + ", " + "world";    // ok: each + has a string operand
```

而字面值和字面值是不能直接相加的。

```c++
string s7 = ("hello" + ",") + s2; //error
```

需要注意的是，为了与C兼容，C++语言中的字符串字面值并不是标准库`string`的对象。

#### 3.2.3 Dealing with the Characters in a string

##### string操作头文件

头文件`cctype`中的字符操作函数：

![](CPP_Primer_5th.assets/3-3.png)

建议使用C++版本的C标准库头文件。C语言中名称为`name.h`的头文件，在C++中则被命名为`cname`。

##### string 与 for循环

C++11提供了范围`for`（range for）语句，可以遍历给定序列中的每个元素并执行某种操作。

```c++
for (declaration : expression)
    statement
```

`expression`部分是一个对象，用于表示一个序列。`declaration`部分负责定义一个变量，该变量被用于访问序列中的基础元素。每次迭代，`declaration`部分的变量都会被初始化为`expression`部分的下一个元素值。

一般来说我们会用auto来定义元素类型。

```c++
string str("some string");
// print the characters in str one character to a line
for (auto c : str)      // for every char in str
    cout << c << endl;  // print the current character followed by a newline
```

如果想在范围`for`语句中改变`string`对象中字符的值，必须把循环变量定义成引用类型。

```c++
string str("some string");
for (auto &c : str)      // for every char in str
    c = toupper(c);
cout<<str<<endl;

```

##### 只处理string内的一部分字符？

想要访问string对象中的单个字符有两种方式：一种是使用下标，另外一种是迭代器（3.4 和 第九章介绍）

下标运算符`[]`接收的输入参数是`string::size_type`类型的值，表示要访问字符的位置，返回值是该位置上字符的引用。

下标数值从0记起，范围是0至`size - 1`。使用超出范围的下标将引发不可预知的后果。

C++标准并不要求标准库检测下标是否合法。但是编程时需要时时刻刻注意这一点。

编程时可以把下标的类型定义为相应的`size_type`，这是一种无符号数，可以确保下标不会小于0，此时代码只需要保证下标小于`size`的值就可以了。另一种确保下标合法的有效手段就是使用范围`for`语句。



### 3.3 Library vector Type

标准库类型`vector`表示对象的集合，也叫做容器（container）（第二部分会对这有更一步的讲解），定义在头文件`vector`中。`vector`中所有对象的类型都相同，每个对象都有一个索引与之对应并用于访问该对象。

> 模板本身不是类或函数，相反可以将模板看做为编译器生成类或函数编写的一份说明。编译器根据模板创建类或函数的过程称之为实例化(instantiation)，当使用模板时，需要指出编译器应把类或类型实例化为何种类型。

`vector`是模板（template）而非类型，由`vector`生成的类型必须包含`vector`中元素的类型，如`vector<int>`。

因为引用不是对象，所以不存在包含引用的`vector`。

在早期的C++标准中，如果`vector`的元素还是`vector`，定义时必须在外层`vector`对象的右尖括号和其元素类型之间添加一个空格，如`vector<vector<int> >`。但是在C++11标准中，可以直接写成`vector<vector<int>>`，不需要添加空格。

#### 3.3.1 Defining and Initializing vectors

定义`vector`对象的常用方法：

![表3-4](CPP_Primer_5th.assets/3-4.png)

初始化`vector`对象时如果使用圆括号，可以说提供的值是用来构造（construct）`vector`对象的；如果使用的是花括号，则是在列表初始化（list initialize）该`vector`对象。

> 列表初始化
>
> C++ 提供初始化方法可以相互等价使用，但也有一些例外情况。
>
> - 使用拷贝初始化时（=），只能提供一个初始值
> - 如果提供的是一个类内初始值，则只能使用拷贝初始化或使用花括号的形式初始化
> - 如果提供的初始元素值的列表，则只能把初始值都放在花括号里进列表初始化

##### 值初始化

可以只提供`vector`对象容纳的元素数量而省略初始值，此时会创建一个值初始化（value-initialized）的元素初值，并把它赋给容器中的所有元素。这个初值由`vector`对象中的元素类型决定。

这种初始化有两个特殊限制，其一，有些类要求必须明确地提供初始值，或vector对象不支持默认初始化，我们就必须设置初始的元素值；其二，如果只提供了元素的数量而没有设定初始值，只能使用直接初始化。

```c++
vector<int> vi = 10; // error
```

##### 列表初始化还是元素数量？

有时候初始化的真实含义需要通过圆括号还是花括号来区分

```c++
vector<int>v1(10,1); // 十个元素
vector<int>v1{10,1}; // 两个元素
```

- 如果我们使用的是圆括号，那么我们可以说提供的值是用来构造vector对象的。
  - 一个元素-容器大小
  - 两个元素-容量，初始值
- 如果我们使用的是花括号，那么我们可以说是想要列表初始化，初始化时会尽可能把花括号内的值当成是元素初始值的列表来处理。如果想要列表初始化，那么花括号里的值必须与元素类型相同，确认无法执行列表初始化后，编译器会尝试用默认值初始化对象。

#### 3.3.2 Adding Elements to a vector

push_back()

> vector 对象能高速增长
>
> 开始时创建空的vector对象，运行时动态添加元素，【9.4】节还会对其有更一步的描述。

> C++支持能高效地朝vector对象中添加元素，但是这也要求我们确保写的循环正确无误，特别是在循环可能改变vector对象容量时。

#### 3.3.3 Other vector Operations

![](CPP_Primer_5th.assets/3-5.png)

`size`函数返回`vector`对象中元素的个数，返回值是由`vector`定义的`size_type`类型。`vector`对象的类型包含其中元素的类型。

```c++
vector<int>::size_type  // ok
vector::size_type       // error
```

##### 不能用下标形式添加元素

`vector`和`string`对象的下标运算符只能用来访问已经存在的元素，而不能用来添加元素。

```c++
vector<int> ivec;   // empty vector
for (decltype(ivec.size()) ix = 0; ix != 10; ++ix)
{
    ivec[ix] = ix;  // disaster: ivec has no elements
    ivec.push_back(ix); // ok: adds a new element with value ix
}
```

### 3.4 Introducing Iterators 迭代器

迭代器的作用和下标类似，但是更加通用。所有标准库容器都可以使用迭代器，但是其中只有少数几种同时支持下标运算符。

类似指针，迭代器有有效无效的区别。有效的迭代器指向某个元素或指向容器中尾元素的下一位置，其他所有情况都算无效。

#### 3.4.1 Using Iterators

定义了迭代器的类型都拥有`begin`和`end`两个成员函数。`begin`函数返回指向第一个元素的迭代器，`end`函数返回指向容器“尾元素的下一位置（one past the end）”的迭代器，通常被称作尾后迭代器（off-the-end iterator）或者简称为尾迭代器（end iterator）。尾后迭代器仅是个标记，表示程序已经处理完了容器中的所有元素。

迭代器一般为`iterator`类型。具体是什么类型我们一般并不能确定。

```c++
// b denotes the first element and e denotes one past the last element in ivec
auto b = ivec.begin(), e = ivec.end();    // b and e have the same type
```

如果容器为空，则`begin`和`end`返回的是同一个迭代器，都是尾后迭代器。

标准容器迭代器的运算符：

![](CPP_Primer_5th.assets/3-6.png)

- 类似指针，也可以通过解引用来获取它所指示的元素，执行解引用的迭代器必须合法且确实指示着某个元素。试图解引用一个非法迭代器或尾后迭代器都是未被定义的行为。因为`end`返回的迭代器并不实际指向某个元素，所以不能对其进行递增或者解引用的操作。

- 在`for`或者其他循环语句的判断条件中，最好使用`!=`而不是`<`。所有标准库容器的迭代器都定义了`==`和`!=`，但是只有其中少数同时定义了`<`运算符。所以为了泛型编程以及日常使用考虑，养成使用迭代器和`!=`的习惯。

```c++
for (auto it = s.begin(); it != s.end() && !isspace(*it);++it)
```

- 迭代器也有iterator和const_iterator的类型区分，如果`vector`或`string`对象是常量，则只能使用`const_iterator`迭代器，该迭代器只能读元素，不能写元素。

- `begin`和`end`返回的迭代器具体类型由对象是否是常量决定，如果对象是常量，则返回`const_iterator`；如果对象不是常量，则返回`iterator`。

  ```c++
  vector<int> v;
  const vector<int> cv;
  auto it1 = v.begin();   // it1 has type vector<int>::iterator
  auto it2 = cv.begin();  // it2 has type vector<int>::const_iterator
  ```

  C++11新增了`cbegin`和`cend`函数，不论`vector`或`string`对象是否为常量，都返回`const_iterator`迭代器。

- 箭头运算符->

  箭头运算符将解引用和成员访问两个操作结合在一起。省略了步骤，还不比考虑什么结合优先级的问题。【4.1.2】

  ```c++
  it->mem; == (*it).men;
  ```

- 某些vector对象的操作会使迭代器失效

  不能在范围for循环中向vector对象添加元素；任何一种可能改变vector对象容量的操作，也会是vector迭代器失效。【9.3.6】会解释为什么失效

谨记：但凡是使用了迭代器的循环体，都不要向迭代器所属的容器添加元素。

#### 3.4.2 Iterator Arithmetic 迭代器运算

`vector`和`string`迭代器支持的操作：

![](CPP_Primer_5th.assets/3-7.png)

两个有效的迭代器可以相减，所得结果是两个迭代器的距离，类型名为difference_type的带符号整型数。string 和vector都支持这个类型。

### 3.5 Arrays

与vector类型不同，数字大小固定，不能随意向数组中随意添加元素。

#### 3.5.1 Defining and Initializing Built-in Arrays

数组是一种复合类型，声明形式为`a[d]`，其中`a`是数组名称，`d`是数组维度（dimension）。维度必须是一个大于0的常量表达式。

默认情况下，数组的元素被默认初始化【2.2.1】。

定义数组的时候必须指定数组的类型，不允许用`auto`关键字由初始值列表推断类型。

类似vector，数组的元素必须为对象，因此不存在引用的数组。

##### 显式初始化数组元素

如果定义数组时提供了元素的初始化列表，则允许省略数组维度，编译器会根据初始值的数量计算维度。但如果显式指明了维度，那么初始值的数量不能超过指定的大小。如果维度比初始值的数量大，则用提供的值初始化数组中靠前的元素，剩下的元素被默认初始化。

```c++
const unsigned sz = 3;
int ia1[sz] = {0,1,2};  // array of three ints with values 0, 1, 2
int a2[] = {0, 1, 2};   // an array of dimension 3
int a3[5] = {0, 1, 2};  // equivalent to a3[] = {0, 1, 2, 0, 0}
string a4[3] = {"hi", "bye"};   // same as a4[] = {"hi", "bye", ""}
int a5[2] = {0,1,2};    // error: too many initializers
```

##### 字符数组的特殊性

可以用字符串字面值初始化字符数组，但字符串字面值结尾处的空字符也会一起被拷贝到字符数组中。

```c++
char a1[] = {'C', '+', '+'};        // list initialization, no null
char a2[] = {'C', '+', '+', '\0'};  // list initialization, explicit null
char a3[] = "C++";      // null terminator added automatically
const char a4[6] = "Daniel";    // error: no space for the null!
```

字符串会自动添加表示字符串结束的空字符，所以要注意留足空间。

##### 数组不允许拷贝和赋值

不能用一个数组初始化或直接赋值给另一个数组。

有的编译器支持，这就是所谓的编译器拓展（compiler extension），但是一般来说最好避免使用非标准特性。

##### 理解复杂的数组声明

从数组的名字开始由内向外阅读有助于理解复杂数组声明的含义。

```c++
int *ptrs[10];              // ptrs is an array of ten pointers to int
int &refs[10] = /* ? */;    // error: no arrays of references
int (*Parray)[10] = &arr;   // Parray points to an array of ten ints
int (&arrRef)[10] = arr;    // arrRef refers to an array of ten ints
```

#### 3.5.2 Accessing the Elements of an Array

数组下标通常被定义成`size_t`类型，这是一种机器相关的无符号类型，可以表示内存中任意对象的大小。`size_t`定义在头文件`cstddef`中。这个文件是`stddef.h`的c++版本

大多数常见的安全问题都源于缓冲区溢出错误。当数组或其他类似数据结构的下标越界并试图访问非法内存区域时，就会产生此类错误。这种错误除了小心检查，加强测试之外，没有什么好的方法。即使通过编译执行也不能证明不会发生这类错误。

#### 3.5.3 Pointers and Arrays

使用数组时，编译器一般会把它转化为指针。

而数组有个特性，在大多数表达式中，使用数组类型的对象其实是在使用一个指向该数组首元素的指针。

当使用数组作为一个`auto`变量的初始值时，推断得到的类型是指针而非数组。但`decltype`关键字【2.5.3】不会发生这种转换，直接返回数组类型。

```c++
int ia[] = {0,1,2,3,4,5,6,7,8,9};   // ia is an array of ten ints
auto ia2(ia);   // ia2 is an int* that points to the first element in ia
ia2 = 42;       // error: ia2 is a pointer, and we can't assign an int to a pointer
auto ia2(&ia[0]);   // now it's clear that ia2 has type int*
// ia3 is an array of ten ints
decltype(ia) ia3 = {0,1,2,3,4,5,6,7,8,9};
ia3 = p;    // error: can't assign an int* to an array
ia3[4] = i;     // ok: assigns the value of i to an element in ia3
```

##### 指针也可以用作迭代器

为了实现迭代器的效果，我们需要数组的首地址以及尾元素后一位的地址。

```c++
int a[10] = {...};
int *start = a;
int *end = a[10];
for(int *p = start;p!=end;++p){
    cout<<*p<<endl;
}
```

> 建议使用++i而不是i++，少一步拷贝。

##### 标准库函数begin和end.

上面的使用很容易出错。为此C++11在头文件`iterator`中定义了两个名为`begin`和`end`的函数，功能与容器中的两个同名成员函数类似，参数是一个数组。

```c++
int ia[] = {0,1,2,3,4,5,6,7,8,9};   // ia is an array of ten ints
int *beg = begin(ia);   // pointer to the first element in ia
int *last = end(ia);    // pointer one past the last element in ia
```

- 一个指针如果指向了某种内置类型数组的尾元素的“下一位置”，则其具备end()类似的功能，特别注意，尾后指针不能用于解引用和递增操作。

##### 指针运算

迭代器操作指针都能做。

两个指针相减的结果类型是`ptrdiff_t`，这是一种定义在头文件`cstddef`中的带符号类型。

##### 下标与指针

只要指针指向的是数组中的元素(或尾指针下一个位置)，都可以进行下标操作。

```c++
int *p = &ia[2];
int j = p[1];	== ia[3]
int k = p[-2];  == ia[0]
```

标准库类型限定使用的下标必须是无符号类型，而内置的下标运算无此要求。

内置的下标运算可以处理负值，当然指的元素必须有效。

#### 3.5.4 C-Style Character Strings

C++标准支持C风格字符串，但是最好不要在C++程序中使用它们。对大多数程序来说，使用标准库`string`要比使用C风格字符串更加安全和高效。

字符串字面值是一种通用结构的实例，这种结构是C++由C继承而来的C风格字符串--将字符串存放在字符数组中，并以空字符结束（null terminated）。这不是一种类型，而是一种为了表达和使用字符串而形成的书写方法。

##### C标准库String函数

C风格字符串的函数，被定义在cstring头文件中，cstring是string.h的c++版本

![](CPP_Primer_5th.assets/3-9.png)

C风格字符串函数不负责验证其参数的正确性，传入此类函数的指针必须指向以空字符作为结尾的数组。

##### 比较字符串

标准string 对象可以直接进行比较，但是如果用在c风格字符串上，实际比较的将会是指针而不是字符串，如果想比较需要用strcmp；

##### 目标字符串的大小由调用者指定

不同于c++ 标准string类可以直接将两个字符串相加，c风格的字符串相加需要使用strcmp和strcat，将两个字符串赋给另一个有足够空间的C风格字符串。而这个空间并不容易估计准确，充满了风险。

#### 3.5.5 Interfacing to Older Code

##### 混用string对象和C风格字符串

任何出现字符串字面值的地方都可以用以空字符结束的字符数组来代替：

- 允许使用以空字符结束的字符数组来初始化`string`对象或为`string`对象赋值。

- 在`string`对象的加法运算中，允许使用以空字符结束的字符数组作为其中一个运算对象（不能两个运算对象都是）。

- 在`string`对象的复合赋值运算中，允许使用以空字符结束的字符数组作为右侧运算对象。

不能用`string`对象直接初始化指向字符的指针。为了实现该功能，`string`提供了一个名为`c_str`的成员函数，返回`const char*`类型的指针，指向一个以空字符结束的字符数组，数组的数据和`string`对象一样。

```c++
string s("Hello World");    // s holds Hello World
char *str = s;  // error: can't initialize a char* from a string
const char *str = s.c_str();    // ok
```

针对`string`对象的后续操作有可能会让`c_str`函数之前返回的数组失去作用，如果程序想一直都能使用其返回的数组，**最好将该数组重新拷贝一份**。

##### 使用数组初始化vector对象

可以使用数组来初始化`vector`对象，但是需要指明要拷贝区域的首元素地址和尾后地址。

```c++
int int_arr[] = {0, 1, 2, 3, 4, 5};
// ivec has six elements; each is a copy of the corresponding element in int_arr
vector<int> ivec(begin(int_arr), end(int_arr));
```

在新版本的C++程序中应该尽量使用`vector`、`string`和迭代器，避免使用内置数组、C风格字符串和指针。

### 3.6 Multidimensional Arrays

C++中的多维数组其实就是数组的数组。当一个数组的元素仍然是数组时，通常需要用两个维度定义它：一个维度表示数组本身的大小，另一个维度表示其元素（也是数组）的大小。通常把二维数组的第一个维度称作行，第二个维度称作列。

##### 多维数组的初始化

多维数组初始化的几种方式：

初始化时的内嵌的花括号并不是必须的。

```c++
int ia[3][4] =
{   // three elements; each element is an array of size 4
    {0, 1, 2, 3},   // initializers for the row indexed by 0
    {4, 5, 6, 7},   // initializers for the row indexed by 1
    {8, 9, 10, 11}  // initializers for the row indexed by 2
};
// equivalent initialization without the optional nested braces for each row
int ib[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
// explicitly initialize only element 0 in each row
int ic[3][4] = {{ 0 }, { 4 }, { 8 }};//初始化每行首元素
// explicitly initialize row 0; the remaining elements are value initialized
int id[3][4] = {0, 3, 6, 9};//初始化第一行
```

##### 多维数组的下标引用

可以使用下标访问多维数组的元素，数组的每个维度对应一个下标运算符。

- 如果表达式中下标运算符的数量和数组维度一样多，则表达式的结果是给定类型的元素。
- 如果下标运算符数量比数组维度小，则表达式的结果是给定索引处的一个内层数组。

```c++
// assigns the first element of arr to the last element in the last row of ia
ia[2][3] = arr[0][0][0];
int (&row)[4] = ia[1];  // binds row to the second four-element array in ia
```

##### 使用范围for语句处理多维数组

使用范围`for`语句处理多维数组时，为了避免数组被自动转换成指针【3.5.3】，语句中的外层循环控制变量必须声明成引用类型。

```c++
for (const auto &row : ia)  // for every element in the outer array
    for (auto col : row)    // for every element in the inner array
        cout << col << endl;
```

如果`row`不是引用类型，编译器初始化`row`时会自动将数组形式的元素转换成指向该数组内首元素的指针，这样得到的`row`就是`int*`类型，而之后的内层循环则试图在一个`int*`内遍历，程序将无法通过编译。

```c++
for (auto row : ia)
    for (auto col : row)
```

**使用范围`for`语句处理多维数组时，除了最内层的循环，其他所有外层循环的控制变量都应该定义成引用类型。如果要对元素进行改写，最内层也得用引用**

##### 指针和多维数组

因为多维数组实际上是数组的数组，所以由多维数组名称转换得到的指针指向第一个内层数组的指针。

```c++
int ia[3][4];       // array of size 3; each element is an array of ints of size 4
int (*p)[4] = ia;   // p points to an array of four ints
p = &ia[2];         // p now points to the last element in ia
```

声明指向数组类型的指针时，必须带有圆括号。

```c++
int *ip[4];     // array of pointers to int
int (*ip)[4];   // pointer to an array of four ints
```

使用`auto`和`decltype`能省略复杂的指针定义。

```c++
// print the value of each element in ia, with each inner array on its own line
// p points to an array of four ints
for (auto p = ia; p != ia + 3; ++p)
{
    // q points to the first element of an array of four ints; that is, q points to an int
    for (auto q = *p; q != *p + 4; ++q)
        cout << *q << ' ';
    cout << endl;
}
```

使用`begin`和`end`也能实现相同的功能，看起来还更简单鲁棒。

```c
for (auto p = begin(ia);p != end(ia);++p){
    for(auto q = begin(*p);q != end(*p);++q){
        cout<<*q<<" ";
    }
	cout<<endl;
}
```

##### 类型别名简化多维数组的指针

```c++
using int_array = int[4];
typedef int int_array[4];
```

两者相同。

> 解释typedef int int_array[4];
> 关键字typedef用来自定义数据类型，这是所有教材都这样讲的，但不要理解为新创建了一个数据类型，而是将已有的一个类型赋予个新名称而已，即起一个别名。
> 具体对这个语句来说，别名就是：int_array。而[4]不属于名字，而表示一种已有的数据类型，即：给一个大小为4的int数组取一个别名为int_array。
> 那如何知道是这样定义的呢？很简单。
> 首先，int a[4];这可是常见的定义格式。再在其前面添加关键字typedef，变成 typedef int a[4];最后将数组名a改为自己想要的一个别名int_array即可。注意：原本的a本意是数组名，属于变量范畴，而int_array则是新数据类型名（即别名），本质不一样了哦。祥见谭浩强的那本经典教材。

> **typedef常见用法**
>
> https://www.shuzhiduo.com/A/D85476oWJE/
>
> 1.常规变量类型定义
>
> 例如：typedef unsigned char uchar
> 描述：uchar等价于unsigned char类型定义 uchar c声明等于unsigned char c声明
>
> 2.数组类型定义
> 例如： typedef int array[2];
> 描述： array等价于 int [2]定义; array a声明等价于int a[2]声明
>
> 扩展： typedef int array[M][N];
> 描述： array等价于 int [M][N]定义; array a声明等价于int a[M][N]声明
>
> 3.指针类型定义
> 例如： typedef int *pointer;
> 描述： pointer等价于 int *定义;pointer p声明等价于int *p声明
>
> 例如： typedef int *pointer[M];
> 描述： pointer等价于 int *[M]定义 pointer p声明等价于int *p[M]声明明
>
> 4.函数地址说明
> 描述：C把函数名字当做函数的首地址来对待，我们可以使用最简单的方法得到函数地址
> 例如： 函数:int func(void); unsigned long funcAddr=(unsigned long)func， funcAddr的值是func函数的首地址
>
> 5.函数声明
> 例如： typedef int func(void); func等价于 int (void)类型函数
> 描述1： func f声明等价于 int f(void)声明，用于文件的函数声明
> 描述2： func *pf声明等价于 int (*pf)(void)声明，用于函数指针的生命，见下一条
>
> 6.函数指针
> 例如： typedef int (*func)(void)
> 描述： func等价于int (*)(void)类型
> func pf等价于int (*pf)(void)声明，pf是一个函数指针变量
>
> 7.识别typedef的方法：
> a).第一步。使用已知的类型定义替代typdef后面的名称,直到只剩下一个名字不识别为正确
> 如typedef u32 (*func)(u8);
> 从上面的定义中找到 typedef __u32 u32;typedef __u8 u8
> 继续找到 typedef unsigned int __u32;typedef unsigned char __u8;
> 替代位置名称 typedef unsigned int (*func)(void);
> 现在只有func属于未知。
> b).第二步.未知名字为定义类型，类型为取出名称和typedef的所有部分，如上为
> func等价于unsigned unsigned int (*)(unsigned char);
> c).第三部.定义一个变量时，变量类型等价于把变量替代未知名字的位置所得到的类型
> func f等价于unsigned unsigned int (*f)(unsigned char)



### Chapter Summary  

- `string`和 `vector`是最重要的两种标准库类型，string对象是一个可变长的字符序列，vector对象是一组同类型对象的容器。
- 迭代器允许对容器中的对象进行间接访问，对于string对象和vector对象来说，可以通过迭代器访问元素或者在元素间移动。
- 数组和指向数组元素的指针在一个较低层次上实现了与标准库string和vector类似的功能。一般来说尽量使用标准库提供的类型，之后在考虑C++语言内置的低层的替代品数组或指针。

### Defined Terms

| 中文       | 英文                  | 含义                                                         |
| ---------- | --------------------- | ------------------------------------------------------------ |
| 缓冲器溢出 | buffer overflow       | 一种严重的程序故障，主要原因是试图通过一个越界的索引访问容器内容，容器类型包括string、vector、数组等。 |
| 拷贝初始化 | copy initialization   | 使用赋值号的初始化形式，新创建的对象是初始值的一个副本       |
| 直接初始化 | direct initialization | 不使用赋值号的初始化形式                                     |
| 实例化     | instantiation         | 编译器生成一个指定的模板类或函数的过程                       |
|            | difference_type       | 由string和vector定义的一种带符号整数类型，表示两个迭代器之间的距离。 |
|            | size_type             | 由string和vector定义的一种无符号整数类型，能存放下任意string对象或vector对象的大小 |
|            | prtdiff_t             | cstddef头文件定义的一种与机器实现有关的带符号整数类型，空间足够大，足以表示数组中任意两个指针之间的距离 |
|            | size_t                | cstddef头文件定义的一种与机器实现有关的带符号整数类型，空间足够大，足以表示任意数组的大小 |





## Chapter 4 Expressions 表达式
### 4.1 Fundamentals

表达式（expression）由一个或多个运算对象（operand）组成，对表达式求值将得到一个结果（result）。字面值和变量是最简单的表达式，其结果就是字面值和变量的值。

#### 4.1.1 Basic Concepts

C++定义了一元运算符（unary operator）和二元运算符（binary operator）。除此之外，还有一个作用于三个运算对象的三元运算符。函数调用`()`也是一种特殊的运算符，它对运算对象的数量没有限制。

另外一些符号既可以作为一元运算符，也可以作为二元运算符，诸如*，一元它是解引用，二元它是乘法。具体是什么取决于上下文。

##### 运算对象转换

表达式求值过程中，小整数类型（如`bool`、`char`、`short`等）通常会被提升（promoted）为较大的整数类型，主要是`int`。【4.11】

##### 重载运算符

C++定义了运算符作用于内置类型和复合类型的运算对象时所执行的操作。当运算符作用于类类型的运算对象时，用户可以自定义其含义，这被称作运算符重载（overloaded operator）。

我们使用重载运算符时，包括运算对象的类型和返回值的类型，都是由该运算符定义的，但是运算对象的个数，运算符的优先级和结合律都是无法改变的。

##### 左值和右值

C++的表达式分为右值（rvalue）和左值（lvalue）。

- 当一个对象被用作右值的时候，用的是对象的值（内容）；

- 当对象被用作左值时，用的是对象的身份（在内存中的位置）-- 地址。

  **一个重要原则**：需要右值的地方可以用左值代替，反之则不行。

> ## 1、左值和右值的概念
>
> C++中左值（lvalue）和右值（rvalue）是比较基础的概念，虽然平常几乎用不到，但C++11之后变得十分重要，它是理解 move/forward 等新语义的基础。
>
> 左值与右值这两个概念是从 C 中传承而来的，左值指既能够出现在等号左边，也能出现在等号右边的变量；右值则是只能出现在等号右边的变量。
>
> ```cpp
> int a; // a 为左值
> a = 3; // 3 为右值
> ```
>
> - 左值是可寻址的变量，有持久性；
> - 右值一般是不可寻址的常量，或在表达式求值过程中创建的无名临时对象，短暂性的。
>
> 左值和右值主要的区别之一是左值可以被修改，而右值不能。
>
> ## 2、左值引用和右值引用
>
> - 左值引用：引用一个对象；
> - 右值引用：就是必须绑定到右值的引用，C++11中右值引用可以实现“移动语义”，通过 && 获得右值引用。
>
> ```cpp
> int x = 6; // x是左值，6是右值
> int &y = x; // 左值引用，y引用x
> 
> int &z1 = x * 6; // 错误，x*6是一个右值
> const int &z2 =  x * 6; // 正确，可以将一个const引用绑定到一个右值
> 
> int &&z3 = x * 6; // 正确，右值引用
> int &&z4 = x; // 错误，x是一个左值
> ```
>
> 右值引用和相关的移动语义是C++11标准中引入的最强大的特性之一，通过std::move()可以避免无谓的复制，提高程序性能。

一些需要使用左值的运算符：

- 赋值运算符需要一个非常量左值作为其左侧运算对象，返回结果也是一个左值。

- 取地址符作用于左值运算对象，返回指向该运算对象的指针，该指针是一个右值。

- 内置解引用运算符、下标运算符、迭代器解引用运算符、`string`和`vector`的下标运算符都返回左值。

- 内置类型和迭代器的递增递减运算符作用于左值运算对象。前置版本返回左值，后置版本返回右值。



如果`decltype`作用于一个求值结果是左值的表达式，会得到引用类型。

`decltype((variable))`一定会返回引用 `decltype(variable)`只有variable为引用类型会返回引用

```c++
#include <iostream>
#include<typeinfo>
using namespace std;
int main()
{
    int m = 6;
    int* p = &m;
    int& n = m;
    decltype(*p) a= *p;
    decltype(&p) b;
    cout << "a的类型是" << typeid(a).name() << endl;
    cout << "b的类型是" << typeid(b).name() << endl;
    cout << "n的类型是" << typeid(n).name() << endl;
    std::cout << "Hello World!\n";
}
/*
a的类型是int
b的类型是int * *
n的类型是int
Hello World!
*/
//还学习到typeid会返回引用指向的类型，不会返回啥reference的。不过visual studio 的智能提示能看到。
```

##### :sunny:关于decltype推导

> ## MSDN
>
> 编译器使用以下规则来确定 *表达式* 参数的类型。
>
> - 如果 *表达式* 参数是标识符或 [类成员访问](https://docs.microsoft.com/zh-cn/cpp/cpp/member-access-operators-dot-and?view=msvc-170)， `decltype(expression)` 则为由 *表达式*命名的实体的类型。 如果没有此类实体或 *表达式* 参数为一组重载函数命名，编译器将生成错误消息。
> - 如果 *表达式* 参数是对函数或重载运算符函数的调用， `decltype(expression)` 则为函数的返回类型。 将忽略重载运算符两边的括号。
> - 如果 *表达式* 参数是 [右值](https://docs.microsoft.com/zh-cn/cpp/cpp/lvalues-and-rvalues-visual-cpp?view=msvc-170)， `decltype(expression)` 则表示 *表达式*的类型。 如果*表达式*参数是[左值](https://docs.microsoft.com/zh-cn/cpp/cpp/lvalues-and-rvalues-visual-cpp?view=msvc-170)，`decltype(expression)`则为对*表达式*类型的[左值引用](https://docs.microsoft.com/zh-cn/cpp/cpp/lvalue-reference-declarator-amp?view=msvc-170)。



> ## decltype推导四规则
>
> 1. 如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype（e）就是e所命名的实体的类型。此外，如果e是一个被重载的函数，则会导致编译错误。
> 2. 否则 ，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
> 3. 否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
> 4. 否则，假设e的类型是T，则decltype（e）为T。

##### :sunny:关于值的类型

> **在前面**
>
>    C++中有“左值”、“右值”的概念，C++11以后，又有了“左值”、“纯右值”、“将亡值”的概念。关于这些概念，许多资料上都有介绍，本文在拾人牙慧的基础上又加入了一些自己的一些理解，同时提出了一些需要读者特别注意的地方，主要目的有二：
>    1.尽可能地将这些概念介绍清楚。
>    2.为后续介绍完美转发和移动语义做好铺垫。
>
> **正文**
>
> 一、表达式
>
> ​    要说清“三值”，首先要说清表达式。
>
> ​    定义
> ​      由运算符(operator)和运算对象(operand)①构成的计算式（类似于数学上的算术表达式）。
>    举例
> ​      字面值(literal)和变量(variable)是最简单的表达式，函数的返回值也被认为是表达式。
>
> 二、值类别
>
> ​    表达式是可求值的，对表达式求值将得到一个结果(result)。这个结果有两个属性：类型和值类别（value categories）。下面我们将详细讨论表达式的值类别②。
>
> ​    在c++11以后，表达式按值类别分，必然属于以下三者之一：左值(left value,lvalue)，将亡值(expiring value,xvalue)，纯右值(pure rvalue,pralue)。其中，左值和将亡值合称泛左值(generalized lvalue,glvalue)，纯右值和将亡值合称右值(right value,rvalue)。见下图
>
>  
>
> ![img](https://images2015.cnblogs.com/blog/642223/201603/642223-20160314175051818-1679937642.png)
>
>  
>
>    有一点需要说明，严格来讲，“左值”是表达式的结果的一种属性，但更为普遍地，我们通常用“左值”来指代左值表达式（正如上边一段中做的那样）。所谓左值表达式，就是指求值结果的值类别为左值的表达式。通常我们无需区分“左值”指的是前者还是后者，因为它们表达的是同一个意思，不会引起歧义。在后文中，我们依然用左值指代左值表达式。对于纯右值和将亡值，亦然。
>
> 三、详细说明
>
>    事实上，无论是左值、将亡值还是纯右值，我们目前都没有一个精准的定义。它们事实上表征了表达式的属性，而这种属性的区别主要体现在使用上，如能否做运算符的左操作数、能否使用移动语义（关于移动语义，在下的后续文章中会详细介绍）等。因此，从实际应用出发，我们首先需要做到的是：给定一个表达式，能够正确地判断出它的值类别。为了使读者能够做到这一点，在下采取了一个实际的方式：先对各个值类别的特征加以描述，然后指出常见的表达式里边，哪些属于该类别。
>
> **左值**
>
> 描述
>    **能够用&取地址的表达式是左值表达式。**
> 举例
>    函数名和变量名（实际上是函数指针③和具名变量，具名变量如std::cin、std::endl等）、返回左值引用的函数调用、前置自增/自减运算符连接的表达式++i/--i、由赋值运算符或复合赋值运算符连接的表达式(a=b、a+=b、a%=b）、解引用表达式*p、字符串字面值"abc"（关于这一点，后面会详细说明）等。
>
> **纯右值**
>
> 描述
>    满足下列条件之一：
>    1）本身就是赤裸裸的、纯粹的字面值，如3、false；
>    2）求值结果相当于字面值或是一个不具名的临时对象。
> 举例
>    除字符串字面值以外的字面值、返回非引用类型的函数调用、后置自增/自减运算符连接的表达式i++/i--、算术表达式（a+b、a&b、a<<b）、逻辑表达式（a&&b、a||b、~a）、比较表达式（a==b、a>=b、a<b）、取地址表达式（&a）等。
>
>    下面从上面的例子中选取若干典型详细说明左值和纯右值的判断。
>
>    1）++i是左值，i++是右值。
>    前者，对i加1后再赋给i，最终的返回值就是i，所以，++i的结果是具名的，名字就是i；而对于i++而言，是先对i进行一次拷贝，将得到的副本作为返回结果，然后再对i加1，由于i++的结果是对i加1前i的一份拷贝，所以它是不具名的。假设自增前i的值是6，那么，++i得到的结果是7，这个7有个名字，就是i；而i++得到的结果是6，这个6是i加1前的一个副本，它没有名字，i不是它的名字，i的值此时也是7。可见，++i和i++都达到了使i加1的目的，但两个表达式的结果不同。
>
>    2）解引用表达式*p是左值，取地址表达式&a是纯右值。
>    &(*p)一定是正确的，因为*p得到的是p指向的实体，&(*p)得到的就是这一实体的地址，正是p的值。由于&(*p)的正确，所以*p是左值。而对&a而言，得到的是a的地址，相当于unsigned int型的字面值，所以是纯右值。
>
>    3）a+b、a&&b、a`==`b都是纯右值
>    a+b得到的是不具名的临时对象，而a&&b和a`==`b的结果非true即false，相当于字面值。
>
> **将亡值**
>
> 描述
>    在C++11之前的右值和C++11中的纯右值是等价的。C++11中的将亡值是随着右值引用④的引入而新引入的。换言之，“将亡值”概念的产生，是由右值引用的产生而引起的，将亡值与右值引用息息相关。所谓的将亡值表达式，就是下列表达式：
>    1）返回右值引用的函数的调用表达式
>    2）转换为右值引用的转换函数的调用表达式
>    读者会问：这与“将亡”有什么关系？
>    在C++11中，我们用左值去初始化一个对象或为一个已有对象赋值时，会调用拷贝构造函数或拷贝赋值运算符来拷贝资源（所谓资源，就是指new出来的东西），而当我们用一个右值（包括纯右值和将亡值）来初始化或赋值时，会调用移动构造函数或移动赋值运算符⑤来移动资源，从而避免拷贝，提高效率（关于这些知识，在后续文章讲移动语义时，会详细介绍）。当该右值完成初始化或赋值的任务时，它的资源已经移动给了被初始化者或被赋值者，同时该右值也将会马上被销毁（析构）。也就是说，当一个右值准备完成初始化或赋值任务时，它已经“将亡”了。而上面1）和2）两种表达式的结果都是不具名的右值引用，它们属于右值（关于“不具名的右值引用是右值”这一点，后面还会详细解释）。又因为
>     1）这种右值是与C++11新生事物——“右值引用”相关的“新右值”
>     2）这种右值常用来完成移动构造或移动赋值的特殊任务，扮演着“将亡”的角色
>     所以C++11给这类右值起了一个新的名字——将亡值。
> 举例
>     std::move()、tsatic_cast<X&&>(x)（X是自定义的类，x是类对象，这两个函数常用来将左值强制转换成右值，从而使拷贝变成移动，提高效率，关于这些，后续文章中会详细介绍。）
> 附注
>    事实上，将亡值不过是C++11提出的一块晦涩的语法糖。它与纯右值在功能上及其相似，如都不能做操作符的左操作数，都可以使用移动构造函数和移动赋值运算符。当一个纯右值来完成移动构造或移动赋值任务⑥时，其实它也具有“将亡”的特点。一般我们不必刻意区分一个右值到底是纯右值还是将亡值。 
>
>    关于“三值”的大体介绍，就到此结束了。想要获知更加详细的内容，读者可以参考cppreference上的文章：
>    http://naipc.uchicago.edu/2015/ref/cppreference/en/cpp/language/value_category.html （精简版）  
>    和
>    http://en.cppreference.com/w/cpp/language/value_category （详细版）
>    文章对“三值”进行了详细地讲述，同时讲出了将左值和将亡值合称泛左值的原因（这是本文未详细讨论的），如两者都可以使用多态，都可以隐式转换成纯右值，都可以是不完全类型（[incomplete type](http://en.cppreference.com/w/cpp/language/type#Incomplete_type)）等。之所以不展开叙述，是因为在下实在举不出合适的代码来加以佐证。这里在下恳请各位读者不吝赐教。另外，关于文章（特别是详细版）中的一些观点，在下不敢苟同，篇幅原因，在下就不一一叙述了。
>
> 四、特别注意
>
> ​    最后，关于“三值”，有些地方需要大家特别注意。
>
>    1）字符串字面值是左值。
>
>    不是所有的字面值都是纯右值，字符串字面值是唯一例外。
>    早期C++将字符串字面值实现为char型数组，实实在在地为每个字符都分配了空间并且允许程序员对其进行操作，所以类似
>
> ```
> cout<<&("abc")<<endl;
> char *p_char="abc";//注意不是char *p_char=&("abc");
> ```
>
> 这样的代码都是可以编译通过的。
>     注意上面代码中的注释，"abc"可以直接初始化指针p_char，p_char的值为字符串"abc"的首字符a的地址。而&("abc")被编译器编译为const的指向数组的指针const char (*) [4]（之所以是4，是因为编译器会在"abc"后自动加上一个'\0'），它不能初始化char *类型，即使是const char *也不行。另外，对于char *p_char="abc";，在GCC编译器上,GCC4.9(C++14)及以前的版本会给出警告，在GCC5.3(C++14)及以后的版本则直接报错：ISO C++ forbids converting a string constant to 'char*'（ISO C++禁止string常量向char*转换）。但这并不影响“字符串字面值是左值”这一结论的正确性，因为cout<<&("abc")<<endl;一句在各个版本的编译器上都能编译通过，没有警告和错误。
>
> ​    2)具名的右值引用是左值，不具名的右值引用是右值。
>
>    见下例（例一）
>
> ```
> void foo(X&& x)
> {
>     X anotherX = x;
>    //后面还可以访问x
>  }
> ```
>
>    上面X是自定义类，并且，其有一个指针成员p指向了在堆中分配的内存；参数x是X的右值引用。如果将x视为右值，那么，X anotherX=x;一句将调用X类的移动构造函数，而我们知道，这个移动构造函数的主要工作就是将x的p指针的值赋给anotherX的p指针，然后将x的p指针置为nullptr。（后续文章讲移动构造函数时会详细说明）。而在后面，我们还可以访问x，也就是可以访问x.p，而此时x.p已经变成了nullptr，这就可能发生意想不到的错误。 
>
>    又如下例（例二）
>
> ```
> X& foo(X&& x)
> {
>      //对x进行一些操作
>      return x;
> }
> 
> //调用
> foo(get_a_X());//get_a_X()是返回类X的右值引用的函数
> ```
>
> [![复制代码](https://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)
>
>    上例中，foo的调用以右值（确切说是将亡值）get_a_X()为实参，调用类X的移动构造函数构造出形参x，然后在函数体内对x进行一些操作，最后return X，这样的代码很常见，也很符合我们的编写思路。注意foo函数的返回类型定义为X的引用，如果x为右值，那么，一个右值是不能绑定到左值引用上去的。 
>    为避免这种情况的出现，C++规定：具名的右值引用是左值。这样一来，例一中X anotherX = x;一句将调用X的拷贝构造函数，执行后x不发生变化，继续访问x不会出问题；例二中，return x也将得到允许。
>    例二中，get_a_X返回一个不具名右值引用，这个不具名右值引用的唯一作用就是初始化形参x，在后面的代码中，我们不会也无法访问这个不具名的右值引用。C++将其归为右值，是合理的，一方面，可以使用移动构造函数，提高效率；另一方面，这样做不会出问题。
>
>    至此，关于“三值”的内容就全部介绍完了。
>
> 注释：
>
>    ①只有当存在两个或两个以上的运算对象时才需要运算符连接，单独的运算对象也可以是表达式，例如上面提到的字面值和变量。
>    ②确切说，是表达式的结果的值类别，但我们一般不刻意区分表达式和表达式的求值结果，所以这里称“表达式的值类别”。
>    ③当我们将函数名作为一个值来使用时，该函数名自动转换为指向对应函数的指针。
>    ④关于右值引用本身，没什么可说的，就是指可以绑定到右值上的引用，用"&&"表示，如int &&rra=6;。相比之下，与右值引用相关的一些主题，如移动语义、引用叠加、完美转发等，更值得我们深入探讨。这些内容，在下在后续文章中都会详细介绍。
>    ⑤前提是该右值（如自定义的类X）有移动构造函数或移动赋值运算符可供调用（有时候是没有的，关于这些知识，后续文章在讲移动构造函数和移动赋值运算符时会详述）。
>    ⑥在本文的例二中，如果将get_a_X()的返回值由X的右值引用改为X对象，则get_a_X()是纯右值表达式（如前所述，返回非引用类型的函数调用是纯右值），此时Foo(get_a_X());一句调用的仍然是类X的移动构造函数，这就是一个纯右值完成移动构造的例子。
>
> **写在后面**
>
> ​    在下在参阅许多资料之后，再结合自己的理解，整理出了这篇文章，力图能实现在下写博客（不光是这篇，是所有）的初衷——为初学者服务，尽量把话说明白。但是，由于“三值”问题本身较为复杂，再加上在下才疏学浅，表达能力有限，错误疏漏及其它不足之处在所难免。所以，希望广大读者能够用批判的眼光来阅读这篇文章，更恳请大家对在下的错误疏漏提出批评指正。您的批评指正，既是对在下莫大的帮助，更是在下进步的力量源泉。
>
> https://www.cnblogs.com/zpcdbky/p/5275959.html
>
> [« ](https://www.cnblogs.com/zpcdbky/p/5027481.html)上一篇： [一文说尽C++赋值运算符重载函数(operator=)](https://www.cnblogs.com/zpcdbky/p/5027481.html)
> [» ](https://www.cnblogs.com/zpcdbky/p/5284711.html)下一篇： [图说函数模板右值引用参数(T&&)类型推导规则（C++11）](https://www.cnblogs.com/zpcdbky/p/5284711.html)
>
> posted @ 2016-03-14 18:16 [同勉共进](https://www.cnblogs.com/zpcdbky/) 阅读(15562) 评论(9) [编辑](https://i.cnblogs.com/EditPosts.aspx?postid=5275959) [收藏](javascript:void(0)) [举报](javascript:void(0))

#### 4.1.2 Precedence and Associativity 优先级和结合律

复合表达式（compound expression）指含有两个或多个运算符的表达式。优先级与结合律决定了运算对象的组合方式。

括号无视优先级与结合律，表达式中括号括起来的部分被当成一个单元来求值，然后再与其他部分一起按照优先级组合。

#### 4.1.3 Order of Evaluation 求值顺序

对于那些没有指定执行顺序的运算符来说，如果表达式指向并修改了同一个对象，将会引发错误并产生未定义的行为。

```c++
int i = 0;
cout << i << " " << ++i << endl;    // undefined
```

注意：**C++只规定了很少的二元运算符的运算顺序（与、或、`,`）**，其他的则没加限制，这调高了代码生成的效率，但是也可能引发潜在的问题。

处理复合表达式时建议遵循以下两点：

- 不确定求值顺序时，使用括号来强制让表达式的组合关系符合程序逻辑的要求。

- 如果表达式改变了某个运算对象的值，则在表达式的其他位置不要再使用这个运算对象。

当改变运算对象的子表达式本身就是另一个子表达式的运算对象时，第二条规则无效。如`*++iter`，递增运算符改变了`iter`的值，而改变后的`iter`又是解引用运算符的运算对象。类似情况下，求值的顺序不会成为问题。

### 4.2 Arithmetic Operators 算术运算符

算术运算符（左结合律）(优先级从高到低)：

![](CPP_Primer_5th.assets/4-1.png)

一元正号运算符作用于一个指针或算术值时，返回运算对象值的一个（提升后的）副本；

```c++
    char c = 42;
    cout << typeid(c).name() << endl;
    cout << typeid(+c).name() << endl;
    char *p = &c;
    cout << typeid(p).name() << endl;
    cout << typeid(+p).name() << endl;
/*
char
int
char *
char *
*/
用于指针没有变化。其实这不是什么“提升”，+c其实相当于0+c，因为0是int型，所以+c也是int型
指针+0还是指针
```

bool型不应该参加运算

```c++
bool b = true;
bool b2 = -b;   // error  b2 == true!
```

因为bool型参与运算被提升为int，int 型的-1 有值，所以不为假。



在除法运算中，C++语言的早期版本允许结果为负数的商向上或向下取整，C++11新标准则规定商一律向0取整（即直接去除小数部分）。



### 4.3 Logical and Relational Operators

关系运算符作用于算术类型和指针类型，逻辑运算符作用于任意能转换成布尔值的类型。逻辑运算符和关系运算符的返回值都是**布尔类型**。

![4-2](CPP_Primer_5th.assets/4-2.png)

**短路求值**

逻辑与（logical AND）运算符`&&`和逻辑或（logical OR）运算符`||`都是先计算左侧运算对象的值再计算右侧运算对象的值，当且仅当左侧运算对象无法确定表达式的结果时才会去计算右侧运算对象的值。这种策略称为短路求值（short-circuit evaluation）。

- 对于逻辑与运算符来说，当且仅当左侧运算对象为真时才对右侧运算对象求值。

- 对于逻辑或运算符来说，当且仅当左侧运算对象为假时才对右侧运算对象求值。

进行比较运算时，除非比较的对象是布尔类型，否则不要使用布尔字面值`true`和`false`作为运算对象。

### 4.4 Assignment Operators

赋值运算符`=`的左侧运算对象必须是一个**可修改**的**左值**。

C++11新标准允许使用花括号括起来的初始值列表作为赋值语句的右侧运算对象。

```c++
vector<int> vi;     // initially empty
vi = {0,1,2,3,4,5,6,7,8,9};     // vi now has ten elements, values 0 through 9
```

如果左侧运算对象是内置类型，那么初始值列表最多只能包含一个值，而且该值即使转换的话，所占空间也不应该大于目标类型的空间。

注：使用列表初始化有个方便之处，即初始值存在丢失信息的风险，编译器会报错。

##### 赋值运算符满足右结合律。

```c++
int ival, jval;
ival = jval = 0;    // ok: each assigned 0
```

##### 赋值运算符优先级较低

因为赋值运算符的优先级低于关系运算符的优先级，所以在条件语句中，赋值部分通常应该加上括号。

##### **不要混淆相等运算符`==`和赋值运算符`=`。**

##### 复合赋值运算符

包括`+=`、`-=`、`*=`、`/=`、`%=`、`<<=`、`>>=`、`&=`、`^=`和`|=`。任意一种复合运算都完全等价于*a = a op b*。唯一的区别在于求值次数，几乎可以忽略不计。

### 4.5 Increment and Decrement Operators

递增和递减运算符是为对象加1或减1的简洁书写形式。很多不支持算术运算的迭代器可以使用递增和递减运算符。

递增和递减运算符分为前置版本和后置版本：

- 前置版本首先将运算对象加1（或减1），然后将改变后的对象作为求值结果。

- 后置版本也会将运算对象加1（或减1），但求值结果是运算对象改变前的值的副本。

```c++
int i = 0, j;
j = ++i;    // j = 1, i = 1: prefix yields the incremented value
j = i++;    // j = 1, i = 2: postfix yields the unincremented value
```

> **除非必须，否则不应该使用递增或递减运算符的后置版本。后置版本需要将原始值存储下来以便于返回修改前的内容，如果我们不需要这个值，那么后置版本的操作就是一种浪费。**

##### 在一条语句中混用解引用和递增运算符

如果我们想在一条复合表达式中既将变量加/减1又能使用它原来的值，这时候就可以用后置递增/递减符，可以使程序更简洁。

```c++
auto pbeg = v.begin();
while(pbeg!=v.end() && *pbeg >= 0){
    cout << *pbeg++ << endl;
}
//输出v直到遇到第一个负值。
```

后置递增运算符优先级高于解引用，所以`*pbeg++` 相当于`*(pbeg++)`。先将pbeg加1，然后将原始副本给求值结果，然后输出，并移动指针。

##### 运算对象可按任意顺序求值

```c++
while (beg != s.end() && !isspace(*beg))
    *beg = toupper(*beg++)  // error ,这句话是未定义明确
    
编译器可能以以下任一思路分析
    *beg = toupper(*beg);		//先求左值
	*(beg + 1) = toupper(*beg)	//先求右值
```

所以要仔细注意求值顺序

### 4.6 The Member Access Operators

点运算符`.`和箭头运算符`->`都可以用来访问成员，表达式`ptr->mem`等价于`(*ptr).mem`。

```c++
string s1 = "a string", *p = &s1;
auto n = s1.size();  // run the size member of the string s1
n = (*p).size();    // run size on the object to which p points
n = p->size();      // equivalent to (*p).size()
```

解引用的优先级低于`.`运算符，所以第三局需要加括号，不然`*p.size()`通不过编译。

### 4.7 The Conditional Operator

条件运算符的使用形式如下：

```c++
cond ? expr1 : expr2;
```

其中`cond`是判断条件的表达式，如果`cond`为真则对`expr1`求值并返回该值，否则对`expr2`求值并返回该值。

只有当条件运算符的两个表达式都是左值或者能转换成同一种左值类型时，运算的结果才是左值，否则运算的结果就是右值。

条件运算符可以嵌套，但是考虑到代码的可读性，运算的嵌套层数最好不要超过两到三层。

条件运算符的优先级**非常低**，因此当一个长表达式中嵌套了条件运算子表达式时，通常需要在它两端加上括号。

### 4.8 The Bitwise Operators 位运算符

位运算符作用于整数类型的运算对象，并把运算对象看成是二进制位的集合。位运算符提供检查和设置二进制的功能【17.2 - bitset.h】

##### 位运算符（左结合律）：

![](CPP_Primer_5th.assets/4-3.png)

**在位运算中符号位如何处理并没有明确的规定，所以建议仅将位运算符用于无符号类型的处理。**



##### 移位运算符

这两种运算符的内置含义是对其运算对象执行基于二进制位的移动操作，首先令左侧运算对象的内容按照右侧运算对象的要求移动指定位数，然后将经过移动的（可能还进行了提升）左侧运算对象的拷贝作为求值结果。其中，右侧的运算对象一定不能为负，而且值必须严格小于结果的位数。而且值必须小于结果的位数，否则就会产生未定义的行为。二进制位或者向左移或者向右移，移出边界之外的位就被舍弃掉了。

- 左移运算符`<<`在运算对象右侧插入值为0的二进制位。

- 右移运算符`>>`的行为依赖于其左侧运算对象的类型：如果该运算对象是无符号类型，在其左侧插入值为0的二进制位；如果是带符号类型，在其左侧插入符号位的副本或者值为0的二进制位，如何选择视具体环境而定。

##### 位取反运算符

按位取反，char型会被提升为int类型。

##### 位与位或位异或

##### 移位运算符(IO运算符)满足左结合律

很多人可能没使用过移位运算符，但是肯定用过它们的重载版本进行IO操作。

### 4.9 The sizeof Operator

`sizeof`运算符返回一个表达式或一个类型名字所占的字节数，返回值是`size_t`类型。

在`sizeof`的运算对象中解引用一个无效指针仍然是一种安全的行为，因为指针实际上并没有被真正使用。

同样的，C++11允许我们通过作用域运算符来获取类成员的大小。通常情况下只有通过类的对象才能访问到类的成员，但是sizeof运算符无须我们提供一个具体的对象，因为想要知道类成员的大小无须真的获取该成员。

`sizeof`运算符的结果部分依赖于其作用的类型：

- 对`char`或者类型为`char`的表达式执行`sizeof`运算，返回值为1。
- 对引用类型执行`sizeof`运算得到被引用对象所占空间的大小。
- 对指针执行`sizeof`运算得到指针本身所占空间的大小。
- 对解引用指针执行`sizeof`运算得到指针指向的对象所占空间的大小，指针不需要有效。
- 对数组执行`sizeof`运算得到整个数组所占空间的大小。
- 对`string`或`vector`对象执行`sizeof`运算只返回该类型固定部分的大小，不会计算对象中元素所占空间的大小。

```c++
	//可以通过下面的方式获得数组的大小。
	int a[10];
    cout << sizeof(a) / sizeof(*a) << endl;//10
```



### 4.10 Comma Operator

逗号运算符`,`含有两个运算对象，按照从左向右的顺序依次求值，首先对左侧的表达式求值，然后丢弃掉，逗号运算符真正的幽魂算结果是右侧表达式的值。逗号运算符经常用在`for`循环中。

```c++
vector<int>::size_type cnt = ivec.size();
// assign values from size... 1 to the elements in ivec
for(vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt)
    ivec[ix] = cnt;
```

### 4.11 Type Conversions

如果两种类型可以相互转换，那么它们就是关联的。

无须程序员介入，会自动执行的类型转换叫做隐式转换（implicit conversions）。

##### 何时发生隐式类型转换

- 在大多数表达式中，比int类型小的整型值首先提升较大的整数类型
- 在条件中，非布尔值转换成布尔类型
- 初始化过程中，初始值转变成变量的类型；在赋值语句中，右侧运算对象转换成左侧运算对象的类型。
- 算术运算或关系运算的运算对象有多种类型，需要转换成同一种类型。
- 【6】，函数调用时也会发生类型转换。

#### 4.11.1 The Arithmetic Conversions

把一种算术类型转换成另一种算术类型叫做算术转换。

整型提升（integral promotions）负责把小整数类型转换成较大的整数类型。前提是转换后的类型要能容纳原类型所有可能的值。

无符号与有符号类型之间的转换：

- 如果无符号类型不小于带符号类型，则带符号类型转换成无符号的。如果是负的可能会有意料之外的错误。
- 如果带符号类型大于无符号类型，此时转换结果依赖于机器，如果无符号类型的所有值都能存在带符号类型中，则无符号转化为带符号，否则带符号转换为无符号；

#### 4.11.2 Other Implicit Conversions

##### 数组转化为指针

在大多数表达式中，数组名字自动转换成指向数组首元素的指针。

##### 指针的转换

常量整数值0或字面值`nullptr`能转换成任意指针类型；指向任意非常量的指针能转换成`void*`；指向任意对象的指针能转换成`const void*`。【15.2.2】还会介绍在有继承关系的类型之间还有另外一种指针转换的方式。

##### 转换成布尔类型

任意一种算术类型或指针类型都能转换成布尔类型。如果指针或算术类型的值为0，转换结果是`false`，否则是`true`。

##### 转换成常量

指向非常量类型的指针能转换成指向相应的常量类型的指针。相反的操作不行，因为这试图删除底层的const。

##### 类类型定义的转换

编译器每次只能执行一种类类型的转换，【7.5.4】会看到一个拒绝同时转化多个请求的例子

举例子：

```c++
while(cin >> s)
```

`while()`实际是检查istream类型的值，不过因为IO库定义了从istream型向布尔值转换的规则，所以可以进行成功转换。

#### 4.11.3 Explicit Conversions

显式类型转换也叫做强制类型转换（cast）。虽然有时不得不使用强制类型转换，但这种方法本质上是非常危险的。建议尽量避免强制类型转换。

命名的强制类型转换（named cast）形式如下：

```c++
cast-name<type>(expression);
```

其中`type`是转换的目标类型，`expression`是要转换的值。如果`type`是引用类型，则转换结果是左值。`cast-name`是`static_cast`、`dynamic_cast`、`const_cast`和`reinterpret_cast`中的一种，用来指定转换的方式。

- `dynamic_cast`支持运行时类型识别。【19.2】

- 任何具有明确定义的类型转换，只要不包含底层`const`，都能使用`static_cast`。

- `const_cast`只能改变运算对象的底层`const`，不能改变表达式的类型。同时也只有`const_cast`能改变表达式的常量属性。`const_cast`常常用于函数重载。

- `reinterpret_cast`通常为运算对象的位模式提供底层上的重新解释。十分危险，类型改变了，但编译器不会给出任何警告或错误的提示信息。【6.4】

早期版本的C++语言中，显式类型转换包含两种形式：

```c++
type (expression);    // function-style cast notation
(type) expression;    // C-language-style cast notation
```

> # C++中的类型转换（static_cast、const_cast、dynamic_cast、reinterpret_cast）
>
> **1. c强制转换与c++强制转换**
>
> c语言[强制类型转换](https://so.csdn.net/so/search?q=强制类型转换&spm=1001.2101.3001.7020)主要用于基础的数据类型间的转换，语法为：
>
> ```
> (type-id)expression//转换格式1
> 
> type-id(expression)//转换格式2123
> ```
>
> c++除了能使用c语言的强制类型转换外，还新增了四种强制类型转换：static_cast、dynamic_cast、const_cast、reinterpret_cast，主要运用于继承关系类间的强制转化，语法为：
>
> ```
> static_cast<new_type>      (expression)
> dynamic_cast<new_type>     (expression) 
> const_cast<new_type>       (expression) 
> reinterpret_cast<new_type> (expression)1234
> ```
>
> 备注：new_type为目标数据类型，expression为原始数据类型变量或者表达式。
>
> 《Effective C++》中将c语言强制类型转换称为旧式转型，c++强制类型转换称为新式转型。
>
> **2. static_cast、dynamic_cast、const_cast、reinterpret_cast**
>
> **static_cast**
>
> static_cast相当于传统的C语言里的强制转换，该运算符把expression转换为new_type类型，用来强迫隐式转换，例如non-const对象转为const对象，编译时检查，用于非多态的转换，可以转换指针及其他，***但没有运行时类型检查来保证转换的安全性\***。它主要有如下几种用法：
> ①用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。
> ***进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；\***
> ***进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。\***
> ②用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
> ③把空指针转换成目标类型的空指针。
> ④把任何类型的表达式转换成void类型。
> 注意：static_cast不能转换掉expression的const、volatile、或者__unaligned属性。
>
> 基本类型数据转换举例如下：
>
> ```
> char a = 'a';
> int b = static_cast<char>(a);//正确，将char型数据转换成int型数据
> 
> double *c = new double;
> void *d = static_cast<void*>(c);//正确，将double指针转换成void指针
> 
> int e = 10;
> const int f = static_cast<const int>(e);//正确，将int型数据转换成const int型数据
> 
> const int g = 20;
> int *h = static_cast<int*>(&g);//编译错误，static_cast不能转换掉g的const属性1234567891011
> ```
>
> 类上行和下行转换：
>
> ```
> if(Derived *dp = static_cast<Derived *>(bp)){//下行转换是不安全的
>   //使用dp指向的Derived对象  
> }
> else{
>   //使用bp指向的Base对象  
> }
> 
> if(Base*bp = static_cast<Derived *>(dp)){//上行转换是安全的
>   //使用bp指向的Derived对象  
> }
> else{
>   //使用dp指向的Base对象  
> }12345678910111213
> ```
>
> **dynamic_cast**
>
> ```
> dynamic_cast<type*>(e)
> dynamic_cast<type&>(e)
> dynamic_cast<type&&>(e)123
> ```
>
> type必须是一个类类型，在第一种形式中，type必须是一个有效的指针，在第二种形式中，type必须是一个左值，在第三种形式中，type必须是一个右值。在上面所有形式中，e的类型必须符合以下三个条件中的任何一个：e的类型是是目标类型type的公有派生类、e的类型是目标type的共有基类或者e的类型就是目标type的的类型。如果一条dynamic_cast语句的转换目标是指针类型并且失败了，则结果为0。如果转换目标是引用类型并且失败了，则dynamic_cast运算符将抛出一个std::bad_cast异常(该异常定义在typeinfo标准库头文件中)。e也可以是一个空指针，结果是所需类型的空指针。
>
> dynamic_cast主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换（cross cast）。
> 在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的；
> ***在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。dynamic_cast是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作。\***
>
> （1）指针类型
> 举例，Base为包含至少一个虚函数的基类，Derived是Base的共有派生类，如果有一个指向Base的指针bp，我们可以在运行时将它转换成指向Derived的指针，代码如下：
>
> ```
> if(Derived *dp = dynamic_cast<Derived *>(bp)){
>   //使用dp指向的Derived对象  
> }
> else{
>   //使用bp指向的Base对象  
> }123456
> ```
>
> 值得注意的是，在上述代码中，if语句中定义了dp，这样做的好处是可以在一个操作中同时完成[类型转换](https://so.csdn.net/so/search?q=类型转换&spm=1001.2101.3001.7020)和条件检查两项任务。
>
> （2）引用类型
>
> 因为不存在所谓空引用，所以引用类型的dynamic_cast转换与指针类型不同，在引用转换失败时，会抛出std::bad_cast异常，该异常定义在头文件typeinfo中。
>
> ```
> void f(const Base &b){
>  try{
>    const Derived &d = dynamic_cast<const Base &>(b);  
>    //使用b引用的Derived对象
>  }
>  catch(std::bad_cast){
>    //处理类型转换失败的情况
>  }
> }123456789
> ```
>
> **const_cast**
>
> const_cast，用于修改类型的const或volatile属性。
> 该运算符用来修改类型的const(唯一有此能力的C++-style转型操作符)或volatile属性。除了const 或volatile修饰之外， new_type和expression的类型是一样的。
> ①常量指针被转化成非常量的指针，并且仍然指向原来的对象；
> ②常量引用被转换成非常量的引用，并且仍然指向原来的对象；
> ③const_cast一般用于修改底指针。如const char *p形式。
>
> 举例转换如下：
>
> ```
> const int g = 20;
> int *h = const_cast<int*>(&g);//去掉const常量const属性
> 
> const int g = 20;
> int &h = const_cast<int &>(g);//去掉const引用const属性
> 
>  const char *g = "hello";
> char *h = const_cast<char *>(g);//去掉const指针const属性12345678
> ```
>
> **reinterpret_cast**
>
> new_type必须是一个指针、引用、算术类型、函数指针或者成员指针。它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针（先把一个指针转换成一个整数，再把该整数转换成原类型的指针，还可以得到原先的指针值）。
>
> ***reinterpret_cast意图执行低级转型，实际动作（及结果）可能取决于编辑器，这也就表示它不可移植。\***
>
> 举一个错误使用reintepret_cast例子，将整数类型转换成函数指针后，vc++在执行过程中会报”…中的 0xxxxxxxxx 处有未经处理的异常: 0xC0000005: Access violation”错误：
>
> ```
> #include <iostream>
> using namespace std;
> int output(int p){
>     cout << p <<endl;
> 　　return 0;
> }
> 
> typedef int (*test_func)(int );//定义函数指针test_func
> int main(){
>     int p = 10;
>     test_func fun1 = output;
>     fun1(p);//正确
>     test_func fun2 = reinterpret_cast<test_func>(&p);
>     fun2(p);//...处有未经处理的异常: 0xC0000005: Access violation
>     return 0;
> }12345678910111213141516
> ```
>
> IBM的C++指南、C++之父Bjarne Stroustrup的FAQ网页和MSDN的Visual C++也都指出：错误的使用reinterpret_cast很容易导致程序的不安全，***只有将转换后的类型值转换回到其原始类型，这样才是正确使用reinterpret_cast方式。\***
>
> MSDN中也提到了，实际中可将reinterpret_cast应用到哈希函数中，如下（64位系统中需将unsigned int修改为unsigned long）：
>
> ```
> // expre_reinterpret_cast_Operator.cpp
> // compile with: /EHsc
> #include <iostream>
> 
> // Returns a hash code based on an address
> unsigned short Hash( void *p ) {
>    unsigned int val = reinterpret_cast<unsigned int>( p );
>    return ( unsigned short )( val ^ (val >> 16));
> }
> 
> using namespace std;
> int main() {
>    int a[20];
>    for ( int i = 0; i < 20; i++ )
>       cout << Hash( a + i ) << endl;
> }12345678910111213141516
> ```
>
> 另外，static_cast和reinterpret_cast的区别主要在于多重继承，比如
>
> ```
> class A {
>     public:
>     int m_a;
> };
> 
> class B {
>     public:
>     int m_b;
> };
> 
> class C : public A, public B {};1234567891011
> ```
>
> 那么对于以下代码：
>
> ```
> C c;
> printf("%p, %p, %p", &c, reinterpret_cast<B*>(&c), static_cast <B*>(&c));12
> ```
>
> 前两个的输出值是相同的，最后一个则会在原基础上偏移4个字节，这是因为static_cast计算了父子类指针转换的偏移量，并将之转换到正确的地址（c里面有m_a,m_b，转换为B*指针后指到m_b处），而reinterpret_cast却不会做这一层转换。
>
> 因此, 你需要谨慎使用 reinterpret_cast。
>
> **3. c++强制转换注意事项**
>
> 新式转换较旧式转换更受欢迎。原因有二，一是新式转型较易辨别，能简化“找出类型系统在哪个地方被破坏”的过程；二是各转型动作的目标愈窄化，编译器愈能诊断出错误的运用。
> 尽量少使用转型操作，尤其是dynamic_cast，耗时较高，会导致性能的下降，尽量使用其他方法替代。

### 4.12 Operator Precedence Table

####  [C++ 运算符优先级和关联性表](https://docs.microsoft.com/zh-cn/cpp/cpp/cpp-built-in-operators-precedence-and-associativity?view=msvc-170)

下表显示 C++ 运算符的优先级和关联性（从最高优先级到最低优先级）。 优先级别编号相同的运算符具有等同的优先级别，除非由括号显式施加另一种关系。

| 运算符说明                                                   | 运算符                                                       | 替代项       |
| :----------------------------------------------------------- | :----------------------------------------------------------- | :----------- |
| **组 1 优先级，无关联性**                                    |                                                              |              |
| [范围解析](https://docs.microsoft.com/zh-cn/cpp/cpp/scope-resolution-operator?view=msvc-170) | [`::`](https://docs.microsoft.com/zh-cn/cpp/cpp/scope-resolution-operator?view=msvc-170) |              |
| **组 2 优先级，从左到右关联**                                |                                                              |              |
| [成员选择（对象或指针）](https://docs.microsoft.com/zh-cn/cpp/cpp/member-access-operators-dot-and?view=msvc-170) | 或 `->`                                                      |              |
| [数组下标](https://docs.microsoft.com/zh-cn/cpp/cpp/subscript-operator?view=msvc-170) | [`[\]`](https://docs.microsoft.com/zh-cn/cpp/cpp/subscript-operator?view=msvc-170) |              |
| [函数调用](https://docs.microsoft.com/zh-cn/cpp/cpp/function-call-operator-parens?view=msvc-170) | [`()`](https://docs.microsoft.com/zh-cn/cpp/cpp/function-call-operator-parens?view=msvc-170) |              |
| [后缀递增](https://docs.microsoft.com/zh-cn/cpp/cpp/postfix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) | [`++`](https://docs.microsoft.com/zh-cn/cpp/cpp/postfix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) |              |
| [后缀递减](https://docs.microsoft.com/zh-cn/cpp/cpp/postfix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) | [`--`](https://docs.microsoft.com/zh-cn/cpp/cpp/postfix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) |              |
| [类型名称](https://docs.microsoft.com/zh-cn/cpp/cpp/typeid-operator?view=msvc-170) | [`typeid`](https://docs.microsoft.com/zh-cn/cpp/cpp/typeid-operator?view=msvc-170) |              |
| [常量类型转换](https://docs.microsoft.com/zh-cn/cpp/cpp/const-cast-operator?view=msvc-170) | [`const_cast`](https://docs.microsoft.com/zh-cn/cpp/cpp/const-cast-operator?view=msvc-170) |              |
| [动态类型转换](https://docs.microsoft.com/zh-cn/cpp/cpp/dynamic-cast-operator?view=msvc-170) | [`dynamic_cast`](https://docs.microsoft.com/zh-cn/cpp/cpp/dynamic-cast-operator?view=msvc-170) |              |
| [重新解释的类型转换](https://docs.microsoft.com/zh-cn/cpp/cpp/reinterpret-cast-operator?view=msvc-170) | [`reinterpret_cast`](https://docs.microsoft.com/zh-cn/cpp/cpp/reinterpret-cast-operator?view=msvc-170) |              |
| [静态类型转换](https://docs.microsoft.com/zh-cn/cpp/cpp/static-cast-operator?view=msvc-170) | [`static_cast`](https://docs.microsoft.com/zh-cn/cpp/cpp/static-cast-operator?view=msvc-170) |              |
| **组 3 优先级，从右到左关联**                                |                                                              |              |
| [对象或类型的大小](https://docs.microsoft.com/zh-cn/cpp/cpp/sizeof-operator?view=msvc-170) | [`sizeof`](https://docs.microsoft.com/zh-cn/cpp/cpp/sizeof-operator?view=msvc-170) |              |
| [前缀递增](https://docs.microsoft.com/zh-cn/cpp/cpp/prefix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) | [`++`](https://docs.microsoft.com/zh-cn/cpp/cpp/prefix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) |              |
| [前缀递减](https://docs.microsoft.com/zh-cn/cpp/cpp/prefix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) | [`--`](https://docs.microsoft.com/zh-cn/cpp/cpp/prefix-increment-and-decrement-operators-increment-and-decrement?view=msvc-170) |              |
| [一个补充](https://docs.microsoft.com/zh-cn/cpp/cpp/one-s-complement-operator-tilde?view=msvc-170) | [`~`](https://docs.microsoft.com/zh-cn/cpp/cpp/one-s-complement-operator-tilde?view=msvc-170) | **`compl`**  |
| [逻辑不是](https://docs.microsoft.com/zh-cn/cpp/cpp/logical-negation-operator-exclpt?view=msvc-170) | [`!`](https://docs.microsoft.com/zh-cn/cpp/cpp/logical-negation-operator-exclpt?view=msvc-170) | **`not`**    |
| [一元否定](https://docs.microsoft.com/zh-cn/cpp/cpp/unary-plus-and-negation-operators-plus-and?view=msvc-170) | [`-`](https://docs.microsoft.com/zh-cn/cpp/cpp/unary-plus-and-negation-operators-plus-and?view=msvc-170) |              |
| [一元加](https://docs.microsoft.com/zh-cn/cpp/cpp/unary-plus-and-negation-operators-plus-and?view=msvc-170) | [`+`](https://docs.microsoft.com/zh-cn/cpp/cpp/unary-plus-and-negation-operators-plus-and?view=msvc-170) |              |
| [地址](https://docs.microsoft.com/zh-cn/cpp/cpp/address-of-operator-amp?view=msvc-170) | [`&`](https://docs.microsoft.com/zh-cn/cpp/cpp/address-of-operator-amp?view=msvc-170) |              |
| [间接寻址](https://docs.microsoft.com/zh-cn/cpp/cpp/indirection-operator-star?view=msvc-170) | [`*`](https://docs.microsoft.com/zh-cn/cpp/cpp/indirection-operator-star?view=msvc-170) |              |
| [创建对象](https://docs.microsoft.com/zh-cn/cpp/cpp/new-operator-cpp?view=msvc-170) | [`new`](https://docs.microsoft.com/zh-cn/cpp/cpp/new-operator-cpp?view=msvc-170) |              |
| [销毁对象](https://docs.microsoft.com/zh-cn/cpp/cpp/delete-operator-cpp?view=msvc-170) | [`delete`](https://docs.microsoft.com/zh-cn/cpp/cpp/delete-operator-cpp?view=msvc-170) |              |
| [投](https://docs.microsoft.com/zh-cn/cpp/cpp/cast-operator-parens?view=msvc-170) | [`()`](https://docs.microsoft.com/zh-cn/cpp/cpp/cast-operator-parens?view=msvc-170) |              |
| **组 4 优先级，从左到右关联**                                |                                                              |              |
| [指向成员的指针（对象或指针）](https://docs.microsoft.com/zh-cn/cpp/cpp/pointer-to-member-operators-dot-star-and-star?view=msvc-170) | 或 `->*`                                                     |              |
| **组 5 优先级，从左到右关联**                                |                                                              |              |
| [乘法](https://docs.microsoft.com/zh-cn/cpp/cpp/multiplicative-operators-and-the-modulus-operator?view=msvc-170) | [`*`](https://docs.microsoft.com/zh-cn/cpp/cpp/multiplicative-operators-and-the-modulus-operator?view=msvc-170) |              |
| [部门](https://docs.microsoft.com/zh-cn/cpp/cpp/multiplicative-operators-and-the-modulus-operator?view=msvc-170) | [`/`](https://docs.microsoft.com/zh-cn/cpp/cpp/multiplicative-operators-and-the-modulus-operator?view=msvc-170) |              |
| [模](https://docs.microsoft.com/zh-cn/cpp/cpp/multiplicative-operators-and-the-modulus-operator?view=msvc-170) | [`%`](https://docs.microsoft.com/zh-cn/cpp/cpp/multiplicative-operators-and-the-modulus-operator?view=msvc-170) |              |
| **组 6 优先级，从左到右关联**                                |                                                              |              |
| [加法](https://docs.microsoft.com/zh-cn/cpp/cpp/additive-operators-plus-and?view=msvc-170) | [`+`](https://docs.microsoft.com/zh-cn/cpp/cpp/additive-operators-plus-and?view=msvc-170) |              |
| [减法](https://docs.microsoft.com/zh-cn/cpp/cpp/additive-operators-plus-and?view=msvc-170) | [`-`](https://docs.microsoft.com/zh-cn/cpp/cpp/additive-operators-plus-and?view=msvc-170) |              |
| **组 7 优先级，从左到右关联**                                |                                                              |              |
| [左移](https://docs.microsoft.com/zh-cn/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-170) | [`<<`](https://docs.microsoft.com/zh-cn/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-170) |              |
| [右移](https://docs.microsoft.com/zh-cn/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-170) | [`>>`](https://docs.microsoft.com/zh-cn/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-170) |              |
| **组 8 优先级，从左到右关联**                                |                                                              |              |
| [小于](https://docs.microsoft.com/zh-cn/cpp/cpp/relational-operators-equal-and-equal?view=msvc-170) | [`<`](https://docs.microsoft.com/zh-cn/cpp/cpp/relational-operators-equal-and-equal?view=msvc-170) |              |
| 大于                                                         | [`>`](https://docs.microsoft.com/zh-cn/cpp/cpp/relational-operators-equal-and-equal?view=msvc-170) |              |
| 小于或等于                                                   | [`<=`](https://docs.microsoft.com/zh-cn/cpp/cpp/relational-operators-equal-and-equal?view=msvc-170) |              |
| 大于或等于                                                   | [`>=`](https://docs.microsoft.com/zh-cn/cpp/cpp/relational-operators-equal-and-equal?view=msvc-170) |              |
| **组 9 优先级，从左到右关联**                                |                                                              |              |
| [等式](https://docs.microsoft.com/zh-cn/cpp/cpp/equality-operators-equal-equal-and-exclpt-equal?view=msvc-170) | [`==`](https://docs.microsoft.com/zh-cn/cpp/cpp/equality-operators-equal-equal-and-exclpt-equal?view=msvc-170) |              |
| [不相等](https://docs.microsoft.com/zh-cn/cpp/cpp/equality-operators-equal-equal-and-exclpt-equal?view=msvc-170) | [`!=`](https://docs.microsoft.com/zh-cn/cpp/cpp/equality-operators-equal-equal-and-exclpt-equal?view=msvc-170) | **`not_eq`** |
| **组 10 优先级从左到右关联**                                 |                                                              |              |
| [按位 AND](https://docs.microsoft.com/zh-cn/cpp/cpp/bitwise-and-operator-amp?view=msvc-170) | [`&`](https://docs.microsoft.com/zh-cn/cpp/cpp/bitwise-and-operator-amp?view=msvc-170) | **`bitand`** |
| **组 11 优先级，从左到右关联**                               |                                                              |              |
| [位异或](https://docs.microsoft.com/zh-cn/cpp/cpp/bitwise-exclusive-or-operator-hat?view=msvc-170) | [`^`](https://docs.microsoft.com/zh-cn/cpp/cpp/bitwise-exclusive-or-operator-hat?view=msvc-170) | **`xor`**    |
| **组 12 优先级，从左到右关联**                               |                                                              |              |
| [位或](https://docs.microsoft.com/zh-cn/cpp/cpp/bitwise-inclusive-or-operator-pipe?view=msvc-170) | [`|`](https://docs.microsoft.com/zh-cn/cpp/cpp/bitwise-inclusive-or-operator-pipe?view=msvc-170) | **`bitor`**  |
| **组 13 优先级，从左到右关联**                               |                                                              |              |
| [逻辑与](https://docs.microsoft.com/zh-cn/cpp/cpp/logical-and-operator-amp-amp?view=msvc-170) | [`&&`](https://docs.microsoft.com/zh-cn/cpp/cpp/logical-and-operator-amp-amp?view=msvc-170) | **`and`**    |
| **组 14 优先级，从左到右关联**                               |                                                              |              |
| [逻辑或](https://docs.microsoft.com/zh-cn/cpp/cpp/logical-or-operator-pipe-pipe?view=msvc-170) | [`||`](https://docs.microsoft.com/zh-cn/cpp/cpp/logical-or-operator-pipe-pipe?view=msvc-170) | **`or`**     |
| **组 15 优先级，从右到左关联**                               |                                                              |              |
| [条件逻辑](https://docs.microsoft.com/zh-cn/cpp/cpp/conditional-operator-q?view=msvc-170) | [`? :`](https://docs.microsoft.com/zh-cn/cpp/cpp/conditional-operator-q?view=msvc-170) |              |
| [分配](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [乘法赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`*=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [除法赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`/=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [取模赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`%=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [加法赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`+=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [减法赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`-=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [左移赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`<<=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [右移赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`>>=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) |              |
| [按位“与”赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`&=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | **`and_eq`** |
| [按位“与或”赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`|=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | **`or_eq`**  |
| [按位“异或”赋值](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | [`^=`](https://docs.microsoft.com/zh-cn/cpp/cpp/assignment-operators?view=msvc-170) | **`xor_eq`** |
| [引发表达式](https://docs.microsoft.com/zh-cn/cpp/cpp/try-throw-and-catch-statements-cpp?view=msvc-170) | [`throw`](https://docs.microsoft.com/zh-cn/cpp/cpp/try-throw-and-catch-statements-cpp?view=msvc-170) |              |
| **组 16 优先级，从左到右关联**                               |                                                              |              |
| [逗号](https://docs.microsoft.com/zh-cn/cpp/cpp/comma-operator?view=msvc-170) | [,](https://docs.microsoft.com/zh-cn/cpp/cpp/comma-operator?view=msvc-170) |              |

### Chapter Summary  

​	C++ 提供了丰富的运算符，还支持运算符重载的机制，允许我们自定义运算符作用于类类型时的定义。【14】

​	对于复杂的表达式，需要理解其含义关键要理解优先级、结合律和求值顺序。

​	大多数运算符并不明确规定运算对象的求值顺序：编译器来处理这部分问题。但时在编程时，需要特别谨慎处理两个运算对象指向同一个对象而且其中一个改变了对象的值。

​	运算对象经常从原始类型自动转换从某种关联的类型，我们也可以自己进行强制类型转换。 

### Defined Terms

| 中文     | 英文                     | 含义                                                         |
| -------- | ------------------------ | ------------------------------------------------------------ |
| 算术转换 | arithmetic conversion    | 从一种算术类型转成另一种，为了保留精度，通常是小类型转换成大类型。 |
| 结合律   | associativity            | 规定具有相同优先级的运算符如何组合在一起，分为左结合律和右结合律。 |
| 左值     | lvalue                   | 那些求职结果为对象或函数的表达式。一个表示对象的非常量左值可以作为赋值运算符的左侧运算对象。 |
| 短路求值 | short-circuit evaluation | 专有名词，描述逻辑与和逻辑或运算符的执行过程，如果运算符的第一个运算对象就能判断整个表达式的值，求值终止。 |
|          |                          |                                                              |
|          |                          |                                                              |
|          |                          |                                                              |





## Chapter 5 Statements

### 5.1 Simple Statements

### 5.2 Statement Scope

### 5.3 Conditional Statements

#### 5.3.1 The if Statement

#### 5.3.2 The switch Statement

### 5.4 Iterative Statements

#### 5.4.1 The while Statement

#### 5.4.2 Traditional for Statement

#### 5.4.3 Range for Statement

#### 5.4.4 The do while Statement

### 5.5 Jump Statements

#### 5.5.1 The break Statement

#### 5.5.2 The continue Statement

#### 5.5.3 The goto Statement

### 5.6 try Blocks and Exception Handling

#### 5.6.1 A throw Expression

#### 5.6.2 The try Block

#### 5.6.3 Standard Exceptions

### Chapter Summary  

### Defined Terms



## Chapter 6 Functions

### 6.1 Function Basics

#### 6.1.1 Local Objects

#### 6.1.2 Function Declarations

#### 6.1.3 Separate Compilation

### 6.2 Argument Passing

#### 6.2.1 Passing Arguments by Value

#### 6.2.2 Passing Arguments by Reference

#### 6.2.3 const Parameters and Arguments

#### 6.2.4 Array Parameters

#### 6.2.5 main: Handling Command-Line Options

#### 6.2.6 Functions with Varying Parameters

### 6.3 Return Types and the return Statement

#### 6.3.1 Functions with No Return Value

#### 6.3.2 Functions That Return a Value

#### 6.3.3 Returning a Pointer to an Array

### 6.4 Overloaded Functions

#### 6.4.1 Overloading and Scope

### 6.5 Features for Specialized Uses

#### 6.5.1 Default Arguments

#### 6.5.2 Inline and constexpr Functions

#### 6.5.3 Aids for Debugging

### 6.6 Function Matching

#### 6.6.1 Argument Type Conversions

### 6.7 Pointers to Functions

### Chapter Summary 

### Defined Terms



## Chapter 7 Classes

### 7.1 Defining Abstract Data Types

#### 7.1.1 Designing the Sales_data Class

#### 7.1.2 Defining the Revised Sales_data Class

#### 7.1.3 Defining Nonmember Class-Related Functions

#### 7.1.4 Constructors

#### 7.1.5 Copy, Assignment, and Destruction

### 7.2 Access Control and Encapsulation

#### 7.2.1 Friends

### 7.3 Additional Class Features

#### 7.3.1 Class Members Revisited

#### 7.3.2 Functions That Return *this

#### 7.3.3 Class Types

#### 7.3.4 Friendship Revisited

### 7.4 Class Scope

#### 7.4.1 Name Lookup and Class Scope

### 7.5 Constructors Revisited

#### 7.5.1 Constructor Initializer List

#### 7.5.2 Delegating Constructors

#### 7.5.3 The Role of the Default Constructor

#### 7.5.4 Implicit Class-Type Conversions

#### 7.5.5 Aggregate Classes

#### 7.5.6 Literal Classes

### 7.6 static Class Members

### Chapter Summary  

### Defined Terms



# Part II The C++ Library

## Chapter 8 The IO Library
### 8.1 The IO Classes

#### 8.1.1 No Copy or Assign for IO Objects

#### 8.1.2 Condition States

#### 8.1.3 Managing the Output Buffer

### 8.2 File Input and Output

#### 8.2.1 Using File Stream Objects

#### 8.2.2 File Modes

### 8.3 string Streams

#### 8.3.1 Using an istringstream

#### 8.3.2 Using ostringstreams

### Chapter Summary 

### Defined Terms



## Chapter 9 Sequential Containers

### 9.1 Overview of the Sequential Containers

### 9.2 Container Library Overview

#### 9.2.1 Iterators

#### 9.2.2 Container Type Members

#### 9.2.3 begin and end Members

#### 9.2.4 Defining and Initializing a Container

#### 9.2.5 Assignment and swap

#### 9.2.6 Container Size Operations

#### 9.2.7 Relational Operators

### 9.3 Sequential Container Operations

#### 9.3.1 Adding Elements to a Sequential Container

#### 9.3.2 Accessing Elements

#### 9.3.3 Erasing Elements

#### 9.3.4 Specialized forward_list Operations

#### 9.3.5 Resizing a Container

#### 9.3.6 Container Operations May Invalidate Iterators

### 9.4 How a vector Grows

### 9.5 Additional string Operations

#### 9.5.1 Other Ways to Construct strings

#### 9.5.2 Other Ways to Change a string

#### 9.5.3 string Search Operations

#### 9.5.4 The compare Functions

#### 9.5.5 Numeric Conversions

### 9.6 Container Adaptors

### Chapter Summary  

### Defined Terms



## Chapter 10 Generic Algorithms

### 10.1 Overview

### 10.2 A First Look at the Algorithms

#### 10.2.1 Read-Only Algorithms

#### 10.2.2 Algorithms That Write Container Elements

#### 10.2.3 Algorithms That Reorder Container Elements

### 10.3 Customizing Operations

#### 10.3.1 Passing a Function to an Algorithm

#### 10.3.2 Lambda Expressions

#### 10.3.3 Lambda Captures and Returns

#### 10.3.4 Binding Arguments

### 10.4 Revisiting Iterators

#### 10.4.1 Insert Iterators

#### 10.4.2 iostream Iterators

#### 10.4.3 Reverse Iterators

### 10.5 Structure of Generic Algorithms

#### 10.5.1 The Five Iterator Categories

#### 10.5.2 Algorithm Parameter Patterns

#### 10.5.3 Algorithm Naming Conventions

### 10.6 Container-Specific Algorithms

### Chapter Summary  

### Defined Terms



## Chapter 11 Associative Containers

### 11.1 Using an Associative Container

### 11.2 Overview of the Associative Containers

#### 11.2.1 Defining an Associative Container

#### 11.2.2 Requirements on Key Type

#### 11.2.3 The pair Type

### 11.3 Operations on Associative Containers

#### 11.3.1 Associative Container Iterators

#### 11.3.2 Adding Elements

#### 11.3.3 Erasing Elements

#### 11.3.4 Subscripting a map

#### 11.3.5 Accessing Elements

#### 11.3.6 A Word Transformation Map

### 11.4 The Unordered Containers

### Chapter Summary  

### Defined Terms



## Chapter 12 Dynamic Memory
### 12.1 Dynamic Memory and Smart Pointers

#### 12.1.1 The shared_ptr Class

#### 12.1.2 Managing Memory Directly

#### 12.1.3 Using shared_ptrs with new

#### 12.1.4 Smart Pointers and Exceptions

#### 12.1.5 unique_ptr

#### 12.1.6 weak_ptr

### 12.2 Dynamic Arrays

#### 12.2.1 new and Arrays

#### 12.2.2 The allocator Class

### 12.3 Using the Library: A Text-Query Program

#### 12.3.1 Design of the Query Program

#### 12.3.2 Defining the Query Program Classes

### Chapter Summary  

### Defined Terms



# Part III Tools for Class Authors

## Chapter 13 Copy Control
### 13.1 Copy, Assign, and Destroy

#### 13.1.1 The Copy Constructor

#### 13.1.2 The Copy-Assignment Operator

#### 13.1.3 The Destructor

#### 13.1.4 The Rule of Three/Five

#### 13.1.5 Using = default

#### 13.1.6 Preventing Copies

### 13.2 Copy Control and Resource Management

#### 13.2.1 Classes That Act Like Values

#### 13.2.2 Defining Classes That Act Like Pointers

### 13.3 Swap

### 13.4 A Copy-Control Example

### 13.5 Classes That Manage Dynamic Memory

### 13.6 Moving Objects

#### 13.6.1 Rvalue References

#### 13.6.2 Move Constructor and Move Assignment

#### 13.6.3 Rvalue References and Member Functions

### Chapter Summary  

### Defined Terms



## Chapter 14 Overloaded Operations and Conversions

### 14.1 Basic Concepts

### 14.2 Input and Output Operators

#### 14.2.1 Overloading the Output Operator <<

#### 14.2.2 Overloading the Input Operator >>

### 14.3 Arithmetic and Relational Operators

#### 14.3.1 Equality Operators

#### 14.3.2 Relational Operators

### 14.4 Assignment Operators

### 14.5 Subscript Operator

### 14.6 Increment and Decrement Operators

### 14.7 Member Access Operators

### 14.8 Function-Call Operator

#### 14.8.1 Lambdas Are Function Objects

#### 14.8.2 Library-Defined Function Objects

#### 14.8.3 Callable Objects and function

### 14.9 Overloading, Conversions, and Operators

#### 14.9.1 Conversion Operators

#### 14.9.2 Avoiding Ambiguous Conversions

#### 14.9.3 Function Matching and Overloaded Operators

### Chapter Summary  

### Defined Terms



## Chapter 15 Object-Oriented Programming
### 15.1 OOP: An Overview

### 15.2 Defining Base and Derived Classes

#### 15.2.1 Defining a Base Class

#### 15.2.2 Defining a Derived Class

#### 15.2.3 Conversions and Inheritance

### 15.3 Virtual Functions

### 15.4 Abstract Base Classes

### 15.5 Access Control and Inheritance

### 15.6 Class Scope under Inheritance

### 15.7 Constructors and Copy Control

#### 15.7.1 Virtual Destructors

#### 15.7.2 Synthesized Copy Control and Inheritance

#### 15.7.3 Derived-Class Copy-Control Members

#### 15.7.4 Inherited Constructors

### 15.8 Containers and Inheritance

#### 15.8.1 Writing a Basket Class

### 15.9 Text Queries Revisited

#### 15.9.1 An Object-Oriented Solution

#### 15.9.2 The Query_base and Query Classes

#### 15.9.3 The Derived Classes

#### 15.9.4 The eval Functions

### Chapter Summary  

### Defined Terms



## Chapter 16 Templates and Generic Programming

### 16.1 Defining a Template

#### 16.1.1 Function Templates

#### 16.1.2 Class Templates

#### 16.1.3 Template Parameters

#### 16.1.4 Member Templates

#### 16.1.5 Controlling Instantiations

#### 16.1.6 Efficiency and Flexibility

### 16.2 Template Argument Deduction

#### 16.2.1 Conversions and Template Type Parameters

#### 16.2.2 Function-Template Explicit Arguments

#### 16.2.3 Trailing Return Types and Type Transformation

#### 16.2.4 Function Pointers and Argument Deduction

#### 16.2.5 Template Argument Deduction and References

#### 16.2.6 Understanding std::move

#### 16.2.7 Forwarding

### 16.3 Overloading and Templates

### 16.4 Variadic Templates

#### 16.4.1 Writing a Variadic Function Template

#### 16.4.2 Pack Expansion

#### 16.4.3 Forwarding Parameter Packs

### 16.5 Template Specializations

### Chapter Summary  

### Defined Terms



# Part IV Advanced Topics

## Chapter 17 Specialized Library Facilities
### 17.1 The tuple Type

#### 17.1.1 Defining and Initializing tuples

#### 17.1.2 Using a tuple to Return Multiple Values

### 17.2 The bitset Type

#### 17.2.1 Defining and Initializing bitsets

#### 17.2.2 Operations on bitsets

### 17.3 Regular Expressions

#### 17.3.1 Using the Regular Expression Library

#### 17.3.2 The Match and Regex Iterator Types

#### 17.3.3 Using Subexpressions

#### 17.3.4 Using regex_replace

### 17.4 Random Numbers

#### 17.4.1 Random-Number Engines and Distribution

#### 17.4.2 Other Kinds of Distributions

### 17.5 The IO Library Revisited

#### 17.5.1 Formatted Input and Output

#### 17.5.2 Unformatted Input/Output Operations

#### 17.5.3 Random Access to a Stream

### Chapter Summary  

### Defined Terms



## Chapter 18 Tools for Large Programs

### 18.1 Exception Handling

#### 18.1.1 Throwing an Exception

#### 18.1.2 Catching an Exception

#### 18.1.3 Function try Blocks and Constructors

#### 18.1.4 The noexcept Exception Specification

#### 18.1.5 Exception Class Hierarchies

### 18.2 Namespaces

#### 18.2.1 Namespace Definitions

#### 18.2.2 Using Namespace Members

#### 18.2.3 Classes, Namespaces, and Scope

#### 18.2.4 Overloading and Namespaces

### 18.3 Multiple and Virtual Inheritance

#### 18.3.1 Multiple Inheritance

#### 18.3.2 Conversions and Multiple Base Classes

#### 18.3.3 Class Scope under Multiple Inheritance

#### 18.3.4 Virtual Inheritance

#### 18.3.5 Constructors and Virtual Inheritance

### Chapter Summary  

### Defined Terms



## Chapter 19 Specialized Tools and Techniques

### 19.1 Controlling Memory Allocation

#### 19.1.1 Overloading new and delete

#### 19.1.2 Placement new Expressions

### 19.2 Run-Time Type Identification

#### 19.2.1 The dynamic_cast Operator

#### 19.2.2 The typeid Operator

#### 19.2.3 Using RTTI

#### 19.2.4 The type_info Class

### 19.3 Enumerations

### 19.4 Pointer to Class Member

#### 19.4.1 Pointers to Data Members

#### 19.4.2 Pointers to Member Functions

#### 19.4.3 Using Member Functions as Callable Objects

### 19.5 Nested Classes

### 19.6 union: A Space-Saving Class

### 19.7 Local Classes

### 19.8 Inherently Nonportable Features

#### 19.8.1 Bit-fields

#### 19.8.2 volatile Qualifier

#### 19.8.3 Linkage Directives: extern "C"

### Chapter Summary  

### Defined Terms



# Appendix A. The Library

## Section A.1 Library Names and Headers

## Section A.2 A Brief Tour of the Algorithms

## Section A.3 Random Numbers







# some code



```c++
#include <fstream>
#include <iostream>
#include<string>
using namespace std;

int main()
{
    //给每个以#开头的，加一个#以降低它的等级
    string line;
    // 以写模式打开文件
    ifstream outfile;
    string a = "#";
    outfile.open("test.md", ios::out);
    while (getline(outfile, line)) {
        if (line[0] == '#') {
            line.insert(0, a);
        }
        cout << line <<endl;
    }
    while (getline(outfile, line)) {
        cout << line << endl;
    }
    outfile.close();
    return 0;
}
```

### Defined Terms

| 中文 | 英文 | 含义 |
| ---- | ---- | ---- |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
