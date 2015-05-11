#include "miniView.h"
#include<iostream>
using namespace std;
const static string table = "delivery";

miniView::miniView(void)
{
}

miniView::~miniView(void)
{
}
void miniView::dotQuerySQL()
{
	long num;
	for(int i=0;;i++)
	{
		cout<<"请输入要查找的运单号："<<endl;
		cout<<"imenu> ";
		cin>>num;
		if(num<=0)
			cout<<"警告！！！输入格式有误！订单号应大于0！\n"<<endl;
		else{
			Delivery delivery = md.findByOrder(table,num);
			cout<<delivery.Number<<endl;
			if(delivery.Number == 0)break;
			cout<<"Number  :"<<delivery.Number<<endl;;
			cout<<"Name    :"<<delivery.Name<<endl;
			cout<<"Telphone:"<<delivery.Tel<<endl;
			cout<<"Address :"<<delivery.Address<<endl;
			cout<<"Company :"<<delivery.Comp<<endl;
			cout<<"Partion :"<<delivery.Part<<endl;		
			break;
		}
	}
}
void miniView::rgQuerySQL()
{
	long num1;//下限
	long num2;//上限
	for(int i=0;;i++)
	{
		cout<<"请输入要查找的运单号范围下限："<<endl;
		cout<<"imenu> ";
		cin>>num1;
		if(num1<=0)
			cout<<"警告！！！输入格式有误！订单号应大于0！\n"<<endl;
		else
			break;

	}
	for(;;)
	{
		cout<<"请输入要查找的运单号范围上限："<<endl;
		cout<<"imenu> ";
		cin>>num2;
		if(num1>num2)
			cout<<"警告！！！输入格式有误！订单号查询上限应大于下限！\n"<<endl;
		else{
			md.findByRangeOrder(table,num1,num2);
			break;
		
		}
	}
}

void miniView::deleteSQL()
{
	long num;
	for(int i=0;;i++)
	{
		cout<<"请输入要删除的运单号："<<endl;
		cout<<"imenu> ";
		cin>>num;
		if(num<=0)
			cout<<"警告！！！输入格式有误！订单号应大于0！\n"<<endl;
		else{
			md.deleteData(table,num);		
			break;
		}
	}
}
void miniView::insertSQL()
{
	long
	long num;
	cout<<"可用订单号："<<endl;
	//调用函数返回空闲订单号并输出给用户
	for(int i=0;;i++)
	{
		cout<<"请输入要插入的运单号："<<endl;
		cout<<"imenu> ";
		cin>>num;
		if(num<=0){
			cout<<"警告！！！输入格式有误！订单号应大于0！\n"<<endl;
		}
		else{
			Delivery d;
			cout<<"a";
			cin>>d.Name;
			cout<<"b";
			cin>>d.Tel;
			cout<<"c";
			cin>>d.Address;
			cout<<"d\n";
			cout<<"e\n";
			d.Number = num;
			d.Comp = "aa";
			d.Part = "P1";
			md.insertData(table,d);
				
			break;
		}
	}
}

void miniView::createTable(string table_name){
	Delivery del(12,"reciver","telphone","address","company","partion");
	md.createTable(table,del);
}

void miniView::showTableHead(string table_name)
{
	vector<string> heads = md.headlist(table);
	for(int i=0;i<heads.size();i++){
		cout<<heads[i]<<" | ";
	}
	cout<<endl;
}