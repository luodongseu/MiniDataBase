#pragma once
#include"miniDao.h"
#include"XMLSrv.h"
#include"miniParaser.h"
#include"miniTimer.h"
#include<fstream>
#include<iostream>
#include<vector>
#include <string>

class miniView
{
public:

	/*��ͨ����*/
	XMLSrv xmlSrv;
		
	/*�����ַ���*/
	miniParaser par;

	/*ʱ�����*/
	miniTimer timea;

	/*DAO����*/
	miniDao md;
	
	
	
	miniView(void);
	~miniView(void);
	void dotQuerySQL();
	void rgQuerySQL();
	void deleteSQL();
	void insertSQL();


	void createTable(string);
	void showTableHead(string);
	
};


/**************************************************************************************/
//
///*�������param ����������**/
//void createNewTable(string tbname,vector<string> cols){
//	time.Start();//��ʱ��ʼ
//	xmlSrv.createXml(tbname.data(),cols);  
//	time.Stop();//��ʱֹͣ
//}
//
///**�鿴��ͷ*/
//void showTableHeads(string tbname){
//	time.Start();//��ʱ��ʼ
//	vector<string> heads = xmlSrv.findTableHead(tbname.data());  
//	time.Stop();//��ʱֹͣ
//	cout<<" \t";
//	for(int i=0;i<heads.size();i++){
//		string h = heads[i];
//		if(heads[i].size()>=8){
//			h= h.substr(0,7);
//		}
//		cout<<h<<"\t";				
//		cout<<"|"<<"\t";
//	}
//	cout<<endl;
//	
//}
//
///**��ȡ���������û��ı������**/
//vector<string> getLocalTables(){
//	time.Start();//��ʱ��ʼ
//	/*��Ž��*/
//	vector<string> result;
//	vector<string> tbs = xmlSrv.findAllTables();
//	time.Stop();//��ʱֹͣ
//	if(!tbs.empty()){
//		cout<<"Found "<<tbs.size()<<" tables!"<<endl;
//		for(int i=0;i<tbs.size();i++){
//			string tb = par.stringSpilt(tbs[i],".xml");
//			result.push_back(tb);
//			cout<<i<<":"<<tb<<endl;
//		}
//	}
//	return result;
//}
//
//
//
//
//
//
///*��ѯ��������*/
//void findTableRecorder(const char* cXmlName1,const char* clounm,const char* value){
//	time.Start();//��ʱ��ʼ
//	/*��ѯ���е�����*/
//	vector<vector<string>> datas = xmlSrv.findByPropertise(cXmlName1,clounm,value);
//	time.Stop();//��ʱֹͣ
//	vector<string> head = xmlSrv.findTableHead(cXmlName1);
//	cout<<" \t";
//	for(int i=0;i<head.size();i++){
//		cout<<head[i]<<"\t";				
//		cout<<"|"<<"\t";
//	}
//	cout<<endl;
//	for(int i=0;i<datas.size();i++){
//		cout<<i<<":\t";
//		for(int j=0;j<datas[i].size();j++){
//			cout<<datas[i][j]<<"\t";				
//			cout<<"|"<<"\t";
//		}
//		cout<<endl;
//	}
//	
//}
//
///**������**/
//void outputTable(vector<vector<string>> datas){
//	if(!datas.empty()){
//		cout<<" \t";
//		for(int i=0;i<datas[0].size();i++){
//			string h = datas[0][i];
//			if(datas[0][i].size()>=8){
//				h= h.substr(0,7);
//			}
//			cout<<h<<"\t";				
//			cout<<"|"<<"\t";
//		}
//		cout<<endl;
//		for(int i=1;i<datas.size();i++){
//			cout<<i<<":\t";
//			for(int j=0;j<datas[i].size();j++){
//				cout<<datas[i][j]<<"\t";				
//				cout<<"|"<<"\t";
//			}
//			cout<<endl;
//		}
//	}
//}
//
////���Եѿ�����
//void testX(){
//	vector<string> cs;
//	cs.push_back("tb_1.age");
//	cs.push_back("tb_1.name");
//	
//	time.Start();//��ʱ��ʼ
//	/*��ѯ���е�����*/
//	vector<vector<string>> datas = xmlSrv.findClounmsIn(xmlSrv.getXResult("tb_1",xmlSrv.getXResult("tb_3",xmlSrv.getXResult("tb_1","tb_2"))),cs);
//	time.Stop();//��ʱֹͣ
//
//	outputTable(datas);
//}
///**������SQL**/
//void createSQL(){
//	string sql = "create table ";
//	string table;
//	string temp;
//	vector<string> col;//�������Ϣ
//	cout<<"������Ҫ������������(-1�鿴�Ѵ��ڵı��)��\n";
//	cout<<"isql> ";
//	cin>>table;
//	while(table == "-1"){
//		getLocalTables();
//		cout<<"isql> ";cin>>table;
//	}
//	sql += table;
//	sql +="(";
//	for(int i=0;i<200;i++)
//	{
//		temp.clear();
//		cout<<"�������"<<i+1<<"�б������(������-1����)��\n";
//		cout<<"isql> ";cin>>temp;
//		if(temp=="-1"){
//			if(col.empty()){
//				cout<<"����������1�У�\n";
//				cout<<"isql> ";cin>>temp;
//			}else
//				break;
//		}
//		if(col.size()>0){
//			sql+=",";
//		}
//		sql += temp;
//		col.push_back(temp);
//	}
//	sql += ");";
//	cout<<"sql> ";
//	cout<<sql<<endl;
//	createNewTable(table,col);
//}
///**��ѯsql***/
//void findSQL(){
//	string sql = " from ";
//	string sql0 = "";
//	string temp;
//	string clounm1;
//	string clounm2;
//	int cho = -1;
//	vector<string> r_col;//�������Ϣ
//	vector<string> f_tab;//�����Դ
//	vector<vector<string>> datas;//���
//	
//	cout<<"������Ҫ��ѯ�ı��(-1����;-2�鿴�������б��)��\n";
//	while(true){
//		temp.clear();
//		cout<<"isql> ";cin>>temp;
//		if(temp=="-1")
//			break;
//		if(temp=="-2"){
//			getLocalTables();
//			continue;
//		}
//		if(f_tab.size()>0){
//			sql += ",";
//			
//		}
//		sql += temp;
//		f_tab.push_back(temp);
//	}
//	
//	if(f_tab.size()==1){
//		cout<<"�������ж�����(0:��������;-1�鿴��ͷ;-2��ʾ�鿴ȫ��;����\n";
//		
//		cout<<"������������";
//		cout<<"isql> ";
//		cin>>clounm1;
//		while(clounm1 == "-1"){
//			showTableHeads(f_tab[0]);
//			cout<<"isql> ";cin>>clounm1;
//		}
//		if(clounm1 == "-2"){
//			findTableRecorder(f_tab[0].data(),"","");
//			return;
//		}else if(clounm1 == "0"){
//			clounm1 = "";
//			clounm2 = "";
//		}
//		else{
//			cout<<"������ֵ��";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"������Ҫ���ص�����(��:tb.id;-1����)��\n";
//		
//		while(true){
//			temp.clear();
//			cout<<"isql> ";cin>>temp;
//			if(temp=="-1")
//			{
//				if(r_col.empty()){
//					sql = "*" + sql;
//				}
//				break;
//			}
//			if(r_col.size()>0){
//				sql0 +=",";
//			}
//			sql0 += temp;
//
//			r_col.push_back(temp);
//		}
//	
//		
//		time.Start();
//		datas = xmlSrv.findClounmsIn(xmlSrv.findColEqStr(xmlSrv.findAllCols(f_tab[0].data()),clounm1,clounm2),r_col);
//		time.Stop();
//	}
//	else if(f_tab.size()>=2){
//		cout<<"�������ж�����(��ʽ��tb1.id = tb2.id�� mid)��\n";
//		cout<<"�������ֶ�1(-1�鿴��ͷ;-2��ʾ��������ѯ)��\n";
//		cout<<"isql> ";cin>>clounm1;
//		while(clounm1 == "-1"){
//			for(int i=0;i<f_tab.size();i++){
//				cout<<"��"<<f_tab[i]<<":";
//				showTableHeads(f_tab[i]);
//			}
//			cout<<"isql> ";cin>>clounm1;
//		}
//		if(clounm1 == "-2"){
//			clounm1 = "";
//			clounm2 = "";
//		}else{
//			cout<<"������ֵ���ֶ�2��\n";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"������Ҫ���ص�����(��:tb.id;-1����)��\n";
//		while(true){
//			temp.clear();
//			cout<<"isql> ";cin>>temp;
//			if(temp=="-1")
//			{	
//				if(r_col.empty()){
//					sql = "*" + sql;
//				}
//				break;
//			}
//			if(r_col.size()>0){
//				sql0 += ",";
//			}
//			sql0 += temp;
//			r_col.push_back(temp);
//		}
//		
//		time.Start();
//		datas = xmlSrv.getXResult(f_tab[0].data(),f_tab[1].data());
//		for(int i=2;i<f_tab.size();i++){
//			datas = xmlSrv.getXResult(f_tab[i].data(),datas);
//		}
//		datas = xmlSrv.findClounmsIn(xmlSrv.findT1EqT2(datas,clounm1,clounm2),r_col);
//		time.Stop();
//	}
//	sql = "select "+ sql0 + sql + ";";
//	cout<<"sql> ";cout<<sql<<endl;
//	outputTable(datas);
//	
//}
//
///**����SQL**/
//void insertSQL(){
//	string sql = "insert into table ";
//	string temp;
//	string clounm1;
//	vector<string> r_col;//�������Ϣ
//	vector<vector<string>> r_cols;//�������Ϣ
//	cout<<"������������(0�鿴���б��;-1ȡ��)\n";//�������ݿ��д�ŵı������
//	cout<<"isql> ";cin>>temp;
//	if(temp=="-1")
//		return;
//	if(temp=="0"){
//		getLocalTables();
//		cout<<"������������";
//		cout<<"isql> ";cin>>temp;
//	}
//	sql += temp;
//	vector<string> heads = xmlSrv.findTableHead(temp.data());
//	if(heads.empty()){
//		cout<<"insert interrupt:No that table exists!"<<endl;
//		return;
//	}
//	sql += " value( ";
//	cout<<"�밴���������ݣ�\n";
//	for(int i=0;i<heads.size();i++){
//		cout<<"��"<<heads[i]<<":";
//		cout<<"isql> ";cin >> clounm1;
//		if(r_col.size()>0){
//			sql += ",";
//		}
//		sql += clounm1;
//		r_col.push_back(clounm1);
//	}
//	r_cols.push_back(r_col);
//	sql += ");";
//	cout<<"sql> ";
//	cout<<sql<<endl;
//
//	time.Start();//��ʱ��ʼ
//	xmlSrv.insert(temp.data(),r_cols);
//	time.Stop();//��ʱ����
//}


