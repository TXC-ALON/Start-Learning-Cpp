# Effective C++ 精华版

## 第一章 让自己习惯C++ 

**[Accustoming Yourself to C++]**

### 条款01 视C++为一个语言联邦 

View C++ as a federation of languages

C++ 有四大部分，分别是C、面对对象的C++、模板C++、STL。

### 条款02 尽量以const，enum，inline 替换 #define 

Prefer consts,enums,and inlines to #defines

#define可能会带来诸多不便。

- 定义常量指针以及在类内定义常量–const
- enum hack（暂时不用考虑）
- 利用inline或者template inline来实现宏

### 条款03 尽可能使用const 

Use const whenever possible

关键字const多才多艺，你可以用它在classes外部修饰global或namespace作用域中的常量，或修饰文件、函数、或区块作用域中被声明为static的对象。也可以用它修饰classes内部的static和non-static成员变量。面对指针，你也可以指出指针自身、指针所指物，或者两者都（或都不）是const。

```c++
char greeting[] = ”Hello”;
char *p = greeting;//non-const pointer non-const data 
const char *p = greeting; //non-const pointer const data
char *const p = greeting;//const pointer non-const data
const char *const p = greeting;//const pointer const data.
```

在指针中const的位置说明

- 如果关键字const出现在星号左边，表示被指物是常量。

- 如果出现在星号右边，表示指针自身是常量。如果出现在星号两边，表示被指物和指针两者都是常量。

- 如果被指物是常量，const在类型的前后其实没有区别。



在 C++ 中，mutable 关键字可以用来修饰类的成员变量。使用 mutable 修饰的成员变量可以在常量成员函数中被修改。（常量成员函数是指在函数声明中使用 const 关键字修饰的成员函数，这类函数不会修改对象的状态。）

### 条款04 确定对象被使用前已先被初始化 

Make sure that objects are initialized before they're used

使用成员初值列(member initialization list)来替换赋值动作

为免除“跨编译单元之初始化次序”问题，请以local static对象替换non-local static对象。

## 第二章 构造/析构/赋值运算

 **[Constructors, Destructors, and Assignment Operators]**

### 条款05 了解C++默默编写并调用哪些函数

Know what functions C++ silently writes and calls

如果你自己没有声明，编译器就会为它声明（编译器版本的）一个copy构造函数，一个拷贝操作符，一个析构函数。如果你连构造函数，编译器也会为你声明一个default构造函数。所有这些函数都是public且inline的【条款30】

### 条款06 若不想使用编译器自动生成的函数，就该明确拒绝

Explicitly disallow the use of compiler-generated

通过明确声明一个成员函数，你阻止了编译器暗自创建其专属版本

而令这些函数为private，使得阻止别人调用这些函数。

### 条款07 为多态基类声明virtual析构函数

Declare destructors virtual in polymorphic

作为基类的类都应该有一个virtual析构函数。如果这个类不会被继承，那就不必这么做。

### 条款08 别让异常逃离析构函数

Prevent exceptions from leaving destructors

析构函数绝不应该吐出异常。

### 条款09 绝不在构造和析构过程中调用virtual函数

Never call virtual functions during construction or destruction

在基类的构造函数中，虚函数永远不会下降到派生类中。

确定你在创建和销毁对象的时候，你的构造函数和虚构函数不会去调用虚函数，并且它们调用的所有函数也需要遵守这个约定。

### 条款10 令operator = 返回一个 reference to *this

Have assignment operators return a reference to *this

为了满足赋值可以连续赋值，同时满足右结合律。

### 条款11 在operator = 中处理“自我赋值”

Handle assignment to self in operator=

两个对象只要来自同一个继承体系，他们甚至不需声明为相同类型就可能造成“别名”，因为一个基类的指针或引用可以指向一个子类对象。那么就需考虑这些对象是否为同一个。

确保当对象自我赋值时，operator= 有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址，精心周到的语句顺序、以及copy-and-swap

### 条款12 复制对象时勿忘其每一个成分 

Copy all parts of an object

当你编写一个copying函数，请确保：

- 复制所有local成员变量
- 调用所有base class内的适当copying 函数。

## 第三章 资源管理

**[Constructors, Destructors, and Assignment Operators]**

### 条款13 以对象管理资源

