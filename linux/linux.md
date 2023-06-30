- linux下的睡眠函数sleep()的单位是s；usleep()的单位是ms

- 十六进制和十进制的转换：0x1000（4096） 0x10000（65536）0x100000（1M）

- 时间

```c
#include<time.h>
time_t tp=time(NULL);
char localtime[1024];
bzero(localtime,1024);
ctime_r(&tp,localtime);
```

- 小写转大写

```c
#include<ctype.h>
char c=toupper('a');//'A'
```













什么是线程，什么是进程，联系和区别

并发和并行；并发和同步（同步解决并发问题）

线程不同状态间的切换（5个，重要的3个）

**什么是协程？（c++20加入了协程）**

> 系统的权限：ring0 ring1 ring2 ring3
>
> 最里面的权限最高ring0：内核态
>
> 最外面的权限最低ring3：用户态
>
> 内核态可以操作硬件，可以向磁盘中写东西
>
> 用户态没有权限操作内存和硬盘，如果想操作，要切换到内核态，操作完再切换回用户态
>
> 线程调度、进程调度都是内核态来完成的。也就是说，线程由运行切换到等待挂起是用户态到内核态的过程。
>
> cpu的上下文切换：用户态到内核态时，cpu要把原来的数据和指令保存起来，将内核态的数据加载到cpu，进行运算；运算完再加载回来（寄存器）。
>
> 线程的上下文切换：上一个线程的时间片用完了，会回到就绪态，运行新的线程；（线程执行时，cpu会保存线程的数据和指令地址）此时，要把上一个线程的数据和指令地址存起来（保存现场），把新的线程的数据和指令地址加载进来。（cpu里面装的都是现在正在运行的东西）
>
> **协程是一直工作在用户态的工作单元，是软件层面比线程更小的执行单元，在用户态中调度（切换）可以降低cpu的负载。优势：用有限的资源干更多的活**

线程的并发问题？

> 线程同步方式：原子访问、临界区、事件、互斥量、信号量、条件变量
>
> 进程的同步方式：信号量、互斥量
>
> （**只要是同步的方式都可以用来通信**）
>
> 线程通信方式：同一个进程：全局变量；不同进程：进程间通信
>
> 进程通信方式：文件映射（mmap），管道，动态库节点（内存映射），剪贴板，套接字

生产者消费者模型？线程池的设计？怎么设计优化？

> 组成：生产者、消费者、同步队列
>
> 生产者生产商品，放入到同步队列
>
> 消费者监听同步队列，拿里面的商品
>
> 阻塞：同步队列空满
>
>  
>
> 线程池：生产者、消费者、管理者、同步队列
>
> 一些线程执行生产者接口，向同步队列投递任务
>
> 创建一些线程处于等待状态，监听同步队列，若有任务，激活消费者线程，执行其内的任务
>
> 同步队列：加锁的循环队列，锁：互斥量条件变量
>
> 管理者：根据空闲线程和繁忙线程的比例创建和销毁线程
>
>  
>
> 优化：扩容缩容（管理者）；可以细化线程的功能，例如有的线程专门做运算，有的专门做逻辑处理；无锁编程（乐观锁）无锁队列

线程池的任务队列设置多大？为什么采用环形缓冲区（数组实现队列）？为什么要使用线程池？

> 尽量大
>
> 如果使用链表，不利于插入删除；数组的空间利用率高
>
> 不希望频繁的创建销毁线程

线程池初始的线程数设置成什么合理？

> **理论结果（经验）：n核处理器，通过执行业务单线程执行本地的任务计算时间x，等待事件y，工作线程数=n*(x+y)/x ;x==y（无缝衔接）：2 *n（核心的2倍）**

**乐观锁和悲观锁、ABA问题和解决方案**

> 乐观锁：有并发加锁，无并发不加（判断并发：读取两次数据，判断是否一致）
>
> 悲观锁：不管有没有并大，都加锁（读写都加锁）
>
> ABA问题：乐观锁判断并发时，如果数据中途改变后又变了回来，判断为无并发
>
> 解决：加个版本控制（标记），每次发生更改，版本+1，判断并发时看版本，若有变化，说明并发

**CAS机制实现乐观锁**

进程调度问题，什么时候发生进程调度？进程调度算法？

> 1. 时间片耗尽，时间片轮转
> 2. 进程等待资源被挂起，切换到其他进程
> 3. sleep主动挂起
> 4. 当有更高优先级进程到来时，保证优先级高的先执行（分两种情况：可剥夺和不可剥夺）
>
>  
>
> 1. 先来先服务（非抢占）按照就绪次序来分配cpu
> 2. 时间片轮转（抢占）用于分时系统，按先来先服务，从就绪队列取第一个执行，仅能运行一个时间片
> 3. 短作业优先调度（非抢占）从后备队列中选择一个或若干个运行时间最短的作业，调入内存执行
> 4. 最短剩余时间优先调度算法（抢占）当一个进程加入到就绪队列时，他可能比当前运行的进程具有更短的剩余时间，因此只要新进程就绪，调度程序就可能抢占当前正在运行的进程
> 5. 高响应比优先调度算法（非抢占）用于作业调度，响应比=（等待时间+要求服务时间）/要求服务时间。只有当前运行的进程主动放弃cpu时，从后备作业中选择响应比最高的执行
> 6. 优先级调度（抢占）选择更高优先级的进程占用cpu，优先级分为动态优先级和静态优先级

死锁：死锁的概念？产生的条件？预防死锁？处理死锁的办法?

> 多个进程竞争资源而处于阻塞状态，相互等待，如果没有外力推进，进程无法继续进行
>
>  
>
> 互斥、不可剥夺、请求与保持（部分分配）、环路等待（循环等待）
>
>  
>
> 预防>处理；破坏死锁产生的四个条件（请求与保持：预先静态分配算法；环路等待：有序资源分配法）
>
>  
>
> 避免死锁：银行家算法（迪杰斯特拉）

**内存管理--windows**

> 连续分配管理：
>
> 1. 单一连续分配：只能用于单用户单任务操作系统；作业一旦进入内存，要等待结束之后释放；无法实现多个进程共享主存。
> 2. 固定分区分配：将内存分成若干个不同分区放不同程序；要先确定，运行了就不能改变；通常采用静态重定位方式装内存。
> 3. 动态分区分配：是可变分区分配。根据作业大小动态分配创建分区。
>
> 
>
> 非连续分配管理：
>
> 虚拟地址（逻辑地址）通过内存管理单元MMU映射表找到物理空间
>
> 1. 页式：逻辑空间分为页，从0开始编号，页面大小4KB；物理内存空间分为块（不一定连续），块大小与页大小相等，从0开始编号。地址长度为32位，0-11位为页内地址（低位到高位），即每页大小为4KB，12-31位为页号，最多2^20页。（逻辑地址/2^12=页号；%2^12=页内地址（偏移x字节））
>
>    ​		**缺页中断和页面置换算法：MMU存储映射表，比如页表，空间是有限的，如果找不到对应的物理地址，就会发生缺页中断，此时会调用页面置换算法（LRU最近最少使用算法、FIFO先进先出置换算法、OPT最佳页面置换算法），淘汰旧页面，加载新页面。**
>
>    ​		**内部碎片、外部碎片：区分内部碎片和外部碎片要看是否是固定的空间，页式的固定空间是4KB。内部碎片（页式）是固定空间分配给你，你没用完；外部碎片（段式）是非固定空间大小的，分配完了系统剩下的。**
>
>    优点：没有外部碎片，内碎片大小不超过页的大小
>
>    缺点：整个程序要全部装入内存，要求有相应的硬件支持
>
> 
>
> 2. 段式：用户编制的程序是由若干段组成的：一个程序可以由一个主程序、若干子程序、符号表、栈以及数据等若干段组成。每一段都有独立、完整的逻辑意义，每一段程序都可以独立编制，且每一段的长度可以不同。段式存储管理支持用户的分段观点，具有逻辑上的清晰和完整性。以段为单位进行存储空间的管理。
>
>    将用户程序地址空间分成若干个大小不等的段，每段可以定义一组相对完整的逻辑信息；存储分配时，以段为单位，段与段在内存中可以不相邻接，也实现了离散分配。内存空间为每个段分配一个连续的分区。（16位段号，16位偏移量，即段最大大小是64KB；逻辑地址/2^16=段号；%2^16=段内地址（偏移x字节））
>
>    ![image-20230414101601129](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230414101601129.png)
>
>    -  根据逻辑将空间分段能满足用户需求，不过有外部碎片没有内部碎片
>
>  
>
> 3. 段页式：用户程序先分段，每个段内再分页（内部原理同基本的分页、分段相同）
>
>    地址结构（逻辑地址）：段号 段内页号 页内地址
>
>    - 结合段式和页式的优点，内部碎片比页式更多。
>
>  
>
> 4. 段式和页式 段页式存储的比较
>
>    页式存储就是说将程序分页时，页的大小时固定的，只根据页面大小强硬的将程序切割开，而分段时比较灵活，只有一段程序有了完整的意义才将这一段切割开。
>
>    分页式作业的地址空间是一维的，页间的逻辑地址是连续的；
>
>    分段式作业的地址空间是二维的，段间的逻辑地址是不连续的。
>
>    在页式，段式存储管理中，为获得一条指令或数据，须两次访问内存；而段也是须三次访问内存。
>
>    - linux内存管理：多级页表

页面置换算法：LRU-最近最少使用算法（力扣146）

> 使用头添加尾删除的链表作为存储结构
>
> 链表存在最大缓存容量-链表的最大长度
>
> 如何操作？
>
> 访问节点：若命中->找到这个节点->将该点移动到头（删除该节点，头添加该节点）
>
> ​					若未命中->看是否到达最大容量->是（尾删除，头添加）否（头添加）
>
> 淘汰节点：为删除
>
> 优化：查找算法（有序用二分，无序用映射，映射分两种，哈希和map）

页面置换算法：FIFO-先进先出置换算法

> 先来的先淘汰
>
> 以尾删除头添加的队列作为数据结构（可以使用链表也可以使用循环队列（数组）实现）
>
> 队列存在最大缓存容量-队列的最大容量
>
> 如何操作？
>
> 访问节点：若命中->不操作
>
> ​					若未命中->看是否达到最大容量：是（头删除、尾添加）否（尾添加）
>
> 淘汰节点：头删除

页面置换算法：opt-最优页面置换算法

> 基础思路：当一个缺页中断发生时，对于保存在内存当中的每一个逻辑页面，计算在它的下一次访问之前，还需要等待多长时间，从中选择等待时间最长的那个被置换。
>
> - 这只是一个理想情况，在实际操作系统中无法知道需要等待多长时间---算法很难实现。
> - 可用于作为其他算法性能评价的依据。

静态库动态库

c语言的编译原理

> 1. 预处理：生成.i文件
>
>    宏定义、条件预编译指令（#ifdef）、头文件的包含、特殊符号（/**/）、保留指令（#pragma）
>
> 2. 编译：生成.a 或.s文件（生成中间文件）
>
>    单词--词法解析--语法解析--语义解析--优化--目标代码生成（由代码生成器将中间代码转换成目标机器代码，生成一系列的代码序列--汇编语言表示）--目标代码优化
>
> 3. 汇编：生成.obj或.o文件（目标文件）
>
>    汇编代码转成机器可执行代码，将中间代码转换的编程指令集放入.obj或.o文件（目标文件）里
>
> 4. 链接：生成执行文件
>
>    通过调用链接器链接程序运行需要的目标文件，以及所依赖的其他库文件，定位函数的实现，以及存储指令的位置，最后生成可执行文件.exe，链接分为静态链接和动态链接。

volatile关键字：可以修饰变量

> 作用：
>
> 1. 运行时，保证线程工作内存（cpu寄存器）和主存（物理内存）数据的一致
>    - 当volatile修饰变量，写值会立即给主存赋值，并且每一次读取值，直接到主存读取；
>    - 并且写先于读，从而保证工作内存（缓存）和主存数据的一致
> 2. 编译时，避免修饰的变量相关的编译优化，所导致多线程出现运行问题。
>
> 3. 编译优化（release版本会有编译优化选项）--指令重排的问题（可能会颠倒语句的顺序）；volatile可以避免编译优化中的指令重排问题，被修饰的语句不会出现指令重排。

**linux操作系统**

