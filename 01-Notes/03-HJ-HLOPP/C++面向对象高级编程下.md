# C++ 程序设计 - 兼谈对象模型

## 导读

 本课程包括模板等等，不仅仅是面向对象。所以叫这个名字

**勿在浮沙筑高台**

### 课程目标

- 在先前基础课程培养的正规大气的编程素养上，继续探讨更多技术。  

- 泛型编程`Generic Programming` 和面向对象编程 `Object-Oriented Programming` 虽然分属不同思维，但它们正是C++的技术主线，所以本课程也讨论模板。
- 深入探索面向对象值继承关系`inheritance`所形成的对象模型`Object model`，包括隐藏于底层的`this`指针，`vptr`虚指针，`vtbl`虚表，`virtual mechanism` 虚机制，以及虚函数 `virtual functions` 造成的多态` polymorphism`效果。

### 编译器 

- 编译 `compile`
- 链接 `link`



发现一个很好的博客   https://www.cnblogs.com/leokale-zz/p/11090627.html





## 转换函数 Conversion Function

#### 以分数举例

```c++
class Fraction{
public:
    Fraction (int num,int den = 1)
    : m_numerator(num),m_denominator(den){}
    operator double() const {
        //return (double)(m_numerator / m_denominator);
        return (double)m_numerator / (double)m_denominator;
    }
private:
    int m_numerator;    //分子
    int m_denominator;  //分母
};

Fraction f(3,5);
double d = 4 + f;
```

`operator 类型 const`

-  转换不可以有参数。

- 前面也不必有类型名（后面已经写了），

- 同时转换不可能改变类里的值，所以通常使用`const`。

`double d = 4 + f;`

首先看有没有配套的重载，结果没有写。

然后看有没有合适的转换，使f是double。

**注：分子分母都需要进行强制转换为double，并不是简单括起来就可以了，编辑环境不管是clion，vstudio，还是linux环境，不进行强制转换，结果都是整数而非分数。**

#### non-explicit-one-argument ctor

```c++
Fraction (int num,int den = 1)
            : m_numerator(num),m_denominator(den){}
```

one-argument: 创建一个Fraction只要一个实参就够了，另外一个的有默认参数。这在数学上也是符合逻辑的。(two parameters)

non-explicit: 没有加explicit

```c++
class Fraction {
public:
    //该构造函数的den参数有默认值，这就形成了单参数构造函数
    Fraction(int num, int den = 1) :m_num(num), m_den(den) {}
    
    Fraction operator +(const Fraction& f) {
        //完成Fraction之间的加法,并返回
        return Fraction(this->m_num*f.m_den + this->m_den*f.m_num, this->m_den*f.m_den);
    }
    int get_num() const {
        return m_num;
    }
    int get_den() const {
        return m_den;
    }
private:
    int m_num;
    int m_den;
};

inline ostream& operator<<(ostream& os,const Fraction& f) {
    os << f.get_num();
    os << "/";
    os << f.get_den();
    return os;
}

Fraction f(10, 3);
//当Fraction对象加一个int时，编译器会自动将4转换为4/1的Fraction对象
Fraction dvi = f + 4 ;
cout << dvi << endl; //输出3/22
```

如果转换和cxoa-ctor并存，会有问题。

```c++
class Fraction {
public:
    //该构造函数的den参数有默认值，这就形成了单参数构造函数
    Fraction(int num, int den = 1) :m_num(num), m_den(den) {}

    //Fraction转double的转换函数
    operator double() const {
        return (double)m_num / (double)m_den;
    }
    
    Fraction operator +(const Fraction& f) {
        //完成Fraction之间的加法,并返回
        return Fraction(this->m_num*f.m_den + this->m_den*f.m_num, this->m_den*f.m_den);
    }
    int get_num() const {
        return m_num;
    }
    int get_den() const {
        return m_den;
    }
private:
    int m_num;
    int m_den;
};

inline ostream& operator<<(ostream& os,const Fraction& f) {
    os << f.get_num();
    os << "/";
    os << f.get_den();
    return os;
}
```