Use objects to manage resources

使用智能指针来管理资源

### 条款14 在资源管理类中小心copying行为

Think carefully about copying behavior in resource-managing classes

使用智能指针来管理资源

### 条款15 在资源管理类中提供对原始资源的访问

Provide access to raw resources in resource-managing classes

- API往往要求访问原始资源（raw resources），所以每一个RAII class 应该提供一个“取得其所管理之资源”的方法。
- 对原始资源的访问可能经由显式转换或隐式转换。一般而言显式转换比较安全，但隐式转换对客户比较方便。

### 条款16 成对使用new和delete时要采取相同形式

Use the same form in corresponding uses of new and delete

如果你在new表达式中使用[]，必须在相应的delete表达式中也使用[]；如果你在new表达式中不使用[]，一定不要在相应的delete表达式中也使用[]；

### 条款17 以独立语句将newd 的对象置入智能指针

Store newed objects in smart pointers in standalone statements

编译器对于跨越语句的各项操作没有重新排列的自由（只有在语句内它才有那个自由度）。

独立语句将newed对象存储于智能指针内。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏。

## 第四章 设计声明

**[Designs and Declarations]**

### 条款18 让接口容易被使用，不易被误用

Make interfaces easy to use correctly and hard to use incorrectly

### 条款19 设计class犹如设计type

Treat class design as type design

### 条款20 宁以pass-by-reference-to-const替换pass-by-value

Prefer pass-by-reference-to-const to pass-by-value

- 按值传递参数会有效率问题

- 按const引用传递会更高效

- 按const引用传递能避免切片问题

  当子类对象以传值方式传递并被视为base class对象时，base class的构造函数会被调用，而它的子类部分都被切割掉了

### 条款21 必须返回对象时，别妄想返回其reference

Don’t try to return a reference when you must return an object

任何时候看到一个reference声明式，你都一个立刻问自己，它的另一个名称是什么？

绝不要返回指向一个local stack对象的指针或引用，或返回指向一个heap-allocated对象的引用，或返回指向一个可能被多个需求需要的local static对象的指针或引用。

从函数中返回新对象的正确方法是返回对象。这是因为返回对象会通过值传递的方式将对象的副本返回给调用者，而不是返回对象的引用或指针。这种方式可以确保调用者获得一个新的、独立的对象，而不是与函数内部创建的对象共享相同的内存地址。

### 条款22 将成员变量声明为private

Declare data members private

- 切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者以充分的实现弹性。
- Protected并不比public更具有封装性。

### 条款23 宁以non-member、non-friend替换member函数

Prefer non-member non-friend functions to member functions

宁可拿同一命名空间下的non-member non-friend函数替换member函数，这一做可以增加封装性、包裹弹性和机能扩充性。

### 条款24 若所有参数皆需类型转换、请为此采用non-member函数

Declare non-member functions when type conversions should apply to all parameters

在导读里曾经提过，令class支持隐式类型转换通常是一个糟糕的主意，但是也得视情况而定。比如把整数隐式转换为有理数就很自然。

如果你需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member。

### 条款25 考虑写出一个不抛异常的swap函数

Consider support for a non-throwing swap

- 首先、如果swap的默认版本对你的class或class template提供可接受的效率，那么你不需要做什么。
- 其次，如果swap默认版本的效率不足（一般来说都是因为类或模板使用了pimpl手法），试着做以下事情：
  - 提供一个public swap成员函数，让它高效地置换你的类型的两个对象值。这个函数绝不应该抛出异常。
  - 在你的class或template所在的命名空间内提供一个non-member swap，并令它调用上述swap函数。
  - 如果你正编写一个class而非类模板，为你的类特化std::swap，并令它调用你的swap成员函数
- 最后，如果你调用swap，请确定包含一个using 声明式，以便让std::swap在你的函数内曝光可见，然后不加任何namespace修饰符，赤裸裸地调用swap。

## 第五章 实现

**[Implementations]**

- 太快定义变量可能导致效率上的拖延。
- 过度使用转型可能导致代码变慢且难以维护。
- 返回对象内部的句柄可能会破坏封装并可能引起虚吊。
- 未考虑异常带来的冲击可能导致资源泄漏和崩坏的数据结构。
- 过分的inline可能会引起代码膨胀。
- 过度耦合则可能导致让人不可接受的建构时间。

