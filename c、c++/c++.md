

 

# 一、基础



## 1.输入输出

```c++
#include<iostream>//输入输出流，不加.h
using namespace std;//打开一个std(标准)命名空间

int main()
{
	int a = 98;
	char b = 'a';

    //c和c++的输出
    //ostream类型:cout
    //<<:输出操作符，本质上是一个函数
    //endl:函数（换行）
	printf("%d,%c\n", a, b);//98,a
	cout << a <<"," << b<<endl;//98,a
    
    //整型和字符型的转换
	printf("%c,%d\n", a, b);//b,97
	cout << (char)a << "," << (int)b << endl;//b,97
    
    //c和c++的输入
    //>>:输入操作符
    scanf("%d %c", &a, &b);
	cout << a << "," << b << endl;
	cin >> a >> b;
	cout << a << "," << b << endl;
   
    system("pause");
}
```

```c++
//输出格式（小数保留两位）
#include<iomanip>
using namespace std;
int main()
{
    float a=10;
    cout<<fixed<<setprecision(2)<<a;
}
```



## 2.命名空间

定义命名空间：区分同一个作用域下的相同成员（变量、方法）

```c++
int a = 10;
int main()
{
	int a = 20;
	cout << a<< endl;//20 局部
    //::作用域运算符，::前未指定任何作用域，为全局作用域
    cout << ::a<< endl;//10 全局
    
}
```

```c++
//定义一个命名空间
namespace AA
{
    int a=30;
    void show()
    {
        cout<<"1";
    }
};
//使用一个命名空间:
//1.using namespace 命名空间名;注意事项：不能和其他命名空间重名  using namespace AA;
//2.手动指定命名空间及成员  using AA::a;
//3.显式的指定使用命名空间里的成员  BB::show(); 

//using namespace AA;
using AA::a;
namespace BB
{
    int a=40;
    void show()
    {
        cout<<"2";
    }
};
int main()
{
    //注意事项：
    //1.若全局区没有a变量，则::a报错
    //2.若使用了两个命名空间，其内都有a变量，输出::a时报错
    //3.若全局区原本已有a变量，使用了同样包含a变量的命名空间后，输出a的值为原本全局区的值。
    
    cout<<a<<endl;//30 (BB同理)
    cout<<AA::a;//30
    cout<<BB::a;//40
    BB::show(); 
}
```

```c++
//应用
//value.h
#pragma once
namespace WINDOW_PLAT
{
	int a = 10;
};

namespace LINUX_PLAT
{
	int a = 100;
};

#ifdef _WINDOW//如果定义了宏WINDOW，则使用WINDOW_PLAT命名空间
using namespace WINDOW_PLAT;
#endif

#ifdef _LINUX
using namespace LINUX_PLAT;
#endif

//def.h
#pragma once
#define _WINDOW

//use.cpp
#include<iostream>
#include"def.h"
#include"value.h"
using namespace std;

int main()
{
	cout << a;
	return 0;
}
```



## 3.动态申请空间

C++动态申请空间关键字：new		

释放空间关键字：delete



在堆区动态申请空间，C和C++的区别：

1、new-delete C++关键字，需要编译器支持；malloc-free C函数，需要头文件支持

2、malloc 需要显式指定所需空间的大小(byte)，new 需要类型，根据类型自动计算所需空间

3、malloc void* 需要强转，new 不需要

4、new-delete 申请、释放对象内存空间，会自动调用构造、析构函数

```c++
//int 型变量

int *p1=new int;//无初始值
int *p2=new int();//0
int *p3=new int(10);//10
int *p3=new int{10};//10
delete p1;
p1=NULL;//p2,p3同理
```

```c++
//int 数组:释放数组 加[]

int* p1 = new int[10];//无初始值
int* p2 = new int[10]();//全0
int* p3 = new int[10]{1,2,3};//赋值
delete []p1;
memset(p4,-1,sizeof(int)*4);//赋初值：-1（只能-1或0）
p1=NULL;////p2,p3同理
```

```c++
//指针

int a=2;
int **p=new int*;
*p=&a;
```

```c++
//指针数组

int **p=new int*[10];
```

```c++
//数组指针
//1
int(**p)[] = new (int(*)[]);
int (**p)[10]=new (int (*)[10]);
//2
typedef int(*PP)[];
PP *p=new PP;
```

```c++
//二维数组
int (*p)[3]=new int [2][3];
```



## 4.BOOL、for

BOOL-bool：

BOOL ：widows系统提供的int 的别名(typedef)  ， TRUE(1)   FALSE(0) 宏，占4个字节空间

bool : C++关键字，  true false 关键字，占1个字节

```c++
#include<windows.h>
BOOL a = TRUE;
a=2;
cout << a;//2
```

```c++
bool b=true;
b=2;
cout<<b;//1
```

```c++
int b[5]={1,2,3,4,5};
//遍历方法1：
for(int a=0;a<5;a++)
{
    cout<<b[a]<<endl;
}
//法2：
for(int c:b)
{
    cout<<c<<endl;
}
```



## 5.string

```c++
#include<string>//没有该头文件也可以使用string 但不能进行输出（cout<<）

string a="1234";//1234
a="123";//123
a="123"+"1234";//1231234

//利用操作符拼接
a+="12";//123123412

//长度
a.size();

//截取
string b=a.substr(3,2);//下标，位数
cout<<b;//12
string b=a.substr(3);//从下标3到最后

//转成字符数组 const char*
const char *p=a.c_str();
cout<<p;//123123412

//字节大小：28
cout<<sizeof(string)<<endl;//28

//字符串转整型
int astoi(str);

//字符串的键盘输入：
cin>>str;//在遇到“空格”时停止输入
string::getline(cin, cmd);//遇到“换行”时停止

//将字符串按空格分为多个字符串
#include<sstream>
stringstream ss(str);
string s;
int i=0;
while(ss>>s)
{
    if(i==0){}//对第一个字符串进行操作...
}

//传参
show(string("nijs"));
```



## 6.nullptr(c++11)

nullptr : 空指针关键字

NULL ： 整型数字  #define NULL 0

引入nullptr的原因：防止函数重载时的二义性（用NULL赋值的无类型指针不能隐式类型转换成其他类型）

```c++
void play(int a)
{
    cout<<"1";
}

void play(int *a)
{
    cout<<"2";
}

void play(char *a)
{
    cout<<"3";
}

play(NULL);//1:优先匹配整型
//play(nullptr);//无法识别
play((int*)nullptr);//2
play((char*)nullptr);//3
```

```c++
//NULL本质是0
void* a = NULL;
//int* b = a;
int* b = (int*)a;
```







## 7.函数

### a.默认值

函数参数可以指定默认值，从右往左依次指定，不能间断；

如果函数声明和定义分开写，在函数声明处指定默认值即可。

```c++
void a(int a,char b='a');//b默认值为a
int main()
{
    func(1);
    func(1,'b');
}
void a(int a,char b){}
```



### b.重载

在同一个作用域下，函数名相同，参数列表不同（参数的类型、数量、顺序）的多个函数之间的关系；

编译器可以根据重载函数的参数自动区别调用对应的函数。

```c++
//不是重载，是重定义，传的都是指针
void a(char *p){}
void a(char p[]){}
```



## 8.引用

引用：对已存在的一块内存空间起别名，引用一旦定义就必须初始化，指向一块空间（没有空的引用）

引用和指针的区别：

1.引用定义就要初始化；指针可以不用初始化（不推荐）。

2.引用一旦引用某个空间，就不能再引用其他空间；指针可以修改其指向的空间。

3.有空的指针；没有空的引用。

4.引用不会额外开辟空间；指针会开辟存储地址的空间。

5.指针可以有多级；引用不能。

```c++
int  a=5;
int &b=a;
cout<<b;//5

b=6;
cout<<a;//6
```



### 通过函数修改实参

函数传参的三种形式：值 地址 引用

不推荐值传递，尤其复合类型；

如果在函数内修改实参，一定要地址、引用传递。

```c++
//1.通过指针
void a(int *p)
{
    *p=5;
}
//2.通过引用
void b(int &p)
{
    p=5;
}

int x=10;
a(&x);
b(x);
```



### 函数重载-引用

```c++
//是函数重载，通过函数指针调用
void show(int a){}
void show(int &b){}

void (*p1)(int)=&show;//第一个
void (*p2)(int &)=&show;//第二个

int a=5;
(*p1)(a);
(*p2)(a);
```



# 二、类

## 1.访问修饰符、类和对象

类：完成某一功能相关的数据和算法的集合，是一个抽象的概念

类名一般以C开头

用对象来实例化类

```c++
//访问修饰符：约束类成员的适用范围，默认为private
//private:私有的，类成员只能在类内使用
//protected:保护的，类成员在 类内 和子类 中可以使用
//public:公共的，类成员在类内和类外，只要能定义对象的地方都可以使用

//定义类：
class Cpeople
{
public:
    string m_strname;//类成员属性（类成员变量）一般以m_开头
protected:
    int m_nAge;
private:
    bool m_bSex;//对于私有和保护的成员，一般提供一对set/get接口。
    
public:
    void eat(){}//成员函数（成员方法）
    void setSex(bool a){m_bSex=a;}
    bool getSex(){return m_bSex;}
};

//实例化（使用类）
int main()
{
    Cpeople p;//定义对象p
    p.eat();
}
```



## 2.构造函数、析构函数

```c++
//构造函数：编译器默认给提供
//默认的构造函数：无返回值（不是void ）函数名是当前类名，无参，函数体代码为空
//构造函数在定义对象的时候自动调用，用来初始化类成员属；
//构造函数允许有多个，是函数重载的关系
//一旦手动编写构造函数，编译器将不提供默认的构造函数
class a
{
public:
    string m_name;
    a(){}
    a(string name){m_name=name;}
};

a a1;
a a2("小米");
//若没有无参构造函数 a a1 将报错；因为没有默认构造函数可用
```



```c++
//析构函数：编译器会默认提供
//默认的析构函数：无返回值，函数名是~类名，无参，函数体代码为空
//析构函数只允许有一个，并且无参数
//用来回收成员申请的额外的空间，在对象生命周期结束前（对象回收前）自动调用
//一旦手动编写析构函数，编译器将不再提供默认的析构
class a
{
public:
    string m_name;
    int age;
    a(string name,int b){m_name=name;age=b;}
    ~a(){}//可在代码体内释放成员变量申请的空间
};

a *p=new a("haha",19);
cout<<p->m_name;
delete p;
```



## 3. C++中类和结构体的区别

c++中结构体也可以有构造函数，要求和类一样

1.默认的访问修饰符不同，类：private  结构体： public

2.默认的继承方式不同， 类：private  结构体：  public



## 4.对象的种类

1、**栈区局部对象**(在函数体内)：遇到函数的返回 或者 } 生命周期结束，自动回收。

```c++
#include"aa.h"int main()
{
    People peo;
}
```

2、**堆区对象**：手动回收

```c++
int main()
{
    People *peo=new People;
    delete peo;
    peo=nullptr;
}
```

3、**全局对象**：

生命周期：程序开始创建----程序退出（销毁）被回收

作用域：整个应用程序，可跨文件使用（extern People peo;）

```c++
People peo;
int main(){}
```

4、**静态全局对象**：

生命周期：程序开始创建----程序退出（销毁）被回收

作用域：只能在当前文件中去使用，具有文件作用域

```c++
static People peo;
int main(){}
```

5、**静态局部对象**：第一次调用包含该对象的函数时创建，直到程序退出（第二次调用函数时不再创建新对象）

```c++
void show()
{
    static People peo;
}
```

6、**临时（匿名）对象**：生命仅限于当行，遇到 ； 结束

```c++
int main()
{
    People();
}
```

- **对象作为返回值：**

```c++
People play()
{
    People peo();
    return peo;
};
//若没有对象获取该返回值
int main()
{
    play();
    //自动创建一个匿名对象并返回，调用拷贝构造函数，该行结束时调用析构函数。（此时执行两次析构函数：play()函数中的局部对象生命周期结束，调用析构函数；生成的匿名对象生命周期结束，调用析构函数。执行一次构造函数：play()函数中的局部对象。）
}

//若有对象获取该返回值
int main()
{
    People peo=play();
    //返回的匿名对象升级为局部对象，生命周期到方法体结束。（一次构造，一次析构：play()函数中的局部对象。）
}
```



## 5.类成员

### 类的大小

```c++
//无成员
class a{};
a aa;
sizeof(aa);//1:占位作用，表示当前类真是存在于内存中

//一个int 型属性
class a{int b;};
sizeof(aa);//4:无需占位，为该类实际占用内存大小

//一个int 一个double
class a{int b; double c;}//16:以大的为基准

//一个int 一个方法
class a{int b;void c(){}};//4:方法不在对象中，而在类中

//一个int 两个方法
class a{int b;void c(){} void d(){}};//4
```





### 编译期和运行期

​		编译期是指把源程序交给编译器编译、生成的过程，最终得到可执行文件。运行期是指将可执行文件交给操作系统执行、直到程序退出，执行的目的是为了实现程序的功能。

​		类是编译期的概念，包括成员的**访问控制**和**作用域。**

​		对象是运行期的概念，包括定义类的实例、引用、指针等使用其类成员。





### 属性和方法（非静态）

1、非静态类成员变量：属于对象，在定义对象时才存在；定义多个对象存在多份，彼此互不影响。

2、非静态类成员函数：属于类，不属于对象（存在与否不依赖对象定义与否）；在编译期就存在，只有一份。

```c++
People *p=nullptr;
cout<<p->name;//报错：未定义对象，属性不存在
cout<<p->eat();//正常输出：函数在编译时就存在

p=new People();
cout<<pp->name;//正常输出：定义对象
```





### this指针

当前类对象的指针，类中 **非静态成员函数** 的参数列表中，

默认编译器加的一个隐藏的参数，在参数列表中的第一个参数，指向了调用该函数的对象。

作用：连接对象和类成员 （桥梁）

```c++
class a
{
    int aa;
    void play(){}
    void show(/* a *const this */)
    {
        aa;//this->aa
        play();//this->play()
    }
};
```





### 属性和方法（静态）

**静态成员属性：**

​		不属于对象，属于类；只有一份，多个对象之间共享这个静态成员；在编译期就存在，不依赖对象的存在而存在。   

​		在类外进行初始化：类型 类名::变量名=初始化值;



**静态成员函数与普通成员函数的区别：**

​		静态成员函数没有隐藏的this指针参数，不能使用普通成员（属性+方法），只能使用静态成员。

- 静态成员在没有对象的情况下，可以通过 类名:: 调用，也可以通过对象调用


