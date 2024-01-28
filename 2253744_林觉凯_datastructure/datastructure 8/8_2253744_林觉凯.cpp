#include <iostream>
#define MAXWEIGHT INT_MAX
using namespace std;
//获得一个在规定范围的字符函数，并进行错误处理
char Get_Char(string errortips)
{
	char retchar;
	cout << endl << "请选择操作：";
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
//打印菜单函数
void Print_Menu()
{
	cout << "**             电网造价模拟系统              **" << endl;
	cout << "**                                           **" << endl;
	cout << "===============================================" << endl;
	cout << "**             A --- 创建电网顶点            **" << endl;
	cout << "**             B --- 添加电网的边            **" << endl;
	cout << "**             C --- 构造最小生成树          **" << endl;
	cout << "**             D --- 显示最小生成树          **" << endl;
	cout << "**             E --- 退出   程序             **" << endl;
	cout << "===============================================" << endl;
}
//边结点类，每一个边结点都记录着该边的起始顶点、终止顶点和边的权重
class Edgenode
{
public:
	char start;				//边的起始顶点
	char end;				//边的终止顶点
	int weight;				//边的权重
	Edgenode() { start = end = ' '; weight = 0; }
};
//图类
class Graph
{
public:
	int Vertices_num = 0;					//图的顶点数
	int Edges_num = 0;						//图的边数
	char* Vertices_list = NULL;				//顶点数组指针
	int** Edge_matrix = NULL;				//邻接矩阵指针
	Edgenode* Minispantree = NULL;			//最小生成树指针
	int Transform_index(char Nodename);		
	void Add_node();
	void Add_edge();
	void Create_tree();
	void Print_tree();
};
//将边名称转化为其所在边链表的下标值
int Graph::Transform_index(char Nodename)
{
	for (int i = 0; i < Vertices_num; i++)
	{
		if (Vertices_list[i] == Nodename)
			return i;
	}
	return -1;
}
//添加结点函数
void Graph::Add_node()
{
	cout << "请输入顶点的个数：";
	int Node_num;
	//输入的错误处理（非法字符和顶点个数限制）
	while (1)
	{
		cin >> Node_num;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误！请重新输入！" << endl;							//非法字符
			continue;
		}
		if (Node_num < 2)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "顶点数应该是大于等于2的正整数，请重新输入！" << endl;		//顶点个数大于等于2
			continue;
		}
		break;
	}
	Vertices_num = Node_num;						//顶点个数
	Vertices_list = new char[Vertices_num];			//顶点数组
	cout << "请输入各顶点的名称：" << endl;
	for (int i = 0; i < Vertices_num; i++)			//创建顶点数组
		cin >> Vertices_list[i];
}
//添加边函数
void Graph::Add_edge()
{
	//前提判断（是否已经添加顶点）
	if (Vertices_num == 0)							
	{
		cout << "无顶点！请先添加顶点！" << endl;
		return;
	}
	//为邻接矩阵分配空间
	Edge_matrix = new int* [Vertices_num];
	for (int i = 0; i < Vertices_num; i++)
		Edge_matrix[i] = new int[Vertices_num];
	for (int i = 0; i < Vertices_num; i++)			//初始化邻接矩阵
	{
		for (int j = 0; j < Vertices_num; j++)
		{
			if (i == j)								
				Edge_matrix[i][j] = 0;				//自己到自己的边权重为0
			else
				Edge_matrix[i][j] = MAXWEIGHT;		//其它的边初始化为MAXWEIGHT
		}
	}
	char start, end;
	int index_1, index_2;
	int weight;
	while (1)
	{
		cout << "请输入两个顶点及边（输入“? ? 0”表示停止输入）：";	
		cin >> start >> end >> weight;
		if (start == '?' || end == '?' || weight == 0)		//依据题目要求设定输入中止条件
			break;
		index_1 = Transform_index(start);					//将start顶点转化为其在结点数组的下标
		index_2 = Transform_index(end);						//将end顶点转化为其在结点数组的下标
		if (index_1 == -1 || index_2 == -1)					//判断边是否存在
		{
			cout << "你输入的边不存在！" << endl;
			continue;
		}
		else if (Edge_matrix[index_1][index_2] == 0)		//判断输入的两顶点是否重复
		{
			cout << "你输入的两个顶点相同！请重新输入！" << endl;
			continue;
		}
		else if (Edge_matrix[index_1][index_2] > 0 && Edge_matrix[index_1][index_2] != MAXWEIGHT)		//判断是否重复输入两顶点和其边权重
		{
			cout << "你重复输入两顶点的边关系！输入无效！请重新输入！" << endl;
			continue;
		}
		else if (index_1 > -1 && index_1 < Vertices_num && index_2 > -1 && index_2 < Vertices_num && Edge_matrix[index_1][index_2] == MAXWEIGHT)
		{
			Edge_matrix[index_1][index_2] = Edge_matrix[index_2][index_1] = weight;			//输入起始顶点、终止顶点和对应权重并赋值完成
			Edges_num++;				//边数加一
		}
	}
}
//创建最小生成树函数
void Graph::Create_tree()
{
	//前提判断（是否已经输入顶点）
	if (Vertices_num == 0)
	{
		cout << "没有顶点！无法创建最小生成树！请首先创建顶点和边的关系！" << endl;
		return;
	}
	//前提判断（是否已经创建顶点之间边的关系）
	if (Edge_matrix == NULL)
	{
		cout << "没有顶点之间的边关系！无法创建最小生成树！请先创建顶点之间边的关系！" << endl;
		return;
	}
	//lowcost数组，存放生成数顶点集合内各顶点到生成树外各顶点的个边上的最小权值
	int* lowcost = new int[Vertices_num];
	//nearvex数组，记录生成树顶点集合外各顶点距离集合内哪个顶点最近（权重最小）
	int* nearvex = new int[Vertices_num];
	char Start_vertice;
	cout << "请输入最小生成树的起始顶点：";
	cin >> Start_vertice;
	while (Transform_index(Start_vertice) == -1)
	{
		cout << "你输入的最小生成树的起始顶点不存在！请重新输入！";
		cin >> Start_vertice;
	}
	int Start_index = Transform_index(Start_vertice);		//输入起始顶点并转化为该顶点在顶点数组内的下标
	lowcost[Start_index] = 0;
	nearvex[Start_index] = -1;								
	for (int i = 0; i < Vertices_num; i++)
	{
		if (i != Start_index)
		{
			lowcost[i] = Edge_matrix[Start_index][i];
			nearvex[i] = Start_index;
		}
	}														//初始化两个数组
	Minispantree = new Edgenode[Vertices_num - 1];			//最小生成树内应该有顶点数减一个边结点
	int count = 0;
	for (int i = 1; i < Vertices_num; i++)
	{
		int min = MAXWEIGHT;
		int v = Start_index;
		//求生成树外顶点到生成树内顶点具有最小权值的边，v是当前具有最小权值的边的位置
		for (int j = 0; j < Vertices_num; j++)
		{
			if (nearvex[j] != -1 && lowcost[j] < min)
			{
				v = j;
				min = lowcost[j];
			}
		}		
		if (v != Start_index)								//v==Start_index表示再也找不到要求的顶点了
		{
			Edgenode e;										//最小生成树结点的辅助单元
			e.start = Vertices_list[nearvex[v]];
			e.end = Vertices_list[v];
			e.weight = lowcost[v];
			Minispantree[count++] = e;						//选出的边结点计入生成树
			nearvex[v] = -1;								//作该边已加入生成树的标记
			for (int j = 1; j < Vertices_num; j++)			//j不在生成树中
			{
				if (nearvex[j] != -1 && Edge_matrix[v][j] < lowcost[j])		//需要修改
				{
					lowcost[j] = Edge_matrix[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	cout << "生成Prim最小生成树！" << endl;
}
//打印最小生成树函数
void Graph::Print_tree()
{
	//前提判断（是否已经输入顶点）
	if (Vertices_num == 0)
	{
		cout << "没有顶点！无法显示最小生成树！请首先创建顶点和边的关系！" << endl;
		return;
	}
	//前提判断（是否已经创建顶点之间边的关系）
	if (Edge_matrix == NULL)
	{
		cout << "没有顶点之间的边关系！无法打印最小生成树！请先创建顶点之间边的关系！" << endl;
		return;
	}
	//前提判断（是否已经生成最小生成树）
	if(Minispantree == NULL)
	{
		cout << "未创建最小生成树，无内容可显示！请创建最小生成树：" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为：" << endl << endl;
	for (int i = 0; i < Vertices_num - 1; i++)			//遍历最小生成树内边结点并输出
		cout << Minispantree[i].start << "--<" << Minispantree[i].weight << ">-->" << Minispantree[i].end << "     ";
	cout << endl;
}
//主函数的实现
int main()
{
	Print_Menu();
	Graph electric_graph;				//实例化Graph electric_graph
	char keydown;
	while (1)
	{
		keydown = Get_Char("输入错误，请重新输入！");
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
			cout << endl << "请退出程序！" << endl;
			system("pause");
			return 0;
		}
	}
	cout << endl << "请退出程序！" << endl;
	system("pause");
	return 0;
}