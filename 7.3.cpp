//�����������
#include<iostream>
#include<vector>
#include<string>

using std::string;
using std::ostream;
using std::istream;
using std::vector;
using std::cout;
using std::cin;

//���ڹ�����
//��ʾ��ʾ���ϵ�һ��screen
class Window_mgr {
public:
	using ScreenIndex = vector<Screen>::size_type;
	ScreenIndex addScreen(const Screen&);
private:
	//Ĭ�������,����һ����׼�ߴ�Ŀհ�screen,���ڳ�ʼֵ
	vector<Screen> screens{ Screen(24,80, ' ') };         //�б��ʼ��
	void clear(ScreenIndex);
};

//��ʾ��������
class Screen {
public:
	typedef string::size_type pos;
	//using pos = string::size_type;

	Screen() = default;
	Screen(pos ht,pos wd):height(ht),width(wd),contents(ht*wd,' '){}
	Screen(pos ht,pos wd,char c):height(ht),width(wd),
		contents(ht*wd,c){}

	char get()const{                            //��ȡ����ַ�           
		some_number();
		return contents[cursor];                //��ʽ����
	}
	inline char get(pos ht, pos wd)const;       //��ʽ����
	Screen& move(pos r, pos c);

	void some_number()const;

	Screen& set(char);
	Screen& set(pos, pos, char);

	//���ݶ����Ƿ���const����display����
	//�ú�������do_displayʱthis��ʽת��Ϊָ��const��ָ��,���طǳ�������
	Screen& display(ostream& os) { do_display(os); return *this; }
	//�ú������س�������
	const Screen& display(ostream& os)const { do_display(os); return *this; }
private:
	pos cursor = 0;                            //���λ��
	pos height = 0, width = 0;                 //�ߣ���
	string contents;

	//�ɱ����ݳ�Ա
	mutable size_t access_ctr = 0;                //��¼��Ա�������ô���

	//�ú���������ʾscreen������
	//ָ��ǳ�����thisָ�뱻const��ʽת��Ϊָ������ָ��
	void do_display(ostream& os)const { os << contents; }

	//��Ԫ��������Ӱ�����Ȩ��,��������������
	friend void Window_mgr::clear(ScreenIndex);
};

//���ں������崦ָ��inline
//�ƶ����,����this�β�
inline Screen& Screen::move(pos r, pos c)
{
	pos row = r * width;   //������λ��
	cursor = row + c;      //������ƶ���ָ����
	some_number();
	return *this;
}

//������ڲ�������inline
//����ָ��λ�õ��ַ�
char Screen::get(pos r, pos c)const
{
	pos row = r * width;
	some_number();
	return contents[row + c];
}

//�����Ա�������ô���
void Screen::some_number()const
{
	//�ɱ����ݳ�Ա��Զ����const����ʹ����const��Ա�Ķ���
	//���,һ��const��Ա�������Ըı�һ���ɱ��Ա��ֵ
	++access_ctr;
}

//���ù������λ�õ��ַ�
inline Screen& Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
	//���ص��Ƕ��������Ƕ���ĸ���
}

//����ָ��λ�õ��ַ�
inline Screen& Screen::set(pos r, pos col, char ch)
{
	//��������,���Զ�ȡ�����ݳ�Ա
	contents[r * width + col] = ch;
	return *this;
}

void Window_mgr::clear(ScreenIndex i)
{
	Screen& s = screens[i];
	//������Ϊ��Ԫ,����Ԫ��ĳ�Ա�������Է��ʴ������г�Ա,����private
	//��������Ԫ����
	s.contents = string(s.height * s.width, ' ');
}

//��������ʹ�õ����ֶ�λ�����������֮��
//�������ͱ���ָ�������ĸ���ĳ�Ա
//�򴰿����һ��Screen���������ı��
Window_mgr::ScreenIndex
Window_mgr::addScreen(const Screen& s)
{
	screens.push_back(s);
	return screens.size() - 1;
}

int main()
{
	Screen myscreen;
	const Screen blank(8, 10);
	myscreen = Screen(8, 10);
	Screen::pos ht = 24, wd = 80;
	Screen scr(ht, wd, ' ');

	Screen* p = &scr;
	char c = scr.get();     //����scr�����get��Ա
	c = p->get();			//����p��ָ�����get��Ա

	//��������������myscreen�����ν���
	//��Ϊmove��set��������,�ı���Ƕ�����
	myscreen.move(4, 0).set('#');

	myscreen.display(cout);     //���÷ǳ����汾
	blank.display(cout);        //���ó����汾

	return 0;
}