```c++
class a
{
    int aa;
    static int bb;
    void play(){}
    static void playy(){}
    static void show()
    {
        aa;//报错
        bb;//OK
        play();//报错
        playy();//OK
    }
};

//初始化
int a::bb=5;//若在构造函数或其他地方进行赋值，不叫做初始化

int main()
{
    cout<<aa::bb;
    aa::show();
}
```





### const 



定义了就要初始化，之后不能修改

```c++
const int a=5;
//a=6;		报错
```



- **修饰指针：**

  

**常量指针**：const修饰的是*p，**不能更改p指向的空间的值**，可以修改p所指向的空间

```c++
int b=4;
const int *p=&a;

//*p=2;		报错：不能给常量赋值
p=&b;		//合法:修改指向的指针
cout<<*p<<endl;		//5 合法：读取
```

**指针常量**：修饰的是p指针，可以通过指针修改指向空间里的值，**不能修改指针的指向**

**（指针常量不能存放常量的地址**）

```c++
int * const q=&b;
//int * const q1=&a;	非法：安全级别降低

*q=10;		//合法
//q=&a;		非法：修改指针的指向
```

**都修饰**：什么都不能改（可以存放常量地址）

```c++
const int* const p1=&a;
//*p1=6;	错
//p1=&b;	错
```



- **修饰类成员**

  

**成员属性**：在**初始化参数列**表初始化

#### **初始化参数列表**

真正初始化类成员的地方（位置：构造函数()后面），const成员的初始化必须在初始化参数列表进行，普通成员也可以初始化，多个成员用“ , ”分割。

- 必须在初始化参数列表中初始化的：const修饰的属性，引用，没有默认无参构造的父类构造函数

```c++
class A
{
    const int m_a;
    int m_b;
    
    A():m_a(4),m_b(5)//初始化参数列表
    {
        //m_a=6;	赋值，常量不能赋值
        m_b=6;		//赋值
    }
};
```

初始化成员的顺序：成员在类中的声明顺序

```c++
class A
{
    int m_b;
    const int m_a;
    A(int a):m_a(a),m_b(m_a){}	//先赋m_b,再赋m_a;	m_b=随机数,m_a=a
};

class B
{
    const int m_a;
    int m_b;
    B(int a):m_a(a),m_b(m_a){}	//先赋m_a,再赋m_b;	m_a=a,m_b=a
};
```



**常函数**：参数列表后加const修饰，修饰的是this指针

```c++
class A
{
    int a;
    void show(/* const A* const this */)const {}
};
```

常函数中不能进行成员变量的修改操作（静态变量可改）

```c++
class A
{
    int a;
    static int b;
    void show(/* const A* const this */)const
    {
        b = 6;		//静态变量可改
        //a = 5;    非法
        cout << b;	//输出合法
    }
};
```

**mutable关键字**：可允许在常函数中修改变量值

```c++
class A
{
    mutable int a;
    void show(/* const A* const this */)const
    {
        a=6;
    }
};
```



**常量对象：**只能调用常函数，不能更改成员变量值

```c++
class A
{
    int a;
    void show(/* const A* const this */)const{}
    void play(/* A* const this */){}
};

//常量对象
const A aa;
//aa.a=4;		非法
aa.show();		//const A* const this=&aa;
//aa.play();	//A* const this=&aa;  安全级别降低，不允许

//普通对象
A bb;
bb.show();		//const A* const this=&bb;  安全级别升高，允许
```





### inline



inline内联关键字：适用于代码少，逻辑简单的函数；在编译期进行内联展开

```c++
inline int add(int a,int b)
{
    return a+b;
}
int main()
{
    add(10,20);//展开为10+20
}
```

优点：程序的执行效率提高，空间换时间

缺点：内存会增大（调用多少次，就复制多少代码）

建议性关键字：递归函数即使加上inline，编译器也不会认为是内联函数

- 类、结构体中**在类内声明并定义的函数默认为内联函数**；在类中只给出声明，类外定义的函数，默认不是内联函数。可手动加inline关键字。





### friend



​		friend 友元函数关键字：在某类中用friend修饰一个外部函数的声明，在该外部函数可以使用本类的**私有成员。**

```c++
class Fun
{
    int a;
    friend void show (int b);
};
void show(int b) { Fun fun; fun.a = b; }
```







## 6.类之间的关系



### 横向关系



#### --组合（复合）

​		是一种"is a  part of"的关系（**部分与整体**）。组合是一个类中**包含**另一个类对象。相比聚合，组合是一种强所属关系，组合关系的两个对象往往**有相同的生命周期**，被组合的对象是在组合对象创建的同时或者创建之后创建，在组合对象销毁之前销毁。一般来说被组合对象不能脱离组合对象独立存在，整体不存在，部分一定不存在。

​		举例：人与手、人与头之间的关系。人需要包含头和手，头和手是人的一部分，不能脱离人而独立存在。

```c++
class CHand{};
class CPeople
{
    CHand m_hand;
};
```



#### --依赖

​		是一种"user a"的关系。**一个对象的某种行为依赖于另一个类对象**，被依赖的对象视为完成某个功能的工具，并不持有对他的引用，只有完成某个功能的时候才会用到，而且是必不可少的。依赖之间**没有生命周期约束关系**。

​		举例：人要完成编程这件事，需要用到电脑。电脑作为一个工具，其他时候不需要，电脑也不可能作为人的属性而存在（非组合关系），人必须依赖电脑才能完成这件事。

```c++
class CComputer{};
class CPeople
{
    void Code(CComputer *pc){}//或CComputer &pc
};
```



#### --关联

​		是一种"has a"的关系。关联不是从属关系，而是**平等关系**。可以拥有对方，但不可占有对方。完成某个功能与被关联的对象有关，但被关联的对象**可有可无**。被关联的对象与关联的对象**无生命周期约束关系**。被关联对象的生命周期由谁创建就由谁来维护。只要二者同意，可以随时解除关系或是进行关联。被关联的对象还可以再被别的对象关联，所以关联是可以共享的。

​		举例：人和朋友的关系。人要完成游戏这个功能，没有朋友可以自己玩，有朋友可以和朋友一起玩。

```c++
class CFriend{};
class CPeople
{
    CFriend *m_pFriend;
    void play()
    {
        if(m_pFriend){/*一起玩*/}
        else /*自己玩*/
    }
};
```



#### --聚合

​		是一种"owns a"的关系。多个被聚合的对象**聚集起来**形成一个大的整体。聚合的目的是**统一进行管理**同类型的对象，聚合是一种若所属关系，被聚合的对象还可以再被别的对象关联，所以被聚合对象时可以共享的。虽然是共享的，聚合代表的是一种更亲密的关系，相当于强版本的关联。**有生命周期约束关系**。

```c++
class CPeople{};
class CFamily
{
    CPeople* families[10];
};
```







### 纵向关系-继承



#### 1.重名问题



​	**子类（派生类）可以使用父类（基类）成员，若成员同名，用类名::进行区分**

```c++
class CFather			//父类
{
public:
    int m_money;
    int m_fage;
};

class CSon:public CFather//子类
{
public:
    int m_money;		//和父类同名
    int m_sage;
};

int main()
{
    CSon cs;//赋值略
    cout<<cs.m_money<<endl;			//输出子类money    重名
    cout<<cs.CFather::m_money<<endl; //输出父类money
    cout<<cs.m_fname<<endl;			//输出父类age     不重名
    cout<<cs.m_sname<<endl;			//输出子类age
}
```





#### 2.空间大小和内存分布



子类对象的**空间大小**：子类大小+父类大小

```c++
cout<<sizeof(cs);	//16
```

成员属性的**内存分布**：定义子类对象，包含父类的成员；**按照声明顺序，先父类成员，再子类成员**

```c++
cout<<&cs<<endl;				//00DFF7D8
cout<<cs.CFather::m_money<<endl; //00DFF7D8
cout<<cs.m_fage<<endl;			//00DFF7DC
cout<<cs.m_money<<endl;			//00DFF7E0
cout<<cs.m_sage<<endl;			//00DFF7E4
```





#### 3.构造函数的调用顺序



父类构造——>组合对象构造——>子类构造函数体

定义子类对象时的构造顺序：**先父类，再子类**，父类的**默认无参构造**可以被自动调用。

```c++
class CFather{};
class CSon:public CFather
{
    CSon()/* :CFather() */{}		//自动调用
};
```



若父类**没有无参构造**，需在子类的初始化参数列表中手动调用父类构造函数

```c++
class CFather{CFather(int a,int b){}};
class CSon:public CFather
{
    CSon():CFather(12,24){}			//手动调用
};
```



创造一个后爹（组合关系）

```c++
class CFather2{CFather2(int a,int b){}};
class CSon:public CFather
{
    CFather2 cf;
    CSon():CFather(12,24),cf(14,28){}	
    //两个构造函数的调用与定义顺序有关，先CFather,后cf，后子类
};
```





#### 4.析构函数的调用顺序



> 析构函数作用（复习）：用于**销毁**类内new 出来的部分

- **与构造函数相反，** 子类析构 - 组合对象析构 - 父类析构

  > 原因：
  >
  > 在栈区对象销毁前，先执行自身析构，销毁 new 出来的部分，
  >
  > 接着要销毁对象了，内部对象也要被销毁，执行组合对象的析构。
  >
  > >  （先把子类所有的new出来的部分都释放掉，最后剩一个组合对象了，再释放。释放时先调用析构函数，再释放本身，就很安全）
  >
  > 最后执行父类的析构。
  >
  > > （父类也是同理，假象在最前面定义了一个临时对象，最后子类内空间全部释放掉「临时对象也释放掉」，再释放父类空间，避免内存泄露
  >
  > **与构造顺序完全相反。**





#### 5.继承的好处

​		提高了程序代码的**复用性、扩展性、后期更容易维护**。将一些功能相似的类的公共成员单独抽离出来，形成一个类，这个类就是父类；子类继承父类，**包含了这些公共的成员**。





#### 6.继承方式



描述了父类的成员在子类中所表现的属性（**使用范围**）

**public公有继承:**

父类：public				子类：public

父类：protected		   子类：protected	

父类：private			   子类：不可访问

```c++
class CFather
{
private:
    int a;
protected:
    int b;
public:
    int c;
};

class CSon:public CFather
{
    void n()
    {
        //cout<<a;		私有成员 子类不可访问
        cout<<b;		//可
        cout<<c;		//可
    }
};

class CGrandson:public CSon
{
    void n()
    {
        cout<<b;		//可   保护成员 孙子类也可使用
    }
};

int main()
{
    CSon cs;
    //cout<<cs.b;		保护成员 类外不可使用
    cout<<cs.c;			//可
}
```



**protected保护继承:**

父类：public				子类：protected

父类：protected		   子类：protected	

父类：private			   子类：不可访问

```c++
CSon cs;
//cout<<cs.a;		父类私有成员 不可访问
//cout<<cs.b;		保护成员 类外不可使用（类内和子类可用）
//cout<<cs.c;		保护成员 类外不可使用（类内和子类可用）
```



**private私有继承:**

父类：public				子类：private

父类：protected		   子类：private

父类：private			   子类：不可访问

```c++
CSon cs;
//cout<<cs.a;		父类私有成员 不可访问
//cout<<cs.b;		私有成员 类外、子类不可使用（类内可用）
//cout<<cs.c;		私有成员 类外、子类不可使用（类内可用）
```





#### 7.隐藏

​		父类与子类中有**重名成员**（属性+方法），若想使用父类的成员，需用"**类名::**"调用。父类和子类的**同名函数不属于重载**，调用父类函数时也需"**类名::**"调用。

```c++
class CFather
{
    void show(int a,int b){}
};

class CSon: public CFather
{
    void show(int a){}
    void shoe(){}
};

int main()
{
    CSon cs;
    cs.show();
    cs.show(1);
    //cs.show(1,2);		若子类没有show()函数，则该条语句可用
    cs.CFather::show(1,2);
}
```





#### 8.类成员函数指针



##### --this指针

​		在继承下，允许未经转换的情况下，**父类指针**指向**子类对象**。

​		**好处**：统一多种类型，提高复用性、扩展性。

```c++
class CFather{void show(/* CFather * const this */){}};
class CSon:public CFather{};
int main()
{
    CSon cs;
    cs.show();//this=&cs;  父类指针指向子类对象
}
```

```c++
class CPeople{void show(){}};
class CWhite:public CPeople{void show(){}};
class CBlack:public CPeople{void show(){} void eat(){}};
class CYellow:public CPeople{void show(){}};
void play(CPeople *peo)
{
    peo->show();
    //peo->eat();  	不能调用子类专有的函数
}
//具体使用哪个show函数，依据传进来的对象类而定。？？？
```

##### --复杂的函数

```c++
int(*fun(char *,void *(long,char*)))(int*,void (*)(char,bool*))
{
    return nullptr;
}
/*
函数名：fun
参数：(char *,void *(long,char*))		两个参数： char*  函数void*(long,char*)
返回值int(*)(int*,void (*)(char,bool*)) 函数指针 指向int(int*,void (*)(char,bool*))
*/
```

##### --用typedef进行优化

```c++
typedef void *A(long,char*);		//参数中的函数
typedef void (*B)(char,bool*);		//返回值指向的函数中的函数指针
typedef int(*C)(int*,B);		    //返回值整体函数指针
C fun(char*,A a){return nullptr;}	//优化后的函数

//使用
void* fun1(long,char*)
{
    return nullptr;
}
C c=fun("12",fun1);
```

##### --用指针指向类成员函数

```c++
//普通函数指针
typedef void (*A)();
void haha(){}
int main()
{
    A a=&haha;
    (*a)();
}
```

```c++
//类成员函数指针	::* c++整体运算符，定义类成员函数指针（不能::(*)）
class CL{void show(){}};
typedef void (CL::*A)();//类成员函数指针
void (CL::*A[4])();//类成员函数指针数组
int main()
{
    A a=&CL::show;
    CL cl;
    CL *cll=new CL;
    (cl.*a)();   //.* c++整体运算符，通过对象调用函数指针指向的函数
    (cll->*a)(); //->* c++整体运算符，通过对象调用函数指针指向的函数
}
```

##### --类成员函数指针的应用

父类指针**调用**子类**函数**

- 注：typedef在类声明下面

```c++
class CFather{};
class CSon :public CFather{public:void show(){}};
typedef void (CFather::*A)();	//定义成员函数指针
int main()
{
    CFather *pcf=new CFather;
    //pcf->show();
    A a=(A)&CSon::show;
    (pcf->*a)();		//调用show函数
}
```