> linux基本命令：apt-get ls cd vi ifconfig mkdir touch cp rm mv cat more less man chmod grep tar kill 用户管理 ping netstat ps telnet umask echo ssh ftp 等
>
> - 怎么看内存？
> - 怎么看磁盘？
> - 怎么看进程？
> - 怎么看网络？
> - 怎么安装开源软件？
>
> 
>
> 文件IO系统函数（和windows c的文件运行时库函数的区别：c是先向缓冲区内写，写满了再写入内存（也可以通过flush?函数将未满缓冲区内的数据写入内存），linuxIO函数是直接对底层进行操作的，不用遵循c的规定（缓冲区））：open read write close lseek fcntl
>
> 
>
> **文件系统：** [3.文件系统.chm](D:\desktop\杂七杂八\各种说明\linux\3.文件系统.chm) 
>
> - **什么是文件系统？什么是块？什么是块组？块组的组成？**
> - **什么是inode？**
> - **再某一个路径下创建一个文件，向里面些内容，文件系统都做了什么？**
> - > 创建文本：在inode table中找一个位置，存文件属性；将inode bitmap中相应的位置成1；文件属性中的数据块指针指向data block的某个点（启用该块），将块位图中对应的位置成1；
>   >
>   > 写入数据：在块组描述符表中找到块位图的起始位置、inode bitmap的起始位置、inode table的起始位置和data block的起始位置，找到后，在inode table 中找到节点属性，根据文件属性中的数据块指针在data block找到对应的块，向其内写入数据
>   >
>   > 删除文件：
>   >
>   > 硬链接的删除：（硬链接和源文件使用同一个inode节点），删除硬链接，触发删除记录项和硬链接计数-1，当硬链接计数为0时，触发：block bitmap 翻转1->0，inode bitmap翻转1->0，进而回收文件数据。
>   >
>   > 软链接的删除：（软链接相当于快捷方式）软链接删除，源文件无变化，源文件删除，软链接不可用。
> - **创建出的文件是怎么浏览的？**
> - **手写遍历某个目录**
> - **间接寻址**：一级、二级、三级间接寻址指针
> - **硬链接软链接的区别：1. 围绕inode节点中文件属性 2. 真正删除文件的时机**
>
>  
>
> linux工具链
>
> 1. vim的使用：命令模式、编辑模式、末行模式、各种快捷键、分屏操作
> 2. gcc 编译指令以及选项：gcc -ocDOeE Wall  gL（库的路径）l（加库的文件）I
> 3. gdb调试：start run n s b p d
> 4. makefile:三要素、变量、示例
> 5. ar生成静态库 ld链接器
> 6. 重点：gdb生成并查看coredump文件，什么是coredump文件？**产生异常退出时，保留异常信息的文件。**
>
>  
>
> 静态库和共享库
>
> realname soname linkname是什么？
>
>  
>
> 正则表达式
>
> 元字符正则表达式的书写
>
> 示例：写提取或校验手机号的正则表达式；写提取或校验邮箱的正则表达式
>
> 如何通过函数完成正则表达式模式匹配
>
>  
>
> linux多线程和多进程的通信和同步
>
> 原子访问的使用 互斥锁与条件变量的使用
>
> 生产者消费者模型 线程池的实现
>
>  
>
> 守护进程、孤儿进程、僵尸进程
>
>  
>
> spinlock自旋锁
>
> spinlock自旋锁在同一时刻，只能有一个进程获得自旋锁，其他尝试获得自旋锁的任何进程将一直进行不断测试，获取资源（获取自旋锁）--自旋
>
> 除此之外，不做任何事情，在获取资源之前一直忙等状态（就绪）不休眠，会一直占cpu
>
> while(1){
>
> ​		尝试获取自旋锁
>
> ​		if(获取到了自旋锁)break;
>
> }
>
> 直到获取资源才退出自旋
>
> 适合保持锁时间短的场合，是忙等不休眠的，互斥锁是休眠的
>
> 相比之下，自旋锁效率比互斥锁更高。
>
> 可能存在的问题：1. 死锁 2. 占用cpu资源较多
>
> 一般自旋锁的实现，要设置参数限定最大尝试次数，达到最大值，就放弃循环，等待下一次机会。
>
>  
>
> linux网络编程
>
> linux下套接字编程的流程
>
> linux下多路IO复用模型 select poll epoll
>
> 对于epoll在项目中的et模式 lt模式
>
> 阻塞和非阻塞的理解，以及他们的实现细节，遇到问题的处理
>
>  
>
> linux服务器性能测试
>
> 分布式 集群 负载均衡等
>
> 常见服务器模型，以及常见开源服务器模型 如：muduo libevent libuv等
>
> 反应堆模型reactor：三个重要组件：多路复用器（同时阻塞多个fd,监听读写事件）、事件分发器（就绪事件分发到处理器）、事件处理器（负责处理特定事件的处理函数）

海量数据处理

> 类型分析：判断有没有、查找、排序、数据量特别大、内存由限制
>
> 第一类问题：topk问题
>
> - 1000万找前50最大的---小堆
>
> 第二类问题：海量数据的两个文件找相同
>
> 































# github







 [GitHub.pdf](相关文件\GitHub.pdf) 

**关键字搜索**

```
官方推荐项目：awesome(如：python awesome)
文档：tutorial(如：python tutorial)
实例：sample(如：c++ sample)
```



**github三要素**

1. 仓库（Respositroy）：用户创建的仓库用于存储开源工程，仓库可选择public or private ，一般情况下一个仓库对应一个工程。
2. 提交（Commit）：可以记录用户所有对于项目资源和代码文件的操作，便于开发者回溯，可以返回找到任意时刻的修改。
3. 分支（Branch）：主要用于多人协作开发



- 本地代码资源通过Git同步到云端仓库（上传）





# Git  markdown



**git与github账户关联及测试关联**

```bash
#测试git是否关联了用户
ssh -T git@github.com

#显示所有git配置列表
git config --list

#修改配置中的用户名及账户名（邮箱），如果配置中没有这两项，也可以通过下面的命令添加
git config --global user.email "your email"
git config --global user.name "your username"

#创建访问密钥rsa_keys (/c/Users/PC/.ssh/id_rs)
ssh-keygen -t rsa -C "your email"

#复制C:\Users\PC\.ssh\id_rsa.pub文档内的密钥数据，打开github，进入设置，在ssh and gpg keys选项内新建一个ssh密钥，在内容处粘贴复制的内容。
```



**22端口错误解决方法：**

![image-20230119083103385](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230119083103385.png)



- 本地代码资源通过git同步到云端仓库（上传）
- 通过Push推同步仓库，可以通过Pull拉取仓库（clone下载的是源代码和资源，pull拉取的是仓库结构资源）



**上传相关**

```bash
#在文件夹中创建本地仓库
git init

#在guthub仓库中复制仓库下的链接（git@github.com:dreamxian4/baby.git）[ssh]

#对云端仓库创建并起别名origin或删除
git remote add origin "git@github.com:dreamxian4/baby.git"
git remote remove origin

#上传代码
#1.加入缓冲区
git add first.c
#查看缓冲区（查看状态）
git status
#2.上传
git commit -m "备注"
#3.本地和云端合并
git push origin master

#恢复删除文件
git restore first.c
#彻底删除（删除云端文件）
rm first.c
git rm first.c
git commit -m "删除文件"
git push origin master
```



**如果本地仓库的内容与云端的版本不一致，可以通过git pull 拉取云端内容与本地同步，保持一致性**

**拉取的用途：**

1. 协作开发，拉取其他人的仓库，创建新分支进行编码。
2. 如果某一刻push推失败了，可能因为本地与云端的版本不一致，可以通过先拉取再推送的方式解决此类问题。



```bash
#拉取
git pull --rebase origin

#从guthub上下载克隆项目到本地
git clone 工程地址（SSH）
```



**readme.md文件**

 [README.md](相关文件\README.md) 

````
touch README.md

# level 1 title
## level 2 title
### level 3 titlt
#### level 4 title
##### level 5 titlt

*正文以斜体的形式呈现*

**正文以粗体的形式呈现**

***粗斜体***

~~正文添加删除线效果~~

正文中有`关键字`

这是一段测试文本，为此README的正文内容<br><br>测试文本第二行数据

---
****

#### 无序列表
* 物理科学
   * 粒子物理
   * 原子核物理
   * 凝聚态物理
 * 流体物理
* 生物
* 计算机科学
   * 硬件概述
   * 网络通信
      * TCP
   * 汇编反汇编

#### 有序列表
1. 单机游戏
     1. FPS
         1. PUBG
         2. CSGO
     2. 第三人称
2. 旅游购物
3. 电子游戏



#### 引用

> 一级引用
>> 二级引用
>>> 三级引用
>>>> 四级引用



#### 表格

游戏名|游戏价格|游戏排行
--|:--:|--:|
PUBG|￥20|26
APEX|￥30|5
LOL|￥20|1


#### 超链接

[Github官方网站](https://github.com "点击跳转到Github")


#### 插入图片
![壁纸截图](D://desktop//a.png)


#### 插入代码
```c
#include<stdio.h>
int main(){
        return 0;
}


```

```bash
cd /user/bin
```

```cpp
#include<iostream>
using namespace std;

```
````







# 进程 PROCESS



## 基本知识





​		**进程基本概述**：进程是系统中的基本执行单元，操作系统可以向进程分配系统资源，进程完成一些特定任务。

- **进程是最小分配西元单位，线程是最小的调度单位**





进程创建时系统分配内存资源

![image-20230209102248503](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209102248503.png)





**进程与程序的关系：**

​		**程序文件**（app,apk,exe）是静态资源，占用磁盘空间（程序是进程的静态表现）。

​		**进程**（PROCESS）占用CPU,MEM等资源，是程序的动态表现，程序执行后创建一个进程，执行任务。





**进程的生存环境**

![image-20230209102634546](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209102634546.png)





​		进程创建后分配的内存地址为**虚拟内存地址**，是通过虚拟内存**间接寻址**的方式获取，与实际的物理内存虽有练习，但并不是一对一的使用比例。

​		虚拟内存地址和物理内存地址之间存在**虚拟内存映射**（系统中复杂的映射关系，保存在**虚拟地址映射表**中（内存管理系负责维护记录这些映射条目））。

![image-20230209103125615](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209103125615.png)





**内存的基本单位**

内存的最小单位是**Page 页单位 1page=4096Bytes**（4K）		

- 例如malloc函数或new都是以4K为单位分配内存的

**内存的四种基本权限：**

1. PROT_READ （只读）
2. PROT_WRITE （只写）
3. PROT_EXEC （可执行）
4. PROT_NONE （无权限）

![image-20230209103542216](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209103542216.png)

```
程序员A：
申请一次内存（3000）系统分配一次内存页（4096），系统堆内存进行使用限制，允许程序员A使用3000，锁定1096；
申请第二次内存，系统检查其内存使用情况，根据需求分配新的一页

程序员B：
向系统申请一次内存，系统给其分配两页（8192）

程序员B以更少的系统调度，完成任务，效率更高
```





**系统调用（调用过程）**

![image-20230209103913998](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209103913998.png)





**cpu运行级别**

![image-20230209104009370](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209104009370.png)



- 触发用户层和内核层权限的转换：系统调用、时间片耗尽、异常





**分时复用机制：**

​		有限的cpu西元被多进程共用，cpu占用有时间限制，创建时间片单位，进程可以获取时间片，暂时使用cpu，完成多进程快速切换。





**保存和恢复处理器现场**

cpu内部的主要部件：

![image-20230209105252349](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209105252349.png)

​		**多进程共用寄存器可能引发使用冲突，运算过程覆盖或重载；使用保存回复现场的手段，避免冲突，可以让多进程很好的共用资源。**

![image-20230209111214304](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209111214304.png)





**linux进程状态转换：**

1. **就绪态**：当前进程已经创建初始化完毕，准备就绪，等待cpu资源执行

2. **运行态**：进程已经获取了cpu资源，开始执行特定任务（R）

3. **阻塞态**：进程即将陷入睡眠或阻塞，停止工作，放弃时间片资源（S）

   > 阻塞态可能被强制中断，无法阻塞预期的时长，无法实现特定任务

4. **挂起态**：进程即将进入挂起状态，停止工作，放弃时间片资源（T）

   > 挂起态的进程无法被外力强制中断，只允许唤醒来拉活进程

5. **新生态/中止态**



**僵尸态进程（**Zombie Process) 内存泄漏：子进程先于父进程退出，且父进程没有回收子进程，子进程变成僵尸进程。

**孤儿进程**（Orphan Process) 孤儿进程的危害是有弹性的，危害的大小取决于孤儿进程的工作：父进程先于子进程退出，子进程变成孤儿进程。







