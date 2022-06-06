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

> C++ 支持了右值引用，rvalue reference 在$13.6.1 中会讲,这种引用主要用于内置类，一般来说我们使用“引用”这个词，是指左值引用。

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

有两个例外，一是允许令一个指向常量的指针指向一个非常量对象（2.4.2）；二是存在继承关系的类，可以将基类的指针或引用绑定到派生类对象上（15.2.3）。



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

`void*`是一种特殊的指针类型，可以存放任意对象的地址，**但不能直接操作`void*`指针所指的对象**。只能拿它和别的指针进行比较，作为函数的输入输出，或是赋给另一个void指针。

概括说来，从void* 的视角来看，内存空间仅仅是内存空间，没办法访问内存空间中的对象。  19.1.1节会详细描述。4.11.3 会描述获取void*指针的方法。

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

#### 2.4.3 Top-Level const

#### 2.4.4 constexpr and Constant Expressions

### 2.5 Dealing with Types

#### 2.5.1 Type Aliases

#### 2.5.2 The auto Type Specifier

#### 2.5.3 The decltype Type Specifier

### 2.6 Defining Our Own Data Structures

#### 2.6.1 Defining the Sales_data Type

#### 2.6.2 Using the Sales_data Class

#### 2.6.3 Writing Our Own Header Files

### Chapter Summary  

### Defined Terms




## Chapter 3 Strings, Vectors, and Arrays
### 3.1 Namespace using Declarations

### 3.2 Library string Type

#### 3.2.1 Defining and Initializing strings

#### 3.2.2 Operations on strings

#### 3.2.3 Dealing with the Characters in a string

### 3.3 Library vector Type

#### 3.3.1 Defining and Initializing vectors

#### 3.3.2 Adding Elements to a vector

#### 3.3.3 Other vector Operations

### 3.4 Introducing Iterators

#### 3.4.1 Using Iterators

#### 3.4.2 Iterator Arithmetic

### 3.5 Arrays

#### 3.5.1 Defining and Initializing Built-in Arrays

#### 3.5.2 Accessing the Elements of an Array

#### 3.5.3 Pointers and Arrays

#### 3.5.4 C-Style Character Strings

#### 3.5.5 Interfacing to Older Code

### 3.6 Multidimensional Arrays

### Chapter Summary  

### Defined Terms



## Chapter 4 Expressions
### 4.1 Fundamentals

#### 4.1.1 Basic Concepts

#### 4.1.2 Precedence and Associativity

#### 4.1.3 Order of Evaluation

### 4.2 Arithmetic Operators

### 4.3 Logical and Relational Operators

### 4.4 Assignment Operators

### 4.5 Increment and Decrement Operators

### 4.6 The Member Access Operators

### 4.7 The Conditional Operator

### 4.8 The Bitwise Operators

### 4.9 The sizeof Operator

### 4.10 Comma Operator

### 4.11 Type Conversions

#### 4.11.1 The Arithmetic Conversions

#### 4.11.2 Other Implicit Conversions

#### 4.11.3 Explicit Conversions

### 4.12 Operator Precedence Table

### Chapter Summary  

### Defined Terms



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



