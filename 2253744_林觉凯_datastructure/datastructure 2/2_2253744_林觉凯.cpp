#include <iostream>
#include <cstring>
using namespace std;
typedef struct node
{
	int number;
	struct node* next;
}Node;																		//����������ṹ��node,����ÿһ�����ı��number��nextָ��ָ����һ�����
//���һ�������跶Χ�ڵ����ֵĺ���
int get_number(const int min = INT_MIN, const int max = INT_MAX, string errortip = "")
{
	int number;
	while (1)
	{
		cin >> number;
		if (cin.good() == 0 || number<min || number>max)			//1.�ж�������ǲ������� 2.�ж�����������Ƿ������Ҫ�ķ�Χ
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << errortip;										//�������Ĳ���һ�����跶Χ�ڵ����֣���������ʾerrortip
			continue;
		}
		break;
	}
	return number;													//���һ������Χ���ֵĺ������򻯺����Ĵ��뽡׳�Լ���
}																			
void Algorithm(int N, int S, int M, int K)
{
	Node* head = NULL, * current = NULL, * temp = NULL, * operation = NULL;	//��ʼ�����ĸ�ָ��,headָ��Ϊͷָ��,currentָ��Ϊ��ǰָ��,tempָ�����ڲ���ʱ����ʱ����,operationָ������ɾ�������е�Ԫ��
	head = (Node*)malloc(sizeof(Node));										//ͷ�������һƬ�ռ�
	if (head == NULL)
	{
		cout << "������ʧ�ܣ�" << endl;
		system("pause");
		return;
	}																		//����Ľ�׳��,����ڴ���������ʧ����ᱨ��
	head->number = 1;														//��1��ʼ���,��ͷָ��ı��Ϊ1
	head->next = NULL;														//Ŀǰֻ��һ��������,����head��next��ָ��NULL
	current = head;															//����ͷָ�벻�ܱ仯,����currentָ�����ͷָ��,�ҵ�����ʼλ��,���������ѭ������
	for (int i = 2; i <= N; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			cout << "������ʧ�ܣ�" << endl;								//����Ľ�׳��,����ڴ���������ʧ����ᱨ��
			system("pause");
			return;
		}
		temp->number = i;
		temp->next = NULL;
		current->next = temp;
		current = temp;
	}																		//����ѭ��������β�巨����������ʣ�µ�N-1�����
	current->next = head;													//����ѭ������,�����һ������next��ָ��ͷ���
	current = head;															//Ϊ�˺����Ĳ�������,�Ƚ�currentָ��ָ��ͷ���
	for (int i = 1; i < S; i++)
		current = current->next;											//��ָ����λ�õ�S�ſ�ʼ��Ϸ,�ò�������˽�currentָ��ָ���S��λ�õĲ���
	int remainer = N;														//���ò����Ҵ���remainer,����Ϊ����whileѭ�����ж�����
	while (remainer > K)													//�ж�����:�Ҵ���remainer��ֵ�������ʣ�µ�����K,���whileѭ������
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
			temp = current;													//��M����1ʱ�������У���ÿ��ɾ����һ�����
		if (current == head)												//���Ҫ��ɾ������ͷ��㣬�ǾͰ���һ�������Ϊͷ���
			head = current->next;
		cout << "��" << N - remainer + 1 << "�����ߵ�λ����:\t" << current->number << endl;
		if (temp != NULL)
			temp->next = current->next;
		operation = current;
		current = current->next;
		delete operation;
		remainer--;															//ɾ��ָ���Ľ��
	}
	cout << endl;
	cout << "���ʣ��:\t" << K << "��" << endl;
	cout << "ʣ�������λ��Ϊ:\t";
	current = head;
	for (int i = 0; i < K; i++)												//�����������������ߵ�λ��
	{
		cout << current->number << "    ";
		current = current->next;
	}
}
int main()
{
	int N, S, M, K;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ" << endl;//����Լɪ����������Ϸ��ʾ
	cout << endl;
	cout << "������������Ϸ��������N��";
	N = get_number(0, INT_MAX, "�������!������һ��������, ���������룺");												//ʹ��get_number�������һ�������N��ʾ��Ϸ��������
	cout << "��������Ϸ��ʼ��λ��S��\t";
	S = get_number(1, N, "�������!������һ������1��С��N��������, ���������룺");										//ʹ��get_number�������һ�������S��ʾ��Ϸ�Ŀ�ʼλ��
	cout << "��������������M��\t";
	M = get_number(1, N, "�������!������һ�������1��С��N��������, ���������룺");									//ʹ��get_number�������һ�������M��ʾ��Ϸ�ı�����ֵ
	cout << "������ʣ�����������K��\t";
	K = get_number(1, N - 1, "�������!������һ������1��С��N-1��������, ���������룺");								//ʹ��get_number�������һ�������K��ʾ��Ϸ��ʣ������
	cout << endl;
	Algorithm(N, S, M, K);	
	cout << endl;
	system("pause");																								//ʹ��Algorithm����������Ľ��					
	return 0;
}