```c++
class CPeople{void show(){}};
class CWhite:public CPeople{public:void show(){} void eat(){}};
class CBlack:public CPeople{public:void show(){} void eat(){}};
class CYellow:public CPeople{public:void show(){} void eat(){}};
typedef void (CPeople::*A)();
void play(CPeople *peo,A a)
{
    (peo->*a)();
    //peo->show();
    //peo->eat();  	不能调用子类专有的函数
}
//具体使用哪个show函数，依据传进来的对象类而定。
int main()
{
    A a =(A)&CBlack::eat;
    play(new CBlack,a);
    play(new CYellow,(A)&CYellow::show);
    play(new CWhite,(A)&CWhite::show);
}
```

```c++
#include<iostream>
using namespace std;

class CCalculate
{
public:
	CCalculate()
	{
		p_fun[add] = &CCalculate::Add;
		p_fun[sub] = &CCalculate::Sub;
		p_fun[mul] = &CCalculate::Mul;
		p_fun[div] = &CCalculate::Div;
	}
	enum cal{add=0,sub,mul,div};//计算标识

private:
	int (CCalculate::*p_fun[4])(int, int);//成员函数指针数组

private://计算函数
	int Add(int a, int b)
	{
		return a + b;
	}

	int Sub(int a, int b)
	{
		return a - b;
	}

	int Mul(int a, int b)
	{
		return a * b;
	}

	int Div(int a, int b)
	{
		return a / b;
	}
public://提供给用户的函数
	int calculate(cal c,int a, int b)
	{
		return ((this->*p_fun[c])(a, b));
	}

};

int main()
{
	CCalculate ca;
	cout<<ca.calculate(ca.add, 1, 2);//或CCalculate::add

	return 0;
}
```





## 7.多态



​		**多态性**：**相同的行为方式**导致了**不同的行为结果**，同一行语句展现了多种不同的表现形式。

​		c++实例：父类指针可以指向任何继承于该类的子类，多种子类具有多种形态，由父类的指针进行统一管理，父类的指针具有多种形态。（类成员函数指针）

​		**多态形成条件**：1.有继承关系，存在父类-子类

​									2.用父类的指针指向子类对象

​									3.父类中存在**虚函数**，子类重写父类的虚函数

​		**virtual关键字**：虚函数的关键字，加在函数前

```c++
class CFather{virtual void show(){cout<<"1";}};
class CSon:public CFather{void show(){cout<<"1";}};
int main()
{
    CFather *cf=new CSon;
    cs->show();//可直接调用子类函数
}
```



###  虚函数



#### 1.虚函数的大小

```c++
class CFun{void show(){}};		//只包含普通函数
class CFun1{virtual void show(){}};	//有一个虚函数
class CFun2{virtual void show(){} virtual void play(){}};//有两个虚函数
int main()
{
    cout<<sizeof(CFun)<<endl;//1
    cout<<sizeof(CFun1)<<endl;//4
    cout<<sizeof(CFun2)<<endl;//4
}
```



#### 2.实质

![image-20220715095628169](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220715095628169.png)

**__vfptr （虚函数指针）:** 

​		类型 void ** (二级指针)指向了一个数组（虚函数列表）。

​		当类中存在任意虚函数，**定义对象时**，会在内存空间的**前面**多分配指针的空间（__vfptr），执行构造函数，**在初始化参数列表中进行初始化**，指向虚函数列表。

- 属于对象，多个对象会有多份虚函数指针，指向同一个__vftable。



**__vftable（虚函数列表）** : 

​		数组的每个元素是指针，指向虚函数的指针。**属于类，在编译期自动创建**。





#### 3.调用虚函数的流程

```c++
	找到对象内存空间的虚函数指针（__vfptr）,通过虚函数指针找到虚函数列表（__vftable），定位虚函数列表中的函数指针，通过指针调用具体的虚函数。
```

```c++
class CFun{virtual void show(){}  void get(){}};
int main()
{
    CFun *cf=nullptr;
    cf->get();			//普通函数属于类，可不通过对象调用
    //cf->show();		//调用虚函数需先找到对象空间，不能直接调用
}
```





#### 4.虚函数和普通函数的区别

（1）二者的**调用流程不同**，虚函数调用效率比普通函数低。

（2）**使用场景不同**，虚函数用来实现多态，普通函数不能实现多态。

```c++
父类指针指向子类对象
普通函数：父类中有就用父类的，父类中没有就不能使用
虚函数：父类中有虚函数定义才能使用，子类中有就用子类的，子类没有就用父类的
```





#### 5.纯虚函数

- **父类只声明，不实现；最终子类必须定义实现该纯虚函数。**
- **抽象类**：包含纯虚函数的类
- **抽象类不能定义对象**
- **override 关键字**：要求当前这个函数必须是重写父类的虚函数，若不是，会报错。

```c++
class CFather			//抽象类
{
public:
    virtual void show()=0;//纯虚函数
};

class CSon :public CFather//具体类
{
    void show(){}			//void show()override{}
};
```









### 虚函数重写

​		重写：子类定义了和父类一模一样（函数名、参数列表、返回值）的虚函数。

​		继承下，虚函数**指针指向创建对象的类的虚函数列表**；子类不仅继承父类的成员，也继承父类的虚函数列表，会检查是否重写虚函数，若重写，会替换掉父类的虚函数地址（覆盖）；若没有重写，则保留父类虚函数；若子类有自己的虚函数，在后面依次添加。

```c++
class CFun
{
public:
	virtual void show1() { cout << "16"; }
	virtual void play(){}
};

class CSon :public CFun
{
public:
	virtual void show1() { cout << "15"; }
};

int main()
{
    //指针形式
    CFun *cf=new CSon;
    cf->show1();//15		虚函数指针指向子类的虚函数列表
    //若show1不是虚函数，此处输出16
    cf->play();	//			子类继承了父类的虚函数列表
    
    //引用形式
    Son son;
    CFun &cfun=son;
    cfun.show1();
    cf.play();
}
```





### 构造析构顺序

- 父类指针指向子类对象：**父类构造-->子类构造-->父类析构**

​		**调用类析构取决于指针的类型**

```c++
CSon son;				//父类构造 子类构造 子类析构 父类析构

CFather *cf=new CSon;	 //父类构造 子类构造
delete cf;				//父类析构

CFather *cf=new CSon;	 //父类构造 子类构造
delete (CSon*)cf;		 //子类析构 父类析构（不推荐）

//在父类的析构函数前加virtual  virtual ~CFather(){}
//虚析构，发生了多态
CFather *cf=new CSon;	 //父类构造 子类构造
delete cf;				//子类析构 父类析构（推荐）
```





### 多态的缺点

1、虚函数指针在每一个对象中都会存在一份，虚函数列表在每个类存在一份。

2、效率问题

3、安全性问题，当虚函数是私有属性时，可通过下面方法获取该函数。

```c++
typedef void (*P_FUN)();
CFather *cf=new CSon;
P_FUN p_fun1=(P_FUN)*(((int *)*(int *)cf)+0);
P_FUN p_fun2=(P_FUN)*(((int *)*(int *)cf)+1);
P_FUN p_fun3=(P_FUN)*(((int *)*(int *)cf)+2);
(*p_fun1)();
(*p_fun2)();
(*p_fun3)();
```





## 8.隐式类型转换



**条件：构造函数只有一个参数，或多个参数有默认值 (赋值给第一个参数)**

```c++
//只有一个参数
class Fun
{
    int a;
    Fun(int b)
    {
        a=b;
    }
};

int main()
{
    Fun fun=5;					//发生了隐式类型转换
    cout<<fun.a;//5
    
    Fun fun2(6);
    fun2=4;						
    //发生了隐式类型转换(实质：生成了一个临时对象，调用了拷贝构造函数（浅拷贝问题）)
    cout<<fun2.a;//4
}
```

```c++
//多个参数有默认值
class Fun
{
    int a;
    Fun(int b=4，int c=5,int d=6)
    {
        a=b;
    }
};

int main()
{
    Fun fun=5;
    cout<<fun.a;//5
}
```



### 避免隐式类型转换



在构造函数前加 **explicit 关键字**

```c++
class Fun
{
    int a;
    explicit Fun(int b)
    {
        a=b;
    }
};

int main()
{
    //Fun fun=5;			不可用
    //cout<<fun.a;//5
}
```









## 9.拷贝构造







拷贝构造函数：函数名为当前类名，参数是当前类对象的引用；

编译器默认提供的函数体代码不为空，**参数对象里的成员给this对象中的成员依次初始化。**

- 如果手动重构了拷贝构造函数，编译器不再提供默认的拷贝构造

```c++
class Fun
{
    int a;
    char b;
    Fun(const Fun &fun)				//拷贝构造函数
    {
        this->a=fun.a;
        this->b=fun.b;
    }
};

int main()
{
    Fun fun1;
    Fun fun2(fun1);					//使用拷贝构造函数
}
```







### 浅拷贝问题



​		编译器**默认提供的**拷贝构造函数是**浅拷贝**（当属性中有指针时，使用浅拷贝，两个对象的该指针变量**指向的是同一个地址**；若某一对象的析构函数回收了该地址，则另一个对象再次回收时会产生错误，引发异常）

1.当类中有指针成员且new了空间，会导致**一块空间被回收多次**，程序崩溃。

2.当类中有指针成员且new了空间，当用一个对象修改指针指向空间的值时，其他对象**使用的是修改后的值**，导致程序逻辑错误。





### 解决浅拷贝问题



**方法1：**

​		手动重构拷贝构造函数，实现一个**深拷贝**（为里面的指针成员单独开辟一块空间，并将指针里面嗯对值传过来）

```c++
class Fun
{
    int *b;
    Fun(const Fun &fun)					//实现深拷贝
    {
        if(fun.b)
        {
            this->b=new int (*fun.b);
        }
        else
        {
            this->b=nullptr;
        }
    }
};
```



**方法2：**

​		避免浅拷贝的发生：参数使用引用或指针

```c++
void show(Fun &fun){}
```







## 10.默认重载 "="



​		类中存在默认的 **operator=(const Fun &)**，编译器提供的（**存在浅拷贝问题**）

```c++
class Fun
{
    int a;
    Fun& operator=(const Fun&fun)	//默认的operator=，参数类型为当前类对象的引用
    {
        this->a=fun.a;
        return *this;
    }
};

int main()
{
    Fun f1;
    Fun f2=f1;
}
```



解决浅拷贝问题：深拷贝

```c++
class Fun
{
    int a;
    int *p;
    Fun& operator=(const Fun&fun)	
    {
        if(this!=&fun)//判断是否为同一个对象
        {
            this->a=fun.a;
            if(fun.p)//判断参数是否为空
            {
                if(this->p)//空间值传递
            	{
                	*(this->p)=*fun.p;
            	}else
            	{
             	   this->p=new int(*fun.p);
           		}
            }else
            {
                if(this->p)
            	{
                	delete this->p;
                    this->p=nullptr;
            	}else
            	{
             	   this->p=nullptr;
           		}
            }
        }
        return *this;
    }
};
```



### 空类中默认提供的函数



- 默认构造函数 

- 默认析构函数 

- 浅拷贝构造函数 

- 默认重载operator=(Fun &fun)

























# 三、基础2



## 1.**头文件 - 源文件**



头文件：**不参与编译**。可写变量的声明、函数的声明、类的定义、宏定义...

- **在头文件中即使写错了，也不会编译报错（当头文件被源文件包含了，写错将报错）**

源文件：**自上而下独立编译**。可写变量的定义、函数的定义、成员定义初始化、类成员函数定义...

区别：使用场景

- **若头文件中放了定义，当有多个文件引用该头文件时，会发生重定义。**



#### --**变量相关**

```c++
//aa.h
//变量的声明，可以声明多次
extern int a; 			//不能写extern int a=0;

//aa.cpp
//变量的定义
int a=10;

//use.cpp
#include"aa.h"
cout<<a;			    //10 
```



#### **--函数相关**

```c++
//aa.h
//函数声明
void ha();

//aa.cpp
#include"aa.h"
//函数定义
void ha(){cout<<1;}

//use.cpp
#include"aa.h"
ha();
```



#### **--类相关**

```c++
//aa.h
//类的声明
class CFun
{
public:
    int m_a;
    const int m_b;
    static int m_c;
    CFun();				//构造函数需声明，才能在其他文件定义
    void show();
    static void play();
    void eat()const;
    virtual void xu();
    ~CFun();
}

//aa.cpp
#include"aa.h"
//类的定义:非静态成员不能在类外部定义
int CFun::m_c=1;				//静态属性
CFun::CFun():m_b(5){m_a=6;}		 //构造函数
void CFun::show(){cout<<m_a;}	 //成员函数
void CFun::play(){cout<<m_c;}	 //静态成员函数   static关键字去掉
void CFun::eat()const{}			 //常函数        const关键字保留
void CFun::xu(){}				//虚函数        virtual、override 关键字去掉
CFun::~CFun(){}				    //析构函数

//use.cpp
#include"aa.h"
int main()
{
    CFun cf;
    cf.show();
}
```



#### **--头文件重复包含**

```c++
//CTest.h
class CTest{public:int a;CTest()};
//CTest.cpp
#include"CTEst.h"
CTest::CTest(){a=5;}
//AA.h
#include"CTest.h"
class CAA{CTest ct;};
//BB.h
#include"CTest.h"
class CBB{CTest ct;};

//main.cpp
#include"AA.h"
#include"BB.h"
int main()
{
    AA aa;			//只有AA时，不会报错
    cout<<aa.ct.a;
    /*BB bb;
    cout<<bb.ct.a;*/	//加上BB时，报错：CTest重定义
}
```

#### **--解决头文件重复包含**

1、在 CTest.h 中加上  #pragma once （告诉编译器，当前头文件在某个源文件中只包含一次）

优点：预处理、编译的速度快。

```c++
//CTest.h
#pragma once
class CTest{public:int a;CTest()};
```

2、基于逻辑宏判断

缺点：宏名字有可能冲突；速度相对慢。

```c++
//CTest.h
#ifndef _CTEST_H_      //如果没有定义宏_CTEST_H_，则进入下面语句
#define _CTEST_H_
class CTest{public:int a;CTest()};
#endif
```







## 2.程序生成过程



#### **1、预处理**：

​		头文件展开（#include）、宏的替换(#define)、预处理命令解析(#ifdef ,#if ,#ifndef ,#else ,#elif ,#endif)、去掉注释

- **查看预处理**：属性 --> c/c++ --> 预处理器 --> 预处理到文件（是） --> 在磁盘的Debug文件夹中的main.i 文件查看**（看完需将属性改回去）**



#### **2、编译**：

​		将预处理后的文件，生成汇编文件 .asm (汇编代码)。

​		词法解析、语法解析、语义分析、优化

