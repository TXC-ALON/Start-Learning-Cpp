# Part II The C++ Library

新的C++标准目前大约2/3 用来描述标准库

## Chapter 8 The IO Library

部分IO库设施：

- `istream`：输入流类型，提供输入操作。

- `ostream`：输出流类型，提供输出操作。

- `cin`：`istream`对象，从标准输入读取数据。

- `cout`：`ostream`对象，向标准输出写入数据。

- `cerr`：`ostream`对象，向标准错误写入数据。

- `>>`运算符：从`istream`对象读取输入数据。

- `<<`运算符：向`ostream`对象写入输出数据。

- `getline`函数：从`istream`对象读取一行数据，写入`string`对象。

### 8.1 The IO Classes

IO**处理头文件**

- `iostream`定义了用于读写流的基本类型，

- `fstream`定义了读写命名文件的类型，

- `sstream`定义了读写内存中`string`对象的类型。

![](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/8-1.png)

宽字符版本的IO类型和函数的名字以`w`开始，如`wcin`、`wcout`和`wcerr`分别对应`cin`、`cout`和`cerr`。它们与其对应的普通`char`版本都定义在同一个头文件中，如头文件`fstream`定义了`ifstream`和`wifstream`类型。

##### IO类型间的关系

标准库使我们进行IO操作时不用考虑不同类型的流之间的差异。这是通过**继承机制**(inheritance)实现的。【15】【18.3】会介绍C++如何支持继承机制的。

简单来说，我们可以声明一个特定类继承自另一个类，可以将派生类的对象当作其基类的对象使用。

#### 8.1.1 No Copy or Assign for IO Objects

IO对象无拷贝或赋值

```c++
ofstream out1, out2;
out1 = out2;    // error: cannot assign stream objects
ofstream print(ofstream);   // error: can't initialize the ofstream parameter
out2 = print(out2);     // error: cannot copy stream objects
```

由于IO对象不能拷贝，因此不能将函数形参或返回类型定义为流类型。进行IO操作的函数通常以引用方式传递和返回流。读写一个IO对象会改变其状态，因此传递和返回的引用不能是`const`的。****

#### 8.1.2 Condition States

IO库条件状态：

![](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/8-2.png)

一个流一旦发生错误，其上后续的IO操作都会失败。

##### 查询流的状态

IO库定义了一个与机器无关的iostate类型，它提供了表达流状态的完整功能。IO库中定义了4个iostate类型的constexpr值。

`badbit`表示系统级错误，如不可恢复的读写错误。通常情况下，一旦`badbit`被置位，流就无法继续使用了。

在发生可恢复错误后，`failbit`会被置位，如期望读取数值却读出一个字符。如果到达文件结束位置，`eofbit`和`failbit`都会被置位。如果流未发生错误，则`goodbit`的值为0。如果`badbit`、`failbit`和`eofbit`任何一个被置位，检测流状态的条件都会失败。

```c++
while (cin >> word)
    // ok: read operation successful...
```

`good`函数在所有错误均未置位时返回`true`。而`bad`、`fail`和`eof`函数在对应错误位被置位时返回`true`。此外，在`badbit`被置位时，`fail`函数也会返回`true`。因此应该使用`good`或`fail`函数确定流的总体状态，`eof`和`bad`只能检测特定错误。

##### 管理条件状态

流对象的`rdstate`成员返回一个`iostate`值，表示流的当前状态。`setstate`成员用于将指定条件置位（叠加原始流状态）。`clear`成员的无参版本清除所有错误标志；含参版本接受一个`iostate`值，用于设置流的新状态（覆盖原始流状态）。

```c++
// remember the current state of cin
auto old_state = cin.rdstate();     // remember the current state of cin
cin.clear();    // make cin valid
process_input(cin);     // use cin
cin.setstate(old_state);    // now reset cin to its old state
```



#### 8.1.3 Managing the Output Buffer 管理输出缓冲

每个输出流都管理一个缓冲区，用于保存程序读写的数据。导致缓冲刷新（即数据真正写入输出设备或文件）的原因有很多：

- 程序正常结束。
- 缓冲区已满。
- 使用操纵符（如`endl`）显式刷新缓冲区。
- 在每个输出操作之后，可以用`unitbuf`操纵符设置流的内部状态，从而清空缓冲区。默认情况下，对`cerr`是设置`unitbuf`的，因此写到`cerr`的内容都是立即刷新的。
- 一个输出流可以被关联到另一个流。这种情况下，当读写被关联的流时，关联到的流的缓冲区会被刷新。默认情况下，`cin`和`cerr`都关联到`cout`，因此，读`cin`或写`cerr`都会刷新`cout`的缓冲区。

##### 刷新输出缓冲区

`flush`操纵符刷新缓冲区，但不输出任何额外字符。

`ends`向缓冲区插入一个空字符，然后刷新缓冲区。

```c++
cout << "hi!" << endl;   // writes hi and a newline, then flushes the buffer
cout << "hi!" << flush;  // writes hi, then flushes the buffer; adds no data
cout << "hi!" << ends;   // writes hi and a null, then flushes the buffer
```

##### unitbuf 操纵符

如果想在每次输出操作后都刷新缓冲区，可以使用`unitbuf`操纵符。它令流在接下来的每次写操作后都进行一次`flush`操作。而`nounitbuf`操纵符则使流恢复使用正常的缓冲区刷新机制。

```C++
cout << unitbuf;    // all writes will be flushed immediately
// any output is flushed immediately, no buffering
cout << nounitbuf;  // returns to normal buffering
```

##### 注意：如果程序异常终止，输出缓冲区不会被刷新。

所以在调试时，常常需要检查是无法正确输出还是卡在缓存区没输出来。

##### 关联输入和输出流

当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流。标准库将`cout`和`cin`关联在一起，因此下面的语句会导致`cout`的缓冲区被刷新：

```c++
cin >> ival;
```

交互式系统通常应该关联输入流和输出流。这意味着包括用户提示信息在内的所有输出，都会在读操作之前被打印出来。

使用`tie`函数可以关联两个流。它有两个重载版本：无参版本返回指向输出流的指针。如果本对象已关联到一个输出流，则返回的就是指向这个流的指针，否则返回空指针。`tie`的第二个版本接受一个指向`ostream`的指针，将本对象关联到此`ostream`。

```c++
cin.tie(&cout);     // illustration only: the library ties cin and cout for us
// old_tie points to the stream (if any) currently tied to cin
ostream *old_tie = cin.tie(nullptr); // cin is no longer tied
// ties cin and cerr; not a good idea because cin should be tied to cout
cin.tie(&cerr);     // reading cin flushes cerr, not cout
cin.tie(old_tie);   // reestablish normal tie between cin and cout
```

每个流同时最多关联一个流，但多个流可以同时关联同一个`ostream`。向`tie`传递空指针可以解开流的关联。

### 8.2 File Input and Output

头文件`fstream`定义了三个类型来支持文件IO：`ifstream`从给定文件读取数据，`ofstream`向指定文件写入数据，`fstream`可以同时读写指定文件。

可以通过IO操作符`<<` `>>`来读写文件，可以通过getline从ifstream读取数据。

**fstream特有的一些操作**

![8-3](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/8-3.png)

### 

#### 8.2.1 Using File Stream Objects

每个文件流类型都定义了`open`函数，它完成一些系统操作，定位指定文件，并视情况打开为读或写模式。

创建文件流对象时，如果提供了文件名（可选），`open`会被自动调用。

```C++
ifstream in(ifile);   // construct an ifstream and open the given file
ofstream out;   // output file stream that is not associated with any file
```

在C++11中，文件流对象的文件名可以是`string`对象或C风格字符数组。旧版本的标准库只支持C风格字符数组。

##### 用fstream代替iostream&

在要求使用基类对象的地方，可以用继承类型的对象代替。因此一个接受`iostream`类型引用或指针参数的函数，可以用对应的`fstream`类型来调用。

```c++
ifstream input(argv[1]);			// 打开销售记录文件
ofstream output(argv[2]);			// 打开输出文件
Sales_data total;					// 保存销售总额的变量
if(read(input,total)) {
    Sales_data trans;
    while(read(input,trans)) {
        if(total.isbn() == trans.isbn())
            total.combine(trans);
        else {
            print(output,total) << endl;		// 注意，endl 换行同样会写入文件，因为print 返
            									// 回的仍然是 output
            total = trans;
        }
    }
    print(output,total) << endl;
} else 
    cerr << "No data?!" << endl;

// read 与 print
istream &read(istream &is,Sales_data &item) {
    double price = 0;							// price 表示某书单价
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
ostream &print(ostream &os,const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

```



