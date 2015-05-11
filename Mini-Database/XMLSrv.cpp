#include"XMLSrv.h"
#include<iostream>
#include<fstream>
using namespace std;
#define MAX_NUM 256  
  
  
/************************************************************************/  
/*����������һ��Ԫ�� 
  ʱ�䣺2012-9-18 
  ����˵����pNode�ڵ㣬flag �ڵ�Ƕ�ײ��� 
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
        //�ڵ�������text�ڵ�  
        case TiXmlText::TINYXML_TEXT:  
        {   pText = pNode->ToText();  
            string text = pText->Value();  
            if(!text.empty())  
            {  
                msg = msg + "="+ text;  
            }  
            break;  
        }  
  
        //�ڵ�������Element  
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
              
            //�������  
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
                    tmpAttrMsg += tmpAttrName + "=" +tmpAttrVal + ",";  //��������֮���ö��ŷָ�  
                }while(pAttr = pAttr->Next());  
                  
                /* ȥ������',' */  
                tmpAttrMsg = tmpAttrMsg.erase(tmpAttrMsg.find_last_of(","));  
                //ͬ�� tmpAttrMsg = tmpAttrMsg.substr(0,tmpAttrMsg.find_last_of(","));  
                  
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
      
    //ѭ����������ÿһ��Ԫ��  
    for(pChildNode=pNode->FirstChild();pChildNode!=0;pChildNode = pChildNode->NextSibling())  
    {  
          
        msg = msg + dumpNode(pChildNode,flag+1);  
  
    }  
  
    return msg;  
}  
/************************************************************************/  
/*  ����һ��xml�ĵ�                                                                   */  
/************************************************************************/  
void XMLSrv::readXml(const char * ccXmlName)  
{  
	string file = ccXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	ccXmlName = file.c_str();

    //����һ��XML���ĵ�����  
    TiXmlDocument *myDocument = new TiXmlDocument(ccXmlName);  
    myDocument->LoadFile(TIXML_ENCODING_UTF8);  
  
    //���xml��ͷ������������  
    TiXmlDeclaration* decl = myDocument->FirstChild()->ToDeclaration();  
    cout << "xml�ļ��İ汾��:" << decl->Version() << endl;  
    cout << "xml�ı����ʽ�ǣ�" << decl->Encoding() << endl;  
  
    //��ø�Ԫ��  
    TiXmlElement *RootElement = myDocument->RootElement();  
  
    //�����Ԫ������  
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
/*  ����һ��xml�ĵ�                                                                    */  
/************************************************************************/  
void XMLSrv::createXml(const char * ccXmlName,vector<string> clounms)  
{  
	  //���浽�ļ�  
	string file =  ccXmlName;
	file += ".xml";
	//������Ƿ����
	ifstream ifs(file.c_str());
    if(ifs) {
       cout<<"create error:The table you try to create is exist already!"<<endl;
		return;
    }
	
	if(clounms.size()==0){
		cout<<"create error:Do you forget give clounm name?"<<endl;
		return;
	}
	//����һ��XML���ĵ�����  
	TiXmlDocument *myDocument = new TiXmlDocument();  

    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","gb2312","yes");  
    myDocument->LinkEndChild(decl);  
  
    //����һ����Ԫ�ز����ӡ�  
    TiXmlElement *RootElement = new TiXmlElement("Clounms");  
    myDocument->LinkEndChild(RootElement);  
      
	 //����һ��ClounmԪ�ز����ӡ�  
     TiXmlElement *PersonElement = new TiXmlElement("TH");  
     RootElement->LinkEndChild(PersonElement);  
	 PersonElement->SetAttribute("num",clounms.size());

	//������ͷ
	for(int i=0;i < clounms.size();i++)
    {  
        //����һ��PersonԪ�ز����ӡ�  
		TiXmlElement *ClounmElement = new TiXmlElement((clounms[i]).data());  
        PersonElement->LinkEndChild(ClounmElement);  
    }  
  
  
	myDocument->SaveFile(file.c_str());  
	 cout<<"create table "<<ccXmlName<<" success!"<<endl;
}  
/************************************************************************/  
/* 
  ���ݸ��ڵ�ѭ�����������ӽڵ� 
  ����˵�� 
    noteName �ڵ��� 
    noteAttrName ������ 
    noteAttrValue ����ֵ 
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
            //ѭ����������ÿһ��Ԫ��  
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
/* ��ѯ��Ψһ�ڵ�                                                         */  
/* ����˵���� 
   string nodeName    �ڵ��� 
   string nodeAttrName �ڵ������ 
   string nodeAttrValue �ڵ����Ե�ֵ 
/************************************************************************/  
TiXmlNode * XMLSrv::SelectSingleNode(const char * cXmlName,string nodeName,string nodeAttrName,string nodeAttrValue)  
{  
    //����һ��XML���ĵ�����  
  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    if(!xmlDoc->LoadFile())  //��tinyXml���Զ������ĵ���BOM  
    {  
        return NULL;  
    }  
  
  
    if(xmlDoc == NULL)  
    {  
        return NULL;  
    }  
  
    //��ø�Ԫ��  
    TiXmlElement *RootElement = xmlDoc->RootElement();  
    if(RootElement == NULL)  
    {  
        cout << "��������,�޷���ȡ��Ԫ��" << endl;  
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
        cout << "�����ɹ�" << endl;  
        cout << "[�ڵ���]=" << pSelectNode->Value() << endl;  
        return pSelectNode;  
    }  
    else  
    {  
        cout << "���������޷���ȡ�ڵ�" << endl;  
        return NULL;  
    }  
  
}  
TiXmlNode * XMLSrv::SelectSingleNodeByRootEle(TiXmlElement* RootElement,string nodeName,string nodeAttrName,string nodeAttrValue)  
{  
    //����һ��XML���ĵ�����  
      
//  TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
//  if(!xmlDoc->LoadFile())  //��tinyXml���Զ������ĵ���BOM  
//  {  
//      return NULL;  
//  }  
//    
//    
//  if(xmlDoc == NULL)  
//  {  
//      return NULL;  
//  }  
      
    //��ø�Ԫ��  
    //TiXmlElement *RootElement = xmlDoc->RootElement();  
    if(RootElement == NULL)  
    {  
        cout << "��������,�޷���ȡ��Ԫ��" << endl;  
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
        //cout << "�����ɹ�" << endl;  
        //cout << pSelectNode->Value() << endl;  
        return pSelectNode;  
    }  
    else  
    {  
        cout << "���������޷���ȡ�ڵ�" << endl;  
        return NULL;  
    }  
      
}  
/************************************************************************/  
/* ��ͨ����һ�м�¼��                                                               */  
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
    ////���xml��ͷ������������  
    //TiXmlDeclaration* decl = myDocument->FirstChild()->ToDeclaration();  
    //if(decl != NULL)  
    //{  
    //    cout << "xml�ļ��İ汾��:" << decl->Version() << endl;  
    //    cout << "xml�ı����ʽ�ǣ�" << decl->Encoding() << endl;  
    //}  
      
  
    //��ø�Ԫ��  
    TiXmlElement *RootElement = myDocument->RootElement();  
	//����һ��TBԪ�ز����ӡ�  
    TiXmlElement *ClounmElement = new TiXmlElement("TB");  
    RootElement->LinkEndChild(ClounmElement);  

	if( RootElement != NULL)  
    {  
		//������������ͷ
		if(arr.size()==2)
		{
			//�ж�����������Ƿ���ȷ
			 vector<string> ths = findTableHead(ccXmlName);
			 if(arr[0]!=ths){
				 cout<<"insert error:there is exist that clounm name is wrong!"<<endl;
				return false;
			 }
			 if(arr[1].size()!=ths.size()){
				 cout<<"insert error:clounms size is not correct!"<<endl;
				return false;
			 }
			
			 //��������
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
		//ֻ�����У��ޱ�ͷ��
		else if(arr.size()==1){
			//�ж�����������Ƿ���ȷ
			 vector<string> ths = findTableHead(ccXmlName);
			 if(ths.size()!=arr[0].size()){
				 cout<<"insert error:clounms size is not correct!"<<endl;
				return false;
			 }
			 //��������
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
/* ��ȡһ���ڵ������                                                  */  
/************************************************************************/  
string XMLSrv::getAttribute(TiXmlNode * pNode)  
{  
    if(pNode == NULL) return "";  
    //�������  
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
            tmpAttrMsg += "[" + tmpAttrName + "]=" + tmpAttrVal+"\n";   //��������֮���ö��ŷָ�  
        }while(pAttr = pAttr->Next());  
          
        //tmpAttrMsg = tmpAttrMsg.erase(tmpAttrMsg.find_last_of(","));  
    }  
  
    //tmpAttrMsg += "]";  
    msg += tmpAttrMsg;  
  
    return msg;  
}  
/************************************************************************/  
/*  ��ָ��λ�ò���һ��Ԫ��                                             */  
/************************************************************************/  
bool XMLSrv::insertAElement(const char * cXmlName, TiXmlElement * pElement)  
{  
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();

    //����һ��XML���ĵ�����  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    xmlDoc->LoadFile();  
  
    if(xmlDoc == NULL)  
    {  
        return false;  
    }  
  
    //���xml��ͷ������������  
    TiXmlDeclaration* decl = xmlDoc->FirstChild()->ToDeclaration();  
    if(decl != NULL)  
    {  
        cout << "xml�ļ��İ汾��:" << decl->Version()  << endl;  
        cout << "xml�ı����ʽ��:" << decl->Encoding() << endl;  
    }  
    //��ø�Ԫ��  
    TiXmlElement *RootElement = xmlDoc->RootElement();  
    if(RootElement != NULL)  
    {  
        TiXmlNode * pNode = SelectSingleNode(cXmlName,"name","length","100");  
        if(pNode == NULL)  
        {  
            return false;  
        }  
          
        //����һ��PersonԪ�ز����ӡ�  
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
            cout << "��ӳɹ�" << endl;  
            return b;  
        }  
        else  
        {  
            cout << "���ʧ��" << endl;  
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
*  \Function: �޸�һ��Ψһ�ڵ��еڶ��������Ե�ֵΪһ�ӷ��� 
* 
*  \param cXmlName       xml�ļ��� 
*  \param strNodeName    ָ���Ľڵ����� 
*  \param strNodeAttrName ָ���Ľڵ������ڽڵ��е�һ�������� 
*  \param strNdeAttrValue ָ���Ľڵ������ڽڵ��е�һ����ֵ�� 
*  \param strPath         �ַ�����Ϊ��ǰ·��������һ��Ŀ¼���ַ��� 
*  \return  �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/  
bool XMLSrv::ModifySingleNode(const char * cXmlName,string strNodeName,string strNodeAttrName,string strNdeAttrValue,string strPath)  
{  

    if (strNodeName.empty() || strNodeAttrName.empty() || strNdeAttrValue.empty() ||strPath.empty())  
    {  
        return false;  
    }  
  
    // ����һ��TiXmlDocument��ָ��  
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
  
    //�������  
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
              
            //�ڵ��е�һ�����Զ�����  
            if (tmpAttrName == strNodeAttrName && tmpAttrVal == strNdeAttrValue)  
            {  
                continue;  
            }  
  
            //�޸ĵڶ��͵��������Զ�  
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
*   ��ȡ��ǰ·��
*/
string XMLSrv::PathOpt()  
{  
    char cStr[MAX_NUM];  
    GetCurrentDirectory(MAX_NUM,LPWSTR(cStr));  
  
    string str = cStr;  
      
    //ȡ��ǰ·������һĿ¼����·��  
    size_t pos = str.find_last_of("\\");  
    str.erase(str.begin()+pos,str.end());  
  
    return str;  
}   
/***
**
**	����ͷ������
** \param cXmlName       xml�ļ��� 
**/
vector<string> XMLSrv::findTableHead(const char * cXmlName){
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();

	vector<string> heads;
	 //����һ��XML���ĵ�����  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  

	if(xmlDoc->LoadFile()&&xmlDoc != NULL){  
		 //��ø�Ԫ��  
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
/* ����Ԫ�ؽ���ֵ��ȡ�������ڵ�   
* param clounm ����
* param value �е�ֵ
* ���������м�¼
/************************************************************************/  
vector<vector<string>> XMLSrv::findByPropertise(const char* cXmlName,const char* clounm,const char* value){
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();
	
	vector<vector<string>> strs;

	//����һ��XML���ĵ�����  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    if(xmlDoc->LoadFile() && xmlDoc!= NULL)  //��tinyXml���Զ������ĵ���BOM  
    {  
	  
		//��ø�Ԫ��  
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
			//������ͷ
			if(strcmp(pNode->Value(),"TH")==0){
				continue;
			}
	          
			for(pCNode=pNode->FirstChildElement();pCNode;pCNode=pCNode->NextSiblingElement())  
			{  
				if(strcmp(clounm,"")==0||strcmp(pCNode->Value(),clounm)==0)
				{
					if(strcmp(value,"")==0||strcmp(pCNode->FirstChild()->ToText()->Value(),value)==0)
					{
						//���ҳɹ�
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
** ����xml�ļ�������xml�ļ�
***/
vector<string> XMLSrv::findAllTables(){
	vector<string> tbs;
	 _finddata_t file; 
    long lf; 
//�޸�����ѡ��·����Ҫ���ҵ��ļ�����
    if((lf = _findfirst("*.xml",&file))==-1l)//_findfirst���ص���long��;long __cdecl _findfirst(const char *, struct _finddata_t *) 
		cout<<"find error:no xml file found!\n"; 
    else 
    { 
        do{ 
			tbs.push_back(file.name);
        } while( _findnext( lf, &file ) == 0 );//int __cdecl _findnext(long, struct _finddata_t *);����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1 
   
    } 
    _findclose(lf); 
	return tbs;
}


/***********************************
**	�ѿ�����1
**	��1�ͱ�2
** ����ֵ��һ��Ϊ��ͷ
*************************************/
vector<vector<string>> XMLSrv::getXResult(const char * ccXmlName1,const char * ccXmlName2){
	vector<vector<string>> result;

	string tb1 = ccXmlName1;//�ݴ����
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

	//��ȡ�ѿ�������ͷ
	vector<string> r_str;
	vector<string> head1 = findTableHead(ccXmlName1);//��1�ı�ͷ
	for(int i=0;i<head1.size();i++){
		r_str.push_back(tb1+"."+head1[i]);
	}
	vector<string> head2 = findTableHead(ccXmlName2);//��2�ı�ͷ
	for(int i=0;i<head2.size();i++){
		r_str.push_back(tb2+"."+head2[i]);
	}
	result.push_back(r_str);

	//��ȡ�ѿ����������㷨
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
**	�ѿ�����2
**	��1�ͻ�
** ����ֵ��һ��Ϊ��ͷ
*************************************/
vector<vector<string>> XMLSrv::getXResult(const char * ccXmlName1,vector<vector<string>> ccXmlName2){
	vector<vector<string>> result;
	if(ccXmlName2.empty()){
		return result;
	}

	string tb = ccXmlName1;//�ݴ����
	string file = ccXmlName1;
	if(file.find(".xml") == -1)
		file += ".xml";
	ccXmlName1 = file.c_str();
	
	//��ȡ�ѿ�������ͷ
	vector<string> r_str;
	vector<string> head1 = findTableHead(ccXmlName1);//��1�ı�ͷ
	
	for(int i=0;i<ccXmlName2[0].size();i++){
		r_str.push_back(ccXmlName2[0][i]);
	}
	for(int i=0;i<head1.size();i++){
		r_str.push_back(tb+"."+head1[i]);
	}
	result.push_back(r_str);


	//��ȡ�ѿ����������㷨
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
**	�ѿ�����3
**	���ͻ�
** ����ֵ��һ��Ϊ��ͷ
*************************************/
vector<vector<string>> XMLSrv::getXResult(vector<vector<string>> ccXmlName1,vector<vector<string>> ccXmlName2){
	vector<vector<string>> result;
	
	//��ȡ�ѿ�������ͷ
	vector<string> r_str;
	for(int i=0;i<ccXmlName1[0].size();i++){
		r_str.push_back(ccXmlName1[0][i]);
	}
	for(int i=0;i<ccXmlName2[0].size();i++){
		r_str.push_back(ccXmlName2[0][i]);
	}
	result.push_back(r_str);

	//��ȡ�ѿ����������㷨

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
**	��������
**	���ط����������м�
**  @param clounm1/clounm2����һ��Ϊ����
**  ��1����2���
*************************************/
vector<vector<string>> XMLSrv::findT1EqT2(vector<vector<string>> strs,string clounm1,string clounm2){
	vector<vector<string>> result;
	
	//��ȡ��ͷ��
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
**	��������
**	���ط����������м�
**  ��1����2���
*************************************/
vector<vector<string>> XMLSrv::findColEqStr(vector<vector<string>> strs,string clounm1,string value){
	vector<vector<string>> result;
	
	//��ȡ��ͷ��
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
		
		if(cid1!=-1){//������������
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
**	ѡ�����
**	����ָ���е��м�
	cs Ϊ��ʱ����ȫ��
*************************************/
vector<vector<string>> XMLSrv::findClounmsIn(vector<vector<string>> strs,vector<string> cs){
	//�㷨���Ż�
	vector<int> ids;
	if(!strs.empty()&&!cs.empty()){
		for(int i = 0;i<strs[0].size();i++){
			for(int j=0;j<cs.size();j++){
				if(strs[0][i]==cs[j]){
					ids.push_back(i);
					//ɾ�����
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
**�������м�¼������ͷ
***/
vector<vector<string>> XMLSrv::findAllCols(const char* cXmlName){
	string file = cXmlName;
	if(file.find(".xml") == -1)
		file += ".xml";
	cXmlName = file.c_str();
	
	vector<vector<string>> strs;

	//����һ��XML���ĵ�����  
    TiXmlDocument *xmlDoc = new TiXmlDocument(cXmlName);  
    if(xmlDoc->LoadFile()&&xmlDoc!= NULL)  //��tinyXml���Զ������ĵ���BOM  
    {  
	  
		//��ø�Ԫ��  
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
			//������ͷ
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