- **查看汇编代码**：属性 --> c/c++ --> 预处理器 --> 输出文件 --> 汇编程序输出（带源码的程序集）--> 在磁盘的Debug文件夹中的 main.asm 文件查看



#### **3、汇编**：

​		汇编文件进一步处理，生成目标文件（二进制文件.obj）



#### **4、链接**：

​		将多个目标文件（库文件）链接生成可执行程序(.exe/.out)。







## 3.宏

#### **--宏的作用：替换**

```c++
//aa.h
#define AA 10
//main.cpp
#include"aa.h"
int main()
{
    cout<<AA-4;
}
```



#### **-- 符号\ :连接**

连接当前行和下一行，最后一行一般不加

**注意事项：\后不要有任何字符（空格、tab、注释）**

```c++
#define BB for(int a=0;a<AA;a++){cout<<a;}
//等同于
#define BB for(int a=0;a<AA;a++)\
{\
	cout<<a;\
}
```



#### **--带参数的宏**

```c++
#define CC(NUM) for(int a=0;a<NUM;a++)\
{\
	cout<<a;\
}

int main()
{
    CC(10);
}
```



#### --**函数宏**

```c++
#define mul(a,b) a*b
/*
int mul(int a,int b)
{
	return a*b;
*/
int main()
{
    cout<<mul(1,2)		//2
    //宏是把mul(1,2)替换成了1*2
    cout<<mul(1+3,2)	//7
    //替换成了 1+3*2 ,与预期结果有出入；使用函数宏是应善用()：#define mul(a,b) (a)*(b)
    //#define mul(a,b) ((a)*(b))
}
```



#### -- 符号**##:拼接**

```c++
#define DD()\
int a##b=5;			//将a和b拼接在一起
int main()
{
    DD();
    cout<<ab;		//5
}
```

```c++
#define EE(CLASS,OBJ)\
CLASS OBJ;\
OBJ.show();
//等同于
#define EE(CLASS)\
CLASS obj##CLASS

int main()
{
	EE(CFun)
	OBJCFun.play();
}
```



#### -- 符号#:转字符串

将参数转成字符串，相当于双引号

```c++
#define FF(P)\
cout<<#P<<endl;

int main()
{
    FF(1);//1
    FF(a);//a
}
```



#### -- 符号**#@:**转字符

将参数转成字符，相当于加单引号

```c++
#define GG(P)\
char a=#@P;

int main()
{
    GG(1);
}
```







## 4. operator 重载



**重载操作符operator**：在程序中遇到这个符号，通过调用当前重载操作符函数来行使操作符的功能。

- 一般有返回值，为了和后续的操作符继续操作。

**匹配操作符**：根据重载操作符函数的**参数的类型、顺序、数量**



分类内、类外重载；



#### --类内运算符重载

​		this作为类成员函数的第一个参数，通过当前类对象去调用，一般在操作符左边；可以手动显式的调用函数。

```c++
class CFun1{public: int m;};
class CFun
{
public:
    int m_a;
    CFun()
    {
        m_a=10;
    }
    //+运算符重载
    int operator+(/* CFun *const this */int a)	//双目运算符：只能一个参数
    {
        return m_a+a;
    }
    
    //+=运算符重载
    int operator+=(int a)
    {
        return m_a+=a;
    }
    
    //=
    int operator=(int a)
    {
        return m_a=a;
    }
	
    //参数是另一个对象
    int operator-(CFun1 &cf)		//推荐引用
    {
        return m_a-cf.m;
    }
    
    //++(左++)    单目运算符：没有参数
    int operator++()
    {
        return ++m_a;
    }
    
    //++(右++)    参数无意义，只用来区分左右++
    int operator++(int)    //若传参数进来，值为0
    {
        return m_a++;
    }
};

int main()
{
    CFun cf;
    CFun cf1;
    
    cout<<cf+(cf+3); 		//23	+
    //3+cf;				    //类内重载，不可交换顺序（第一个参数是对象（this））
    cf.operator+(3);		//显式调用
    
    cf+=3;
    cout<<cf.m_a;			//13	+=
    
    cf=cf1=15;
    cout<<cf.m_a<<cf1.m_a;   //15 15  =
    
    cout<<++cf<<" "<<cf.m_a; // 16 15  左++    <<函数：先计算右边，再计算左边
    cout<<cf.m_a;			//16
    
    cout<<cf++;				//16      右++
    cout<<cf.m_a;			//17
    
    CFun1 cf1;
    cf1.m=10;
    cout<<cf-cf1;			//7
}
```





#### --类外运算符重载

​		注意参数列表的顺序；有可能与类内运算符重载函数冲突。

- **要求：参数列表中必须有自定义类型（类、结构体）**

```c++
class CFun{public:int m_a;};
int operator+(int a,CFun &cf)
{
    return a+cf.m_a;
}

int operator+(CFun &cf,int a)		//该函数与类内重载冲突（只能有一个）
{
    return cf.m_a+a;
}



int main()
{
    CFun cf;
    cf.m_a=5;
    cout<<1+cf;					//6        数字是第一个参数
    cout<<cf+1;					//6
}
```



###### 输出操作符重载

```c++
class CFun{public:int m_a;};
ostream& operator<<(ostream &os,CFun &cf)//cout是ostream类型  返回值的目的：连续输出
{
    os<<cf.m_a;
    return os;
}

int main()
{
    CFun cf;
    cf.m_a=5;
    cout<<cf;				//5
}
```



###### 输入操作符重载

```c++
class CFun{public:int m_a;};
istream& operator>>(istream &is,CFun &cf)//cin是istream类型
{
    is>>cf.m_a;
    return is;
}

int main()
{
    CFun cf;
    cin>>cf;
}
```



#### --注意事项

- 对于**同一个操作符**，指定不同的参数类型、顺序、数量，都有**可能产生不同的含义**。
- 参数的类型、顺序、数量，都有一定的约束。
- **重载操作符，参数不能有默认值**；不能改变操作符的使用规则（双目两个参数，单目一个参数）。
- 不能改变操作符的优先级和结合性。
- **有一些操作符只能在类内重载（"="、"->"、"[]"、"()"）**，出于安全考虑。
- **不能重载的操作符（" sizeof "、"? :"、"::"、"."）**
- 不能创建新的操作符。

```c++
class CFun
{
public:
    int m_a;
    CFun()
    {
        m_a=10;
    }
    
    int operator*(int a)		//乘法
    {
        return m_a*a;
    }
    
    int operator*()			    //间接引用
    {
        return m_a;
    }
};

int main()
{
    CFun cf;
    cout<<cf*5;		//乘法
    
    cout<<*cf;		//间接引用:取m_a的值
}
```





#### --对象类型转换（重载类型）

```c++
class CFun
{
public:
    int m_a;
    int* m_p;
    int operator+(int a)	//重载运算符	
	{
    	return m_a+a;
	}
    
    operator int()			//重载int类型:可以使该对象像int一样使用
    {
        /*该处可用其他语句，例如输出*/
        return m_a;
    }
    
    operator bool()			//重载bool类型，可以用来判断
    {
        return m_p;
    }
};

int operator+(int a,CFun &cf)//与类内的类型重载函数不冲突  优先级：重载运算符>重载类型
{
    return a+cf.m_a;
}

void show(int a)
{
    cout<<a;
}

int main()
{
    CFun cf;
    cf.m_a=5;
    cout<<cf+1;					//6
    cout<<1+cf;					//优先匹配类外的运算符重载函数
    
    if(cf){cout<<*m_p;}			//对象当bool用
    
    show(cf);					//对象当int用
    
    int a=cf.operator int()+10;  //显式 调用
}
```







## 5. list - map



### -- list 链表



头文件：

```c++
#include<list>
using namespace std;
```



链表操作（双向链表）：

```c++
list<int> li;		//定义链表  <>中写链表中的数据类型
li.push_back(1);	//尾添加
li.push_front(2);   //头添加
li.pop_back();	    //尾删除
li.pop_front();		//头删除
int a=li.front();	//返回第一个节点的值
int b=li.back();	//返回最后一个节点的值
int c=li.size();	//返回链表长度
bool d=li.empty();	//判断链表是否为空
li.clear();		    //清空链表



//降序的规则函数
bool rule(int a,int b)
{
    return a>b;
}

li.remove(3);		//将值为3的所有节点删除
li.unique();		//将连续且相同值的节点删至一个      1223344  -->  1234
li.sort();			//将链表进行排序，默认升序
li.sort(&rule);		//降序：指定规则函数
li.reverse();		//将链表进行翻转
list<int> li2;		//*********
li2.push_back(1);
li2.push_back(2);
li.splice(++li.begin(),li2);		//剪切：将li2的所有节点剪切到li的第一个节点后，li2为空
li.splice(++li.begin(),li2,li2.begin());//只把li2的第一个节点剪切到li
li.splice(++li.begin(),li2,li2.begin(),li2.end());//[begin,end)剪切到li,等同于第一个****//
li.merge(li2);		//合并：二者必须有序（升序排列），合并后的也升序排列（li2为空）
li.sort(&rule);
li2.sort(&rule);
li.merge(li2,&rule);//降序合并（li2为空）
li.swap(li2);		//交换两个链表



//在指向的节点之前插入，返回插入节点的迭代器(insert)     1 2->1 10 2
list<int>::iterator it=++li.begin();
list<int>::iterator it2=li.insert(it,10);
cout << endl << *it << "  " << *it2 << endl;	//2 10

//删除迭代器指向的节点，该迭代器将失效，返回返回被删节点的下一个节点的迭代器 1 10 2->1 2
list<int>::iterator it3=li.erase(it2);
//cout << *it2 ;
cout << -it3 ;		//2   
```



iterator 迭代器：遍历容器

```c++
list<int>::iterator ite;		//定义迭代器
ite=li.begin();				   //begin()函数，返回头结点的迭代器
```



遍历：

```c++
//1、迭代器法
while(ite!=li.end())			//li.end()指向的是 尾节点后面的无效节点
{
	cout<<*ite<<" ";		   //*ite是<>中的类型
    ite++;					  //是双向链表，迭代器也可以--
}
//----------------------------------------------------------------------------
cout<<*(--li.end());		    //输出尾节点的值
```

```c++
//2、增强的for循环遍历
for(int wal:li)
{
    cout<<val<<" ";
}
```

```c++
//3、算法库中的遍历函数
#include<algorithm>
//功能函数
void show(int v)
{
    cout<<v<<" ";
}
::for_each(li.begin(),li.end(),&show);
```







### -- map 映射表



映射表：k-v 键值对

排序规则：按键值大小自动排序，要求键值不能重复

头文件：

```c++
#include<map>
using namespace std;
```



映射表操作：

```c++
map<int,string> ma;				//<>中第一个参数为键值 第二个参数为实值
ma[2,"haha"];					//直接赋值
ma[1]="hehe";
ma[3,"niha"];
ma[3,"hani"];					//若键值已存在，则修改实值


//插入
pair<int,string> pa(4,"han");	
ma.insert(pa);					//可成功插入
pair<int,string> paa(3,"han");	 //键值3已存在，插入失败
//返回值是键值对，第一个参数是迭代器，第二个参数是bool值
pair<map<int,string>::iterator,bool> p=ma.insert(paa);
if(p.second)
{
    cout<<" 成功";
    cout<<p.first->first;	//p.first是迭代器，->first是映射表的键值
}
ma.insert(make_pair(2, "b"));		//自动转换


//删除,返回被删除键值对的下一个键值对的迭代器
map<int,string>::iterator ite=ma.begin();
ite=ma.erase(ite);
cout<<ite->first; 				//2


//查找
ite=li.find(5);
if(ite!=end())cout<<ite->second;
else cout<<"没找到";


//判断键值是否存在
cout<<li.count(5);				//输出个数 0代表不存在   1代表

int a=ma.size();				//长度
bool b=ma.empty();				//判空
```



pair键值对：

```c++
pair<int,string> pa(4,"han");
```



遍历：

```c++
//迭代器
map<int,string>::iterator ite=ma.begin();
while(ite!=ma.end())
{
    //*ite 是键值对，.first是键值对的第一个值（键值） .second是键值对的第二个值（实值）
    cout<<(*ite).first<<" "<<ite->second<<endl;	//1 2 3 4
    ite++;
}

//for
for(pair<int,string>pa1:ma)
{
    cout<<pa1.first<<" "<<pa1.second<<endl;
}

//for_each
#include<algorithm>
void show(pair<int,string> pa1)
{
    cout<<pa1.first<<" "<<pa1.second<<endl;
}
for_each(ma.begin(),ma.end(),&show);
```









## 6.函数模板



### --泛型编程



​		通用的数据类型和算法，将算法从数据结构中抽象出来，程序写的尽可能通用，用不变的代码完成一个可变的算法。屏蔽掉数据和操作数据的细节，让算法更为通用，让编程者更多的关注算法的结构，而不是在算法中处理不同的数据类型，总之是不考虑具体数据类型的一种编程方式。

​		使用模板需要用到两个关键字 template typename ，写法：template告诉编译器，将要定义一个模板，<>中的是模板参数列表，类似于函数的参数列表，关键字typename看做是变量的类型名，该变量接受类型作为其值，把Type看做是该变量的名称。





### --函数模板



template:定义模板的关键字

typename:定义模板类型的关键字

< >:模板的参数列表

**确定函数模板类型的三种方式：实参自动推导、显式指定、模板类型默认类型**

**优先级**：显式指定>实参自动推导>模板类型默认类型



- **函数的模板类型可以通过实参自动推导，前提在形参列表中使用的模板类型。**

```c++
template<typename T>

//T可以代表任何类型
T add(T t1,T t2)
{
    return t1+t2;
}

int main()
{
    //可以自动识别类型
    int a=1,b=2;
    cout<<add(a,b);
    double c=1,d=2;
    cout<<add(c,d);
}
```

```c++
//下面这种写法，T在add中只能为一种类型：要么都是int,要么都是double
template<typename T>
T add(T t1,T t2);

//下面这种写法，add中可以使任何两个类型的参数
template<typename T,typename K>
T add(T t,K k);
```

​		

​		如果模板类型**不能通过实参进行自动推导**，需要**显式的手动指定**，在函数调用时**从左向右**指定模板参数列表类型。

```c++
template<typename T,typename K,typename F>
T add(T t,K k);

//不能自动识别类型，需手动
//T匹配int K匹配double F匹配char
add<int,double,char>(1,1.2);
```



​		上面那种情况，若模板参数有**默认值**，则不需要手动指定**（随意指定，最好从后往前）**

