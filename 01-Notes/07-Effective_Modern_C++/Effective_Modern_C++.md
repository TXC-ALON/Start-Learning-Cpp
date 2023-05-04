# Effective Modern C++

## 一 类型推导

 Item 1:理解模板类型推导 
 Item 2:理解auto类型推导
 Item 3:理解decltype
 Item 4:学会查看类型推导结果

## 二 auto

 Item 5:优先考虑auto而⾮显式类型声明
 Item 6:auto推导若⾮⼰愿，使⽤显式类型初始化惯⽤法

## 三 移步现代C++

 Item 7:区别使⽤()和{}创建对象 

 Item 8:优先考虑nullptr而⾮0和NULL
 Item 9:优先考虑别名声明而⾮typedefs
 Item 10:优先考虑限域枚举而⾮未限域枚举
 Item 11:优先考虑使⽤deleted函数而⾮使⽤未定义的私有声明
 Item 12:使⽤override声明重载函数
 Item 13:优先考虑const_iterator而⾮iterator
 Item 14:如果函数不抛出异常请使⽤noexcept
 Item 15:尽可能的使⽤constexpr
 Item 16:让const成员函数线程安全
 Item 17:理解特殊成员函数函数的⽣成

## 四 智能指针

 Item 18:对于独占资源使⽤std::unique_ptr
 Item 19:对于共享资源使⽤std::shared_ptr
 Item 20:像std::shared_ptr⼀样使⽤std::weak_ptr可能造成dangle
 Item 21:优先考虑使⽤std::make_unique和std::make_shared而⾮new 
 Item 22:当使⽤Pimpl惯⽤法，请在实现⽂件中定义特殊成员函数 

## 五 右值引⽤，移动语意，完美转发

 Item 23:理解std::move和std::forward 
 Item 24:区别通⽤引⽤和右值引⽤
 Item 25:对于右值引⽤使⽤std::move，对于通⽤引⽤使⽤std::forward
 Item 26:避免重载通⽤引⽤
 Item 27:熟悉重载通⽤引⽤的替代品由
 Item 28:理解引⽤折叠
 Item 29:认识移动操作的缺点
 Item 30:熟悉完美转发失败的情况

## 六 Lambda表达式

 Item 31:避免使⽤默认捕获模式
 Item 32:使⽤初始化捕获来移动对象到闭包中
 Item 33:对于std::forward的auto&&形参使⽤decltype
 Item 34:优先考虑lambda表达式而⾮std::bind

## 七 并发API

 Item 35:优先考虑基于任务的编程而⾮基于线程的编程
 Item 36:如果有异步的必要请指定std::launch::threads
 Item 37:从各个⽅⾯使得std::threads unjoinable
 Item 38:关注不同线程句柄析构⾏为 
 Item 39:考虑对于单次事件通信使⽤void
 Item 40:对于并发使⽤std::atomic，volatile⽤于特殊内存区

## 八 微调

 Item 41:对于那些可移动总是被拷⻉的形参使⽤传值⽅式
 Item 42:考虑就地创建而⾮插⼊