> 当用&引用的方式进行值传递时，就相当将自己阉割成父类对象的样子，即将只属于自己的那一部分割去。然后将剩下的这一部分当作实参传递给函数。
>
> https://blog.csdn.net/weixin_45590473/article/details/108328192



##### 成员函数open和close

可以先定义空文件流对象，再调用`open`函数将其与指定文件关联。如果`open`调用失败，`failbit`会被置位。

**检测文件是否正常打开，是个好习惯**

对一个已经打开的文件流调用`open`会失败，并导致`failbit`被置位。随后试图使用文件流的操作都会失败。如果想将文件流关联到另一个文件，必须先调用`close`关闭当前文件，再调用`clear`重置流的条件状态（`close`不会重置流的条件状态）。

##### 自动构造和析构

当`fstream`对象被销毁时，`close`会自动被调用。

#### 8.2.2 File Modes

每个流都有一个关联的文件模式，用来指出如何使用文件。

![8-4](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/8-4.png)

我们在很多地方都可以指定文件格式，调用open打开文件时可以。用一个文件名初始化流来隐式打开文件时也可以。指定文件模式有以下限制。

- 只能对`ofstream`或`fstream`对象设定`out`模式。

- 只能对`ifstream`或`fstream`对象设定`in`模式。

- 只有当`out`被设定时才能设定`trunc`模式。

- 只要`trunc`没被设定，就能设定`app`模式。在`app`模式下，即使没有设定`out`模式，文件也是以输出方式打开。

- 默认情况下，即使没有设定`trunc`，以`out`模式打开的文件也会被截断。如果想保留以`out`模式打开的文件内容，就必须同时设定`app`模式，这会将数据追加写到文件末尾；或者同时设定`in`模式，即同时进行读写操作。

- `ate`和`binary`模式可用于任何类型的文件流对象，并可以和其他任何模式组合使用。

- 与`ifstream`对象关联的文件默认以`in`模式打开，与`ofstream`对象关联的文件默认以`out`模式打开，与`fstream`对象关联的文件默认以`in`和`out`模式打开。

默认情况下，打开`ofstream`对象时，文件内容会被丢弃，阻止文件清空的方法是同时指定`app`或`in`模式。

流对象每次打开文件时都可以改变其文件模式。

```c++
ofstream out;   // no file mode is set
out.open("scratchpad");    // mode implicitly out and trunc
out.close();    // close out so we can use it for a different file
out.open("precious", ofstream::app);   // mode is out and app 输出和追加
out.close();
```

第一个open 调用未显式指定输出模式，文件隐式地以out模式打开。一般地 ， out 模式同时使用trunc模式。

除非使用append模式，否则文件内容将被情况。

### 8.3 string Streams

头文件`sstream`定义了三个类型来支持内存IO：`istringstream`从`string`读取数据，`ostringstream`向`string`写入数据，`stringstream`可以同时读写`string`的数据。使得string就好像一个IO流一样。

![8-5](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/8-5.png)

#### 8.3.1 Using an istringstream

### 使用istringstream（Using an istringstream）

```c++
// members are public by default
struct PersonInfo
{
    string name;
    vector<string> phones;
};

string line, word;   // will hold a line and word from input, respectively
vector<PersonInfo> people;    // will hold all the records from the input
// read the input a line at a time until cin hits end-of-file (or another error)
while (getline(cin, line))
{
    PersonInfo info;    // create an object to hold this record's data
    istringstream record(line);    // bind record to the line we just read
    record >> info.name;    // read the name
    while (record >> word)  // read the phone numbers
        info.phones.push_back(word);   // and store them
    people.push_back(info);    // append this record to people
}
```



> 流插入,流提取运算符重载和类型转换的讲解和实例
>
> https://bbs.huaweicloud.com/blogs/271271
>
> ```c++
> template<typename _Traits>
>  inline basic_ostream<char, _Traits>&
>  operator<<(basic_ostream<char, _Traits>& ___out, const char* __s)
>  {
>    if (!__s)
> 	___out.setstate(ios_base::badbit);
>    else
> 	__ostream_insert(___out, __s,
> 			 static_cast<streamsize>(_Traits::length(__s)));
>    return ___out;
>  }
> ```
>
> <<的模板源码，在ostream600行左右，目前来看它可以过滤掉空格，回头等学完模板来研究一下。

#### 8.3.2 Using ostringstreams

### 使用ostringstream（Using ostringstreams）

对文本文件，进行构造后（修改，判断等操作），最后一起打印时，ostringstream很好用。

```C++
for (const auto &entry : people)
{ // for each entry in people
    ostringstream formatted, badNums;   // objects created on each loop
    for (const auto &nums : entry.phones)
    { // for each number
        if (!valid(nums))
        {
            badNums << " " << nums;  // string in badNums
        }
        else
            // ''writes'' to formatted's string
            formatted << " " << format(nums);
    }

    if (badNums.str().empty())   // there were no bad numbers
        os << entry.name << " "  // print the name
            << formatted.str() << endl;   // and reformatted numbers
    else  // otherwise, print the name and bad numbers
        cerr << "input error: " << entry.name
            << " invalid number(s) " << badNums.str() << endl;
}
```



### Chapter Summary 

C++使用标准库来处理面向流的输入和输出。

- iostream处理控制台IO
- fstream处理命名文件IO
- stringstream处理内存String的IO

fstream 以及stringstream都继承自iostream

### Defined Terms

| 中文     | 英文            | 含义                                                         |
| -------- | --------------- | ------------------------------------------------------------ |
| 条件状态 | condition state | 可被任何流类使用的一组标志和函数，用来指出给定流是否可用     |
| 文件流   | file stream     | 用来读写命名文件的流对象。                                   |
|          | open            | 接受一个string或C风格字符串参数，指定要打开的文件名，它还可以接受一个可选的参数。指明文件打开模式 |
|          | close           | 关闭流所关联的文件，调用close后才可以调用open打开另一个文件。 |
|          |                 |                                                              |
|          |                 |                                                              |
|          |                 |                                                              |
|          |                 |                                                              |



## Chapter 9 Sequential Containers

一个容器就是一些特定类型对象的集合。

顺序容器为程序员提供了控制元素存储和访问顺序的能力。这种顺序不依赖于元素的值，而是和元素加入容器的位置相对应。

### 9.1 Overview of the Sequential Containers

所有的顺序都提供了快速顺序访问元素的能力。但是这些容器在以下方面都有不同的性能折中。

- 向容器添加或从容器中删除元素的代价
- 非顺序访问容器中元素的代价

顺序容器类型：

![9-1](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-1.png)

|      类型      |                             特性                             |
| :------------: | :----------------------------------------------------------: |
|    `vector`    | 可变大小数组。支持快速随机访问。在尾部之外的位置插入/删除元素可能很慢 |
|    `deque`     |   双端队列。支持快速随机访问。在头尾位置插入/删除速度很快    |
|     `list`     | 双向链表。只支持双向顺序访问。在任何位置插入/删除速度都很快  |
| `forward_list` | 单向链表。只支持单向顺序访问。在任何位置插入/删除速度都很快  |
|    `array`     |      固定大小数组。支持快速随机访问。不能添加/删除元素       |
|    `string`    | 类似`vector`，但用于保存字符。支持快速随机访问。在尾部插入/删除速度很快 |

`forward_list`和`array`是C++11新增类型。与内置数组相比，`array`更安全易用。

为了避免开销，`forward_list`没有`size`操作。



#### 容器选择原则：

- 除非有合适的理由选择其他容器，否则应该使用`vector`。

- 如果程序有很多小的元素，且空间的额外开销很重要，则不要使用`list`或`forward_list`。

- 如果程序要求随机访问容器元素，则应该使用`vector`或`deque`。

- 如果程序需要在容器头尾位置插入/删除元素，但不会在中间位置操作，则应该使用`deque`。

- 如果程序只有在读取输入时才需要在容器中间位置插入元素，之后需要随机访问元素。则：

  - 先确定是否真的需要在容器中间位置插入元素。当处理输入数据时，可以先向`vector`追加数据，再调用标准库的`sort`函数重排元素，从而避免在中间位置添加元素。

  - 如果必须在中间位置插入元素，可以在输入阶段使用`list`。输入完成后将`list`中的内容拷贝到`vector`中。

- 不确定应该使用哪种容器时，可以先只使用`vector`和`list`的公共操作：使用迭代器，不使用下标操作，避免随机访问。这样在必要时选择`vector`或`list`都很方便。

### 9.2 Container Library Overview

这一节，会介绍适用于所有容器的操作。

每个容器都定义在一个头文件中，文件名与类型名相同。容器均为模板类型。

![9-2](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-2.png)



#### 9.2.1 Iterators 迭代器

类似容器，迭代器有着公共的接口：如果一个迭代器提供某个操作，那么所有提供相同操作的迭代器度这个操作的实现方式都是相同的。例如访问容器元素（解引用），递增运算符等等。