​		指定模板参数列表的顺序：能通过实参**自动推导出来的放在参数列表最后**，不能自动推导出的（函数体代码，返回值中用到的模板类型），**如果有默认值，放在中间**；没有默认值需要**手动显式指定的放在最前面**。

```c++
template<typename T,typename K,typename F=long>
T add(T t,K k);
add(1,1.2);
```

```c++
template<typename T,typename K=char,typename F>
void show(F f)
{
    cout<<typeid(T).name();
    cout<<typeid(K).name();
    cout<<typeid(F).name();
}
show<double>(10);				 //double char int
show<double,float>(10);			  //double float int
show<double,float,long>(10); 	  //double float long
```



​		**获取模板的实际类型**

```c++
#include<typeinfo>
cout<<typeid(T).name();
```





### --函数模板实例化



​		**实例化**：有一个通用的模板函数，生成具体、确定类型的函数

- 模板函数是否实例化，实例化多少个，取决于实际的函数调用。



#### 隐式实例化：

​		根据函数的实际调用能够自动生成实例化

```c++
template<typename T>
void show(T t)
{
    cout<<typeid(T).name();
}

template<typename T>
void show()
{
    T t=10;
    cout<<typeid(T).name();
}

int main()
{
    show(1);			//int	
    show('a');			//char
    show<double>();		//double
}
```



#### **显式实例化**：

根据确定的类型，实例化一个具体的函数（无论实际是否需要，是否用到）；只需要写具体的声明即可，他是**依赖于通用模板函数，不能独立存在。**

```c++
template<typename T>
void show(T t)
{
    cout<<typeid(T).name();
}
template void show<int>(int);//显式实例化，可以显式指定，但要于参数类型一致，也可以不指定。
```

```c++
template<typename T>
void show()
{
    T t=10;
    cout<<typeid(T).name();
}
template void show<char>();//显式实例化，模板类型不能自动推导，显式指定
```



#### 显式专用化（显式具体化）：

是否用到函数都是存在的，声明和定义都需要。他是**依赖于通用模板函数，不能独立存在。**当匹配时，**优先调用专用化**。

- 对于同模板类型的**显示实例化和专用化**不能同时存在。不同类型的通用模板函数与专用化函数同时存在，专用化优先级高。

```c++
template<> void show(int a)
{
    cout<<1;
}
template<> void show<char>(char a)
{
    cout<<2;
}
```





### --模板函数的重载（专用化）



​		**同类型的全局函数、模板显式专用化函数、通用模板函数可以同时存在**

**优先级**：全局函数 > 专用化 > 通用模板函数

```c++
#include<iostream>
using namespace std;

struct Node
{
	int val;
	Node* next;
	Node(int a)
	{
		val = a;
		next = nullptr;
	}
};

//通用模板
template <typename T>
void swapp(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

//针对于模板类型的专用化
template<> void swapp(Node& a, Node& b)
{
	int c = a.val;
	a.val = b.val;
	b.val = c;
}

//全局函数
void swapp(Node& a, Node& b)
{
	int c = a.val;
	a.val = b.val;
	b.val = c;
}

int main()
{
	int a = 1, b = 2;
	swapp(a, b);
	cout << a << " " << b << endl;
	Node node1(3);
	Node node2(4);
	swapp<>(node1, node2);			//强制匹配模板函数（正常将匹配全局函数）
	cout << node1.val << " " << node2.val;
	return 0;
}
```





### --模板函数的声明



​		**如果模板函数的声明和定义分开，二者处都需要指定模板，才具备通用性。**

声明

```c++
template<typename T>
void show(T t);
```

定义

```c++
//①
template<typename T>
void show(T t)
{
    cout<<t;
}
```

```c++
//②指定类型目标函数实现，不具备通用性
void show<int>(int t)
{
    cout<<a;
}
```



### --注



​		**模板函数并不是真正的函数，只是一个模板；所以不能放到与实际的调用分离的单独的文件中。模板函数的声明和定义放到一起。**











## 7.类模板



```c++
template<typename T>			//类模板
template<class T>				//和上条语句同义
class Fun					   //模板类
{
    T m_t;
    Fun(){m_t=10;}
    void show(T tt){m_t=tt;}
}

int main()
{
    Fun<int> fun;
    cout<<fun.m_t;
}
```

​		

​		可设置**默认值**（**从右向左依次指定，不能间断**），加了默认值后，定义对象时也需**显式指定类型**；如果显式指定和默认同时存在，以**显式指定为准**。

```c++
template<typename T=long>
Fun<> fun;   			//即使使用默认类型，<>也不能省略
cout<<fun.m_t;
```

```c++
template<typename T,typename K=long,typename F=double>
```



​		**类外定义成员函数**

```c++
template<typename T>			
class Fun					  
{
    void show(T t);
    void play();
}

//函数定义
template<typename T>
void Fun<T>::show(T t){}
void Fun<int>::show(int t){}//也可以将模板具体化，但调用时参数只能是int类型，其他类型将报错

template<typename T>		//即使该成员函数没有用到模板，也要写上
void Fun<T>::play(){}
```



​		**成员函数有自己的模板（先类模板，再函数模板）**

```c++
template<typename T>			
class Fun					   
{
    template<typename K>
    void get();
}

//函数定义
template<typename T>
template<typename K>
void Fun<T>::get(){}

int main()
{
    Fun<int> fun;
    fun.get<double>();
}
```



​		**嵌套模板类**

```c++
template<typename T>
class CAA
{
    T aa;
    CAA(T b){aa=b;}
};


class CBB
{
    CAA<int> bb;
    CBB(CAA<int> &a){bb=a;}
};

template<typename K>
class CCC
{
    CAA<K> cc;
    CCC(CAA<K> &a){cc=a;}
};


int main()
{
    //CBB:只能是int类型
    CAA <int> a(10);
    CBB b(a);
    cout<<b.bb.aa;
    
    //CCC：随意指定类型
    CCC<char> c;
    c.cc.aa=65;
    cout<<c.cc.aa;
}
```



































# 四、设计模式



**设计模式（3大类，23种）：**

​		前人总结的经验规则，经过分类，编排形成了一套针对于程序设计的经验总结。是针对于某类重复出现的问题而设计的一套成功有效的解决方案。

- 3类：创建型模式、结构型模式、行为型模式







## 1.单例模式 Sington 



**单例模式 Sington :（创建型模式）**

1.类最多只能创建一个实例

2.类能够自主的创建实例

3.能够向整个系统提供全局的访问接口访问实例



**分类：**

**懒汉式：**不调用就不生成，在第一次使用该实例时，再创建（时间换空间）

- **问题：多线程下可能会创建出来多个对象，解决方法：加锁**

**饿汉式：**程序创建之初，不管用不用这个实例，都提前创建好（空间换时间）

- **在多线程下不会创建出多个实例，不存在多线程下的安全问题**



**优点：**

1.提供了严格的对唯一的实例的创建，访问，销毁，安全性高

2.节约系统资源

### 懒汉式：



```c++
//不完美写法
class CSington
{
private:
	static CSington* pcs;				
	CSington() { m_a = 5; }				//构造函数私有化
	CSington(const CSington& cst){m_a = cst.m_a;}//拷贝构造私有化
    ~CSington(){}						//析构函数私有化
public:
	int m_a;
	static CSington* getSington()		//创建的全局接口	
	{
		if (!pcs)pcs = new CSington;	//只有一个实例
		return pcs;
	}
    
    static void DestroySington(CSington*& psin)		//销毁的全局接口
    {
        if(pcs)
        {
            delete pcs;
            pcs=nullptr;
        }
        psin=nullptr;
    }
};

CSington* CSington::pcs = nullptr;

int main()
{
	CSington* cs= CSington::getSington();
	CSington* cs2= CSington::getSington();
	cout << cs->m_a << "  " << cs2->m_a << endl;
	//若不将拷贝构造私有化，下面语句将创建一个新对象
    //CSington cs3(*cs);
    CSington::DestroySington(cs);//销毁
    //问题：在一个对象中销毁成员后，其他对象不知道
	return 0;
}
```



```c++
//完美写法
class CSington
{
private:			
	CSington() { m_a = 5; }				//构造函数私有化
	CSington(const CSington& cst){m_a = cst.m_a;}//拷贝构造私有化
    ~CSington(){}						//析构函数私有化
public:
	int m_a;
	static CSington* getSington()		//创建的全局接口	
	{
         //静态局部对象，只在第一次创建，在程序退出时自动回收（解决上面的销毁问题）
		static CSington sin;			
         return &sin;
     }
};
```





### 饿汉式：



```c++
class CSington
{
private:
	static CSington sin;				
	CSington() { m_a = 5; }				//构造函数私有化
	CSington(const CSington& cst){m_a = cst.m_a;}//拷贝构造私有化
    ~CSington(){}						//析构函数私有化
public:
	int m_a;
	static CSington* getSington()		//创建的全局接口	
	{
        return &sin;
     }
};
CSington CSington::sin;
```







## 2.工厂模式



​		主要用来集中创建对象，如果在任何使用的地方创建对象那就造成了类或方法之间的耦合，如果要更换对象，那么在所有使用到的地方都要修改一遍，不利于后期的维护，也违背了开闭设计原则。如果使用工厂来创建对象，那么久彻底解耦合了。如果要修改，指出修改工厂类即可。

### **简单工厂**



​		适用于：种类较少、比较固定的情况（解耦合）

```c++
class CEngine{virtual void working()=0;};//发动机
class CEngineA:public CEngine{virtual void working(){cout<<1;}};
class CEngineB:public CEngine{virtual void working(){cout<<2;}};

class CFactory//工厂
{
    CEngine* createEngine(string type)
    {
        if(type=="a")return new CEngineA;
        else if(type=="b")return new CEngineB;
        else return nullptr;
    }
};

class CCar//车
{
    CEngine* m_pEng;//父类发动机指针
    CCar(){m_pEng=new CEngineA;}			//通过无参构造增加发动机
    CCar(string type)						//通过有参构造增加发动机
    {
        if(type=="a")m_pEng=new CEngineA;
        else if(type=="b")m_pEng=new CEngineB;
        else m_pEng=nullptr;
    }
    CCar(CFactory *pFac,string type)		//通过工厂增加发动机（解耦合）
    {
        if(pFac)
        {
           m_pEng =pFac.createEngine(type);
        }else
        {
            m_pEng=nullptr;
        }
    }
    void driving()
    {
        if(m_pEng)
        {
            m_pEng.working();
            cout<<5;
        }
    }
};
int main()
{
    CCar c1;
    c1.driving();
    CCar c2("a");
    c2.driving();
    
    CFactory* pFac=new CFactory;
    CCar c3(pFac,"a");
    c3.driving();
}

```







### 工厂方法模式



​		适用于：种类较少、比较固定的情况（解耦合）

```c++
class CEngine{virtual void working()=0;};//发动机
class CEngineA:public CEngine{virtual void working(){cout<<1;}};
class CEngineB:public CEngine{virtual void working(){cout<<2;}};

class CFactory{virtual CEngine* createEngine()=0;};//工厂
class CFactoryA{virtual CEngine* createEngine(){return new CEngineA;}};
class CFactoryB{virtual CEngine* createEngine(){return new CEngineB;}};

class CCar//车
{
    CEngine* m_pEng;
    CCar(CFactory *pFac)
    {
        if(pFac)
        {
           m_pEng =pFac.createEngine();
        }else
        {
            m_pEng=nullptr;
        }
    }
};
int main()
{
    CFactoryA* pFac=new CFactoryA;
    CCar c1(pFac);
	CFactoryB* pFac1=new CFactoryB;
    CCar c2(pFac1);    
}
```





### 抽象工厂



​		用来解决相对复杂的问题，使用与一系列、大批量的对象生产。

```c++
class CEngine{virtual void working()=0;};//发动机
class CEngineA:public CEngine{virtual void working(){cout<<1;}};
class CEngineB:public CEngine{virtual void working(){cout<<2;}};

class GearBox{virtual void working()=0;};//变速箱
class GearBoxA{virtual void working(){cout<<3;}};
class GearBoxB{virtual void working(){cout<<4;}};

class CFactory//工厂
{
    virtual CEngine* createEngine()=0;
    virtual GearBox* createGearBox()=0;
};

class AA:public CFactory
{
    virtual CEngine* createEngine(){return new CEngineA;}
    virtual GearBox* createGearBox(){return new GearBoxA;}
};

class BB:public CFactory
{
    virtual CEngine* createEngine(){return new CEngineB;}
    virtual GearBox* createGearBox(){return new GearBoxB;}
};

class CCar//车
{
    CEngine* m_pEng;//发动机
    GearBox* m_pBox;//变速箱
    CCar(CFactory* pfac)
    {
        if(pfac)
        {
            m_pEng=pfac->createEngine();
            m_pBox=pfac->createGearBox();
        }else
        {
            m_pEng=nullptr;
            m_pBox=nullptr;
        }
    }
};
int main()				
{
    CFactory*pfac=new AA;
    CCar c1(pfac);
    CFactory*pfacc=new BB;
    CCar c2(pfacc);
}
```













# 五、STL



​		**STL** ：Standard Template Library

**6大组件**：容器(container)、算法(algorithm)、迭代器(iterator)、容器适配器(adapter)、空间适配器(Alloctor)、仿函数（函数对象）(Function object)







## 1.**容器(container)：**



### **序列性容器**



​		保持了元素在容器中的原始顺序，允许指定插入的位置，每个元素都有固定的位置，位置取决于插入的时间、地点。



#### list链表   

```c++
/*链表:
	空间不连续
	在头尾添加删除效率固定（O(1)）
	利用于使用添加删除操作较多的场景
*/

#include<list>
using namespace std;

//降序的规则函数
bool rule(int a,int b)
{
    return a>b;
}

list<int> li;					 //定义链表  <>中写链表中的数据类型
li.push_back(1);				 //尾添加
li.push_front(2);   			 //头添加
li.pop_back();	    			 //尾删除
li.pop_front();					 //头删除
int a=li.front();				 //返回第一个节点的值
int b=li.back();				 //返回最后一个节点的值
int c=li.size();				 //返回链表长度
bool d=li.empty();				 //判断链表是否为空
li.clear();		   			     //清空链表
li.insert(li.begin(),1);	      //在头部插入1
li.erase(++li.begin());		      //删除第二个元素
li.remove(3);			   		 //将值为3的所有节点删除
li.unique();					//将连续且相同值的节点删至一个      1223344  -->  1234
li.sort();						//将链表进行排序，默认升序
li.sort(&rule);					//降序：指定规则函数
li.reverse();					//将链表进行翻转
list<int> li2;					//*********
li2.push_back(1);
li2.push_back(2);
li.splice(++li.begin(),li2);		//剪切：将li2的所有节点剪切到li的第一个节点后，li2为空
li.splice(++li.begin(),li2,li2.begin());//只把li2的第一个节点剪切到li
li.splice(++li.begin(),li2,li2.begin(),li2.end());//[begin,end)剪切到li,等同于第一个****//
li.merge(li2);				//合并：二者必须有序（升序排列），合并后的也升序排列（li2为空）
li.sort(&rule);
li2.sort(&rule);
li.merge(li2,&rule);		//降序合并（li2为空）
li.swap(li2);				//交换两个链表
```