此时，Fraction类的定义中，同时存在单参数构造函数和转换函数。当调用以下代码时（报错）：

```c++
Fraction f(10, 3);
//当Fraction对象加一个int时，编译器会自动将4转换为4/1的Fraction对象
Fraction dvi = f + 4 ;
cout << dvi << endl;
```

Fraction dvi = f + 4;会报错。因为编译器认为，可以把f转换为double，也可以把4转换为Fraction。当把4转换为Fraction时，这条路能走通。但是把f转换为double时，做完加法后，无法将得到的double类型的dvi转换为Fraction，所以报错。

同样的，这样调用也会报错，与上面的过程相反。

```c++
Fraction f(10, 3);
//当Fraction对象加一个int时，编译器会自动将4转换为4/1的Fraction对象
double dvi = f + 4 ;
cout << dvi << endl;
```

**可选择的太多，编译器会不知道怎么办，换句话说编译器不知道判断好坏，他只知道对错。**

这里还可以总结一下， 就是之前的转换函数，是将Fraction转为double。而加号重载，是将double转为Fraction类。



### explict-one-argument ctor

explicit关键字意为“明确的”。很大几率用在构造函数前面，指明该构造函数只做构造函数使用，让编译器不要自动去调用它。

```c++
class Fraction {
public:
    //该构造函数的den参数有默认值，这就形成了单参数构造函数
    explicit Fraction(int num, int den = 1) :m_num(num), m_den(den) {}

    //Fraction转double的转换函数
    operator double() const {
        return (double)m_num / (double)m_den;
    }
    
    Fraction operator +(const Fraction& f) {
        //完成Fraction之间的加法,并返回
        return Fraction(this->m_num*f.m_den + this->m_den*f.m_num, this->m_den*f.m_den);
    }
    int get_num() const {
        return m_num;
    }
    int get_den() const {
        return m_den;
    }
private:
    int m_num;
    int m_den;
};

inline ostream& operator<<(ostream& os,const Fraction& f) {
    os << f.get_num();
    os << "/";
    os << f.get_den();
    return os;
}
```

在构造函数前使用了explicit关键字，也就相当于把前面例子里编译器面对的两条路减少为一条，这就没有冲突了。程序就能正确运行，但只能将f转换为double进行运算。

```c++
Fraction f(10, 3);
//当Fraction对象加一个int时，编译器会自动将4转换为4/1的Fraction对象
double dvi = f + 4 ;
cout << dvi << endl;  //输出7.3333
```

**总结：**explicit很少使用，90%的几率都使用在构造函数之前，还有模板里很小一部分会用到。用作控制编译器的自动行为，减少从中带来的莫名错误。



## Pointer-like class

Pointer-like class 即做出来的对象，像一个指针。例如智能指针就是其中一种。在这种类中，一定包含一个普通的指针。基本都会包括`.` `->`的重载。

### 智能指针 

```c++
template<class T>
class shared_ptr {
public:
    T& operator*() const {
        return *px;
    }
    T* operator->() const {
        return px;
    }
    //构造函数
    shared_ptr(T* p):px(p) {}
private:
    T* px;
};
//测试类，将其对象指针包装成shared_ptr智能指针
class Test {
public:
    void mytest() {
        printf("testing...\n");
    }
};
```

`注意T& operator*() const;和T* operator->() const;两个操作符重载函数，其中“*”的重载函数很好理解，就是取指针指向地址的数据。但是“->”符号的重载不太好理解，这是因为在C++中，->这个符号比较特殊，这个符号除了第一次作用在shared_ptr对象上，返回原始指针px，还会继续作用在px上，用来调用函数m ytest。但好在重载这个符号，基本就是这种固定写法。`

