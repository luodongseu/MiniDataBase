#include "miniDao.h"

#include<iostream>
#include<fstream>
using namespace std;

miniDao::miniDao(void)
{
	
}

miniDao::~miniDao(void)
{
	
}

bool miniDao::createTable(string table_name,Delivery d)//创建一个表和b+树
{
	/**判断表是否存在，不存在才创建，否则直接退出函数*/
	ifstream if1(name2Table(table_name).c_str());
	ifstream if2(name2BPlus(table_name).c_str());
	if(if1||if2){
		cout<<"表已经存在，请勿重复创建！"<<endl;
		return false;
	}

	/*创建一个表格文件*/
	fstream iof;
	iof.open(name2Table(table_name).c_str(),ios::out|ios::binary);
	if(!iof){
		cerr << "Open Failed!" << endl;
		return false;
		abort();
	}

	char s[10];
	sprintf(s,"%ld",d.Number);
	iof.write(s,10);
	iof.write(d.Name.c_str(),30);
	iof.write(d.Tel.c_str(),15);
	iof.write(d.Address.c_str(),30);
	iof.write(d.Comp.c_str(),10);
	iof.write(d.Part.c_str(),5);
	iof.close();


	/*创建一个对应的b+树文件*/
	time.Start();
	BPlusTreeApi btree(name2BPlus(table_name),_CREATE);
	btree.Build_BPlus_Tree();
	time.Stop();

	cout<< "Create Table "<<table_name<<" Success" <<endl;
	return true;
}


void miniDao::insertData(string table_name,Delivery d)//向表和b+树中顺序插入一行数据
{
	cout<< "begin insert into "<<table_name <<" key = ["<<d.Number<<"]"<<endl;


	fstream iof;
	iof.open(name2Table(table_name).c_str(),ios::out|ios::in|ios::binary|ios::_Nocreate);
	if(!iof){
		cerr << "Table not exist!" << endl;
		abort();
	}


	//打开一个对应的b+树
	BPlusTreeApi btree(name2BPlus(table_name),0);
	TRecord tr;
	iof.seekg(0,ios::end);
	tr.key = d.Number;
	tr.name = iof.tellg();
	tr.Raddress = iof.tellg();
	if(!btree.Insert_BPlus_Tree(tr)){
		cout<<"主键重复！"<<endl;
		iof.close();
		//btree.EnumLeafKey();
		btree.~BPlusTreeApi();
		return;
	}


	////////////for(long i=0;i<1000000;i++)
	////////////{
	////////////	//TRecord tr;
	////////////	tr.key = i;
	////////////	
	////////////	if(!btree.Insert_BPlus_Tree(tr)){
	////////////		cout<<"主键重复！"<<endl;
	////////////		iof.close();
	////////////		continue;
	////////////	}

	////////////	//char s[10];
	////////////	//sprintf(s,"%ld",i);
	////////////	//string temps(s);


	////////////	//string name = "name_"+temps;
	////////////	//char tel1[10];
	////////////	//sprintf(tel1,"%07ld",i);
	////////////	//string temp(tel1);
	////////////	//string tel = "158"+temp;

	////////////	//
	////////////	//string add = "In_" + temps + "Street";
	////////////	//string com = "YT";
	////////////	//string part = "P1";


	////////////	//iof.write(s,10);
	////////////	//iof.write(name.c_str(),30);
	////////////	//iof.write(tel.c_str(),15);
	////////////	//iof.write(add.c_str(),30);
	////////////	//iof.write(com.c_str(),10);
	////////////	//iof.write(part.c_str(),5);

	////////////	cout<<"插入成功"<<i<<endl;
	////////////
	////////////	tr.name = tr.name + 100;
	////////////}


	char s[10];
	sprintf(s,"%ld",d.Number);
	iof.write(s,10);
	iof.write(d.Name.c_str(),30);
	iof.write(d.Tel.c_str(),15);
	iof.write(d.Address.c_str(),30);
	iof.write(d.Comp.c_str(),10);
	iof.write(d.Part.c_str(),5);
	iof.close();

//	btree.EnumLeafKey();
}
Delivery miniDao::findByOrder(string table_name,long k)//查找到一个数据
{
	time.Start();
	ifstream if1(name2Table(table_name).c_str());
	ifstream if2(name2BPlus(table_name).c_str());
	if(!if1||!if2){
		cout<<"没有可查询的表存在！"<<endl;
		return Delivery();
	}

	cout<< "begin query from b+ tree: "<<table_name <<endl;
	//打开一个对应的b+树
	BPlusTreeApi btree(name2BPlus(table_name),0);
	TRecord tr;
	tr.key = k;
	SearchResult sr;
	int i;
	btree.Search_BPlus_Tree(tr,sr,i);//查找b+树中的数据

	if(sr.na<0){
		cout<<"没有找到符合的数据！"<<endl;
		return Delivery();
	}
	cout<<"在b+树中找到地址："<<sr.na<<endl;
	
	//通过得到的地址查找表格
	fstream iof;
	iof.open(name2Table(table_name).c_str(),ios::out|ios::binary|ios::_Nocreate);
	if(!iof){
		cerr << "Open Failed!" << endl;
		abort();
	}

	char num[10];
	char name[30];
	char tel[15];
	char addr[30];
	char comp[10];
	char port[5];

	iof.seekg(sr.na+20,ios::beg);
	iof.read(num,10);
	iof.read(name,30);
	iof.read(tel,15);
	iof.read(addr,30);
	iof.read(comp,10);
	iof.read(port,5);

	cout<<num<<endl;
	iof.close();
	time.Stop();
	return Delivery(atol(num),name,tel,addr,comp,port);
}
void miniDao::findByRangeOrder(string table_name,long k,long p)//查找到一个数据
{
	
	ifstream if1(name2Table(table_name).c_str());
	ifstream if2(name2BPlus(table_name).c_str());
	if(!if1||!if2){
		cout<<"没有可查询的表存在！"<<endl;
		return;
	}

	cout<< "begin query from b+ tree: "<<table_name <<endl;
	//打开一个对应的b+树
	BPlusTreeApi btree(name2BPlus(table_name),0);
	TRecord tr1;
	TRecord tr2;

	tr1.key = k;
	tr2.key = p;
	SearchResult sr;
	int i;
	
	time.Start();
	vector<node> vnodes = btree.Search_BPlus_TreeRange(tr1,tr2,sr,i);
	time.Stop();
	
	cout<<"找到结果！如下"<<endl;
	for(int i= 0; i< vnodes.size();i++){
		cout<<"key = "<<vnodes[i].first<<":";
		cout<<"add = "<<vnodes[i].second<<endl;
	}

}

