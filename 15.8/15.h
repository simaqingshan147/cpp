#include<iostream>
#include<string>
#include<vector>
using namespace std;

//在15.8节中修改了bulk_quote和disc_quote的构造函数
//15.8以前的15.h是错的，请知悉 2022.3.7

//基类quote,代表书籍
class quote{
public:
    //派生类不做改变直接继承的函数
    string isbn() const{return bookNo;}
    quote() = default;
    quote(const string& book,double sales_price):
        bookNo(book),price(sales_price){}

    //基类的拷贝构造函数
    quote(const quote& rhs){
        bookNo = rhs.bookNo;
        price = rhs.price;
    }
    //类型相关，派生类自定义自身版本的函数,为虚函数
    virtual double net_price(size_t n) const{return n*price;}

    //基类通常要定义虚析构函数
    //在删除动态指针时，要仔细析构函数
    //指针的静态类型与对象动态类型可能不符
    //将析构函数定义为虚函数确保正确的析构
    virtual ~quote()=default;
    //定义了虚析构函数就不能合成移动操作
    //使用移动时实际使用的是拷贝操作

    //15.8为使用类添加返回拷贝的函数
    virtual quote* clone() const &{return new quote(*this);}  //拷贝版本
    virtual quote* clone() const &&{return new quote(std::move(*this));}  //右值版本

private:  //派生类和外部不能访问
    string bookNo;  //书籍isbn
protected:  //派生类可以访问，不能外部访问
    double price = 2.0;  //普通状态下不打折的价格
};

//保存折扣和购买量的类，派生类使用数据实现不同价格策略
//含有或未覆盖直接继承的纯虚函数的类是抽象基类
class Disc_quote :public quote{
public:
    Disc_quote() = default;
    Disc_quote(const string& book,double p,
        size_t qty,double disc):
        quote(book,p),
        quantity(qty),discount(disc){}

    pair<size_t,double>discount_policy()const
    {return {quantity,discount};}

    //无需定义，因为抽象基类无法定义对象
    //Disc_quote* clone() const & override{return new Disc_quote(*this);}

    ~Disc_quote() override = default;

    //纯虚函数
    virtual double net_prize(size_t n) const = 0;
protected:
    size_t quantity = 0;  //折扣适用的购买量
    double discount = 0.0;  //折扣
};

//派生类Bulk_quote,代表打折书籍
//使用类派生列表指出从哪些基类继承而来
class Bulk_quote: public Disc_quote{  //public,派生类对继承而来的成员可见
public:
    Bulk_quote() = default;
    //每个类只能控制它自己的初始化过程
    Bulk_quote(const string& book,double p,
        size_t qty,double disc):
        Disc_quote(book,p,qty,disc){}

    //override,显式注明改写基类虚函数
    ~Bulk_quote() override = default;
   
   //一定要定义两个，否则会报Bulk_quote是抽象基类
    double net_price(size_t n) const{
        if(n>=quantity)
            return n*(1-discount)*price;
        return n*price;
    }
    double net_prize(size_t n) const override{
        if(n>=quantity)
            return n*(1-discount)*price;
        return n*price;
    }

    Bulk_quote* clone() const & override{return new Bulk_quote(*this);}
    Bulk_quote* clone() const && override{return new Bulk_quote(std::move(*this));}
};

//动态绑定,同一段代码同时处理基类和派生类
//打印销售所得
double print_total(ostream& os,const quote& item,size_t n){
    //quote或bulk_quote,根据形参判断
    //使用基类引用调用虚函数，发生动态绑定
    //运行时而非编译时解析
    double ret = item.net_price(n);
    os<<"ISBN: "<<item.isbn()  //只能是quote的isbn(),因为派生类不定义
    <<" # sold: "<<n<<" total due: "<<ret<<endl;
    return ret;
}
