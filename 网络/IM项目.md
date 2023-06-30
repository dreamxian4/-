

# 宏定义+协议













# net



## **父类 INet**

- 前三个函数都由mediator对象调用，因此为public属性
- INet和INetMediator都需要用到对方的对象，为避免重复包含，可以在类前写个声明：

class INetMediator;

- 避免重复包含：1. 写类声明	2. 在类内创建一个静态对象，其他类可以通过该静态对象调用本类的共有函数



成员对象：

> INetmediator* m_pMediator;	用来将网络和中介者类连接起来，通过构造函数将mediator对象传进来

成员函数：

> virtual bool InitNet() = 0;	初始化网络虚函数，子类实现（TCP UDP）
> virtual void UninitNet() = 0;	关闭网络
> virtual bool SendData(long lSendIP, char* buf,int nlen) = 0;	发送数据，由mediator对象调用，发到lSendIP
> virtual bool RecvData() = 0;	接收数据，当有数据发来时自动调用，接收到的数据发给mediator对象处理（成员对象）





## 客户端 TcpClientNet



- 继承INet



成员对象：

> SOCKET m_sock;	负责监听的套接字
> HANDLE handle;	线程句柄，该线程负责接收数据
> bool m_isstop;	是否停止接收数据

成员函数：

> bool InitNet();	初始化网络
>
> > 加载库、创建套接字、建立连接（connect）、开始线程
>
> void UninitNet();	关闭网络
>
> > 退出线程、关闭套接字、卸载库
>
> bool SendData(long lSendIP, char* buf, int nlen);	发送数据
>
> > 1. 判断传入参数是否合法（buf nlen）
> >
> > 2. 防止粘包，先发送包大小（nlen），再发送包内容（buf）
>
> static unsigned int _stdcall recvthread(LPVOID p);	负责接收数据的线程
>
> > 将p转换成TcpClientNet*类型，调用RecvData()函数
>
> bool RecvData();	接收数据函数
>
> > 1. 先接收包大小，再接收包内容
> >
> > > 创建一个和包大小一样大的字符数组，记录每次接收到的数据大小，算出偏移量，将下一次接收到的数据拼接到后面（有的包不是一次性发过来的）
> >
> > 2. 将包发送给mediator对象的deal函数处理







## 服务端 TcpServerNet



- 继承Inet



成员变量：

> SOCKET m_sock;	用于连接的socket
> bool m_isstop;	是否停止接收数据
> list<HANDLE>m_hThreadHandleList;	保存线程句柄，每个线程负责和对应的主机通信（接收主机信息）
> map<unsigned int, SOCKET>m_mapThreadToSocket;	保存客户端和对应sock的映射关系

成员函数：

> bool InitNet();	初始化网络
>
> > 加载库，创建套接字，绑定IP，监听，创建负责连接的线程
>
> void UninitNet();	关闭网络
>
> > 退出线程，关闭套接字，卸载库
>
> bool SendData(long lSendIP, char* buf, int nlen);	发送数据
>
> > lSendIP里面装的是SOCKET
> >
> > 判断传入参数是否合法
> >
> > 先发送包大小，再发送包内容（防止粘包）
>
> static unsigned int _stdcall recvthread(LPVOID p);	负责接收数据的线程，由负责连接的线程创建
>
> > 调用接收数据函数
>
> static unsigned int _stdcall acceptthread(LPVOID p);	负责和客户端主机连接的线程，来一个连一个，并创建对应的接收数据线程
>
> > 每来一个客户端，为其创建一个套接字和接收数据的线程
>
> bool RecvData();	接收数据函数
>
> > 获取与客户端通信的socket，判断合法性
> >
> > 接收数据：先接收包大小，再接收包内容
> >
> > 调用中介者类的处理函数







# mediator



## 父类 INetMediator

成员对象：

> INet* m_pNet;	网络对象，用来将网络和媒介连接起来；通过new创建，参数为this

成员函数：

