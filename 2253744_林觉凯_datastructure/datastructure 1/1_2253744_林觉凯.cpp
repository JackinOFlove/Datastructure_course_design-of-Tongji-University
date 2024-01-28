#include <iostream>
#include <cstring>
using namespace std;
class ListNode//������������(ListNode)��ÿһ����㴢����һ����������Ϣ����һ��������Ϣ�ĵ�ַ
{
public:
	int student_id;//����
	int student_age;//����
	string student_name;//����
	string student_sex;//�Ա�
	string student_category;//��������
	ListNode* next;//ָ����һ������ָ��
	ListNode(int number1 = 0, int number2 = 0, string str1 = "", string str2 = "", string str3 = "", ListNode* point = NULL)
	{
		student_id = number1;
		student_age = number2;
		student_name = str1;
		student_sex = str2;
		student_category = str3;
		next = NULL;
	}//���캯������ʼ����������Ϣ
	void ShowNode();//���в����������㿼���Ļ�����Ϣ
};
//���ĳ����㴢��Ŀ���������Ϣ����
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
	LinkList();									//���캯�����������Ա�����Ϣ��
	~LinkList();								//����������ʵ���ͷ��ڴ�
	void Length();								//���������ȣ������Ա���ϵͳ��������ͬʱ�ֱ�ͳ��������Ů��������
	void ShowList();							//������������ڵ�ÿ��������Ϣ
	int Search(int id);							//Ѱ�Һ���������һ�������Ŀ��ţ�������λ�����������е�λ�ã��ڼ�����
	ListNode* Located(int Location);			//��λ������������λ�����������е�λ�ã�������λ��������λ�õĵ�ַ
	bool Insert(int Location, ListNode& node);   //���뺯��������Ҫ���뿼����λ�úͻ�����Ϣ�����ز���ɹ���ʧ��
	bool Change(int Location, ListNode& anode, ListNode& bnode);	//�޸ĺ���������Ҫ�޸Ŀ�����λ�ã������޸ĳɹ���ʧ�ܣ�node���ڼ�¼�޸�ǰ�����Ļ�����Ϣ
	bool Delete(int Location, ListNode& node);	//ɾ������������Ҫɾ��������λ�ã����ز���ɹ���ʧ�ܣ�node���ڼ�¼ɾ���Ŀ����Ļ�����Ϣ
