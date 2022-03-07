//15.1 ---- oop概述
//15.2 ---- 定义基类和派生类
//15.3 ---- 虚函数
#include<15.h>

class base;
// class based:base{......} 错误,基类必须已经被定义

//class unbase final;  //final指定不能被继承

int main(){
    quote item("0-201-82740-1",50);
    Bulk_quote bulk("0-201-82740-1",50,5,.19);
    quote *p = &item;
    //将基类的指针和引用绑定到派生类对象的基类部分上
    p = &bulk;
    quote& r = bulk;

    //不存在基类向派生类的转换
    //Bulk_quote& bulkref = item;

    /*
    quote* temp = &bulk;  //动态类型是bulk_quote
    Bulk_quote *bulkp = temp;
    错误，即使temp的动态类型是bulk_quote
    !!编译器只能检查指针或引用的静态类型来推断转换是否合法!!
    */

   Bulk_quote bulk2("0-201-82740-1",50,5,.19);

   //派生类向基类的自动类型转换只对指针和引用有效
   //因此,允许向基类拷贝/移动操作传递派生类对象
   quote item2(bulk2);  //bulk的基类部分用来构造,其他被切掉
   
   quote base("0-201-82740-1",50);
   print_total(cout,base,10);  //调用qutoe::net_price
   Bulk_quote derived("0-201-82740-1",50,5,.19);
   print_total(cout,derived,10);  //调用bulk_quote::net_price

   //通过普通类型调用虚函数时，编译时确定版本
   //通过对象调用函数，调用在编译时绑定
   base.net_price(20);   //quote::net_price

    //回避虚函数动态绑定
    quote* p2 = &derived;
    //不管p2的动态类型是什么，强制调用基类版本
    double undiscounted = p2->quote::net_price(42);

    //Disc_quote a; 不允许定义抽象基类的对象
    return 0;
}