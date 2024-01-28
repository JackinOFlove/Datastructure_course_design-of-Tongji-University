#include <iostream>
#include <cstring>
#define Max 100
using namespace std;
template <typename T>
class stack											//ջ��ģ����
{
public:
	stack();										//���캯��
	~stack();										//��������
	void Push(const T& item);						   	//��Ԫ��ѹ��ջ��
	T Pop();										//��ջ��Ԫ���Ƴ�
	T GetTop();									//ȡ��ջ��Ԫ��
	bool is_Empty() { return top == -1; };					//�ж�ջ�Ƿ�Ϊ��
	bool is_Full() { return top == size; };					//�ж�ջ�Ƿ�����
private:
	int top;										//ջ��
	int size = Max;									//ջ�Ĵ�С
	T* element;									//ջ����
};
template <typename T>
stack<T>::stack()
{
	element = new T[size + 1];							//Ϊջ�������ռ�
	top = -1;										//top��Ϊ-1
}
template <typename T>
stack<T>::~stack()
{
	delete[] element;								//ɾ��ջ����
	top = -1;										//top��Ϊ-1
}
template <typename T>
void stack<T>::Push(const T& item)
{
	if (is_Full())									//���ջ����ֱ��return
		return;
	else
		element[++top] = item;						//��Ԫ��ѹ��ջ�У�ͬʱtop��һ
}
template <typename T>
T stack<T>::Pop()
{
	if (top == -1)									//���ջ�գ�return -1
		exit(-1);
	else
		return element[top--];							//��Ԫ���˳���ͬʱtop��1
}
template <typename T>
T stack<T>::GetTop()
{
	if (top == -1)									//���ջ�գ�return -1
		exit(-1);
	else
		return element[top];							//ȡ��ջ��Ԫ��
}
//�ж�������ַ��Ƿ��м�ֵ��Ϊ���ֻ����������
bool Is_value(char ch)					
{
	if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return true;					//�м�ֵ��return true
	else
		return false;					//û��ֵ��return false
}
//�жϲ����������ȼ�
int Priority(char ch)						
{
	if (ch == '+' || ch == '-')
		return 1;						//'+'��'-'����1
	else if (ch == '*' || ch == '/')
		return 2;						//'*'��'/'����2
	else
		return 0;						//'('��')'����0
}
//�����������
class BitNode
{
public:
	string data;				//���������������ֵ��
	BitNode* left;				//��ָ��
	BitNode* right;				//��ָ��
	BitNode() { data = ""; left = right = NULL; }
};
//��������
class BitTree
{
public:
	BitTree(BitNode* node) { root = node; };
	~BitTree() {};
	void PreOrder(BitNode* current);	//ǰ�����
	void PostOrder(BitNode* current);	//��������
	BitNode* root;
};
//��������ǰ�����
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
//�������ĺ������
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
//�ж�����������ȼ�֮���������������ջ�е�Ԫ�أ����㣩
void Calculate(stack<BitNode*> &number, stack<char> &oper)
{
	BitNode* anewnode = new BitNode;		//���anewnodeΪnumberջ��ջ��Ԫ��
	anewnode = number.GetTop();
	number.Pop();							//���anewnode��ջ����һ�����bnewnode��Ϊջ��Ԫ��
	BitNode* bnewnode = new BitNode;		//���bnewnodeΪnumberջ��ջ��Ԫ��
	bnewnode = number.GetTop();
	number.Pop();
	BitNode* current = new BitNode;			//�½����current
	current->left = bnewnode;
	current->right = anewnode;
	current->data = oper.GetTop();			//�½��current����ԭ������ջ��Ԫ�غͲ�����ջ�������
	number.Push(current);					//���½��ѹ��numberջ��
	oper.Pop();								//�ո���������������ջջ��Ԫ����ջ
}
//��������ʵ��
int main()
{
	char expression[Max] = { 0 };
	cout << "��������ʽ:\t";
	cin.getline(&expression[1], Max);				//�õ�Ӣ�ĵ���׺���ʽ
	cout << endl;
	stack<BitNode*>number;							//numberջ����Ŷ���������
	stack<char>oper;								//operջ����������
	expression[0] = '(';							//�˴���expression��ǰ�����һ�����ţ���Ϊ�˷�ֹ�����һ��Ԫ�ؽ�numberջ֮��û�б����뵽���Ķ�������ȥ
	int length = strlen(expression);
	expression[length] = ')';
	int i = 0;
	while (expression[i] != '\0')					//ѭ��������־
	{
		if (!Is_value(expression[i]))				//�������ļ��������
		{
			cout << "����ĵ�" << i++ << "λ���ڷǷ��ַ�������ʱ����" << endl << endl;
			continue;
		}
		if (expression[i] >= '0' && expression[i] <= '9')	//��ǰ�ַ������֣�ֱ��ѹ��numberջ��ȥ
		{
			BitNode* newnode = new BitNode;
			newnode->data = expression[i];
			newnode->left = NULL;
			newnode->right = NULL;
			number.Push(newnode);
		}
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '(' || expression[i] == ')')	//����������
		{
			if (expression[i] == '(')				//������ѹ�������ջ
				oper.Push(expression[i]);
			else if (expression[i] == ')')			//�������ŵĻ���Ҫ���������Ԫ�ؽ��м����ˣ��ϲ�Ϊ�µ�������
			{
				while (oper.GetTop() != '(')		//ѭ������Ϊ��û����ǰ��һ��������
					Calculate(number, oper);
				oper.Pop();							//�����������ջ
			}
			else if (oper.is_Empty() || Priority(expression[i]) > Priority(oper.GetTop()))	 //���ջΪ�ջ��ߵ�ǰ�����ַ������ȼ����������ջ����������ȼ�
				oper.Push(expression[i]);			//ѹ�������ջ
			else if (!oper.is_Empty() && Priority(expression[i]) <= Priority(oper.GetTop())) //���ջ��Ϊ�ջ��ߵ�ǰ�����ַ������ȼ�С�ڵ��������ջ����������ȼ�
			{
				while (!oper.is_Empty() && Priority(expression[i]) <= Priority(oper.GetTop()))	//��ʱ��Ҫ���������Ԫ�ؽ��м��㣨�����µ�������
					Calculate(number, oper);
				oper.Push(expression[i]);
			}
		}
		i++;
	}
	BitTree Exptree(number.GetTop());			//ʵ�������ʽ��
	cout << "�������ʽ��\t";
	Exptree.PreOrder(Exptree.root);				//ǰ���������������ʽ
	cout << endl << endl;
	cout << "��׺���ʽ��\t";
	for (int i = 1; i < length; i++)			//��׺���ʽ
	{
		if (Is_value(expression[i]))
			cout << expression[i];
	}
	cout << endl << endl;
	cout << "�沨�����ʽ��\t";
	Exptree.PostOrder(Exptree.root);			//�����������沨�����ʽ
	cout << endl << endl;
	system("pause");
	return 0;
}