```c++
Test a;
//Foo f(*sp); 从sp中取出数据进入Foo的构造函数。  
shared_ptr<Test> ptr(&a);
ptr->mytest();
```

### 迭代器

迭代器类型的Pointer-like和智能指针的Pointer-like有一定的区别。

作为迭代器，他将一个对象（结构体或类产生的对象）的指针包装为一个迭代器（类指针对象），例如链表的某个节点指针，这样，在他的内部重载多个操作符，比如“*”、“->”、“++”、“--”、“==”、“!=”等，分别对应链表节点之间的取值、调用、右移、左移、判断等于、判断不等于。
链表的基本结构图：

![img](C++面向对象高级编程下.assets/1244144-20190626190908080-1756617049.png)

 迭代器中“*”和“->”的重载：

![img](C++面向对象高级编程下.assets/1244144-20190626191004817-1295883612.png)

图中所示，迭代器中的“*”，返回的是某个node中的data，而不是这个node（这些实现都是根据用户需求来实现）。

`迭代器中的“->”返回的是data的指针，因为operator*()就是调用“*”的重载函数，返回data数据，前面再使用“&”来取地址，则就是data的指针。从而可以达到使用“->”来完成data->func_name()的目的。`

![image-20220802174348439](C++面向对象高级编程下.assets/image-20220802174348439.png)

举一反三，其他的符号重载也是根据用户需求来做相应的操作。

所以说操作符重载非常重要。



看你马的台湾局势，看你马的国际政治，管你鸟事，好好学技术才是真的。

嘴炮屁用没有。



## function-like classes

像函数一样的类，意思就是将一个类定义为可以接受`()`这个操作符的东西。

能接受`()`的对象 ，就是一个函数对象或仿函数。

```c++
template<class T>
class Identity {
public:
    //重载()操作符，使该类衍生的对象可以像函数一样调用
    T& operator()(T& x) {
        return x;
    }
};

class Test {
public:
    void mytest() {
        printf("testing...\n");
    }
}; 
```



```c++
int a1 = 5;
Identity<int> iden_i;
int a2 = iden_i(a1);
cout << a2 << endl;

Test t1;
Identity<Test> iden_t;
Test t2 = iden_t(t1);
t2.mytest();
```
> 标准库的仿函数多会继承一些奇特的类型
> ```c++
> template <class Arg, class Result>  //这两个类的特点：大小为0，没有函数
> struct unary_function  {//一个操作数
>     typedef Arg argumrnt_type;
>     typedef Result result_type;
> };
> 
> template <class Arg1,class Arg2,class Result>
> struct binary_function  {//两个操作数
>     typedef Arg1 first_argument_type;
>     typedef Arg2 second_argument_type;
>     typedef Result result_type;
> };
> 
> template <class T>
> struct identity:public unary_function<T,T>  {  //继承了奇怪的类
>     const T&
>     operator()  (const T& x)  const  {return x;  }  //重载了()
> };
> 
> template <class Pair>
> struct select1st:public unary_function<Pair, typename Pair::first_type>  {
>     const typename Pair::first_type&
>     operator() (const Pair& x)  const
>     {  return x.first;  }
> };
> template <class Pair>
> struct select2nd:public unary_function<Pair, typename Pair::second_type> {
>     const typename Pair::second_type &
>     operator()(const Pair &x) const { return x.second; }
> };
> template <class T1,class T2>
> struct pair  {
>     T1 first;
>     T2 second;
>     pair():first(T1()),second(T2())  { }
>     pair(const T1& a,const T2& b)
>             :  first(a), second(b)  { }
> };
> ```

## namespace 经验谈

要养成使用命名空间的习惯。

## class template 类模板

将可以提供外界控制的类型名抽出来，然后制作模板

```c++
template<typename T>
class complex
{
public:
    complex(T r = 0,T i = 0)
    : re(r),im(i)
    {}
    complex& operator += (const complex&);
    T real () const {return re;}
    T imag () const {return im;}
private:
    T re,im;
    friend complex& __doapl(complex*,const complex&);
};

{
    complex<double>c1(1.4,3.2);
    complex<int>c2(2,4);
}
```