### 条款26 尽可能延后变量定义式的出现时间

Postpone variable definitions as long as possible

你不但要将变量的定义推迟到你必须使用的时候，你同样应该尝试将定义推迟到你获得变量的初始化值的时候。这么做，你就能避免不必要的构造和析构，也避免了不必要的默认构造函数。并且，通过在意义已经明确的上下文中对变量进行初始化，你也帮助指明了使用此变量的意图。

### 条款27 尽量少做转型动作

Minimize casting

- C风格的转型动作
  - (T)expression
- 函数风格的转型动作
  - T(expression)
- 新式转型（C++ style）
  - const_cast<T>(expression) 通常被用来将对象的常量性转除，他也是唯一有此能力的C++-style的转型操作符
  - dynamic_cast<T>(expression) 主要用来执行安全向下转型，也就是用来决定某个对象是否归属继承体系中的某个类型。它是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作。
  - reinterpret_cast<T>(expression) 意图执行低级转型，实际动作可能取决于编译器，这就意味着它不可移植。【条款50】
  - static_cast<T>(expression) 用来强迫隐式转换（implicit conversions）。可以把non-const转化为const（但是反过来不行），可以将point-to-base转化为point-to-derived。

四种新式转换，最明显的区别是安全性和目的：

- `const_cast` 和 `reinterpret_cast` 很不安全，它们没有任何类型检查，所以易出错。
- `dynamic_cast` 和 `static_cast` 更安全，它们进行了类型检查，可以保证转换后的类型是正确的。
- `dynamic_cast` 用于多态类型转换，它检查类型转换是否可行。
- `static_cast` 用于简单的类型转换，它不进行任何类型检查，但它可以在编译时发现错误。

### 条款28 避免返回handles指向对象内部成分

Avoid returning “handles” to object internals

**句柄(handles)**不仅包含引用，也包含指针和迭代器。用于取得某个对象，而返回一个代表对象内部数据的handle，随之而来的便是降低对象封装性的风险。同时，他也可能导致“虽然调用const成员函数却造成对象状态被更改”的情况。

函数如果返回一个handle代表对象内部成分总是危险的原因。无论这个handle是指针、迭代器、引用，也不论这个handle是否为const，也不论哪个返回handle的成员函数是否为const。这里的唯一关键是有个handle被传出去了，一旦如此，你就是暴露在“handle比其所指对象更加长寿”的风险下。

### 条款29 为”异常安全“而努力是值得的

Strive for exception-safe code

异常安全有两个条件：不泄露任何资源；不允许数据结构被破坏。

异常安全函数（Exception-safe function） 提供以下三个保证之一：

- 基本承诺：如果抛出异常，程序内的任何事物仍然保持在有效状态下，没有任何对象或数据结构会因此而败坏，所有对象都处于一种内部前后一致的状态（例如所有class约束条件都继续获得满足），然而程序的显式状态恐怕不可预料。举例，我们可以撰写changeBackground使得当抛出异常是，PrettyMenu对象可以继续拥有原背景图像，或是令它拥有某个默认背景图像，但客户无法预期哪一种情况。
- 强烈保证：如果异常被抛出。程序状态不改变。调用这样的函数需有这样的认识：如果函数成功，就是完全成功。如果函数失败，程序会回复到调用函数之前的状态。（强烈保证比起基本承诺，让人放心多了，因为只有两种可能，而基本承诺下玩意出现异常，程序可能处于任何合法但不合理的状态）
- 不抛保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能，作用于内置类型身上所有操作都提供nothrow保证。这是异常安全码中一个必不可少的关键基础材料。

提供异常安全的两种方法：

- 使用智能指针
- 拷贝和交换 copy-and-swap 

### 条款30 透彻了解inlining的里里外外

Understand the ins and outs of inlining

inline只是对编译器的一个申请，不是强制命令。这项申请可以隐喻提出，也可以明确提出。

将大多数inlining限制在小型、被频繁调用的函数身上。这可使日后的调试过程和二进制升级更容易。也可以使得潜在的代码膨胀问题降低到最小，使程序的速度提升机会最大化。

### 条款31 将文件间的编译依存关系降至最低

