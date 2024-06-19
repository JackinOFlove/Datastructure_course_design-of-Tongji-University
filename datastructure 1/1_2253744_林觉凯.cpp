#include <iostream>
#include <cstring>
using namespace std;
class ListNode//定义链表结点类(ListNode)，每一个结点储存着一名考生的信息和下一名考生信息的地址
{
public:
	int student_id;//考号
	int student_age;//年龄
	string student_name;//姓名
	string student_sex;//性别
	string student_category;//报考类型
	ListNode* next;//指向下一个结点的指针
	ListNode(int number1 = 0, int number2 = 0, string str1 = "", string str2 = "", string str3 = "", ListNode* point = NULL)
	{
		student_id = number1;
		student_age = number2;
		student_name = str1;
		student_sex = str2;
		student_category = str3;
		next = NULL;
	}//构造函数，初始化考生的信息
	void ShowNode();//公有操作：输出结点考生的基本信息
};
//输出某个结点储存的考生基本信息函数
void ListNode::ShowNode()
{
	cout << student_id << "\t";
	cout << student_name << "\t";
	cout << student_sex << "\t";
	cout << student_age << "\t";
	cout << student_category << endl;
}
class LinkList
{
public:
	LinkList();									//构造函数，建立考试报名信息库
	~LinkList();								//析构函数，实现释放内存
	void Length();								//计算链表长度（即考试报名系统总人数，同时分别统计男生、女生人数）
	void ShowList();							//依次输出链表内的每个结点的信息
	int Search(int id);							//寻找函数，输入一个考生的考号，返回这位考生在链表中的位置（第几个）
	ListNode* Located(int Location);			//定位函数，输入这位考生再链表中的位置，返回这位考生所在位置的地址
	bool Insert(int Location, ListNode& node);   //插入函数，输入要插入考生的位置和基本信息，返回插入成功或失败
	bool Change(int Location, ListNode& anode, ListNode& bnode);	//修改函数，输入要修改考生的位置，返回修改成功或失败，node用于记录修改前考生的基本信息
	bool Delete(int Location, ListNode& node);	//删除函数，输入要删除考生的位置，返回插入成功或失败，node用于记录删除的考生的基本信息
private:
	ListNode* head;                             //私有成员：链表的头结点
};
//构造函数，建立考试报名信息库
LinkList::LinkList()
{
	head = NULL;					
	head = new ListNode;			//给头结点分配空间
	if (head == NULL)				//代码的健壮性，如果分配失败则会给出提示
	{
		cout << "链表构建失败！" << endl;
		system("pause");
		return;
	}
	cout << "请首先建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	int number;
	while (1)
	{
		cin >> number;
		if (cin.good() == 0 || number < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入的考生人数错误，请重新输入：";		//代码健壮性，保证输入的考生人数是正整数
			continue;
		}
		break;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类型！" << endl;
	for (int i = 0; i < number; i++)
	{
		ListNode current;
		while (1)
		{
			cin >> current.student_id;
			if (cin.good() == 0 || current.student_id < 1)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入的第" << i + 1 << "位考生考号错误，请从此项开始重新输入，考号，姓名，性别，年龄及报考类型：" << endl;
				continue;
			}								 //代码的健壮性，可以精确的定位到是哪一位学生的输入考号错误，并且从 此项 开始继续输入
			break;
		}
		if (Search(current.student_id) != -1)//代码的健壮性，可以防止输入两位考生的考号相同
		{
			cout << "第" << i + 1 << "位的考生考号已经存在，请此项开始重新输入，考号，姓名，性别，年龄及报考类型：" << endl;
			i--;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		while (1)
		{
			cin >> current.student_name;
			if (cin.good() == 0 || current.student_name.size() < 2 || current.student_name.size() > 10)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入的第" << i + 1 << "位考生姓名有误，请此项开始重新输入，姓名，性别，年龄及报考类型：" << endl;
				continue;						//代码的健壮性，可以精确的定位到是哪一位学生的输入姓名错误，并且从 此项 开始继续输入
			}
			break;
		}
		while (1)
		{
			cin >> current.student_sex;
			if (cin.good() == 0 || current.student_sex != "男" && current.student_sex != "女")
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入的第" << i + 1 << "位考生性别有误，请此项开始重新输入，性别，年龄及报考类型：" << endl;
				continue;						//代码的健壮性，可以精确的定位到是哪一位学生的输入性别错误，（这里的性别只能是“男”或者“女”）并且从 此项 开始继续输入
			}
			break;
		}
		while (1)
		{
			cin >> current.student_age;
			if (cin.good() == 0 || current.student_age < 1 || current.student_age> 100)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入的第" << i + 1 << "位考生年龄有误，请此项开始重新输入，年龄、报考类型：" << endl;
				continue;						//代码的健壮性，可以精确的定位到是哪一位学生的输入年龄错误，并且从 此项 开始继续输入
			}
			break;
		}
		while (1)
		{
			cin >> current.student_category;
			if (cin.good() == 0 || current.student_category.size() < 2 || current.student_category.size() > 20)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入的第" << i + 1 << "位考生报考类型有误，请此项开始重新输入，报考类型：" << endl;
				continue;						//代码的健壮性，可以精确的定位到是哪一位学生的输入报考类型错误，并且从 此项 开始继续输入
			}
			break;
		}
		Insert(i, current);
	}
}
//析构函数，实现释放内存
LinkList::~LinkList()
{
	ListNode* current = head->next;
	while (head->next != NULL)
	{
		current = head->next;
		head->next = current->next;
		delete current;
	}
	delete head;
}
//依次输出链表内每个结点的信息
void LinkList::ShowList()
{
	cout << "考号\t" << "姓名\t" << "性别\t" << "年龄\t" << "报考类型" << endl;
	ListNode* current = head->next;
	while (current != NULL)
	{
		cout << current->student_id << "\t" << current->student_name << "\t" << current->student_sex << "\t" << current->student_age << "\t" << current->student_category << endl;
		current = current->next;
	}
}
//计算链表长度（即考试报名系统总人数，同时分别统计男生、女生人数）
void LinkList::Length()
{
	int length = 0;						 //length为链表长度，即考生的总人数
	int number_man = 0;
	int number_woman = 0;
	ListNode* current = head->next;		 //从头开始扫描链表，计算长度
	while (current != NULL)
	{
		if (current->student_sex == "男")
			number_man++;
		else
			number_woman++;
		current = current->next;
		length++;
	}
	cout << "一共有" << length << "名考生；" << "其中男生" << number_man << "名，女生" << number_woman << "名，具体如下：" << endl;
}
//寻找函数，输入一个考生的考号，返回这位考生在链表中的位置（第几个）
int LinkList::Search(int id)			//通过考号定位这位考生在链表第几位
{
	int Location = 1;
	ListNode* current = head->next;
	while (current != NULL)
	{
		if (current->student_id == id)
			return Location;
		else
		{
			current = current->next;
			Location++;
		}
	}
	return -1;							//如果没有找到这位考生（即考生不存在），return -1
}
//定位函数，输入这位考生在链表中的位置，返回这位考生所在位置的地址
ListNode* LinkList::Located(int Location)	//上一个Search函数可以找到考生是在链表第几位，Located函数返回这一位的地址
{
	if (Location < 0)
		return NULL;						//代码的健壮性，如果Location为负数说明该位置不存在，return NULL
	else
	{
		ListNode* current = head;
		int counter = 0;
		while (current != NULL && counter < Location)
		{
			current = current->next;
			counter++;
		}
		return current;
	}
}
//插入函数，输入要插入考生的位置和基本信息，返回插入成功或失败
bool LinkList::Insert(int Location, ListNode& node)		
{
	ListNode* current = Located(Location);
	if (current == NULL)
		return false;								//代码的健壮性，如果该地址不存在返回false
	else
	{
		ListNode* Newnode = new ListNode(node);
		if (Newnode == NULL)
		{
			cout << "新链表结点构建失败！" << endl;	//代码的健壮性，如果申请失败则会提示
			return false;				
		}
		Newnode->next = current->next;				//插入新的结点
		current->next = Newnode;
		return true;
	}
}
//删除函数，输入要删除考生的位置（在main函数里面输入学号，通过Search函数返回一个位置，所以这个函数的一个输入为待删除考生的位置即可），返回删除成功或失败，node用于记录删除的考生的基本信息
bool LinkList::Delete(int Location, ListNode& node)
{
	ListNode* current, * temp = NULL;
	current = Located(Location - 1);					//得到待删除结点的前一个地址
	if (current == NULL || current->next == NULL)
		return false;									//代码的健壮性，如果当前结点或下一个结点不存在，无法进行删除操作
	else
	{
		temp = current->next;
		current->next = temp->next;
		node.student_id = temp->student_id;
		node.student_age = temp->student_age;
		node.student_name = temp->student_name;
		node.student_sex = temp->student_sex;
		node.student_category = temp->student_category;	//node用来储存删除结点信息
		delete temp;									//删除结点
		return true;
	}
}
//修改函数，输入要修改考生的位置，（在main函数里面输入学号，通过Search函数返回一个位置，所以这个函数的一个输入为待修改考生的位置即可），返回修改成功或失败，anode为修改后考生的基本信息，bnode用于记录修改前考生的基本信息
bool LinkList::Change(int Location, ListNode& anode, ListNode& bnode)
{
	ListNode* current = Located(Location);
	if (current == NULL)
		return false;
	else
	{
		Delete(Location, bnode);		//调用Delete函数删除这个结点
		Insert(Location - 1, anode);	//调用Insert函数在删除的这个结点插入新的结点，完成修改
	}
	return true;
}
int main()
{
	LinkList StudentSystem;				//LinkList类的实例化
	StudentSystem.ShowList();
	cout << endl;
	int KeyDown;
	cout << "请输入您要进行的操作（1为插入，2为删除，3为修改，4为查找，5为统计，0为退出操作）" << endl;
	//代码的健壮性，保证输入的操作数字为0，1，2，3，4，5
	while (1)
	{
		cout << "请输入您要进行的操作：";
		while (1)
		{
			cin >> KeyDown;
			if (cin.good() == 0 || KeyDown < 0 || KeyDown > 5)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入错误！请重新请输入您要进行的操作：";
				continue;
			}
			break;
		}
		//0-退出程序
		if (KeyDown == 0)
		{
			cout << "测试结束，请退出程序！" << endl;
			break;
		}
		//1-插入操作
		else if (KeyDown == 1)
		{
			cout << "请输入你要插入的考生的位置：";
			int location;
			while (1)
			{
				cin >> location;
				if (cin.good() == 0 || location < 0)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请重新请输入要插入学生的位置：";
					continue;
				}
				break;
			}
			cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别" << endl;
			ListNode NewNode;
			while (1)
			{
				cin >> NewNode.student_id;
				if (cin.good() == 0 || NewNode.student_id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请重新请输入要插入学生的考号：";
					continue;
				}
				break;
			}
			while (1)
			{
				cin >> NewNode.student_name;
				if (cin.good() == 0 || NewNode.student_name.size() < 2 || NewNode.student_name.size() > 10)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请从此项开始输入要插入学生的姓名、性别、年龄及报考项目：";
					continue;
				}
				break;
			}
			while (1)
			{
				cin >> NewNode.student_sex;
				if (cin.good() == 0 || NewNode.student_sex != "男" && NewNode.student_sex != "女")
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请从此项开始输入要插入学生的性别、年龄及报考项目：";
					continue;
				}
				break;
			}
			while (1)
			{
				cin >> NewNode.student_age;
				if (cin.good() == 0 || NewNode.student_age < 1 || NewNode.student_age >100)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请从此项开始输入要插入学生的年龄、报考项目：";
					continue;
				}
				break;
			}
			while (1)
			{
				cin >> NewNode.student_category;
				if (cin.good() == 0 || NewNode.student_category.size() < 2 || NewNode.student_category.size() > 20)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请重新请输入要插入学生的报考项目：";
					continue;
				}
				break;
			}//代码的健壮性，保证插入考生信息的准确性
			if (StudentSystem.Insert(location - 1, NewNode) == 0)
			{
				cout << "插入位置不合法，操作失败！" << endl;
			}//代码的健壮性，对插入位置不合法的提示
			StudentSystem.ShowList();
			cout << endl;
		}
		//2-删除操作
		else if (KeyDown == 2)
		{
			cout << "请输入你要删除的考生考号：";
			int id;
			while (1)
			{
				cin >> id;
				if (cin.good() == 0 || id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请重新请输入要删除学生的学号：";
					continue;
				}
				break;
			}
			int Location = StudentSystem.Search(id);			//将学号变为该学生所在链表的位置
			ListNode DeleteNode;
			if (StudentSystem.Delete(Location, DeleteNode) == 0)
			{
				cout << "删除学生不存在，请重新操作！" << endl;  //代码的健壮性，对没有该学生的提示
				continue;
			}
			else
			{
				cout << "删除的考生信息如下：" << endl;
				DeleteNode.ShowNode();
			}
			cout << "删除后的考生信息库如下：" << endl;
			StudentSystem.ShowList();
			cout << endl;
		}
		//3-修改操作
		else if (KeyDown == 3)
		{
			cout << "请输入你要修改的考生考号：";
			int id;
			while (1)
			{
				cin >> id;
				if (cin.good() == 0 || id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请重新请输入要修改学生的学号：";
					continue;
				}
				break;
			}//代码的健壮性，保证输入的学号的正确性
			ListNode AfterChangeNode;
			ListNode BeforeChangeNode;
			cout << "请依次输入修改后考生的考号，姓名，性别，年龄及报考类别！" << endl;
			for (int i = 0; i < 1; i++)
			{
				int temp_student_id;
				while (1)
				{
					cin >> temp_student_id;
					if (cin.good() == 0 || temp_student_id < 1)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "修改的考生考号错误，请从此项开始重新输入，考号，姓名，性别，年龄及报考类型：" << endl;
						continue;
					}
					break;
				}
				if (StudentSystem.Search(temp_student_id) != -1)
				{
					cout << "修改的后考生考号已经存在，请此项开始重新输入，考号，姓名，性别，年龄及报考类型：" << endl;
					i--;
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}//代码的健壮性，如果修改后的考生学号已存在，则有提示
				AfterChangeNode.student_id = temp_student_id;
				while (1)
				{
					cin >> AfterChangeNode.student_name;
					if (cin.good() == 0 || AfterChangeNode.student_name.size() < 2 || AfterChangeNode.student_name.size() > 10)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "修改的考生姓名有误，请此项开始重新输入，姓名，性别，年龄及报考类型：" << endl;
						continue;
					}
					break;
				}
				while (1)
				{
					cin >> AfterChangeNode.student_sex;
					if (cin.good() == 0 || AfterChangeNode.student_sex != "男" && AfterChangeNode.student_sex != "女")
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "修改的考生性别有误，请此项开始重新输入，性别，年龄及报考类型：" << endl;
						continue;
					}
					break;
				}
				while (1)
				{
					cin >> AfterChangeNode.student_age;
					if (cin.good() == 0 || AfterChangeNode.student_age < 1 || AfterChangeNode.student_age> 100)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "修改的考生年龄有误，请此项开始重新输入，年龄、报考类型：" << endl;
						continue;
					}
					break;
				}
				while (1)
				{
					cin >> AfterChangeNode.student_category;
					if (cin.good() == 0 || AfterChangeNode.student_category.size() < 2 || AfterChangeNode.student_category.size() > 20)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "修改的考生报考类型有误，请此项开始重新输入，报考类型：" << endl;
						continue;
					}
					break;
				}//代码的健壮性，保证输入修改后的学生信息的正确性
			}
			int Location = StudentSystem.Search(id);
			if (StudentSystem.Change(Location, AfterChangeNode, BeforeChangeNode) == 0)
				cout << "修改的考生不存在，操作失败！" << endl;//代码的健壮性，如果考生不存在则会提示
			else
			{
				cout << "被修改的考生原先的信息如下：" << endl;
				BeforeChangeNode.ShowNode();
				cout << "修改后的考生信息库如下：" << endl;
				StudentSystem.ShowList();
			}
			cout << endl;
		}
		//4-查找操作
		else if (KeyDown == 4)
		{
			cout << "请输入你要查找的考生考号：";
			int id;
			while (1)
			{
				cin >> id;
				if (cin.good() == 0 || id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误！请重新请输入要查找学生的学号：";
					continue;
				}
				break;
			}//代码的健壮性，保证输入要查找的学生学号的准确性
			if (StudentSystem.Search(id) == -1)
			{
				cout << "查找的考生不存在，操作失败！" << endl;
				cout << endl;
			}//代码的健壮性，如果查找的考生不存在则会提示
			else
			{
				int Location = StudentSystem.Search(id);
				cout << "考号为" << id << "的考生信息如下：" << endl;
				cout << "考号\t" << "姓名\t" << "性别\t" << "年龄\t" << "报考类型\t" << endl;
				(*StudentSystem.Located(Location)).ShowNode();
				cout << endl;
			}
		}
		//5-统计操作
		else if (KeyDown == 5)
		{
			StudentSystem.Length();
			StudentSystem.ShowList();
			cout << endl;
		}
	}
	system("pause");
	return 0;
}
