



# ui界面组件介绍

1.布局，框选起来的为一组（竖直和水平标反了）

![image-20220808105101886](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808105101886.png)



2.分割符，窗口内显示为空白

![image-20220808105219226](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808105219226.png)

![image-20220808105236417](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808105236417.png)



3.设置为朋友关系（放在一组->点击朋友关系->拖动->QLable->text(英文括号)）

作用：设置快捷键（alt+字母）

![image-20220808105337762](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808105337762.png)

![image-20220808105809008](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808105809008.png)

![image-20220808110014591](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808110014591.png)



4.按住tab时，焦点的切换顺序

![image-20220808110301162](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808110301162.png)

# 一、QT

## 1.QT简介

- 跨平台 C++ 开发库

- 主要用于开发图形用户界面
- 既是**库**，也是图形用户界面应用程序**框架**（已经封装好）。

- 支持多个操作系统。
- **多线程、访问数据库、音视频处理、文件操作等**

## 2.QT建立工程

- 建立工程时，名字和路径，不能有中文和空格
- 创建项目时：**Base class**

> Qmainwidow ：带工具栏、菜单、状态栏等
>
> QWinget：简单的窗口，无菜单栏等
>
> QDialog：用于提示的窗口

- 从上到下依次为

  ```c++
  ***.pro //工程文件：在外层
  mainwindow.h //主窗口头文件：表示主窗口这个类
  main.cpp //主函数源文件
  mainwindow.cpp//主窗口源文件：在main里定义对象
  mainwindow.ui //绘制界面
  ```

- 在 ui 绘制窗口进行操作后，会生成`ui-mainwindow.h`作为主窗口源文件的头文件代码。

  > 注：
  >
  > 如果想对 ui 窗口进行操作，需要在绘制窗口中改，而不是在ui-mainwindow代码块中改。
  >
  > 如果想改对象名称，可以修改 ui窗口旁边的filter



## **3.命令行项目**

```c++
#include <QCoreApplication>
/*
命令行参数：
argc :命令行参数的数量
argv :对应的命令行参数
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
```







# 二、语法



## 1.控制台输出

![image-20220806110824664](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806110824664.png)

```c++
//main.cpp
#include<Q/qDebug>								//头文件
int main(int argc, char *argv[])
{
    int aa=1;
    char b='a';
    char *p="ni";
    string str("hao");
    
    //类似于printf的格式化输出						输出语句
    qDebug("%d %c %s %s",aa,b,p,str.c_str());		//string类型要转为字符数组才能输出
    
    //类似于cout输出
    qDebug()<<aa<<b<<p<<str.c_str();				//不能二者结合输出
    
    //打印函数名字
    qDebug()<<__func__<<endl;
    
    return a.exec();
}
```





## 2.字符串

```q
#include<QString>							//头文件

QString qstr("nihao");
qDebug()<<qstr<<endl;						//可直接输出

string str2=qstr.toStdString();             //转普通字符串
qDebug()<<str2.c_str()<<endl;
QString qstr2=qstr.fromStdString(str2);     //普通字符串转qstring
qDebug()<<qstr<<endl;
qstr2=QString::number(11);  			   //数字转字符串
qstr2=QString::number(11.1);
bool isOK=false;						  //字符串转数字
double d=qstr2.toDouble(&isOK);			   //若成功转换，isOK为true（失败返回0）
double d=qstr2.toInt(&isOK,16);			   //转成16进制

qstr.append("a");                           //拼接，默认在后面（等同于+=），返回拼后字符串   
qstr.prepend("a");                          //在字符串前面拼接     

qstr.sprintf("%d %c %s",aa,b,p);            //重新赋值（等同于=）  1ani      
//赋值，按照数字从小到大依次拼接(1-99)(若大于99，取前两位进行替换，后面保留)(要带空格)
qstr2=QString("%1 %2 %6").arg("ni").arg("hao").arg("a"); //nihaoa
qstr2=QString("%11 %2 %6").arg("ni").arg("hao").arg("a"); //anihao
qstr2=QString("%111 %2 %6").arg("ni").arg("hao").arg("a"); //a1nihao
qstr2=QString("%1%3%2").arg(11).arg(22).arg(33); 		  //11332

bool e=qstr2.contains("a");                 //判断是否包含             
int f=qstr2.indexOf("1");                   //返回第一次出现的下标(不包含返回-1)
int g=qstr2.lastIndexOf("1");               //从右向左找（最后一次出现的下标）  

QString qstr3=qstr2.mid(1,2);               //从下标1开始，截取两个长度

qstr3.size();                               //长度
qstr3.count("a");                           //a字符出现的次数

qstr2=qstr3.trimmed();                      //去除两端的空白符
QStringList ql=qstr3.split(" ");            //按照空格分割,返回链表
for(int i=0;i<ql.size();i++){qDebug()<<ql[i];} //输出链表     
```





