#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#define Max_filename 10
#define NUM_OF_WORDS 26
using namespace std;
//判断某一个字符是否为字母
bool Is_alphabet(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}
//将某个字符大写转小写的函数
char Transform_lowcase(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch += ('a' - 'A');
	return ch;
}
//将一个字符串转化为小写
string Transform_str(string str)
{
	string retstr = "";
	for (unsigned int i = 0; i < str.length(); i++)
		retstr += Transform_lowcase(str[i]);
	return retstr;
}
//字典树结点类
class Trienode
{
public:
	int Word_times;
	Trienode* Next[NUM_OF_WORDS];
	Trienode()
	{
		Word_times = 0;
		for (int i = 0; i < NUM_OF_WORDS; i++)
			Next[i] = NULL;
	}
};
//字典树类
class Trietree
{
public:
	Trietree();
	void Insert(string word);
	int Search(string word);
private:
	Trienode* root;
};
//初始化字典树
Trietree::Trietree()
{
	root = NULL;
	root = new Trienode;
	if (root == NULL)
	{
		cout << "字典树构造失败！" << endl;
		system("pause");
		return;
	}
}
//将单词word插入字典树
void Trietree::Insert(string word)
{
	Trienode* current = root;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		char element = word[i];
		if (current->Next[element - 'a'] == NULL)			//如果当前结点指向下一个结点的指针不存在
		{
			current->Next[element - 'a'] = new Trienode;	//则分配一个新的结点
			if (current->Next[element - 'a'] == NULL)
			{
				cout << "内存分配失败！" << endl;
				system("pause");
				return;
			}
		}
		current = current->Next[element - 'a'];				//如果存在则继续下去
	}
	current->Word_times++;									//这个词插入进去后该词的词频加一
}
//搜索单词word出现的次数
int Trietree::Search(string word)
{
	Trienode* current = root;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		char element = word[i];
		if (current->Next[element - 'a'] == NULL)			//如果不存在则说明没有该词
			return 0;
		current = current->Next[element - 'a'];
	}
	return current->Word_times;								//存在则显示出该词词频
}
//主函数的实现
int main()
{
	cout << "关键字检索系统" << endl;
	FILE* fp;
	char File_name[Max_filename]; 
	cout << "请输入文件名：";
	cin.getline(File_name, Max_filename);
	fp = fopen(File_name, "w");									//建立并打开空文件File_name
	if (fp == NULL)
	{
		cout << "文件打开失败" << endl;
		system("pause");
		return 0;
	}
	cout << endl << "请输入一段英文：" << endl;
	char File_content[1024];
	cin.getline(File_content, 1024);
	fputs(File_content, fp);									//将输入的内容保存在文本文件中
	cout << "本段文本已经保存在文本文件“" << File_name << "”中。" << endl << endl;
	fclose(fp);										
	string KeyWord;
	cout << "请输入要检索的关键字：";								//获得关键字
	cin >> KeyWord;											
	cout << endl << "显示源文件“" << File_name << "”：" << endl;	//显示文本文件中的内容
	fp = fopen(File_name, "r");
	fgets(File_content, 1024, fp);
	cout << File_content << endl;
	Trietree trietree;
	int i = 0;
	while (File_content[i] != '\0')
	{
		if (!Is_alphabet(File_content[i]))						//如果文章中的某个位置不是单词，则跳过
		{
			i++;
			continue;
		}
		string current = "";
		while (Is_alphabet(File_content[i]))
		{
			current += Transform_lowcase(File_content[i]);		//将单词current转化为小写后
			i++;
		}
		if (current != " ")										//单词末尾遇到空格，说明这个单词结束
			trietree.Insert(current);							//将单词插入字典树
	}
	string Key_word = Transform_str(KeyWord);					//将要搜索的关键词转化为小写
	cout << endl << "在源文件中共检索到： " << trietree.Search(Key_word) << " 个关键字“" << KeyWord << "”" << endl;
	system("pause");
	return 0;
}