##### 标准迭代器支持的操作

![3-6](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/3-6.png)

`PS：forward_list`类型不支持递减运算符`--`。

##### 标准迭代器支持的算术运算

这些运算只支持`string`,`vector`,`deque`,`array`的迭代器。

![3-6](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/3-7.png)

##### 迭代器范围

**迭代器的范围是标准库的基础**

一个迭代器范围（iterator range）由一对迭代器表示。

这两个迭代器通常被称为`begin`和`end`，分别指向同一个容器中的元素或尾后地址。

`end`迭代器不会指向范围中的最后一个元素，而是指向尾元素之后的位置。这种元素范围被称为左闭合区间（left-inclusive interval），其标准数学描述为`[begin，end）`。迭代器`begin`和`end`必须指向相同的容器，`end`可以与`begin`指向相同的位置，但不能指向`begin`之前的位置（由程序员确保）。

##### 左闭合范围蕴含的编程假定

假定`begin`和`end`构成一个合法的迭代器范围，则：

- 如果`begin`等于`end`，则范围为空。

- 如果`begin`不等于`end`，则范围内至少包含一个元素，且`begin`指向该范围内的第一个元素。

- 可以递增`begin`若干次，令`begin`等于`end`。

```c++
while (begin != end)
{
    *begin = val;   // ok: range isn't empty so begin denotes an element
    ++begin;    // advance the iterator to get the next element
}
```



#### 9.2.2 Container Type Members

部分容器还提供反向迭代器（++就是--）【10.4.3】会介绍。

通过类型别名，可以在不了解容器元素类型的情况下使用元素。如果需要元素类型，可以使用容器的`value_type`。如果需要元素类型的引用，可以使用`reference`或`const_reference`。

> 这里我还疑惑，为什么要搞这个东西，比如`vector<int>::value_type x;`其实就是`int x`，这不是脱裤子放屁吗？但是稍微查了下，就发现这实际上是提供了一层抽象。
>
> > ```c++
> > typedef _Vector_base<_Tp, _Alloc>			_Base;
> >    typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
> >    typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Alloc_traits;
> > public:
> > typedef _Tp              value_type;
> > typedef typename _Base::pointer        pointer;
> > typedef typename _Alloc_traits::const_pointer    const_pointer;
> > typedef typename _Alloc_traits::reference       reference;
> > typedef typename _Alloc_traits::const_reference  const_reference;
> > ```
>
> 底层是用typedef _Tp来做的，所以实际上和`typedef double _DBX32`没啥区别。
>
> 都是为了方便后面的操作，比如改一下容器内部类型，不必一个个去修改变量前的类型名。
>
> 在模板里面肯定有更多的应用。

#### 9.2.3 begin and end Members

`begin`和`end`操作生成指向容器中第一个元素和尾后地址的迭代器。其常见用途是形成一个包含容器中所有元素的迭代器范围。

`begin`和`end`操作有多个版本：带`r`的版本返回反向迭代器。以`c`开头的版本（C++11新增）返回`const`迭代器。不以`c`开头的版本都是重载的，当对非常量对象调用这些成员时，返回普通迭代器，对`const`对象调用时，返回`const`迭代器。

```c++
list<string> a = {"Milton", "Shakespeare", "Austen"};
auto it1 = a.begin();    // list<string>::iterator
auto it2 = a.rbegin();   // list<string>::reverse_iterator
auto it3 = a.cbegin();   // list<string>::const_iterator
auto it4 = a.crbegin();  // list<string>::const_reverse_iterator
```

当`auto`与`begin`或`end`结合使用时，返回的迭代器类型依赖于容器类型。但调用以`c`开头的版本仍然可以获得`const`迭代器，与容器是否是常量无关。

当程序不需要写操作时，应该使用`cbegin`和`cend`。

#### 9.2.4 Defining and Initializing a Container 容器初始化

每个容器都有对应的构造函数，除了array之外，其他容器的默认构造函数都会创建一个指定类的空容器，也可以接受指定容器大小和元素初始值的参数。

容器定义和初始化方式：

![9-3](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-3.png)

##### 将一个容器初始化为另一个容器的拷贝

将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同。

传递迭代器参数来拷贝一个范围时，不要求容器类型相同，而且新容器和原容器中的元素类型也可以不同，但是要能进行类型转换。

```c++
// each container has three elements, initialized from the given initializers
list<string> authors = {"Milton", "Shakespeare", "Austen"};
vector<const char*> articles = {"a", "an", "the"};
list<string> list2(authors);        // ok: types match
deque<string> authList(authors);    // error: container types don't match
vector<string> words(articles);     // error: element types must match
// ok: converts const char* elements to string
forward_list<string> words(articles.begin(), articles.end());
```

##### 列表初始化

C++11允许对容器进行列表初始化。

```c++
// each container has three elements, initialized from the given initializers
list<string> authors = {"Milton", "Shakespeare", "Austen"};
vector<const char*> articles = {"a", "an", "the"};
```

##### 与顺序容器大小相关的构造函数

```c++
vector<int> ivec(10,-1);
list<string>svec(10,"hi");
forward_list<int>ivec(10);	//10个空元素，每个都是0
deque<string> svec(10);  //10个空元素，都是空string
```

如果元素没有默认构造参数，除了元素大小外，必须制定一个显式的初始值。

注: 只有顺序容器的构造函数才接受大小参数，关联容器并不支持

##### 标准库array具有固定大小 

定义和使用`array`类型时，需要同时指定元素类型和容器大小。

```c++
array<int, 42>      // type is: array that holds 42 ints
array<string, 10>   // type is: array that holds 10 strings
array<int, 10>::size_type i;   // array type includes element type and size
array<int>::size_type j;       // error: array<int> is not a type
```

对`array`进行列表初始化时，初始值的数量不能大于`array`的大小。如果初始值的数量小于`array`的大小，则只初始化靠前的元素，剩余元素会被值初始化。如果元素类型是类类型，则该类需要一个默认构造函数。

可以对`array`进行拷贝或赋值操作，但要求二者的元素类型和大小都相同。

#### 9.2.5 Assignment and swap

容器赋值操作：

![9-4](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-4.png)

##### 使用assign（仅顺序容器）

赋值运算符两侧的运算对象必须类型相同。`assign`允许用不同但相容的类型赋值，或者用容器的子序列赋值。

```c++
list<string> names;
vector<const char*> oldstyle;
names = oldstyle;   // error: container types don't match
// ok: can convert from const char*to string
names.assign(oldstyle.cbegin(), oldstyle.cend());
```

由于其旧元素被替换，因此传递给`assign`的迭代器不能指向调用`assign`的容器本身。

assign的第二个版本接受一个整型值和一个元素值，它用指定数目且具有相同给定元素替换容器中原有的元素

```c++
list<string>alist1(1);
alist1.assign(10,"hello"); // 十个hello
```



##### 使用swap

`swap`交换两个相同类型容器的内容。除`array`外，`swap`不对任何元素进行拷贝、删除或插入操作，只交换两个容器的内部数据结构，因此可以保证快速完成。

```c++
vector<string> svec1(10);   // vector with ten elements
vector<string> svec2(24);   // vector with 24 elements
swap(svec1, svec2);
```

赋值相关运算会导致指向左边容器内部的迭代器、引用和指针失效。而`swap`操作交换容器内容，不会导致迭代器、引用和指针失效（`array`和`string`除外）。

**对于`array`，`swap`会真正交换它们的元素**。因此在`swap`操作后，指针、引用和迭代器所绑定的元素不变，但元素值已经被交换。

> std::array直接将数据保存在对象自身里，并不通过指针来间接访问。被保存的对象不是被管理的资源，而是array类本身的data member，没得“交换指针”。想自己做成交换指针也做不成。

```c++
array<int, 3> a = { 1, 2, 3 };
array<int, 3> b = { 4, 5, 6 };
auto p = a.cbegin(), q = a.cend();
a.swap(b);
// 输出交换后的值，即4、5、6
while (p != q)
{
    cout << *p << endl;
    ++p;
}
```

对于其他容器类型（除`string`），指针、引用和迭代器在`swap`操作后仍指向操作前的元素，但这些元素已经属于不同的容器了。

```c++
vector<int> a = { 1, 2, 3 };
vector<int> b = { 4, 5, 6 };
auto p = a.cbegin(), q = a.cend();
a.swap(b);
// 输出交换前的值，即1、2、3
while (p != q)
{
    cout << *p << endl;
    ++p;
}
```

`array`不支持`assign`，也不允许用花括号列表进行赋值。

```c++
array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
array<int, 10> a2 = {0};    // elements all have value 0
a1 = a2;    // replaces elements in a1
a2 = {0};   // error: cannot assign to an array from a braced list
```