## 进程源语



进程源语基本概述：linux提供的系统级API函数接口，用于进程开发

```
//获取进程pid;哪个进程调用就返回哪个进程的pid
int pid=getpid();
```



### **FORK（进程创建）**

> **pid_t** #进程pid类型，进程ID，身份标识，存于PCB中

```bash
pid_t pid = fork(void) #该函数执行，创建一个子进程
```

​		进程间的亲缘关系（父子进程构成），在linux操作系统下，每个进程不一定有子进程但必然有父进程，int(0)根进程比较特殊，属于系统第一个进程，它是没有父进程的。

![image-20230209114418583](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230209114418583.png)

![image-20230210075200386](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210075200386.png)

![image-20230210075230420](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210075230420.png)

![image-20230210075256286](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210075256286.png)





**关于父子进程继承：**

![image-20230210080222979](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210080222979.png)



- 父子进程对于代码的执行，父进程从起始位置执行到末尾位置（包含fork），但是子进程从fork之后执行到末尾位置。（×实际fork函数子进程也执行了（返回0））





**区分父子进程工作区：**

![image-20230210081234534](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210081234534.png)

> 父进程返回pid（>0）
>
> 子进程返回0
>
> 失败返回-1

![image-20230210082355833](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210082355833.png)

- 严禁子进程踏出工作区，让子进程阻塞在工作区或者执行完工作区立即结束，子进程的生命周期为工作区开始到工作区结束。





**创建多个子进程（一父多子）**

![image-20230210084407735](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210084407735.png)





**fork函数的版本变更**

1. 第一版fork：

   ​		老版的fork，父进程创建子进程后，要将自身资源继承给子进程（拷贝继承），如果子进程完全不使用父进程拷过来的资源，那么这次拷贝没有任何意义，反而浪费系统资源。

2. 第二版fork：

   ​		vfork函数创建子进程，只对内核层进行初始化，用户层为空，预留给开发者自行设置（使用vfork创建的子进程是无法直接使用的），必须结合exec使用。

3. 第三版fork：

   ​		新版的fork加入了读时共享，写时复制机制，该机制可以检测出子进程是否需要继承，如果需要则拷贝，不需要则映射。

![image-20230210085708649](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210085708649.png)

- 读时共享，父进程创建映射，子进程读取映射内容可以读使用
- 写时复制，子进程要写访问映射资源，父进程检测到子进程需要继承，则拷贝一份给子进程
- 读时共享写时复制，写复制机制对父子都有效，无论时谁写，都要对子进程进行拷贝，通过这种做法，可以让子进程继承不同的代码片段。







### **EXECL（进程功能重载）**





​		子进程可以加载电脑中现有程序或命令，获取该程序的应用层内容，让一个子进程可以用很简单的方式，获取出色的功能。

![image-20230210111122070](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230210111122070.png)





**代码实现**

```c
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

else if(pid==0){
	printf("child process %d running...\n",getpid());
	//重载成功后火狐浏览器的代码会替换本部分的代码（用户层代码），所以后面的都不会执行（被替换掉了）
	//第一个参数是程序的位置：which firefox
	//第二个参数是命令名称
	//第三个参数是执行命令时的参数（每个参数用双引号隔开）
	//最后一个参数时NULL，代表输入参数完成
	execl("/usr/bin/firefox","firefox","www.baidu.com",NULL);
	execl("/usr/bin/touch","touch","aa","bb","cc",NULL);
	//一定要在参数的最后传null,表示参数传递完毕
	printf("child done\n");		//不会执行
}
```

- 如果需要子进程完成特定自定义任务，一定要在fork之后，execl之前执行，exec之后的代码已被覆盖~





**execl execlp execv execvp execve:**

​		l：参数以字符串形式单独传递。

​		v：参数以字符指针数组形式传递

```
char* pram={"firefox","www.baidu.com",NULL};
execv("/usr/bin/firefox",pram);
```

​		p：自动寻找命令位置，可以直接填写程序名，不需要写路径

```
char* pram={"firefox","www.baidu.com",NULL};
execvp("firefox",pram);
```

​		e：支持重载时，自定义进程环境变量





**用途：**方便进程完成共层扩展，如果系统有现成的功能命令，开发者无需二次实现，直接可以使用。也可以重载自定义实现的软件程序。







### **WAIT,WAITPID（进程回收）**



​		子进程被父进程fork创建，如果子进程先于父进程结束，需要被父进程回收；如果不回收会产生僵尸进程（内存泄漏）。



**产生内存泄漏的过程、父进程回收子进程的原因：**

![image-20230211162727064](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230211162727064.png)



**回收方式：**

1. pid_t zpid=wait(int* status)函数，阻塞回收僵尸进程

   ​	头文件：#include<sys/wait.h>

> status：传出参数，用于验尸；传出子进程的退出信息到status，如果并不关心子进程的退出原因，可以传NULL。

> zpid：回收成功：返回子进程的pid，回收失败（没有子进程可回收）：返回-1。

![image-20230211171358836](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230211171358836.png)



2. pid_t zpid=waitpid(pid_t pid,int* status,int opt) 非阻塞回收

> pid：>0：直接传递一个子进程的pid，那么waitpid就会回收这个指定的子进程
>
> ​		  -1：回收任意子进程；只要是子进程都可以回收掉
>
> ​		  0：同组回收，父进程只能回收与自身同组的子进程，其他组中的子进程回收不掉。
>
> ​		 <-1：例如：-3000，跨组回收

> status ：传出参数，用于验尸；传出子进程的推出信息到status，如果并不关心子进程的退出原因，可以传NULL。

> opt     ：WNOHANG  此关键字可以将waitpid改成非阻塞方式；失败即立即返回，不会阻塞。



> 返回值zpid:
>
> ​	>0：回收成功将子进程的pid返回
>
> ​	-1：没有可回收的子进程却调用wait
>
> ​	0：子进程未结束，无法回收，waitpid非阻塞返回0

![image-20230211172056755](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230211172056755.png)

- 采用非阻塞回收模式，可以在父进程回收的过程中，穿插执行一些自身的任务





**回收验证，获取子进程推出原因：**

​		子进程正常退出（return,exit）：代码执行结束指令，种植进程。

​		子进程异常退出：子进程执行过程中，被信号或其他方式中止，这些为异常退出。

![image-20230211173242495](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230211173242495.png)



```c
WIFEXITED(int status);  //判断是否为正常退出
int a=WEXITSTATUS(int status);	//正常退出返回码
WIFSIGNALED(int status);	//判断是否为异常退出
WTERMSIG(int status);	//异常退出返回码
```

![image-20230211175030746](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230211175030746.png)







### -- 多进程拷贝





process_copy.c



![image-20230214105510305](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105510305.png)

![image-20230214105532928](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105532928.png)

![image-20230214105548021](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105548021.png)

![image-20230214105640450](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105640450.png)

![image-20230214105710507](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105710507.png)





copy.c

![image-20230214105746075](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105746075.png)

![image-20230214105808077](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105808077.png)

![image-20230214105819969](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230214105819969.png)



![image-20230217101326226](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230217101326226.png)







## IPC进程间通信



**基本概念**：多进程开发时，需要在多进程间传递消息或共享数据，可以采用进程间通信技术实现。

![image-20230217101905257](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230217101905257.png)





### **匿名管道**



**管道特性**：

1. 流通性（数据）
2. 方向性（数据传输方向）
3. 可以暂存数据（不能持久化存储）





**管道的创建与使用**：

```c
int pipe(int dfs[2]);
//调用该函数在内核层创建一个匿名管道，管道创建成功，传出两个描述符用于管道
dfs[0]=3;	//用于读缓冲区
dfs[1]=4;	//用于写缓冲区
```

![image-20230218092605440](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218092605440.png)



- 匿名管道在使用时要**确定通信方向**（父写子读或子写父读），进程**将无用的描述符关闭**。（负责读的进程要将写权限关闭close(fds[1])）
- **匿名管道只能解决亲缘进程间的通信**，如果多个无关联，无法使用匿名通道。
- 管道的创建一定要在**fork前**完成，**子进程只继承描述符**，访问使用管道。
- 当**没有描述符**指向管道时，系统就会**销毁释放**管道缓冲区；所以管道使用完毕时，要检查将所有描述符都close。
- 匿名管道的传输方式为**单工**。



![image-20230218094548742](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218094548742.png)

![image-20230218094431852](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218094431852.png)





**管道使用时的几种特殊情况：**

1. 管道写端未写数据（**管道为空**），读端读取管道，**读端阻塞**。
2. 管道读端未读数据，写端**写满管道**后，再次写，**写端阻塞**。
3. **写端关闭**，读端读完管道内剩余数据后，再次读读到0。
4. 管道**读端关闭**，写端尝试向管道写数据，系统向写端进程发送SIGPIPE，杀死写端进程。







### 命名管道



​		使用命名管道**先要创建管道文件**，创建时为管道文件命名。命名管道**没有通信限制**，任何进程都可以使用该管道相互通信。

```bash
#使用命令创建删除管道文件
mkfifo named
rm 管道文件 -rf
```

```c
//使用函数创建删除管道文件
mkfifo(const char* named,int flag);
unlink(named);
```

![image-20230218101258227](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218101258227.png)



- 管道文件**非常规文件**，**没有存储数据的能力**；向管道文件描述符写入数据都会**重定向**到**管道缓冲区**。
- 管道文件访问**必须凑齐两种权限**，否则只有一端以只读或只写的方式打开管道，**会阻塞（在open处阻塞）**，等待另一种权限，**没有进程数量限制**。

![image-20230218102409705](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218102409705.png)

![image-20230218102424220](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218102424220.png)





**命名管道使用时的特殊情况**：

1. 如果一个进程中有**多个读序列**（多个线程），**阻塞只对第一个读序列生效**，其他序列都会设置为非阻塞；避免无意义的等待开销。

![image-20230218104724643](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218104724643.png)

2. **命名管道的原子访问与非原子访问：**

   **原子访问**：系统会检查缓冲区余量，如果写入数据大于缓冲区余量，系统强制挂起写端；如果余量满足存储要求，则正常写入。

   > **优点：**可以把证数据完整。

   > **缺点**：传输效率比较低，系统开销比较大，系统频繁挂起唤醒写端，造成延迟传输，系统开销变大。

   **非原子访问**：不会对写端进行干预，只要缓冲区可以存储，哪怕时1字节，写端也可以写1字节。

   > **优点：**传输速度特别快。

   > 缺点：数据包可能分多次传输、拆分，读端需要对数据完整性进行验证，否则无法使用。



**判断原子非原子：**

- **原子访问**：写入数据量**小于**管道大小（4K）

- **非原子访问**：写入数据量**大于**管道大小（4K）

​		

![image-20230218105236167](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230218105236167.png)







### MMAP内存映射



- 使用MMAP映射机制，可让多个进程共享资源。



**功能：**

1. 进程间通信 
2. 进程共享资源
3.  大文件的映射处理
4. 网络实现数据零拷贝

![image-20230219095953248](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219095953248.png)

- 申请的映射内存时从库空间申请的



**映射方式：**

**私有映射（MAP_PRIVATE）**：将映射文件的内容拷贝到映射内存中，但是两个数据无关联。

**共享映射（MAP_SHARED）**：将映射文件的内容拷贝映射到内存中，但是在两份数据之间建立sync同步机制，对一端数据的修改立即同步给另一端，永远保持一致性。

```c
//头文件
#include<sys/mman.h>

//申请映射内存
//1.系统分配内存 2.映射文件大小 3.文件权限 4.映射方式 5.文件描述符 6.偏移量
//成功返回映射内存的地址，失败返回MAP_FAILED关键字
void* ptr=mmap(NULL,int size,PROT_READ|PROT_WRITE,MAP_SHARED,int fd,ssize_t offset);

//释放映射内存
munmap(void* ptr,int size);
```



- MMAP映射时，要检查文件打开权限，不允许映射权限大于打开权限，如果这么做一定会映射失败。