## Function template 函数模板 

同理

```c++
template<class T>
inline
const T& min(const T& a , const T& b)
{
    return b < a ? b : a;
}
class stone
{
public:
    stone(int w, int h,int we)
        : _W(w),_H(h),_WE(we)
        {}
    bool operator< (const stone& rhs) const
    {
        return _WE < rhs._WE;
    }
private:
    int _W;
    int _H;
    int _WE;
}


//编译器会对Function template进行实参推导argument deduction。 
stone r1(2,4),r2(3,4),r3;
r3 = min(r1,r2)
```

## Member template 成员模板

```c++
template<class T1,class T2>
class Pair {
public:
    T1 first;
    T2 second;
    //普通构造
    Pair() :first(T1()), second(T2()) {}
    Pair(const T1& a,const T2& b):first(a),second(b){}
    //成员模板
    template<class U1,class U2>
    Pair(const Pair<U1, U2>& p) : first(p.first),second(p.second) {}

};
//Base1理解为鱼类
class Base1 {};
//derived1理解为鲫鱼
class derived1 :public Base1 {};
//Base2理解为鸟类
class Base2 {};
//derived2理解为麻雀
class derived2 :public Base2 {};
```

Q: 将一个由鲫鱼和麻雀构成的pair，放进一个由鸟类和鱼类构成的pair中，可行吗？

A: 可以，反之不行。为满足这种需求，设计pair的人，需要特殊设计，

```c++
template<class U1,class U2>
    Pair(const Pair<U1, U2>& p) : first(p.first),second(p.second) {}
```

将初值的头尾放入当做本身的头尾。可以通过。

**标准库的构造函数 大量使用这种手法，为了使构造函数更有弹性**

### 成员模板与智能指针

将成员模板引申到前面所讲的智能指针，即可实现父类指针指向子类对象的效果。

因为普通的指针都可以指向自己子类的对象`up-cast`，那么作为这个指针的封装（智能指针），那必须能够指向子类对象。所以，可以模板T1就是父类类型，U1就是子类类型。实现如下：

```c++
template<class T>
class shared_ptr {
public:
    T& operator*() const {
        return *px;
    }
    T* operator->() const {
        return px;
    }
    shared_ptr(T* p):px(p) {}
    //成员模板
    template<class U>
    explicit shared_ptr(U* p) : px(p) {}
private:
    T* px;
};
//测试类，将其对象指针包装成shared_ptr智能指针
class Test {
public:
    virtual void mytest() {
        printf("testing...\n");
    }
};
class Test2 :public Test {
    void mytest() {
        printf("testing2...\n");
    }
}; 

//
Test2 t2;
shared_ptr<Test> ptr(&t2); //实际上里面的成员属性px是Test类型的，但是保存的却是Test2类型数据
ptr->mytest();  //输出testing2..
```

## specialization 模板特化

模板特化和泛化是反义的。我们使用的普通模板化指模板泛化，

而特化就是指在泛化的基础上，有一些特殊的类型做特殊处理，例如： 

```c++
//这个是Hash类的泛化定义
using namespace std;
template<class T>
class Hash {
public:
    size_t operator()(T in)const {
        cout << "Template:"<<in << endl;
        return in;
    }
};
//这个是Hash类对于int类型的特化定义
template<>//这个东西因为被绑定，所以不用写class了
class Hash<int> {
public:
    void operator()(int in)const {// 每个特化都对()做重载
        cout << "Int:"<<in<< endl;
    }
};
//这个是Hash类对于Double类型的特化定义
template<>
class Hash<double> {
public:
    void operator()(double in)const {
        cout << "Double:" << in << endl;
    }
};
```

调用：

