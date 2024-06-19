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
};															//设置mazemap(迷宫地图)为全局变量
//ascend_dimension函数，用来将一维储存的的长度转化为二维迷宫的坐标位置
void ascend_dimension(int& number, int& row, int& column)	
{
	row = number / 7;
	column = number % 7 - 1;
}
//reduce_dimension函数，用来将二维的迷宫坐标位置转化为一维储存的的长度储存起来
int reduce_dimension(int& row, int& column)					
{
	int length = row * 7 + column + 1;
	return length;
}
//bool Search函数，用于计算递归回溯，StackArray数组用来储存储存可行路径的二维坐标转化为一维坐标的结果(递归的是从入口向出口递归的，第三返回是从出口到入口返回的，所以StackArray里下标大的储存的是靠近入口的位置坐标)
bool Search(char mazemap[7][7], int* StackArray, int Start_row, int End_row, int Start_column, int End_column, int& top)
{
	if (Start_row == End_row && Start_column == End_column)	//如果遍历至尾行尾列，遍历完成，找到出口，记录出口坐标，返回true
	{
		StackArray[top++] = reduce_dimension(Start_row, Start_column);
		return true;
	}
	if (mazemap[Start_row][Start_column] == '#')			//如果这一个位置是墙，返回false
	{
		return false;
	}
	if (mazemap[Start_row][Start_column] == '0')			//如果这一个位置是通路
	{
		mazemap[Start_row][Start_column] = '#';				//先将这个位置变为墙，以免对下面的遍历产生影响
		if (Search(mazemap, StackArray, Start_row + 1, End_row, Start_column, End_column, top))		//向下走可行
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//记录此点坐标信息
			return true;
		}
		else if (Search(mazemap, StackArray, Start_row - 1, End_row, Start_column, End_column, top))		//向上走可行
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//记录此点坐标信息
			return true;
		}
		else if (Search(mazemap, StackArray, Start_row, End_row, Start_column + 1, End_column, top))		//向右走可行
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//记录此点坐标信息
			return true;
		}
		else if (Search(mazemap, StackArray, Start_row, End_row, Start_column - 1, End_column, top))		//向左走可行
		{
			StackArray[top++] = reduce_dimension(Start_row, Start_column);									//记录此点坐标信息
			return true;
		}
		mazemap[Start_row][Start_column] = '0';			//恢复当前位置现场为'0'
	}
	return false;										//如果以上四种情况都不能达成，则此点不在路径上，不记录此点坐标信息，返回false
}
//主函数，由于初始化数据和最后打印迷宫路径和迷宫地图
int main()
{
	int StackArray[50] = { 0 };							//运用"栈"的思维，StackArray用来储存可行路径的二维坐标转化为一维坐标的结果
	int top = 0;
	Search(mazemap,StackArray, 1, 5, 1, 5, top);		//递归从第一行第一列开始至第五行第五列
	int row = 0, column = 0;
	ascend_dimension(StackArray[--top], row, column);	//类似"出栈"的思想打印迷宫路径
	mazemap[row][column] = 'x';
	cout << "迷宫路径：" << endl << endl;
	cout << "<" << row << "," << column << "> ";
	while (top != 0)
	{
		ascend_dimension(StackArray[--top], row, column);
		mazemap[row][column] = 'x';
		cout << "---> <" << row << "," << column << "> ";
	}
	cout << endl << endl;
	cout << "迷宫地图：" << endl << endl;				//遍历mazemap数组，打印迷宫地图
	for (int i = 0; i < 7; i++)
		cout << "\t" << i << "列";
	cout << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << i << "行";
		for (int j = 0; j < 7; j++)
			cout << "\t" << mazemap[i][j];
		cout << endl << endl;
	}
	system("pause");
	return 0;
}