**测试mmap的共享映射，测试同步机制：**

![image-20230219102009497](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219102009497.png)



**测试两个进程的通信，交互数据：**

![image-20230219111326088](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219111326088.png)

![image-20230219111356286](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219111356286.png)





**处理大文件数据喜欢用映射**：

![image-20230219112556211](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219112556211.png)

- 采用映射机制读取数据，要节省一次拷贝开销，整个读取流程速度更快，开销更小。

![image-20230219112643478](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219112643478.png)



> MMAP申请的映射内存是否是连续的？
>
> 使用MMAP时内核通过SIGBUS信号杀死了进程，错误为总线错误，为什么？











## 进程间的关系



#### **亲缘关系：**

​		在linux操作系统或者unix，亲缘关系主要体现在**父子进程**上，子进程被父进程创建，子进程的代码任务继承于父进程，子进程结束后父进程负责回收。

- 操作系统中频繁看到亲缘进程

![image-20230219144318625](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219144318625.png)

- 父子进程具有强亲缘关系（创建、继承、回收）
- 多级继承关系（回收）



```bash
#查看进程间关系的终端命令
ps ajx
```

```c
#include<unistd.h>
//相关函数
pid_t getpid();				//获取自身进程pid
pid_t getppid();			//获取自身父进程的pid
pid_t getpgrp();			//获取自身进程组id
pid_t getsid(pid_t pid);	 //获取自身进程会话id
```

![image-20230219150220059](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230219150220059.png)





 

#### **进程组：**

- 进程组由一个组长进程和若干个组员进程构成，终端进程被创建就是一个进程组的组长进程。

- **组长进程**标识：**PID==PGID** 两个id相等，该进程为组长进程（组id系统唯一，不会出现多个相同的组id）。
- 进程组的生命周期：随组中的进程持续，与特定进程无关，直到**最后一个组中进程结束**、转移，组中无进程后，系统回收组资源，回收组id。
- 如果一个终端进程循环创建了多个子进程，**父进程为组长进程**，所有子进程也会被归纳到父进程同组

，成为组员进程。

- **进程组关系与亲缘关系没有必然联系，因为组成员可以随意转移。**

```c
//可以创建一个新的进程组，也可以把一个组中的进程转移到其他组
setpgid(pid_t pid,pid_t pgid);
```

**注意事项：**

1. 只有组员进程可以通过setgpid创建新进程组，组长进程无法创建（setgpid(2500,2500);）
2. 转移的要求：首先目标组必须存在，其次用户必须对目标组由访问权限。（setgpid(2500,3000);）

![image-20230220100306320](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220100306320.png)

- 父进程创建的子进程是跟父进程一个组的









#### **会话关系：**

一、会话由一个发起者和多个参与者构成。

​		会话**发起者**身份表示：**PID==GID==SID**

![](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220105601234.png)

- 会话发起者结束，会以组为单位杀死参与者；杀死的是子进程的一组，如果会话发起者是bash（终端），会杀死终端进程的一组（./app）



二、**脱离终端控制，这类进程不受终端影响，终端是否结束与他们无关。**

脱离终端的方法：

1. 将创建的子进程转移到其他组（不和./app在同一组，这样终端关闭，子进程还存在）

```
setpgid(getpid(),getpid());
```

2. 自行创建会话，脱离原有会话，成为会话发起者

```
void setsid();
```

- **只有组员进程可以创建会话**，因为setsid内部流程是**先创建组，再创建会话**；如果该进程已经是组长进程，那么组创建会失败。









#### 孤儿进程（orphan process）：



一、**孤儿进程的产生原因**：父进程**先于**子进程退出，子进程变为孤儿进程。

![image-20230220122139403](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220122139403.png)

- **托管进程**为用户启动进程，该进程结束，系统会登出用户。



二、**孤儿进程的危害**：具有弹性，取决于孤儿进程执行的任务，有些任务损失很小，有些任务可能持续消耗系统资源。

三、**孤儿进程的检测于处理**：

1. 提高父进程的容错能力，做好错误处理，父进程越安全，就不会引发孤儿。
2. 使用检测进程：

![image-20230220122528330](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220122528330.png)

- 某一刻检测到父进程退出，但是没有收到退出事件，表示父进程异常退出，可能产生孤儿进程，检测进程通过gid批量杀死孤儿进程。









#### 守护进程（daemon process）

​		在各个操作系统中，守护进程是特别常见的一类进程类型；无论是windows还是linux等系统，通常使用守护进程研发**系统后台进程**或**服务进程**。

- **在linux操作系统中，守护进程其实就是孤儿进程，人为创建服务于后台。**



一、**精灵进程（守护进程）服务于后台**

**前台进程**：绝大多数操作系统，前台进程永远只有一个；该进程会获取操作焦点，多个进程可以切换焦点使用，虽然同时可以由多个程序启动执行，但是可以使用操作的只有一个。

**后台进程**：工作于后台，大多数后台进程都属于系统服务器进程或者特定软件后台服务程序。



二**、精灵进程（守护进程）特征：**

1. 生命周期：守护进程生命周期较长，随操作系统持续，开机启动，关机关闭，持续工作于后台。

2. 工作模式：守护进程的任务和工作模式不允许占用大量系统资源。（间隔执行、条件出发、定时触发（特定时间））

3. 开机自动启动：

   > 使用shell脚本实现开机启动程序



三、精灵进程（守护进程）实现步骤：

1. 父进程创建子进程，父进程退出

2. 子进程创建新会话，脱离原有控制终端

3. 关闭无用的描述符（守护进程不影响和占用前台设备，不适用标准输入和标准输出

   STDIN_FILENO,STDOUT_FILENO）

4. 将进程默认工作目录移动到/目录

5. 修改守护进程umask权限掩码，改为0或2

6. 实现守护进程任务（定时触发，条件触发）

7. 守护进程执行完毕，进行退出处理

![image-20230220133039361](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220133039361.png)



> **实现后台守护进程，间隔执行，每间隔5s，向特定log文件写入系统时间**

```bash
sudo cp myshell /etc.init.d
#添加开机自启的命令
/etc/init.d sudo update-rc.d myshell start 99 2.
#删除开机自启命令
/etc/init.d sudo update-rc.d myshell remove
```

![image-20230220142711638](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220142711638.png)

![image-20230220142723458](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220142723458.png)

![image-20230220142739921](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220142739921.png)



> **shell脚本实现程序开机启动流程：**

![image-20230220142934924](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230220142934924.png)









# 信号 SIGNAL



一、**signal信号概念基本概述：**

​		信号是linux操作系统下进程的**消息机制**，通常系统可以**向进程发送信号，干预系统（杀死，挂起）。**

```bash
#查看系统下支持的所有信号
kill -l
#向特定的进程发送信号
kill -signo pid
```



二、**信号的分类：**

**unix经典信号：1-31**		经典信号软件开发使用

**自定义信号：34-64**		  底层研发，驱动层研发使用自定义信号

**隐藏信号：32 33**			  预留给NPTL线程库使用



**三、linux系统常见发送信号的几种方式**

1.  **终端组合按键触发信号**（终端组合按键产生的信号只对终端进程有效（./））

```
ctl+c (2:SIGINT)
ctl+z (20:SIGTSTP)
ctl+\ (3:SIGQUIT)
jobs命令：可以查看手动的作业，通过作业编号，可以唤醒到前台继续执行或唤醒到后台执行（fg 1/bg 1）
```

![image-20230221074847108](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221074847108.png)



2. **命令触发信号：**

```bash
kill -signo pid #向指定进程发送指定信号 kill -9 3000
kill -signo -pid #群发向一个特定的组发送信号 kill -9 -8000
```

-  如果要干预进程，例如发送信号杀死，必须要**具备足够的权限**，否则因权限不足而失败。



3. **函数发送信号：**

```c
#include<signal.h>
//向指定进程发送指定信号
int kill(pid_t pid,int signo);
//向调用进程（自己）发送一个指定信号 
int raise(int signo);
//向调用进程（自己）发送一个固定的SIGABRT信号
int abort(void);
```

![image-20230221081006123](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221081006123.png)



4. **硬件异常产生信号：**

（1） **非法访问内存**，linux系统中发现进程非法访问内存，例如只读内存进行写操作，那么系统杀死违规进程，抛出**“段错误异常”（SIGSEGV:11）**

- linux系统保护机制，进程只要违规访问硬件资源，发送信号杀死进程

（2） **CPU违规运算**，linux系统发现进程违规使用cpu运算，例如cpu不允许直接除0，系统杀死违规运算进程，抛出**“浮点数例外”（AIGFPE:8**）

（3） **调度异常**，内存越界等问题，linux系统向进程发送信号杀死进程，抛出**“总线错误”（SIGBUS:7）**

- 进程异常访问系统资源，产生违规操作，系统会分类发送特定信号。



5. **软条件触发信号**

（1） **定时器alarm(30)**，定时30s，定时到时（触发软条件），系统向定时进程发送**SIGALRM：14**，通知到时（SIGALRM**默认杀死进程**）。

```c
#include<unistd.h>
unsigned int alarm(unsigned int seconds);
```

![image-20230221084049337](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221084049337.png)

（2） **管道读端关闭，写端尝试向管道写数据**，内核发送**SIGPIPE**信号杀死写端进程。





四、**信号的三大行为和五种动作：**

信号的行为选择，动作选择，处置进程

![image-20230221103845610](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221103845610.png)





五、**信号的传递过程：**’

![image-20230221103933347](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221103933347.png)





六、**让信号失效的方式**

1. **屏蔽方式：**用户自定义屏蔽字，设置屏蔽，最后用自己的屏蔽字替换进程原有屏蔽字，实现阻塞信号（暂时）。

```c
//信号集类型
sigset_t set;
//将一个信号集中所有位码初始化为0
sigemptyset(sigset_t* set);
//将一个信号集中所有的位码初始化为1
sigfillset(sigset_t* set);
//将某个一个信号集中特定的信号位设置1
sigaddset(sigset_t* set,int signo);
//将某个一个信号集中特定的信号位设置0
sigdelset(sigset_t* set,int signo);
//帮助用户查看信号集中某个信号的位码是0还是1，直接返回
int bit=sigismember(sigset_t* set,int signo);
//设置替换进程屏蔽字
sigprocmask(SIG_SETMASK,sigset_t* new_set,sigset_t* old_set);
```

![image-20230221163047347](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221163047347.png)



- **通过查看未决信号集，获取进程信号屏蔽情况：**

```c
//该函数执行成功，会传出当前进程的未决信号集
sigpending(sigset_t pset);
//循环遍历未决信号集，结合sigismember函数，就能打印查看未决集合了
```

![image-20230221163937706](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221163937706.png)



- **高权级信号：**

```bash
SIGNAL(9)		#只要发出必杀死目标进程，无法忽略，屏蔽，捕捉
SIGSTOP（19）	   #只要发出必然挂起目标进程，无法忽略，屏蔽，捕捉
```



- **相同信号传递：**

​		为了避免多个相同信号同时抵达产生冲突，系统同一时刻**只允许一个信号抵达**，其他信号会被**临时屏蔽**（屏蔽一个，由系统设置和翻转），等第一个信号处理完毕，会让等待的信号抵达。（unix经典信号，最大可以排队一个）





2. **信号行为修改**，**信号的忽略和捕捉**

**信号忽略**：

​		开发者定义**信号行为结构体**，然后通过提供的**API函数接口**，修改进程中信号的原有行为，将默认行为改为捕捉或忽略。

```c
//信号行为结构体
struct sigaction act;
//信号行为
act.sa_handler=SIG_DFL,SIG_IGN,捕捉函数地址
//该参数于信号函数接口绑定，如果使用sa_handler接口，那么flag就是0
act.sa_flags=0;
//临时屏蔽字
act.sa_mask;
//信号行为替换，对某个信号设置新行为，可以传出原有行为
sigaction(int singo,struct aigaction*new_act,struct sigaction*old_set);
```

![image-20230221170847513](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221170847513.png)



**信号捕捉**：

![image-20230221171725969](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221171725969.png)

![image-20230221172323100](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221172323100.png)

 

3. **三种信号失效方式的差别：**

信号屏蔽：这种方式为临时屏蔽信号，信号被卡在两个信号集之间，没有丢弃。

信号忽略：这种方式已经处理了信号，只不过没有处理动作，信号已经处理完消失了。

