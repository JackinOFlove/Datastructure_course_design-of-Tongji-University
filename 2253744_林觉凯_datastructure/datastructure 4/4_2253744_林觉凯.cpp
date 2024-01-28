#include<iostream>
using namespace std;
int Totalmethods = 0,N;							//��������ȫ�ֱ���Totalmethods(�ⷨ����)��N(�ʺ���Ŀ)
//��ӡ���̺�����ͨ������N(���̳���)������queenchess(��ǰĳ�еĻʺ������ĳ��)������������̰ڷ��ͽⷨ����
void Print_Board(int N, int* queenchess)
{
	for (int row = 0; row < N; row++)
	{
		for (int column = 0; column < N; column++)
		{
			if (queenchess[row] != column)		//�����row�еĻʺ󲻰ڷ��ڵ�column�У����"0 "
				cout << "0 ";
			else
				cout << "X ";					//�����row�еĻʺ�ڷ��ڵ�column�У����"X "
		}
		cout << endl;
	}
	cout << endl;								
	return;
}
//�жϺ��������ڵݹ���㣬�жϱ�����ÿ��λ�õ����лʺ��ʺϵİڷŷ���
void Judgement(int start_row,int* queenchess, bool* column, bool* md, bool* sd)
{
	if (start_row == N)							//����ݹ������N-1�У�˵���Ѿ������һ�ַ����ļ��㣬��ӡ����
	{
		Print_Board(N, queenchess);
		Totalmethods++;							//ÿ��ӡһ�ֽⷨ���ⷨ������1
		return;
	}
	for (int i = 0; i < N; i++)					//������һ������Ӧ��ÿһ��
	{
		if (!column[i] && !md[start_row + i] && !sd[start_row - i + N])		//����ڵ�start_row�е�i�з��ûʺ������λ��û�г�ͻ
		{
			column[i] = md[start_row + i] = sd[start_row - i + N] = true;	//���ûʺ󣬲�������Ӧλ�ñ�־true
			queenchess[start_row] = i;										//��¼��start_row�еĻʺ�λ��
			Judgement(start_row + 1,queenchess, column, md, sd);			//����������һ��
		}
		else
			continue;														//����ڵ�start_row�е�i�з��ûʺ��г�ͻ��ֱ�ӻ������е���һ��
		column[i] = md[start_row + i] = sd[start_row - i + N] = false;		//�ָ����̣�����Ӱ����һ�α���
	}
}
//����������ʼ���ʺ���������������ʼ����������
int main()
{
	cout << "����NXN�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһб���ϣ�";
	cout << endl << endl;
	cout << "������ʺ�ĸ�����";
	while (1)
	{
		cin >> N;
		if (cin.good() == 0 || N < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "���벻�Ϸ������������룺";
			continue;
		}
		break;
	}											//����Ľ�׳�ԣ�ȷ�������N�Ϸ�
	cout << endl;
	int* queenchess = new int[N];				//��̬����queenchess���������ĳһ�еĻʺ�����ڵڼ���
	bool* column = new bool[N];					//��̬����column��column[i]���ڱ�ʶ��i���Ƿ�����˻ʺ�
	bool* md = new bool[2 * N];					//��̬����md��md[k]���ڱ�ʶ��k�����Խ����Ƿ�����˻ʺ�
	bool* sd = new bool[2 * N];					//��̬����sd��sd[k]���ڱ�ʶ��k�����Խ����Ƿ�����˻ʺ�
	if (queenchess == NULL || column == NULL || md == NULL || sd == NULL)
	{
		cout << "�ڴ����ʧ�ܣ�" << endl;
		system("pause");
		return 0;
	}											//���ڴ������д�����������ֿռ����ʧ�����
	for (int i = 0; i < N; i++)
		column[i] = false;						//��ʼ����̬����queenchess����ʼʱ����Ϊ�գ�δ���ûʺ�
	for (int i = 0; i < 2*N; i++)
		md[i] = sd[i] = false;					//��ʼ����̬����md��sd����ʼʱ����Ϊ�գ�δ���ûʺ�
	Judgement(0,queenchess, column, md, sd);	//�ӵ�0�п�ʼ�ݹ�������нⷨ
	cout << "����" << Totalmethods << "�ֽⷨ��" << endl;;
	delete[] queenchess;						//�ͷŶ�̬����queenchess
	delete[] column;							//�ͷŶ�̬����column
	delete[] md;								//�ͷŶ�̬����md
	delete[] sd;								//�ͷŶ�̬����sd
	system("pause");
	return 0;
}
