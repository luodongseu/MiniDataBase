#pragma once
#include<string>
#include<vector>
#include"miniTimer.h"
#include"Delivery.h"
#include"BPlusTreeApi.h"
using namespace std;

class miniDao
{
public:
	miniTimer time;
	miniDao(void);
	~miniDao(void);
	/*创建表格 参数：T*/
	bool createTable(string ,Delivery );
	void insertData(string ,Delivery );
	Delivery findByOrder(string ,long);
	void findByRangeOrder(string ,long,long);
	void enumBPlusKey(string );
	void deleteData(string,long id);
	vector<string> headlist(string);



	/*转换表格名->文件名*/
	string name2Table(string name){
		return name.append(".tb");
	}
	/*转换表格名->b+树名*/
	string name2BPlus(string name){
		string a = name.append(".bp");
		return a;
	}
};