## 3.提示对话框

![image-20220806110853795](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806110853795.png)

​		除了 information 还有 warning ,critical ,about ,question ；about 不能指定按钮，只有一个默认的ok，所以也没有返回值。其他的用法差不多。

```q
#include<QMessageBox>

QApplication a(argc, argv);
MainWindow w;           //定义窗口对象
w.show();               //显示主窗口
//只有一个默认按钮ok
QMessageBox::information(&w,"info","123");		
//两个按钮（yes,no）默认焦点yes
QMessageBox::information(&w,"info","123",QMessageBox::Yes|QMessageBox::No); 
//两个按钮（yes,no）默认焦点no
QMessageBox::information(&w,"info","123",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
```







# 三、信号和槽



## 1.基本概念

​		信号（signal）和槽（slot）用于**完成界面操作的响应**，是完成任意两个qt对象之间的**通信机制**。

​		**信号**：特定条件下发射的事件。例如pushButton最常见的信号使鼠标单击时发射一个clicked信号。

​		**槽**：对信号响应的函数。槽就是一个类成员函数可以是任何属性的（public,protected,private），可以有参数，也可以被直接调用，槽函数与一般的函数的区别：槽函数可以与一个信号关联，当信号被发射时，关联的槽函数被自动执行。

​		当某个时间发生之后，他会发射一个信号，如果有对象对这个信号感兴趣，将信号和自己的一个函数（成为槽）绑定来处理这个信号，这个槽函数就会执行，也就是回调。所有槽的本质是一个**类成员函数**。

- **所有使用信号与槽的类中，必须有Q_OBJECT这个宏。**









## 2.添加信号与槽



### --方法1：快捷添加

​		

- **加完组件要构建，在代码中生成对应的类**

​		快捷的方式添加信号与槽：设计界面右键 --> 转到槽 --> 选择函数(clicked)

![image-20220806113607493](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806113607493.png)

```c++
//槽函数名字：on_发射信号的对象名字_发射的信号
void MainWindow::on_pushButton_clicked()
{
    //每点击按钮一次就运行下面语句
    qDebug()<<"on_pushButton_clicked";
}
```





### 		--方法2：手动添加



​		**法1：拖动**

![image-20220806113949182](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806113949182.png)



​		**法2：代码**(设计的右上角板块可以更改类名)

![image-20220806120620490](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806120620490.png)

```c++
//mainwindow.h
class MainWindow : public QMainWindow
{
private slots:
    void on_deal_signal();
};

//mainwindow.cpp
//构造函数写连接语句
QObject::connect(ui->mypush,                //信号的发射者（指针对象）
                 SIGNAL(clicked()),         //发送的信号，使用SIGNAL()做一个转化
                 this,                      //接收信号的对象（指针对象）
                 SLOT(on_deal_signal()));   //接收的槽函数使用SLOT()做一个转化
//手动添加的槽
void MainWindow::on_deal_signal()
{
    qDebug()<<"关闭";
    this->close();//关闭主窗口
}
```

![image-20220806154902945](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806154902945.png)

