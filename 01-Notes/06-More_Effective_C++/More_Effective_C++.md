# More Effective C++



## 基础议题 Basics 

### 条款01：仔细区别指针和引用

Item 1: Distinguish between pointers and references.

### 条款02：最好使用C++转型操作符

Item 2: Prefer C++-style casts.

### 条款03：绝对不要以多态方式处理数组

Item 3: Never treat arrays polymorphically. 

### 条款04：非必要不提供默认构造函数

Item 4: Avoid gratuitous default constructors. 

## 操作符 Operators 

### 条款05：对定制的”类型转换函数“保持警觉。

Item 5: Be wary of user-defined conversion functions. 

### 条款06：区别好前置后置的递增递减符

Item 6: Distinguish between prefix and postfix forms of increment and decrement operators. 

### 条款07：永远不要重载`&&`、`||`、`,`操作符

Item 7: Never overload &&, ||, or ,. 

### 条款08：了解new delete的不同意义

Item 8: Understand the different meanings of new and delete. 

## 异常 Exceptions 
### 条款09：利用析构函数避免泄露资源
Item 9: Use destructors to prevent resource leaks. 
### 条款10：在构造函数内阻止资源泄露
Item 10: Prevent resource leaks in constructors. 
### 条款11：禁止异常流出析构函数之外
Item 11: Prevent exceptions from leaving destructors. 
### 条款12：了解“抛出异常”和“传递参数”或“调用虚函数”的区别
Item 12: Understand how throwing an exception differs from passing a parameter or calling a virtual function. 
### 条款13：以传引用方式来捕捉异常
Item 13: Catch exceptions by reference. 
### 条款14：明智运用异常规范
Item 14: Use exception specifications judiciously. 
### 条款15：了解异常处理的成本
Item 15: Understand the costs of exception handling. 

## 效率 Efficiency 
### 条款16：谨记80-20法则
Item 16: Remember the 80-20 rule.
### 条款17：考虑使用缓式评估
Item 17: Consider using lazy evaluation.
### 条款18：分期摊还预期的计算成本
Item 18: Amortize the cost of expected computations. 
### 条款19：了解临时对象的来源
Item 19: Understand the origin of temporary objects. 
### 条款20：协助完成返回值优化RVO1
Item 20: Facilitate the return value optimization. 
### 条款21：利用重载机制来避免类型转换
Item 21: Overload to avoid implicit type conversions. 
### 条款22：考虑以操作符复合形式来取代其独身形式
Item 22: Consider using op= instead of stand-alone op. 
### 条款23：考虑使用其他程序库
Item 23: Consider alternative libraries. 
### 条款24：了解虚函数、多重继承、虚基类和RTTI的成本
Item 24: Understand the costs of virtual functions, multiple inheritance, virtual base classes, and RTTI. 

## 技术 Techniques 
### 条款25：将构造函数和非成员函数虚化
Item 25: Virtualizing constructors and non-member functions. 
### 条款26：限制某个class所能产生的对象数量
Item 26: Limiting the number of objects of a class. 
### 条款27：要求（或禁止）对象产生于heap中
Item 27: Requiring or prohibiting heap-based objects. 
### 条款28：智能指针
Item 28: Smart pointers.
### 条款29：引用计数
Item 29: Reference counting. 
### 条款30：替身/代理类
Item 30: Proxy classes. 
### 条款31：让函数根据一个以上的对象类型来决定如何虚化
Item 31: Making functions virtual with respect to more than one object. 

## 杂项讨论 Miscellany 
### 条款32：在未来时态下发展程序
Item 32: Program in the future tense. 
### 条款33：将非尾端类设计为抽象类
Item 33: Make non-leaf classes abstract. 
### 条款34：理解如何在一个程序中结合C++和C
Item 34: Understand how to combine C++ and C in the same program. 
### 条款35：让自己熟悉标准C++语言
Item 35: Familiarize yourself with the language standard. 