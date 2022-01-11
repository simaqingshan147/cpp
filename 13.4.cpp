//13.4 ---- ��������ʾ��
//�����ʼ������������
#include<iostream>
#include<string>
#include<set>
using namespace std;


//һ����Ϣ���Գ����ڶ��Ŀ¼�ڣ���ֻ��һ���ڴ��ַ
//ÿ����Ϣ�������ڵ�Ŀ¼��
//ÿ��Ŀ¼������Ϣ��

//������Ϣ,������������ͬ����Ŀ¼�У�����Ŀ¼��,������Ŀ¼��Ӹ���
//������Ϣ��������Ŀ¼��ɾ��
//��ֵ��Ϣ��������ݱ��Ҳ�ȡ���������Ϣ��Ŀ¼����ɾ������ӵ��Ҳ�Ŀ¼����

//folder��ǰ,message��save����folder��������Ԫ"δ����"folder
//����folder�ֲ���message
//ֻ���ȶ���message,������
class Message;

class Folder {
public:
	Folder() = default;
	~Folder() = default;
	void addMsg(Message* m) { messages.insert(m); }
	void remMsg(Message* m) { messages.erase(m); }
	//չʾ������Ϣ
	void show();
private:
	set<Message*> messages;  //Ŀ¼��
};

//Message �����ʼ���Ϣ
class Message {
	friend class Folder;  //��ϢĿ¼
	void friend swap(Message&, Message&);
public:
	//��ʽ��ʼ��
	explicit Message(const string& str=""):
		contents(str){}
	//�������캯��
	Message(const Message&);
	//������ֵ�����
	Message& operator=(const Message&);
	//��������
	~Message();
	//�ڸ���folder�����/ɾ��Meaasge
	void save(Folder&);
	void remove(Folder&);
private:
	string contents;  //��Ϣ�ı�
	set<Folder*> folders;  //��������Ϣ��Ŀ¼��
	//�������캯����������ֵ�����ʹ�õĹ��ߺ���
	//��message��ӵ�ָ��message��folder��
	void add_to_folders(const Message&);
	//��ÿ��folder��ɾ��message
	void remove_from_folders();
};


void Message::save(Folder& f) {
	//����Ϣ��Ŀ¼�б�����Ӹ�Ŀ¼
	folders.insert(&f);
	//��Ŀ¼����Ӹ���Ϣ
	f.addMsg(this);
}

void Message::remove(Folder& f) {
	//����Ϣ��Ŀ¼����ɾ����Ŀ¼
	folders.erase(&f);
	//��Ŀ¼��ɾ������Ϣ
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
	//�ѱ���Ϣ��ӵ�������Ϣ��Ŀ¼��
	add_to_folders(m);
}

Message::~Message() {
	//��ÿһ��Ŀ¼��ɾ������Ϣ
	remove_from_folders();
}

Message& Message::operator=(const Message& rhs) {
	//����������ϢĿ¼��ȷ���Ը�ֵ����ȷ��
	//������Ը�ֵ��������Ϣ�;�����ͬ��ַ
	//�ȼӺ���ͻ��������Ŀ¼
	remove_from_folders();
	//����
	contents = rhs.contents;
	folders = rhs.folders;
	//������Ϣ��ӵ��Ҳ�Ŀ¼��
	add_to_folders(rhs);
	return *this;
}

//����������Ϣ
void swap(Message& lhs, Message& rhs) {
	using std::swap;
	//����Ϣ��ָ���Ŀ¼��ɾ��
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	//�����ı���Ŀ¼��
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);

	//��ÿ����Ϣ��ӵ�������Ŀ¼����
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

void Folder::show() {
	int i = 1;
	for (auto m : messages)
		cout << "��Ŀ¼�ĵ�" << i++
		<< "����Ϣ��" << m->contents << endl;
}

int main()
{
	Folder f1;
	Folder f2;
	Message m1("hello");
	//����message
	m1.save(f1);
	//����folder������ֵ�����
	f1.show();
	f2 = f1;
	f2.show();
	//����messsage�������캯��
	Message m2(m1);
	f1.show();
	f2.show();

	return 0;
}