```c++
//mainwindow.h
class MainWindow : public QMainWindow
{
private slots:
    void on_deal_checkBox(int);        //  槽的参数列表应与信号的参数列表保持一致
};

//mainwindow.cpp
//构造函数中
QObject::connect(ui->checkBox,                                                
                 SIGNAL(stateChanged(int)),                                   
                 this,                                                        
                 SLOT(on_deal_checkBox(int)));//宏里放函数名参数列表（形参名去掉\只保留类型）
ui->checkBox->setTristate(true);              //设置checkbox的三态

//处理checkBox的槽(状态转换)
void MainWindow::on_deal_checkBox(int a)
{
    //未勾选,a=0       勾选,a=2        半勾选,a=1
    qDebug()<<"on_deal_checkBox"<<"   "<<a;
}
```





### --方法3：自定义添加



​		自定义信号

```c
//mainwindow.h
signals:                                    //自定义信号，不能加访问修饰符
void emitToDialog(int,char,QString);        //信号只声明，不需要定义
```

​		

​		自定义槽（添加新文件：右击项目名 --> add new --> Qt --> Qt设计师界面类）

```c
//dialog.h
public slots:			//自定义槽，slots前必须有访问修饰符
void recvMain(int,char,QString);

//dialog.cpp
void Dialog::recvMain(int a,char b,QString str)	//实现槽
{
    qDebug()<<a<<b<<str;
    //弹出dialog窗口，设置一个文本
    QString st=QString::number(a)+b+str;
    ui->label->setText(st);                 //label设置文本
    this->show();                           //显示dialog
}
```



​		连接

```c
//main.cpp
MainWindow w;
w.show();
Dialog dialog;
//自定义信号与槽进行绑定关联
QObject::connect(&w,
                 SIGNAL(emitToDialog(int,char,QString)),
                 &dialog,
                 SLOT(recvMain(int,char,QString)));
```



​		发射信号

```c
//mainwindow.ui  加一个按钮，右键转到槽clicked()
void MainWindow::on_pushButton_2_clicked()
{
    emit emitToDialog(10,'b',QString("str"));                    //发射一个信号
    qDebug()<<"发射！";
}
```





### --判断是否连接成功

```c++
QMetaObject::Connection con1=QObject::connect(ui->horizontalSlider,        
                 						    SIGNAL(valueChanged(int)),   
                 						    this,                        
                 						    SLOT(on_deal_progress(int)));

//成功在控制台输出，失败弹出提示对话框
if(con1)
    {
        qDebug()<<"水平滑块和进度条连接成功";
    }else
        {
          QMessageBox::critical(this,"error","水平滑块和进度条连接失败");     
    }
```









## 3.一个信号对应多个槽

![image-20220806164115127](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220806164115127.png)



```c++
//mainwindow.h
private slots:
void on_deal_progress(int);
void on_deal_time(int);

//mainwindow.cpp
//水平滑块和进度条绑定
ui->horizontalSlider->setRange(0,100);       //设置水平滑块的移动范围
QObject::connect(ui->horizontalSlider,
                 SIGNAL(valueChanged(int)),
                 this,
                 SLOT(on_deal_progress(int)));
//水平滑块和time控件绑定
QObject::connect(ui->horizontalSlider,
                 SIGNAL(valueChanged(int)),
                 this,
                 SLOT(on_deal_time(int)));

//进度条
void MainWindow::on_deal_progress(int a)
{
    qDebug()<<a;                            //0-100
    ui->progressBar->setValue(a);
}

//时间组件
void MainWindow::on_deal_time(int a)
{
    QTime time(0,0);                        //time初始0
    int sec=3600*24*a/100;                  //通过比例换算加多少秒
    time=time.addSecs(sec);                 //加秒数
    ui->timeEdit->setTime(time);            //设置时间
}
```





## 4.多个信号对应一个槽

![image-20220807100155792](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220807100155792.png)

​		mainwindow 的两个开关看都可以控制dialog窗口的显示与隐藏