```c++
#include <iostream>
#include "head.h"
using namespace std;
int main() {
    Hash<int> hash_int;
    hash_int(50);
//double类型调用的是double类型的特化
    Hash<double> hash_db;
    hash_db(88.8);
//float类型调用的是泛化情况下的构造方法
    Hash<float> hash_fl;
    hash_fl(77.7);

    cout<< Hash<long>()(1000)<<endl; // Hash<long>()这是一个临时对象 () 启动operator()
    return 0;
}


Int:50
Double:88.8
Template:77.7
Template:1000
1000
```



## partial special 模板偏特化

- 个数上偏

```c++
template<typename T,typename Alloc=...>//vector 可以指定 类型以及分配器
class vector{
  ...  
};
//绑定
template<typename Alloc=...>
class vector<bool,Alloc>{
    ...
}
```

- 范围上偏

从任意类型缩小到指针

```c++
template<typename T>
class C
{
    ...
};

template<typename T>
class C<T*> // 如果使用者使用的是指针，就使用这一套代码
{
    ...
};
//上下两个T完全没有关系，可以换名字
template<typename U>
class C<U*>
{
    ...
};

//
C<string> obj1;
C<string*> obj2;
```









> 偏特化是在全特化的基础上发展来的，全特化就是上面所述的例子，只有一个泛化类型T。而偏特化就是指有多个泛化类型，例如：
>
> ```
> //多类型模板泛化
> template<class T1,class T2,class T3>
> class Hash2 {
> public:
>     void operator()(T1 in1,T2 in2,T3 in3)const {
>         cout <<"泛化"<< endl;
>     }
> };
> //前两个固定为int和double，偏泛化
> template<class T3>
> class Hash2<int,double, T3> {
> public:
>     void operator()(int in1,double in2,T3 in3)const {
>         cout << "偏特化"<<endl;
>     }
> };
> ```
>
> 调用：
>
> ```
> //泛化
> Hash2<float, double, float> hash_fdf;
> hash_fdf(5.0, 6.6, 7.7); //输出 泛化
> //偏特化
> Hash2<int,double,float> hash_idf;
> hash_idf(5,6.6,7.7); //输出 偏泛化
> ```
>
> **范围上的偏**
>
> 本来是全泛化，假设为template<class T>，我们想单独拿出任意类型的指针来偏特化。
>
> ```
> template<class T>
> class  A {
> public:
>     void operator()(T t)const {
>         cout << "泛化" << endl;
>     }
> };
> 
> template<class T>
> class A<T*> {
> public:
>     void operator()(T* tp)const {
>         cout << "范围偏特化" << endl;
>     }
> };
> ```
>
> 调用：
>
> ```
> int num = 5;
> int *p_num = &num;
> A<int> a1;
> A<int*> a2;
> a1(num);    //输出泛化
> a2(p_num);    //输出范围偏特化
> ```



## 模板模板参数 template template parameter  

模板参数本身也是模板

```c++
#include<list>
template<typename T,
        template<typename T> //这里会报错，侯捷老师这边这样讲没问题，是实际操作时候不能同名
        /*
         *The rule clang is using to block it is: C++ 2011 [temp.local] Paragraph 6: A template-parameter shall not be redeclared within its scope (including nested scopes). A template- parameter shall not have the same name as the template name. This can be found in the clang source code within the Sema::DiagnoseTemplateParameterShadow method. – 
Bill Lynch
 Jan 2, 2014 at 2:04 
        */
            class Container
          >
class XCLS{
private:
    Container<T>c;
public:

};

template<typename T>
using Lst = std::list<T,std::allocator<T>>;

//
XCls<string,list>mylist1;//error list 本身是个模板，里面类型和分配器都未定。不能直接这样使用
XCLs<string,Lst> mylist2;//ok
```

PS：只有在template<>的尖括号里面，`class`和`typename`是共通的。这是因为最初没有`typename`关键词，借用的`class` 。属于历史问题。

### 另一种情况 - 传smartPtr

