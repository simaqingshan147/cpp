//13.4 ---- 拷贝控制示例
//用于邮件处理的两个类
#include<iostream>
#include<string>
#include<set>
using namespace std;


//一个消息可以出现在多个目录内，但只有一个内存地址
//每个消息保存所在的目录集
//每个目录保存消息集

//拷贝消息,副本将出现在同样的目录中，拷贝目录集,向所有目录添加副本
//销毁消息，从所有目录中删除
//赋值消息，左侧内容被右侧取代，左侧消息从目录集中删除，添加的右侧目录集中

//folder在前,message的save才认folder而不是友元"未定义"folder
//但是folder又不认message
//只能先定义message,再声明
class Message;

class Folder {
public:
	Folder() = default;
	~Folder() = default;
	void addMsg(Message* m) { messages.insert(m); }
	void remMsg(Message* m) { messages.erase(m); }
	//展示所有消息
	void show();
private:
	set<Message*> messages;  //目录集
};

//Message 电子邮件消息
class Message {
	friend class Folder;  //消息目录
	void friend swap(Message&, Message&);
public:
	//显式初始化
	explicit Message(const string& str=""):
		contents(str){}
	//拷贝构造函数
	Message(const Message&);
	//拷贝赋值运算符
	Message& operator=(const Message&);
	//析构函数
	~Message();
	//在给定folder中添加/删除Meaasge
	void save(Folder&);
	void remove(Folder&);
private:
	string contents;  //消息文本
	set<Folder*> folders;  //包含该消息的目录集
	//拷贝构造函数，拷贝赋值运算符使用的工具函数
	//将message添加到指定message的folder中
	void add_to_folders(const Message&);
	//从每个folder中删除message
	void remove_from_folders();
};


void Message::save(Folder& f) {
	//在消息的目录列表中添加该目录
	folders.insert(&f);
	//在目录中添加该消息
	f.addMsg(this);
}

void Message::remove(Folder& f) {
	//从消息的目录集中删除该目录
	folders.erase(&f);
	//在目录中删除该消息
	f.remMsg(this);
}

void Message::add_to_folders(const Message& m) {
	for (auto f : m.folders)
		f->addMsg(this);
}

void Message::remove_from_folders() {
	for (auto f : this->folders)
		f->remMsg(this);
}

Message::Message(const Message& m) :
	contents(m.contents), folders(m.folders) {
	//把本消息添加到复制消息的目录中
	add_to_folders(m);
}

Message::~Message() {
	//从每一个目录中删除本消息
	remove_from_folders();
}

Message& Message::operator=(const Message& rhs) {
	//先清空左侧消息目录，确保自赋值的正确性
	//如果是自赋值，两个消息就具有相同地址
	//先加后减就会清空所有目录
	remove_from_folders();
	//复制
	contents = rhs.contents;
	folders = rhs.folders;
	//将本消息添加的右侧目录中
	add_to_folders(rhs);
	return *this;
}

//交换两个消息
void swap(Message& lhs, Message& rhs) {
	using std::swap;
	//把消息的指针从目录中删除
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	//交换文本和目录集
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);

	//将每个消息添加到它的新目录集中
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

void Folder::show() {
	int i = 1;
	for (auto m : messages)
		cout << "本目录的第" << i++
		<< "个消息是" << m->contents << endl;
}

int main()
{
	Folder f1;
	Folder f2;
	Message m1("hello");
	//测试message
	m1.save(f1);
	//测试folder拷贝赋值运算符
	f1.show();
	f2 = f1;
	f2.show();
	//测试messsage拷贝构造函数
	Message m2(m1);
	f1.show();
	f2.show();

	return 0;
}