```c
//dialog.h
public slots:
    void on_showorhide();

//dialog.cpp
//显示或隐藏对话框窗口
void Dialog::on_showorhide()
{
    bool b=this->isVisible();
    b?this->hide():this->show();
}

//mainwindow.h
//获取mainwindow的ui
public:
    Ui::MainWindow* getui();

//mainwindow.cpp
Ui::MainWindow* MainWindow::getui()
{
    return  this->ui;
}

//main.cpp
#include "ui_mainwindow.h"
Ui::MainWindow *pui=w.getui();
QObject::connect(pui->doorbutton,
                 SIGNAL(clicked()),
                 &dialog,
                 SLOT(on_showorhide()));
QObject::connect(pui->bedbutton,
                 SIGNAL(clicked()),
                 &dialog,
                 SLOT(on_showorhide()));
```





## 5.信号 -> 信号 -> 槽



![image-20220808092640733](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808092640733.png)



​		左边mainwindow的spinbox组件发出一个valuechanged信号，触发自定义的sendnumber信号，触发右边dialog文件的槽函数使得数字发生改变。

```c
//mainwindow.h
signals:
    void sendNumber(int);

//mainwindow.cpp
//spinbox和mainwindow信号与信号的连接
QObject::connect(ui->spinBox,
                 SIGNAL(valueChanged(int)),
                 this,
                 SIGNAL(sendNumber(int)));

//dialog.h
public slots:
    void on_shownumber(int);

//dialog.cpp
void Dialog::on_shownumber(int a)
{
    ui->lcdNumber->display(a);              //lcd显示对应的数字
}

//main.cpp
QObject::connect(&w,
                 SIGNAL(sendNumber(int)),
                 &dialog,
                 SLOT(on_shownumber(int)));
```





## 6.断开连接

![image-20220808094647218](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808094647218.png)



```c
//mainwindow.h  
public:
    QMetaObject::Connection con1;           //水平滑块与进度条之间的连接信息
    QMetaObject::Connection con2;           //水平滑块与time之间的连接信息

//mainwindow.cpp
//水平滑块和进度条绑定                                                     
ui->horizontalSlider->setRange(0,100);       //设置水平滑块的移动范围       
con1=QObject::connect(ui->horizontalSlider,                      
                      SIGNAL(valueChanged(int)),                 
                      this,                                      
                      SLOT(on_deal_progress(int)));              
//水平滑块和time控件绑定                                                  
con2=QObject::connect(ui->horizontalSlider,                      
                      SIGNAL(valueChanged(int)),                 
                      this,                                      
                      SLOT(on_deal_time(int)));   

//(使用右键添加槽)
//水平滑块和进度条之间的连接
void MainWindow::on_checkprogress_clicked(bool checked)
{
    if(checked)//勾选 断开连接（法1）
    {
        QObject::disconnect(con1);
    }else//重新建立连接
    {
        con1=QObject::connect(ui->horizontalSlider,
                              SIGNAL(valueChanged(int)),
                              this,
                              SLOT(on_deal_progress(int)));
    }
}

//水平滑块和time之间的连接
void MainWindow::on_checkBox_3_clicked(bool checked)
{
    if(checked)//勾选 断开连接（法2）
    {
        QObject::disconnect(ui->horizontalSlider,
                            SIGNAL(valueChanged(int)),
                            this,
                            SLOT(on_deal_time(int)));
    }else//重新建立连接
    {
        con2=QObject::connect(ui->horizontalSlider,
                              SIGNAL(valueChanged(int)),
                              this,
                              SLOT(on_deal_time(int)));
    }
}

```





## 7.**练习（字体、颜色）

![image-20220808100821678](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220808100821678.png)

​		

​		栅格布局围起来的为一组，可以互斥

