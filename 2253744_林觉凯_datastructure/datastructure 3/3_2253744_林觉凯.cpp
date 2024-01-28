#include<iostream>
using namespace std;
char mazemap[7][7] =
{
 '#', '#', '#', '#', '#', '#', '#',
 '#', '0', '#', '0', '0', '0', '#',
 '#', '0', '#', '0', '#', '#', '#',
 '#', '0', '0', '0', '#', '0', '#',
 '#', '0', '#', '0', '0', '0', '#',
 '#', '0', '#', '0', '#', '0', '#',
 '#', '#', '#', '#', '#', '#', '#',
};															//����mazemap(�Թ���ͼ)Ϊȫ�ֱ���
//ascend_dimension������������һά����ĵĳ���ת��Ϊ��ά�Թ�������λ��
void ascend_dimension(int& number, int& row, int& column)	
{
	row = number / 7;
	column = number % 7 - 1;
}
//reduce_dimension��������������ά���Թ�����λ��ת��Ϊһά����ĵĳ��ȴ�������
int reduce_dimension(int& row, int& column)					
{
	int length = row * 7 + column + 1;
	return length;
}
//bool Search���������ڼ���ݹ���ݣ�StackArray�����������洢�����·���Ķ�ά����ת��Ϊһά����Ľ��(�ݹ���Ǵ��������ڵݹ�ģ����������Ǵӳ��ڵ���ڷ��صģ�����StackArray���±��Ĵ�����ǿ�����ڵ�λ������)
bool Search(char mazemap[7][7], int* StackArray, int Start_row, int End_row, int Start_column, int End_column, int& top)
{
	if (Start_row == End_row && Start_column == End_column)	//���������β��β�У�������ɣ��ҵ����ڣ���¼�������꣬����true
	{
		StackArray[top++] = reduce_dimension(Start_row, Start_column);
		return true;
	}
	if (mazemap[Start_row][Start_column] == '#')			//�����һ��λ����ǽ������false
	{
		return false;
	}
	if (mazemap[Start_row][Start_column] == '0')			//�����һ��λ����ͨ·
	{
		mazemap[Start_row][Start_column] = '#';				//�Ƚ����λ�ñ�Ϊǽ�����������ı�������Ӱ��
		if (Search(mazemap, StackArray, Start_row + 1, End_row, Start_column, End_column, top))		//�����߿���
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//��¼�˵�������Ϣ
			return true;
		}
		else if (Search(mazemap, StackArray, Start_row - 1, End_row, Start_column, End_column, top))		//�����߿���
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//��¼�˵�������Ϣ
			return true;
		}
		else if (Search(mazemap, StackArray, Start_row, End_row, Start_column + 1, End_column, top))		//�����߿���
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//��¼�˵�������Ϣ
			return true;
		}
		else if (Search(mazemap, StackArray, Start_row, End_row, Start_column - 1, End_column, top))		//�����߿���
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//��¼�˵�������Ϣ
			return true;
		}
		mazemap[Start_row][Start_column] = '0';			//�ָ���ǰλ���ֳ�Ϊ'0'
	}
	return false;										//�������������������ܴ�ɣ���˵㲻��·���ϣ�����¼�˵�������Ϣ������false
}
//�����������ڳ�ʼ�����ݺ�����ӡ�Թ�·�����Թ���ͼ
int main()
{
	int StackArray[50] = { 0 };							//����"ջ"��˼ά��StackArray�����������·���Ķ�ά����ת��Ϊһά����Ľ��
	int top = 0;
	Search(mazemap,StackArray, 1, 5, 1, 5, top);		//�ݹ�ӵ�һ�е�һ�п�ʼ�������е�����
	int row = 0, column = 0;
	ascend_dimension(StackArray[--top], row, column);	//����"��ջ"��˼���ӡ�Թ�·��
	mazemap[row][column] = 'x';
	cout << "�Թ�·����" << endl << endl;
	cout << "<" << row << "," << column << "> ";
	while (top != 0)
	{
		ascend_dimension(StackArray[--top], row, column);
		mazemap[row][column] = 'x';
		cout << "---> <" << row << "," << column << "> ";
	}
	cout << endl << endl;
	cout << "�Թ���ͼ��" << endl << endl;				//����mazemap���飬��ӡ�Թ���ͼ
	for (int i = 0; i < 7; i++)
		cout << "\t" << i << "��";
	cout << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << i << "��";
		for (int j = 0; j < 7; j++)
			cout << "\t" << mazemap[i][j];
		cout << endl << endl;
	}
	system("pause");
	return 0;
}