/*����Ϊ��������һ�ַ���
#include <iostream>
#include <cstring>
#define Max 100
using namespace std;
template <typename T>
class stack											//ջ��ģ����
{
public:
	stack();										//���캯��
	~stack();										//��������
	void Push(const T& item);						//��Ԫ��ѹ��ջ��
	T Pop();										//��ջ��Ԫ���Ƴ�
	T GetTop();										//ȡ��ջ��Ԫ��
	bool is_Empty(){ return top == -1; };			//�ж�ջ�Ƿ�Ϊ��
	bool is_Full(){ return top == size; };			//�ж�ջ�Ƿ�����
private:
	int top;										//ջ��
	int size = Max;									//ջ�Ĵ�С
	T* element;										//ջ����
};
template <typename T>
stack<T>::stack()
{
	element = new T[size + 1];						//Ϊջ�������ռ�
	top = -1;										//top��Ϊ-1
}
template <typename T>
stack<T>::~stack()
{
	delete[] element;								//ɾ��ջ����
	top = -1;										//top��Ϊ-1
}
template <typename T>
void stack<T>::Push(const T& item)
{
	if (is_Full())									//���ջ����ֱ��return
		return;
	else
		element[++top] = item;						//��Ԫ��ѹ��ջ�У�ͬʱtop��һ
}
template <typename T>
T stack<T>::Pop()
{
	if (top == -1)									//���ջ�գ�return -1
		return -1;
	else
		return element[top--];						//��Ԫ���˳���ͬʱtop��1
}
template <typename T>
T stack<T>::GetTop()
{
	if (top == -1)									//���ջ�գ�return -1
		return -1;
	else
		return element[top];						//ȡ��ջ��Ԫ��
}
bool Is_value(char ch)								//�ж�������ַ��Ƿ��м�ֵ��Ϊ���ֻ����������
{
	if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return true;					//�м�ֵ��return true
	else
		return false;					//û��ֵ��return false
}
int Priority(char ch)					//�жϲ����������ȼ�
{
	if (ch == '+' || ch == '-')
		return 1;						//'+'��'-'����1
	else if (ch == '*' || ch == '/')
		return 2;						//'*'��'/'����2
	else
		return 0;						//'('��')'����0
}
//��׺���ʽת��Ϊǰ׺���ʽ���������ʽ��
char* Transform_Pre(char* expression)
{
	stack <char> Stack;								//ԭʼջStack
	stack <char> result_stack;						//���ջresult_stack
	stack <char> operator_stack;					//�����ջoperator_stack
	int i = 0;
	//�����ʽ�е�Ԫ��ѹ��ԭʼջ��
	while (expression[i] != '\0')
	{
		if (!Is_value(expression[i]))			//�������ַ��޼�ֵ��ֱ����������ѹ��ջ��
		{
			i++;
			continue;
		}
		Stack.Push(expression[i]);				//�ַ��м�ֵ��ѹ��ջ�У�ͬʱi++
		i++;
	}
	//������Ӧ�Ľ��ջ
	while (!Stack.is_Empty())					//��ԭʼջStack��Ϊ��ʱ
	{
		char temp = Stack.GetTop();				//�õ�ԭʼջStack�����ַ�Ԫ��
		Stack.Pop();							//ԭʼջStack��Ԫ�س�ջ
		if (temp >= '0' && temp <= '9')			//��������֣�ֱ��ѹ����ջresult_stack��
			result_stack.Push(temp);
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/')		//�����'+'��'-'��'*'��'/'�����
		{
			if (operator_stack.is_Empty() || Priority(temp) > Priority(operator_stack.GetTop()))
//��������ջΪ�ջ��߸�����������ȼ����������ջ�������Ԫ�ص����ȼ�
				operator_stack.Push(temp);		//���������ѹ�������ջ
			else if (Priority(temp) <= Priority(operator_stack.GetTop()))
//���������������ȼ�С�ڵ��������ջ�������Ԫ�ص����ȼ�
			{
				while (!operator_stack.is_Empty() && Priority(temp) <= Priority(operator_stack.GetTop()))
//��ѭ������Ϊ�����ջ��Ϊ����Ҫ�˳���Ԫ�ص����ȼ�С�ڵ��ڸ������
				{
					result_stack.Push(operator_stack.GetTop());
//��ʱ��Ҫ�������ջ�е�Ԫ���˳������ջ��
					operator_stack.Pop();
				}
				operator_stack.Push(temp);			//�ٽ��������ѹ�������ջ��
			}
		}
		else										//����������Ż���������
		{
			if (temp == ')')						//�����������
				operator_stack.Push(temp);			//ֱ�ӽ�������ѹ��ջ��
			else									//����������ţ���ʱ��Ҫ�������ջ����ǰ��Ԫ���˳�
			{
				while (operator_stack.GetTop() != ')')	//�˳���ѭ���������˳����������Ϊ������
				{
					result_stack.Push(operator_stack.GetTop());
//�������ջ��Ԫ���˳���ѹ����ջ��
					operator_stack.Pop();
				}
				operator_stack.Pop();			//���������Ҳ��ջ
			}
		}
	}
	while (!operator_stack.is_Empty())			//��������ջ��ʣ���Ԫ��ѹ����ջ��
	{
		result_stack.Push(operator_stack.GetTop());
		operator_stack.Pop();
	}
	//�����ջ�е�Ԫ��ת��Ϊǰ׺���ʽ���������ʽ�����ַ���
	int j = 0;
	char* retchar = new char[Max];
	while (!result_stack.is_Empty())					//�����ջ��Ϊ��
	{
		retchar[j++] = result_stack.GetTop();			//��ջ��Ԫ��ת�����ַ��������Ӧ��λ��
		result_stack.Pop();						//���ջԪ�س�ջ
	}
	retchar[j] = '\0';								//����һ��'\0'
	return retchar;
}
//��׺���ʽת��Ϊ��׺���ʽ���沨�����ʽ��
char* Transform_Post(char* expression)
{
	stack <char> Stack;							//ԭʼջStack����׺���ʽת��Ϊ��׺���ʽ����Ҫ����һ�����ջ��һ�������ջ��
	char* retchar = new char[Max];
	int index = 0;
	for (int i = 0; Is_value(expression[i]) && expression[i] != '\0'; i++)
//������׺���ʽ���м�ֵ���ַ���
	{
		if (expression[i] >= '0' && expression[i] <= '9')	//������ַ�������
			retchar[index++] = expression[i];		//�Ͳ���ѹ��ջ���ˣ�ֱ�Ӹ�ֵ������ַ���
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
//�����'+'��'-'��'*'��'/'�����
		{
			if (Stack.is_Empty() || Priority(Stack.GetTop()) < Priority(expression[i]))
//���ջΪ�ջ���ջ������������ȼ�С�ڵ�ǰ��������ȼ�
				Stack.Push(expression[i]);
//����ǰ�����ѹ��ջ��
			else
//���������Ҫ��ջ�е�������˳�ջ��
			{
				while (!Stack.is_Empty() && Priority(Stack.GetTop()) >= Priority(expression[i]))
//ѭ������Ϊջ��Ϊ�ն���Ҫ�˳������������ڵ�ǰ�����
				{
					retchar[index++] = Stack.GetTop();
//��ջ�������Ԫ�ظ�������ַ���
					Stack.Pop();
//ջStack��Ԫ����ջ
				}
				Stack.Push(expression[i]);
//��󽫸������ѹ��ջ��
			}
		}
		else
	//����������Ż���������
		{
			if (expression[i] == '(')					//����������ŵĻ���ѹ��ջ��
				Stack.Push(expression[i]);
			else									//����������ţ���Ҫ�������ջ
			{
				while (Stack.GetTop() != '(')			//��ջ��ѭ������Ϊ��û������������
				{
					retchar[index++] = Stack.GetTop();	//��ջ��Ԫ�ظ�ֵ������ַ���
					Stack.Pop();					//��ջ
				}
				Stack.Pop();						//���������Ҳ��ջ
			}
		}
	}
	while (!Stack.is_Empty())							//��ջ��ʣ���Ԫ�ظ�ֵ������ַ���
	{
		retchar[index++] = Stack.GetTop();
		Stack.Pop();
	}
	retchar[index] = '\0';								//����һ��'\0'
	return retchar;
}
int main()
{
	char expression[Max];
	cout << "��������ʽ:\t";
	cin.getline(expression, Max);					//�õ�Ӣ�ĵ���׺���ʽ
	cout << endl;
	char* Pre_string = Transform_Pre(expression);		//��׺���ʽת��Ϊǰ׺���ʽ���������ʽ��
	cout << "�������ʽ��\t" << Pre_string << endl << endl;
	cout << "��׺���ʽ��\t" << expression << endl << endl;
	char* Post_string = Transform_Post(expression);		//��׺���ʽת��Ϊ��׺���ʽ���沨�����ʽ��
	cout << "�沨�����ʽ��\t" << Post_string << endl << endl;
	system("pause");
	return 0;
}
*/