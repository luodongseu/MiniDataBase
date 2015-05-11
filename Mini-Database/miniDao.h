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
	/*������� ������T*/
	bool createTable(string ,Delivery );
	void insertData(string ,Delivery );
	Delivery findByOrder(string ,long);
	void findByRangeOrder(string ,long,long);
	void enumBPlusKey(string );
	void deleteData(string,long id);
	vector<string> headlist(string);



	/*ת�������->�ļ���*/
	string name2Table(string name){
		return name.append(".tb");
	}
	/*ת�������->b+����*/
	string name2BPlus(string name){
		string a = name.append(".bp");
		return a;
	}
};
