// AES_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "AesHelper.h"
#include <tchar.h>
#include <windows.h>
#include <codecvt>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>
#include <windows.h>
using namespace std;
std::wstring str2wstr(const std::string& str)
{
	if (str.empty() == true)
	{
		return L"";
	}
	const char* utf8String = str.c_str();
	int unicodeLen = MultiByteToWideChar(936, 0, utf8String, -1, NULL, NULL);
	WCHAR*  unicodeString = new WCHAR[unicodeLen + 1];
	memset(unicodeString, 0x00, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(936, 0, utf8String, -1, unicodeString, unicodeLen);

	std::wstring dest = unicodeString;
	delete[] unicodeString;
	return dest;
}
std::string str2utf8(const std::string& str)
{
	if (str.empty() == true)
	{
		return "";
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(str2wstr(str));
}
string wstr2utf8(const wstring& wstr)
{
	if (wstr.empty() == true)
	{
		return "";
	}
	wstring_convert<codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstr);
}
std::string Utf8ToGbk(const std::string& strUtf8)//�����strUtf8��UTF-8����  
{
	if (strUtf8.empty() == true)
	{
		return "";
	}
	//UTF-8תunicode  
	int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
	wchar_t * strUnicode = new wchar_t[len];//len = 2  
	wmemset(strUnicode, 0, len);
	MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, strUnicode, len);

	//unicodeתgbk  
	len = WideCharToMultiByte(936, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	char *strGbk = new char[len];//len=3 ����Ϊ2������char*�����Զ�������\0  
	memset(strGbk, 0, len);
	WideCharToMultiByte(936, 0, strUnicode, -1, strGbk, len, NULL, NULL);

	std::string strTemp(strGbk);//��ʱ��strTemp��GBK����  
	delete[]strUnicode;
	delete[]strGbk;
	strUnicode = NULL;
	strGbk = NULL;
	return strTemp;
}

int _tmain(int argc, _TCHAR* argv[])
{


	CAesHelper tool;
	std::string strRet = tool.Encrypt("admin", "123");
	printf("Result is \n%s\n", strRet.c_str());
	std::string strSource = tool.Decrypt("rSZ7d6AsLWO3C6rIIMESXg==", "123");
	printf("Result is \n%s\n", strSource.c_str());
	
	std::string strSource1 = Utf8ToGbk(strSource);
	system("pause");
	return 0;
}