信号捕捉：这种方式处理信号，执行自定义行为，信号处理完消失。





七、**信号递达处理及捕捉函数调用**：

- **信号的处理是延时处理**

![image-20230221175145496](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221175145496.png)

- 内核执行捕捉函数**使用进程资源，消耗进程本身时间片。**

- **主函数和捕捉函数不会同时执行**。

![image-20230221175248897](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221175248897.png)

- 通常情况下，主函数先执行，执行过程中产生信号，主函数因各种原因暂停切换到内核层，内核执行捕捉函数，捕捉函数执行完毕，切换到主函数继续运行。
- 如果**主函数调用阻塞方法**，在阻塞等待结果，这时**产生信号**，内核执行信号捕捉，会将主函数的**阻塞强制中断**，阻塞方法报错返回，错误原因为**EINTER。**





八、**自定义信号（34-64）与经典信号（1-31）**：

​		**经典信号不支持排队（排队一次）**：经典信号用于处置进程，一个信号就可以达成目的，无需排队。

​		**自定义信号支持排队**：无论用户触发多少次相同信号，都可以排队处理，内部实现了排队序列。

![image-20230221181027263](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221181027263.png)





九、**可重入与不可重入概念**：

​		**不可重入函数**：函数参数有**全局参数或静态参数**，如果信号开发使用这类不可重入函数，那么会产生资源访问冲突。

​		**可重入函数**：这类函数的参数都是**局部资源**，即使信号开发使用，也不会由冲突和影响。

![image-20230221181208928](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221181208928.png)

- **全局资源被主函数和捕捉函数共享访问，必然产生冲突。**
- 在信号开发环境下，**尽量使用可重入版本函数**，避免使用不可重入版本，避免冲突。
- **很多函数具备_r版本，该版本为可重入版。**

```bash
man 7 signal #可查看可用的可重入函数
```





十、**利用signal信号技术，实现进程间通信**：

![image-20230221222123666](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221222123666.png)

发送端进程：

```c
union sigval val;
val.sival_int=1234;
//发送信号的同时传递消息
sigqueue(pid_t pid,int signo,union sigval val);
//可用信号：SIGUSR1(10) SIGUSR2(12)
//为提供给开发者使用的信号，这两个信号的默认行为与动作是杀死进程。
```

接收段进程：

```c
//采用捕捉方式让信号失效（不能杀死接收进程）
struct sigaction act,oact;
act.sa_sigaction=sig_fun;
act.sa_flags=SA_SIGINFO;
sigemptyset(&act.sa_mask);
sigaction(SIGUSR1,&act,&oact);
//捕获函数
void sig_fun(int n,siginfo_t* info,void* arg){
	printf("%d",info->si_int);
}
//void (*sa_sigaction)(int,siginfo*,void*)
//info->si_int=接收整型数据
//info->si_ptr=接收地址数据
```

- 信号通信有个限制，**就是pid的获取**，如果不清楚接收者的进程pid就无法发送信号，而父子进程可以轻易的获取对方pid。

![image-20230221224557761](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221224557761.png)



> **父子进程交叉报数**

![image-20230221231312805](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230221231312805.png)









# 线程 Pthread



## 线程基础



一、**线程**

​		**线程**是操作系统的调度与执行单位，它更轻量，体积与开销更小，相比多进程而言很多开发者青睐线程。

​		线程寄存于进程中，与进程共享内存资源。

- **进程是最小的分配资源单位，线程是最小的调度单位。**

![image-20230222132159398](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230222132159398.png)



二、**线程调度**

![image-20230222132250360](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230222132250360.png)

- 进程创建后自带的调度单元为主控线程，而后主控线程可以创建普通线程。

**用户级线程**：

> 1. **用户级线程无法被内核识别**，不会按用户级线程的数量分配时间片
>
> 2. 用户级线程在**用户层实现与使用**，无需内核干预，线程调度切换用户态完成，在某些情况下**开销更小**，效率更高。

**内核级线程：**

> 1. **内核级线程系统可识别，会为每个线程创建一个内核对象**，该线程**可以被分配时间片资源**，使用cpu完成任务可以得到更多的系统资源，可以更好地完成任务。
> 2. 内核级线程使用与调度，系统内核全程参与，频繁出现层级转换，终端等等系统开销。





三、**进程可以蜕化为线程**

1. 如果进程内部资源独占，使用访问所有资源，称为**进程资源**。
2. 在进程内部创建了很多新线程（普通线程），**普通线程分享了进程资源**，这时进程蜕化为了主控线程。

- **多线程模型开销小**





四、**资源共享**

多线程开发中，进程的那些资源时共享的？

**共享资源**：

1. 全局资源共享（全局变量）
2. 文件描述符表共享
3. 信号行为共享，一个线程修改了信号行为，例如捕捉行为，其他所有线程也都同步为捕捉行为。
4. 共享堆，空间共享
5. 多线程进程信息共享，PCB,pid,pgid,sid,uid工作路径等

**非共享资源**：

1. 线程栈非共享，每个线程拥有独立栈地址（虚拟地址=8M）
2. 每个线程拥有独立的调度优先级，通过修改优先级可以使线程获取更多的系统资源
3. 线程tcb非共享，每个线程通过tcb记录线程信息
4. ERRNO全局变量非共享

![image-20230222133502591](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230222133502591.png)

- 系统对ERROENO进行了使用优化，如果使多线程使用ERRNO，那么ERRNO是局部的。
- 多线程开发无需使用ERRNO全局变量，线程有自己的错误处理方式，不适用perror函数。

5. 线程也需要保存和恢复处理器现场，多以保存现场的内核栈是非共享的。







## 线程开发API



- NPTL（nativ posix thread library） 内核级线程库 2.23



### 线程创建回收等





一、**pthread_create**:

```c
#include<pthread.h>
pthread_t tid;		//线程tid类型
int err=pthread_create(pthread_t* tid,NULL,void*(*thread_job)(void* ),void*arg);
//tid 线程创建成功传出线程tid
//NULL 线程属性，如果让线程使用默认属性传NULL即可
//thread_job 线程任务地址，线程被系统创建后，默认执行的工作
//arg 线程工作参数
//返回值：成功返回0，失败直接返回错误号；可以使用strerror函数，结合错误号err，获取错误原因
```

![image-20230225095607170](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225095607170.png)

```bash
#查看系统中所有线程
ps -eLf
#查看特定进程的所有线程
ps -Lf
#线程查看时，LWP表示线程编号，主线程与普通线程区分：主线程的PID==LWP
```

![image-20230225103850450](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225103850450.png)

![image-20230225103911537](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225103911537.png)



**验证错误**：

![image-20230225105418458](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225105418458.png)



**线程数量问题：**

![image-20230225110416182](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225110416182.png)



二、**pthread_self**:

```c
//返回调用进程的线程tid
pthread_t tid=pthread_self();
//主函数创建后传出的tid，只存储到了变量中，无法确定此线程是否存活，但是线程内部通过self()获取并打印的tid,可以保证tid指向的线程还存活有效。
```

![image-20230225110903678](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225110903678.png)



三、**pthread_join**:

```c
//线程回收函数，可以回收指定的线程，并且获取该线程的返回值或者退出码
pthread_join(pthread_t tid,void** real);
//一直阻塞等待线程退出后进行回收
```

![image-20230225150806042](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225150806042.png)



四、**pthread_cancel**:

```c
//线程取消，可以结束取消特定线程
pthread_cancel(pthread_t tid);
//被取消的线程只有在进程系统调用时才会检测取消事件，如果没有系统调用发生，无法检测事件，无法结束。

//调用该函数后，触发一次系统调用事件
void pthread_testcancel(void);

//二者配套使用
```

![image-20230225152905510](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225152905510.png)

- 无论是线程创建（create）还是线程取消（cancel）还是线程回收（join），主线程都可以使用，**普通线程一样可以使用**，没有使用限制（普通线程也可以创建取消回收线程，甚至回收主线程）。



五、**pthread_exit**: 

```c
//线程退出，无论主线程还是普通线程都可以用它退出，也不会影响整个进程
pthread_exit(void* arg);
```

![image-20230225154259257](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225154259257.png)





**线程的几种退出方式：**

1. **return**：

​	主控线程执行：进程退出，杀死所有线程

​	普通线程执行：当前线程退出，与进程无关

2. **pthread_exit**：

​	主控线程执行：当前线程退出，与进程无关

​	普通线程执行：当前线程退出，与进程无关

3. **exit**：

​	主控线程执行：进程退出，杀死所有线程

​	普通线程执行：进程退出，杀死所有线程

4. **pthread_cancel**：

   向其他线程发送取消事件，结束目标线程





六、**pthread_detach**:

```c
//设置分离线程
pthread_detach(pthread_t tid);
```



- 线程的两种状态：PTHREAD_JOINABLE（回收态）

  ​								PTHREAD_DETACHED（分离态）

- **线程只允许有一种退出状态，两种状态互斥**



**回收态线程**：这类线程结束，需要用户自行回收（pthread_join），否则产生内存泄漏，一个线程被创建后，默认为回收线程。

**分离态线程**：这类线程结束后系统自行回收线程资源，无需用户干预，分离态线程无法获取线程的退出值。

> **线程从回收态切换为分离态，此操作不可逆转，无法将分离态线程再变回回收态。**



**状态互斥**：

1. 如果对一个分离态线程，进行回收操作（pthread_join），那么回收操作会失败。
2. 如果对一个已经处于回收阶段的线程（join函数已经阻塞等待线程退出）进行分离设置（pthread_detach），分离设置会失效。

![image-20230225162223136](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225162223136.png)



**测试分离回收互斥：**

![image-20230225164732096](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230225164732096.png)





### **线程属性**



一、**属性**

![image-20230226195415488](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230226195415488.png)



二、**使用属性的流程**

1. 定义线程属性类型 

```c
pthread_attr_t myattr;
```

2. 初始化线程属性 

```c
//使用此函数初始化的属性结构体，为默认属性结构体
pthread_attr_init(pthread_attr_t*);
```

3. 根据需求修改属性中的成员，例如修改防溢缓冲区大小，修改线程退出状态，修改线程栈大小。

```c
//获取设置属性中的线程退出状态
//获取属性中的退出状态并传出
pthread_attr_getdetachstate(pthread_attr_t*,int* detachstate);
//PTHREAD_CREATE_JOINABLE 回收态关键字
//PTHREAD_CREATE_DETACHED 分离态关键字
//修改属性中的退出状态
pthread_attr_setdetachstate(pthread_attr_t*,int detachstate);

//获取设置属性中的线程栈
//获取属性中的栈大小和栈地址，传出
pthread_attr_getstack(pthread_attr_t*,void** stackaddr,size_t* stacksize);
//向属性中设置栈地址和栈大小
pthread_attr_setstack(pthread_attr_t*,void stackaddr,size_t stacksize);
```

4. 创建线程时一定要使用自定义属性，否则属性修改设置没有任何意义。
5. 线程属性使用完毕后，销毁属性释放内存

```c
pthread_attr_destroy(pthread_attr_t*);
```

- **部分线程库函数，即使不编译时不连接库（-lpthread）也可以成功编译，但是函数时不能用的，功能异常。**
- 64**位系统无法通过修改线程栈大小修改线程数量，因为系统有硬限制。但是32位可以测试出来。**

![image-20230226201529609](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230226201529609.png)

![image-20230226202453055](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230226202453055.png)



![image-20230226204353105](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230226204353105.png)







### 线程安全



**一、访问冲突**：

​		多线程并发执行时，因使用共享资源不当，导致的共享资源访问冲突（数据异常）

![image-20230226205629030](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230226205629030.png)

- 多线程访问数据库，多线程访问文件，多线程访问共享数据结构（队列，栈，树），都要注意全局资源访问冲突。
- 单例模式双检锁，避免冲突（线程安全问题）



**测试访问冲突**：

![image-20230226210527118](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230226210527118.png)







二、**互斥锁（pthread_mutex_t）**

![image-20230227133403640](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227133403640.png)

- 上面的案例，**需要使用一把互斥锁**，用于保护number资源，两个线程交替使用
- 使用锁技术实现对全局资源的互斥访问，**一个一个交替使用**，避免同时访问引发异常。

