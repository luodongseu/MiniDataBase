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

	/*普通服务*/
	XMLSrv xmlSrv;
		
	/*解析字符串*/
	miniParaser par;

	/*时间服务*/
	miniTimer timea;

	/*DAO操作*/
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
///*创建表格param 表名，列名**/
//void createNewTable(string tbname,vector<string> cols){
//	time.Start();//计时开始
//	xmlSrv.createXml(tbname.data(),cols);  
//	time.Stop();//计时停止
//}
//
///**查看表头*/
//void showTableHeads(string tbname){
//	time.Start();//计时开始
//	vector<string> heads = xmlSrv.findTableHead(tbname.data());  
//	time.Stop();//计时停止
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
///**获取本地所有用户的表格名称**/
//vector<string> getLocalTables(){
//	time.Start();//计时开始
//	/*存放结果*/
//	vector<string> result;
//	vector<string> tbs = xmlSrv.findAllTables();
//	time.Stop();//计时停止
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
///*查询表格的数据*/
//void findTableRecorder(const char* cXmlName1,const char* clounm,const char* value){
//	time.Start();//计时开始
//	/*查询表中的数据*/
//	vector<vector<string>> datas = xmlSrv.findByPropertise(cXmlName1,clounm,value);
//	time.Stop();//计时停止
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
///**输出表格**/
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
////测试笛卡尔积
//void testX(){
//	vector<string> cs;
//	cs.push_back("tb_1.age");
//	cs.push_back("tb_1.name");
//	
//	time.Start();//计时开始
//	/*查询表中的数据*/
//	vector<vector<string>> datas = xmlSrv.findClounmsIn(xmlSrv.getXResult("tb_1",xmlSrv.getXResult("tb_3",xmlSrv.getXResult("tb_1","tb_2"))),cs);
//	time.Stop();//计时停止
//
//	outputTable(datas);
//}
///**创建表SQL**/
//void createSQL(){
//	string sql = "create table ";
//	string table;
//	string temp;
//	vector<string> col;//表格列信息
//	cout<<"请输入要创建表格的名称(-1查看已存在的表格)：\n";
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
//		cout<<"请输入第"<<i+1<<"列表格列名(请输入-1结束)：\n";
//		cout<<"isql> ";cin>>temp;
//		if(temp=="-1"){
//			if(col.empty()){
//				cout<<"请输入至少1列：\n";
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
///**查询sql***/
//void findSQL(){
//	string sql = " from ";
//	string sql0 = "";
//	string temp;
//	string clounm1;
//	string clounm2;
//	int cho = -1;
//	vector<string> r_col;//表格列信息
//	vector<string> f_tab;//表格来源
//	vector<vector<string>> datas;//结果
//	
//	cout<<"请输入要查询的表格(-1结束;-2查看本地所有表格)：\n";
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
//		cout<<"请输入判断条件(0:跳过条件;-1查看表头;-2表示查看全部;）：\n";
//		
//		cout<<"请输入列名：";
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
//			cout<<"请输入值：";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"请输入要返回的列名(如:tb.id;-1结束)：\n";
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
//		cout<<"请输入判断条件(格式：tb1.id = tb2.id或 mid)：\n";
//		cout<<"请输入字段1(-1查看表头;-2表示无条件查询)：\n";
//		cout<<"isql> ";cin>>clounm1;
//		while(clounm1 == "-1"){
//			for(int i=0;i<f_tab.size();i++){
//				cout<<"表"<<f_tab[i]<<":";
//				showTableHeads(f_tab[i]);
//			}
//			cout<<"isql> ";cin>>clounm1;
//		}
//		if(clounm1 == "-2"){
//			clounm1 = "";
//			clounm2 = "";
//		}else{
//			cout<<"请输入值或字段2：\n";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"请输入要返回的列名(如:tb.id;-1结束)：\n";
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
///**插入SQL**/
//void insertSQL(){
//	string sql = "insert into table ";
//	string temp;
//	string clounm1;
//	vector<string> r_col;//表格列信息
//	vector<vector<string>> r_cols;//表格列信息
//	cout<<"请输入表格名：(0查看所有表格;-1取消)\n";//调用数据库中存放的表格名称
//	cout<<"isql> ";cin>>temp;
//	if(temp=="-1")
//		return;
//	if(temp=="0"){
//		getLocalTables();
//		cout<<"请输入表格名：";
//		cout<<"isql> ";cin>>temp;
//	}
//	sql += temp;
//	vector<string> heads = xmlSrv.findTableHead(temp.data());
//	if(heads.empty()){
//		cout<<"insert interrupt:No that table exists!"<<endl;
//		return;
//	}
//	sql += " value( ";
//	cout<<"请按列输入数据：\n";
//	for(int i=0;i<heads.size();i++){
//		cout<<"列"<<heads[i]<<":";
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
//	time.Start();//计时开始
//	xmlSrv.insert(temp.data(),r_cols);
//	time.Stop();//计时结束
//}


