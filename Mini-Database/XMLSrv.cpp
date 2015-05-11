#include"XMLSrv.h"
#include<iostream>
#include<fstream>
using namespace std;
#define MAX_NUM 256  
  
  
/************************************************************************/  
/*描述：遍历一个元素 
  时间：2012-9-18 
  参数说明：pNode节点，flag 节点嵌套层数 
/************************************************************************/  
string XMLSrv::dumpNode(TiXmlNode * pNode,int flag)  
{     
    string msg = "";  
      
    if(pNode == NULL)  
    {  
        return "";  
    }  
  
    TiXmlText * pText = NULL;  
    TiXmlNode * pChildNode = NULL;  
    int t = pNode->Type();  
      
    switch(t)  
    {  
        //节点类型是text节点  
        case TiXmlText::TINYXML_TEXT:  
        {   pText = pNode->ToText();  
            string text = pText->Value();  
            if(!text.empty())  
            {  
                msg = msg + "="+ text;  
            }  
            break;  
        }  
  
        //节点类型是Element  
        case TiXmlText::TINYXML_ELEMENT:  
        {  
            msg = msg + "\r\n";  
            int num = flag;  
              
            while(num >= 1)  
            {  
                msg = msg + "  ";  
                num--;  
            }  
              
            msg = msg + pNode->Value();  
              
            //输出属性  
            TiXmlElement * pElement = pNode->ToElement();  
              
            TiXmlAttribute * pAttr = pElement->FirstAttribute();  
            TiXmlAttribute * pNextAttr =NULL;  
            string tmpAttrMsg = "[";  
              
            //if(pAttr != NULL && !(string(pAttr->Name())).compare("name") && !(string(pAttr->Value())).compare("IDH_CFG_USB"))  
            if(pAttr != NULL )  
            {     
                string tmpAttrVal = "";  
                string tmpAttrName = "";          
                  
                do  
                {                             
                    tmpAttrVal = pAttr->Value();  
                    tmpAttrName = pAttr->Name();  
                    tmpAttrMsg += tmpAttrName + "=" +tmpAttrVal + ",";  //各个属性之间用逗号分隔  
                }while(pAttr = pAttr->Next());  
                  
                /* 去掉最后的',' */  
                tmpAttrMsg = tmpAttrMsg.erase(tmpAttrMsg.find_last_of(","));  
                //同上 tmpAttrMsg = tmpAttrMsg.substr(0,tmpAttrMsg.find_last_of(","));  
                  
            }  
            tmpAttrMsg += "]";  
            msg += tmpAttrMsg;  
  
            break;  
        }  
  
        case TiXmlText::TINYXML_DOCUMENT:  
        case TiXmlText::TINYXML_COMMENT:  
        case TiXmlText::TINYXML_UNKNOWN:  
        case TiXmlText::TINYXML_DECLARATION:  
        case TiXmlText::TINYXML_TYPECOUNT:  
        {  
            ;//Nothing to do  
        }  
    }  
      
    //循环访问它的每一个元素  
    for(pChildNode=pNode->FirstChild();pChildNode!=0;pChildNode = pChildNode->NextSibling())  
    {  
          
        msg = msg + dumpNode(pChildNode,flag+1);  
  
    }  
  
    return msg;  
}  
/************************************************************************/  
/*  遍历一个xml文档                                                                   */  
/************************************************************************/  
void XMLSrv::readXml(const char * ccXmlName)  
{  
	string file = ccXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	ccXmlName = file.c_str();

    //创建一个XML的文档对象。  
    TiXmlDocument *myDocument = new TiXmlDocument(ccXmlName);  
    myDocument->LoadFile(TIXML_ENCODING_UTF8);  
  
    //获得xml的头，即声明部分  
    TiXmlDeclaration* decl = myDocument->FirstChild()->ToDeclaration();  
    cout << "xml文件的版本是:" << decl->Version() << endl;  
    cout << "xml的编码格式是：" << decl->Encoding() << endl;  
  
    //获得根元素  
    TiXmlElement *RootElement = myDocument->RootElement();  
  
    //输出根元素名称  
    cout << RootElement->Value() << endl;  
  
    TiXmlNode* pNode  = NULL;  
    string msg = "";  
  
    for(pNode=RootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
    {  
        msg += dumpNode(pNode,0);  
    }  
  
    cout << msg << endl;  
}  
/************************************************************************/  
/*  创建一个xml文档                                                                    */  
/************************************************************************/  
void XMLSrv::createXml(const char * ccXmlName,vector<string> clounms)  
{  
	  //保存到文件  
	string file =  ccXmlName;
	file += ".xml";
	//检查表格是否存在
	ifstream ifs(file.c_str());
    if(ifs) {
       cout<<"create error:The table you try to create is exist already!"<<endl;
		return;
    }
	
	if(clounms.size()==0){
		cout<<"create error:Do you forget give clounm name?"<<endl;
		return;
	}
	//创建一个XML的文档对象。  
	TiXmlDocument *myDocument = new TiXmlDocument();  

    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","gb2312","yes");  
    myDocument->LinkEndChild(decl);  
  
    //创建一个根元素并连接。  
    TiXmlElement *RootElement = new TiXmlElement("Clounms");  
    myDocument->LinkEndChild(RootElement);  
      
	 //创建一个Clounm元素并连接。  
     TiXmlElement *PersonElement = new TiXmlElement("TH");  
     RootElement->LinkEndChild(PersonElement);  
	 PersonElement->SetAttribute("num",clounms.size());

	//创建表头
	for(int i=0;i < clounms.size();i++)
    {  
        //创建一个Person元素并连接。  
		TiXmlElement *ClounmElement = new TiXmlElement((clounms[i]).data());  
        PersonElement->LinkEndChild(ClounmElement);  
    }  
  
  
	myDocument->SaveFile(file.c_str());  
	 cout<<"create table "<<ccXmlName<<" success!"<<endl;
}  
/************************************************************************/  
/* 
  根据父节点循环遍历查找子节点 
  参数说明 
    noteName 节点名 
    noteAttrName 属性名 
    noteAttrValue 属性值 
/************************************************************************/  
TiXmlNode * XMLSrv::selectChildNode(TiXmlNode * pNode,string nodeName,string nodeAttrName,string nodeAttrValue)  
{  
    if(pNode == NULL)  
    {  
        return NULL;  
    }  
    TiXmlNode * pSelectedNode = NULL;  
    TiXmlNode * pChildNode = NULL;  
    int t = pNode->Type();  
    switch (t)  
    {  
    case TiXmlText::TINYXML_DOCUMENT:  
    case TiXmlText::TINYXML_DECLARATION:  
    case TiXmlText::TINYXML_TEXT:  
    case TiXmlText::TINYXML_UNKNOWN:  
    case TiXmlText::TINYXML_COMMENT:  
        break;  
    case TiXmlText::TINYXML_ELEMENT:  
    if(pNode->Value() == nodeName)  
    {  
            //cout << pNode->Value() << endl;  
            if(!nodeAttrName.empty() && !nodeAttrValue.empty())  
            {  
                TiXmlElement * pElement = pNode->ToElement();  
  
                TiXmlAttribute * pAttr = pElement->FirstAttribute();  
                TiXmlAttribute * pNextAttr =NULL;  
                if(pAttr != NULL)  
                {     
                    do  
                    {                             
                        if(pAttr->Name()==nodeAttrName&&pAttr->Value()== nodeAttrValue)  
                        {  
                            //cout << pAttr->Value() << endl;  
                            return pNode;  
                        }  
                    }while(pAttr = pAttr->Next());  
                }  
            }  
            else  
            {  
                return pNode;  
            }  
              
        }  
        else  
        {  
            //循环访问它的每一个元素  
            for(pChildNode=pNode->FirstChild();  
                pChildNode!=0;  
                pChildNode = pChildNode->NextSibling())  
            {  
                pSelectedNode = selectChildNode(  
                                    pChildNode,  
                                    nodeName,  
                                    nodeAttrName,  
                                    nodeAttrValue);  
                if(pSelectedNode)  
                {  
                    return pSelectedNode;  
                }  
            }  
        }  
  
    default:break;  
    }  
    return NULL;  
}  
/************************************************************************/  
/* 查询出唯一节点                                                         */  
/* 参数说明： 
   string nodeName    节点名 
   string nodeAttrName 节点的属性 
   string nodeAttrValue 节点属性的值 
/************************************************************************/  
TiXmlNode * XMLSrv::SelectSingleNode(const char * cXmlName,string nodeName,string nodeAttrName,string nodeAttrValue)  
{  
    //加载一个XML的文档对象。  
  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    if(!xmlDoc->LoadFile())  //是tinyXml会自动处理文档的BOM  
    {  
        return NULL;  
    }  
  
  
    if(xmlDoc == NULL)  
    {  
        return NULL;  
    }  
  
    //获得根元素  
    TiXmlElement *RootElement = xmlDoc->RootElement();  
    if(RootElement == NULL)  
    {  
        cout << "解析错误,无法获取根元素" << endl;  
        return NULL;  
    }  
  
    TiXmlNode * pNode  = NULL;  
    TiXmlNode * pSelectNode = NULL;  
    string msg = "";  
  
    for(pNode=RootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
    {  
          
        pSelectNode = selectChildNode(pNode,nodeName,nodeAttrName,nodeAttrValue);  
        if(pSelectNode)  
        {  
            break;  
        }  
    }  
      
    if(pSelectNode)  
    {  
        cout << "解析成功" << endl;  
        cout << "[节点名]=" << pSelectNode->Value() << endl;  
        return pSelectNode;  
    }  
    else  
    {  
        cout << "解析错误，无法获取节点" << endl;  
        return NULL;  
    }  
  
}  
TiXmlNode * XMLSrv::SelectSingleNodeByRootEle(TiXmlElement* RootElement,string nodeName,string nodeAttrName,string nodeAttrValue)  
{  
    //加载一个XML的文档对象。  
      
//  TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
//  if(!xmlDoc->LoadFile())  //是tinyXml会自动处理文档的BOM  
//  {  
//      return NULL;  
//  }  
//    
//    
//  if(xmlDoc == NULL)  
//  {  
//      return NULL;  
//  }  
      
    //获得根元素  
    //TiXmlElement *RootElement = xmlDoc->RootElement();  
    if(RootElement == NULL)  
    {  
        cout << "解析错误,无法获取根元素" << endl;  
        return NULL;  
    }  
      
    TiXmlNode * pNode  = NULL;  
    TiXmlNode * pSelectNode = NULL;  
    string msg = "";  
      
    for(pNode=RootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
    {  
          
        pSelectNode = selectChildNode(pNode,nodeName,nodeAttrName,nodeAttrValue);  
        if(pSelectNode)  
        {  
            break;  
        }  
    }  
      
    if(pSelectNode)  
    {  
        //cout << "解析成功" << endl;  
        //cout << pSelectNode->Value() << endl;  
        return pSelectNode;  
    }  
    else  
    {  
        cout << "解析错误，无法获取节点" << endl;  
        return NULL;  
    }  
      
}  
/************************************************************************/  
/* 普通插入一行记录。                                                               */  
/************************************************************************/  
bool XMLSrv::insert(const char * ccXmlName,vector<vector<string>> arr){  
	string file = ccXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	ccXmlName = file.c_str();

      
   TiXmlDocument *myDocument = new TiXmlDocument(ccXmlName);  
    myDocument->LoadFile();  
      
    if(myDocument == NULL)  
    {  
		cout<<"insert error:no table named "<<ccXmlName<<" exsit!"<<endl;
        return false;  
	}
    ////获得xml的头，即声明部分  
    //TiXmlDeclaration* decl = myDocument->FirstChild()->ToDeclaration();  
    //if(decl != NULL)  
    //{  
    //    cout << "xml文件的版本是:" << decl->Version() << endl;  
    //    cout << "xml的编码格式是：" << decl->Encoding() << endl;  
    //}  
      
  
    //获得根元素  
    TiXmlElement *RootElement = myDocument->RootElement();  
	//创建一个TB元素并连接。  
    TiXmlElement *ClounmElement = new TiXmlElement("TB");  
    RootElement->LinkEndChild(ClounmElement);  

	if( RootElement != NULL)  
    {  
		//如果输入包含表头
		if(arr.size()==2)
		{
			//判断输入的列名是否正确
			 vector<string> ths = findTableHead(ccXmlName);
			 if(arr[0]!=ths){
				 cout<<"insert error:there is exist that clounm name is wrong!"<<endl;
				return false;
			 }
			 if(arr[1].size()!=ths.size()){
				 cout<<"insert error:clounms size is not correct!"<<endl;
				return false;
			 }
			
			 //插入数据
			 for(int i=0;i<arr[1].size();i++){
				 try{TiXmlElement *TBElement = new TiXmlElement(arr[0][i].data());    
				ClounmElement->LinkEndChild(TBElement);    
		          
				TiXmlText *textElement = new TiXmlText(arr[1][i].data());  
				TBElement->LinkEndChild(textElement);  }
				 catch(exception &e){
					cout<<"xml error!"<<endl;
					return false;
				 }
			 }
			myDocument->SaveFile(ccXmlName);  
		}
		//只插入列（无表头）
		else if(arr.size()==1){
			//判断输入的列名是否正确
			 vector<string> ths = findTableHead(ccXmlName);
			 if(ths.size()!=arr[0].size()){
				 cout<<"insert error:clounms size is not correct!"<<endl;
				return false;
			 }
			 //插入数据
			 for(int i=0;i<ths.size();i++){
				 try{
					TiXmlElement *TBElement = new TiXmlElement(ths[i].data());    
					ClounmElement->LinkEndChild(TBElement);    
			          
					TiXmlText *textElement = new TiXmlText(arr[0][i].data());  
					TBElement->LinkEndChild(textElement);  
				 }
				 catch(exception &e){
					cout<<"xml error!"<<endl;
					return false;
				 }
			 }
			
			myDocument->SaveFile(ccXmlName);  
			cout<<"insert data success!"<<endl;
		
		}else{
			return false;
		}
        return true;  
    }  
     return false;  
}  
/************************************************************************/  
/* 获取一个节点的属性                                                  */  
/************************************************************************/  
string XMLSrv::getAttribute(TiXmlNode * pNode)  
{  
    if(pNode == NULL) return "";  
    //输出属性  
    string msg = "";  
    TiXmlElement * pElement = pNode->ToElement();  
  
    TiXmlAttribute * pAttr = pElement->FirstAttribute();  
    TiXmlAttribute * pNextAttr =NULL;  
    string tmpAttrMsg = "";  
  
    if(pAttr != NULL)  
    {     
        string tmpAttrVal = "";  
        string tmpAttrName = "";          
  
        do  
        {                             
            tmpAttrVal = pAttr->Value();  
            tmpAttrName = pAttr->Name();  
            tmpAttrMsg += "[" + tmpAttrName + "]=" + tmpAttrVal+"\n";   //各个属性之间用逗号分隔  
        }while(pAttr = pAttr->Next());  
          
        //tmpAttrMsg = tmpAttrMsg.erase(tmpAttrMsg.find_last_of(","));  
    }  
  
    //tmpAttrMsg += "]";  
    msg += tmpAttrMsg;  
  
    return msg;  
}  
/************************************************************************/  
/*  在指定位置插入一个元素                                             */  
/************************************************************************/  
bool XMLSrv::insertAElement(const char * cXmlName, TiXmlElement * pElement)  
{  
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();

    //加载一个XML的文档对象。  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    xmlDoc->LoadFile();  
  
    if(xmlDoc == NULL)  
    {  
        return false;  
    }  
  
    //获得xml的头，即声明部分  
    TiXmlDeclaration* decl = xmlDoc->FirstChild()->ToDeclaration();  
    if(decl != NULL)  
    {  
        cout << "xml文件的版本是:" << decl->Version()  << endl;  
        cout << "xml的编码格式是:" << decl->Encoding() << endl;  
    }  
    //获得根元素  
    TiXmlElement *RootElement = xmlDoc->RootElement();  
    if(RootElement != NULL)  
    {  
        TiXmlNode * pNode = SelectSingleNode(cXmlName,"name","length","100");  
        if(pNode == NULL)  
        {  
            return false;  
        }  
          
        //创建一个Person元素并连接。  
        TiXmlElement *pNewElement = new TiXmlElement("Person");  
        if(pNewElement == NULL)  
        {  
            return false;  
        }  
        pNewElement->SetAttribute("Id","1");  
        TiXmlText *textElement = new TiXmlText("gbnn");  
        if(textElement == NULL)  
        {  
            return false;  
        }  
        pNewElement->LinkEndChild(textElement);  
        TiXmlNode * pRet = pNode->InsertBeforeChild(pNode->LastChild(),*pNewElement);  
        //TiXmlNode * pRet = pNode->LinkEndChild(pNewElement);  
        xmlDoc->Print();  
        bool b = xmlDoc->SaveFile();  
        if(b)  
        {  
            cout << "添加成功" << endl;  
            return b;  
        }  
        else  
        {  
            cout << "添加失败" << endl;  
            return false;  
        }  
    }  
    else  
    {  
        return false;  
    }  
}     
  
//const char * cXmlName,string strNodeName,string strNodeAttrName,string strNdeAttrValue,string strPath  
/*! 
*  \Function: 修改一个唯一节点中第二、三属性的值为一子符串 
* 
*  \param cXmlName       xml文件名 
*  \param strNodeName    指定的节点名。 
*  \param strNodeAttrName 指定的节点名所在节点中第一属性名。 
*  \param strNdeAttrValue 指定的节点名所在节点中第一属性值。 
*  \param strPath         字符串。为当前路径名的上一级目录的字符串 
*  \return  是否成功。true为成功，false表示失败。 
*/  
bool XMLSrv::ModifySingleNode(const char * cXmlName,string strNodeName,string strNodeAttrName,string strNdeAttrValue,string strPath)  
{  

    if (strNodeName.empty() || strNodeAttrName.empty() || strNdeAttrValue.empty() ||strPath.empty())  
    {  
        return false;  
    }  
  
    // 定义一个TiXmlDocument类指针  
    TiXmlDocument *pDoc = new TiXmlDocument();  
    if (NULL==pDoc)  
    {  
        return false;  
    }  
      
    pDoc->LoadFile(cXmlName);  
  
    TiXmlElement* pRootElement = pDoc->RootElement();  
  
    TiXmlNode * pNode = SelectSingleNodeByRootEle(pRootElement,strNodeName,strNodeAttrName,strNdeAttrValue);  
      
    if (NULL == pNode)  
    {  
        return false;  
    }  
  
    //输出属性  
    TiXmlElement * pElement = pNode->ToElement();  
  
    TiXmlAttribute * pAttr = pElement->FirstAttribute();  
    TiXmlAttribute * pNextAttr =NULL;  
      
    if(pAttr != NULL)  
    {     
        string tmpAttrVal = "";  
        string tmpAttrName = "";          
          
        do  
        {                             
            tmpAttrVal = pAttr->Value();  
            tmpAttrName = pAttr->Name();  
              
            //节点中第一个属性对跳过  
            if (tmpAttrName == strNodeAttrName && tmpAttrVal == strNdeAttrValue)  
            {  
                continue;  
            }  
  
            //修改第二和第三个属性对  
            if ("href" == tmpAttrName)  
            {  
                pAttr->SetValue(strPath.c_str());  
            }  
  
            if ("test" == tmpAttrName)  
            {  
                pAttr->SetValue(strPath.c_str());  
            }  
  
        }while(pAttr = pAttr->Next());  
    }  
      
    pDoc->SaveFile("a.xml");  
      
    return true;  
}  
  
void XMLSrv::ShowSingleNode(const char * cXmlName,string strNodeName,string strNodeAttrName,string strNdeAttrValue)  
{  
    TiXmlNode * pNode = SelectSingleNode(cXmlName,strNodeName,strNodeAttrName,strNdeAttrValue);  
      
    if (NULL == pNode)  
    {  
        return;  
    }  
  
    string strTem = getAttribute(pNode);  
  
    cout << strTem.c_str() << endl;  
}  
/*
*   获取当前路径
*/
string XMLSrv::PathOpt()  
{  
    char cStr[MAX_NUM];  
    GetCurrentDirectory(MAX_NUM,LPWSTR(cStr));  
  
    string str = cStr;  
      
    //取当前路径的上一目录所在路径  
    size_t pos = str.find_last_of("\\");  
    str.erase(str.begin()+pos,str.end());  
  
    return str;  
}   
/***
**
**	查找头部列名
** \param cXmlName       xml文件名 
**/
vector<string> XMLSrv::findTableHead(const char * cXmlName){
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();

	vector<string> heads;
	 //加载一个XML的文档对象。  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  

	if(xmlDoc->LoadFile()&&xmlDoc != NULL){  
		 //获得根元素  
		TiXmlElement *RootElement = xmlDoc->RootElement(); 
		TiXmlNode* pNode  = RootElement->FirstChildElement();  
		TiXmlNode * pChildNode = NULL; 
		for(pChildNode=pNode->FirstChild();pChildNode!=0;pChildNode = pChildNode->NextSibling())  
		{  
			heads.push_back(pChildNode->Value());  
		}  
	}else{
		cout<<"find error:no table!"<<endl;
	}
	return heads;
}
/************************************************************************/  
/* 根据元素结点的值获取整个父节点   
* param clounm 列名
* param value 列的值
* 返回所有行记录
/************************************************************************/  
vector<vector<string>> XMLSrv::findByPropertise(const char* cXmlName,const char* clounm,const char* value){
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();
	
	vector<vector<string>> strs;

	//加载一个XML的文档对象。  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    if(xmlDoc->LoadFile() && xmlDoc!= NULL)  //是tinyXml会自动处理文档的BOM  
    {  
	  
		//获得根元素  
		TiXmlElement *RootElement = xmlDoc->RootElement();  
		if(RootElement == NULL)  
		{  
			cout << "error root!" << endl;    
		}  
	  
		TiXmlNode * pNode  = NULL; 
		TiXmlNode * pCNode  = NULL;
		TiXmlNode * pSelectNode = NULL;  
		string msg = "";  
	  
		for(pNode=RootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
		{  
			//跳过表头
			if(strcmp(pNode->Value(),"TH")==0){
				continue;
			}
	          
			for(pCNode=pNode->FirstChildElement();pCNode;pCNode=pCNode->NextSiblingElement())  
			{  
				if(strcmp(clounm,"")==0||strcmp(pCNode->Value(),clounm)==0)
				{
					if(strcmp(value,"")==0||strcmp(pCNode->FirstChild()->ToText()->Value(),value)==0)
					{
						//查找成功
						//cout<<"select sucess!"<<endl;
						TiXmlNode * pCCNode  = NULL;
						vector<string> find;
						for(pCCNode=pNode->FirstChildElement();pCCNode;pCCNode=pCCNode->NextSiblingElement())
						{
							find.push_back(pCCNode->FirstChild()->ToText()->Value());
						}
						strs.push_back(find);
						break;
					}
				}
			}
		}  
	}
	return strs;
}



/**
** 查找xml文件下所有xml文件
***/
vector<string> XMLSrv::findAllTables(){
	vector<string> tbs;
	 _finddata_t file; 
    long lf; 
//修改这里选择路径和要查找的文件类型
    if((lf = _findfirst("*.xml",&file))==-1l)//_findfirst返回的是long型;long __cdecl _findfirst(const char *, struct _finddata_t *) 
		cout<<"find error:no xml file found!\n"; 
    else 
    { 
        do{ 
			tbs.push_back(file.name);
        } while( _findnext( lf, &file ) == 0 );//int __cdecl _findnext(long, struct _finddata_t *);如果找到下个文件的名字成功的话就返回0,否则返回-1 
   
    } 
    _findclose(lf); 
	return tbs;
}


/***********************************
**	笛卡尔积1
**	表1和表2
** 返回值第一行为表头
*************************************/
vector<vector<string>> XMLSrv::getXResult(const char * ccXmlName1,const char * ccXmlName2){
	vector<vector<string>> result;

	string tb1 = ccXmlName1;//暂存表名
	string tb2 = ccXmlName2;

	if(tb1 == tb2){
		tb1 += "1";
		tb2 += "2";
	}

	string file1 = ccXmlName1;
	if(file1.find(".xml") == -1)
		file1 += ".xml";
	ccXmlName1 = file1.c_str();
	
	string file2 = ccXmlName2;
	if(file2.find(".xml") == -1)
		file2 += ".xml";
	ccXmlName2 = file2.c_str();

	//获取笛卡尔积表头
	vector<string> r_str;
	vector<string> head1 = findTableHead(ccXmlName1);//表1的表头
	for(int i=0;i<head1.size();i++){
		r_str.push_back(tb1+"."+head1[i]);
	}
	vector<string> head2 = findTableHead(ccXmlName2);//表2的表头
	for(int i=0;i<head2.size();i++){
		r_str.push_back(tb2+"."+head2[i]);
	}
	result.push_back(r_str);

	//获取笛卡尔积表内算法
	vector<vector<string>> t1 = findByPropertise(ccXmlName1,"","");
	vector<vector<string>> t2 = findByPropertise(ccXmlName2,"","");
	for(int i=0;i<t1.size();i++){
		for(int m=0;m<t2.size();m++){
			r_str.clear();
			for(int j=0;j<t1[i].size();j++){
				r_str.push_back(t1[i][j]);
			}
			for(int n=0;n<t2[m].size();n++){
				r_str.push_back(t2[m][n]);
			}
			result.push_back(r_str);
		}
	}
	
	return result;

}

/***********************************
**	笛卡尔积2
**	表1和积
** 返回值第一行为表头
*************************************/
vector<vector<string>> XMLSrv::getXResult(const char * ccXmlName1,vector<vector<string>> ccXmlName2){
	vector<vector<string>> result;
	if(ccXmlName2.empty()){
		return result;
	}

	string tb = ccXmlName1;//暂存表名
	string file = ccXmlName1;
	if(file.find(".xml") == -1)
		file += ".xml";
	ccXmlName1 = file.c_str();
	
	//获取笛卡尔积表头
	vector<string> r_str;
	vector<string> head1 = findTableHead(ccXmlName1);//表1的表头
	
	for(int i=0;i<ccXmlName2[0].size();i++){
		r_str.push_back(ccXmlName2[0][i]);
	}
	for(int i=0;i<head1.size();i++){
		r_str.push_back(tb+"."+head1[i]);
	}
	result.push_back(r_str);


	//获取笛卡尔积表内算法
	vector<vector<string>> t1 = findByPropertise(ccXmlName1,"","");
	for(int i=0;i<t1.size();i++){
		for(int m=1;m<ccXmlName2.size();m++){
			r_str.clear();
			for(int n=0;n<ccXmlName2[m].size();n++){
				r_str.push_back(ccXmlName2[m][n]);
			}
			for(int j=0;j<t1[i].size();j++){
				r_str.push_back(t1[i][j]);
			}
			
			result.push_back(r_str);
		}
	}

	return result;
}

/***********************************
**	笛卡尔积3
**	积和积
** 返回值第一行为表头
*************************************/
vector<vector<string>> XMLSrv::getXResult(vector<vector<string>> ccXmlName1,vector<vector<string>> ccXmlName2){
	vector<vector<string>> result;
	
	//获取笛卡尔积表头
	vector<string> r_str;
	for(int i=0;i<ccXmlName1[0].size();i++){
		r_str.push_back(ccXmlName1[0][i]);
	}
	for(int i=0;i<ccXmlName2[0].size();i++){
		r_str.push_back(ccXmlName2[0][i]);
	}
	result.push_back(r_str);

	//获取笛卡尔积表内算法

	for(int i=1;i<ccXmlName1.size();i++){
		for(int m=1;m<ccXmlName2.size();m++){
			r_str.clear();
			for(int j=0;j<ccXmlName1[i].size();j++){
				r_str.push_back(ccXmlName1[i][j]);
			}
			for(int n=0;n<ccXmlName2[m].size();n++){
				r_str.push_back(ccXmlName2[m][n]);
			}
			result.push_back(r_str);
		}
	}
	return result;
}

/***********************************
**	查找条件
**	返回符合条件的行集
**  @param clounm1/clounm2至少一个为列名
**  列1和列2相等
*************************************/
vector<vector<string>> XMLSrv::findT1EqT2(vector<vector<string>> strs,string clounm1,string clounm2){
	vector<vector<string>> result;
	
	//获取表头号
	int cid1 = -1;
	int cid2 = -1;
	if(clounm1 == "" || clounm2 == ""){
		return strs;
	}
	if(!strs.empty()){
		result.push_back(strs[0]);
		for(int i = 0;i<strs[0].size();i++){
			if(strs[0][i]==clounm1){
				cid1 = i;
			}
			else if(strs[0][i]==clounm2){
				cid2 = i;
			}
		}
		
		if(cid1!=-1&&cid2!=-1){
			for(int i=1;i<strs.size();i++){
				if(strs[i][cid1] == strs[i][cid2]){
					result.push_back(strs[i]);
				}
			}
		}else if(cid1!=-1&&cid2==-1){
			for(int i=1;i<strs.size();i++){
				if(strs[i][cid1] == clounm2){
					result.push_back(strs[i]);
				}
			}
		}else if(cid1==-1&&cid2!=-1){
			for(int i=1;i<strs.size();i++){
				if(strs[i][cid2] == clounm1){
					result.push_back(strs[i]);
				}
			}
		}else{
			cout<<"find error:no the special clounms in the table!"<<endl;
		}
	}
	return result;
}



/***********************************
**	查找条件
**	返回符合条件的行集
**  列1和列2相等
*************************************/
vector<vector<string>> XMLSrv::findColEqStr(vector<vector<string>> strs,string clounm1,string value){
	vector<vector<string>> result;
	
	//获取表头号
	int cid1 = -1;
	if(value == ""){
		return strs;
	}
	if(!strs.empty()){
		result.push_back(strs[0]);
		for(int i = 0;i<strs[0].size();i++){
			if(strs[0][i]==clounm1){
				cid1 = i;
			}
		}
		
		if(cid1!=-1){//如果存在这个列
			for(int i=1;i<strs.size();i++){
				if(strs[i][cid1] == value){
					result.push_back(strs[i]);
				}
			}
		}else{
			cout<<"find error:no the special clounm in the table!"<<endl;;
		}
	}
	return result;
}


/***********************************
**	选择操作
**	返回指定列的行集
	cs 为空时返回全部
*************************************/
vector<vector<string>> XMLSrv::findClounmsIn(vector<vector<string>> strs,vector<string> cs){
	//算法可优化
	vector<int> ids;
	if(!strs.empty()&&!cs.empty()){
		for(int i = 0;i<strs[0].size();i++){
			for(int j=0;j<cs.size();j++){
				if(strs[0][i]==cs[j]){
					ids.push_back(i);
					//删除结点
					vector<string>::iterator it = cs.begin()+j;
					cs.erase(it);
					break;
				}
			}
		}
	}else if(strs.empty()){
		cout<<"find error:no any table!"<<endl;
		return strs;
	}
	else{
		return strs;
	}
	vector<vector<string>> result;
	vector<string> temp;
	if(!cs.empty()){
		cout<<"clounm error:some clounms' name are absent!"<<endl;
	}
	if(ids.empty()){
		return result;
	}
	for(int i=0;i<strs.size();i++){
		temp.clear();
		for(int j=0;j<ids.size();j++){
			temp.push_back(strs[i][ids[j]]);
		}
		result.push_back(temp);
	}
	return result;
}

/***
**返回所有记录，包含头
***/
vector<vector<string>> XMLSrv::findAllCols(const char* cXmlName){
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();
	
	vector<vector<string>> strs;

	//加载一个XML的文档对象。  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    if(xmlDoc->LoadFile()&&xmlDoc!= NULL)  //是tinyXml会自动处理文档的BOM  
    {  
	  
		//获得根元素  
		TiXmlElement *RootElement = xmlDoc->RootElement();  
		if(RootElement == NULL)  
		{  
			cout << "error root!" << endl;    
		}  
	 
		TiXmlNode * pNode  = NULL; 
		TiXmlNode * pCCNode  = NULL;
		vector<string> find;
	  
		for(pNode=RootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
		{  
			find.clear();
			//跳过表头
			if(strcmp(pNode->Value(),"TH")==0){
				for(pCCNode=pNode->FirstChildElement();pCCNode;pCCNode=pCCNode->NextSiblingElement())
				{
					find.push_back(pCCNode->Value());
				}
				strs.push_back(find);
				continue;
			}		
			for(pCCNode=pNode->FirstChildElement();pCCNode;pCCNode=pCCNode->NextSiblingElement())
			{
				find.push_back(pCCNode->FirstChild()->ToText()->Value());
			}
			strs.push_back(find);
		}  
	}
	return strs;

}