private:
	ListNode* head;                             //˽�г�Ա�������ͷ���
};
//���캯�����������Ա�����Ϣ��
LinkList::LinkList()
{
	head = NULL;					
	head = new ListNode;			//��ͷ������ռ�
	if (head == NULL)				//����Ľ�׳�ԣ��������ʧ����������ʾ
	{
		cout << "������ʧ�ܣ�" << endl;
		system("pause");
		return;
	}
	cout << "�����Ƚ���������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	int number;
	while (1)
	{
		cin >> number;
		if (cin.good() == 0 || number < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����Ŀ��������������������룺";		//���뽡׳�ԣ���֤����Ŀ���������������
			continue;
		}
		break;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������ͣ�" << endl;
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
				cout << "����ĵ�" << i + 1 << "λ�������Ŵ�����Ӵ��ʼ�������룬���ţ��������Ա����估�������ͣ�" << endl;
				continue;
			}								 //����Ľ�׳�ԣ����Ծ�ȷ�Ķ�λ������һλѧ�������뿼�Ŵ��󣬲��Ҵ� ���� ��ʼ��������
			break;
		}
		if (Search(current.student_id) != -1)//����Ľ�׳�ԣ����Է�ֹ������λ�����Ŀ�����ͬ
		{
			cout << "��" << i + 1 << "λ�Ŀ��������Ѿ����ڣ�����ʼ�������룬���ţ��������Ա����估�������ͣ�" << endl;
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
				cout << "����ĵ�" << i + 1 << "λ����������������ʼ�������룬�������Ա����估�������ͣ�" << endl;
				continue;						//����Ľ�׳�ԣ����Ծ�ȷ�Ķ�λ������һλѧ���������������󣬲��Ҵ� ���� ��ʼ��������
			}
			break;
		}
		while (1)
		{
			cin >> current.student_sex;
			if (cin.good() == 0 || current.student_sex != "��" && current.student_sex != "Ů")
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "����ĵ�" << i + 1 << "λ�����Ա���������ʼ�������룬�Ա����估�������ͣ�" << endl;
				continue;						//����Ľ�׳�ԣ����Ծ�ȷ�Ķ�λ������һλѧ���������Ա���󣬣�������Ա�ֻ���ǡ��С����ߡ�Ů�������Ҵ� ���� ��ʼ��������
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
				cout << "����ĵ�" << i + 1 << "λ����������������ʼ�������룬���䡢�������ͣ�" << endl;
				continue;						//����Ľ�׳�ԣ����Ծ�ȷ�Ķ�λ������һλѧ��������������󣬲��Ҵ� ���� ��ʼ��������
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
				cout << "����ĵ�" << i + 1 << "λ��������������������ʼ�������룬�������ͣ�" << endl;
				continue;						//����Ľ�׳�ԣ����Ծ�ȷ�Ķ�λ������һλѧ�������뱨�����ʹ��󣬲��Ҵ� ���� ��ʼ��������
			}
			break;
		}
		Insert(i, current);
	}
}
//����������ʵ���ͷ��ڴ�
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
//�������������ÿ��������Ϣ
void LinkList::ShowList()
{
	cout << "����\t" << "����\t" << "�Ա�\t" << "����\t" << "��������" << endl;
	ListNode* current = head->next;
	while (current != NULL)
	{
		cout << current->student_id << "\t" << current->student_name << "\t" << current->student_sex << "\t" << current->student_age << "\t" << current->student_category << endl;
		current = current->next;
	}
}
//���������ȣ������Ա���ϵͳ��������ͬʱ�ֱ�ͳ��������Ů��������
void LinkList::Length()
{
	int length = 0;						 //lengthΪ�����ȣ���������������
	int number_man = 0;
	int number_woman = 0;
	ListNode* current = head->next;		 //��ͷ��ʼɨ���������㳤��
	while (current != NULL)
	{
		if (current->student_sex == "��")
			number_man++;
		else
			number_woman++;
		current = current->next;
		length++;
	}
	cout << "һ����" << length << "��������" << "��������" << number_man << "����Ů��" << number_woman << "�����������£�" << endl;
}
//Ѱ�Һ���������һ�������Ŀ��ţ�������λ�����������е�λ�ã��ڼ�����
int LinkList::Search(int id)			//ͨ�����Ŷ�λ��λ����������ڼ�λ
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
	return -1;							//���û���ҵ���λ�����������������ڣ���return -1
}
//��λ������������λ�����������е�λ�ã�������λ��������λ�õĵ�ַ
ListNode* LinkList::Located(int Location)	//��һ��Search���������ҵ�������������ڼ�λ��Located����������һλ�ĵ�ַ
{
	if (Location < 0)
		return NULL;						//����Ľ�׳�ԣ����LocationΪ����˵����λ�ò����ڣ�return NULL
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
//���뺯��������Ҫ���뿼����λ�úͻ�����Ϣ�����ز���ɹ���ʧ��
bool LinkList::Insert(int Location, ListNode& node)		
{
	ListNode* current = Located(Location);
	if (current == NULL)
		return false;								//����Ľ�׳�ԣ�����õ�ַ�����ڷ���false
	else
	{
		ListNode* Newnode = new ListNode(node);
		if (Newnode == NULL)
		{
			cout << "�������㹹��ʧ�ܣ�" << endl;	//����Ľ�׳�ԣ��������ʧ�������ʾ
			return false;				
		}
		Newnode->next = current->next;				//�����µĽ��
		current->next = Newnode;
		return true;
	}
}
//ɾ������������Ҫɾ��������λ�ã���main������������ѧ�ţ�ͨ��Search��������һ��λ�ã��������������һ������Ϊ��ɾ��������λ�ü��ɣ�������ɾ���ɹ���ʧ�ܣ�node���ڼ�¼ɾ���Ŀ����Ļ�����Ϣ
bool LinkList::Delete(int Location, ListNode& node)
{
	ListNode* current, * temp = NULL;
	current = Located(Location - 1);					//�õ���ɾ������ǰһ����ַ
	if (current == NULL || current->next == NULL)
		return false;									//����Ľ�׳�ԣ������ǰ������һ����㲻���ڣ��޷�����ɾ������
	else
	{
		temp = current->next;
		current->next = temp->next;
		node.student_id = temp->student_id;
		node.student_age = temp->student_age;
		node.student_name = temp->student_name;
		node.student_sex = temp->student_sex;
		node.student_category = temp->student_category;	//node��������ɾ�������Ϣ
		delete temp;									//ɾ�����
		return true;
	}
}
//�޸ĺ���������Ҫ�޸Ŀ�����λ�ã�����main������������ѧ�ţ�ͨ��Search��������һ��λ�ã��������������һ������Ϊ���޸Ŀ�����λ�ü��ɣ��������޸ĳɹ���ʧ�ܣ�anodeΪ�޸ĺ����Ļ�����Ϣ��bnode���ڼ�¼�޸�ǰ�����Ļ�����Ϣ
bool LinkList::Change(int Location, ListNode& anode, ListNode& bnode)
{
	ListNode* current = Located(Location);
	if (current == NULL)
		return false;
	else
	{
		Delete(Location, bnode);		//����Delete����ɾ��������
		Insert(Location - 1, anode);	//����Insert������ɾ��������������µĽ�㣬����޸�
	}
	return true;
}
int main()
{
	LinkList StudentSystem;				//LinkList���ʵ����
	StudentSystem.ShowList();
	cout << endl;
	int KeyDown;
	cout << "��������Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ�޸ģ�4Ϊ���ң�5Ϊͳ�ƣ�0Ϊ�˳�������" << endl;
	//����Ľ�׳�ԣ���֤����Ĳ�������Ϊ0��1��2��3��4��5
	while (1)
	{
		cout << "��������Ҫ���еĲ�����";
		while (1)
		{
			cin >> KeyDown;
			if (cin.good() == 0 || KeyDown < 0 || KeyDown > 5)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "���������������������Ҫ���еĲ�����";
				continue;
			}
			break;
		}
		//0-�˳�����
		if (KeyDown == 0)
		{
			cout << "���Խ��������˳�����" << endl;
			break;
		}
		//1-�������
		else if (KeyDown == 1)
		{
			cout << "��������Ҫ����Ŀ�����λ�ã�";
			int location;
			while (1)
			{
				cin >> location;
				if (cin.good() == 0 || location < 0)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "�������������������Ҫ����ѧ����λ�ã�";
					continue;
				}
				break;
			}
			cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
			ListNode NewNode;
			while (1)
			{
				cin >> NewNode.student_id;
				if (cin.good() == 0 || NewNode.student_id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "�������������������Ҫ����ѧ���Ŀ��ţ�";
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
					cout << "���������Ӵ��ʼ����Ҫ����ѧ�����������Ա����估������Ŀ��";
					continue;
				}
				break;
			}
			while (1)
			{
				cin >> NewNode.student_sex;
				if (cin.good() == 0 || NewNode.student_sex != "��" && NewNode.student_sex != "Ů")
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "���������Ӵ��ʼ����Ҫ����ѧ�����Ա����估������Ŀ��";
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
					cout << "���������Ӵ��ʼ����Ҫ����ѧ�������䡢������Ŀ��";
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
					cout << "�������������������Ҫ����ѧ���ı�����Ŀ��";
					continue;
				}
				break;
			}//����Ľ�׳�ԣ���֤���뿼����Ϣ��׼ȷ��
			if (StudentSystem.Insert(location - 1, NewNode) == 0)
			{
				cout << "����λ�ò��Ϸ�������ʧ�ܣ�" << endl;
			}//����Ľ�׳�ԣ��Բ���λ�ò��Ϸ�����ʾ
			StudentSystem.ShowList();
			cout << endl;
		}
		//2-ɾ������
		else if (KeyDown == 2)
		{
			cout << "��������Ҫɾ���Ŀ������ţ�";
			int id;
			while (1)
			{
				cin >> id;
				if (cin.good() == 0 || id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "�������������������Ҫɾ��ѧ����ѧ�ţ�";
					continue;
				}
				break;
			}
			int Location = StudentSystem.Search(id);			//��ѧ�ű�Ϊ��ѧ�����������λ��
			ListNode DeleteNode;
			if (StudentSystem.Delete(Location, DeleteNode) == 0)
			{
				cout << "ɾ��ѧ�������ڣ������²�����" << endl;  //����Ľ�׳�ԣ���û�и�ѧ������ʾ
				continue;
			}
			else
			{
				cout << "ɾ���Ŀ�����Ϣ���£�" << endl;
				DeleteNode.ShowNode();
			}
			cout << "ɾ����Ŀ�����Ϣ�����£�" << endl;
			StudentSystem.ShowList();
			cout << endl;
		}
		//3-�޸Ĳ���
		else if (KeyDown == 3)
		{
			cout << "��������Ҫ�޸ĵĿ������ţ�";
			int id;
			while (1)
			{
				cin >> id;
				if (cin.good() == 0 || id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "�������������������Ҫ�޸�ѧ����ѧ�ţ�";
					continue;
				}
				break;
			}//����Ľ�׳�ԣ���֤�����ѧ�ŵ���ȷ��
			ListNode AfterChangeNode;
			ListNode BeforeChangeNode;
			cout << "�����������޸ĺ����Ŀ��ţ��������Ա����估�������" << endl;
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
						cout << "�޸ĵĿ������Ŵ�����Ӵ��ʼ�������룬���ţ��������Ա����估�������ͣ�" << endl;
						continue;
					}
					break;
				}
				if (StudentSystem.Search(temp_student_id) != -1)
				{
					cout << "�޸ĵĺ��������Ѿ����ڣ�����ʼ�������룬���ţ��������Ա����估�������ͣ�" << endl;
					i--;
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}//����Ľ�׳�ԣ�����޸ĺ�Ŀ���ѧ���Ѵ��ڣ�������ʾ
				AfterChangeNode.student_id = temp_student_id;
				while (1)
				{
					cin >> AfterChangeNode.student_name;
					if (cin.good() == 0 || AfterChangeNode.student_name.size() < 2 || AfterChangeNode.student_name.size() > 10)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "�޸ĵĿ���������������ʼ�������룬�������Ա����估�������ͣ�" << endl;
						continue;
					}
					break;
				}
				while (1)
				{
					cin >> AfterChangeNode.student_sex;
					if (cin.good() == 0 || AfterChangeNode.student_sex != "��" && AfterChangeNode.student_sex != "Ů")
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "�޸ĵĿ����Ա���������ʼ�������룬�Ա����估�������ͣ�" << endl;
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
						cout << "�޸ĵĿ���������������ʼ�������룬���䡢�������ͣ�" << endl;
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
						cout << "�޸ĵĿ�������������������ʼ�������룬�������ͣ�" << endl;
						continue;
					}
					break;
				}//����Ľ�׳�ԣ���֤�����޸ĺ��ѧ����Ϣ����ȷ��
			}
			int Location = StudentSystem.Search(id);
			if (StudentSystem.Change(Location, AfterChangeNode, BeforeChangeNode) == 0)
				cout << "�޸ĵĿ��������ڣ�����ʧ�ܣ�" << endl;//����Ľ�׳�ԣ�������������������ʾ
			else
			{
				cout << "���޸ĵĿ���ԭ�ȵ���Ϣ���£�" << endl;
				BeforeChangeNode.ShowNode();
				cout << "�޸ĺ�Ŀ�����Ϣ�����£�" << endl;
				StudentSystem.ShowList();
			}
			cout << endl;
		}
		//4-���Ҳ���
		else if (KeyDown == 4)
		{
			cout << "��������Ҫ���ҵĿ������ţ�";
			int id;
			while (1)
			{
				cin >> id;
				if (cin.good() == 0 || id < 1)
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "�������������������Ҫ����ѧ����ѧ�ţ�";
					continue;
				}
				break;
			}//����Ľ�׳�ԣ���֤����Ҫ���ҵ�ѧ��ѧ�ŵ�׼ȷ��
			if (StudentSystem.Search(id) == -1)
			{
				cout << "���ҵĿ��������ڣ�����ʧ�ܣ�" << endl;
				cout << endl;
			}//����Ľ�׳�ԣ�������ҵĿ��������������ʾ
			else
			{
				int Location = StudentSystem.Search(id);
				cout << "����Ϊ" << id << "�Ŀ�����Ϣ���£�" << endl;
				cout << "����\t" << "����\t" << "�Ա�\t" << "����\t" << "��������\t" << endl;
				(*StudentSystem.Located(Location)).ShowNode();
				cout << endl;
			}
		}
		//5-ͳ�Ʋ���
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
