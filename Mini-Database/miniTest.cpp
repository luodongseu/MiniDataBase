#include"miniDao.h"
#include"XMLSrv.h"
#include"miniParaser.h"
#include"miniTimer.h"
#include"miniView.h"
#include<fstream>
#include<iostream>
#include<vector>
#include <string>
using namespace std;

/*普通服务*/
XMLSrv xmlSrv;
	
/*解析字符串*/
miniParaser par;

/*时间服务*/
miniTimer timea;

/*DAO操作*/
miniDao md;

//测试类
int main()  
{  
	long deliveryquery=-1;//点查询关键字
	long mindeliveryquery=-2;//范围查询下限关键字
	long maxdeliveryquery=-3;//范围查询上限关键字
	long deliverydelete=-4;//删除关键字
	long deliveryinsert=-5;//插入关键字
	miniView view;
	cout<<"------------------hello miniDatabase!---------------------\n";
	cout<<"----------------author:ld|dtt|lx|cc|ctt-------------------\n";
	cout<<"------------------------version:2.0-------------------------\n";

	view.createTable("s");

	while(1)
	{
		int operation=0;//获取用户操作
		string info;//存放查询信息
		cout<<"\n########################\n功能菜单：\n"<<"1.点查询\n"<<"2.范围查询\n"<<"3.删除\n"<<"4.插入\n"<<"0:退出\n########################\n"<<endl;
		cout<<"请输入操作序号：\n";
		cin.clear();//重置错误输入
		cin.sync();
		cout<<"imenu> ";cin>>operation;
		cin.clear();//重置错误输入
		cin.sync();
		if(operation==0)
			break;
		switch(operation)
		{
		case 1 ://点查询
			view.dotQuerySQL();
			//点查询：参数为deliveryquery（订单号）
			//cout<<deliveryquery<<endl;//测试
			break;
		case 2://范围查询
			view.rgQuerySQL();
			//范围查询：参数为mindeliveryquery（订单号下限）maxdeliveryquery（订单号上限）
			//cout<<mindeliveryquery<<endl;//测试
			//cout<<maxdeliveryquery<<endl;//测试
			break;
		case 3://删除
			view.deleteSQL();
			////删除：参数为deliverydelete（订单号）
			//cout<<deliverydelete<<endl;//测试
			break;
		case 4://插入
			view.insertSQL();
			////删除：参数为deliveryinsert（订单号）
			//cout<<deliveryinsert<<endl;//测试
			break;
		}
	}

	//while(1)
	//{
	//	int operation=0;//获取用户操作
	//	string info;//存放查询信息
	//	cout<<"\n########################\n功能菜单：\n"<<"1.创建表格\n"<<"2.插入数据\n"<<"3.查询\n"<<"0:退出\n########################\n"<<endl;
	//	cout<<"请输入操作序号：\n";
	//	cin.clear();//重置错误输入
	//	cin.sync();
	//	cout<<"imenu> ";cin>>operation;
	//	cin.clear();//重置错误输入
	//	cin.sync();
	//	if(operation==0)
	//		break;
	//	switch(operation)
	//	{
	//	case 1 ://创建表格
	//		createSQL();
	//		break;
	//	case 3://查询信息
	//		findSQL();
	//		break;
	//	case 2://插入信息
	//		insertSQL();
	//		break;
	//	}
	//}

	
	//vector<string> a;
	//a.push_back("dasdasd");
	//a.push_back("dasdadasdasdas");
	//a.push_back("dsadasdsa");


	//for(int i=0;i<a.size();i++){
	//	cout<<a[i]<<endl;
	//}

	////md.createTable("demo21",a);

	//char s[10];
/*	for(KEYTYPE i=0;i<22;i++){
		string name = "name";
		sprintf(s,"%ld",i); 
		name += s;
		md.insertData("demo21",i%21,name);
	}
	md.enumBPlusKey("demo21");*/

	/*for(KEYTYPE i=0;i<100;i++){
		string name = "name";
		sprintf(s,"%ld",i); 
		name += s;
		md.insertData("demo21",i,name);
	}*/
	//KEYTYPE j = 18;
	//md.insertData("demo21",j,"a");
	//j = 19;
	//md.insertData("demo21",j,"a");
	//j = 16;
	//md.insertData("demo21",j,"a");
	//j = 13;
	//md.insertData("demo21",j,"a");
	//j = 15;
	//md.insertData("demo21",j,"a");
	//j = 19;
	//md.insertData("demo21",j,"a");
	//j = 22;
	//md.insertData("demo21",j,"a");
	//j = 656;
	//md.insertData("demo21",j,"a");
	//j = 4;
	//md.insertData("demo21",j,"a");
	//j = 23;
	//md.insertData("demo21",j,"a");
	//j = 1;
	//md.insertData("demo21",j,"a");
	//j = 2;
	//md.insertData("demo21",j,"a");
	//j = 4;
	//md.insertData("demo21",j,"a");
	//j = 100;
	//md.insertData("demo21",j,"a");
	//j = 44;
	//md.insertData("demo21",j,"a");
	//j = 1212;
	//md.insertData("demo21",j,"a");
	//j = 333;
	//md.insertData("demo21",j,"a");
	//j = 2323;
	//md.insertData("demo21",j,"a");
	//j = 2112;
	//md.insertData("demo21",j,"a");
	//j = 3232;
	//md.insertData("demo21",j,"a");
	//j = 42324;
	//md.insertData("demo21",j,"a");
	/*md.enumBPlusKey("demo21");
	md.deleteData("demo21",100);
	md.enumBPlusKey("demo21");
	md.findByOrder("demo21",100);*/	
	system("pause");//阻止直接退出



	//我的代码区
	cout<<"Hello mini!"<<endl;

    return 0;  
}  