新标准库同时提供了成员和非成员函数版本的`swap`。非成员版本的`swap`在泛型编程中非常重要，建议统一使用非成员版本的`swap`。

#### 9.2.6 Container Size Operations

`size`成员返回容器中元素的数量；`empty`当`size`为0时返回`true`，否则返回`false`；`max_size`返回一个大于或等于该类型容器所能容纳的最大元素数量的值。`forward_list`支持`max_size`和`empty`，但不支持`size`。

#### 9.2.7 Relational Operators

每个容器类型都支持相等运算符（`==`、`!=`）。除无序关联容器外，其他容器都支持关系运算符（`>`、`>=`、`<`、`<=`）。关系运算符两侧的容器类型和保存元素类型都必须相同。

两个容器的比较实际上是元素的逐对比较，其工作方式与`string`的关系运算符类似：

- 如果两个容器大小相同且所有元素对应相等，则这两个容器相等。

- 如果两个容器大小不同，但较小容器中的每个元素都等于较大容器中的对应元素，则较小容器小于较大容器。

- 如果两个容器都不是对方的前缀子序列，则两个容器的比较结果取决于第一个不等元素的比较结果。

```c++
vector<int> v1 = { 1, 3, 5, 7, 9, 12 };
vector<int> v2 = { 1, 3, 9 };
vector<int> v3 = { 1, 3, 5, 7 };
vector<int> v4 = { 1, 3, 5, 7, 9, 12 };
v1 < v2     // true; v1 and v2 differ at element [2]: v1[2] is less than v2[2]
v1 < v3     // false; all elements are equal, but v3 has fewer of them;
v1 == v4    // true; each element is equal and v1 and v4 have the same size()
v1 == v2    // false; v2 has fewer elements than v1
```

容器的相等运算符实际上是使用元素的`==`运算符实现的，而其他关系运算符则是使用元素的`<`运算符。如果元素类型不支持所需运算符，则保存该元素的容器就不能使用相应的关系运算。

### 9.3 Sequential Container Operations

顺序容器与关联容器的不同之处在于两者组织元素的方式，上一节介绍了所以元素都适用的操作，这一章将介绍顺序容器特有的操作。

#### 9.3.1 Adding Elements to a Sequential Container

除`array`外（因为这些操作会改变容器大小），所有标准库容器都提供灵活的内存管理，在运行时可以动态添加或删除元素。

![9-5](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-5.png)

**向一个vector、string、deque插入元素会使所以指向容器的迭代器，引用和指针失效**

根本原因是因为插入元素可能会引起内存空间的重新分配，可能会搬到新的空间去。自然就失效了。

> 向容器添加元素后：
>
> 1.对于vector 或者 string
> 如果存储空间被重新分配，则指向容器的迭代器，指针和引用都会失效。
> 如果存储空间未重新分配，指向插入位置之前元素的迭代器，指针和引用仍有效，但指向存在的元素的引用和指针不会失效。
>
> 2.对于deque
> 插入到除首尾位置之外的任何位置都会导致迭代器，指针和引用失效。
> 如果在首尾位置添加元素，迭代器会失效，但指向存在的元素的指针和引用不会失效。
>
> 3.对于list和forward_list
> 指向容器的迭代器（包括尾后迭代器和首前迭代器），指针和引用仍有效。
>
> 当我们从一个容器中删除元素后，指向被删除元素的迭代器，指针和引用会失效，这应该不会令人惊讶。毕竟，这些元素都已经被销毁了。当我们删除一个元素后：
>
> 1.对于list和forward_list
> 指向容器其它位置的迭代器，引用和指针仍有效。
>
> 2.对于deque
> 如果在首尾之外的任何位置删除元素，那么指向被删除元素外的其它元素的迭代器，引用和指针都会失效。
>
> 如果删除deque的尾元素，则尾后迭代器也会失效，但其它迭代器，指针和引用不受影响；如果删除首元素，这些也不会受影响。
>
> 3.对于vector和string
> 指向被删元素之前的迭代器，引用和指针仍有效。
>
> 注意：使用失效的迭代器，指针或引用是严重的运行时错误。因此必须保证每次改变容器的操作之后都正确的重新定位迭代器。这个建议对于vector,string和deque尤为重要。
> ————————————————
> 版权声明：本文为CSDN博主「拥抱@」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
> 原文链接：https://blog.csdn.net/tonglin12138/article/details/88359618

##### push_back

`push_back`将一个元素追加到容器尾部，`push_front`将元素插入容器头部。

```c++
// read from standard input, putting each word onto the end of container
string word;
while (cin >> word)
    container.push_back(word);
```

##### push_front

list,forward_list,deque容器还支持push_front 插入容器头部。

##### insert 在特定位置添加元素

`insert`将元素插入到迭代器指定的位置之前。一些不支持`push_front`的容器可以使用`insert`将元素插入开始位置。

```c++
vector<string> svec;
list<string> slist;
// equivalent to calling slist.push_front("Hello!");
slist.insert(slist.begin(), "Hello!");
// no push_front on vector but we can insert before begin()
// warning: inserting anywhere but at the end of a vector might be slow
svec.insert(svec.begin(), "Hello!");
```

将元素插入到`vector`、`deque`或`string`的任何位置都是合法的，但可能会很耗时。

##### insert 插入范围内元素

insert 还可以接受更多的参数。

- 接受一个元素数目和一个值，将指定数量的元素添加到指定位置之前，且按照给定值初始化。
- 接受一对迭代器或一个初始化列表的insert，将给定范围中的元素插入到指定位置之前。

```c++
vector<string> v = {"quasi","simba","Lforl","fas"};
list<string> slist;
slist.insert(slist.begin(),v.end()-2,v.end());
slist.insert(slist.end(),{"a","b","v","d"});
```

在新标准库中，接受元素个数或范围的`insert`版本返回指向第一个新增元素的迭代器，而旧版本中这些操作返回`void`。如果范围为空，不插入任何元素，`insert`会返回第一个参数。

##### insert 使用insert返回值

```c++
list<string> 1st;
auto iter = 1st.begin();
while (cin >> word)
    iter = 1st.insert(iter, word);  // same as calling push_front
```

将读入的新元素插入iter所指向的元素之前的位置，insert返回的迭代器恰好指向这个新元素，如此重复循环。

##### 使用emplace

新标准库增加了三个直接构造而不是拷贝元素的操作：`emplace_front`、`emplace_back`和`emplace`，其分别对应`push_front`、`push_back`和`insert`。当调用`push`或`insert`时，元素对象被拷贝到容器中。而调用`emplace`时，则是将参数传递给元素类型的构造函数，直接在容器的内存空间中构造元素。

```c++
// construct a Sales_data object at the end of c
// uses the three-argument Sales_data constructor
c.emplace_back("978-0590353403", 25, 15.99);
// error: there is no version of push_back that takes three arguments
c.push_back("978-0590353403", 25, 15.99);
// ok: we create a temporary Sales_data object to pass to push_back
c.push_back(Sales_data("978-0590353403", 25, 15.99));
```

传递给`emplace`的参数必须与元素类型的构造函数相匹配。



注：

- `forward_list`有特殊版本的`insert`和`emplace`操作，且不支持`push_back`和`emplace_back`。

- `vector`和`string`不支持`push_front`和`emplace_front`。

#### 9.3.2 Accessing Elements 访问元素

包括`array`在内， 每个顺序容器都有一个`front`成员函数，而除了`forward_list`之外的顺序容器还有一个`back`成员函数。这两个操作分别返回首元素和尾元素的引用。

在调用`front`和`back`之前，要确保容器非空。

顺序容器的元素访问操作：

![9-6](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-6.png)

##### 访问成员函数返回的是引用

在容器中访问元素的成员函数都返回引用类型。如果容器是`const`对象，则返回`const`引用，否则返回普通引用。如果希望修改容器内的值，应该使用引用来取。

```c++
if (!c.empty()) {
	c.front() = 42; // assigns 42 to the first element in c
	auto &v = c.back(); // get a reference to the last element
	v = 1024; // changes the element in c
	auto v2 = c.back(); // v2 is not a reference; it’s a copy of c.back()
	v2 = 0; // no change to the element in c
}
```

##### 下标访问和安全的随机访问

可以快速随机访问的容器（`string`、`vector`、`deque`和`array`）都提供下标运算符。保证下标有效是程序员的责任。如果希望确保下标合法，可以使用`at`成员函数。

`at`类似下标运算，但如果下标越界，`at`会抛出`out_of_range`异常。

```c++
vector<string> svec;  // empty vector
cout << svec[0];      // run-time error: there are no elements in svec!
cout << svec.at(0);   // throws an out_of_range exception
```



#### 9.3.3 Erasing Elements

顺序容器的元素删除操作：