smartPtr里面shared_ptr和auto_ptr接受一个参数

![image-20220804105513770](C++面向对象高级编程下.assets/image-20220804105513770.png)

### 这不是template template parameter

```c++
template<class T,class Sequence = deque<T>>
class stack{
	friend bool operator == <> (const stack&,cosnt stack&);
	friend bool operator < <> (const stack&,cosnt stack&);
protected:
	Sequence c;
}
//
stack<int>s1; // 由于第二个有默认值，只指定第一个模板参数
stack<int,list<int>> s2;//这个第二个参数已经写死，不再是模板参数。
```



>模板的参数就是指template<typename T>中的T，他可以是任意类型。
>
>但是当T也是一个模板时，就叫模板的模板参数。
>
>```
>template<class T>
>class Test{};
>
>template<typename T,template<typename CT> class C>
>class XC {
>
>private:
>    //C可以是List,该list需要一个模板参数CT,可以是任何类型，这里使用T的类型
>    C<T> c;
>};
>```
>
>调用：
>
>```
>//实际上xc中的c的类型为Test<int>
>XC<int, Test> xc;
>```
>
>当然，像vector等类型拥有多于1个的模板参数，所以以上代码中的C不能是vector。如果要实现vector作为XC的第二个模板，那么需要指明vector的两个模板参数：
>
>```
>template<class T>
>class Test{};
>
>template< class T1,class T2, template<class CT1, class CT2>  class C>
>class XC {
>
>private:
>    //C可以是List,该list需要一个模板参数CT,可以是任何类型，这里使用T的类型
>    C<T1,T2> c;
>};
>```
>
>调用：
>
>```
>//实际上xc中的c的类型为vector<int,std::allocator<int>>
>XC<int, std::allocator<int>,vector> xc;
>```
>
> **模板的模板参数，还需要和另一种形式区分开：**
>
>```
>template<class T, class Sequence = deque<T>> //这种不是模板的模板参数
>```
>
>Sequence的默认值deque<T>实际上已经指明了Sequence的类型时deque，只是因为deque还有一个模板参数而已。
>
>它和上面讲的不一样，上面讲的 template<class CT1, class CT2> class C，相当于Sequence<T>，Sequence和T都是待指定的模板参数。所以还是有本质区别的。



## 关于C++标准库

![image-20220804110313076](C++面向对象高级编程下.assets/image-20220804110313076.png)

![image-20220804110847806](C++面向对象高级编程下.assets/image-20220804110847806.png)



## 三个主题

### Variadic templates(since C++11) 模板参数可变化

variadic 是生造出来的一个单词。

新的语法允许你写任意个数的模板参数。

递归拆包。 

 ```c++
 //用于当args...里没有参数的时候调用，避免报错
 void leo_print() {
     //Do Nothing
 }
 
 //数量不定模板参数
 template<class T, class ... Types>// 一包，用...表示
 void leo_print(const T& firstArg, const Types& ... args)
 {
     cout << firstArg << endl;
     //递归调用leo_print，每次打印下一个参数
     //自动将args...里的多个参数分为1+n个
     leo_print(args...);
 }
 //
 leo_print(64, 5.5, "gogogo", 90, bitset<16>(377);
 ```

注：这里递归调用，包里面的参数都已经有了<<重载。

 可以使用`sizeof...(args)`来抓住这一包几个。

标准库用这个语法大量返修过了。



### auto（since C++11)

auto关键字的作用在于，让编译器自动帮你推导需要的类型。这是一个语法糖，仅仅是让写代码更加方便。

例如：

```
list<int> c;
c.push_back(11);
c.push_back(22);
c.push_back(33);
    
//普通写法，自定指定类型
list<int>::iterator ite;
ite = find(c.begin(), c.end(), 33);
//auto写法，编译器从右边的find返回值推导其变量类型
auto ite = find(c.begin(), c.end(), string("leo"));
//错误写法
auto ite; //光从这句话，编译器没法推导他的类型
ite = find(c.begin(), c.end(), string("hello3"));
```

