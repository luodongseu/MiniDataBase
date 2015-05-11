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

/*��ͨ����*/
XMLSrv xmlSrv;
	
/*�����ַ���*/
miniParaser par;

/*ʱ�����*/
miniTimer timea;

/*DAO����*/
miniDao md;

//������
int main()  
{  
	long deliveryquery=-1;//���ѯ�ؼ���
	long mindeliveryquery=-2;//��Χ��ѯ���޹ؼ���
	long maxdeliveryquery=-3;//��Χ��ѯ���޹ؼ���
	long deliverydelete=-4;//ɾ���ؼ���
	long deliveryinsert=-5;//����ؼ���
	miniView view;
	cout<<"------------------hello miniDatabase!---------------------\n";
	cout<<"----------------author:ld|dtt|lx|cc|ctt-------------------\n";
	cout<<"------------------------version:2.0-------------------------\n";

	view.createTable("s");

	while(1)
	{
		int operation=0;//��ȡ�û�����
		string info;//��Ų�ѯ��Ϣ
		cout<<"\n########################\n���ܲ˵���\n"<<"1.���ѯ\n"<<"2.��Χ��ѯ\n"<<"3.ɾ��\n"<<"4.����\n"<<"0:�˳�\n########################\n"<<endl;
		cout<<"�����������ţ�\n";
		cin.clear();//���ô�������
		cin.sync();
		cout<<"imenu> ";cin>>operation;
		cin.clear();//���ô�������
		cin.sync();
		if(operation==0)
			break;
		switch(operation)
		{
		case 1 ://���ѯ
			view.dotQuerySQL();
			//���ѯ������Ϊdeliveryquery�������ţ�
			//cout<<deliveryquery<<endl;//����
			break;
		case 2://��Χ��ѯ
			view.rgQuerySQL();
			//��Χ��ѯ������Ϊmindeliveryquery�����������ޣ�maxdeliveryquery�����������ޣ�
			//cout<<mindeliveryquery<<endl;//����
			//cout<<maxdeliveryquery<<endl;//����
			break;
		case 3://ɾ��
			view.deleteSQL();
			////ɾ��������Ϊdeliverydelete�������ţ�
			//cout<<deliverydelete<<endl;//����
			break;
		case 4://����
			view.insertSQL();
			////ɾ��������Ϊdeliveryinsert�������ţ�
			//cout<<deliveryinsert<<endl;//����
			break;
		}
	}

	//while(1)
	//{
	//	int operation=0;//��ȡ�û�����
	//	string info;//��Ų�ѯ��Ϣ
	//	cout<<"\n########################\n���ܲ˵���\n"<<"1.�������\n"<<"2.��������\n"<<"3.��ѯ\n"<<"0:�˳�\n########################\n"<<endl;
	//	cout<<"�����������ţ�\n";
	//	cin.clear();//���ô�������
	//	cin.sync();
	//	cout<<"imenu> ";cin>>operation;
	//	cin.clear();//���ô�������
	//	cin.sync();
	//	if(operation==0)
	//		break;
	//	switch(operation)
	//	{
	//	case 1 ://�������
	//		createSQL();
	//		break;
	//	case 3://��ѯ��Ϣ
	//		findSQL();
	//		break;
	//	case 2://������Ϣ
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
	system("pause");//��ֱֹ���˳�



	//�ҵĴ�����
	cout<<"Hello mini!"<<endl;

    return 0;  
}  