> virtual bool OpenNet() = 0;	打开网络
> virtual bool SendData(long lSendIP, char* buf, int nlen) = 0;	发送数据
> virtual void CloseNet() = 0;	关闭网络
> virtual void DealData(long lSendIP,char* buf, int nlen) = 0;	处理数据，由net对象调用







## 客户端 TCPclientMediator



- 继承INetMediator



成员函数：

> virtual bool OpenNet();
>
> > 调用m_pNet的初始化函数
>
> virtual bool SendData(long lSendIP, char* buf, int nlen);
>
> > 调用m_pNet的发送函数
>
> virtual void CloseNet();
>
> > 调用m_pNet的关闭函数
>
> virtual void DealData(long lSendIP, char* buf, int nlen);
>
> > 由INET调用，在函数内通过信号的方式将数据发送给核心处理类ckernel
> >
> > > ```
> > > Q_EMIT SIG_ReadyData(lSendIP,  buf,  nlen)
> > > ```
>
> void SIG_ReadyData(long lSendIP, char* buf, int nlen);	信号，在ckernel内和ckernel的槽函数绑定





## 服务端 TCPserverMediator



- 继承INetMediator



成员函数：

> virtual bool OpenNet();	打开网络，调用Net的打开网络函数
> virtual bool SendData(long lSendIP, char* buf, int nlen);	发送数据，调用INet的发送数据函数
> virtual void CloseNet();	关闭网络，调用Net的关闭网络函数
> virtual void DealData(long lSendIP, char* buf, int nlen);	处理数据，调用中心处理类的处理数据函数（通过中心处理类内的静态成员对象调用）





# ckernel





## 客户端 ckernel





成员属性：

> myChatDialog* m_mainWnd;	ui界面类
> INetmediator* m_tcpClientMediator;	中介者类
> FUNC m_netProtocalMap[_DEF_PROTOCAL_COUNT];	协议映射表(函数指针数组)【协议头-base】->处理函数

成员函数：

>构造函数
>
>> new窗口对象，显示窗口
>>
>> 创建中介者类对象，打开网络
>>
>> 绑定中介者的接收数据信号和本类的处理函数槽

> typedef void (CKernel::*FUNC)(char* buf, int nlen);	类成员函数指针，用来和协议头关联起来（处理数据时根据协议头调用不同的函数）
>
> void slot_ReadyData(long lSendIP, char* buf, int nlen);	处理接收的数据
>
> > 通过协议头找到对应的处理函数
>
>
>  void slot_RegisterRs(char* buf,int nLen);	处理注册请求回复
>
>  void slot_LoginRs(char* buf,int nLen);	 处理登录请求回复
>
>  void setProtocalMap();	初始化协议映射表：将协议头和对应的处理函数关联起来





## 服务端 ckernel



成员变量：

> static CKernel* pKernel;	静态对象，供中介这类调用；需要类外初始化
> CMySql m_sql;	负责连接数据库
> INetmediator* m_pServer;	中介者类对象
> FUNC m_netProtocalMap[_DEF_PROTOCAL_COUNT];	协议映射表(函数指针数组)【协议头-base】->处理函数

成员函数：

> 函数指针
> typedef void (CKernel::* FUNC)(long lSendIP, char* buf, int nlen);

> bool startServer();	开启服务
>
> > 连接数据库
> >
> > 开启网络：调用中介者类的开启网络
>
> void closeServer();	关闭服务
>
> > 断开数据库连接
> >
> > 关闭网络...
>
> void dealData(long lSendIP, char* buf, int nlen);	处理数据
>
> > 获取协议头
> >
> > 判断协议头是否在映射范围内
> >
> > 计算数组下标，获取对应函数
> >
> > 若对应函数存在，调用该函数
>
> void setProtocalMap();	初始化协议映射表
>
> > 同客户端
>
> void dealRegisterRq(long lSendIP, char* buf, int nlen);	处理注册请求
> void dealLoginRq(long lSendIP, char* buf, int nlen);	处理登录请求







# 未完待续...