```c
pthread_mutex_t lock;
//互斥锁初始化函数，第二个参数传NULL，表示默认属性
pthread_mutex_init(pthread_mutex_t* lock,pthread_mutexattr_t* attr);
//销毁互斥锁
pthread_mutex_destroy(pthread_mutex_t* lock);
//上锁请求，如果锁被占用则挂起，阻塞上锁
pthread_mutex_lock(pthread_mutex_t* lock);
//解锁
pthread_mutex_unlock(pthread_mutex_t* lock);
```

- **上锁位置，要求开发者在读写访问全局资源时加锁。**

![image-20230227201215913](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227201215913.png)

​		**早期会发生争抢锁效应**：惊群效应（唤醒大量的等待线程，但是锁资源有限，只有一个线程可以使用锁，其他线程依然要被挂起，哪意味着除了抢到资源的线程是由意义的，没有抢到的所有线程唤醒和挂起操作都是没有意义的系统开销）。

​		**现在**：

![image-20230227200210706](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227200210706.png)







三、**读写锁（pthread_rwlock_t）**

- **读共享，写独占，读写互斥**
- **设计初衷：**为了让多个线程能同时读访问全局资源，提高全局资源的使用率。
- **读锁**有多把，每个线程都可以申请读锁，读访问全局资源。
- **写锁**只有一把，写锁与互斥锁类似；只有占用写锁的线程才可以写全局资源，其他申请写锁的线程会被系统挂起等待。
- **读锁线程在读取数据时，不允许写锁线程修改数据；同样，写锁线程在修改数据时，也不允许读锁线程读取数据。**
- **读取数据不允许修改，保证读取数据的准确性。**
- **申请读锁也会阻塞**，一般为系统读锁耗尽。

```c
//读写锁类型
pthread_rwlock_t rwlock;
//初始化读写锁
pthread_rwlock_init(pthread_rwlock_t* lock,NULL);
//销毁释放读写锁
pthread_rwlock_destroy(pthread_rwlock_t* lock);
//申请读锁
pthread_rwlock_rdlock(pthread_rwlock_t* lock);
//申请写锁
pthread_rwlock_wrlock(pthread_rwlock_t* lock);
//解锁，读写锁都可解
pthread_rwlock_unlock(pthread_rwlock_t* lock);
```



**实例：3个写线程使用写锁，互斥修改全局资源；5个读线程使用读锁，共享读取全局资源。循环持续运行。**

![image-20230227203307942](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227203307942.png)









四、**进程互斥锁（pthread_mutex_t）**

- **默认情况下使用互斥锁都为线程互斥锁**，但是可以通过**修改互斥锁属性**的方式，将线程互斥**改为进程间互斥**。
- 如果多进程间有共享数据或资源，多进程并发同时访问该资源，一样会出现共享资源访问冲突，可以采用进程互斥锁，避免此问题。



**进程锁的创建方式**：

1. 定义互斥锁变量（pthread_mutex_t）
2. 定义互斥锁属性（pthread_mutexattr_t）
3. 初始化互斥锁属性（初始化后锁属性都是线程互斥锁）
4. 修改锁属性，将线程互斥改为进程互斥
5. 初始化互斥锁，使用自定义的锁属性初始化（进程锁）
6. 多进程使用进程锁，互斥访问共享资源

```c
//互斥锁属性类型
pthread_mutexattr_t attr;
//互斥锁属性初始化函数
pthread_mutexattr_init(pthread_mutexattr_t*);
//销毁互斥锁属性
pthread_mutexattr_destroy(pthread_mutexattr_t*);
//修改属性，可以将线程互斥改为进程互斥
pthred_mutexattr_setpshared(pthread_mutexattr_t*,PTHREAD_PROCESS_SHARED);
//PTHREAD_PROCESS_SHARED 进程互斥关键字
//PTHREAD_PROCESS_PRIVATE 线程互斥关键字
```

![image-20230227204931742](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227204931742.png)



**进程互斥锁使用：**

![image-20230227210615858](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227210615858.png)

![image-20230227210654531](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227210654531.png)









五、**文件读写锁（flock）**

![image-20230227213441543](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227213441543.png)

![image-20230227214521585](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227214521585.png)









六、**死锁问题**

**产生原因**：某一个线程在占用自身锁资源的前提下还去申请其他线程占用的资源，如果对方线程也是这个请求流程，那么两个线程会产生永久等待，都在等待对方资源。

**危害：**两个线程都在等待对方的锁资源，但是无法获取，产生永久挂起，线程任务无法推进执行。

![image-20230227220503086](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230227220503086.png)

- 多线程资源有限的情况下，相互请求锁资源，容易产生死锁。
- 产生死锁后，不可逆，只能杀死一个死锁线程，接触死锁。



**死锁产生的四个必要条件**：

1. **请求与保持条件**：线程占用了一个锁资源，还要请求其他锁资源
2. **互斥等待**：锁资源无法被两个共有，一个线程占用后，其他线程申请则会挂起
3. **非剥夺条件**：某个线程占用了锁资源后，其他线程采用任何形式也无法抢夺资源，必须占用者自己释放
4. **循环等待条件**：多线程并发模型，线程间会出现资源循环等待环路，每个线程都在等待相邻线程的资源

**预防**：非阻塞请求锁资源









### 线程控制和调度（信号量，条件变量）



![image-20230301202721965](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230301202721965.png)

- 多线程开发模型中，对线程的执行顺序和流程有要求，需要使用条件变量进行控制和调度。
- 根据执行条件的数量，决定条件变量数量，与线程数量无关。
- 线程A执行条件：BUFFERA为空则读取一行数据，否则挂起等待
- 线程B执行条件：BUFFERA为空则挂起等待，否则检测数据
- 线程C执行条件：BUFFERC为空则挂起等待，否则将C数据写道result文件中

**条件变量**：通过拟定的执行条件，可以控制线程的挂起和唤醒，如果该线程工作条件满足，则唤醒执行，不满足则挂起等待。



**DEMO**：

​		两个线程（安保人员），每个安保，按天气决定是否巡逻或休息，如果天气信息为0，白班的安保巡逻，夜班的安保休息；反之亦然。安保巡逻结束修改天气信息，唤醒另一个安保。

- 条件变量数量是连个，锁的数量是一个

```c
//条件变量类型，线程可以挂起在条件变量上，也可以唤醒挂起在某个条件变量上的线程
pthread_cond_t cd;
//条件变量初始化函数
pthread_cond_init(&cd,NULL);
//销毁释放条件变量
pthread_cond_destroy(&cd);
//将自身线程挂起在特定条件变量上
pthread_cond_wait(&cd,pthread_mutex_t* lock);
//唤醒一个挂起线程
pthread_cond_signal(pthread_cond_t* cd);
//唤醒所有线程
pthread_cond_broadcast(pthread_cond_t* cd);

//wait函数还负责上锁和解锁
//第一次执行，挂起并解锁
//其他线程唤醒挂起时，该线程还要第二次执行cond_wait，进行一次上锁操作。
```

![image-20230301203909818](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230301203909818.png)

![image-20230302164105915](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230302164105915.png)

![image-20230302164128125](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230302164128125.png)









# SOCKET套接字



- 套接字用于开发网络应用，系统提供的一系列API函数接口

![image-20230302160512289](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230302160512289.png)



一、**SOCKET创建（TCP UDP）**

```c
//头文件
#include<sys/socket.h>
#include<arpa/inet.h>//用于各种转换

int sockfd=socket(AF_INET,SOCK_STREAM,0);
//arg[1]=表示协议族，AF_INET（ipv4=32） AF_INET6(ipv6=128)
//arg[2]=选择传输协议，SOCK_STREAM(tcp) SOCK_DGRAM(udp)
//arg[3]=选择协议模型，如果传0表示默认协议
//RETURN=成功返回sockfd(>0),失败返回-1，并且系统设置errno,用于错误处理
```





二、**BIND用于绑定设置socket中网络信息（TCP UDP）**

```c
//网络信息结构体
struct sockaddr_in myaddr;
myaddr.sin_family=AF_INET|AF_INET6;
myaddr.sin_port=htons(8080);
myaddr.sin_addr.s_addr=htonl(INADDR_ANY);//本机任意关键字
```

> - 因大小端存储差异，本地数据要存储到网络设备中必须通过一系列函数进行数据转换，不能直接复制。

- **常用的大小端置换函数：htons() htonl() ntohs() ntohl()** 

N:网络序（大端），H：主机序（小端），S：端口 ，L：IP

- **字符串IP转大端序IP：**

```c
ip="43.125.7.116";
//将字符串IP地址转后为大端后，直接存储到网络信息结构体中
inet_pton(AF_INET,ip,&myaddr.sin_addr.s_addr);
```

- **大端序IP转字符串IP：**

```c
char ip[16];
//将大端IP转成字符串后传出到自定义数组保存
inet_ntop(AF_INET,&myaddr.sin_addr.s_addr,ip,sizeof(ip));
```

- **绑定BIND：**

```c
int reval=bind(int sockfd,struct sockaddr* addr,sizeof(addr));
//arg[1]=要设置的socket描述符
//arg[2]=要设置进socket的网络信息（ip,port）
//arg[3]=网络信息结构体大小
//return=成功返回0，失败返回-1，并且设置errno,用于错误处理
```

> - 使用bind固定socket中的ip信息和端口信息，便于其他人查找
> - 考虑到向前兼容的问题，参数为旧版网络信息结构体（sockaddr），开发者如果要传新版（sockaddr_in），则强制类型转换。





三、**LISTEN网络事件（连接）监听（TCP）**

```
int reval=listen(int sockfd,int backlog);
```

![image-20230302162228613](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230302162228613.png)







四、**CONNECT请求TCP连接函数（主动端）（TCP）**

```c
//客户端掉用该函数向服务器发起tcp连接请求
int reval=connect(int mysock,struct sockaddr* addr,socklen_t* addrlen);
//return=成功返回0，失败返回-1，并且系统设置errno,用于错误处理
```







五、**ACCEPT等待tcp连接请求，并完成连接（被动端）（TCP）**

```c
int reval=accept(int server_fd,struct sockaddr* clientaddr,socklen_t* addrlen);
//arg[1]=包含自身网络信息的socket
//arg[2]=连接成功，传出保存客户端的网络信息（ip,port）
//arg[3]=传入可以接收的网络信息大小，传出实际大小
socklen_t addrlen=sizeof(struct sockaddr);
//return=成功返回请求端的socket，失败返回-1，并且系统设置errno,用于错误处理
```

- accept为阻塞等待连接，每次只连接一个客户端，如果要多次连接，要执行多次该函数
- cs框架，服务器中，服务器socket永远只有一个，客户端的socket有多个（server_fd用于连接，client_fd用于与客户端交互数据）





六、**数据交互相关的函数：**

TCP:recv(),send(),read(),write()

UDP:recvfrom(),sendto()

**客户端：**

![image-20230302201206787](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230302201206787.png)

**服务端：**

![image-20230304101914790](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304101914790.png)







# 服务器





## 基础



**服务器基本概述：**

​		服务器时典型的后台服务器软件，可以为客户端提供数据和业务支持，服务器可以帮助用户缓存数据（个人信息，账号信息，用户使用数据和配置都可以在云端存储。

![image-20230304091913692](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304091913692.png)



**服务器基本能力：**

1. 网络穿透（建立中转枢纽，让若干客户端相互关联）
2. 数据中转，多端之间转发数据及消息
3. 持久化能力，可以为用户提供云端存储
4. 安全性（Dos检测，防火墙设置，安全隔离，数据安全传输）
5. 并发数量和并发处理能力（服务器性能指标）
6. 服务器性能测试（TPS，QPS，吞吐量，压力测试，负载测试，并发数，平均响应时间
7. 负载均衡概念（分布式架构）
8. HA高可用性设计



**服务器操作系统：**

WINDOWS SERVER

Windows Net Server

CentOS

Ununtu

- 服务器系统种类繁多，但是市场占用率最高的依然是Unix，Linux系统



**服务器软件：**

Apache：目前世界范围内，市场占用率最高的Web服务器，完全开源免费（在意稳定性，多进程模型较为突出）

Nginx：俄罗斯的轻量级Web服务器，完全是采用c语言开发实现



**服务器种类：**

处理服务器（处理业务，完成请求反馈响应）

存储服务器（数据库服务器，文件服务器）

代理服务器







**网络穿透概念：**

