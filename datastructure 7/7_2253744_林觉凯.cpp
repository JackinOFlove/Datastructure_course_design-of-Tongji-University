#include <iostream>
#include <cstring>
#define Max 100
using namespace std;
template <typename T>
class stack											//栈的模板类
{
public:
	stack();										//构造函数
	~stack();										//析构函数
	void Push(const T& item);						   	//将元素压入栈中
	T Pop();										//将栈顶元素移出
	T GetTop();									//取得栈顶元素
	bool is_Empty() { return top == -1; };					//判断栈是否为空
	bool is_Full() { return top == size; };					//判断栈是否已满
private:
	int top;										//栈顶
	int size = Max;									//栈的大小
	T* element;									//栈数组
};
template <typename T>
stack<T>::stack()
{
	element = new T[size + 1];							//为栈数组分配空间
	top = -1;										//top置为-1
}
template <typename T>
stack<T>::~stack()
{
	delete[] element;								//删除栈数组
	top = -1;										//top置为-1
}
template <typename T>
void stack<T>::Push(const T& item)
{
	if (is_Full())									//如果栈满，直接return
		return;
	else
		element[++top] = item;						//将元素压入栈中，同时top加一
}
template <typename T>
T stack<T>::Pop()
{
	if (top == -1)									//如果栈空，return -1
		exit(-1);
	else
		return element[top--];							//将元素退出，同时top减1
}
template <typename T>
T stack<T>::GetTop()
{
	if (top == -1)									//如果栈空，return -1
		exit(-1);
	else
		return element[top];							//取得栈顶元素
}
//判断输入的字符是否有价值（为数字或者运算符）
bool Is_value(char ch)					
{
	if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return true;					//有价值，return true
	else
		return false;					//没价值，return false
}
//判断操作符的优先级
int Priority(char ch)						
{
	if (ch == '+' || ch == '-')
		return 1;						//'+'、'-'返回1
	else if (ch == '*' || ch == '/')
		return 2;						//'*'、'/'返回2
	else
		return 0;						//'('、')'返回0
}
//二叉树结点类
class BitNode
{
public:
	string data;				//数据域（运算符或数值）
	BitNode* left;				//左指针
	BitNode* right;				//右指针
	BitNode() { data = ""; left = right = NULL; }
};
//二叉树类
class BitTree
{
public:
	BitTree(BitNode* node) { root = node; };
	~BitTree() {};
	void PreOrder(BitNode* current);	//前序遍历
	void PostOrder(BitNode* current);	//后续遍历
	BitNode* root;
};
//二叉树的前序遍历
void BitTree::PreOrder(BitNode* current)
{
	if (current != NULL)
	{
		if (current != NULL)
			cout << current->data;
		PreOrder(current->left);
		PreOrder(current->right);
	}
}
//二叉树的后序遍历
void BitTree::PostOrder(BitNode* current)
{
	if (current != NULL)
	{
		PostOrder(current->left);
		PostOrder(current->right);
		if (current->left == NULL && current->right == NULL)
			cout << current->data;
		else
			cout << current->data;
	}
}
//判断运算符的优先级之后调整二叉树子树栈中的元素（运算）
void Calculate(stack<BitNode*> &number, stack<char> &oper)
{
	BitNode* anewnode = new BitNode;		//结点anewnode为number栈中栈顶元素
	anewnode = number.GetTop();
	number.Pop();							//结点anewnode退栈，下一个结点bnewnode便为栈顶元素
	BitNode* bnewnode = new BitNode;		//结点bnewnode为number栈中栈顶元素
	bnewnode = number.GetTop();
	number.Pop();
	BitNode* current = new BitNode;			//新建结点current
	current->left = bnewnode;
	current->right = anewnode;
	current->data = oper.GetTop();			//新结点current包括原先两个栈顶元素和操作符栈的运算符
	number.Push(current);					//将新结点压入number栈中
	oper.Pop();								//刚刚做完运算的运算符栈栈顶元素退栈
}
//主函数的实现
int main()
{
	char expression[Max] = { 0 };
	cout << "请输入表达式:\t";
	cin.getline(&expression[1], Max);				//得到英文的中缀表达式
	cout << endl;
	stack<BitNode*>number;							//number栈，存放二叉树子树
	stack<char>oper;								//oper栈，存放运算符
	expression[0] = '(';							//此处在expression的前后各加一个括号，是为了防止当最后一个元素进number栈之后没有被插入到最后的二叉树中去
	int length = strlen(expression);
	expression[length] = ')';
	int i = 0;
	while (expression[i] != '\0')					//循环结束标志
	{
		if (!Is_value(expression[i]))				//输入错误的检验与忽略
		{
			cout << "输入的第" << i++ << "位存在非法字符，计算时忽略" << endl << endl;
			continue;
		}
		if (expression[i] >= '0' && expression[i] <= '9')	//当前字符是数字，直接压到number栈中去
		{
			BitNode* newnode = new BitNode;
			newnode->data = expression[i];
			newnode->left = NULL;
			newnode->right = NULL;
			number.Push(newnode);
		}
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '(' || expression[i] == ')')	//如果是运算符
		{
			if (expression[i] == '(')				//左括号压入运算符栈
				oper.Push(expression[i]);
			else if (expression[i] == ')')			//是右括号的话就要将括号里的元素进行计算了（合并为新的子树）
			{
				while (oper.GetTop() != '(')		//循环条件为还没遇到前面一个左括号
					Calculate(number, oper);
				oper.Pop();							//最后将左括号退栈
			}
			else if (oper.is_Empty() || Priority(expression[i]) > Priority(oper.GetTop()))	 //如果栈为空或者当前运算字符的优先级大于运算符栈顶运算符优先级
				oper.Push(expression[i]);			//压入运算符栈
			else if (!oper.is_Empty() && Priority(expression[i]) <= Priority(oper.GetTop())) //如果栈不为空或者当前运算字符的优先级小于等于运算符栈顶运算符优先级
			{
				while (!oper.is_Empty() && Priority(expression[i]) <= Priority(oper.GetTop()))	//这时就要对括号里的元素进行计算（建立新的子树）
					Calculate(number, oper);
				oper.Push(expression[i]);
			}
		}
		i++;
	}
	BitTree Exptree(number.GetTop());			//实例化表达式树
	cout << "波兰表达式：\t";
	Exptree.PreOrder(Exptree.root);				//前序遍历输出波兰表达式
	cout << endl << endl;
	cout << "中缀表达式：\t";
	for (int i = 1; i < length; i++)			//中缀表达式
	{
		if (Is_value(expression[i]))
			cout << expression[i];
	}
	cout << endl << endl;
	cout << "逆波兰表达式：\t";
	Exptree.PostOrder(Exptree.root);			//后序遍历输出逆波兰表达式
	cout << endl << endl;
	system("pause");
	return 0;
}

