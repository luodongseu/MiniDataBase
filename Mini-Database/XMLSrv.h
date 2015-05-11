#pragma once
#include<vector>
#include"tinyxml.h"
#include"tinystr.h"
#include<atlstr.h>
#include<string>
#include<io.h> 
using namespace std;

class XMLSrv{
public:
	void createXml(const char * ccXmlName ,vector<string> clounms);
	void readXml(const char * ccXmlName);
	string dumpNode(TiXmlNode * pNode,int flag);
	void ShowSingleNode(const char * cXmlName,string strNodeName,string strNodeAttrName,string strNdeAttrValue);
	bool ModifySingleNode(const char * cXmlName,string strNodeName,string strNodeAttrName,string strNdeAttrValue,string strPath);
	bool insertAElement(const char * cXmlName, TiXmlElement * pElement);
	string getAttribute(TiXmlNode * pNode);
	bool insert(const char * ccXmlName,vector<vector<string>> arr);
	TiXmlNode * SelectSingleNodeByRootEle(TiXmlElement* RootElement,string nodeName,string nodeAttrName,string nodeAttrValue);
	TiXmlNode * SelectSingleNode(const char * cXmlName,string nodeName,string nodeAttrName,string nodeAttrValue);
	TiXmlNode * selectChildNode(TiXmlNode * pNode,string nodeName,string nodeAttrName,string nodeAttrValue);
	vector<vector<string>> findByPropertise(const char* cXmlName,const char* clounm,const char* value);
	vector<string> findTableHead(const char * cXmlName);
	string PathOpt();  
	vector<string> findAllTables();
	vector<vector<string>> getXResult(const char * ccXmlName1,const char * ccXmlName2);
	vector<vector<string>> getXResult(const char * ccXmlName1,vector<vector<string>> ccXmlName2);
	vector<vector<string>> getXResult(vector<vector<string>> ccXmlName1,vector<vector<string>> ccXmlName2);
	vector<vector<string>> findT1EqT2(vector<vector<string>> strs,string clounm1,string clounm2);
	vector<vector<string>> findColEqStr(vector<vector<string>> strs,string clounm1,string value);
	vector<vector<string>> findClounmsIn(vector<vector<string>> strs,vector<string> cs);
	vector<vector<string>> findAllCols(const char* cXmlName);
};