#### vector向量   

```c++
/*向量：
	空间连续，动态数组。
	添加元素如果超过了其容量，申请更大的空间，将原来的元素一一拷贝，释放原来空间。
	在头添加删除效率不定（O(n)），尾添加效率（O(1)）
	定位快，适用于查找等场景
*/

#include<vector>
using namespace std;

vector<int> vec(2);				//容量和使用量都为2，初始化两个元素为当前类型的初值（0）
vector<int>vec2(2,4);			//容量和使用量都为2，初始化两个值为4
vec.size();				   	    //使用量
vec.capacity();			  	    //容量
vec.push_back(1);				//尾添加，使用量和容量都增加（不能头添加：效率低）
vec.pop_back();					//尾删除，使用量减少，容量不变（不能头删除：效率低）
vec.begin();					//返回首元素的迭代器
vec.end()；					   //返回尾元素的迭代器
vec.front();					//返回首元素的值
vec.back();						//返回尾元素的值
vec.insert(vec.begin(),1);		  //在头部插入1（等同于头添加）
vec.insert(vec.begin(),2,4);	  //在头部插入两个4
vec.erase(++vec.begin());		  //删除第二个元素
vec.empty();				     //若向量为空，返回true
vec.clear();				     //清空向量,使用量0，容量不变
vec.resize(2);				     //重新设置向量的大小，若原本使用量大于2，则截取前两个（12）
vec.resize(5,3);			     //扩大容量，指定值为3（12333）
vec.swap(vec2);			         //交换两个向量
vector<vector<int>> vec(a, vector<int>(b));//a个b长度的向量
vec.push_back(vector<int>());//存入一个空的横排

//遍历
//1
vector<int>::iterator ite=vec.begin();		//迭代器
while(ite!=vec.end())
{
    cout<<*ite;
    ite++;
}
//2
for(int a:vec)
{
    cout<<a;
}
//3
for(int i=0,i<vec.size(),i++)
{
    cout<<vec[i];
}
```



#### deque双向队列

```c++
/*双端队列：


*/
#include<deque>
using namespace std;

deque<int> de(10);					//大小为10，数值为0（10个0）
deque<int> de2(10,2);				//大小为10，数值为2（10个2）
de.push_back(1);					//尾添加
de.push_front(2);					//头添加
de.pop_back();						//尾删除
de.pop_front();						//头删除
de.front();							//返回首元素的值
de.back();							//返回尾元素的值
de.insert(de.begin(),1);			 //在头部插入1
//de.insert(de.begin(),2,4);		 //在头部插入两个4(待试)
de.erase(de.begin()+2);				 //删除第三个元素
de.empty();				  		    //若队列为空，返回true
de.clear();				   		    //清空队列
de.size();						    //大小

//遍历
//1
deque<int>::iterator ite=de.begin();
while(ite!=de.end())
{
    cout<<*ite;
    ite++;
}
//2
for(int va:de)
{
    cout<<va;
}
//3
for(int i=0,i<vec.size(),i++)
{
    cout<<de[i];
}
```



### **关联性容器**



​		元素的位置取决于容器特定的排序规则，和插入的值有关。





#### map映射表

​		map的特性是：所有元素都会根据元素的键值**自动被排序**，map的所有元素**都是pair**，同时拥有**键值**(key)和**实值**(value)。pair的第一个元素被视为键值，第二个元素被视为实值。map**不允许两个元素拥有相同的键值**，map的键值关系到map的元素的排列规则，任意改变map元素键值将严重破坏map的组织。所以**不可以通过map的迭代器来改变map的键值**。但是**可以通过迭代器来修改元素的实值。**

```c++
//映射表
#include<map>
using namespace std;

map<string,int> ma;
ma["a"]=1;								//添加
ma["a"]=2;								//修改实值
ma.insert(pair<string,int>("b",3));		  //插入(若插入已存在的键值，插入失败)
ma.erase(map.begin());					 //删除:根据迭代器删除（返回下一个元素的迭代器）
ma.erase("a");							//删除：根据键值删除（返回被移除的元素数）
ma.empty();				  		  		//若为空，返回true
ma.clear();				   		   		//清空
ma.size();							    //大小
ma.find("a");							//查找（返回迭代器，若等于end()说明没找到）
ma.count("a");							//个数（存在：1，不存在：0）
ma.upper_bound("a");					//返回大于该键值的map的迭代器        abcd:b
ma.lower_bound("a");					//返回大于或等于该键值的map的迭代器  abcd:a
//若上面两个语句相等，说明该键值不存在；若不相等，说明存在。


//遍历
map<string,int>::iteator ite=ma.begin();
while(ite!=ma.end())
{
    cout<<*ite.first<<"  "<<*ite.second;
    ite++;
}

//-------------------------
map<string,list<int>> ma;
ma["ha"].push_back(3);

//unordered_map和map的区别：一个有序，一个无序
//map内部实现了红黑树，unordered_map内部时哈希表
//unordered_map查找速率更高些
```







#### set集合

​		所有元素都会根据元素的键值**自动被排序**，set 的元素不像map那样可以同时拥有实值和键值，set元素的**键值就是实值，实值就是键值**。set**不允许两个元素有相同的键值**，因为set元素值就是其键值，关系到set元素的排列规则。如果任意改变set的元素值，会严重破坏set组织。

```c++
//集合
#include<set>
using namespace std;

set<int> se;
se.insert(1);						//插入（若插入已存在的键值，插入失败）
pair<set<int>::iterator,bool> pr=se.insert(1);//返回键值对
se.erase(se.begin());					 //删除
se.empty();				  		  		//若为空，返回true
se.clear();				   		   		//清空
se.size();							    //大小
se.find(1);								//查找（返回迭代器，若等于end()说明没找到）
se.upper_bound(1);						//返回大于该键值的set的迭代器        1234:2
se.lower_bound(1);						//返回大于或等于该键值的set的迭代器  1234:1
*(se.begin());							//返回第一个元素值
//遍历
set<int>::iterator ite=se.begin();
while(ite!=se.end())
{
    cour<<*ite;
    ite++;
}
```





#### hash_map 哈希表

​		基于hash table （哈希表），数据的存储和查找**效率非常高**，几乎可以看做常量时间(O(1))，响应的代价是消耗**更多的内存**。使用一个较大的**数组**来存储元素，经过算法，是的每个元素与数组下标有**唯一的对应关系**，查找时直接定位。

```c++
//unordered_map?
//哈希表
#include<hash_map>
using namespace std;

hash_map<string,int> hm;
hm.insert(pair<string, int>(string("ni"), 1));		//插入
hm.erase(se.begin());					 //删除
hm.find("a");							//查找
hm.begin();								//头迭代器
hm.end();								//尾迭代器
```









## 2.算法(algorithm)



```c++
#include<algorithm>
#include<vector>

vector<int> vec;
vec.push_back(1);
vector<int> vec2;
vec.push_back(1);


int a=::count(vec.begin(),vec.end(),1);				//统计vec从头到尾1的个数
bool b=::equal(vec.begin(),vec.end(),vec2.begin());	 //vec从头到尾与vec2比较
::find(vec.begin(),vec.end(),2);			//查找，返回迭代器（没找到返回范围的最后一个）
::sort(vec.begin(),vec.end());				//排序，默认升序（第三个参数为规则函数）
vector<int> vec5=::max(vec,vec2);			//比较，复制一个大的返回（一个一个比）
vector<int> vec5=::min(vec,vec2);			//比较，复制一个小的返回（一个一个比）
void aa(int a)
{
    cout<<a;
}
for_each(vec.begin(),vec.end(),&aa);		//遍历
```





## 3.迭代器(iterator)



```c++
//用于遍历
#include<list>
using namespace std;

list<int> li;
li.push_back(1);

//正向
list<int>::iterator ite=li.begin();	
while(ite!=li.end())
{
    cout<<*ite;
    ite++;
}

//反向
list<int>::iterator ite=--li.end();	
while(ite!=li.begin())
{
    cout<<*ite;
    ite--;
}
cout<<*ite;

//反向迭代器
list<int>reverse_iterator rev=li.rbegin();//反向头
while(rev!=li.rend())//反向尾
{
    cout<<*rev;
    if(*rev==1)
    {
       li.erase(--rev.base());//将反向迭代器转成正向（移一位）（反向迭代器不能作为删除的参数）
    }
    rev++;
}
```







## 4.容器适配器(adapter)



​		容器适配器即是对特定类封装作为其底层的容器，并提供一组特定的成员函数来访问其元素。容器适配器本质上还是容器，只不过此容器模板类的实现，利用了大量其他基础容器模板类中已经写好的成员函数。当然也可以添加新的成员，它是封装了序列性容器的模板类，它在一般序列性容器的基础上提供了一些不同的功能。之所以成为适配器，是因为它可以通过适配器现有的接口来提供不同的功能，将不适用的序列性容器（包括vector,deque,list）变得适用。容器适配器不支持迭代器、当然也就不能适用算法（algorithm）函数。

​		注：容器适配器默认都是用底层序列性容器实现的。

​		主要包括：stack栈适配器、queue队列适配器

- **不能遍历，无迭代器**



#### stack栈

​		后入先出

```c++
size();
empty();
pop();
push();
top();
```





#### queue队列

​		先进先出

```c++
empty();
size();
back();
front();
pop();
push();
```







## 5.仿函数(Function object)



​		仿函数又称函数对象，是一个能行使函数功能的类。仿函数的语法几乎与我们普通的函数调用一样，不过作为仿函数的类，都必须重载operator()运算符。

```c++
#include<iostream>
using namespace std;

int add(int a,int b)
{
    return a+b;
}

class sub			//仿函数，一个有状态的函数
{
	int operator()(int a,int b)
    {
        return a-b;
    }
};

int main()
{
    cout<<add(10,20);
    sub s;
    cout<<s(20,10);
    
    return 0;
}
```











# 六、c++11特性





## *



```c++
//可以用{}给任意类型变量初始化
struct T{int a};
int a{2};				//a=2;
T t{5};					//结构体中a=5
```













## 1.原始字面量



​		在c++11中添加了定义**原始字符串**的**字面量**，定义方法为：**R"xxx(原始字符串)xxx**"，其中()两边的字符串xxx在编译时会**被忽略**，**可做备注用，两边必须相等，也可以省略**（不可以写中文）。原始字面量R可以直接表示字符串的实际含义，而**不需要额外对字符串做转义或连接等操作。**



语法：R"()";

```c++
//取代转义
string a = "D:\hello\world\test.txt";
cout << a << endl;					//D:helloworld    est.txt(\为转义字符，\t制表符)

a = "D:\\hello\\world\\test.txt";
cout << a << endl;					//D:\hello\world\test.txt(第一个\为转义字符)

a = R"(D:\hello\world\test.txt)";
cout << a << endl;					//D:\hello\world\test.txt
```

```c++
//取代连接
a = "a\
b\
c\
";
cout << a << endl;					//abc(换行赋值需加转义字符)

a = R"(a
b
c)";
cout << a << endl;					//a换行b换行c（用原始字面量不需要加转义字符，但会有换行）
```

```c++
//xxx
a = R"ha(nihao)ha";
cout << a << endl;					//nihao
```















## 2.指针空值类型-nullptr

​																		**见第一章基础第六节**

















## 3.×常量表达式-constexpr



### const



​		**const**的双重语义：**变量只读、修饰常量**。

```c++
void show(const int num)
{
	int a = 5;
	const int b = 6;
	//int c[a];							vs变量不可以给数组初始化
	int c[b];							//常量可以给数组初始化
	//int c[num];						此处num为只读，不算常量
}
```



### constexpr



​		**constexpr**:用来修饰**常量表达式**（多个常量进行加减乘除等运算，最终结果还是常量）、**常量函数**（返回值是常量）。

- 常量表达式和非常量表达式的区别：**计算时机不同**，非常量表达式在**运行期**进行计算，常量表达式在**编译期**计算出结果，可提高运行效率。

```c++
//在修饰常量时，既可以使用const，也可以使用constexpr（推荐）
const int m=f();			//不是常量表达式，m的值只有在运行时才会获取
const int a = 1;			//常量表达式
const int b = a + 1;		//常量表达式

constexpr int c = 1;		//常量表达式
constexpr int d = c + 1;	//常量表达式
```



​		constexpr可以修饰**基本数据类型**，不能修饰**自定义类型（结构体、类）**

```c++
//下面写法非法
constexpr struct a
{
    int b;
    int c;
};
```

​		可修饰对象

```c++
struct T
{
    int a;
    int b;
};
constexpr T t { 5 , 6 };
//t.b=5;					不能修改
```



### 常量表达式函数(有些不适用)



​		可用 constexpr **修饰函数的返回值**，这种函数称为**常量表达式函数**。主要包括：**普通函数/类成员函数、类的构造函数、模板函数。**



#### 修饰函数

constexpr 修饰函数的**要求**：

1. 函数必须要有**返回值**，并且return 返回的表达式必须是**常量表达式**

```c++
//错
constexpr void fun(){cout<<1;}
//(vs2019编译通过？？？？)
constexpr int fun1(){int a=5;return a;}
```

2. 函数在使用之前，必须有对应的定义语句

```c++
```





















## 4.自动类型推导





​		**可以使用auto自动推导变量的类型，还能够结合decltype来表示函数的返回值。**





#### auto：

​		c++11中auto并不代表一种实际的数据类型，只是一个类型声明的**“占位符”**，auto并**不是**万能的在任意场景下都能够推导出变量的实际类型，使用auto声明的变量**必须要进行初始化**，以让编辑器推导出它的实际类型，在编译时将auto占位符**替换为真正的类型。**

```c++
auto 变量名=变量值;
```

```c++
auto a=1;		//a是int型
auto b=3.14;	//b是double
auto c='a';		//c是 char
//auto d;		必须赋初值
//auto int b;	不能修改类型
```



​		auto还可以和**指针、引用**结合起来使用；也可以带上 **const 、volatile** 限定符，推导规则如下：

***const修饰常量，volatile修饰变量***

- 当变量**不是**指针或者引用类型时，推导的结果中**不会**保留auto、volatile关键字
- 当变量**是**指针或者引用类型时，推导的结果中**会**保留auto、volatile关键字

