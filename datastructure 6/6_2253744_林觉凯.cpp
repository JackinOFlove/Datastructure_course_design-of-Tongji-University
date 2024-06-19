#include <iostream>
#include <cstring>
#define Max_namelength 5
#define Min_namelength 1
using namespace std;
//��ӡ�˵�����
void Print_Menu()
{
	cout << "**                  ���׹���ϵͳ                  **" << endl;
	cout << "====================================================" << endl;
	cout << "**               ��ѡ��Ҫִ�еĲ��� ��            **" << endl;
	cout << "**                A --- ���Ƽ���                  **" << endl;
	cout << "**                B --- ��Ӽ�ͥ��Ա              **" << endl;
	cout << "**                C --- ��ɢ�ֲ���ͥ              **" << endl;
	cout << "**                D --- ���ļ�ͥ��Ա����          **" << endl;
	cout << "**                E --- �˳�����                  **" << endl;
}
//���һ���ں���Χ�����������������д�����
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
//���һ���ڹ涨��Χ���ַ������������д�����
char Get_Char(string errortips)
{
	char retchar;
	cout << endl << "��ѡ��Ҫִ�еĲ�����";
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
//���һ���ڹ涨��Χ�ڵ�string�����������д�����
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
//���׳�Ա��
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
//��������
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
//�������ף���ʼ�����ڵ㣩
void FamilyTree::Establish()
{
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	string Ancestorname;
	Ancestorname = Get_String(Max_namelength, Min_namelength, "����������������룡");
	Ancestor = new Member;
	if (Ancestor == NULL)
	{
		cout << "���״���ʧ�ܣ�" << endl;
		system("pause");
		return;
	}
	Ancestor->name = Ancestorname;
	cout << "�˼��׵������ǣ�" << Ancestor->name << endl;
}
//��ӡ��current����������Ů
void FamilyTree::Show_Child(Member* current)
{
	if (current->firstChild != NULL)				//�����������
	{
		current = current->firstChild;				//�������
		cout << current->name << "  ";
		while (current->nextSibling != NULL)		//������ຢ�ӣ����ӵ��ֵܣ�
		{
			current = current->nextSibling;
			cout << current->name << "  ";
		}
	}
}
//���Һ������ڼ������в�������Ϊname�Ľ�㣬���ҵ����ظý�����ڵ�λ�ã��Ҳ�������NULL
Member* FamilyTree::Search(Member* current, string &name)
{
	Member* temp = new Member;
	if (current->name == name)							//����ҵ���ֱ�ӷ��ظý��
		return current;
	else 
	{
		if (current->firstChild != NULL)				//������Ӵ���
		{
			temp = Search(current->firstChild, name);	//����ݹ�����
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
			if (current->nextSibling != NULL)			//���ҵݹ�����
				return Search(current->nextSibling, name);
		}
	}
	return NULL;
}
//���Ƽ��׺���
void FamilyTree::Perfect_Operation()
{
	cout << "������Ҫ������ͥ���˵�������";
	string name = Get_String(Max_namelength, Min_namelength, "����������������룡");
	int Child_number;
	Member* current = Search(Ancestor, name);
	Member* Save_current = current;
	if (current == NULL)								//���current�Ҳ�������˵�������ڴ���
	{
		cout << "���޴��ˣ������²�����" << endl;
		return;
	}
	cout << "������" << name << "�Ķ�Ů������";
	Child_number = Get_Int("����������������룡");
	cout << "����������" << name << "�Ķ�Ů��������";
	string tempname;
	for (int i = 0; i < Child_number; i++)
	{
		if (i == 0)										//��һ������������ӣ����ӣ�
		{
			Member* Newchild = new Member;
			tempname = Get_String(Max_namelength, Min_namelength, "����������������룡");
			Newchild->name = tempname;
			current->firstChild = Newchild;
			current = Newchild;
		}
		else
		{
			Member* Newchild = new Member;				//֮������������ֵ�
			tempname = Get_String(Max_namelength, Min_namelength, "����������������룡");
			Newchild->name = tempname;
			current->nextSibling = Newchild;
			current = Newchild;
		}
	}
	cout << name << "�ĵ�һ�������ǣ�";
	Show_Child(Save_current);
	cout << endl;
}
//��Ӽ��׺���
void FamilyTree::Add_Operation()
{
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	string name = Get_String(Max_namelength, Min_namelength, "����������������룡");
	Member* current = Search(Ancestor, name);
	Member* Save_current = current;
	if (current == NULL)								//���current�Ҳ�������˵�������ڴ���
	{
		cout << "���޴��ˣ������²�����" << endl;
		return;
	}
	cout << "������" << name << "����ӵĶ��ӣ���Ů����������:";
	string Add_childname = Get_String(Max_namelength, Min_namelength, "����������������룡");
	if (current->firstChild == NULL)					//��������ڳ��ӣ�����ӵĺ���Ϊ����
	{
		Member* Newchild = new Member;
		Newchild->name = Add_childname;
		current->firstChild = Newchild;
	}
	else
	{													//������ڳ��ӣ�����ӵĺ���Ϊ���ֵ�
		current = current->firstChild;
		while (current->nextSibling != NULL)
			current = current->nextSibling;
		Member* Newchild = new Member;
		Newchild->name = Add_childname;
		current->nextSibling = Newchild;
	}
	cout << name << "�ĵ�һ�������ǣ�";
	Show_Child(Save_current);
	cout << endl;
}
//��ɢ�ֲ���ͥ����
void FamilyTree::Dissolve_Operation()
{
	cout << "������Ҫɾ����ͥ���˵�������";
	string name = Get_String(Max_namelength, Min_namelength, "����������������룡");
	Member* current = Search(Ancestor, name);
	if (current == NULL)								//���current�Ҳ�������˵�������ڴ���
	{
		cout << "���޴��ˣ������²�����" << endl;
		return;
	}						
	if (current->firstChild == NULL)					//������������ӣ���˵����û�м�ͥ
	{
		cout << "Ҫ��ɢ��ͥ����" << name << "û�м�ͥ�������²�����" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;
	cout << name << "�ĵ�һ�������ǣ�";
	Show_Child(current);
	current->firstChild = NULL;
	cout << endl;
	
}
//������������
void FamilyTree::Change_Operation()
{
	cout << "������Ҫ�����������˵�Ŀǰ��������";
	string Origin_name = Get_String(Max_namelength, Min_namelength, "����������������룡");
	Member* current = Search(Ancestor, Origin_name);
	if (current == NULL)								//���current�Ҳ�������˵�������ڴ���
	{
		cout << "���޴��ˣ������²�����" << endl;
		return;
	}
	else
	{
		cout << "��������ĺ��������";
		cin >> current->name;
		cout << Origin_name << "�Ѹ���Ϊ" << current->name << endl;
	}
}
//������
int main()
{
	Print_Menu();
	FamilyTree Jiapu;
	Jiapu.Establish();
	while (1)
	{
		char keydown = Get_Char("����������������룡");
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
			cout << endl << "���˳�����" << endl;
			system("pause");
			return 0;
		}
	}
	system("pause");
	return 0;
}