![9-7](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-7.png)

删除`deque`中除首尾位置之外的任何元素都会使所有迭代器、引用和指针失效。删除`vector`或`string`的元素后，指向删除点之后位置的迭代器、引用和指针也都会失效。

删除元素前，程序员必须确保目标元素存在。

`pop_front`和`pop_back`函数分别删除首元素和尾元素。`vector`和`string`类型不支持`pop_front`，`forward_list`类型不支持`pop_back`。

`erase`函数删除指定位置的元素。可以删除由一个迭代器指定的单个元素，也可以删除由一对迭代器指定的范围内的所有元素。两种形式的`erase`都返回指向删除元素（最后一个）之后位置的迭代器。

```c++
// delete the range of elements between two iterators
// returns an iterator to the element just after the last removed element
elem1 = slist.erase(elem1, elem2);  // after the call elem1 == elem2
```

`clear`函数删除容器内的所有元素。

#### 9.3.4 Specialized forward_list Operations

在`forward_list`中添加或删除元素的操作是通过改变给定元素之后的元素来完成的。

![9-8](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-8.png)

`forward_list`的插入和删除操作：

![9-9](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-9.png)

当在forward_list中添加或删除元素时，我们必须关注两个迭代器--一个指向我们要处理的元素，另一个指向其前驱。

```c++
forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
auto prev = flst.before_begin(); // denotes element "off the start" of flst
auto curr = flst.begin(); // denotes the first element in flst
while (curr != flst.end()) { // while there are still elements to process
	if (*curr % 2) // if the element is odd
		curr = flst.erase_after(prev); // erase it and move curr
	else {
		prev = curr; // move the iterators to denote the next
		++curr; // element and one before the next element
		}
}
```



#### 9.3.5 Resizing a Container

`array` 不支持resize，当前大小大了，截取；当前大小小了，填充新元素。

顺序容器的大小操作：

![9-10](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-10.png)

`resize`函数接受一个可选的元素值参数，用来初始化添加到容器中的元素，否则新元素进行值初始化。如果容器保存的是类类型元素，且`resize`向容器添加新元素，则必须提供初始值，或元素类型提供默认构造函数。

#### 9.3.6 Container Operations May Invalidate Iterators

向容器中添加或删除元素可能会使指向容器元素的指针、引用或迭代器失效。失效的指针、引用或迭代器不再表示任何元素，使用它们是一种严重的程序设计错误。

- 向容器中添加元素后：

  - 如果容器是`vector`或`string`类型，且存储空间被重新分配，则指向容器的迭代器、指针和引用都会失效。如果存储空间未重新分配，指向插入位置之前元素的迭代器、指针和引用仍然有效，但指向插入位置之后元素的迭代器、指针和引用都会失效。

  - 如果容器是`deque`类型，添加到除首尾之外的任何位置都会使迭代器、指针和引用失效。如果添加到首尾位置，则迭代器会失效，而指针和引用不会失效。

  - 如果容器是`list`或`forward_list`类型，指向容器的迭代器、指针和引用仍然有效。

- 从容器中删除元素后，指向被删除元素的迭代器、指针和引用失效：

  - 如果容器是`list`或`forward_list`类型，指向容器其他位置的迭代器、指针和引用仍然有效。

  - 如果容器是`deque`类型，删除除首尾之外的任何元素都会使迭代器、指针和引用失效。如果删除尾元素，则尾后迭代器失效，其他迭代器、指针和引用不受影响。如果删除首元素，这些也不会受影响。

  - 如果容器是`vector`或`string`类型，指向删除位置之前元素的迭代器、指针和引用仍然有效。但尾后迭代器总会失效。

**必须保证在每次改变容器后都正确地重新定位迭代器。**

```c++
vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
auto iter = vi.begin(); // call begin, not cbegin because we’re changing vi
while (iter != vi.end()) {
	if (*iter % 2) {
		iter = vi.insert(iter, *iter); // duplicate the current element
		iter += 2; // advance past this element and the one inserted before it
	} else
		iter = vi.erase(iter); // remove even elements
		// don’t advance the iterator; iter denotes the element after the one we erased
}
```

这段程序的目的是删除偶数，复制奇数。

那么要注意erase后，迭代器指向序列下一个元素；insert在给定位置前插入新元素，insert后，迭代器指向新插入元素的迭代器，所以要+2，越过这两个，指向下一个未处理的元素。

**不要保存`end`函数返回的迭代器。**

因为很容易混乱。

```c++
// safer:在每个循环步骤添加/删除元素后都重新计算end
while (begin != v.end())
{
    // do some processing
    ++begin;    // advance begin because we want to insert after this element
    begin = v.insert(begin, 42);    // insert the new value
    ++begin;    // advance begin past the element we just added
}
```



### 9.4 How a vector Grows

为了快速随机访问,vector 将元素连续存储。

> 所谓“随机存取”，指的是当存储器中的消息被读取或写入时，所需要的时间与这段信息所在的位置无关。相对的，读取或写入顺序访问（SequentialAccess）存储设备中的信息时，其所需要的时间与位置就会有关系（如磁带）。

而为了避免扩容带来的频繁内存移动，`vector`和`string`的实现通常会分配比新空间需求更大的内存空间，容器预留这些空间作为备用，可用来保存更多新元素。

容器大小管理操作：

![9-11](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-11.png)

`capacity`函数返回容器在不扩充内存空间的情况下最多可以容纳的元素数量。`reserve`函数告知容器应该准备保存多少元素，它并不改变容器中元素的数量，仅影响容器预先分配的内存空间大小。

![9-12](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-12.png)

```c++
#include <iostream>
#include<vector>
using namespace std;
int main() {
    vector<int> a = {1,3,4};
    cout<<a.capacity()<<endl;
    cout<<a.size();
    cout<<endl;
    a.push_back(4);
    cout<<a.capacity()<<endl;
    cout<<a.size();
    cout<<endl;
    for(int i = 0;i<8;i++){
        a.push_back(4);
    }
    cout<<a.capacity()<<endl;
    cout<<a.size();
    cout<<endl;
    a.push_back(4);
    cout<<a.capacity()<<endl;
    cout<<a.size();
    return 0;
}

/*
3
3
6
4
12
12
24
13
*/
```

> 可以看到，当超出容器大小时，vector会扩容一倍

只有当需要的内存空间超过当前容量时，`reserve`才会真正改变容器容量，分配不小于需求大小的内存空间。当需求大小小于当前容量时，`reserve`并不会退回内存空间。因此在调用`reserve`之后，`capacity`会大于或等于传递给`reserve`的参数。

在C++11中可以使用`shrink_to_fit`函数来要求`deque`、`vector`和`string`退回不需要的内存空间（并不保证退回）。

### 9.5 Additional string Operations

#### 9.5.1 Other Ways to Construct strings 构建string的其他方法

构造`string`的其他三个构造函数：

![9-13](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-13.png)

这些构造函数接受一个string或一个const char* 参数。还接受（可选） 指定拷贝多少个字符的参数。

从另一个`string`对象拷贝字符构造`string`时，如果提供的拷贝开始位置（可选）大于给定`string`的大小，则构造函数会抛出`out_of_range`异常。

子字符串操作：

![9-14](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-14.png)

如果传递给`substr`函数的开始位置超过`string`的大小，则函数会抛出`out_of_range`异常。

#### 9.5.2 Other Ways to Change a string

修改`string`的操作：

![9-15](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-15.png)

`append`函数是在`string`末尾进行插入操作的简写形式。

```c++
string s("C++ Primer"), s2 = s;     // initialize s and s2 to "C++ Primer"
s.insert(s.size(), " 4th Ed.");     // s == "C++ Primer 4th Ed."
s2.append(" 4th Ed.");     // equivalent: appends " 4th Ed." to s2; s == s2
```

`replace`函数是调用`erase`和`insert`函数的简写形式。

```c++
// equivalent way to replace "4th" by "5th"
s.erase(11, 3);         // s == "C++ Primer Ed."
s.insert(11, "5th");    // s == "C++ Primer 5th Ed."
// starting at position 11, erase three characters and then insert "5th"
s2.replace(11, 3, "5th");   // equivalent: s == s2
```

##### 改变string的多种重载函数

`append` `assign` `insert` `replace` 都有多个重载版本

- assign 和 append 无需指定要替换string中哪个部分，因为assign总是全部替换string，而append总是在string追加。

-  replace函数提供两种删除元素方式的方法，可以通过一个位置和一个长度来指定范围，也可以通过一个迭代器范围来指定。
- insert函数允许我们用两个方式指定插入点：用一个下标或一个迭代器。这两种情况下，新元素都会插入到给定下标（或迭代器）之前的位置。

但是insert 不支持下标和初始化列表参数。如果我们希望使用迭代器指定插入点，就不能用字符指针来指定新字符的来源。

