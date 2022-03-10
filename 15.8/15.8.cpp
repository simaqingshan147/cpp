#include<memory>
#include<set>
#include"15.h"

//无法直接使用对象进行面向对象编程
//必须使用指针和引用

//辅助类，购物筐
class Basket{
public:  //默认构造函数和拷贝控制由编译器合成

    //void add_tiem(const shared_ptr<quote>& sale){items.insert(sale);}
    //用户仍然要处理动态内存(指针),不如隐藏

    //添加书到购物车
    //注意:如果不使用类定义的克隆,在加书时的拷贝可能切除派生类部分
    //如new quote(sale)  使用了基类构造函数,切掉派生类部分
    void add_item(const quote& sale){  //拷贝对象
        items.insert(shared_ptr<quote>(sale.clone()));
    }
    void add_item(quote&& sale){ //移动对象
        //move(sale)产生sale的右值版本
        //调用clone()的右值版本,返回右值
        items.insert(shared_ptr<quote>(std::move(sale).clone()));
    }

    //打印购物车总价
    double total_receipt(ostream&) const;

private:
    //比较shared_ptr,供multiset使用
    static bool compare(const shared_ptr<quote>&lhs,
                        const shared_ptr<quote>& rhs)
    {return lhs->isbn() < rhs->isbn();}
    //mltiset保存交易信息,按compare排序
    multiset<shared_ptr<quote>,decltype(compare)*> items{compare};
    //声明使用一个与compare类型相同的函数进行比较
    //初始化items并使用compare函数
};

//打印购物车总价
double Basket::total_receipt(ostream& os) const{
    double sum = 0;

    //mltiset.upper_bound，跳过所有相同值，返回第一个指向不相同值的迭代器
    //即要么指向末尾，要么指向下一本书
    //upper_bound比较成员是否相同，使用的是compare

    //print_total调用net_price，所以返回值动态绑定
    
    //mltiset.count(n),返回n的出现次数，即这本书的购买本数

    for(auto iter = items.cbegin();
    iter != items.cend();
    iter = items.upper_bound(*iter))
        sum += print_total(os,**iter,items.count(*iter));
    
    os<<"Total Sale: "<<sum<<endl;
    return sum;
}

int main(){
    //不能把具有继承关系的多种类型对象直接存放至容器
    vector<quote> basket1;
    basket1.push_back(quote("0-201-82470-1",50));
    //正确，但只有基类部分被拷贝至vector
    basket1.push_back(Bulk_quote("0-201-82470-1",50,10,.25));
    //派生类部分会被切掉
    cout<<basket1.back().net_price(15)<<endl;  //只能调用基类版本

    //使用容器存放基类的智能指针
    vector<shared_ptr<quote>> basket2;
    basket2.push_back(make_shared<quote>("0-201-82470-1",50));

    //base* p = &bulk_quote 普通派生类指针能转换为基类指针
    //派生类智能指针也支持转换为基类智能指针
    basket2.push_back(make_shared<Bulk_quote>("0-201-82470-1",50,10,.25));
    //执行bulk_quote版本
    cout<<basket2.back()->net_price(15)<<endl;

    Basket b;
    Bulk_quote book1("0-201-82470-1",50,10,.25);
    quote book2("0-201-82470-2",50);
    b.add_item(book1);
    b.add_item(book2);
    b.total_receipt(cout);

    return 0;
}