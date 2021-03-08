# Homework 2
余北辰 519030910245

---

**2.2 What is the purpose of the command interpreter? Why is it usually separate from the kernel?**

命令解释程序的作用是读取用户所指定的下一条命令，并且执行该命令。

命令解释程序可能会变化，所以不作为内核的一部分。

（参考《操作系统概念中文翻译版（原书第9版）》 第40页）

---

**2.5 What is the main advantage of the layered approach to system design? What are the disadvantages of the layered approach?**

采用分层法进行系统的模块化，可以简化构造以及调试的过程。由于每一层都只能够调用其下层的功能，调试的时候就可以从最底层向最高层调试、一次只调试一层，而不必考虑对其他层次的影响。这样也可以快速定位错误所发生的层次位置，因为其下层如果没有错误，错误一定发生在当层。

分层法有两个主要的缺点。第一，各层次的合理定义存在困难；第二，分层法与其他方法相比效率较低。

（参考《操作系统概念中文翻译版（原书第9版）》 第55-56页）

---

**2.7 Why do some systems store the operating system in firmware, while others store it on disk?**

有些操作系统是小型操作系统，只需要实现一些简单的与硬件交互的功能，那么将这样的操作系统储存在固件中是比较合适的。而对于大型操作系统或者经常发生改变的操作系统，就很难放在固件较小的存储空间中，因此将引导程序储存在固件中，而将操作系统储存在磁盘中。

（参考《操作系统概念中文翻译版（原书第9版）》 第90页）
