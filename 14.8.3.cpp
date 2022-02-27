#include<iostream>
#include<map>
#include<functional>
#include<algorithm>
using namespace std;

//不同的调用对象可能有相同的调用形式

//函数
int add(int i,int j){return i+j;}
//lambda,其产生的未命名函数对象类
auto mod = [](int i,int j){return i%j;};
//函数对象类
struct divide{
    int operator()(int i,int j){
        return i/j;
    }
};
//函数形式都是int(int,int)

int main(){
    
    /*
    //定义函数表，存储可调用对象的指针
    map<string,int(*)(int,int)> binops;

    binops.insert({"+",add});
    binops.insert({"%",mod});
    //错误，divide是类类型
    binops.insert({"/",divide()});
    */

   //function标准库类型,接受可调用对象
   function<int(int,int)> f1 = add;
   function<int(int,int)> f2 = mod;
   function<int(int,int)> f3 = divide();

   cout<<f1(4,2)<<endl;
   cout<<f2(4,2)<<endl;
   cout<<f3(4,2)<<endl;

   //列出可调用对象与二元运算符对应关系的表格
   map<string,function<int(int,int)>> binops;
   binops = {
     {"+",add},
     {"%",mod},
     {"/",divide()},  //现在ok
     {"*",[](int i,int j){return i*j;}},
     {"-",minus<int>()}  //标准库函数对象，类似greater
   };
   cout<<binops["+"](10,5)<<endl;
   cout<<binops["-"](10,5)<<endl;
   cout<<binops["*"](10,5)<<endl;
   cout<<binops["/"](10,5)<<endl;
   cout<<binops["%"](10,5)<<endl;

   return 0;
}