#include<iostream>
using namespace std;
int Totalmethods = 0,N;							//设置两个全局变量Totalmethods(解法总数)和N(皇后数目)
//打印棋盘函数，通过输入N(棋盘长宽)和数组queenchess(当前某行的皇后放置在某列)，输出所有棋盘摆法和解法总数
void Print_Board(int N, int* queenchess)
{
	for (int row = 0; row < N; row++)
	{
		for (int column = 0; column < N; column++)
		{
			if (queenchess[row] != column)		//如果第row行的皇后不摆放在第column列，输出"0 "
				cout << "0 ";
			else
				cout << "X ";					//如果第row行的皇后摆放在第column列，输出"X "
		}
		cout << endl;
	}
	cout << endl;								
	return;
}
//判断函数，用于递归计算，判断遍历行每个位置的所有皇后适合的摆放方法
void Judgement(int start_row,int* queenchess, bool* column, bool* md, bool* sd)
{
	if (start_row == N)							//如果递归完成了N-1行，说明已经完成了一种方法的计算，打印棋盘
	{
		Print_Board(N, queenchess);
		Totalmethods++;							//每打印一种解法，解法总数加1
		return;
	}
	for (int i = 0; i < N; i++)					//遍历这一行所对应的每一列
	{
		if (!column[i] && !md[start_row + i] && !sd[start_row - i + N])		//如果在第start_row行第i列放置皇后和其他位置没有冲突
		{
			column[i] = md[start_row + i] = sd[start_row - i + N] = true;	//放置皇后，并且在相应位置标志true
			queenchess[start_row] = i;										//记录第start_row行的皇后位置
			Judgement(start_row + 1,queenchess, column, md, sd);			//继续遍历下一行
		}
		else
			continue;														//如果在第start_row行第i列放置皇后有冲突，直接换到此行的下一列
		column[i] = md[start_row + i] = sd[start_row - i + N] = false;		//恢复棋盘，以免影响下一次遍历
	}
}
//主函数，初始化皇后数量，创建并初始化三个数组
int main()
{
	cout << "现有NXN的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！";
	cout << endl << endl;
	cout << "请输入皇后的个数：";
	while (1)
	{
		cin >> N;
		if (cin.good() == 0 || N < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入不合法，请重新输入：";
			continue;
		}
		break;
	}											//代码的健壮性，确保输入的N合法
	cout << endl;
	int* queenchess = new int[N];				//动态数组queenchess，用来存放某一行的皇后放置在第几列
	bool* column = new bool[N];					//动态数组column，column[i]用于标识第i列是否放置了皇后
	bool* md = new bool[2 * N];					//动态数组md，md[k]用于标识第k条主对角线是否放置了皇后
	bool* sd = new bool[2 * N];					//动态数组sd，sd[k]用于标识第k条主对角线是否放置了皇后
	if (queenchess == NULL || column == NULL || md == NULL || sd == NULL)
	{
		cout << "内存分配失败！" << endl;
		system("pause");
		return 0;
	}											//对内存分配进行错误处理，以免出现空间分配失败情况
	for (int i = 0; i < N; i++)
		column[i] = false;						//初始化动态数组queenchess，开始时棋盘为空，未放置皇后
	for (int i = 0; i < 2*N; i++)
		md[i] = sd[i] = false;					//初始化动态数组md和sd，开始时棋盘为空，未放置皇后
	Judgement(0,queenchess, column, md, sd);	//从第0行开始递归计算所有解法
	cout << "共有" << Totalmethods << "种解法！" << endl;;
	delete[] queenchess;						//释放动态数组queenchess
	delete[] column;							//释放动态数组column
	delete[] md;								//释放动态数组md
	delete[] sd;								//释放动态数组sd
	system("pause");
	return 0;
}