###  基于range的循环

```
list<int> c;
c.push_back(11);
c.push_back(22);
c.push_back(33);
//遍历一个容器里的元素    
for (int i : c) {
    cout << i << endl;
}
//除了遍历传统的容器，还能遍历{...}形式的数据
//{}中的数据要和i的类型符合
for (int i : {1,2,3,4,5,6,7,8,9,10}){
    cout << i << endl;
}    
//使用auto自己推导遍历元素的类型
for (auto i : c)
{        
    cout << i <<endl;
}    
```

上面过程，遍历到的数据都是拷贝给“i”的，不会影响容器中的数据。

可以通过传引用改变容器中的数据。

```
//pass by reference，直接作用于容器元素本身
for (auto& i : c) {
    i *= 3;
}
```





## Reference 再探引用

##  ![img](C++面向对象高级编程下.assets/1244144-20190627021704182-655246197.png)

```c++
int x = 0;
int *p = &x;
int &r = x;
int x2 = 5;
r = x2;
int &r2 = r; 
```



1.x是一个int类型的变量，大小为4bytes。

2.p是一个指针变量，保存的是x的地址，在32bit计算机中，指针的大小为4bytes。

3.r是x的引用，可以认为r就是x，x就是r，

> 引用就是一个编译器增加了严格限制的const指针，单纯用c++代码看引用的地址是和变量相同，但是用汇编代码看，是会把变量地址放入引用中，因此从内存角度来说，引用是和指针一样的。
>
> https://zhuanlan.zhihu.com/p/89175296  

4.当r=x2时，相当于也是x=x2。

5.r2是r的引用，也即是x的引用。现在r、r2、x都是一体。

6.使用sizeof()来看引用r和变量x的大小，返回的数值是一样的。

```c++
	int a = 4;
    int* o = &a;
    int& b = a;
    double m[5] = {1,2,5,6,4};
    double* p = m;
    double(&t)[5] = m;
    cout << sizeof(a) << endl;
    cout << sizeof(o) << endl;
    cout << sizeof(b) << endl;
    cout << "----------" << endl;
    cout << sizeof(m) << endl;
    cout << sizeof(p) << endl;
    cout << sizeof(*p) << endl;
    cout << sizeof(t) << endl;
    cout << t[3] << endl;
/* 
32位系统
4
4
4
----------
40
4
8
40
6
*/
```



7.对引用r和变量x取地址，返回的地址也都是一样的。

### 对引用的几个认识

从实现的角度来看，引用的底层都是通过指针来实现的。但是从逻辑的角度来看，引用又不是指针，我们看到引用，就要像看到变量本身一样，例如一个int类型变量，其引用也应该看成整数。

**引用就是一个变量的别名，引用就是那个变量。**引用一旦创建，就不能再代表其他变量了。如果此时再将某个变量赋值给这个引用，相当于赋值给引用代表的变量。参照前面第4点。

**所以，对引用最好的理解方式，就是认为引用就是变量，不用关心为什么，编译器给我们制造了一个假象，就像一个人有大名和小名一样。你对引用做的任何操作，就相当于对变量本身做操作。**

### 引用的常见用途

引用多用在参数传递和返回类型上，从写法上来说，传引用也更优美。

![image-20220805174123253](C++面向对象高级编程下.assets/image-20220805174123253.png)

### 引用不能重载

```
double imag(const double& im){}
double imag(const double im){}
```

上述两句代码不能并存，因为他们的签名（signature）是相同的，signature就是[ imag(const double im) ----- ]这一段，‘----’表示可能存在的const关键字等。（const是作为签名的一部分的）

为什么不能并存，因为这两个函数虽然传参数的方式不同，一个传引用，一个传值。但**对于调用**来说，是一样的imag(im)，这样对于编译器来说，它不知道该调用哪一个，所以不能并存（重载）。



