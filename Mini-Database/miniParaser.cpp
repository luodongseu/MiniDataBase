#include "miniParaser.h"

miniParaser::miniParaser(void)
{
}

miniParaser::~miniParaser(void)
{
}
//�ҳ�������insert/create/select...
string miniParaser::paraseSQL2Func(const char* sql){
	return false;
}

//����������create
bool miniParaser::createTableBySQL(const char* sql){
	return false;
}

//������insert
bool miniParaser::insertIntoTableByNameAndClounms(const char* sql){
	return false;
}

//ɾ�����drop
bool miniParaser::dropTableByName(const char* name){
	return false;
}

//��ѯ���select
//���صĽ����һ��Ϊ����
vector<vector<string>> miniParaser::selectByCondition(const char* sql){
	vector<vector<string>> vts;
	return vts;
}

//�ָ�
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