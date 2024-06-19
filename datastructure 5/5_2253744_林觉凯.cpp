#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#define Max_filename 10
#define NUM_OF_WORDS 26
using namespace std;
//�ж�ĳһ���ַ��Ƿ�Ϊ��ĸ
bool Is_alphabet(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}
//��ĳ���ַ���дתСд�ĺ���
char Transform_lowcase(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch += ('a' - 'A');
	return ch;
}
//��һ���ַ���ת��ΪСд
string Transform_str(string str)
{
	string retstr = "";
	for (unsigned int i = 0; i < str.length(); i++)
		retstr += Transform_lowcase(str[i]);
	return retstr;
}
//�ֵ��������
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
//�ֵ�����
class Trietree
{
public:
	Trietree();
	void Insert(string word);
	int Search(string word);
private:
	Trienode* root;
};
//��ʼ���ֵ���
Trietree::Trietree()
{
	root = NULL;
	root = new Trienode;
	if (root == NULL)
	{
		cout << "�ֵ�������ʧ�ܣ�" << endl;
		system("pause");
		return;
	}
}
//������word�����ֵ���
void Trietree::Insert(string word)
{
	Trienode* current = root;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		char element = word[i];
		if (current->Next[element - 'a'] == NULL)			//�����ǰ���ָ����һ������ָ�벻����
		{
			current->Next[element - 'a'] = new Trienode;	//�����һ���µĽ��
			if (current->Next[element - 'a'] == NULL)
			{
				cout << "�ڴ����ʧ�ܣ�" << endl;
				system("pause");
				return;
			}
		}
		current = current->Next[element - 'a'];				//��������������ȥ
	}
	current->Word_times++;									//����ʲ����ȥ��ôʵĴ�Ƶ��һ
}
//��������word���ֵĴ���
int Trietree::Search(string word)
{
	Trienode* current = root;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		char element = word[i];
		if (current->Next[element - 'a'] == NULL)			//�����������˵��û�иô�
			return 0;
		current = current->Next[element - 'a'];
	}
	return current->Word_times;								//��������ʾ���ôʴ�Ƶ
}
//��������ʵ��
int main()
{
	cout << "�ؼ��ּ���ϵͳ" << endl;
	FILE* fp;
	char File_name[Max_filename]; 
	cout << "�������ļ�����";
	cin.getline(File_name, Max_filename);
	fp = fopen(File_name, "w");									//�������򿪿��ļ�File_name
	if (fp == NULL)
	{
		cout << "�ļ���ʧ��" << endl;
		system("pause");
		return 0;
	}
	cout << endl << "������һ��Ӣ�ģ�" << endl;
	char File_content[1024];
	cin.getline(File_content, 1024);
	fputs(File_content, fp);									//����������ݱ������ı��ļ���
	cout << "�����ı��Ѿ��������ı��ļ���" << File_name << "���С�" << endl << endl;
	fclose(fp);										
	string KeyWord;
	cout << "������Ҫ�����Ĺؼ��֣�";								//��ùؼ���
	cin >> KeyWord;											
	cout << endl << "��ʾԴ�ļ���" << File_name << "����" << endl;	//��ʾ�ı��ļ��е�����
	fp = fopen(File_name, "r");
	fgets(File_content, 1024, fp);
	cout << File_content << endl;
	Trietree trietree;
	int i = 0;
	while (File_content[i] != '\0')
	{
		if (!Is_alphabet(File_content[i]))						//��������е�ĳ��λ�ò��ǵ��ʣ�������
		{
			i++;
			continue;
		}
		string current = "";
		while (Is_alphabet(File_content[i]))
		{
			current += Transform_lowcase(File_content[i]);		//������currentת��ΪСд��
			i++;
		}
		if (current != " ")										//����ĩβ�����ո�˵��������ʽ���
			trietree.Insert(current);							//�����ʲ����ֵ���
	}
	string Key_word = Transform_str(KeyWord);					//��Ҫ�����Ĺؼ���ת��ΪСд
	cout << endl << "��Դ�ļ��й��������� " << trietree.Search(Key_word) << " ���ؼ��֡�" << KeyWord << "��" << endl;
	system("pause");
	return 0;
}