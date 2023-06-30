#include <iostream>

using namespace std;

class student
{
public:

private:

};

class A1
{
public:
    virtual void fun(){}
};
class A2:public A1
{

};
class A3:public A1
{

};
class A4:public A2
{

};

///         A1
///        /  \
///       A2  A3
///      /
///     A4



int main()
{
    int a = 0 ;
    int *p = &a;
    char c = 0;
    char* pc = &c;
    student st;

    {
        //////////////////static_cast///////////////////////////
        /// 相关内容的转换(包括数与数之间,继承关系中对象的向上和向下转换)
//        p = static_cast<int *>(pc);
        void* lpvoid = static_cast<void *>(pc);
        a = static_cast<int>(c);
//        student* ps = static_cast<student*>(p);
//        p = static_cast<int*>(&st);
//        a = static_cast<int>(p);
        p = static_cast<int>(a);
        student* ps =(student*)(p);
        p = (int*)(&st);
        /////////////////////////////////////////////////////

        A2 *pa2 = (A2*)(new A1); // 子类指针默认无法指向父类对象, 除非强转.
        //继承关系中对象的向上转换
        A1 *pa1 = static_cast<A1*>(pa2);
        pa1 = new A2;

        //继承关系中对象的向下转换
        pa2 = static_cast<A2*>(pa1); // 类似于 pa2 = (A2*)(pa1);
        A3 *pa3 = static_cast<A3*>(pa1); //没有检验,可能会出问题
        if( pa3 )
        {
            cout<< "pa3 is valid;"<<endl;
        }
    }
    cout<< "======================"<<endl;
    {
        //////////////////dynamic_cast///////////////////////////
        ///
        /// 只适用于继承关系的两个类 或多个类之间转换
        //        p = static_cast<int *>(pc);
//                void* lpvoid = dynamic_cast<void *>(pc);
//                a = dynamic_cast<int>(c);

        /////////////////////////////////////////////////////

        A2 *pa2 = (A2*)(new A1); // 子类指针默认无法指向父类对象, 除非强转.
        //继承关系中对象的向上转换
        A1 *pa1 = dynamic_cast<A1*>(pa2);
        pa1 = new A2;

        //继承关系中对象的向下转换
        pa2 = dynamic_cast<A2*>(pa1); // 类似于 pa2 = (A2*)(pa1);
        A3 *pa3 = dynamic_cast<A3*>(pa1); //向下转换校验
        if( pa3 )
        {
            cout<< "pa3 is valid;"<<endl;
        }else{
            cout<< "pa3 is invalid;"<<endl;
        }
        //特殊情况, 向下转化安全--父类指针要转换为子类指针, 恰巧这个父类指针指向这个子类的子类对象
        pa1 = new A4;
        pa2 = dynamic_cast<A2*>(pa1);
        if( pa2 )
        {
            cout<< "pa2 is valid;"<<endl;
        }else{
            cout<< "pa2 is invalid;"<<endl;
        }
        pa1 = new A2;
        A4* pa4 = dynamic_cast<A4*>(pa1);
        if( pa4 )
        {
            cout<< "pa4 is valid;"<<endl;
        }else{
            cout<< "pa4 is invalid;"<<endl;
        }
        //交叉转换
        //pa3 = static_cast<A3*>(pa2);
        pa3 = dynamic_cast<A3*>(pa2);
    }
    cout << "Hello World!" << endl;
    return 0;
}