void miniDao::enumBPlusKey(string table_name)//枚举所有b+树里面的键值
{
	//
	//time.Start();
	//ifstream if1(name2Table(table_name).c_str());
	//ifstream if2(name2BPlus(table_name).c_str());
	//if(!if1||!if2){
	//	cout<<"没有可查询的表存在！"<<endl;
	//	return;
	//}

	////打开一个对应的b+树
	//BPlusTreeApi btree(name2BPlus(table_name),0);
	//vector<node> vnodes = btree.EnumLeafKey();
	//time.Stop();
	//cout<<"找到结果！如下"<<endl;
	//for(int i= 0; i< vnodes.size();i++){
	//	cout<<"key = "<<vnodes[i].first<<":";
	//	cout<<"add = "<<vnodes[i].second<<endl;
	//}
	
}

void miniDao::deleteData(string table_name,long id)//删除数据
{
	time.Start();
	ifstream if1(name2Table(table_name).c_str());
	ifstream if2(name2BPlus(table_name).c_str());
	if(!if1||!if2){
		cout<<"没有可查询的表存在！"<<endl;
		return;
	}

	//打开一个对应的b+树
	BPlusTreeApi btree(name2BPlus(table_name),0);
	TRecord tr;
	tr.key = id;
	SearchResult sr;
	int i;
	btree.Search_BPlus_Tree(tr,sr,i);//查找b+树中的数据
	cout<<"i = "<<i<<endl;
	cout<<"bd "<<sr.Baddress<<endl;
	cout<<"aa "<<sr.Baddress<<endl;
	if(sr.exist){
		btree.Delete_BPlus_Tree(tr);
		tr.key = 0-tr.key;
		tr.name = sr.na;
		btree.Insert_BPlus_Tree(tr);
		cout<<"modify!"<<endl;
	}

	vector<node> vns =  btree.EnumLeafKey();
	for(int i=0;i<vns.size();i++){
		cout<<"-node = [ "<<vns[i].first<<";"<<vns[i].second<<" ]"<<endl;	
	}
}

vector<string> miniDao::headlist(string table_name)//输出表头
{
	vector<string> list;

	ifstream if1(name2Table(table_name).c_str());
	if(!if1){
		cout<<"没有可查询的表存在！"<<endl;
	}

	fstream iof;
	iof.open(name2Table(table_name).c_str(),ios::out|ios::binary);
	if(!iof){
		cerr << "Open Failed!" << endl;
		abort();
	}

	char headnum[10];
	char headname[30];
	char headtel[15];
	char headaddr[30];
	char headcomp[10];
	char headport[5];

	iof.read(headnum,10);
	iof.read(headname,30);
	iof.read(headtel,15);
	iof.read(headaddr,30);
	iof.read(headcomp,10);
	iof.read(headport,5);
	iof.close();

	string num = headnum;
	string name = headname;
	string tel = headtel;
	string addr = headaddr;
	string comp = headcomp;
	string port = headport;

	list.push_back(num);
	list.push_back(name);
	list.push_back(tel);
	list.push_back(addr);
	list.push_back(comp);
	list.push_back(port);


	return list;
}

vector<node>