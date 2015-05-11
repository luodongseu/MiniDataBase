#include "miniParaser.h"

miniParaser::miniParaser(void)
{
}

miniParaser::~miniParaser(void)
{
}
//找出操作符insert/create/select...
string miniParaser::paraseSQL2Func(const char* sql){
	return false;
}

//创建表格操作create
bool miniParaser::createTableBySQL(const char* sql){
	return false;
}

//插入表格insert
bool miniParaser::insertIntoTableByNameAndClounms(const char* sql){
	return false;
}

//删除表格drop
bool miniParaser::dropTableByName(const char* name){
	return false;
}

//查询表格select
//返回的结果第一行为列名
vector<vector<string>> miniParaser::selectByCondition(const char* sql){
	vector<vector<string>> vts;
	return vts;
}

//分割
string miniParaser::stringSpilt(string str,string sp){
	string res = "";
	int comma_n = 0;
	comma_n = str.find(sp);
	if( -1 == comma_n )
	{
		res = str;
		
	}else{
		res = str.substr( 0, comma_n);
	}
	return res;
}