#### 9.5.3 string Search Operations

`string`的每个搜索操作都返回一个`string::size_type`值，表示匹配位置的下标。如果搜索失败，则返回一个名为`string::npos`的`static`成员。标准库将`npos`定义为`const string::size_type`类型，并初始化为-1。

不建议用`int`或其他带符号类型来保存`string`搜索函数的返回值。

`string`搜索操作：

![9-16](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-16.png)

#### 9.5.4 The compare Functions

`string`类型提供了一组`compare`函数进行字符串比较操作，类似C标准库的`strcmp`函数。

根据s是等于、大于还是小于参数指定的字符串，s.compare 返回0，正数或负数。

`compare`函数的几种参数形式：

![9-17](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-17.png)

#### 9.5.5 Numeric Conversions

C++11增加了`string`和数值之间的转换函数：

![9-18](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-18.png)

进行数值转换时，`string`参数的第一个非空白字符必须是符号（`+`或`-`）或数字。它可以以`0x`或`0X`开头来表示十六进制数。对于转换目标是浮点值的函数，`string`参数也可以以小数点开头，并可以包含`e`或`E`来表示指数部分。

如果给定的`string`不能转换为一个数值，则转换函数会抛出`invalid_argument`异常。如果转换得到的数值无法用任何类型表示，则抛出`out_of_range`异常。

### 9.6 Container Adaptors 适配器

标准库定义了`stack`、`queue`和`priority_queue`三种容器适配器。容器适配器可以改变已有容器的工作机制。

所有容器适配器都支持的操作和类型：

![9-19](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-19.png)

默认情况下，`stack`和`queue`是基于`deque`实现的，`priority_queue`是基于`vector`实现的。可以在创建适配器时将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型。

```c++
// empty stack implemented on top of vector
stack<string, vector<string>> str_stk;
// str_stk2 is implemented on top of vector and initially holds a copy of svec
stack<string, vector<string>> str_stk2(svec);
```

所有适配器都要求容器具有添加和删除元素的能力，因此适配器不能构造在`array`上。适配器还要求容器具有添加、删除和访问尾元素的能力，因此也不能用`forward_list`构造适配器。

##### stack

栈适配器`stack`定义在头文件`stack`中，其支持的操作如下：

![9-20](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-20.png)

##### queue

队列适配器`queue`和`priority_queue`定义在头文件`queue`中，其支持的操作如下：

![9-21](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/9-21.png)

`queue`使用先进先出（first-in，first-out，FIFO）的存储和访问策略。进入队列的对象被放置到队尾，而离开队列的对象则从队首删除。

### Chapter Summary  

标准库容器是模板类型，用来保存给定类型的对象，在一个顺序容器中，元素是按顺序操作的。通过为止来访问，

除array外，所有的容器都提供高效的动态内存管理。不用关心元素存储位置。

当我们使用添加和删除元素的容器操作时，必须注意这些操作可能使得容器中的迭代器、指针、引用失效。

### Defined Terms

|    中文    |          英文           | 含义                                                         |
| :--------: | :---------------------: | ------------------------------------------------------------ |
|   适配器   |         adaptor         | 标准库类型、函数或迭代器，他们接受一个类型、函数或迭代器，使其行为像另外一个类型、函数或迭代器一样。 |
|  单向列表  |      forward_list       | forward_list的元素只能顺序访问，不支持--，与其他容器不同，插入和删除发生在给定的迭代器之后的位置。因此，除了通常的尾后迭代器外，它还有一个首前迭代器。在添加新元素后，原有的指向forward_list的迭代器仍有效。在删除元素后，只有原来指向被删除元素的迭代器才会失效。 |
| 左闭合区间 | left-inclusive interval | 值范围，包含首元素，不包括尾元素。                           |
|            |                         |                                                              |
|            |                         |                                                              |
|            |                         |                                                              |
|            |                         |                                                              |
|            |                         |                                                              |



## Chapter 10 Generic Algorithms 泛型算法

标准库定义了一组泛型算法，来实现各种有用的操作。

称他们为算法，是因为它们实现了一些经典算法的公共接口，如排序和搜索

称他们为泛型，是因为他们可以用于不同类型的元素和多种容器类型

### 10.1 Overview

大多数算法都定义在头文件`algorithm`中，此外标准库还在头文件`numeric`中定义了一组数值泛型算法。一般情况下，这些算法并不直接操作容器，而是遍历由两个迭代器指定的元素范围进行操作。

`find`函数将范围中的每个元素与给定值进行比较，返回指向第一个等于给定值的元素的迭代器。如果无匹配元素，则返回其第二个参数来表示搜索失败。

```c++
int val = 42;   // value we'll look for
// result will denote the element we want if it's in vec, or vec.cend() if not
auto result = find(vec.cbegin(), vec.cend(), val);
// report the result
cout << "The value " << val
    << (result == vec.cend() ? " is not present" : " is present") << endl;
```

另外指针就像内置数组上的迭代器，可以用find在数组中查找值：

```c++
int ia[] = {27, 210, 12, 47, 109, 83};
int val = 83;
int* result = find(begin(ia), end(ia), val);
//还可以在序列的子范围中查找
auto result = find(ia+1,ia+4,val);
```

迭代器参数令算法不依赖于特定容器，但依赖于元素类型操作。比如需要容器提供例如`<` `==`的重载版本。

泛型算法本身不会执行容器操作，它们只会运行于迭代器之上，执行迭代器操作。算法可能改变容器中元素的值，或者在容器内移动元素，但不会改变底层容器的大小（当算法操作插入迭代器`insert`时，迭代器可以向容器中添加元素，但算法自身不会进行这种操作）。

### 10.2 A First Look at the Algorithms

除了少数例外，标准库算法都对一个范围内的元素进行操作。我们将此元素范围称为“输入范围”。一般用两个迭代器来实现。

了解一个算法，最基本的就是了解它们是否读取元素、改变元素或是重排元素。

#### 10.2.1 Read-Only Algorithms 只读算法

一些算法只读取范围内元素，而不进行操作，如`find` `count`。

##### accumulate  求和

`accumulate`函数（定义在头文件`numeric`中）用于计算一个序列的和。它接受三个参数，前两个参数指定需要求和的元素范围，第三个参数是和的初值（第三个参数的类型决定加法运算符和返回值类型）。

```c++
// sum the elements in vec starting the summation with the value 0
int sum = accumulate(vec.cbegin(), vec.cend(), 0);
string sum = accumulate(v.cbegin(), v.cend(), string(""));
// error: no + on const char* 简单使用空串是不行的，因为这种类型没有定义+运算符。
string sum = accumulate(v.cbegin(), v.cend(), "");
```

建议在只读算法中使用`cbegin`和`cend`函数。

##### equal 相等

`equal`函数用于确定两个序列是否保存相同的值。它接受三个迭代器参数，前两个参数指定第一个序列范围，第三个参数指定第二个序列的首元素。

`equal`函数假定第二个序列至少与第一个序列一样长。

```c++
// roster2 should have at least as many elements as roster1
equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
```

注：只接受单一迭代器表示第二个操作序列的算法都假定**第二个序列至少与第一个序列一样长**

#### 10.2.2 Algorithms That Write Container Elements 写算法

一些算法将新值赋予序列中的元素，这时候要注意，由于算法不会进行容器操作，不会改变容器大小，所以容器大小至少不小于我们要求写入的元素数目。

##### fill 填充

`fill`函数接受两个迭代器参数表示序列范围，还接受一个值作为第三个参数，它将给定值赋予范围内的每个元素。

```c++
// reset each element to 0
fill(vec.begin(), vec.end(), 0);
fill(vec.begin(), vec.begin() + vec.size()/2, 10);
```

`fill_n`函数接受单个迭代器参数、一个计数值和一个值，它将给定值赋予迭代器指向位置开始的指定个元素。

```c++
// reset all the elements of vec to 0
fill_n(vec.begin(), vec.size(), 0);
```

向目的位置迭代器写入数据的算法都假定目的位置**足够大**，能容纳要写入的元素。

##### 算法不检查写操作

最容易犯的错误就是在空容器上写。

##### back_inserter

插入迭代器（insert iterator）是一种向容器内添加元素的迭代器。通过插入迭代器赋值时，一个与赋值号右侧值相等的元素会被添加到容器中。【10.4.1】会详细介绍迭代器。

`back_inserter`函数（定义在头文件`iterator`中）接受一个指向容器的引用，返回与该容器绑定的插入迭代器。通过此迭代器赋值时，赋值运算符会调用`push_back`将一个具有给定值的元素添加到容器中。

