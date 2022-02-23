//引用限定符
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Foo{
public:
    Foo() = default;
    Foo(int i,vector<int> j){a=i;s=j;}
    Foo(const Foo& rhs){
        a = rhs.a;
        s = rhs.s;
    }
    //只能向可修改的左值赋值
    Foo& operator=(const Foo&) &;  //=左边强制为左值

    //&只能跟在const之后
    //Foo afunction() & const;  错误

    //引用限定符用于重载
    Foo sorted() &&;       //右值

    //const左值引用绑定右值 
    //重载函数时，要么都有引用限定符，要么都没有
    Foo sorted() const &;  //任何类型Foo

    //练习1的sort
    Foo sorted1() const &{
        Foo ret(*this);
        return ret.sorted();
    }
    //练习2的sort
    Foo sorted2() const &{
        return Foo(*this).sorted();
    }
private:
    int a;
    vector<int> s;
};

//引用限定符必须同时出现在声明和定义中
Foo& Foo::operator=(const Foo& rhs) &{
    a = rhs.a;
    s = rhs.s;
    return *this;
}

//对象为右值，可以原地址排序
Foo Foo::sorted() &&{
    sort(s.begin(),s.end());
    for(int i:s)
        cout<<i<<" ";
        cout<<endl;
    return *this;
}


//const左值和右值不能改变
Foo Foo::sorted() const &{
    //必须先复制
    Foo ret(*this);
    sort(ret.s.begin(),ret.s.end());
    for(int i:ret.s)
        cout<<i<<" ";
    cout<<endl;
    return ret;
}



Foo retFoo()
{
    return {1,{1,224343,3}};
}

int main(){
    string s1 = "a value";  //右值引用=
    string s2 = "hell0";
    //s1+s2是右值，但新标准库允许向右值赋值(向后兼容)
    s1 + s2 = "wow";

    Foo i,j;
    i = j;  //正确
    //retFoo() = i;  错误
    
    vector<int> v{1,23,-1,45,456,-23,7};
    Foo a(2,v);

    retFoo().sorted();  //调用右值版本
    a.sorted();         //调用const &版本

    return 0;
}