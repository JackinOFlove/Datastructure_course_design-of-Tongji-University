#include <iostream>
#include <cstring>
#define Max_namelength 5
#define Min_namelength 1
using namespace std;
//打印菜单函数
void Print_Menu()
{
	cout << "**                  家谱管理系统                  **" << endl;
	cout << "====================================================" << endl;
	cout << "**               请选择要执行的操作 ：            **" << endl;
	cout << "**                A --- 完善家谱                  **" << endl;
	cout << "**                B --- 添加家庭成员              **" << endl;
	cout << "**                C --- 解散局部家庭              **" << endl;
	cout << "**                D --- 更改家庭成员姓名          **" << endl;
	cout << "**                E --- 退出程序                  **" << endl;
}
//获得一个在合理范围的整数函数，并进行错误处理
int Get_Int(string errortips)
{
	int retint;
	while (1)
	{
		cin >> retint;
		if (cin.good() == 0 || retint < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << errortips;
			continue;
		}
		break;
	}
	return retint;
}
//获得一个在规定范围的字符函数，并进行错误处理
char Get_Char(string errortips)
{
	char retchar;
	cout << endl << "请选择要执行的操作：";
	while (1)
	{
		cin >> retchar;
		if (cin.good() == 0 || retchar < 'A' || retchar>'E')
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << errortips;
			continue;
		}
		break;
	}
	return retchar;
}
//获得一个在规定范围内的string函数，并进行错误处理
string Get_String(unsigned int lengthmax, unsigned int lengthmin, string errortips)
{
	string retstring;
	while (1)
	{
		cin >> retstring;
		if (cin.good() == 0 || retstring.size() < lengthmin || retstring.size() > lengthmax)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << errortips;
			continue;
		}
		break;
	}
	return retstring;
}
//家谱成员类
class Member
{
public:
	string name;
	Member* firstChild;
	Member* nextSibling;
	Member(string str = "", Member* point = NULL)
	{
		name = str;
		firstChild = nextSibling = point;
	}
};
//家谱树类
class FamilyTree
{
public:
	FamilyTree() { Ancestor = NULL; };
	void Establish();
	Member* Search(Member* current, string &name);
	void Show_Child(Member* current);
	void Perfect_Operation();
	void Add_Operation();
	void Dissolve_Operation();
	void Change_Operation();
private:
	Member* Ancestor;
};
//建立家谱（初始化根节点）
void FamilyTree::Establish()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string Ancestorname;
	Ancestorname = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
	Ancestor = new Member;
	if (Ancestor == NULL)
	{
		cout << "家谱创建失败！" << endl;
		system("pause");
		return;
	}
	Ancestor->name = Ancestorname;
	cout << "此家谱的祖先是：" << Ancestor->name << endl;
}
//打印出current结点的所有子女
void FamilyTree::Show_Child(Member* current)
{
	if (current->firstChild != NULL)				//如果存在左孩子
	{
		current = current->firstChild;				//输出左孩子
		cout << current->name << "  ";
		while (current->nextSibling != NULL)		//输出其余孩子（长子的兄弟）
		{
			current = current->nextSibling;
			cout << current->name << "  ";
		}
	}
}
//查找函数，在家谱树中查找姓名为name的结点，若找到返回该结点所在的位置，找不到返回NULL
Member* FamilyTree::Search(Member* current, string &name)
{
	Member* temp = new Member;
	if (current->name == name)							//如果找到，直接返回该结点
		return current;
	else 
	{
		if (current->firstChild != NULL)				//如果左孩子存在
		{
			temp = Search(current->firstChild, name);	//向左递归搜索
			if (temp == NULL)							
			{
				if (current->nextSibling != NULL)
					return Search(current->nextSibling, name);
			}
			else
				return temp;
		}
		else 
		{
			if (current->nextSibling != NULL)			//向右递归搜索
				return Search(current->nextSibling, name);
		}
	}
	return NULL;
}
//完善家谱函数
void FamilyTree::Perfect_Operation()
{
	cout << "请输入要建立家庭的人的姓名：";
	string name = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
	int Child_number;
	Member* current = Search(Ancestor, name);
	Member* Save_current = current;
	if (current == NULL)								//如果current找不到，则说明不存在此人
	{
		cout << "查无此人！请重新操作！" << endl;
		return;
	}
	cout << "请输入" << name << "的儿女人数：";
	Child_number = Get_Int("输入错误，请重新输入！");
	cout << "请依次输入" << name << "的儿女的姓名：";
	string tempname;
	for (int i = 0; i < Child_number; i++)
	{
		if (i == 0)										//第一个输入的是左孩子（长子）
		{
			Member* Newchild = new Member;
			tempname = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
			Newchild->name = tempname;
			current->firstChild = Newchild;
			current = Newchild;
		}
		else
		{
			Member* Newchild = new Member;				//之后输入的是右兄弟
			tempname = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
			Newchild->name = tempname;
			current->nextSibling = Newchild;
			current = Newchild;
		}
	}
	cout << name << "的第一代子孙是：";
	Show_Child(Save_current);
	cout << endl;
}
//添加家谱函数
void FamilyTree::Add_Operation()
{
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	string name = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
	Member* current = Search(Ancestor, name);
	Member* Save_current = current;
	if (current == NULL)								//如果current找不到，则说明不存在此人
	{
		cout << "查无此人！请重新操作！" << endl;
		return;
	}
	cout << "请输入" << name << "新添加的儿子（或女儿）的姓名:";
	string Add_childname = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
	if (current->firstChild == NULL)					//如果不存在长子，则添加的孩子为左孩子
	{
		Member* Newchild = new Member;
		Newchild->name = Add_childname;
		current->firstChild = Newchild;
	}
	else
	{													//如果存在长子，则添加的孩子为右兄弟
		current = current->firstChild;
		while (current->nextSibling != NULL)
			current = current->nextSibling;
		Member* Newchild = new Member;
		Newchild->name = Add_childname;
		current->nextSibling = Newchild;
	}
	cout << name << "的第一代子孙是：";
	Show_Child(Save_current);
	cout << endl;
}
//解散局部家庭函数
void FamilyTree::Dissolve_Operation()
{
	cout << "请输入要删除家庭的人的姓名：";
	string name = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
	Member* current = Search(Ancestor, name);
	if (current == NULL)								//如果current找不到，则说明不存在此人
	{
		cout << "查无此人！请重新操作！" << endl;
		return;
	}						
	if (current->firstChild == NULL)					//如果此人无左孩子，则说明还没有家庭
	{
		cout << "要解散家庭的人" << name << "没有家庭，请重新操作！" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;
	cout << name << "的第一代子孙是：";
	Show_Child(current);
	current->firstChild = NULL;
	cout << endl;
	
}
//更改姓名函数
void FamilyTree::Change_Operation()
{
	cout << "请输入要更改姓名的人的目前的姓名：";
	string Origin_name = Get_String(Max_namelength, Min_namelength, "输入错误，请重新输入！");
	Member* current = Search(Ancestor, Origin_name);
	if (current == NULL)								//如果current找不到，则说明不存在此人
	{
		cout << "查无此人！请重新操作！" << endl;
		return;
	}
	else
	{
		cout << "请输入更改后的姓名：";
		cin >> current->name;
		cout << Origin_name << "已更名为" << current->name << endl;
	}
}
//主函数
int main()
{
	Print_Menu();
	FamilyTree Jiapu;
	Jiapu.Establish();
	while (1)
	{
		char keydown = Get_Char("输入错误，请重新输入！");
		switch (keydown)
		{
		case 'A':
			Jiapu.Perfect_Operation();    
			break;
		case 'B':
			Jiapu.Add_Operation();
			break;
		case 'C':
			Jiapu.Dissolve_Operation();
			break;
		case 'D':
			Jiapu.Change_Operation();
			break;
		case 'E':
			cout << endl << "请退出程序！" << endl;
			system("pause");
			return 0;
		}
	}
	system("pause");
	return 0;
}