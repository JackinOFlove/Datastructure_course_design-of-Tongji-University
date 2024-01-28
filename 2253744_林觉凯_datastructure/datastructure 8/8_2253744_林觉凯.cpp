#include <iostream>
#define MAXWEIGHT INT_MAX
using namespace std;
//���һ���ڹ涨��Χ���ַ������������д�����
char Get_Char(string errortips)
{
	char retchar;
	cout << endl << "��ѡ�������";
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
//��ӡ�˵�����
void Print_Menu()
{
	cout << "**             �������ģ��ϵͳ              **" << endl;
	cout << "**                                           **" << endl;
	cout << "===============================================" << endl;
	cout << "**             A --- ������������            **" << endl;
	cout << "**             B --- ��ӵ����ı�            **" << endl;
	cout << "**             C --- ������С������          **" << endl;
	cout << "**             D --- ��ʾ��С������          **" << endl;
	cout << "**             E --- �˳�   ����             **" << endl;
	cout << "===============================================" << endl;
}
//�߽���࣬ÿһ���߽�㶼��¼�Ÿñߵ���ʼ���㡢��ֹ����ͱߵ�Ȩ��
class Edgenode
{
public:
	char start;				//�ߵ���ʼ����
	char end;				//�ߵ���ֹ����
	int weight;				//�ߵ�Ȩ��
	Edgenode() { start = end = ' '; weight = 0; }
};
//ͼ��
class Graph
{
public:
	int Vertices_num = 0;					//ͼ�Ķ�����
	int Edges_num = 0;						//ͼ�ı���
	char* Vertices_list = NULL;				//��������ָ��
	int** Edge_matrix = NULL;				//�ڽӾ���ָ��
	Edgenode* Minispantree = NULL;			//��С������ָ��
	int Transform_index(char Nodename);		
	void Add_node();
	void Add_edge();
	void Create_tree();
	void Print_tree();
};
//��������ת��Ϊ�����ڱ�������±�ֵ
int Graph::Transform_index(char Nodename)
{
	for (int i = 0; i < Vertices_num; i++)
	{
		if (Vertices_list[i] == Nodename)
			return i;
	}
	return -1;
}
//��ӽ�㺯��
void Graph::Add_node()
{
	cout << "�����붥��ĸ�����";
	int Node_num;
	//����Ĵ������Ƿ��ַ��Ͷ���������ƣ�
	while (1)
	{
		cin >> Node_num;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룡" << endl;							//�Ƿ��ַ�
			continue;
		}
		if (Node_num < 2)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "������Ӧ���Ǵ��ڵ���2�������������������룡" << endl;		//����������ڵ���2
			continue;
		}
		break;
	}
	Vertices_num = Node_num;						//�������
	Vertices_list = new char[Vertices_num];			//��������
	cout << "���������������ƣ�" << endl;
	for (int i = 0; i < Vertices_num; i++)			//������������
		cin >> Vertices_list[i];
}
//��ӱߺ���
void Graph::Add_edge()
{
	//ǰ���жϣ��Ƿ��Ѿ���Ӷ��㣩
	if (Vertices_num == 0)							
	{
		cout << "�޶��㣡������Ӷ��㣡" << endl;
		return;
	}
	//Ϊ�ڽӾ������ռ�
	Edge_matrix = new int* [Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
		Edge_matrix[i] = new int[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)			//��ʼ���ڽӾ���
	{
		for (int j = 0; j < Vertices_num; j++)
		{
			if (i == j)								
				Edge_matrix[i][j] = 0;				//�Լ����Լ��ı�Ȩ��Ϊ0
			else
				Edge_matrix[i][j] = MAXWEIGHT;		//�����ı߳�ʼ��ΪMAXWEIGHT
		}
	}
	char start, end;
	int index_1, index_2;
	int weight;
	while (1)
	{
		cout << "�������������㼰�ߣ����롰? ? 0����ʾֹͣ���룩��";	
		cin >> start >> end >> weight;
		if (start == '?' || end == '?' || weight == 0)		//������ĿҪ���趨������ֹ����
			break;
		index_1 = Transform_index(start);					//��start����ת��Ϊ���ڽ��������±�
		index_2 = Transform_index(end);						//��end����ת��Ϊ���ڽ��������±�
		if (index_1 == -1 || index_2 == -1)					//�жϱ��Ƿ����
		{
			cout << "������ı߲����ڣ�" << endl;
			continue;
		}
		else if (Edge_matrix[index_1][index_2] == 0)		//�ж�������������Ƿ��ظ�
		{
			cout << "�����������������ͬ�����������룡" << endl;
			continue;
		}
		else if (Edge_matrix[index_1][index_2] > 0 && Edge_matrix[index_1][index_2] != MAXWEIGHT)		//�ж��Ƿ��ظ���������������Ȩ��
		{
			cout << "���ظ�����������ı߹�ϵ��������Ч�����������룡" << endl;
			continue;
		}
		else if (index_1 > -1 && index_1 < Vertices_num && index_2 > -1 && index_2 < Vertices_num && Edge_matrix[index_1][index_2] == MAXWEIGHT)
		{
			Edge_matrix[index_1][index_2] = Edge_matrix[index_2][index_1] = weight;			//������ʼ���㡢��ֹ����Ͷ�ӦȨ�ز���ֵ���
			Edges_num++;				//������һ
		}
	}
}
//������С����������
void Graph::Create_tree()
{
	//ǰ���жϣ��Ƿ��Ѿ����붥�㣩
	if (Vertices_num == 0)
	{
		cout << "û�ж��㣡�޷�������С�������������ȴ�������ͱߵĹ�ϵ��" << endl;
		return;
	}
	//ǰ���жϣ��Ƿ��Ѿ���������֮��ߵĹ�ϵ��
	if (Edge_matrix == NULL)
	{
		cout << "û�ж���֮��ı߹�ϵ���޷�������С�����������ȴ�������֮��ߵĹ�ϵ��" << endl;
		return;
	}
	//lowcost���飬������������㼯���ڸ����㵽�������������ĸ����ϵ���СȨֵ
	int* lowcost = new int[Vertices_num];
	//nearvex���飬��¼���������㼯�����������뼯�����ĸ����������Ȩ����С��
	int* nearvex = new int[Vertices_num];
	char Start_vertice;
	cout << "��������С����������ʼ���㣺";
	cin >> Start_vertice;
	while (Transform_index(Start_vertice) == -1)
	{
		cout << "���������С����������ʼ���㲻���ڣ����������룡";
		cin >> Start_vertice;
	}
	int Start_index = Transform_index(Start_vertice);		//������ʼ���㲢ת��Ϊ�ö����ڶ��������ڵ��±�
	lowcost[Start_index] = 0;
	nearvex[Start_index] = -1;								
	for (int i = 0; i < Vertices_num; i++)
	{
		if (i != Start_index)
		{
			lowcost[i] = Edge_matrix[Start_index][i];
			nearvex[i] = Start_index;
		}
	}														//��ʼ����������
	Minispantree = new Edgenode[Vertices_num - 1];			//��С��������Ӧ���ж�������һ���߽��
	int count = 0;
	for (int i = 1; i < Vertices_num; i++)
	{
		int min = MAXWEIGHT;
		int v = Start_index;
		//���������ⶥ�㵽�������ڶ��������СȨֵ�ıߣ�v�ǵ�ǰ������СȨֵ�ıߵ�λ��
		for (int j = 0; j < Vertices_num; j++)
		{
			if (nearvex[j] != -1 && lowcost[j] < min)
			{
				v = j;
				min = lowcost[j];
			}
		}		
		if (v != Start_index)								//v==Start_index��ʾ��Ҳ�Ҳ���Ҫ��Ķ�����
		{
			Edgenode e;										//��С���������ĸ�����Ԫ
			e.start = Vertices_list[nearvex[v]];
			e.end = Vertices_list[v];
			e.weight = lowcost[v];
			Minispantree[count++] = e;						//ѡ���ı߽�����������
			nearvex[v] = -1;								//���ñ��Ѽ����������ı��
			for (int j = 1; j < Vertices_num; j++)			//j������������
			{
				if (nearvex[j] != -1 && Edge_matrix[v][j] < lowcost[j])		//��Ҫ�޸�
				{
					lowcost[j] = Edge_matrix[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	cout << "����Prim��С��������" << endl;
}
//��ӡ��С����������
void Graph::Print_tree()
{
	//ǰ���жϣ��Ƿ��Ѿ����붥�㣩
	if (Vertices_num == 0)
	{
		cout << "û�ж��㣡�޷���ʾ��С�������������ȴ�������ͱߵĹ�ϵ��" << endl;
		return;
	}
	//ǰ���жϣ��Ƿ��Ѿ���������֮��ߵĹ�ϵ��
	if (Edge_matrix == NULL)
	{
		cout << "û�ж���֮��ı߹�ϵ���޷���ӡ��С�����������ȴ�������֮��ߵĹ�ϵ��" << endl;
		return;
	}
	//ǰ���жϣ��Ƿ��Ѿ�������С��������
	if(Minispantree == NULL)
	{
		cout << "δ������С�������������ݿ���ʾ���봴����С��������" << endl;
		return;
	}
	cout << "��С�������Ķ��㼰��Ϊ��" << endl << endl;
	for (int i = 0; i < Vertices_num - 1; i++)			//������С�������ڱ߽�㲢���
		cout << Minispantree[i].start << "--<" << Minispantree[i].weight << ">-->" << Minispantree[i].end << "     ";
	cout << endl;
}
//��������ʵ��
int main()
{
	Print_Menu();
	Graph electric_graph;				//ʵ����Graph electric_graph
	char keydown;
	while (1)
	{
		keydown = Get_Char("����������������룡");
		switch (keydown)
		{
		case 'A':
			electric_graph.Add_node();
			break;
		case 'B':
			electric_graph.Add_edge();
			break;
		case 'C':
			electric_graph.Create_tree();
			break;
		case 'D':
			electric_graph.Print_tree();
			break;
		case 'E':
			cout << endl << "���˳�����" << endl;
			system("pause");
			return 0;
		}
	}
	cout << endl << "���˳�����" << endl;
	system("pause");
	return 0;
}