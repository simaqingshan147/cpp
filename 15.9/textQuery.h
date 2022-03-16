#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<memory>
#include<map>
#include<set>
#include<sstream>
#include<cctype>

using line_no = std::vector<std::string>::size_type;

//实现单词查询,与或非查询，与混用逻辑符查询
//每种逻辑用不同的类实现

//12.9的类文件丢失，重写

class QueryResult;  //处理结果类

//文本处理类
class TextQuery{
public:
    //绑定输入文件，逐行读取并写入file所指的vector
    TextQuery(std::ifstream&);
    //查询函数
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;  //输入文件
    //每个单词到它所在行号(的set)的映射
    std::map<std::string,
            std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult{
friend std::ostream& print(std::ostream&,const QueryResult&);  //打印查询结果
public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f):
            sought(s),lines(p),file(f){}
    
    //15.9所需函数,返回file和行号set的迭代器
    std::shared_ptr<std::vector<std::string>>& get_file(){return file;}
    std::set<line_no>::iterator begin(){return lines->begin();}
    std::set<line_no>::iterator end(){return lines->end();}

private:
    std::string sought;  //查询string
    std::shared_ptr<std::set<line_no>> lines;   //对应单词的行号set指针
    std::shared_ptr<std::vector<std::string>> file;  //输入文件转换的vector
};

//新建vector初始化file
TextQuery::TextQuery(std::ifstream &is):file(new std::vector<std::string>)
{
    std::string text;
    std::string res;  //句子在上面几行的部分
    //按句子写入,改进原代码的按行写入
    while(std::getline(is,text)){
        int i = 0;
        int beg = 0;  //上一个句号出现位置
        //对一行遍历
        while(i<text.size())
        {
            if(text[i] == '.')  //出现句号
            {
                if(i==text.size()-1)  //res为空(一整行/部分),res不空
                {
                    //无论有无res,都添加res
                    file->push_back(res+text.substr(beg,i+1));
                    res.clear();
                }
                else if(std::isalpha(text[i+1])&&std::isupper(text[i+1]))  //确定断句的句号
                {
                    if(res.size())  //上面有句子的部分
                    {
                        file->push_back(res+text.substr(0,i+1));  //加上从0到i的字符串
                        res.clear();
                    }
                    else
                        file->push_back(text.substr(beg,i+1));  //加上句子
                    beg = i+1;
                }
            }
            //检查是否断句
            if(i==text.size()-1&&text[i] != '.')  //句尾无句号
            {
                if(!beg)  //一行都是句子的一部分
                    res += text;
                else
                    res += text.substr(beg,i);  //添加后半段字符
            }
            i++;
        }
    }
    //添加单词出现句子号的set
    for(auto i=file->begin();i!=file->end();i++)
    {
        std::string word;
        std::istringstream sentence(*i);
        while(sentence>>word){
            //返回对应set指针,且lines是引用
            auto &lines = wm[word];
            //string之前未出现,指针绑定新set
            if(!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(i-file->begin()+1);  //添加行号
        }
    }
}

QueryResult TextQuery::query(const std::string& sought) const{
    //如未找到sought,返回空set指针
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

    auto loc = wm.find(sought);
    if(loc == wm.end())
    {
        std::cout<<sought<<" none"<<std::endl;
        return QueryResult(sought,nodata,file);
    }
    else //用对应行号指针构建结果类
        return QueryResult(sought,loc->second,file);
}

//打印给定结果类对象
std::ostream& print(std::ostream& os,const QueryResult& qr)
{
    os<<qr.sought<<" occurs "<<qr.lines->size()<<" "
    <<(qr.lines->size() > 1 ? "times" : "time")<<std::endl;

    //打印单词出现的每一句
    for(auto num:*qr.lines)
    {
        os<<"\t(line "<<num<<") "
        <<*(qr.file->begin()+num-1)<<std::endl;
    }
    return os;
}

void runQuery(std::ifstream& infile){
    TextQuery tq(infile);
    while(true){
        std::cout<<"enter word to look for,or q to quit"<<std::endl;
        std::string s;

        if(!(std::cin>>s)||s=="q")break;
        print(std::cout,tq.query(s))<<std::endl;
    }
}
#endif