```c++
vector<int> vec;    // empty vector
auto it = back_inserter(vec);   // assigning through it adds elements to vec
*it = 42;   // vec now has one element with value 42
// ok: back_inserter creates an insert iterator that adds elements to vec
fill_n(back_inserter(vec), 10, 0);  // appends ten elements to vec
```

```c++
#include <iostream>
#include<vector>
#include<iterator>
using namespace std;
int main() {
    vector<int> vec;
    auto it = back_inserter(vec);
    for(int i = 0;i<10;i++){
        *it = i;
    }
    for(auto it : vec){
        cout<<it<<" ";
    }
    return 0;
}
/*
0 1 2 3 4 5 6 7 8 9
*/
```

##### copy 拷贝

`copy`函数接受三个迭代器参数，前两个参数指定输入范围，第三个参数指定目的序列的起始位置。

它将输入序列中的元素拷贝到目的序列中，返回目的位置迭代器（递增后）的值。

```c++
int a1[] = { 0,1,2,3,4,5,6,7,8,9 };
int a2[sizeof(a1) / sizeof(*a1)];     // a2 has the same size as a1
// ret points just past the last element copied into a2
auto ret = copy(begin(a1), end(a1), a2);    // copy a1 into a2
```

`copy` 返回的是其目的位置迭代器（递增后）的值。ret恰好指向拷贝到a2的尾元素之后的位置。

##### replace

`replace`函数接受四个参数，前两个迭代器参数指定输入序列，后两个参数指定要搜索的值和替换值。它将序列中所有等于第一个值的元素都替换为第二个值。

```c++
// replace any element with the value 0 with 42
replace(ilst.begin(), ilst.end(), 0, 42);
```

相对于`replace`，`replace_copy`函数可以保留原序列不变。它接受第三个迭代器参数，指定调整后序列的保存位置。

```c++
// use back_inserter to grow destination as needed
replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 0, 42);
```

很多算法都提供“copy”版本，这些版本不会将新元素放回输入序列，而是创建一个新序列保存结果。

#### 10.2.3 Algorithms That Reorder Container Elements 重排容器元素的算法.

##### sort

`sort`函数接受两个迭代器参数，指定排序范围。它利用元素类型的`<`运算符重新排列元素。

```c++
void elimDups(vector<string> &words)
{
    // sort words alphabetically so we can find the duplicates
    sort(words.begin(), words.end());
    // unique reorders the input range so that each word appears once in the
    // front portion of the range and returns an iterator one past the unique range
    auto end_unique = unique(words.begin(), words.end());
    // erase uses a vector operation to remove the nonunique elements
    words.erase(end_unique, words.end());
}
```

##### unique

`unique`函数重排输入序列，消除相邻的重复项，返回指向不重复值范围末尾的迭代器。

![10-1](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/10-1.png)

重复的元素并没有真的删除，而是通过迭代器限定范围将其屏蔽了。

##### 使用容器操作真正删除元素

本例使用了erase，而且用法比较规范，即使重复单词为空，也不会造成bug。

### 10.3 Customizing Operations

默认情况下，很多算法会比较序列中的元素，这时候要使用元素类型的`<`或`==`运算符完成操作。

标准库允许我们可以为这些算法提供自定义操作来代替默认运算符。

#### 10.3.1 Passing a Function to an Algorithm

###### 谓词

谓词（predicate）是一个可调用的表达式，其返回结果是一个能用作条件的值。

标准库算法使用的谓词分为一元谓词（unary predicate，接受一个参数）和二元谓词（binary predicate，接受两个参数）。

接受谓词参数的算法会对输入序列中的元素调用谓词，因此元素类型必须能转换为谓词的参数类型。

```c++
// comparison function to be used to sort by word length
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

// sort on word length, shortest to longest
sort(words.begin(), words.end(), isShorter);
```

稳定排序函数`stable_sort`可以维持输入序列中相等元素的原有顺序。

> https://en.cppreference.com/w/cpp/algorithm/stable_sort
>
> ```c++
> #include <algorithm>
> #include <iostream>
> #include <string>
> #include <vector>
>  
> struct Employee
> {
>     int age;
>     std::string name;  // Does not participate in comparisons
> };
>  
> bool operator<(const Employee & lhs, const Employee & rhs)
> {
>     return lhs.age < rhs.age;
> }
>  
> int main()
> {
>     std::vector<Employee> v =
>     { 
>         {108, "Zaphod"},
>         {32, "Frthur"},
>         {32, "Arthur"},
>         {108, "Ford"},
>     };  
>  
>     std::stable_sort(v.begin(), v.end());
>  
>     for (const Employee & e : v)
>         std::cout << e.age << ", " << e.name << '\n';
> }
> 
> 
> /*
> 32, Frthur
> 32, Arthur
> 108, Zaphod
> 108, Ford
> */
> ```
>
> 简单来说，对于同名元素的排序后按照输入顺序。

#### 10.3.2 Lambda Expressions

`find_if`函数接受两个迭代器参数和一个谓词参数。迭代器参数用于指定序列范围，之后对序列中的每个元素调用给定谓词，并返回第一个使谓词返回非0值的元素。如果不存在，则返回尾迭代器。



##### 介绍lambda

对于一个对象或表达式，如果可以对其使用调用运算符`()`，则称它为可调用对象（callable object）。可以向算法传递任何类别的可调用对象。

> **可调用对象**
>
> - 函数
> - 函数指针
> - 重载了函数调用运算符的类 【14.8】
> - lambda表达式

一个`lambda`表达式表示一个可调用的代码单元，类似未命名的内联函数，但可以定义在函数内部。其形式如下：

```c++
[capture list] (parameter list) -> return type { function body }
```

其中，`capture list`（捕获列表）是一个由`lambda`所在函数定义的局部变量的列表（通常为空）。`return type`、`parameter list`和`function body`与普通函数一样，分别表示返回类型、参数列表和函数体。但与普通函数不同，`lambda`必须使用尾置返回类型，且不能有默认实参。

定义`lambda`时可以省略参数列表和返回类型，但必须包含捕获列表和函数体。省略参数列表等价于指定空参数列表。省略返回类型时，若函数体只是一个`return`语句，则返回类型由返回表达式的类型推断而来。否则返回类型为`void`。

```c++
auto f = [] { return 42; };
cout << f() << endl;    // prints 42
```

##### 向lambda 传递参数

与其他普通函数一样，调用lambda时放入的实参会用来初始化lambda的形参，实参与形参类型必须匹配。

但 lambda与普通函数不同，不能有默认参数。因此lambda的实参数量与形参数量必须相当。

##### 使用捕获列表

`lambda`可以使用其所在函数的局部变量，但必须先将其包含在捕获列表中。捕获列表只能用于局部非`static`变量，`lambda`可以直接使用局部`static`变量和其所在函数之外声明的名字。

```c++
// get an iterator to the first element whose size() is >= sz
auto wc = find_if(words.begin(), words.end(),
                    [sz](const string &a) { return a.size() >= sz; });
```

##### for_each 算法

`for_each`函数接受一个输入序列和一个可调用对象，它对输入序列中的每个元素调用此对象。

```c++
// print words of the given size or longer, each one followed by a space
for_each(wc, words.end(),
            [] (const string &s) { cout << s << " "; });
```

完整的代码

```c++
void biggies(vector<string> &words,vector<string>::size_type sz)
{
 elimDups(words); // put words in alphabetical order and remove
duplicates
 // sort words by size, but maintain alphabetical order for words of the same size
 stable_sort(words.begin(), words.end(), [](const string &a, const string &b) { return a.size() < b.size();});
 // get an iterator to the first element whose size() is >= sz
 auto wc = find_if(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; });
 // compute the number of elements with size >= sz
 auto count = words.end() - wc; cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;
 // print words of the given size or longer, each one followed by a space
 for_each(wc, words.end(), [](const string &s){cout << s << " ";}); cout << endl;
}
```



#### 10.3.3 Lambda Captures and Returns

##### 值捕获

被`lambda`捕获的变量的值是在**`lambda`创建时拷贝，而不是调用时拷贝**。在`lambda`创建后修改局部变量不会影响`lambda`内对应的值。

```c++
size_t v1 = 42; // local variable
// copies v1 into the callable object named f
auto f = [v1] { return v1; };
v1 = 0;
auto j = f();   // j is 42; f stored a copy of v1 when we created it
```

##### 引用捕获

`lambda`可以以引用方式捕获变量，但必须保证`lambda`执行时变量存在。

```c++
size_t v1 = 42; // local variable
// the object f2 contains a reference to v1
auto f2 = [&v1] { return v1; };
v1 = 0;
auto j = f2();  // j is 0; f2 refers to v1; it doesn't store it
```

> 这里需要强调一点，就是需要尽量让lambda的变量捕获简单化，最好避免捕获指针或引用，因为把握不好它们的生存周期。

##### 隐式捕获

