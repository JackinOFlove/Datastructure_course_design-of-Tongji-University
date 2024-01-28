#include<iostream>
using namespace std;
class BSTnode									//���������������
{
public:
	int data;									//��ֵ
	BSTnode* leftchild;							//����
	BSTnode* rightchild;						//�Һ���
	BSTnode(int number = 0, BSTnode* leftpoint = NULL, BSTnode* rightpoint = NULL)
	{
		data = number;
		leftchild = leftpoint;
		rightchild = rightpoint;
	}
};
class BST										//������������
{
public:
	BSTnode* root = NULL;
	void InitTree();										//��ʼ����������
	void DeleteTree(BSTnode* current);						//ɾ������������
	void InOrderTree(BSTnode* current);						//�����������������
	bool SearchNode(BSTnode* current, int target);			//���������������еĽ��
	bool InsertNode(BSTnode* current, BSTnode* NewBSTnode);	//��������������еĽ��
	void InsertOperation();									//�������
	void SearchOperation();									//��������
};
//���������������������ӡ����������
void BST::InOrderTree(BSTnode* current)
{
	if (current == NULL)
		return;
	InOrderTree(current->leftchild);
	cout << current->data << "->";
	InOrderTree(current->rightchild);
}
//ɾ���������������������õݹ飬ɾ�����н��
void BST::DeleteTree(BSTnode* current)
{
	if (current == NULL)
		return;
	if (current->leftchild == NULL)
		DeleteTree(current->leftchild);
	if (current->rightchild == NULL)
		DeleteTree(current->rightchild);
	delete current;
}
//��������������еĽ��
bool BST::InsertNode(BSTnode* current, BSTnode* NewBSTnode)
{
	if (current->data == NewBSTnode->data)		//���Ҫ����������ڶ������������д��ڣ�return false
		return false;
	if (current->data > NewBSTnode->data)		//���Ҫ���������С�ڵ�ǰ�������ݣ����������Ӽ������Ҳ���
	{
		if (current->leftchild != NULL)
			return InsertNode(current->leftchild, NewBSTnode);
		current->leftchild = NewBSTnode;
	}
	else if (current->data < NewBSTnode->data)	//���Ҫ��������ݴ��ڵ�ǰ�������ݣ��������Һ��Ӽ������Ҳ���
	{
		if (current->rightchild != NULL)
			return InsertNode(current->rightchild, NewBSTnode);
		current->rightchild = NewBSTnode;
	}
	return true;
}
//���õݹ����������������еĽ��
bool BST::SearchNode(BSTnode* current, int target)
{
	if (current == NULL)				//����Ҳ�����return false
		return false;
	if (current->data == target)		//����ҵ��ˣ�return true
		return true;					
	if (target < current->data)			//���Ҫ�ҵ�����С�ڵ�ǰ������ݣ������������Ӽ�����������	
		return SearchNode(current->leftchild, target);
	else
		return SearchNode(current->rightchild, target);	 //���Ҫ�ҵ����ݴ��ڵ�ǰ������ݣ����������Һ��Ӽ�����������
}
//��ʼ����������
void BST::InitTree()
{
	DeleteTree(root);					//ÿ�δ����µĶ���������ǰ��Ҫ��ԭ���Ķ������������
	root = NULL;
	cout << "�������������ֽ�����������������0��β��:" << endl;
	while (1)
	{
		int value;
		cin >> value;
		if (cin.good() == 0) {
			DeleteTree(root);
			BSTnode* root = NULL;
			cout << "�����������������: " << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;					//����Ľ�׳�Լ���
		}
		if (value == 0)
			break;
		BSTnode* NewBSTnode = new BSTnode;
		NewBSTnode->data = value;
		if (root == NULL)
			root = NewBSTnode;			//���һ��ʼ�ǿ��������ø����Ϊ��һ�����������
		else
		{
			bool operation = InsertNode(root, NewBSTnode);		//����InsertNode�ڸ���㴴��֮�������������
			if (operation == 0)
				cout << "��ֵ" << value << "������룬��Ϊ����һ�Ρ�" << endl;		//����Ľ�׳�ԣ����һ����ֵ�����Σ���Ϊ����һ��
		}
	}
}
//�������ݵĲ�������
void BST::InsertOperation()
{
	if (root == NULL)						//����ǿ���������ʾҪ���Ƚ�������������
	{
		cout << "�����Ƚ���������������";
		return;
	}
	int number;
	cout << "����������Ҫ��������֣�";
	while (1)
	{
		cin >> number;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룺";
			continue;
		}
		break;
	}											//����Ľ�׳�Լ���
	BSTnode* NewBSTnode = new BSTnode;
	NewBSTnode->data = number;
	bool insertoperation = InsertNode(root, NewBSTnode);	//����InsertNode��������
	if (insertoperation == 0)
		cout << "��ֵ" << number << "�Ѿ������ڶ�����������" << endl;		//������ݴ��������ʾ
	return;
}
//�������ݵĲ�������
void BST::SearchOperation()
{
	if (root == NULL)						//����ǿ���������ʾҪ���Ƚ�������������
	{
		cout << "�����Ƚ���������������";
		return;
	}
	int number;
	cout << "����������Ҫ���ҵ����֣�";
	while (1)
	{
		cin >> number;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룺";
			continue;
		}
		break;
	}										//����Ľ�׳�Լ���
	bool searchoperation = SearchNode(root, number);	//����SearchNode�������Ҹ������Ƿ����
	if (searchoperation == 1)
		cout << "����" << number << "�����ڶ�����������";
	else
		cout << "����" << number << "�������ڶ�����������";
}
//get_choice�������������������ֵĽ�׳�Լ��飬ͬʱ����һ����������
int get_choice()
{
	cout << endl << "��ѡ�������";
	int choice;
	while (1)
	{
		cin >> choice;
		if (cin.good() == 0 || choice < 1 || choice > 4)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룺";
			continue;
		}
		break;
	}
	return choice;
}
//Print_Menu��������ӡ�˵�����ʾ
void Print_Menu()
{
	cout << "**                 ����������                  **" << endl;
	cout << "=================================================" << endl;
	cout << "**             1 --- ��������������            **" << endl;
	cout << "**             2 --- ����Ԫ��                  **" << endl;
	cout << "**             3 --- ��ѯԪ��                  **" << endl;
	cout << "**             4 --- �˳�����                  **" << endl;
	cout << "=================================================" << endl;
}
//������������������߼��ṹ
int main()
{
	BST bst;			//ʵ����BST����������������
	Print_Menu();		//��ӡ�˵�
	int keydown;
	while (1)
	{
		keydown = get_choice();
		switch (keydown)
		{
		case 1:			//��������������
			bst.InitTree();
			cout << "The BST is:";
			bst.InOrderTree(bst.root);
			cout << endl;
			break;
		case 2:			//�������
			bst.InsertOperation();
			if (bst.root != 0)
			{
				cout << "The BST is:";
				bst.InOrderTree(bst.root);
			}
			cout << endl;
			break;
		case 3:			//���Ҳ���
			bst.SearchOperation();
			cout << endl;
			break;
		case 4:			//�˳�����
			cout << "�˳�����" << endl;
			system("pause");
			return 0;
		}
	}
	return 0;
}
