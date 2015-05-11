#include<iostream>  
#include<time.h> 
#include<vector>
#include<cstdlib> 
using namespace std;  
   
#define _CREATE 8    //����B+��
#define MAX_KEY 101   //B+���Ľ�,����Ϊ����3����  
  
typedef  __int64  KEYTYPE;  
typedef  unsigned long  FILEP;  
struct node
{
	KEYTYPE first;
	long second;
};
  
//B+���ڵ�����ݽṹ  
struct  BPlusNode
{  
      node key[MAX_KEY] ;      //�ؼ�����  
      FILEP Pointer[MAX_KEY+1] ;    //ָ����  
      int   nkey ;              //�ؼ�����  
      bool  isleaf ;                //�Ƿ�ΪҶ�ڵ� Ҷ�ڵ�:true ����Ϊfalse  
        
};  
    
//����ؼ��ֵ����ݽṹ  
struct  TRecord
{  
      KEYTYPE   key; //�ü�¼�Ĺؼ���
	  long name;
      FILEP Raddress;         //�ùؼ��ֶ�Ӧ��¼�ĵ�ַ  
        
};  
  
  
//�����ѯ��������ݽṹ  
 struct    SearchResult        
{  
      bool  exist;
	  long na;
      FILEP Baddress;   //��������ü�¼��B+���ڵ��ַ  
      FILEP Raddress;   //�ùؼ��ֵ���ָ��ļ�¼��ַ  
};  
  

  
class BPlusTreeApi  
{

      FILEP ROOT;       //�������ļ��ڵ�ƫ�Ƶ�ַ  
      FILE  *Bfile;     //B+���ļ���ָ��  
      FILE  *Rfile;     //��¼�ļ���ָ��  
        
public:  
        
      FILEP GetBPlusNode() const;  
      void  ReadBPlusNode(const FILEP ,BPlusNode& ) const;  
      void  WriteBPlusNode(const FILEP ,const BPlusNode& );  
        
      void  Build_BPlus_Tree();  
        
      bool  Insert_BPlus_Tree(TRecord& );  
      bool  insert_bplus_tree(FILEP ,TRecord& );  
        
      void  Split_BPlus_Node(BPlusNode& ,BPlusNode& ,const int );  
        
      void  Search_BPlus_Tree(TRecord& ,SearchResult&,int& ) const;  

	  bool  Search_Blank_BPlus_Tree(node&) const; 

      void  Delete_BPlus_Tree(TRecord& );  
      void  delete_BPlus_tree(FILEP ,TRecord& );  
        
      vector<node>  EnumLeafKey(); 
	  void  SearchRange(TRecord& record,__int64,SearchResult&);
	  vector<node>  Search_BPlus_TreeRange(TRecord & ,TRecord &,SearchResult &,int &)const;
	  FILEP GetRoot();
      BPlusTreeApi(string,int);  
      ~BPlusTreeApi();  
        
};  