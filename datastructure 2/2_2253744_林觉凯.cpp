#include <iostream>
#include <cstring>
using namespace std;
typedef struct node
{
	int number;
	struct node* next;
}Node;																		//定义链表结点结构体node,包含每一个结点的编号number和next指针指向下一个结点
//获得一个在所需范围内的数字的函数
int get_number(const int min = INT_MIN, const int max = INT_MAX, string errortip = "")
{
	int number;
	while (1)
	{
		cin >> number;
		if (cin.good() == 0 || number<min || number>max)			//1.判断输入的是不是数字 2.判断输入的数字是否符合想要的范围
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << errortip;										//如果输入的不是一个所需范围内的数字，则会输出提示errortip
			continue;
		}
		break;
	}
	return number;													//获得一个合理范围数字的函数，简化后续的代码健壮性检验
}																			
void Algorithm(int N, int S, int M, int K)
{
	Node* head = NULL, * current = NULL, * temp = NULL, * operation = NULL;	//开始定义四个指针,head指针为头指针,current指针为当前指针,temp指针用于操作时的临时运用,operation指针用于删除链表中的元素
	head = (Node*)malloc(sizeof(Node));										//头结点申请一片空间
	if (head == NULL)
	{
		cout << "链表创建失败！" << endl;
		system("pause");
		return;
	}																		//代码的健壮性,如果内存的申请分配失败则会报告
	head->number = 1;														//从1开始编号,故头指针的编号为1
	head->next = NULL;														//目前只有一个链表结点,所以head的next域指向NULL
	current = head;															//由于头指针不能变化,先让current指针等于头指针,找到链表开始位置,方便后续的循环操作
	for (int i = 2; i <= N; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			cout << "链表创建失败！" << endl;								//代码的健壮性,如果内存的申请分配失败则会报告
			system("pause");
			return;
		}
		temp->number = i;
		temp->next = NULL;
		current->next = temp;
		current = temp;
	}																		//运用循环操作的尾插法来创建链表剩下的N-1个结点
	current->next = head;													//创建循环链表,让最后一个结点的next域指向头结点
	current = head;															//为了后续的操作方便,先将current指针指向头结点
	for (int i = 1; i < S; i++)
		current = current->next;											//从指定的位置第S号开始游戏,该操作完成了将current指针指向第S号位置的操作
	int remainer = N;														//设置参数幸存者remainer,以作为下列while循环的判断条件
	while (remainer > K)													//判断条件:幸存者remainer的值大于最后剩下的人数K,则该while循环进行
	{
		if(M > 1)															
		{ 
			for (int i = 1; i < M; i++)
			{
				temp = current;
				current = current->next;
			}
		}
		else
			temp = current;													//对M等于1时进行特判，即每次删除下一个结点
		if (current == head)												//如果要被删除的是头结点，那就把下一个结点设为头结点
			head = current->next;
		cout << "第" << N - remainer + 1 << "个死者的位置是:\t" << current->number << endl;
		if (temp != NULL)
			temp->next = current->next;
		operation = current;
		current = current->next;
		delete operation;
		remainer--;															//删除指定的结点
	}
	cout << endl;
	cout << "最后剩下:\t" << K << "人" << endl;
	cout << "剩余的生者位置为:\t";
	current = head;
	for (int i = 0; i < K; i++)												//遍历链表，输出最后生者的位置
	{
		cout << current->number << "    ";
		current = current->next;
	}
}
int main()
{
	int N, S, M, K;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止" << endl;//给出约瑟夫生死环游戏提示
	cout << endl;
	cout << "请输入生死游戏的总人数N：";
	N = get_number(0, INT_MAX, "输入错误!请输入一个正整数, 请重新输入：");												//使用get_number函数获得一个合理的N表示游戏的总人数
	cout << "请输入游戏开始的位置S：\t";
	S = get_number(1, N, "输入错误!请输入一个大于1并小于N的正整数, 请重新输入：");										//使用get_number函数获得一个合理的S表示游戏的开始位置
	cout << "请输入死亡数字M：\t";
	M = get_number(1, N, "输入错误!请输入一个大等于1并小于N的正整数, 请重新输入：");									//使用get_number函数获得一个合理的M表示游戏的报数数值
	cout << "请输入剩余的生者人数K：\t";
	K = get_number(1, N - 1, "输入错误!请输入一个大于1并小于N-1的正整数, 请重新输入：");								//使用get_number函数获得一个合理的K表示游戏的剩余人数
	cout << endl;
	Algorithm(N, S, M, K);	
	cout << endl;
	system("pause");																								//使用Algorithm函数获得最后的结果					
	return 0;
}
