#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class miniParaser
{
public:
	miniParaser(void);
	~miniParaser(void);

	//�ҳ�������insert/create/select...
	string paraseSQL2Func(const char* sql);

	//����������create
	bool createTableBySQL(const char* sql);
	//������insert
	bool insertIntoTableByNameAndClounms(const char* sql);
	//ɾ�����drop
	bool dropTableByName(const char* name);
	//��ѯ���select
	//���صĽ����һ��Ϊ����
	vector<vector<string>> selectByCondition(const char* sql);



	//�ָ��ַ���
	string stringSpilt(string str,string sp);
};