```c
//mainwindow.h
public slots:
    void on_textStyleBold(bool);
    void on_textStyleItalic(bool);
    void on_textStyleUnder(bool);
    void on_textStyleDelete(bool);
    void on_textColor(bool);

//mainwindow.cpp
//连接
QObject::connect(ui->check_bold,SIGNAL(clicked(bool)),
                 this,SLOT(on_textStyleBold(bool)));    
QObject::connect(ui->check_itatic,SIGNAL(clicked(bool)),
                 this,SLOT(on_textStyleItalic(bool)));
QObject::connect(ui->check_under,SIGNAL(clicked(bool)),
                 this,SLOT(on_textStyleUnder(bool)));  
QObject::connect(ui->check_delete,SIGNAL(clicked(bool)),
                 this,SLOT(on_textStyleDelete(bool)));
QObject::connect(ui->radio_black,SIGNAL(toggled(bool)),this,SLOT(on_textColor(bool)));  
QObject::connect(ui->radio_red,SIGNAL(toggled(bool)),this,SLOT(on_textColor(bool)));
QObject::connect(ui->radio_yellow,SIGNAL(toggled(bool)),this,SLOT(on_textColor(bool)));
QObject::connect(ui->radio_blue,SIGNAL(toggled(bool)),this,SLOT(on_textColor(bool)));

//槽函数
void MainWindow::on_textStyleBold(bool a)
{
    QFont font=ui->plainTextEdit->font();       //获取当前fond
    font.setBold(a);                            //加粗
    ui->plainTextEdit->setFont(font);
}
void MainWindow::on_textStyleItalic(bool a)
{
    QFont font=ui->plainTextEdit->font();       //获取当前fond
    font.setItalic(a);                          //斜体
    ui->plainTextEdit->setFont(font);
}
void MainWindow::on_textStyleUnder(bool a)
{
    QFont font=ui->plainTextEdit->font();       //获取当前fond
    font.setUnderline(a);                       //下划线
    ui->plainTextEdit->setFont(font);
}
void MainWindow::on_textStyleDelete(bool a)
{
    QFont font=ui->plainTextEdit->font();       //获取当前fond
    font.setStrikeOut(a);                       //删除线
    ui->plainTextEdit->setFont(font);
}

void MainWindow::on_textColor(bool)
{
    QPalette pal;
    if(ui->radio_black->isChecked())            //判断该radio是否勾选
    {
        pal.setColor(QPalette::Text,QColor(0,0,0));
    }else if(ui->radio_red->isChecked())
    {
        pal.setColor(QPalette::Text,Qt::red);
    }else if(ui->radio_yellow->isChecked())
    {
        pal.setColor(QPalette::Text,Qt::yellow);
    }else if(ui->radio_blue->isChecked())
    {
        pal.setColor(QPalette::Text,Qt::blue);
    }
    ui->plainTextEdit->setPalette(pal);
}
```







# 四、事件



## 1.基本概念



​		事件是由系统或Qt本身在不同的时刻发出的。比如：当用户按下鼠标，敲下键盘，或窗口需要重新绘制的时候，都会发出一个相应的事件。一些事件是在对用户操作做出响应的时候发出，如键盘事件；另一些事件是由系统自动发出，如定时器事件。

​		Qt的事件和信号槽很容易混淆，事件其实也就是所谓的事件驱动，signal由具体对象发出，然后会马上交由connect函数连接的slot进行处理。而对于事件，Qt使用一个“事件队列（windowSystemEventQueue）” 对所有的事件进行维护，当新的事件产生时，会被追加到事件队列的尾部，前一个事件完成后，取出后面的事件进行处理。但是，必要的时候，Qt的事件也是可以不进入事件队列，直接处理。

- **如果我们使用组件，我们关心的是信号槽；如果我们使用自定义组件，我们关心的是事件。**





## 2.重写事件



​		MainWindow 的父类 QMainWindow 的父类 QWidget 搜索 event

```c
//mainwindow.h
public:
    virtual void mousePressEvent(QMouseEvent *event);

//mainwindow.cpp
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->x();			//输出鼠标按下的x坐标
    qDebug()<<event->y();			//输出鼠标按下的y坐标
}
```



![image-20220809103837541](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220809103837541.png)

![image-20220809103924458](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220809103924458.png)



​		在label组件内按鼠标，输出鼠标操作到label组件上

