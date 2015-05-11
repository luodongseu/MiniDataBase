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

	//找出操作符insert/create/select...
	string paraseSQL2Func(const char* sql);

	//创建表格操作create
	bool createTableBySQL(const char* sql);
	//插入表格insert
	bool insertIntoTableByNameAndClounms(const char* sql);
	//删除表格drop
	bool dropTableByName(const char* name);
	//查询表格select
	//返回的结果第一行为列名
	vector<vector<string>> selectByCondition(const char* sql);



	//分割字符串
	string stringSpilt(string str,string sp);
};