```c++
auto a=3;		//auto:int
auto b=&a;		//auto:int*
auto* c=&a;		//auto:int
auto& d=a;		//auto:int
auto e=a;		//auto:int
```

```c++
int a=3;
const auto b=a;		//b:const int
auto c=b;			//c:int

const auto d=a;		//d:const int
auto &e=d;			//e:const int &
auto *f=&d;			//f:const int *
```





#### **auto的限制：**

auto关键字并不是万能的，在一下场景中是不能完成类型推导的。



1. **不能作为函数参数使用**。因为只有在函数调用的时候才会给函数参数传递实参，auto要求必须给修饰的变量赋值，因此二者矛盾。

```c++
//void fun1(auto a,auto b){}

//可以在返回值明确的情况下，做返回值
auto fun() { return 1; }			//int fun()
```

2. 不能用于类的**非静态成员变量**的初始化。

```c++
class T
{
    //auto a=10;
    //static auto a=10;		类的静态非常量成员不可以在类内直接初始化
    const static auto a=10;
    int b=5;
};
```

3. 不能使用auto关键字定义数组。

```c++
int a[] = { 1,2,3,4,5 };
//auto b[] = { 1,2,3,4,5 };
//auto b[] = a;
auto b = a;						//b:int*
```

4. 无法使用auto推导出模板参数。

```c++
template<typename T>
struct test{};
test<int> t;
//test<auto> t1;				//不能用auto
```







#### auto的应用：

1. 用于STL的容器遍历

```c++
//make_pair() 自动转换
map<int, string> ma;
ma.insert(pair<int, string>(1, "a"));
ma.insert(make_pair(2, "b"));
map<int, int> maa;
maa.insert(make_pair(1, 1));

//遍历(1)			it:迭代器
auto it = ma.begin();
while (it != ma.end())
{
	cout << it->first << " " << it->second << endl;
	it++;
}

//(2)				it:键值对
for (auto it : ma)
{
	cout << it.first << " " << it.second << endl;
}
```

2. 用于泛型编程

```c++
class T1
{
public:
	static int get() { return 1; }
};

class T2
{
public:
	static string get() { return "haha"; }
};

template<class T>
void fun()
{
	auto a=T::get();			//get返回的类型不确定
	cout << a << endl;
}

fun<T1>();				//1
fun<T2>();				//haha
```







#### decltype:

​		decltype 是 "declare type" 的缩写，意思是 **“声明类型”** 。decltype 的推导是在**编译期**完成的，它只是用于表达式**类型**的推导，并不会计算表达式的值。

```c++
int a = 10;
decltype(a) b;			//b:int
decltype(a+1.0) c;		//c:doubleZ
```





#### decltype的推导规则：

1. 表达式为**普通变量**或者**普通表达式**或者**类表达式**，在这种情况下，使用 decltype 推导出的类型和表达式的**类型是一致的**。

```c++
class T
{
public:
	static char a;
};
int a = 10;
const int& b = a;

decltype(a) c;				//c:int
decltype(b) d=a;			//d:const int &
decltype(T::a) e;			//e:char
```

2. 表达式是**函数调用**，使用 decltype 推导出的类型和**函数返回值**一致。

```c++
int fun1(){}
int& fun2(){}
int&& fun3(){}
const int fun4() {}		//const int 返回右值（纯数值）
const int& fun5() {}
const int&& fun6(){}
const T fun7(){}

int n = 1;
decltype(fun1()) a;				//a:int
decltype(fun2()) b=n;			//b:int&
decltype(fun3()) c=1;			//c:int&&
decltype(fun4()) d;				//d:int		返回纯右值，const\volatile忽略
decltype(fun5()) e=n;			//e:const int&
decltype(fun6()) f=1;			//f:const int&&
decltype(fun7()) g;				//g:const T
```

3. 表达式是一个**左值**，或者被**括号 () 包围**，使用 decltype 推导出的是**表达式类型的引用**（如果有const、volatile 限定符**不能省略**）。

```c++
class T
{
public:
	int a;
};

const T t;
decltype(t.a) a=0;				//a:int（根据第一条推导）
decltype((t.a)) b=a;			//b:const int&（根据第三条）

int m=0,n=1;
decltype(n+m) a=0;				//a:int(不是左值)
decltype(n=n+m) b=a;			//b:int& （是左值）
decltype(n) c=0;				//c:int（是左值，也是普通表达式；优先第一条）
```





#### decltype的应用：

​		应用在泛型编程中：

```c++
//遍历T容器
template<typename T>
class Test
{
public:
    void print(T &t)
    {
        for(ite=t.begin();ite!=t.end();ite++)
        {
            cout<<*ite<<endl;
        }
    }
private:
    //T::iterator ite;			t的类型无法确定
    decltype(T().begin()) ite;  //推导出迭代器类型
};

int main()
{
    list<int>li{1,2,3,4,5,6};
    Test<list<int>> t;
    t.print(li);
}
```





#### 返回类型后置：

​		c++11特性，c++14已改

```c++
template<typename T,typename Y>
//可不用多设一个模板参数存放返回值
auto add(T a,Y b)->decltype(a+b)
{
    return a+b;
}
//c++14后可直接使用auto，不需要decltype推导
auto add(T a,Y b)
{
    return a+b;
}
```

















## 5. final 和 override



#### final:

- 放在类或函数的后面

​		使用final修饰函数，只能修饰**虚函数**；可**阻止子类重写**父类的这个虚函数。

```c++
//1.不能在father类的虚函数添加final关键字
//2.不能在非虚函数添加final关键字
class father{public:virtual void fun(){}};
class son:public father
{
    void fun()final{}
};
class sonson:public son
{
    //void fun(){}
};
```



​		使用final修饰类，该类**不能被继承**

```c++
class father{public:virtual void fun(){}};
class son final:public father
{
    void fun()final{}
};
//class sonson:public son{};
```



#### override:

​		可用于判断当前函数是否重写父类的虚函数，提高可读性

```c++
class father{public:virtual void fun(){}};
class son final:public father
{
    void fun()override{}
    //void funn()override{}			报错
};
```



















## 6. using 的使用



### 起别名



```c++
typedef int int1;
int1 a=1;

using int2=int;
int2 b=1;
```



### 修饰函数指针（提高可读性）



```c++
typedef int(*fun1)(int,char);
using fun2=int(*)(int,char);

int fun(int,char){}

fun1 f1=&fun;
fun2 f2=&fun;
f1(1,'a');
f2(1,'a');
(*f1)(1,'a');
(*f2)(1,'a');
```



### 使用typedef给模板定义别名



```c++
template<typename T>
struct Mymap
{
    typedef map<int,T> mmap;//不能单独在外部用typedef定义map别名
};
Mymap<int>::mmap m1;//map<int,int>
Mymap<string>::mmap m2;//map<int,string>

m1.insert(make_pair(1,1));
m2.insert(make_pair(1,"a"));

//遍历
template<typename T>
class container
{
public:
    void print(T &t)
    {
        auto a=t.begin();
        for(;a!=t.end();a++)
        {
            cout<<a->first<<" "<<a->second<<endl;
        }
    }
};

container<Mymap<int>::mmap> c;
c.print(m1);
```





### 使用using给模板定义别名



```c++
template<typename T>
using mmap=map<int,T>;

mmap<string> mm3;
mm3.insert(make_pair(1,"haha"));
//遍历函数同上
container<mmap<string>> c;
c.print(mm3);
```























## 7.委托构造函数和继承构造函数





### 委托构造函数



​		**委托构造函数**允许使用同一个类中的一个构造函数调用其他的构造函数，从而简化相关变量的初始化。

```c++
class T
{
    int a;
    int b;
    int m;
    T(){}
    T(int max){a=max;}
    T(int max,int min):T(max){b=min;}
    T(int max,int min,int mid):T(max,min){m=(a+b)/2;}
};
```

注意事项：

​		1.这种链式的构造函数调用不能形成一个闭环（死循环），否则会在运行期报异常。

​		2.如果要进行多层多层构造函数的链式调用，建议将构造函数的调用写在初始化列表中而不是函数体内部，否则编译器会提示形参的重复定义。

​		3.在初始化列表中调用了代理构造函数初始化某个类成员变量之后，就不能再初始化列表中再次初始化这个变量了。

```c++
//T(int max,int min):T(max),max(5){b=min;}	错误
```









### 继承构造函数



​		1.子类可直接使用父类的构造函数(using Father::Father)

原：

```c++
class A
{
public:
	int a;
	A(int b):a(b){}
};

class B :public A
{
public:
	B(int b):A(b){}//需显式调用父类的构造函数
};
```

今：

```c++
class A
{
public:
	int a;
	A(int b):a(b){}
};

class B :public A
{
	using A::A;
};
//main
B b(1);
//可直接在主函数使用父类的所有构造函数
```



​		2.子类可以使用父类被隐藏的方法

```c++
class A{func(int a){} func(int a,int b){}};
class B:public A{func(){}/*父类的同名函数被隐藏了*/};
B b;
//b.func(1);    报错
```

```c++
class A{func(int a){} func(int a,int b){}};
class B:public A
{
    using A::func; 
    func(){}
};
B b;
b.func(1);		//可
```























## 8.列表初始化



### 		c++11之前的初始化（数组、结构体）

```c++
int a[5]={1,2,3,4,5};
double b[]={1.1,2.2};
struct a
{
    int aa;
    char bb;
}newa{5,'a'};//newa为对象名
```



### c++11

```c++
class a
{
    int b;
    double c;
    a(int bb):b(bb){}
    a(int bb,double cc):b(bb),c(cc){}
};
//main
a a1(1);//构造函数
a a2 = 1;//隐式类型转换
//初始化列表
a a3 = { 1 };
a a4{ 1 };
a a5{ 1,1.1 };
```

```c++
int a{5};
int a[5]{1,2,3,4};
int *a=new int{5};
int a=int{5};
int *a=new 
```







### 列表初始化细节



#### 聚合体类型

​		**聚合体类型可直接使用大括号赋值**，非聚合体不能使用大括号赋值。



普通数组本身可以看成一个聚合体

```c++
int a[]={1,2,3,4,5};
```

满足以下条件的类（struct class union），可以被看做是一个聚合类型

- 无用户自定义的构造函数
- 无私有或保护的非静态成员
- 无基类
- 无虚函数
- 类中不能有使用{}或=直接初始化的非静态数据成员（c++14开始就支持了）

```c++
//1.类中有私有成员，无法使用列表初始化
struct s1
{
    int aa;
    double b;
private:
    int c;
}news{1};//error

struct s1
{
    int aa;
    double b;
//private:
    int c;
}news{1};//可

//2.类中有静态成员，可以使用初始化列表初始化；但不能初始化静态成员（类外::初始化）
struct s2
{
    int a;
    double b;
protected:
    static int c;
}news2{1,2,3};//error

struct s2
{
    int a;
    double b;
protected:
    static int c;
}news2{1,2};//可
int s2::c=3;
```









#### 非聚合类型

​		不是聚合体类型的为非聚合体类型



​		当类中有私有成员时，不能使用{}初始化，当类中有自定义构造函数时，不能使用{}初始化；但当二者结合起来，就可以使用{}初始化 

```c++
struct s1
{
    s1(int a1,double a2,int a3){aa=a1;b=a2;c=a3;}
    int aa;
    double b;
private:
    int c;
}news{1,1,1};//可

s1 haha()
{
    return {1,1,1};//可（调用构造函数）
}
```







#### 注意

​		聚合类型的定义是非递归的，即若一个类中包含了非聚合类型的对象，这个类可能是聚合类型也可能是非聚合类型

```c++
struct s8
{
    //s8(int a){}     若写上该条语句，s4的初始化将失败
    int aa=1;
    double b;
private:
    int c;
};

//s4包含了非聚合类型s8的对象，但s4符合聚合类型的要求，所以s4是聚合类型
//注：在初始化列表中初始化非聚合对象时，直接写空{}即可（调用了s8的无参构造函数，若无参构造不存在，将失败，若只有有参的构造函数，在{}中添加参数也可完成初始化）
struct s4
{
    s8 s;
    int a;
}news4{{},1};//可
```







### std::initializer_list



- 是一个轻量级的容器类型，内部定义了迭代器iterator等容器必须的概念，遍历时得到的迭代器是只读的
- 对于std::initializer_list<T>而言，它可以接收任意长度的初始化列表，但是要求元素必须是同种类型T
- 在STD::initializer_list内部有三个成员接口：size() begin() end()
- std::initializer_list对象只能被整体初始化或者赋值

```c++
//用于参数
void hai(initializer_list<int> in)
{
    auto ite = in.begin();
    while (ite != in.end())
    {
        cout << *ite << " ";
        ite++;
    }
}
//main
hai({ 1,2,3,4,5,6 });

//用于成员初始化
struct s9
{
    vector<int>vec;
    s9(initializer_list<int> in)
    {
        auto ite = in.begin();
        while (ite != in.end())
        {
            vec.push_back(*ite);
            ite++;
        }
    }
};
```

























## 9.基于范围的for循环





​		语法格式：

```c++
//declaration表示遍历声明，在遍历过程中，当前被遍历到的元素会被存储到声明的变量中。expression是要遍历的对象，它可以是表达式、容器、数组、初始化列表等。
for(declaration:expression)
{
    //循环体
}
```



​		例：

```c++
#include<vector>
vector<int>vec{1,2,3,4,5,6,7};

for(auto &a:vec){//推荐使用引用：可提高效率（不加引用为拷贝数据），还可通过a修改容器内的值
    cout<<a;
}

for(auto &a:vec){
    cout<<a++;//vec容器内的每个值都+1
}

for(const auto &a:vec){
    cout<<a;//只读，不能更改容器内的值
}
```



### 使用细节





#### 关系型容器

​		对关系型容器**map**（有k-v结构）的遍历：

```c++
//使用普通的for循方式（基于迭代器）遍历关联性容器，auto自动推导出的是一个迭代器类型，需要使用迭代器的方式取出元素中的键值对（和指针的操作方法相同）
for(auto a=ma.begin();a!=ma.end();a++){
    cout<< a->first << a->second ;
}

//使用基于范围的for循环遍历关联性容器，auto自动推导出的类型是容器中的value_type，相当于一个数组对象，提取键值对的方式为.
for(auto &a:ma){
    cout<< a.first << a.second ;
}
```





#### 元素只读

​		通过基于范围的for循环语法的介绍可以得知，在for循环内部***声明一个变量的引用就可以修改遍历的表达式中的元素的值***，但是这并不适用于所有的情况。**对于 set 容器来说，内部元素都是只读的，这是由容器的特性决定的，因袭在foe循环中 auto& 会被视为 const auto & 。**

