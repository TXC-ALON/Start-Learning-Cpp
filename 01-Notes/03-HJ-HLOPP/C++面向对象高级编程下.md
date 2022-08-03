# C++ 程序设计 - 兼谈对象模型

## 导读

 本课程包括模板等等，不仅仅是面向对象。所以叫这个名字、

**勿在浮沙筑高台**

### 课程目标

- 在先前基础课程培养的正规大气的编程素养上，继续探讨更多技术。  

- 泛型编程`Generic Programming` 和面向对象编程 `Object-Oriented Programming` 虽然分属不同思维，但它们正是C++的技术主线，所以本课程也讨论模板。
- 深入探索面向对象值继承关系`inheritance`所形成的对象模型`Object model`，包括隐藏于底层的`this`指针，`vptr`虚指针，`vtbl`虚表，`virtual mechanism` 虚机制，以及虚函数 `virtual functions` 造成的多态` polymorphism`效果。

### 编译器 

- 编译 `compile`
- 链接 `link`



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

