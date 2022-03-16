//15.9  拓展12.3的文本查找类,实现逻辑运算
#include"textQuery.h"
#include<algorithm>

//派生查询类型的抽象基类
//不希望派生类直接使用它,所以没有public
class Query_base{
    friend class Query;  //只有Query能调用private的函数
protected:
    virtual ~Query_base() = default;
private:
    //纯虚函数,返回与当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    //rep为表示查询的string
    virtual std::string rep() const = 0;
};

//对外提供接口,同时隐藏Query_base的继承体系
//Query为Query_base的唯一接口

class Query{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&,const Query&);
    friend Query operator&(const Query&,const Query&);
public:
    //构建WordQuery对象
    Query(const std::string&);
    //接口函数,调用query_base操作
    QueryResult eval(const TextQuery& t)const{return q->eval(t);}
    std::string rep()const{return q->rep();}

private:
    Query(std::shared_ptr<Query_base> query):q(query){}
    std::shared_ptr<Query_base> q;  //绑定派生类的智能指针
};

//WordQuery查找一个string,执行TextQuery的工作
class WordQuery:public Query_base{
    friend class Query;  //Query要使用WordQuery的构造函数
    WordQuery(const std::string& s):query_word(s){}
    //返回结果类
    QueryResult eval(const TextQuery& t) const override{return t.query(query_word);}
    //返回查询单词
    std::string rep()const override{return query_word;}

    std::string query_word;
};

//定义接受string的Query构造函数
//用Query封装WordQuery
inline Query::Query(const std::string& s):q(new WordQuery(s)){}

//~生成NotQuery
//保存要取反的Query
class NotQuery:public Query_base{
    friend Query operator~(const Query&);
    NotQuery(const Query&q):query(q){}

    QueryResult eval(const TextQuery&) const;
    std::string rep() const{return "~("+query.rep()+")";}

    Query query;  //要取反的query
};

//重载输出符,用于解释结果
std::ostream&
operator<<(std::ostream& os, const Query& query){
    //通过智能指针虚调用rep()
    return os<<query.rep();
}

//非运算符返回NotQuery对象
inline Query operator~(const Query& operand)
{
    //使用Query(shared_ptr<>)的构造函数隐式构造
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

//两个运算对象的查询类的抽象基类
class BinaryQuery:public Query_base{
protected:
    BinaryQuery(const Query& l,const Query& r,std::string s):
        lhs(l),rhs(r),opSym(s){}

    //不定义eval，为抽象基类
    std::string rep() const override{
        return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";}
    
    Query lhs,rhs;  //左右侧运算对象
    std::string opSym;  //运算符 $或|
};

//and 和 or 继承 BinaryQuery的rep,但覆盖eval,为具体类

class AndQuery:public BinaryQuery{
    friend Query operator&(const Query&,const Query&);
    AndQuery(const Query& left,const Query& right):
        BinaryQuery(left,right,"&"){}

    QueryResult eval(const TextQuery&) const;
};

//且运算符返回AndQuery对象
inline Query operator&(const Query& lhs,const Query& rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery:public BinaryQuery{
    friend Query operator|(const Query&,const Query&);
    OrQuery(const Query& left,const Query& right):
        BinaryQuery(left,right,"|"){}

    QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query& lhs,const Query& rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult
OrQuery::eval(const TextQuery& text) const{
    //对rhs和lhs的动态调用
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);

    //左侧行号
    auto ret_lines =
        std::make_shared<std::set<line_no>>(left.begin(),left.end());
    //将右侧行号插入,应用set去重,实现或操作
    ret_lines->insert(right.begin(),right.end());
    //返回结果类，表示两者的并集
    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult
AndQuery::eval(const TextQuery& text) const{
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);
    //空指针用于保存结果
    auto ret_lines = std::make_shared<std::set<line_no>>(std::set<line_no>());

    //set_intersection用于取两set的交集
    //使用插入迭代器将结果写入ret_lines
    std::set_intersection(left.begin(),left.end(),
                        right.begin(),right.end(),
                        std::inserter(*ret_lines,ret_lines->begin()));
    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult
NotQuery::eval(const TextQuery& text)const{
    //通过query对象对eval进行虚调用
    auto res = query.eval(text);
    //生成空set
    auto ret_lines = std::shared_ptr<std::set<line_no>>();
    auto beg = res.begin();
    auto end = res.end();

    //res的set按升序排列,因为生成QueryResult时从前往后添加行号
    //且res的set无重复行号
    //所以对所有行号升序比较res行号
    for(size_t n=0;n!=res.get_file()->size();n++)
    {
        //所有res的行号处理完，剩下的都是未出现的
        //或该行号未在res中出现
        if(beg==end||*beg != n)
            ret_lines->insert(n+1);
        else if(beg!=end)  //未处理完，且该行号出现在res
            beg++;  //递增res的行号
    }
    return QueryResult(rep(),ret_lines,res.get_file());
}