```c++
for(auto &a:sett){
    //cout<<a++;	error
    cout<<a;
}
```

​		对于关联型容器map，其键值也是自带只读属性，不能更改；但是可更改实值。

```c++
for(auto &a:mapp){
    //cout<<a.first++;	error
    cout<<a.second++;	//可
}
```





#### 访问次数

​		在使用基于范围的for循环时，后面的遍历对象只会被**访问一次**：首先确定对象中有多少个元素，以确定循环次数，基于该次数去在对象内进行循环。

- 使用正常的for循环时，每次循环都要判断一下边界；而基于范围的for循环在第一次就把边界找好了。

```c++
//可用来判断访问次数
vector<int>vec{1,2,3,4,5,6};
vector<int>& getvec(){
    cout<<"访问啦！";
    return vec;
}
//main
for(auto &a:getvec()){
    cout<<a<" ";
}
```



























## 10.可调用对象包装器、绑定器



​		**可调用对象：可以像函数一样被调用的对象**

### 可调用对象



#### 函数指针

```c++
using a=void (*)(int);
void b(int c){}
a aa=&b;
```





#### 重载（）操作符

​		重载了（）操作符的类对象（仿函数）

```c++
class sub			//仿函数，一个有状态的函数
{
	int operator()(int a,int b)
    {
        return a-b;
    }
};
sub s;
cout<<s(20,10);
```





#### 可被转换为函数指针的类对象

​		重载类型

```c++
//重载类型
class A{
    operator int(){
        return 1;
    }
};
int main(){
    A aa;
    cout<<aa;//1
}

//将对象转换为函数指针
using a=void(*)(int,string);
class A{
    operator a(){//将对象重载为函数指针a
        return fun2;//函数应为静态的，因为非静态函数与对象挂钩。
        //return fun1;   error
    }
    void fun1(int i,string s){}
    static void fun2(int i,string s){}
};
A aa;
aa(1,"haha");//调用fun2函数
```





#### 类成员函数指针或类成员指针

```c++
//类的函数指针
using p=void(*)(int);//普通函数指针
p p1=cla::stafun;//可以指向类内的静态函数
p p2=cla::fun;   //error,不能指向普通成员函数

using pp=void(cla::*)(int);//类成员函数指针
pp p3=cla::fun;	 //可以指向普通成员函数,但不能指向静态成员函数

//类的成员指针
using pint=int cla::*;
pint p1=&cla::a;

cla c;
(c.*p3)(1);
c.*p1;
```



### 可调用对象包装器



​		std :: function 是可调用对象的包装器。它是一个模板类，可以容纳除了类成员（函数）指针之外（需借助绑定器）的所有可调用对象。通过指定它的模板参数，它可以用同意的方式处理函数、函数对象、函数指针，并允许保存和延迟执行它们。

​		用法：包含一个叫做 functional 的头文件

```
#include<functional>
std::function<返回值类型(参数类型列表)>diy_name=可调用对象;
```

```c++
#include<functional>
using namespace std;
//包装普通函数
void fun1(int a){}
function<void(int)> ion1=fun1;

//包装类的静态函数
class cla1{public:static void fun(int,string){}};
function<void(int,string)> ion2=cla1::fun;

//包装仿函数
class cla2{public:void operator()(int){} };
cla2 cl1;
function<void(int)>ion3=cl1;

//包装转换为函数指针的对象
using p=void(*)(int);
class cla3{public:operator p(){return fun;} void fun(int a){}};
cla3 cl2;
function<void(int)>ion4=cl2;


//调用
ion1(1);
ion2(1,"ha");
ion3(2);
ion4(3);


//应用
class A{
    public:
    A(function<void(int)>&f):callback(f){}
    void notify(int a){
        callback(a);
    }
    private:
    function<void(int)> callback;
}
//传普通函数
A aa(fun1);
aa.notify(1);
//传静态函数（由于静态函数设置了两个参数，不能在A类中使用）
A ab(cla1::fun);
//传仿函数
A ac(cl1);
ac.notify(2);
//传转换为指针的对象
A ad(cl2);
ad.notify(3);
```





### 可调用对象绑定器



​		std::bind 用来将可调用对象与其参数一起进行绑定。绑定后的结果可以使用std::function 进行保存，并延迟调用到任何我们需要的时候。通俗来讲，有两大作用：

1. 将可调用对象与其参数一起绑定成一个仿函数。
2. 将多元（参数个数为n,n>1）可调用对象转换为一元或者（n-1）元可调用对象，即只绑定部分参数。

```c++
//绑定非类成员函数/变量
auto f=std::bind(可调用对象地址，绑定的参数/占位符);
//绑定类成员函数/变量
auto f=std::bind(类函数/成员地址，类实例对象地址，绑定的参数/占位符);

//std::bind绑定器返回的是一个仿函数类型，得到的返回值可以直接复制给一个std::function，在使用的时候我们并不需要关心绑定器的返回值类型，使用auto进行自动类型推导就行了。
//placeholders::_1是一个占位符，代表这个位置将在函数调用时被传入的第一个参数所替代。同样还有其他的占位符placeholders::_2\placeholders::_3\...
```

```c++
#include<functional>
using namespace std;
void output(int a,int b){cout<<a<<" "<<b;}
int main(){
    //使用绑定器绑定调用对象和参数，并调用得到的仿函数(_1会在参数中找第一个参数替换，_2会在参数中找第二个参数替换)
    bind(output,1，2)();//1 2
    bind(output,placeholders::_1,2)(10);//10 2
    bind(output,2,placeholders::_1)(10);//2 10
    
    //bind(output,2,placeholders::_2)(10);   error 调用时没有第二个参数
    bind(output,2,placeholders::_2)(10,20);//2 20  调用时第一个参数10被吞掉了，没有被使用
    bind(output,placeholders::_1,placeholders::_2)(10,20);//10 20
    bind(output,placeholders::_2,placeholders::_1)(10,20);//20 10
}

//应用
void test_func(int a,int b,const function<void(int,int)>&f){
    if(a%2==0)f(a,b);
}
void output_add(int a,int b){
    cout<<a<<" "<<b;
}

int main(){
    for(int a=0;a<10;a++){
        //在绑定器中指定了参数，调用时参数不会改变
        auto f=bind(output_add,a+100,a+200);
        test_func(a,a,f);// 100 200 102 202...
        //在绑定器中使用了占位符，传进来的参数可以传进函数中
        auto f1=bind(output_add,placeholders::_1,placeholders::_2);
        test_func(a,a,f);//0 0 2 2 ...
    }
}

//绑定类成员函数/变量
class A{
    public:
    void fun(int a,int b){}
    int m_a;
};
//成员函数绑定
A a;
auto f1=bind(&A::fun,&a,2,placeholders::_1);
//包装成员函数
function<void(int,int)>ion1=bind(&A::fun,&a,2,placeholders::_1);//类型和f1不一样，f1是仿函数，ion1是把仿函数进行包装的包装器
f1(5);//2 5
//成员变量绑定
auto f2=bind(&A::m_a,&a);
//包装成员变量
function<int&(void)>ion2=bind(&A::m_a,&a);//要可读（返回值位变量类型）可写（加引用）
cout<<f2();//输出成员变量的值
f2()=100;//修改成员变量的值
cout<<f2();//100
```













## 11. Lambda表达式



**优点：**

- 声明式的编程风格：就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或函数对象。
- 简洁：避免了代码膨胀和功能分散，让开发更加高效。
- 在需要的时间和地点实现功能闭包，使程序更加灵活。



**Lambda表达式定义了一个匿名函数，并且可以捕获一定范围内的变量。语法：**

```c++
[capture](params)opt->ret{body;};
//调用：后面加(),如果有形参，在()中写形参
[](int a){cout<<a;}(9);
```



**介绍：**

1. **capture** : 捕获列表。捕获一定范围内的变量

```c++
//捕获变量的方式
[]:不捕获任何变量
[&]:捕获外部作用域中的所有变量，并作为引用在函数体内使用（按引用捕获）
[=]:捕获外部作用域中所有变量，并作为副本在函数体内使用（按值捕获）
*拷贝的副本在匿名函数体内部是只读的
[=,&foo]:按值捕获外部作用域中所有变量，并按照引用捕获外部变量foo
[bar]:按值捕获bar变量，同时不捕获其他变量
[&bar]:按引用捕获bar变量，同时不捕获其他变量
[this]:捕获当前类中的this指针

int a=5,b=10;
[=](){int c=a,d=b;};

class test {
public:
	int m_int=9;
	void fun(int x, int y) {
        //auto x1 = [] {return m_int; };    error，没有捕获this，不能使用成员变量
        auto x2 = [=] {return m_int + x + y; };     //ok，以值传递的方式拷贝所有外部变量（包括类成员变量）
        auto x3 = [&] {return m_int + x + y; };     //ok，以引用传递的方式拷贝所有外部变量（包括类成员变量）
        auto x4 = [this] {return m_int; };          //ok，捕获this指针，可以使用内部成员
        //auto x5 = [this] {return m_int + x + y; };    error，没有捕获x,y
        auto x6 = [this, x, y] {return m_int + x + y; };//ok,都捕获了
        auto x7 = [this] {return m_int + 1; };      //ok，可以使用
        [this] {return m_int++;}();      //9,捕获this时可以修改对象内部成员变量
        cout << m_int;                   //10
	}
};
```

2. **params** : 参数列表。和普通的参数列表一样，如果没有参数列表可以省略不写

```c++
auto a=[](){return 1;};
auto b=[]{return 1;};
//调用
void fun(int a, int b) {//5 6
    [=, &b] {
        cout << ++b << endl;                //7
        //cout<<++a;//error ,a是值捕获，只读，不可更改
    }();
    
    [](int c){//带参数的调用
        cout << c << endl;                   //20
    }(20);
}
```

3. **opt**     : 函数选项。不需要可以省略

> mutable : 可以修改按值传递进来的拷贝（注意是修改拷贝，不是值本身）
>
> exception : 指定函数抛出的异常，如抛出整数类型的异常，可以使用throw();

```c++
void fun(int a, int b) {5 5
    [=, &b]()mutable{//使用opt时，形参的()不能省略
        cout << ++b << endl;                  //6
        cout << ++a << endl;  //ok,mutable可以修改形参的拷贝，而不是本身      6
    }();
    cout << a << " " << b << endl;            //5 6
}
```

4.  **ret**     : 返回值类型。在c++11中，lambda表达式的返回值是通过返回值后置语法来定义的

```c++
//指定返回值时参数列表的()不能省略
//若lambda匿名函数没有调用，则不会将值返回，变量不能输出
auto a = []{return 1; }();  //int
auto b = []()->double {return 1; }(); //double
//注：初始化列表不能自动推导
//auto c = [] {return { 1,2 }; }();
```

5. **body**   : 函数体。函数的实现，这部分不能省略，但可以为空。

```c++
[](){};
```



**本质：**

1. lambda表达式的类型在c++11中会被看作是一个带operator()的类，即仿函数。
2. 按照c++11标准，lambda表达式的operator()默认是const的，一个const成员函数时无法修改成员变量值的。

```c++
//可用函数指针指向匿名函数（lambda函数），要求匿名函数不能捕获任何变量
using ptr=void(*)(int);
ptr p1=[](int a){cout<<a<<endl;};
p1(12);
//ptr p2=[=](int a){cout<<a<<endl;};	捕获了，只是一个仿函数

//包装lambda表达式
function<void(int)>f1=[=](int a){cout<<a<<endl;};
f1(13);

//绑定成仿函数并保存到包装器
function<void(int)>f2=bind([=](int a){cout<<a<<endl;},
                          placeholders::1);
f2(14);
```









## 12.右值引用



### 右值和右值引用



**右值：**

​		c++11增加的新类型，称为右值引用，标记为&&。

- lvalue是locator value的缩写，rvalue是read value的缩写
- 左值是指存储在欸村中，有明确存储地址（可取地址）的数据。
- 右值是值可以提供数据值的数据（不可取地址）。

```c
//左值
int num=9;
//左值引用
int& a=num;
//右值引用
int&& b=5;
//int&& c=b;		error
//常量右值引用
const int&& d=6;
//const int&& e=b;		error
//常量左值引用(各种类型的变量都可以用来初始化左值引用)
const int& g=num;
const int& h=b;
const int& i=d;
```





### 右值引用的作用













## 13.转移和完美转发







## 14.共享智能指针







## 15.独占智能指针







## 16.弱引用智能指针

















# 问题与答案



## c和c++的区别



- c++是面向对象的语言，c是面向过程的语言
- c++引入new/delete运算符，取代了c的malloc/free库函数
- c++引入引用的概念，c中没有
- c++引入类的概念，c中没有
- c++引入函数重载的特性，c没有





## static关键字的作用



- 修饰局部变量时，使该变量在静态存储区分配内存；只能在首次函数调用中进行首次初始化，之后的函数调用不再进行初始化；生命周期与程序相同，但作用域为局部作用域，不能一直被访问。
- 修饰全局变量时，使该变量在静态存储区分配内存；在声明该变量的整个文件中都是可见的，而在文件外是不可见的。
- 修饰函数时，在声明该函数的整个文件中都是可见的，而在文件外是不可见的，从而可以在多人协作时避免同名的函数冲突。
- 修饰成员变量时，所有的对象都只维持一份拷贝，可以实现不同对象间的数据共享；不需要实例化对象即可访问；不能在类内部初始化，一般在类外部初始化，并且初始化时不加static。
- 修饰成员函数时，该函数不接受this指针，只能访问类的静态成员；不需要实例化对象即可访问。







## 结构体可以直接赋值吗



​		声明时可以直接初始化，同一结构体的不同对象之间也可以直接赋值，但是当结构体中含有指针“成员”时要小心：当有多个指针指向同一段内存时，某个指针释放这段内存可能会导致其他指针的非法操作。因此在释放前一定要确保其他指针不能再使用这段内存空间。







## volatile 有什么作用



- 状态寄存器一类的并行设备硬件寄存器
- 一个中断服务子程序会访问到的非自动变量
- 多线程间被几个任务共享的变量









## 一个参数可以既是const又是volatile吗



​		可以。用const 和volatile 同时修饰变量，表示这个变量在程序内部是只读的，不能改变的；只在程序外部条件变化下改变，并且编译器不会优化这个变量。每次使用这个变量时，都要小心地去内存读取这个变量的值，而不是去寄存器读取他的备份。









# haha



```c++
printf("enter you code:______\b\b\b\b\b\b");
int a;
cin >> a;
```