Minimize compilation dependencies between files

支持“编译依存性最小化”的一般构想是：相依于声明式，不要相依于定义式。基于此构想的两个手段是Handle classes 和Interface classes。

Handle classes 是一种设计模式，用于隐藏对象的实现细节，从而提高代码的灵活性和可重用性。Handle classes 包含一个指向实际对象的指针，这个指针可以被多个 Handle 对象共享。Handle classes 提供了一个统一的接口，使得用户可以访问实际对象的数据和方法，同时又不必关心实际对象的实现细节。Handle classes 的实现通常是基于 PIMPL（Private Implementation）技术，即将实际实现放在一个私有的类中，并在 Handle 类中保存一个指向该私有类的指针。这样，Handle 类的用户就只能看到 Handle 类的接口，而无法直接访问实际对象的实现细节。

Interface classes 是另一种常见的设计模式，用于实现对象间的解耦。Interface classes 定义了一个抽象接口，该接口描述了对象的行为，但并不提供实际的实现。具体的对象实现这个接口，并提供实际的实现。使用 Interface classes 的好处是，不同的对象可以实现同一个接口，从而实现对象间的松耦合，使得代码更加灵活和可重用。

## 第六章 继承与面向对象设计

**[Inheritance and Object-Oriented Design]**

### 条款32 确定你的public继承塑模出is-a关系

Make sure public inheritance models “is-a.”

如果你令Dpublic继承B，那么意味着**D首先就是B**。B能够做的，D一定能做。而D可以比B表现出更多的特殊性。反之你需要一个D，B对象无法效劳。

### 条款33 避免遮掩继承而来的名称

Avoid hiding inherited names

Derived class作用域被嵌套在base class作用域内。

当编译器看到这里使用mf2，必须估算它指涉refer to了什么东西，编译器的方法是按照作用域从内到外寻找：

- 首先查找local作用域（也就是mf4覆盖的作用域）
- 再找其外围作用域，也就是class Derived覆盖的作用域。
- 再向外，本例是class Base，这里找到
- 如果没找到，那么会接着找，首先找内含Base的那个namespace的作用域，最后往global作用域找去。

为了让被遮掩的名称重见天日，可使用using 声明或转交函数。

### 条款34 区分接口继承和实现继承

Differentiate between inheritance of interface and inheritance of implementation

- 接口继承和实现继承不同。在public继承下，derived classes总是继承base classes的接口。
- pure virtual函数只具体指定接口继承。
- impure virtual 函数具体指定接口继承和默认实现继承。
- non virtual函数具体指定接口继承以及强制性实现继承。

### 条款35 考虑virtual函数以外的其他选择

Consider alternatives to virtual functions

使用 NVI 技巧、std::function、策略模式等等是一种备选的实现多态的方法，满足了这些需求。（我暂时不用，学好设计模式再说）

### 条款36 绝不重新定义继承而来的non-virtual函数

Never redefine an inherited non-virtual function

【条款32】已经说过，所谓public继承意味着is-a。【条款34】描述了为什么在class内声明一个non-virtual函数会为该class建立一个不变性invariant，凌驾其特异性。那么结合这两个观点，那么：

- 适用于B的每一件事，也适用于D，因为D都是B
- B的derived对象一定会继承mf的接口和实现，因为mf是B的一个non-virtual函数。

现在，如果D重新定义mf，那么就出现了矛盾：

- 如果D真有必要实现出与B不同的mf，并且每个B对象必须使用B所提供的mf实现码，那么D就为B不为真。那么D就不该以public继承B；
- 如果D真的必须Public继承B，并且D真的有需要实现出与B不同的mf，那么mf就无法为B反映出“不变性凌驾于特异性”的性质，那么mf就不该是个non-virtual，而是个virtual函数。
- 如果D真的是B，而且mf真的为B反映出“不变性凌驾特异性”的性质，那么D就不需要重新定义mf，也不应该。

【条款7】 (为多态基类声明virtual析构函数)实际上是本条款的一个特殊案例。

### 条款37 绝不重新定义继承而来的缺省参数值

Never redefine a function’s inherited default parameter value

虚函数是动态绑定的，而默认参数是静态绑定的。

### 条款38 通过复合塑模出has-a 或“根据某物实现出“