![image-20230304092724282](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304092724282.png)





**DNS域名解析器：**

![image-20230304092741304](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304092741304.png)



**分布式概念**：

**集群**：对设备进行横向扩展，让多台设备共享资源，提高服务器的处理能力和并发能力。

![image-20230304092810048](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304092810048.png)

- 分布式架构具备较强抗压性，灾害转移能力





**服务器处理种类：**

1. 高并发高活跃

> 用户基数较大（在线人数），客户端与服务端同步数据交互频繁
>
> 看重吞吐量，数据交互处理能力，并发数量可以略少

2. 高并发低活跃

> 用户基数大，并发数高（在线人数），但是与服务器交互不频繁
>
> 看重并发数量，处理能力可以稍弱







**APUE服务器模型：**

1. **单进程模型**

![image-20230304093314118](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304093314118.png)

> 测试业务：

> 客户端向服务端发送小写数据，服务端处理响应大写数据 send="abcd"	recv="ABCD"

> 客户端向服务端发送关键字，send="timeofday"	recv="网络时间"

- **客户端：**

![image-20230304104407916](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304104407916.png)

- **服务端：**

![image-20230304104456258](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304104456258.png)

![image-20230304104534435](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230304104534435.png)









## 多线程 多进程



一、

- 如果客户端退出，服务器读取（recv）客户端socket时返回0，相当于读到文件末尾。

![image-20230305150526774](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305150526774.png)

**优点：**

​		拥有较强的稳定性，某个节点（进程）崩溃不会影响其他节点

**缺点：**

1. 子进程与客户端高度绑定，这意味着如果客户端连接断开频繁，服务器会频繁创建销毁子进程，系统开销较大，资源浪费。
2. 并发数量取决于进程数量，如果系统可创建的进程较少，那表示服务器并发数受进程数量限制。
3. 进程模型本身就有较大的内存开销





二、

**多进程通信：**

![image-20230305153606263](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305153606263.png)

**使用线程回收僵尸进程：**

- 判断进程客户端是否退出

![image-20230305161224330](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305161224330.png)

- 主线程创建屏蔽并创建线程

![image-20230305161255792](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305161255792.png)

- 捕捉函数和线程函数

![image-20230305161318801](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305161318801.png)







三、

**多线程通信：**xxx









## 多路IO复用基数（多路IO转接基数）





一、

- 多路IO复用基数：可以为进程监听若干个网络IO（socket）的网络事件

**讨论单进程模型的阻塞冲突（accept recv）**

![image-20230305163047421](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305163047421.png)



> 多路io复用技术可以帮助用户同时监听若干个socket上的网络事件

![image-20230305163202294](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305163202294.png)

> select完成socket事件监听，产生就绪后，执行accept或recv处理事件

![image-20230305163253497](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305163253497.png)

- 同步异步？？？？？？





### select



一、

**select执行过程：**（select最大监听数量为1024）

![image-20230305163736497](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305163736497.png)

```c
//头文件
#include<sys/select.h>
//监听集合
fd_set set;
//集合初始化函数，将所有位码初始化为0
FD_ZERO(fd_set* set);
//对监听集合中某一个sockfd的位码设置为1
FD_SET(int sockfd,fd_set* set);
//对监听集合中某一个sockfd的位码设置为0
FD_CLR(int sockfd,fd_set* set);
//传出返回某个监听集合中特定sockfd的位码，返回0或1
int bit_code=FD_ISSET(int sockfd,fd_set* set);

int readycode=select(int num,fd_set* rdset,fd_set* wrset,fd_set* errset,struct timeval* timeout);
//num 监听数量，应该如何传参，传当前进程最大的文件描述符+1，(maxfd+1)一定要即使更新maxfd
//rdset,wrset,errset是选择设置监听事件的参数，如果监听某种特定c事件就在参数上传监听集合地址，如果不见听则传空
//timeout 选择select监听模式，阻塞、非阻塞或定时阻塞
```

![image-20230305164341127](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230305164341127.png)

![image-20230307210551375](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230307210551375.png)

![image-20230307210629461](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230307210629461.png)

![image-20230307210649926](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230307210649926.png)

![image-20230307210719066](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230307210719066.png)

- select模型拥有较大的监听能力，但是单进程模型处理能力很弱，虽然可以实现简单的一对多效果，但是实际投入使用，用户和会等待处理。







二、

**select利弊：**

**优点：**

1. 跨平台能力比较好，多个系统和语言都有对select的支持和实现
2. 服务器单进程即可实现简单的一对多效果，实现较为简繁
3. 局域网应用如果需要监听socket，可以选择select
4. 监听模型，定时阻塞监听如果对事件精度要求较高（微妙），可以选择select

**缺点：**

1. select最大的网络IO监听数量为1024，较少，如果并发数量较多，无法使用
2. 轮询问题，随着轮询数量的增长IO处理性能呈线性下降（服务器吞吐量受波及）

> 因为大量的轮询会影响读写性能，所以select轮询数量限制为1024

3. select没有将传入传出分离，使用者要自行分离

4. select监听到就绪后，指挥返回就绪的数量（readycode），但是没有妇女会哪个sockfd就绪，使用者需要自行遍历判断就绪的sockfd，然后处理

5. select监听事件设置问题，首先可监听的网络事件比较少（读、写、异常），其次不够灵活，不能让不同的sockfd监听不同的事件，因为是批处理
6. 随着select持续使用，会产生大量无意义的拷贝开销和挂载开销





三、

**select底层监听过程：**

![image-20230307212203956](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230307212203956.png)







### poll



一、 

**POLL模型**：POLL允许用户自定义长度结构体数组作为监听集合

```c
//头文件
#include<poll.h>
//监听集合
struct pollfd listen_array[1024];
struct pollfd node;
//node.fd=要监听的sockfd，存储socket表示监听，存储-1表示不监听
//node.events=POLLIN|POLLOUT|POLLERR;//传入要监听的事件
//node.revents=监听的sockfd就绪，则在revents传出就绪事件

//POLL监听函数
int readycode=poll(listen_array,1024,int timeout);
//listen_array=传监听数组（集合）首地址
//listen_max=监听最大值，一般传数组大小即可
//timeout=工作模式，-1（阻塞监听）0（非阻塞监听）>0（定时阻塞监听）默认毫秒定时，如果不支持毫秒向上取秒
```

- **为什么poll设置监听大小为4096会出现异常？**

> linux中socket也是**文件描述符**，那就意味着进程中能够使用多少个sockfd取决于描述符数量，默认情况一个进程**可以使用的最大描述符数量为1024**，我们使用POLL模型的时候，如果定义的监听数量大于描述符数量，poll函数报错立即返回，**可以通过修改配置文件的方式，将1024变大。**







二、

**POLL利弊：**

**优点：**

1. 服务器单进程即可实现简单的一对多效果，实现较为简单
2. poll可监听的事件更丰富而且更灵活，poll设置了两个成员变量events和revents，一个用于设置监听一个用于传出就绪，做到了传入传出分离
3. poll突破了1024的限制（没有解决轮询问题）

**缺点：**

1. poll的兼容性比较差，只有部分平台支持。

2. 轮询问题、反复挂载拷贝开销、遍历查询就绪；重点问题与select一样，并没有解决。

![image-20230308190944327](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308190944327.png)

![image-20230308191036190](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308191036190.png)

![image-20230308191104701](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308191104701.png)









### epoll



一、

epoll模型：EPOLL的监听集合是在内核层创建的红黑树，用户可以将要监听的sockfd和事件封装在一个监听节点中，挂载到监听树进行网络事件监听。

![image-20230308191404322](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308191404322.png)

```c
//创建监听树
int epfd=epoll_create(1024);

//监听节点
struct epoll_event node;
node.data.fd=sockfd;	//存储监听的socket
node.events=EPOLLIN|EPOLLOUT|EPOLLERR;	//监听事件

//对节点进行操作
epoll_ctl(int epfd,EPOLL_CTL_ADD,sockfd,&node);	//将节点添加进监听树
//EPOLL_CTL_ADD	添加节点
//EPOLL_CTL_DEL	删除节点
//EPOLL_CTL_MOD	修改节点

//就绪队列
struct epoll_event ready_array[1024];

//开始监听
int readycode=epoll_wait(int epfd,就绪队列地址，最大就绪数量，int timeout);
//监听树大小等于就绪队列长度等于最大就绪数
```

- epoll监听树中某些节点监听到事件就绪，epoll会**直接将这些就绪节点传出到用户层就绪队列中**，用户只需要遍历处理这些就绪的sockfd即可。





二、

**epoll的底层监听过程：**

- epoll是**线程安全**的，对监听树的操作都是会上锁，**无需用户上锁**

![image-20230308221631303](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308221631303.png)

**优点：**

- epoll的监听树直接在内核层创建，用户使用时需要将一个新节点拷贝到内核层，并挂载到监听树中即可，每个节点值拷贝一次并且只挂载一次，避免无意义的拷贝开销。
- epoll采用自定义实现的监听队列，没有使用系统监听设备，避免了轮询问题。
- epoll没有轮询问题，所以epoll可以监听设备上最大的socket数量。
- epoll监听到就绪后，会直接将就绪的socket传出到就绪队列中，便于用户处理就绪。
- epoll可以监听的socket网络事件更丰富，并且较为灵活，可以针对不同的socket设置不同的事件监听。



> **以上三种模型中，epoll的监听能力最出色**（处理能力与epoll无关，主要看服务器的并发处理（进程池、线程池等））

**缺点：**

- epoll监听集合采用红黑树，红黑树的效率问题，内存开销问题，各种限制也适用于epoll。

![image-20230309181206210](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230309181206210.png)

![image-20230309181335729](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230309181335729.png)

![image-20230309181308134](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230309181308134.png)





三、

**epoll高级内容：**

**epoll的两种工作模式**：EPOLLET|EPOLLLT

监听模式是当监听到socket就绪后的反应机制，这意味着监听模式的设置单位为socket



**水平触发模式（默认）：**如果使用epoll时不对监听模式进行额外设置，所有的socket监听模式默认为水平触发。

- **水平触发=责任模式=EPOLLT**

![image-20230308222539347](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308222539347.png)

![image-20230308222624313](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308222624313.png)

- 水平模式下的epoll，会持续检测用户读取情况，当用户将所有的数据读取完毕，这轮就绪才算处理完毕，否则只要缓冲区有数据，就持续向上层发送处理通知。
- 水平触发模式下，用户不讲就绪事件处理掉，不允许使用epoll_wait进行新一轮阻塞监听，如果调用则立即返回，返回值为未处理的事件数量。

**水平模式的利弊：**

利：可以保证事件处理及时，也可以保证数据包的读写完整

弊：此模式的开销比较大，因为内核要干预检测数据处理情况，而且水平模式监听效率较低





- 边缘触发=不负责任模式=EPOLLET

​		边缘模式下，监听到socket事件就绪，会向上层发送一次处理通知，但仅有一次。无论用户使用处理就绪数据与epoll无关，边缘触发模式的epoll随时可以进行新一轮事件监听，即使时上一轮的事件未处理，数据未读写也没关系。

**利弊：**

利：边缘模式监听，开销小，监听效率高。

弊：无法保证及时处理事件，无法保证数据读写完整（可能会漏处理）





**修改监听模式：**

```c
struct epoll_event node;
node.data.fd=serverfd;
node.events=EPOLLIN|EPOLLET;
```

![image-20230308223353930](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230308223353930.png)







### 修改文件描述符的数量



1. cat /proc/sys/fs/file-max #查看系统允许最大文件个数

2. ulimit -a #查看当前最大文件描述符（open ）

3. sudo vi /etc/security/limits.conf   #修改文件最大描述符

   #在文件内插入

   ```bash
   *	soft	nofile	65536	#软限制（最小）
   *	hard	nofile	65536	#硬限制（最大）
   #也可以用下面一行替代上面两行(65536为到该文件描述符个数)
   *	-	nofile	65536
   ```

4. 重启







## IO复用线程池模型（高并发低活跃）



![image-20230309183120412](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230309183120412.png)



### **线程池的设计与实现：**



**线程池简述：**线程池是一个线程容器，很多线程即存在线程池中，如果需要线程，随时可以在线程池中调用存活线程，线程池概念是在多线程的基础上加入了人阈值等概念，便于线程的使用和管理。



**传统多线程为业务驱动：**