```c
//更改父类为QLabel,重写QLabel关于鼠标事件的函数
//右键组件->提升为->类名：自定义的类名->添加->提升
#include<QMouseEvent>
#include<QString>

void myLabel::mousePressEvent(QMouseEvent *ev)
{
    this->setText("鼠标按下"+QString::number(ev->x())+","+QString::number(ev->y()));
}

void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
    //button():表示的是触发当前事件的按钮，在鼠标移动的事件中总是返回NoButton
    //buttons():表示当事件触发时，有哪些按钮是按下的
    if(ev->buttons()==Qt::LeftButton)//判断鼠标左键是否按下
    {
        this->setText("鼠标左键按下移动："+
                      QString::number(ev->x())+","+QString::number(ev->y()));
    }
}

void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    this->setText("鼠标抬起："+QString::number(ev->x())+","+QString::number(ev->y()));
}
```





## 3.事件分发



```c
//键盘抬起、按下
//mylineedit.h
public:
    void keyPressEvent(QKeyEvent *) override;
    virtual void keyReleaseEvent(QKeyEvent *event);
    bool event(QEvent *) override;

public:
    QString str;        //存取电话号码

//mylineedit.cpp
#include<QKeyEvent>
//事件分发，一旦重写了将由我们自定义分发规则
bool myLineEdit::event(QEvent *e)
{
    if(e->type()==QEvent::KeyPress)       //type():判断事件类型
    {
        QKeyEvent *pkey=(QKeyEvent *)e;		//强转为键盘事件
        if(pkey->key()>=Qt::Key_0 && pkey->key()<=Qt::Key_9 || pkey->key()==Qt::Key_Backspace)
        {
            //继续分发
            return QLineEdit::event(e);          //回归正常的分发流程
        }else
        {
            //不分发
            qDebug()<<pkey->key();
            return true;                  //表示当前事件已经被处理，不需要继续分发
            //return false;               //当前事件未得到处理，也不会继续分发
        }
    }
    return QLineEdit::event(e);           //其他的事件回归正常流程
}

//event handler 事件处理器
void myLineEdit::keyPressEvent(QKeyEvent *key)
{
    if(key->key()==Qt::Key_Backspace)   //删除最后一位电话号
    {
        str=str.left(str.size()-1);
        this->setText(str);
    }else if(str.size()<=10)                  //判断电话号码的位数
    {
        str+=QString::number(key->key()-Qt::Key_0);
        this->setText(str);
    }
}
```





## 4.事件过滤



​													**输入密码，不显示文本**

![image-20220810103607917](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220810103607917.png)



​		event()函数是一个protected的函数，这意味着我们要想重写event()，必须继承一个已有的组件类，并重写event()函数。event()函数的确有一定的控制，不过有时候我们的需求更严格一些：希望那些组件根本看不到这种事件。event()函数虽然可以拦截，但其实也是接收到了事件。我们让他收都收不到。这样做的好处是：模拟一种系统根本没有那个事件的效果，所以其他组件根本不会收到这个事件，也就无需修改自己的事件处理函数。所以我们可以使用事件过滤器，事件过滤器给我们一种能力，让我们能够完全移除某种事件。事件过滤器可以安装到任意 QObject 类型上面，并且可以安装多个。

​		我们需要用到两个函数：QObject::eventFilter 过滤器函数、QObject::installEventFilter 安装过滤器

