#include<iostream>
using namespace std;
int Bubble_count = 0;
int Select_count = 0;
int Insert_count = 0;
int Shell_count = 0;
int Quick_count = 0;
int Heap_count = 0;
int Merge_count = 0;
int Radix_count = 0;
//生成待排序的数组
int* Establish_array(int number)
{
	int* array = new int[number];
	srand((unsigned int)(time(0)));
	for (int i = 0; i < number; i++)
		array[i] = rand() % 65536;
	return array;
}
//交换函数
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
//冒泡排序
void Bubble_sort(int* array,int number)
{
	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < number - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				swap(array[j], array[j + 1]);
				Bubble_count++;
			}	
		}
	}
}
//选择排序
void Select_sort(int* array, int number)
{
	for (int i = 0; i < number - 1; i++)
	{
		int Min_index = i;
		for (int j = i; j < number; j++)
		{
			if (array[Min_index] > array[j])
				Min_index = j;
			Select_count++;
		}
		if (Min_index != i)
			swap(array[i], array[Min_index]);
	}
}
//直接插入排序
void Insert_sort(int* array, int number)
{
	for (int i = 1; i < number; i++)
	{
		int temp = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > temp)
		{
			array[j + 1] = array[j];
			Insert_count++;
			j--;
		}
		array[j + 1] = temp;
	}
}
//希尔排序
void Shell_sort(int* array, int number)
{
	int gap = number / 2;
	while (gap)
	{
		for (int i = gap; i < number; i++)
		{
			int temp = array[i];
			int j = i - gap;
			while (j >= 0 && array[j] > temp)
			{
				array[j + gap] = array[j];
				Shell_count++;
				j -= gap;
			}
			array[j + gap] = temp;
		}
		gap /= 2;
	}
}
//快速排序
void Quick_sort(int* array, int left, int right)
{
	if (left < right)
	{
		int i = left, j = right, x = array[left];
		while (i < j)
		{
			while (i < j && array[j] >= x)
				j--;
			if (i < j)
			{
				array[i++] = array[j];
				Quick_count++;
			}
			while (i < j && array[i] < x)
				i++;
			if (i < j)
			{
				array[j--] = array[i];
				Quick_count++;
			}
		}
		array[i] = x;
		Quick_count++;
		Quick_sort(array, left, i - 1);
		Quick_sort(array, i + 1, right);
	}
}
//堆排序
void Adjust(int* array, int length, int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int max_idx = index;
	if (left < length && array[left] > array[max_idx])
		max_idx = left;
	if (right < length && array[right] > array[max_idx])
		max_idx = right;
	if (max_idx != index)
	{
		swap(array[max_idx], array[index]);
		Adjust(array, length, max_idx);
	}
}
void Heap_sort(int* array, int number)
{
	for (int i = number / 2 - 1; i >= 0; i--)
		Adjust(array, number, i);
	for (int i = number - 1; i >= 1; i--)
	{
		swap(array[0], array[i]);
		Heap_count++;
		Adjust(array, i, 0);
	}
}
//归并排序
void Merge(int* array, int start, int mid, int end)
{
	int length = end - start + 1;
	int* temp_array = new int[length];
	for (int index = 0; index < length; index++)
		temp_array[index] = array[start + index];
	int i = 0;
	int j = mid - start + 1;
	for (int k = start; k <= end; k++)
	{
		if (i == mid - start + 1)
		{
			array[k] = temp_array[j++];
			Merge_count++;
			continue;
		}
		if (j == end - start + 1)
		{
			array[k] = temp_array[i++];
			Merge_count++;
			continue;
		}
		if (temp_array[i] > temp_array[j] && temp_array[1])
		{
			array[k] = temp_array[j++];
			Merge_count++;
		}
		else
		{
			array[k] = temp_array[i++];
			Merge_count++;
		}
	}
	delete[] temp_array;
}
void Merge_sort(int* array, int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	Merge_sort(array, start, mid);
	Merge_sort(array, mid + 1, end);
	Merge(array, start, mid, end);
}
//基数排序
int Get_maxbit(int* array, int number)
{
	int Max_num = array[0];
	for (int i = 0; i < number; i++)
	{
		if (array[i] > Max_num)
			Max_num = array[i];
	}
	int bit = 0;
	while (Max_num > 0)
	{
		Max_num /= 10;
		bit++;
	}
	return bit;
}
int Get_index_number(int number, int index)
{
	int i = 1;
	while (index > 1)
	{
		i *= 10;
		index--;
	}
	return number / i % 10;
}
void Radix_sort(int* array, int number)
{
	int maxbit = Get_maxbit(array, number);
	int* temp_array = new int[number];
	int count[10] = { 0 };
	for (int d = 1; d <= maxbit; d++)
	{
		// 计数器清0
		for (int i = 0; i < 10; i++) 
			count[i] = 0;
		// 统计各个桶中的个数
		for (int i = 0; i < number; i++) 
			count[Get_index_number(array[i], d)]++;
		for (int i = 1; i < 10; i++)      //得到每个数应该放入temp_array中的位置
			count[i] += count[i - 1];
		for (int i = number - 1; i >= 0; i--) 
		{  //采用倒序进行排序是为了不打乱已经排好的顺序
			int k = Get_index_number(array[i], d);
			temp_array[count[k] - 1] = array[i];
			count[k]--;
		}
		for (int j = 0; j < number; j++)    // 临时数组复制到原先array数组中
			array[j] = temp_array[j];
	}
	delete[] temp_array;
}
//主函数
int main()
{
	cout << "**            排序算法比较              **" << endl;
	cout << "==========================================" << endl;
	cout << "**          1---冒泡排序                **" << endl;
	cout << "**          2---选择排序                **" << endl;
	cout << "**          3---直接插入排序            **" << endl;
	cout << "**          4---希尔排序                **" << endl;
	cout << "**          5---快速排序                **" << endl;
	cout << "**          6---堆排序                  **" << endl;
	cout << "**          7---归并排序                **" << endl;
	cout << "**          8---基数排序                **" << endl;
	cout << "**          9---退出程序                **" << endl;
	cout << "==========================================" << endl;
	cout << endl;
	int number;
	while (1)
	{
		cout << "请输入要产生的随机数的个数：";
		cin >> number;
		if (cin.good() == 0 || number < 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "非法输入！请重新输入！" << endl;
			continue;
		}
		break;
	}
	int* Standard_Array = Establish_array(number);
	clock_t Start_time, End_time;
	int tag = 1;
	int keydown;
	while (tag)
	{
		int* array = new int[number];
		for (int i = 0; i < number; i++)
			array[i] = Standard_Array[i];
		cout << endl;
		while (1)
		{
			cout << "请选择排序算法:\t\t\t";
			cin >> keydown;
			if (cin.good() == 0 || keydown < 1 || keydown > 9)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "非法输入！请重新输入！" << endl;
				continue;
			}
			break;
		}
		switch (keydown)
		{
		case 1:
			Start_time = clock();
			Bubble_sort(array, number);
			End_time = clock();
			cout << "冒泡排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "冒泡排序的交换次数：\t\t" << Bubble_count << endl;
			break;
		case 2:
			Start_time = clock();
			Select_sort(array, number);
			End_time = clock();
			cout << "选择排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "选择排序的交换次数：\t\t" << Select_count << endl;
			break;
		case 3:
			Start_time = clock();
			Insert_sort(array, number);
			End_time = clock();
			cout << "直接插入排序所用的时间：        " << End_time - Start_time << endl;
			cout << "直接插入排序的交换次数：        " << Insert_count << endl;
			break;
		case 4:
			Start_time = clock();
			Shell_sort(array, number);
			End_time = clock();
			cout << "希尔排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "希尔排序的交换次数：\t\t" << Shell_count << endl;
			break;
		case 5:
			Start_time = clock();
			Quick_sort(array, 0, number - 1);
			End_time = clock();
			cout << "快速排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "快速排序的交换次数：\t\t" << Quick_count << endl;
			break;
		case 6:
			Start_time = clock();
			Heap_sort(array, number);
			End_time = clock();
			cout << "堆排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "堆排序的交换次数：\t\t" << Heap_count << endl;
			break;
		case 7:
			Start_time = clock();
			Merge_sort(array, 0, number - 1);
			End_time = clock();
			cout << "归并排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "归并排序的比较次数：\t\t" << Merge_count << endl;
			break;
		case 8:
			Start_time = clock();
			Radix_sort(array, number);
			End_time = clock();
			cout << "基数排序所用的时间：\t\t" << End_time - Start_time << endl;
			cout << "基数排序的交换次数：\t\t" << "0" << endl;
			break;
		case 9:
			tag = 0;
			break;
		}
	}
	system("pause");
	return 0;
}