![image-20230309183334595](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230309183334595.png)

- 任务驱动方式使用线程，任务抵达创建，执行完毕销毁，如果任务抵达频繁，任务比较简单，这意味着系统会有大量的创建销毁线程开销。
- 线程缺乏重用性
- 任务处理不及时，如果任务抵达再去创建线程，任务需要等待
- 缺乏线程管理，不清楚线程的上下限，只关心创建和使用



**线程池设计优势：**

1. 线程池会预创建一批线程待用，任务抵达，可以调用线程实时处理（避免任务等待）
2. 线程池线程有较好的重用性，每个线程都可以反复的处理任务
3. 提高了线程重用性，减少下黄健销毁开销
4. 线程池在意线程状态管理，通过阈值的方式记录线程状态和数量，便于管理线程
5. 线程池内部可以实现扩容缩减，任务量增大，创建线程处理任务，闲线程数量变大（缩减线程），减小开销
6. 线程池与业务分离，线程池中的线程无需关心业务实现，只负责执行业务即可

- 线程池数量一般=cpu*2=线程数量



**线程池模型：生产者消费者（条件变量+互斥锁+环形队列）**

![image-20230309183943198](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230309183943198.png)





二、

**线程池函数接口和类型**

```c
struct thread_poll_t ptr{
	线程池开关 0 or 1线程最大数
	线程最小数
	存活线程数
	繁忙线程数
	闲置线程数
	线程退出码
	
	任务队列首地址
	任务队列头索引
	任务队列尾索引
	任务队列最大值
	任务队列当前值
	
	互斥锁（队列锁）
	生产者条件变量
	消费者条件变量
	
	管理线程tid
	消费者线程tid数组
}

struct task_t{
	void* (*busines)(void*);
	void* arg;
}

//线程池创建初始化
thread_pool_t* thread_pool_create(int thread_max,int thread_min,int que_max);
//生产者添加一次任务
int thread_produce(thread_pool_t* ptr,task_t job);
//消费者线程工作
void* thread_customer(void* arg);
//管理者线程工作
void* thread_manager(void* arg);
//线程池资源释放
int thread_pool_destroy(thread_pool_t*);
//业务接口用户需要自行实现，消费者帮助执行
void* business(void*);
```









### **管理者实现问题：**

1. **关于coutumer_tids数组使用：**

![image-20230311163157614](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230311163157614.png)

- 如果某一位为0，可以直接使用，存储新线程id
- 如果某位不为0，要进行线程存活判断，如果该线程存活，此位不允许使用，如果该线程结束，覆盖使用这一位
- thread_if_alive(pthread_t tid)试探一个线程是否存活，函数返回0，表示该线程已经结束，如果返回1，表示还有效



2. **阈值如何获取和使用？**

- 线程池阈值属于多线程共享资源（互斥访问）

- 锁数量有限，如果管理者频繁占用互斥锁，影响生产者和消费者，降低任务执行效率



3. **扩容条件？**

- 当前任务数 >= 闲线程数量
- 计算占用比，忙线程在存活线程中占70%，创建一批线程备用
- 限制条件 = 当前存活数量 + 扩容数量 <= 线程池最大阈值



4. **缩减条件？**

* 闲线程是忙线程的2倍，占用比，闲线程在存活线程中占有一定比率则缩减
* 限制条件 = 当前存活数量 - 缩减数量 >= 线程池最小阈值



5. **如何缩减？**

PLANA：管理者完成缩减，判断缩减条件满足后，通过pthread_cancel取消结束一定数量线程

PLANB：管理者与消费者合作完成缩减

![image-20230311164353380](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230311164353380.png)

 [Makefile](相关文件\Makefile)  [POOL.h](相关文件\POOL.h)  [thread_customer.c](相关文件\thread_customer.c)  [thread_if_alive.c](相关文件\thread_if_alive.c)  [thread_manager.c](相关文件\thread_manager.c)  [thread_poll_create.c](相关文件\thread_poll_create.c)  [thread_poll_destroy.c](相关文件\thread_poll_destroy.c)  [thread_producer.c](相关文件\thread_producer.c)  [business.c](相关文件\business.c)  [main.c](相关文件\main.c) 







### epoll服务器模型问题



1. **关于业务的异常添加**，客户端只发送了一次请求（连接请求），但是服务端生产者添加了福多次业务到线程池任务队列（异常的业务数量会导致线程池扩容和缩减）

![image-20230314202937512](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230314202937512.png)

![image-20230314202947464](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230314202947464.png)



2. **epoll边缘触发模式监听结合非阻塞读写网络IO**

   边缘触发模式读IO，要保持将socket缓冲区数据读取完毕，那就需要循环读取，循环读取一定要采用非阻塞读取IO，避免读阻塞，线程与和护短绑定（影响并发数）

   ```c
   recv(MSG_DOTWAIT)
   ```

   

**3. 服务器模型（管道情况）**

管道读端关闭，写端向管道写数据，系统向写端发送SIGPIPE信号，杀死写端进程

服务端（写端），客户端（读端），服务端向客户端发送消息，但是客户端已经关闭退出，系统向服务端发送SIGPIPE信号，杀死服务端进程

```
send(MSG_NOSIIGNAL)
```



4. **关于多线程处理同一个sockfd的问题**

   ![image-20230314203629033](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230314203629033.png)



- 水平触发模式监听（EPOLLLT）+EPOLLONESHOT是否可以解决错误添加任务的问题

![image-20230314203725127](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230314203725127.png)







### 服务器性能指标



![image-20230314204326222](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230314204326222.png)

1. **TPS（每秒请求响应数量）**：大多数交互场景中，TPS包含QPS，一次交互过程中，产生多次查询。

   > timelock()计算，客户端发送请求，直到接收到响应的事件

2. **QPS（每秒查询数量）**

   > QPS计算=1000/（60*60） #1000名用户，一个小时大概的每秒处理事务数量

3. **吞吐量：**服务器，IO处理能力（读写能力），IO读写特别在意cpu占用，如果cpu负载特别高，IO读写能力下降（吞吐量降低），cpu负载轻，吞吐量提高。

4. **并发数：**

   > 并发数=QPS*平均响应事件 1000/(60*x60)x(5x60)

5. **平均响应事件：**

   > 平均响应事件 5*60



6. **负载测试：**

   > 1W用户，（1W请求包/秒），服务器处理能力，每秒1W请求（服务器性能）
   >
   > 负载测试强调在处理时间不变的情况下（1S），堆叠用户量，请求量，查看每秒处理上限

7. **压力测试：**

   > 通过高并发量，高请求数量高请求频率，向服务器递增施加压力，检测服务器处理极限，直到服务器异常崩溃（IO异常，调度单位异常，cpu异常），无法承受为止。









# 正则表达式



​		正则表达式在各个系统和编程语言都有广泛的使用和支持，主要用户数据检索，查询和提取，正则表达式内部使用贪心算法，可以以数据规则快速检索目标数据。

​		在linux系统下常见使用正则技术的命令 grep sed awk 比较经典的grep用于查询数据内容



**命令使用正则技术：**

grep '正则表达式字符串' 文件名

- 正则表达式是一种数据描述格式，用户描述数据规则，后期通过规则匹配数据，正则语句是一个字符串，由若干特殊符号构成。

![image-20230315214606765](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230315214606765.png)



**正则元字符：**

![image-20230315214634123](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230315214634123.png)

![image-20230315214647023](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230315214647023.png)

- 正则表达式看重数据规则，通过编写规则函数匹配一类数据，但是如果数据没有任何规则，无法使用正则表达式。
- 待匹配数据，规则越明确，正则越简单





**正则表达式工作模式：**

![image-20230315214812018](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230315214812018.png)



**正则函数：**

![image-20230315214834881](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230315214834881.png)





![image-20230315214139939](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230315214139939.png)









# 网络爬虫（web spider）



​		网络爬虫（网页抓取机器人），工作于万维网（www.网页和对应的web服务器），可以自动化批量下载保存网页信息或网络资源（提取数据）。

![image-20230316222235793](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316222235793.png)





一、**网络资源**：

![image-20230316222306580](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316222306580.png)





二、

**URL**：

![image-20230316222345518](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316222345518.png)



**HTML（超文本标记语言）：**

​		网页都是由html（超文本标记语言编写的），如果爬虫要爬取文章咨询类文本内容，那么需要了解html语言结构，从复杂的html源码中匹配提取数据内容。



**HTTP协议：（超文本传输协议）**

​		万维网环境中唯一协议，用户通过此协议与web服务器进行链接，请求网站数据，提交表单等等操作（HTTP协议基于TCP实现，用法与TCP没有太大区别）。

​		HTTP协议安全性较差，https（使用https协议通信之前要完成一系列安全认证过程，单向认证，双向认证）



**OPENSSL：技术**

​		https安全交互的主要技术，完成证书验证，双端验证，通过密钥对概念，完成数据加密及交互。



**种子URL：**

​		种子URL，爬虫程序处理的第一个链接（资源地址），精心挑选，可以通过种子url拓扑到更多url。



三、**爬虫的执行过程：**

![image-20230316222942512](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316222942512.png)

![image-20230316222959124](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316222959124.png)





四、**HTTP协议交互过程：**

![image-20230316223029618](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316223029618.png)





五、**HTTPS安全认证过程：**

​		CA证书（生成的数字签名），具有唯一性，可以通过认证识别签名，确保目标网站合法性，也是https安全认证的第一步，确认目标数据传输的安全性可靠性，通过密钥对的方式，保证数据传输安全（即使第三方通过抓包等放大得到数据也无法解密）

![image-20230316223101640](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316223101640.png)

![image-20230316223255119](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316223255119.png)

![image-20230316223317550](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230316223317550.png)





六、**HTTP请求响应模块：**

1. 发送请求头（Request_head）
2. 读取响应头
3. 提取保存响应头
4. 提取响应码
5. 判断辨别响应码
6. 读取保存数据

![image-20230318085541155](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230318085541155.png)

- OPENSET属于库函数，意味着如果代码中使用了这些函数，在gcc编译时需要加入库名 -lssl -lcrypto



- 通过域名获取IP地址

```c
#include<netdb.h>
```

![image-20230318094954467](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230318094954467.png)

[Analyical_HTML.c](相关文件\spider\Analytical_HTML.c)  [Analytical_URL.c](相关文件\spider\Analytical_URL.c)  [Check_Duplication.c](相关文件\spider\Check_Duplication.c)  [Connect_Webserver.c](相关文件\spider\Connect_Webserver.c)  [Container_Create.c](相关文件\spider\Container_Create.c)  [Container_Get_Node.c](相关文件\spider\Container_Get_Node.c)  [Container_Set_Node.c](相关文件\spider\Container_Set_Node.c)  [Download_Result.c](相关文件\spider\Download_Result.c)  [Get_statcode.c](相关文件\spider\Get_statcode.c)  [main.c](相关文件\spider\main.c)  [Net_init.c](相关文件\spider\Net_init.c)  [Openssl_Create.c](相关文件\spider\Openssl_Create.c)  [Request_Head_Create.c](相关文件\spider\Request_Head_Create.c)  [result.html](相关文件\spider\result.html)  [Save_Result.c](相关文件\spider\Save_Result.c)  [spider.h](相关文件\spider\spider.h)  [Spider_Controler.c](相关文件\spider\Spider_Controler.c) 





七、

**HTML解析和提取**

![image-20230318170807979](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20230318170807979.png)

- 网站的网页源码规则都有通用模板，大多数情况下，编写了一条提取网页数据的正则，对此网站的其他网页同样使用，具有通用性和复用性
- 有些时候，审查元素看到的网页源码，与实际源码略有不同，如果匹配不到数据检查一下网页源码





八、

**爬虫的优化选项：**

1. 去重优化，采用布隆过滤器（Hash），提高去重效率（消耗内存）
2. 并发爬虫（多线程，线程池），（并发下载），（并发解析），提高爬虫工作效率
3. DNS优化，频繁访问DNS域名解析服务，开销较大并且特别耗时，在程序内部创建一个DNS缓存表（里面以键值对的形式存储曾经访问过的域名=IP）







九、

**需要自行了解的额外内容：**

爬虫的抓取策略：广度优先爬虫，深度优先爬虫，大站优先爬虫

反爬虫和反反爬虫：反爬虫机制，IP封禁，行为验证，等等相关内容