/*以下为我做的另一种方法
#include <iostream>
#include <cstring>
#define Max 100
using namespace std;
template <typename T>
class stack											//栈的模板类
{
public:
	stack();										//构造函数
	~stack();										//析构函数
	void Push(const T& item);						//将元素压入栈中
	T Pop();										//将栈顶元素移出
	T GetTop();										//取得栈顶元素
	bool is_Empty(){ return top == -1; };			//判断栈是否为空
	bool is_Full(){ return top == size; };			//判断栈是否已满
private:
	int top;										//栈顶
	int size = Max;									//栈的大小
	T* element;										//栈数组
};
template <typename T>
stack<T>::stack()
{
	element = new T[size + 1];						//为栈数组分配空间
	top = -1;										//top置为-1
}
template <typename T>
stack<T>::~stack()
{
	delete[] element;								//删除栈数组
	top = -1;										//top置为-1
}
template <typename T>
void stack<T>::Push(const T& item)
{
	if (is_Full())									//如果栈满，直接return
		return;
	else
		element[++top] = item;						//将元素压入栈中，同时top加一
}
template <typename T>
T stack<T>::Pop()
{
	if (top == -1)									//如果栈空，return -1
		return -1;
	else
		return element[top--];						//将元素退出，同时top减1
}
template <typename T>
T stack<T>::GetTop()
{
	if (top == -1)									//如果栈空，return -1
		return -1;
	else
		return element[top];						//取得栈顶元素
}
bool Is_value(char ch)								//判断输入的字符是否有价值（为数字或者运算符）
{
	if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return true;					//有价值，return true
	else
		return false;					//没价值，return false
}
int Priority(char ch)					//判断操作符的优先级
{
	if (ch == '+' || ch == '-')
		return 1;						//'+'、'-'返回1
	else if (ch == '*' || ch == '/')
		return 2;						//'*'、'/'返回2
	else
		return 0;						//'('、')'返回0
}
//中缀表达式转化为前缀表达式（波兰表达式）
char* Transform_Pre(char* expression)
{
	stack <char> Stack;								//原始栈Stack
	stack <char> result_stack;						//结果栈result_stack
	stack <char> operator_stack;					//运算符栈operator_stack
	int i = 0;
	//将表达式中的元素压入原始栈中
	while (expression[i] != '\0')
	{
		if (!Is_value(expression[i]))			//如果这个字符无价值，直接跳过，不压入栈中
		{
			i++;
			continue;
		}
		Stack.Push(expression[i]);				//字符有价值，压入栈中，同时i++
		i++;
	}
	//获得相对应的结果栈
	while (!Stack.is_Empty())					//当原始栈Stack不为空时
	{
		char temp = Stack.GetTop();				//得到原始栈Stack顶的字符元素
		Stack.Pop();							//原始栈Stack顶元素出栈
		if (temp >= '0' && temp <= '9')			//如果是数字，直接压入结果栈result_stack中
			result_stack.Push(temp);
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/')		//如果是'+'、'-'、'*'、'/'运算符
		{
			if (operator_stack.is_Empty() || Priority(temp) > Priority(operator_stack.GetTop()))
//如果运算符栈为空或者该运算符的优先级大于运算符栈顶运算符元素的优先级
				operator_stack.Push(temp);		//将该运算符压入运算符栈
			else if (Priority(temp) <= Priority(operator_stack.GetTop()))
//如果该运算符的优先级小于等于运算符栈顶运算符元素的优先级
			{
				while (!operator_stack.is_Empty() && Priority(temp) <= Priority(operator_stack.GetTop()))
//当循环条件为运算符栈不为空且要退出的元素的优先级小于等于该运算符
				{
					result_stack.Push(operator_stack.GetTop());
//此时就要将运算符栈中的元素退出到结果栈中
					operator_stack.Pop();
				}
				operator_stack.Push(temp);			//再将该运算符压入运算符栈中
			}
		}
		else										//如果是左括号或者右括号
		{
			if (temp == ')')						//如果是右括号
				operator_stack.Push(temp);			//直接将右括号压入栈中
			else									//如果是左括号，此时就要将运算符栈中先前的元素退出
			{
				while (operator_stack.GetTop() != ')')	//退出的循环条件是退出的运算符不为右括号
				{
					result_stack.Push(operator_stack.GetTop());
//将运算符栈顶元素退出并压入结果栈中
					operator_stack.Pop();
				}
				operator_stack.Pop();			//最后将右括号也出栈
			}
		}
	}
	while (!operator_stack.is_Empty())			//最后将运算符栈中剩余的元素压入结果栈中
	{
		result_stack.Push(operator_stack.GetTop());
		operator_stack.Pop();
	}
	//将结果栈中的元素转化为前缀表达式（波兰表达式）的字符串
	int j = 0;
	char* retchar = new char[Max];
	while (!result_stack.is_Empty())					//当结果栈不为空
	{
		retchar[j++] = result_stack.GetTop();			//将栈中元素转化到字符数组相对应的位置
		result_stack.Pop();						//结果栈元素出栈
	}
	retchar[j] = '\0';								//最后加一个'\0'
	return retchar;
}
//中缀表达式转化为后缀表达式（逆波兰表达式）
char* Transform_Post(char* expression)
{
	stack <char> Stack;							//原始栈Stack（中缀表达式转化为后缀表达式不需要再设一个结果栈和一个运算符栈）
	char* retchar = new char[Max];
	int index = 0;
	for (int i = 0; Is_value(expression[i]) && expression[i] != '\0'; i++)
//遍历中缀表达式中有价值的字符串
	{
		if (expression[i] >= '0' && expression[i] <= '9')	//当这个字符是数字
			retchar[index++] = expression[i];		//就不用压入栈中了，直接赋值给结果字符串
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
//如果是'+'、'-'、'*'、'/'运算符
		{
			if (Stack.is_Empty() || Priority(Stack.GetTop()) < Priority(expression[i]))
//如果栈为空或者栈顶的运算符优先级小于当前运算符优先级
				Stack.Push(expression[i]);
//将当前运算符压入栈中
			else
//其它情况就要将栈中的运算符退出栈了
			{
				while (!Stack.is_Empty() && Priority(Stack.GetTop()) >= Priority(expression[i]))
//循环条件为栈不为空而且要退出的运算符大等于当前运算符
				{
					retchar[index++] = Stack.GetTop();
//将栈顶运算符元素赋给结果字符串
					Stack.Pop();
//栈Stack顶元素退栈
				}
				Stack.Push(expression[i]);
//最后将该运算符压入栈中
			}
		}
		else
	//如果是左括号或者右括号
		{
			if (expression[i] == '(')					//如果是左括号的话，压入栈中
				Stack.Push(expression[i]);
			else									//如果是右括号，则要有序地退栈
			{
				while (Stack.GetTop() != '(')			//退栈的循环条件为还没有遇到左括号
				{
					retchar[index++] = Stack.GetTop();	//将栈中元素赋值给结果字符串
					Stack.Pop();					//出栈
				}
				Stack.Pop();						//最后将左括号也出栈
			}
		}
	}
	while (!Stack.is_Empty())							//将栈中剩余的元素赋值给结果字符串
	{
		retchar[index++] = Stack.GetTop();
		Stack.Pop();
	}
	retchar[index] = '\0';								//最后加一个'\0'
	return retchar;
}
int main()
{
	char expression[Max];
	cout << "请输入表达式:\t";
	cin.getline(expression, Max);					//得到英文的中缀表达式
	cout << endl;
	char* Pre_string = Transform_Pre(expression);		//中缀表达式转化为前缀表达式（波兰表达式）
	cout << "波兰表达式：\t" << Pre_string << endl << endl;
	cout << "中缀表达式：\t" << expression << endl << endl;
	char* Post_string = Transform_Post(expression);		//中缀表达式转化为后缀表达式（逆波兰表达式）
	cout << "逆波兰表达式：\t" << Post_string << endl << endl;
	system("pause");
	return 0;
}
*/