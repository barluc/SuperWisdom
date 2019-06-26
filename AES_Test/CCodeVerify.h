
#pragma once 
#include <vector>
#include <regex>
#include <string>
class CCodeVerify
{
public:
	CCodeVerify();
	~CCodeVerify();
public:

	//��ȡ������
	std::string  GetSerialNumber();

	//����������
	std::string  CreateActiveNumber(std::string strSerialNumber, std::string otherInfo);
	
	//����������
	bool  VerifyActiveNumber(std::string strAcitveNumber, std::string& strDate,std::string& otherInfo);

	//��ǰϵͳʱ��
	std::string DatetimeToString();

	std::vector<std::string> Split11(const std::string& strInput, const std::string& delim);
private:

	std::string m_strKey;


};