```c
//mainwindow.h
public:
    bool eventFilter(QObject *watched,QEvent *event);

//mainwindow.cpp
//构造函数	1
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //窗口上的组件安装监控（安装过滤器）
    ui->lineEdit->QObject::installEventFilter(this);
    ui->plainTextEdit->QObject::installEventFilter(this);
    ui->plainTextEdit->setAttribute(Qt::WA_InputMethodEnabled,false);    //关闭中文输入法
}

//监视者
bool MainWindow::eventFilter(QObject *watched,QEvent *event)
{
    if(watched==ui->lineEdit)                       //输入密码（显示为点，回车对话框内显示密码）
    {
        if(event->type()==QEvent::KeyPress)         //如果是键盘事件
        {
            QKeyEvent *key=(QKeyEvent*)event;       //强转为键盘事件
            if((key->key()>=Qt::Key_0 && key->key()<=Qt::Key_9) ||
                   (key->key()>=Qt::Key_A && key->key()<=Qt::Key_Z))
            {
                return false;                       //放行，不被过滤
            }else if(key->key()==Qt::Key_Return)    //Key_Return:字母区回车  Key_Enter:数字区的回车
            {
                QMessageBox::information(this,"密码",ui->lineEdit->text());
                return true;                        //过滤掉
            }
            else return true;                      //过滤掉
        }
    }else if(watched==ui->plainTextEdit)           //输入文本（用滑轮改变文字大小）
    {
        if(event->type()==QEvent::Wheel)           //如果是滑轮事件
        {
            QWheelEvent *wheel=(QWheelEvent*)event;//强转成滑轮事件
            if(wheel->angleDelta().y()>0)          //滑轮向上滑动（远离用户方向）
            {
                ui->plainTextEdit->zoomIn();        //文本放大
            }else
            {
                ui->plainTextEdit->zoomOut();       //文本缩小
            }
            return true;
        }
    }
    return false;
}
```





## 5.自定义事件（id:1000-65535）

![image-20220811105125715](C:\Users\PC\AppData\Roaming\Typora\typora-user-images\image-20220811105125715.png)



```c
//meinwindow.h
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include"myevent.h"
#include"dialog.h"
int MY_EVENT_ID =QEvent::User;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置选择框的选项
    QStringList str;
    str.push_back("+");
    str.push_back("-");
    str.push_back("*");
    str.push_back("/");
    ui->comboBox->addItems(str);
}

//点击按钮的槽函数
void MainWindow::on_pushButton_clicked()
{
    QString str1=ui->num1->text();
    bool is=false;
    int num=str1.toUInt(&is);

    QString str2=ui->num2->text();
    is=false;
    int numm=str2.toUInt(&is);

    QString rule=ui->comboBox->currentText();
    QString strrule;        //发送走
    int result=0;           //发送走

    if(rule=="+")
    {
        strrule="加法";
        result=num+numm;
    }else if(rule=="-")
    {
        strrule="减法";
        result=num-numm;
    }else if(rule=="*")
    {
        strrule="乘法";
        result=num*numm;
    }else if(rule=="/")
    {
        strrule="除法";
        result=num/numm;
    }

    //QEvent::User;                   //事件ID，用来唯一标识事件

    //定义事件
    MyEvent *pev=new MyEvent (MY_EVENT_ID);
    pev->m_rule=strrule;
    pev->m_result=result;

    //发送自定义事件（若post栈区事件，接收方接收时，该对象已被销毁）
    extern Dialog *pdialog;
    QCoreApplication::postEvent(/*接受者*/pdialog,pev);		//非阻塞（只发送堆区）
    //QCoreApplication::sendEvent(/*接受者*/pdialog,pev);		//阻塞（可发送栈区事件）
}

//事件类:继承QEvent类（没有无参构造函数）
//myevent.h
#include <QEvent>
#include<QString>

class MyEvent : public QEvent
{
public:
    MyEvent(int typeId);

public:
    QString m_rule;         //计算规则
    int     m_result;       //计算结果
};

//myevent.cpp
MyEvent::MyEvent(int typeId):QEvent((QEvent::Type)typeId)
{

}

//接收自定义事件的窗口
//dialog.h
public:
    void customEvent(QEvent *event);        //自定义事件的处理器

//dialog.cpp
extern int MY_EVENT_ID;
void Dialog::customEvent(QEvent *event)
{
    if(event->type()==MY_EVENT_ID)
    {
        qDebug()<<"接收到自定义事件";
        MyEvent* pev=(MyEvent*)event;
        ui->label->setText(pev->m_rule+"的计算结果为："+QString::number(pev->m_result));
        this->show();
    }
}
```