Model “has-a” or “is-implemented-in-terms-of” through composition

【条款32】曾说，public继承带有一种`is-a`（是一种）的意义、而复合则有两种含义。复合意味着`has-a`（有一个）或`is-implemented-in-terms-of`（根据某物实现出）。程序中的一些对象相当于你所塑造的世界中的一些事物，属于应用域`application domain`。而其他对象则是实现细节上的人工制品，相当于你的软件的实现域`implementation domain`。当复合发生于应用域内的对象之间，表现出`has-a`的关系；当它发生于实现域内则是表现`is-implemented-in-terms-of`的关系。

`has-a` 和`is-a` 很容易区别，但是`is-a`和`is-implemented-in-terms-of`在实现功能时很容易混淆。比如set的底层可以通过list来实现，但是set是不能有重复元素的，而list可以，那么两者就不是is-a的关系。也不能用public继承。

### 条款39 明智而审慎地使用private继承

Use private inheritance judiciously

private继承意味着 is-implemented-in-terms-of。它通常比复合composition的级别低。但是当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时，这么设计是合理的。

### 条款40 明智而审慎地使用多重继承

Use multiple inheritance judiciously

简单的逻辑告诉我们，IO对象只应该有一个文件名称，所以它继承自两个base classes而来的filename不应该重复。

C++同时支持这两种方案。其默认做法是执行复制。如果那不是你想要的，你必须令带有这个数据成为一个virtual base class。

对virtual base classes的忠告很简单：

- 第一，非必要不使用virtual bases。平常请使用non-virtual继承。

- 第二，如果你必须使用virtual base classes，尽可能避免在其中放置数据。这样一来你就不需担心这些classes身上的初始化（和赋值）所带来的诡异事情了。

## 第七章 模板与泛型编程

**[Templates and Generic Programming]**

### 条款41 了解隐式接口和编译期多态

Understand implicit interfaces and compile-time polymorphism

- classes和templates 都支持接口interfaces和多态polymorphism
- 对classes而言，接口是显式的，以函数签名为中心。多态则是通过virtual函数发生于运行期。
- 对template参数而言，接口是隐式的，奠基于有效表达式。多态则是通过template具现化和函数重载解析function overloading resolution发生于编译期。

### 条款42 了解typename的双重意义

Understand the two meanings of typename

- 声明template参数时，前缀class typename是同一的。
- 请使用typename表示嵌套从属类型名称；但不得在base class lists（基类列）或member initialization list（成员初值列）内以它作为base class修饰符。

在 C++ 中，`typename` 关键字在模板定义中经常使用，用于指定一个类型名是类型还是值。这是因为在模板定义中，有些名称可能既可以是类型名，也可以是变量名，这就使得编译器在解析模板参数时变得棘手。

- **一般性规则很简单：任何时候当你想要在template中指涉一个嵌套从属类型名称，就必须在紧邻它的前一个位置上放上关键字typename。**

### 条款43 了解处理模板化基类内的名称

Know how to access names in templatized base classes

面对“指涉base class members“之无效references，编译器的诊断时间可能发生在早期（当解析derived class template 的定义式时），有可能发生在晚期（当那些templates被特定之template实参具现化时）。

C++政策是宁愿较早诊断，这就是为什么“当base classes 从templates中被具现化时”，它假设它对那些base classes的内容毫无所悉的缘故。

可在derived class templates 内通过“this->”指涉base class templates内的成员名称，或藉由一个明白写明的”base class资格修饰符“完成。

### 条款44 将与参数无关的代码抽离templates

Factor parameter-independent code out of templates

使用共性与变性分析“commonality and variability analysis”。来厘清如何生成模板。

### 条款45 运用成员函数模板接受所有兼容类型

Use member function templates to accept “all compatible types.”

- 请使用member function template（成员函数模板）生成“可接受所有兼容类型”的函数
- 如果你上面member templates 用于“泛化 copy构造”或“泛化 assignment 操作”，你最好还是需要声明正常的copy构造函数和copy assignment操作符。因为你不那么做，编译器很可能自己生成默认的，而默认的可能达不到你的要求。

### 条款46 需要类型转换时请为定义非成员函数

Define non-member functions inside templates when type conversions are desired

