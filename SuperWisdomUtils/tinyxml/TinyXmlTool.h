
#ifndef TINYXMLTOOL_H
#define TINYXMLTOOL_H

#include"../tinyxml/tinystr.h"
#include"../tinyxml/tinyxml.h"
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream >
using namespace std;

class CTinyXmlTool
{
public:

	CTinyXmlTool();
	~CTinyXmlTool();
public:
	static void ReadXml(string strHtml) ;

	/*!
	*  /brief ��ȡxml�ļ���������
	*  /param XmlFile xml�ļ�ȫ·����
	*  /param strVersion  Version����ֵ
	*  /param strStandalone Standalone����ֵ
	*  /param strEncoding Encoding����ֵ
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ�
	*/
	static bool GetXmlDeclare(std::string XmlFile,std::string &strVersion,std::string &strStandalone,std::string &strEncoding);

};

























#endif // ANIMATEDTEXTEDIT_H
