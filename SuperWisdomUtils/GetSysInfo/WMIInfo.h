#pragma once
/*************************************************************************************************

* Description  : [[CN]] ��ȡϵͳӲ��������Ϣ [[CN]]
*
**************************************************************************************************/

#include <windows.h>
#include <tchar.h>
#include <string>
#include <WbemIdl.h>  
#include <iostream>
#include <comdef.h>
#include <vector>
class CWmiInfo
{
public:
	CWmiInfo();
	~CWmiInfo();

public:
	HRESULT InitWmi();    //��ʼ��WMI  
	HRESULT ReleaseWmi(); //�ͷ� 

	/*��ȡһ�����Ա
	*@param [in ] ClassName   Example: "Win32_Processor"
	*@param [in ] ClassMember Example: "SerialNumber"
	*@param [out] chRetValue
	*@param return TRUE success; false fail

	Example:
	std::string strRetValue;
	GetSingleItemInfo(_T("Win32_Processor"),_T("Caption"),strRetValue);
	*/
	BOOL GetSingleItemInfo(std::string ClassName, std::string ClassMember, std::string &chRetValue, std::string strWhere = "");

	BOOL GetSingleItemInfo(std::string ClassName, std::string ClassMember, std::vector<std::string> &vecRetValue, std::string strWhere = "");




	VARIANT GetSingleItemInfo(std::string ClassName, std::string ClassMember);


	/*��ȡһ����Ķ����Ա
	*@param [in ] ClassName   Example: "Win32_Processor"
	*@param [in ] ClassMember Example: "SerialNumber"
	*@param [in ] n   ��Ա����
	*@param [out] chRetValue
	*@param return TRUE success; false fail

	Example:
	std::string strRetValue;std::string [] strClassMem = {_T("Caption"),_T("CurrentClockSpeed"),_T("DeviceID"),_T("Manufacturer"),_T("Manufacturer")};
	GetGroupItemInfo(_T("Win32_Processor"),strClassMem,5,strRetValue);
	*/
	BOOL GetGroupItemInfo(std::string ClassName, std::string ClassMember[], int n, std::string &chRetValue);

private:
	void VariantToString(const LPVARIANT, std::string &) const;//��Variant���͵ı���ת��Ϊstd::string

private:
	IEnumWbemClassObject* m_pEnumClsObj;
	IWbemClassObject* m_pWbemClsObj;
	IWbemServices* m_pWbemSvc;
	IWbemLocator* m_pWbemLoc;
};