当我们编写一个class template，而它所提供之“与之template相关的”函数支持“所有参数之隐式类型转换”时，请将那些函数定义为“class template 内部的friend 函数”。

我们虽然使用了friend，但是和friend的传统用途（访问class的non-public成分）毫不相干。为了让类型转换可能发生于所有实参上，我们需要一个non-member函数；而为了令这个函数被自动具现化，我们需要将它声明在class内部，而在class内部声明non-member函数的唯一办法就是令它成为一个friend。不习惯，但是确实有效。

### 条款47 请使用traits classes表现类型信息

Use traits classes for information about types

- Traits classes 使得类型相关信息在编译期可用，它们以template 和template 特化完成实现。
- 整合重载技术后，traits classeskn在编译期对类型执行if-else测试。

### 条款48 认识template元编程 

Be aware of template metaprogramming

TMP有两个伟大的效力：

- 第一，它让某些事情更加容易。
- 第二，由于template metaprogramming执行于C++编译期，因此可将工作从运行期转移到编译器。
  - 这导致一个好处，就是原本某些错误可以在编译期就被揪出来了。
  - 使用TMP的C++程序可能在每一个方面都更加高效：较小的可执行文件、较短的运行期、较少的内存需求。但是编译时间会变长。

TMP已被证明是图灵完备的，通过TMP你可以声明变量、执行循环、编写及调用函数。但其构建与正常的C++对应的很是不同。

## 第八章 定制new 和delete

**[Customizing new and delete]**

### 条款49 了解new-handler的行为

Understand the behavior of the new-handler

在 C++ 中，`new-handler` 是一个回调函数，它会在内存分配失败时被调用。当内存分配失败时，标准库的 `new` 操作符会调用 `new-handler` 函数，以尝试释放一些内存，使得后续的内存分配操作可以成功。

`new-handler` 可以用 `set_new_handler` 函数来设置，这个函数接受一个指向 `new-handler` 回调函数的指针作为参数。如果内存分配失败时没有设置 `new-handler`，`new` 操作符将会抛出一个 `std::bad_alloc` 异常。

`new-handler` 的主要作用是帮助我们在内存分配失败时执行一些定制的操作。例如，当内存分配失败时，我们可以尝试释放一些不必要的内存，或者向用户显示一条错误信息并退出程序。如果没有 `new-handler`，`new` 操作符会默默地失败，导致程序可能会出现奇怪的行为或者崩溃。

### 条款50 了解new和delete的合理替换时机

Understand when it makes sense to replace new and delete

有许多理由需要写一个自定的new和delete，包括改善效能、对heap运用错误进行调试、收集heap使用信息。

但是大多数情况，你不需要自己实际重新写一个。

### 条款51 编写new和delete时需固守常规

Adhere to convention when writing new and delete

operator new实现的效果十分单纯。如果它有能力供应客户申请的内存，就返回一个指针指向那个内存。如果没有那个能力，就遵循【条款49】描述的规则，并抛出一个bad_alloc异常。

operator new应该包含一个无限循环来尝试分配内存，如果不能满足对内存的请求，就应该调用new-handler。它也应该可以处理对0个byte的请求。类的特定版本应该处理比预期更大的内存块的（错误）请求。

operator delete中传递的指针如果是null，应该什么都不做。类特定版本需要处理比预期要大的内存块的（错误）申请。

### 条款52 写了placement new也要写placement delete

Write placement delete if you write placement new

placement new的主要作用不是为了控制内存，而是为了在已经存在的一段内存上创建对象。

- 当你实现operator new的placement版本的时候，确保实现与之相对应的operator delete placement版本。如果你不进行实现，有的程序会发生微妙的，间歇性的内存泄漏。
- 当你声明new和delete的placement版本的时候，确保不要无意识地隐藏这些函数的正常版本。

## 第九章 杂项讨论

**[Miscellany]**

### 条款53 不要轻忽编译器的警告

Pay attention to compiler warnings

严肃对待编译器警告，在编译器支持的最大警告级别下努力写出没有警告的程序。

### 条款54 让自己熟悉包括TR1在内的标准程序库

Familiarize yourself with the standard library, including TR1

好好学STL

### 条款55 让自己熟悉Boost

Familiarize yourself with Boost

Boost NB！