可以让编译器根据`lambda`代码隐式捕获函数变量，方法是在捕获列表中写一个`&`或`=`符号。`&`为引用捕获，`=`为值捕获。

可以混合使用显式捕获和隐式捕获。混合使用时，捕获列表中的第一个元素必须是`&`或`=`符号，用于指定默认捕获方式。显式捕获的变量必须使用与隐式捕获不同的方式。

```c++
// os implicitly captured by reference; c explicitly captured by value
for_each(words.begin(), words.end(),
            [&, c] (const string &s) { os << s << c; });
// os explicitly captured by reference; c implicitly captured by value
for_each(words.begin(), words.end(),
            [=, &os] (const string &s) { os << s << c; });
```

`lambda`捕获列表形式：

![10-2](E:/00Learning/C++/Start learing C++/01-Notes/02-CPP_Primer_5th/CPP_Primer_5th.assets/10-2.png)

##### 可变lambda

默认情况下，对于值方式捕获的变量，`lambda`不能修改其值。如果希望修改，就必须在参数列表后添加关键字`mutable`。

```c++
#include <iostream>
using namespace std;
int main() {
    size_t v1 = 42; // local variable
// f can change the value of the variables it captures
    auto f = [v1] () mutable { return ++v1; };
    cout<<v1<<endl;
    v1 = 0;
    auto j = f();   // j is 43
    cout<<v1<<endl;
    cout<<j<<endl;
    return 0;
}
/*
42
0
43
*/
```

对于引用方式捕获的变量，`lambda`是否可以修改依赖于此引用指向的是否是`const`类型。

```c++
#include <iostream>
using namespace std;
int main() {
    size_t v1 = 42; // local variable
// f can change the value of the variables it captures
    auto f = [&v1] () mutable { return ++v1; };
    cout<<v1<<endl;
    v1 = 0;
    auto j = f();   // j is 43
    cout<<v1<<endl;
    cout<<j<<endl;
    return 0;
}
/*
42
1
1
*/
```

##### 指定lambda返回类型

默认情况下，如果一个lambda体包含return以外的任何语句，则编译器假定此lambda返回void。也就是说不能返回值。

`transform`函数接受三个迭代器参数和一个可调用对象。前两个迭代器参数指定输入序列，第三个迭代器参数表示目的位置。它对输入序列中的每个元素调用可调用对象，并将结果写入目的位置。

```c++
transform(vi.begin(), vi.end(), vi.begin(), 
            [](int i) { return i < 0 ? -i : i; });
```

这类使用运算符，只有一个return语句，但是如果是用了if来表示同样的意思就会出问题。

``` c++
transform(vi.begin(), vi.end(), vi.begin(),
 			[](int i) { if (i < 0) return -i; else return i;});
```

编译器推断这里返回void，但是你给了int值。

所以为`lambda`定义返回类型时，必须使用尾置返回类型。

```c++
transform(vi.begin(), vi.end(), vi.begin(), 
          [](int i) -> int 
          { if (i < 0) return -i; else return i; });
```



#### 10.3.4 Binding Arguments 参数绑定

如果lambda的捕获列表为空，通常可以用函数表示。但对于捕获局部变量的函数，就不容易用函数来替换了。

```c++
auto  wc = find_if(words.begin(),words.end(),
                  [sz](const string &a)
                   {return a.size() >= sz;}
                  );
```

这里的lambda表达式很容易写成函数

```c++
bool check_size(const string &s, string::size_type sz)
{
 return s.size() >= sz;
}
```

但是我们不能用这个函数作为find_if的一个参数。因为find_if接受一个一元谓词，因此传递给find_if的可调用对象必须接受一元参数。之前的lambda使用捕获列表来保存sz。

> 这里我废了一番功夫来理解，用自己的话理一下。
>
> find_if是一个标准库算法， 在不对其进行重载的情况下，那么我们只能去适应它。
>
> 而它要求的是一个一元谓词，那么这样我们就无法把需要的参数来传递给它。
>
> sz是一个形参，我们就需要在调用时传参过去。
>
> 这就需要函数绑定了。

##### 标准库bind函数

`bind`函数定义在头文件`functional`中，相当于一个函数适配器，它接受一个可调用对象，生成一个新的可调用对象来适配原对象的参数列表。一般形式如下：

```c++
auto newCallable = bind(callable, arg_list);
```

其中，`newCallable`本身是一个可调用对象，`arg_list`是一个以逗号分隔的参数列表，对应给定的`callable`的参数。之后调用`newCallable`时，`newCallable`会再调用`callable`，并传递给它`arg_list`中的参数。`arg_list`中可能包含形如`_n`的名字，其中`n`是一个整数。这些参数是占位符，表示`newCallable`的参数，它们占据了传递给`newCallable`的参数的位置。数值`n`表示生成的可调用对象中参数的位置：`_1`为`newCallable`的第一个参数，`_2`为`newCallable`的第二个参数，依次类推。



##### 使用placeholders名字

_n都定义在命名空间`placeholders`中，它又定义在命名空间`std`中，因此使用时应该进行双重限定。

```c++
using std::placeholders::_1;
```

这样做每个占位符都要声明一下，比较麻烦也容易出错。

可以使用另一种形式的using语句，【18.2.2】会讲。

```c++
using namespace namespace_name;
```

这表示希望所有来自namespace_namespace 的名字都可以在我们的程序中直接使用。

```c++
using namespace std::placeholders;
bool check_size(const string &s, string::size_type sz);

// check6 is a callable object that takes one argument of type string
// and calls check_size on its given string and the value 6
auto check6 = bind(check_size, _1, 6);
string s = "hello";
bool b1 = check6(s);    // check6(s) calls check_size(s, 6)
```

##### 用bind重排参数顺序

`bind`函数可以调整给定可调用对象中的参数顺序。

```c++
// sort on word length, shortest to longest
sort(words.begin(), words.end(), isShorter);
// sort on word length, longest to shortest
sort(words.begin(), words.end(), bind(isShorter, _2, _1));
```

##### 绑定引用参数

默认情况下，`bind`函数的非占位符参数被拷贝到`bind`返回的可调用对象中。但有些类型不支持拷贝操作。

如果希望传递给`bind`一个对象而又不拷贝它，则必须使用标准库的`ref`函数。`ref`函数返回一个对象，包含给定的引用，此对象是可以拷贝的。`cref`函数生成保存`const`引用的类。

```c++
ostream &print(ostream &os, const string &s, char c);
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
```

函数ref返回一个对象，包含给定的引用，此对象是可以拷贝的。标准库中还有cref函数，生成一个保存const引用的类。与bind一样，这俩也在头文件functional中。

> 使用std::ref可以在模板传参的时候传入引用，否则无法传递
> &是类型说明符， std::ref 是一个函数，返回 std::reference_wrapper(类似于指针）
> 用std::ref 是考虑到c++11中的函数式编程，如 std::bind.
>
> C++11的设计者认为bind默认应该采用拷贝，如果使用者有需求，加上std::ref()即可。同理std::thread也是这样。
>
> 那么如果std::ref()返回的不是对象的引用，返回的是什么？查一下手册可以发现：函数模板 ref 与 cref 是生成 **std::reference_wrapper 类型对象**的帮助函数，它们用模板实参推导确定结果的模板实参。所以std::ref()返回的实际上是一个reference_wrapper而不是T&，可以从一个指向不能拷贝的类型的对象的引用生成一个可拷贝的对象。 std::reference_wrapper 的实例是对象（它们可被复制或存储于容器），但它们能隐式转换成 T& ，故能以之为以引用接收底层类型的函数的参数。
>
> 考虑了函数式编程(如std::bind)在使用时，是对参数直接拷贝，而不是引用。具体可以参照这一句话：std::reference_wrapper 用于按引用传递对象给 std::bind 或 std::thread 的构造函数
>
> 结论
> std::ref只是尝试模拟引用传递，并不能真正变成引用，在非模板情况下，std::ref根本没法实现引用传递，只有模板自动推导类型时，ref能用包装类型reference_wrapper来代替原本会被识别的值类型，而reference_wrapper能隐式转换为被引用的值的引用类型，但是并不能被用作&类型。
>
> 而回到刚开始的那个多线程代码，thread的方法传递引用的时候，我们希望使用的是参数的引用，而不是浅拷贝，所以必须用ref来进行引用传递。
> ————————————————
> 版权声明：本文为CSDN博主「另寻沧海」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
> 原文链接：https://blog.csdn.net/weixin_42244181/article/details/123426590

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

| 中文 | 英文 | 含义 |
| ---- | ---- | ---- |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |

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

| 中文 | 英文 | 含义 |
| ---- | ---- | ---- |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |



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

| 中文 | 英文 | 含义 |
| ---- | ---- | ---- |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |
|      |      |      |

