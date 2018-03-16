#include "TinyXmlTool.h"


CTinyXmlTool::CTinyXmlTool()
{

}


CTinyXmlTool::~CTinyXmlTool()
{


}


void CTinyXmlTool::ReadXml(string strHtml) 
{
	const char* demoStart =
		"<?xml version=\"1.0\"  standalone='no' >\n"
		"<!-- Our to do list data -->"
		"<ToDo>\n"
		"<!-- Do I need a secure PDA? -->\n"
		"<Item priority=\"1\" distance='close'> Go to the <bold>Toy store!</bold></Item>"
		"<Item priority=\"2\" distance='none'> Do bills   </Item>"
		"<Item priority=\"2\" distance='far &amp; back'> Look for Evil Dinosaurs! </Item>"
		"</ToDo>";
	std::string strVersion,strStandalone,strEncoding;

	GetXmlDeclare(strHtml.c_str(),strVersion,strStandalone,strEncoding);


	TiXmlDocument doc;    
	//doc.Parse(demoStart);
	if (doc.Parse(strHtml.c_str()) ==nullptr)
	{
		doc.Print();
	} else 
	{
		std::cout << "can not parse xml conf/school.xml" ;
		return;
	}
	TiXmlElement* rootElement = doc.RootElement();  //SchoolԪ��  
	TiXmlElement* classElement = rootElement->FirstChildElement();  // ClassԪ��
	TiXmlElement* studentElement = classElement->FirstChildElement();  //Students  
	for (; studentElement != NULL; studentElement = studentElement->NextSiblingElement() ) 
	{
		TiXmlAttribute* attributeOfStudent = studentElement->FirstAttribute();  //���student��name����  
		for (;attributeOfStudent != NULL; attributeOfStudent = attributeOfStudent->Next() )
		{
			std::cout   << attributeOfStudent->Name() << " : " << attributeOfStudent->Value() ;       
		}                                 

		TiXmlElement* studentContactElement = studentElement->FirstChildElement();//���student�ĵ�һ����ϵ��ʽ 
		for (; studentContactElement != NULL; studentContactElement = studentContactElement->NextSiblingElement() )
		{
			string contactType = studentContactElement->Value();
			string contactValue = studentContactElement->GetText();
			std::cout  <<contactType.c_str() << " : " <<contactValue.c_str()  ;            
		}   

	} 
}

/*!
*  /brief ��ȡxml�ļ���������
*  /param XmlFile xml�ļ�ȫ·����
*  /param strVersion  Version����ֵ
*  /param strStandalone Standalone����ֵ
*  /param strEncoding Encoding����ֵ
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ�
*/
bool CTinyXmlTool::GetXmlDeclare(std::string XmlFile,std::string &strVersion,std::string &strStandalone,std::string &strEncoding)
{
	// ����һ��TiXmlDocument��ָ��
	TiXmlDocument *pDoc = new TiXmlDocument();
	if (NULL==pDoc)
	{
		return false;
	}
	//pDoc->LoadFile(XmlFile.c_str());
	pDoc->Parse(XmlFile.c_str());

	TiXmlNode* pXmlFirst = pDoc->FirstChild();   
	if (NULL != pXmlFirst)  
	{  
		TiXmlDeclaration* pXmlDec = pXmlFirst->ToDeclaration();  
		if (NULL != pXmlDec)  
		{  
			strVersion = pXmlDec->Version();
			strStandalone = pXmlDec->Standalone();
			strEncoding = pXmlDec->Encoding();
		}
	}
	return true;
}
