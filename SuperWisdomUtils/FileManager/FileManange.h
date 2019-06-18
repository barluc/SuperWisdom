#ifndef __FILE_MANAGE_H__
#define __FILE_MANAGE_H__

#include <string>
#include <list>
#include <map>

#include <Shlwapi.h>


#include <tchar.h>
using namespace std;


#ifdef UNICODE
#define GetRootDirectory GetRootDirectoryW
#else
#define GetRootDirectory GetRootDirectoryA
#endif




namespace WisdomUtils
{
	enum emCopyFileRes
	{
		emContinue,
		emCancel,
		emStop,		
		emQuiet
	};

	typedef emCopyFileRes(*CopyFileCallbackFunction)(long lTotalFileSize, long lTotalBytesTransferred);

	class CFileManange
	{
	public:

		CFileManange(void);

		virtual ~CFileManange(void);

		/****************************/
		//��ȡ�ļ�����
		//pFilePath �ļ���ַ
		/****************************/
		static std::string LoadFile(const char* pFilePath);

		/****************************/
		//���ļ�д������
		//pFilePath �ļ���ַ  strData��Ҫд������� bAppend �Ƿ�׷�ӵ��ļ�ĩβ
		/****************************/
		static int WriteFile(const char* pFilePath, std::string strData, bool bAppend = true);

		/****************************/
		//ɾ���ļ�
		//pFilePath ���ļ���ַ
		/****************************/
		static int DelFile(const char* pFilePath);

		/****************************/
		//pSrcFilePath, // ��Ҫ������Դ�ļ��� 
		//pDescFilePath, // ��Ҫ������Ŀ���ļ��� 
		//bFailIfExists // ���Ŀ���Ѿ����ڣ���������True��������False������Ŀ�꣨false��
		/****************************/
		static int CpyFile(const char* pSrcFilePath, const char* pDescFilePath, bool bFailIfExist = true);
		
		/****************************/
		//pSrcFilePath, // ��Ҫ������Դ�ļ��� 
		//pDescFilePath, // ��Ҫ������Ŀ���ļ��� 
		//bFailIfExists // ���Ŀ���Ѿ����ڣ���������True��������False������Ŀ�꣨false��
		/****************************/
		static int CpyFileEx(const char* pSrcFilePath, const char* pDescFilePath, bool bFailIfExist, CopyFileCallbackFunction pFunc);

		static int CreateDir(const char* pDir);
	
		static int DeleteDir(const char* pDir);

		static std::list<std::pair<std::string, bool>> GetDirFiles(const char* pDir);
	
		/************************/
		//����������ļ��Ƿ����
		//pFile ���ļ���ַ
		/************************/
		static bool CheckFileExist(const char* pFile);		
		
		/************************/
		//��������ȡ��ǰ�ļ���С
		/************************/
		static long GetFileSize(const char* pFile);

		/************************/
		//��������ȡ��ǰ��������·��
		/************************/
		static void GetRootDirectoryA(LPSTR pszRootDir);

		/************************/
		//��������ȡ��ǰ��������·��
		/************************/
		static void GetRootDirectoryW(LPTSTR pszRootDir);

		/************************/
		//��������ȡ��ǰ��������·��
		/************************/
		string GetImageHead(wstring strPath);
	};
}

#endif