/**************************************************************************************/
//
///*创建表格param 表名，列名**/
//void createNewTable(string tbname,vector<string> cols){
//	time.Start();//计时开始
//	xmlSrv.createXml(tbname.data(),cols);  
//	time.Stop();//计时停止
//}
//
///**查看表头*/
//void showTableHeads(string tbname){
//	time.Start();//计时开始
//	vector<string> heads = xmlSrv.findTableHead(tbname.data());  
//	time.Stop();//计时停止
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
///**获取本地所有用户的表格名称**/
//vector<string> getLocalTables(){
//	time.Start();//计时开始
//	/*存放结果*/
//	vector<string> result;
//	vector<string> tbs = xmlSrv.findAllTables();
//	time.Stop();//计时停止
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
///*查询表格的数据*/
//void findTableRecorder(const char* cXmlName1,const char* clounm,const char* value){
//	time.Start();//计时开始
//	/*查询表中的数据*/
//	vector<vector<string>> datas = xmlSrv.findByPropertise(cXmlName1,clounm,value);
//	time.Stop();//计时停止
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
///**输出表格**/
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
////测试笛卡尔积
//void testX(){
//	vector<string> cs;
//	cs.push_back("tb_1.age");
//	cs.push_back("tb_1.name");
//	
//	time.Start();//计时开始
//	/*查询表中的数据*/
//	vector<vector<string>> datas = xmlSrv.findClounmsIn(xmlSrv.getXResult("tb_1",xmlSrv.getXResult("tb_3",xmlSrv.getXResult("tb_1","tb_2"))),cs);
//	time.Stop();//计时停止
//
//	outputTable(datas);
//}
///**创建表SQL**/
//void createSQL(){
//	string sql = "create table ";
//	string table;
//	string temp;
//	vector<string> col;//表格列信息
//	cout<<"请输入要创建表格的名称(-1查看已存在的表格)：\n";
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
//		cout<<"请输入第"<<i+1<<"列表格列名(请输入-1结束)：\n";
//		cout<<"isql> ";cin>>temp;
//		if(temp=="-1"){
//			if(col.empty()){
//				cout<<"请输入至少1列：\n";
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
///**查询sql***/
//void findSQL(){
//	string sql = " from ";
//	string sql0 = "";
//	string temp;
//	string clounm1;
//	string clounm2;
//	int cho = -1;
//	vector<string> r_col;//表格列信息
//	vector<string> f_tab;//表格来源
//	vector<vector<string>> datas;//结果
//	
//	cout<<"请输入要查询的表格(-1结束;-2查看本地所有表格)：\n";
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
//		cout<<"请输入判断条件(0:跳过条件;-1查看表头;-2表示查看全部;）：\n";
//		
//		cout<<"请输入列名：";
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
//			cout<<"请输入值：";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"请输入要返回的列名(如:tb.id;-1结束)：\n";
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
//		cout<<"请输入判断条件(格式：tb1.id = tb2.id或 mid)：\n";
//		cout<<"请输入字段1(-1查看表头;-2表示无条件查询)：\n";
//		cout<<"isql> ";cin>>clounm1;
//		while(clounm1 == "-1"){
//			for(int i=0;i<f_tab.size();i++){
//				cout<<"表"<<f_tab[i]<<":";
//				showTableHeads(f_tab[i]);
//			}
//			cout<<"isql> ";cin>>clounm1;
//		}
//		if(clounm1 == "-2"){
//			clounm1 = "";
//			clounm2 = "";
//		}else{
//			cout<<"请输入值或字段2：\n";
//			cout<<"isql> ";cin>>clounm2;
//			sql += " where ";
//			sql += clounm1;
//			sql += " = ";
//			sql += clounm2;
//		}
//		
//		cout<<"请输入要返回的列名(如:tb.id;-1结束)：\n";
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
///**插入SQL**/
//void insertSQL(){
//	string sql = "insert into table ";
//	string temp;
//	string clounm1;
//	vector<string> r_col;//表格列信息
//	vector<vector<string>> r_cols;//表格列信息
//	cout<<"请输入表格名：(0查看所有表格;-1取消)\n";//调用数据库中存放的表格名称
//	cout<<"isql> ";cin>>temp;
//	if(temp=="-1")
//		return;
//	if(temp=="0"){
//		getLocalTables();
//		cout<<"请输入表格名：";
//		cout<<"isql> ";cin>>temp;
//	}
//	sql += temp;
//	vector<string> heads = xmlSrv.findTableHead(temp.data());
//	if(heads.empty()){
//		cout<<"insert interrupt:No that table exists!"<<endl;
//		return;
//	}
//	sql += " value( ";
//	cout<<"请按列输入数据：\n";
//	for(int i=0;i<heads.size();i++){
//		cout<<"列"<<heads[i]<<":";
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
//	time.Start();//计时开始
//	xmlSrv.insert(temp.data(),r_cols);
//	time.Stop();//计时结束
//}