#include <iostream>  
#include"tinyxml2.h"  
using namespace std;  
using namespace tinyxml2;  
/*
����һ�¼���������
FirstChildElement(const char* value=0):��ȡ��һ��ֵΪvalue���ӽڵ㣬valueĬ��ֵΪ�գ��򷵻ص�һ���ӽڵ㡣
RootElement():��ȡ���ڵ㣬�൱��FirstChildElement�Ŀղ����汾��
const XMLAttribute* FirstAttribute() const����ȡ��һ������ֵ��
XMLHandle NextSiblingElement( const char* _value=0 ) �������һ���ڵ㡣
*/

//�ݹ���ȡÿ���ڵ�
void GetEleNameAndValue(XMLElement* pEle)
{
	XMLElement* pEleTemp=NULL;
	pEleTemp=pEle;
	if(pEleTemp)
	{
		XMLElement* childEleTemp=pEleTemp->FirstChildElement();
		while(childEleTemp)
		{
			cout<<"<"<< childEleTemp->Value()<<">"<<endl;
			GetEleNameAndValue(childEleTemp);
			cout<<"</"<< childEleTemp->Value()<<">"<<endl;
			childEleTemp=childEleTemp->NextSiblingElement();
			
		}
		if(childEleTemp==NULL)
		{
			const char* pText=pEleTemp->GetText();
			if(pText)
			{
				std::cout  << pEleTemp->Value() <<":"<<pEleTemp->GetText()<<std::endl;
			}
			const char* pValue=pEleTemp->Value();
			if(pValue)
			{
				const XMLAttribute *IDAttribute = pEleTemp->FirstAttribute(); 
				while(IDAttribute)
				{
					const char* pIDTest=IDAttribute->Name();
					if (pIDTest)
					{
						std::cout <<"  "<< IDAttribute->Name() <<":"<< IDAttribute->Value();

					}		
					IDAttribute=IDAttribute->Next();
				}
			}

		}

	}

}
void example1()  
{  
	XMLDocument doc;  
	XMLError  xmlerror=doc.LoadFile("E:\\1.xml");  
	if (xmlerror == XML_SUCCESS)
	{
		XMLElement *rootElement=doc.RootElement();  
		GetEleNameAndValue(rootElement);
	}

}  

int main1()  
{  
	example1();  
	int i;
	cin>> i;
	return 0;  
}  