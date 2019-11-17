This repository is test codes and implementations  based on the material from 
the first chapter of the book ["Linux多线程服务端编程:使用muduo C++网络库"](https://book.douban.com/subject/20471211//).

The first chapter discusses one of the most basic problem that may arise when
writing multithreaded c++ program, which is it is hard to do graceful destruct.
Usually if one object can be seen and used in different threads, it can be hard
to gracefully delete the object gracefully. When trying to destruct an object,
it is hard to know if other thread is still calling an object method, and vise
versa. And when that happens, it will cause undefined bahaviour and likely to
cause a core dump.

The solution this chapter brings is to use smart pointers and customize
destructor functions.
