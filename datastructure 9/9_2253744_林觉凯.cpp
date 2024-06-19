#include<iostream>
using namespace std;
class BSTnode									//二叉排序树结点类
{
public:
	int data;									//数值
	BSTnode* leftchild;							//左孩子
	BSTnode* rightchild;						//右孩子
	BSTnode(int number = 0, BSTnode* leftpoint = NULL, BSTnode* rightpoint = NULL)
	{
		data = number;
		leftchild = leftpoint;
		rightchild = rightpoint;
	}
};
class BST										//二叉排序树类
{
public:
	BSTnode* root = NULL;
	void InitTree();										//初始二叉排序树
	void DeleteTree(BSTnode* current);						//删除二叉排序树
	void InOrderTree(BSTnode* current);						//中序遍历二叉排序树
	bool SearchNode(BSTnode* current, int target);			//搜索二叉排序树中的结点
	bool InsertNode(BSTnode* current, BSTnode* NewBSTnode);	//插入二叉排序树中的结点
	void InsertOperation();									//插入操作
	void SearchOperation();									//搜索操作
};
//中序遍历二叉排序树，打印二叉排序树
void BST::InOrderTree(BSTnode* current)
{
	if (current == NULL)
		return;
	InOrderTree(current->leftchild);
	cout << current->data << "->";
	InOrderTree(current->rightchild);
}
//删除二叉排序树函数，运用递归，删除所有结点
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
//插入二叉排序树中的结点
bool BST::InsertNode(BSTnode* current, BSTnode* NewBSTnode)
{
	if (current->data == NewBSTnode->data)		//如果要插入的数据在二叉树排序树中存在，return false
		return false;
	if (current->data > NewBSTnode->data)		//如果要插入的数据小于当前结点的数据，向它的左孩子继续查找插入
	{
		if (current->leftchild != NULL)
			return InsertNode(current->leftchild, NewBSTnode);
		current->leftchild = NewBSTnode;
	}
	else if (current->data < NewBSTnode->data)	//如果要插入的数据大于当前结点的数据，向它的右孩子继续查找插入
	{
		if (current->rightchild != NULL)
			return InsertNode(current->rightchild, NewBSTnode);
		current->rightchild = NewBSTnode;
	}
	return true;
}
//运用递归搜索二叉排序树中的结点
bool BST::SearchNode(BSTnode* current, int target)
{
	if (current == NULL)				//如果找不到，return false
		return false;
	if (current->data == target)		//如果找到了，return true
		return true;					
	if (target < current->data)			//如果要找的数据小于当前结点数据，则向它的左孩子继续搜索查找	
		return SearchNode(current->leftchild, target);
	else
		return SearchNode(current->rightchild, target);	 //如果要找的数据大于当前结点数据，则向它的右孩子继续搜索查找
}
//初始二叉排序树
void BST::InitTree()
{
	DeleteTree(root);					//每次创建新的二叉排序树前都要将原来的二叉排序树清空
	root = NULL;
	cout << "请依次输入数字建立二叉搜索树（以0结尾）:" << endl;
	while (1)
	{
		int value;
		cin >> value;
		if (cin.good() == 0) {
			DeleteTree(root);
			BSTnode* root = NULL;
			cout << "输入错误！请重新输入: " << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;					//代码的健壮性检验
		}
		if (value == 0)
			break;
		BSTnode* NewBSTnode = new BSTnode;
		NewBSTnode->data = value;
		if (root == NULL)
			root = NewBSTnode;			//如果一开始是空树，就让根结点为第一个输入的数据
		else
		{
			bool operation = InsertNode(root, NewBSTnode);		//调用InsertNode在根结点创建之后继续插入数据
			if (operation == 0)
				cout << "数值" << value << "多次输入，视为输入一次。" << endl;		//代码的健壮性，如果一个数值输入多次，视为输入一次
		}
	}
}
//插入数据的操作函数
void BST::InsertOperation()
{
	if (root == NULL)						//如果是空树，则提示要首先建立二叉排序树
	{
		cout << "请首先建立二叉排序树！";
		return;
	}
	int number;
	cout << "请输入你想要插入的数字：";
	while (1)
	{
		cin >> number;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误！请重新输入：";
			continue;
		}
		break;
	}											//代码的健壮性检验
	BSTnode* NewBSTnode = new BSTnode;
	NewBSTnode->data = number;
	bool insertoperation = InsertNode(root, NewBSTnode);	//调用InsertNode插入数据
	if (insertoperation == 0)
		cout << "数值" << number << "已经存在于二叉排序树中" << endl;		//如果数据存在则会提示
	return;
}
//查找数据的操作函数
void BST::SearchOperation()
{
	if (root == NULL)						//如果是空树，则提示要首先建立二叉排序树
	{
		cout << "请首先建立二叉排序树！";
		return;
	}
	int number;
	cout << "请输入你想要查找的数字：";
	while (1)
	{
		cin >> number;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误！请重新输入：";
			continue;
		}
		break;
	}										//代码的健壮性检验
	bool searchoperation = SearchNode(root, number);	//调用SearchNode函数查找该数据是否存在
	if (searchoperation == 1)
		cout << "数字" << number << "存在于二叉排序树中";
	else
		cout << "数字" << number << "不存在于二叉排序树中";
}
//get_choice函数，完成输入操作数字的健壮性检验，同时返回一个操作数字
int get_choice()
{
	cout << endl << "请选择操作：";
	int choice;
	while (1)
	{
		cin >> choice;
		if (cin.good() == 0 || choice < 1 || choice > 4)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入：";
			continue;
		}
		break;
	}
	return choice;
}
//Print_Menu函数，打印菜单并显示
void Print_Menu()
{
	cout << "**                 二叉排序树                  **" << endl;
	cout << "=================================================" << endl;
	cout << "**             1 --- 建立二叉排序树            **" << endl;
	cout << "**             2 --- 插入元素                  **" << endl;
	cout << "**             3 --- 查询元素                  **" << endl;
	cout << "**             4 --- 退出程序                  **" << endl;
	cout << "=================================================" << endl;
}
//主函数，程序的主体逻辑结构
int main()
{
	BST bst;			//实例化BST（二叉排序树）类
	Print_Menu();		//打印菜单
	int keydown;
	while (1)
	{
		keydown = get_choice();
		switch (keydown)
		{
		case 1:			//建立二叉排序树
			bst.InitTree();
			cout << "The BST is:";
			bst.InOrderTree(bst.root);
			cout << endl;
			break;
		case 2:			//插入操作
			bst.InsertOperation();
			if (bst.root != 0)
			{
				cout << "The BST is:";
				bst.InOrderTree(bst.root);
			}
			cout << endl;
			break;
		case 3:			//查找操作
			bst.SearchOperation();
			cout << endl;
			break;
		case 4:			//退出程序
			cout << "退出程序！" << endl;
			system("pause");
			return 0;
		}
	}
	return 0;
}