/**************************************************************************************/
//
///*�������param ����������**/
//void createNewTable(string tbname,vector<string> cols){
//	time.Start();//��ʱ��ʼ
//	xmlSrv.createXml(tbname.data(),cols);  
//	time.Stop();//��ʱֹͣ
//}
//
///**�鿴��ͷ*/
//void showTableHeads(string tbname){
//	time.Start();//��ʱ��ʼ
//	vector<string> heads = xmlSrv.findTableHead(tbname.data());  
//	time.Stop();//��ʱֹͣ
//	cout<<" \t";
//	for(int i=0;i<heads.size();i++){
//		string h = heads[i];
//		if(heads[i].size()>=8){
//			h= h.substr(0,7);
//		}
//		cout<<h<<"\t";				
//		cout<<"|"<<"\t";
//	}
//	cout<<endl;
//	
//}
//
///**��ȡ���������û��ı������**/
//vector<string> getLocalTables(){
//	time.Start();//��ʱ��ʼ
//	/*��Ž��*/
//	vector<string> result;
//	vector<string> tbs = xmlSrv.findAllTables();
//	time.Stop();//��ʱֹͣ
//	if(!tbs.empty()){
//		cout<<"Found "<<tbs.size()<<" tables!"<<endl;
//		for(int i=0;i<tbs.size();i++){
//			string tb = par.stringSpilt(tbs[i],".xml");
//			result.push_back(tb);
//			cout<<i<<":"<<tb<<endl;
//		}
//	}
//	return result;
//}
//
//
//
//
//
//
///*��ѯ��������*/
//void findTableRecorder(const char* cXmlName1,const char* clounm,const char* value){
//	time.Start();//��ʱ��ʼ
//	/*��ѯ���е�����*/
//	vector<vector<string>> datas = xmlSrv.findByPropertise(cXmlName1,clounm,value);
//	time.Stop();//��ʱֹͣ
//	vector<string> head = xmlSrv.findTableHead(cXmlName1);
//	cout<<" \t";
//	for(int i=0;i<head.size();i++){
//		cout<<head[i]<<"\t";				
//		cout<<"|"<<"\t";
//	}
//	cout<<endl;
//	for(int i=0;i<datas.size();i++){
//		cout<<i<<":\t";
//		for(int j=0;j<datas[i].size();j++){
//			cout<<datas[i][j]<<"\t";				
//			cout<<"|"<<"\t";
//		}
//		cout<<endl;
//	}
//	
//}
//
///**������**/
//void outputTable(vector<vector<string>> datas){
//	if(!datas.empty()){
//		cout<<" \t";
//		for(int i=0;i<datas[0].size();i++){
//			string h = datas[0][i];
//			if(datas[0][i].size()>=8){
//				h= h.substr(0,7);
//			}
//			cout<<h<<"\t";				
//			cout<<"|"<<"\t";
//		}
//		cout<<endl;
//		for(int i=1;i<datas.size();i++){
//			cout<<i<<":\t";
//			for(int j=0;j<datas[i].size();j++){
//				cout<<datas[i][j]<<"\t";				
//				cout<<"|"<<"\t";
//			}
//			cout<<endl;
//		}
//	}
//}
//
////���Եѿ�����
//void testX(){
//	vector<string> cs;
//	cs.push_back("tb_1.age");
//	cs.push_back("tb_1.name");
//	
//	time.Start();//��ʱ��ʼ
//	/*��ѯ���е�����*/
//	vector<vector<string>> datas = xmlSrv.findClounmsIn(xmlSrv.getXResult("tb_1",xmlSrv.getXResult("tb_3",xmlSrv.getXResult("tb_1","tb_2"))),cs);
//	time.Stop();//��ʱֹͣ
//
//	outputTable(datas);
//}
///**������SQL**/
//void createSQL(){
//	string sql = "create table ";
//	string table;
//	string temp;
//	vector<string> col;//�������Ϣ
//	cout<<"������Ҫ������������(-1�鿴�Ѵ��ڵı��)��\n";
//	cout<<"isql> ";
//	cin>>table;
//	while(table == "-1"){
//		getLocalTables();
//		cout<<"isql> ";cin>>table;
//	}
//	sql += table;
//	sql +="(";
//	for(int i=0;i<200;i++)
//	{
//		temp.clear();
//		cout<<"�������"<<i+1<<"�б������(������-1����)��\n";
//		cout<<"isql> ";cin>>temp;
//		if(temp=="-1"){
//			if(col.empty()){
//				cout<<"����������1�У�\n";
//				cout<<"isql> ";cin>>temp;
//			}else
//				break;
//		}
//		if(col.size()>0){
//			sql+=",";
//		}
//		sql += temp;
//		col.push_back(temp);
//	}
//	sql += ");";
//	cout<<"sql> ";
//	cout<<sql<<endl;
//	createNewTable(table,col);
//}
///**��ѯsql***/
//void findSQL(){
//	string sql = " from ";
//	string sql0 = "";
//	string temp;
//	string clounm1;
//	string clounm2;
//	int cho = -1;
//	vector<string> r_col;//�������Ϣ
//	vector<string> f_tab;//�����Դ
//	vector<vector<string>> datas;//���
//	
//	cout<<"������Ҫ��ѯ�ı��(-1����;-2�鿴�������б��)��\n";
//	while(true){
//		temp.clear();
//		cout<<"isql> ";cin>>temp;
//		if(temp=="-1")
//			break;
//		if(temp=="-2"){
//			getLocalTables();
//			continue;
//		}
//		if(f_tab.size()>0){
//			sql += ",";
//			
//		}
//		sql += temp;
//		f_tab.push_back(temp);
//	}
//	
//	if(f_tab.size()==1){
//		cout<<"�������ж�����(0:��������;-1�鿴��ͷ;-2��ʾ�鿴ȫ��;����\n";
//		
//		cout<<"������������";
//		cout<<"isql> ";
//		cin>>clounm1;
//		while(clounm1 == "-1"){
//			showTableHeads(f_tab[0]);
//			cout<<"isql> ";cin>>clounm1;
//		}
//		if(clounm1 == "-2"){
//			findTableRecorder(f_tab[0].data(),"","");
//			return;
//		}else if(clounm1 == "0"){
//			clounm1 = "";
//			clounm2 = "";
//		}
//		else{
//			cout<<"������ֵ��";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"������Ҫ���ص�����(��:tb.id;-1����)��\n";
//		
//		while(true){
//			temp.clear();
//			cout<<"isql> ";cin>>temp;
//			if(temp=="-1")
//			{
//				if(r_col.empty()){
//					sql = "*" + sql;
//				}
//				break;
//			}
//			if(r_col.size()>0){
//				sql0 +=",";
//			}
//			sql0 += temp;
//
//			r_col.push_back(temp);
//		}
//	
//		
//		time.Start();
//		datas = xmlSrv.findClounmsIn(xmlSrv.findColEqStr(xmlSrv.findAllCols(f_tab[0].data()),clounm1,clounm2),r_col);
//		time.Stop();
//	}
//	else if(f_tab.size()>=2){
//		cout<<"�������ж�����(��ʽ��tb1.id = tb2.id�� mid)��\n";
//		cout<<"�������ֶ�1(-1�鿴��ͷ;-2��ʾ��������ѯ)��\n";
//		cout<<"isql> ";cin>>clounm1;
//		while(clounm1 == "-1"){
//			for(int i=0;i<f_tab.size();i++){
//				cout<<"��"<<f_tab[i]<<":";
//				showTableHeads(f_tab[i]);
//			}
//			cout<<"isql> ";cin>>clounm1;
//		}
//		if(clounm1 == "-2"){
//			clounm1 = "";
//			clounm2 = "";
//		}else{
//			cout<<"������ֵ���ֶ�2��\n";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"������Ҫ���ص�����(��:tb.id;-1����)��\n";
//		while(true){
//			temp.clear();
//			cout<<"isql> ";cin>>temp;
//			if(temp=="-1")
//			{	
//				if(r_col.empty()){
//					sql = "*" + sql;
//				}
//				break;
//			}
//			if(r_col.size()>0){
//				sql0 += ",";
//			}
//			sql0 += temp;
//			r_col.push_back(temp);
//		}
//		
//		time.Start();
//		datas = xmlSrv.getXResult(f_tab[0].data(),f_tab[1].data());
//		for(int i=2;i<f_tab.size();i++){
//			datas = xmlSrv.getXResult(f_tab[i].data(),datas);
//		}
//		datas = xmlSrv.findClounmsIn(xmlSrv.findT1EqT2(datas,clounm1,clounm2),r_col);
//		time.Stop();
//	}
//	sql = "select "+ sql0 + sql + ";";
//	cout<<"sql> ";cout<<sql<<endl;
//	outputTable(datas);
//	
//}
//
///**����SQL**/
//void insertSQL(){
//	string sql = "insert into table ";
//	string temp;
//	string clounm1;
//	vector<string> r_col;//�������Ϣ
//	vector<vector<string>> r_cols;//�������Ϣ
//	cout<<"������������(0�鿴���б��;-1ȡ��)\n";//�������ݿ��д�ŵı������
//	cout<<"isql> ";cin>>temp;
//	if(temp=="-1")
//		return;
//	if(temp=="0"){
//		getLocalTables();
//		cout<<"������������";
//		cout<<"isql> ";cin>>temp;
//	}
//	sql += temp;
//	vector<string> heads = xmlSrv.findTableHead(temp.data());
//	if(heads.empty()){
//		cout<<"insert interrupt:No that table exists!"<<endl;
//		return;
//	}
//	sql += " value( ";
//	cout<<"�밴���������ݣ�\n";
//	for(int i=0;i<heads.size();i++){
//		cout<<"��"<<heads[i]<<":";
//		cout<<"isql> ";cin >> clounm1;
//		if(r_col.size()>0){
//			sql += ",";
//		}
//		sql += clounm1;
//		r_col.push_back(clounm1);
//	}
//	r_cols.push_back(r_col);
//	sql += ");";
//	cout<<"sql> ";
//	cout<<sql<<endl;
//
//	time.Start();//��ʱ��ʼ
//	xmlSrv.insert(temp.data(),r_cols);
//	time.Stop();//��ʱ����
//}