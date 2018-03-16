#include "FileManange.h"
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <string>
#include <sys/stat.h>

using namespace WisdomUtils;
using namespace std;

CFileManange::CFileManange(void)
{
}


CFileManange::~CFileManange(void)
{
}

std::string WisdomUtils::CFileManange::LoadFile( const char* pFilePath )
{
	FILE* pFile = fopen(pFilePath, "rb");
	std::string strData;
	if (pFile)
	{
		int nReadSize = 1024;
		char szBuff[1024];
		int nLen = 0;
		while(1)
		{
			nLen = fread(szBuff, 1, 1024, pFile);
			if (nLen <= 0)
			{
				break;
			}
			strData += std::string(szBuff, nLen);
		}
	}
	fclose(pFile);
	return strData;
}

int WisdomUtils::CFileManange::WriteFile( const char* pFilePath, std::string strData, bool bAppend )
{
	FILE* pFile = fopen(pFilePath, bAppend ? "a" : "w");
	if (pFile)
	{
		fwrite(strData.data(), 1, strData.length(), pFile);
		fclose(pFile);
		return 0;
	}	
	return GetLastError();
}

int WisdomUtils::CFileManange::DelFile( const char* pFilePath )
{
	return remove(pFilePath);
}

int WisdomUtils::CFileManange::CpyFile( const char* pSrcFilePath, const char* pDescFilePath, bool bFailIfExist )
{
	return CopyFileA(pSrcFilePath, pDescFilePath, bFailIfExist);
}

DWORD CALLBACK CopyProgressRoutine(
	LARGE_INTEGER TotalFileSize,              // �ļ����ֽ���
	LARGE_INTEGER TotalBytesTransferred,      // �Ѹ��Ƶ��ֽ���
	LARGE_INTEGER StreamSize,                 // ��ǰ�����ֽ���
	LARGE_INTEGER StreamBytesTransferred,     // ��ǰ���ѿ������ֽ���
	DWORD dwStreamNumber,                     // ��ǰ�����
	DWORD dwCallbackReason,                   // �ص�������״̬; �����в���... 
	HANDLE hSourceFile,                       // Դ�ļ����
	HANDLE hDestinationFile,                  // Ŀ���ļ����
	LPVOID lpData                             // CopyFileEx ���ݵĲ���ָ��
	)
{
		//return PROGRESS_CANCEL;
		CopyFileCallbackFunction pFun = (CopyFileCallbackFunction)lpData;
		return pFun(TotalFileSize.QuadPart, TotalBytesTransferred.QuadPart);
};

int WisdomUtils::CFileManange::CpyFileEx( const char* pSrcFilePath, const char* pDescFilePath, bool bFailIfExist, CopyFileCallbackFunction pFunc )
{
	if (pFunc == nullptr)
	{
		return -1;
	}
	return CopyFileExA(pSrcFilePath, pDescFilePath, CopyProgressRoutine, pFunc, 0, 0);
}

int WisdomUtils::CFileManange::CreateDir( const char* pDir )
{
	int nLen = strlen(pDir);
	std::string strPath;

	for (int i = 0; i < nLen; i++){
		if (pDir[i] == '\\' || pDir[i] == '/'){
			strPath = std::string(pDir, &pDir[i] - pDir);			
			if (_access(strPath.c_str(), 0 != 0)){
				_mkdir(strPath.c_str());
			}
		}
	}
	if (pDir[nLen -1] != '\\' && pDir[nLen -1] != '/'){
		strPath = pDir;
		if (_access(strPath.c_str(), 0 )!= 0){
			_mkdir(strPath.c_str());
		}	
	}		
	return 0;
}

std::list<std::pair<std::string, bool>> WisdomUtils::CFileManange::GetDirFiles( const char* pDir )
{
	list<pair<string, bool>> lstFileInfo;
	WIN32_FIND_DATAA fd;
	HANDLE lFile;
	char szDir[1024] = "";
	int nLen = strlen(pDir);
	sprintf(szDir, "%s%s*.*", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\");

	lFile = FindFirstFileA(szDir, &fd);
	char szSub[1024];
	while(lFile != INVALID_HANDLE_VALUE)
	{
		if(FindNextFileA(lFile, &fd) == false){
			break;
		}
		if ((fd.dwFileAttributes & 0x10) == 0x10){						
			sprintf(szSub, "%s%s%s\\*.*", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\", fd.cFileName);
			if (string(fd.cFileName) != "." && string(fd.cFileName) != ".."){
				char szFileName[1024];
				sprintf(szFileName, "%s%s%s", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\", fd.cFileName);
				lstFileInfo.push_back(make_pair(szFileName, true));
				list<pair<string, bool>> listTemp = GetDirFiles(szFileName);
				for (list<pair<string, bool>>::iterator iter = listTemp.begin(); iter != listTemp.end(); iter++){
					lstFileInfo.push_back(*iter);
				}
			}			
		}else{
			char szFileName[1024];
			sprintf(szFileName, "%s%s%s", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\", fd.cFileName);
			lstFileInfo.push_back(make_pair(szFileName, false));
		}		
	}
	FindClose(lFile);
	return lstFileInfo;
}

bool WisdomUtils::CFileManange::CheckFileExist( const char* pFile )
{
	if (_access(pFile, 0) != 0){
		return false;
	}
	return true;
}

int WisdomUtils::CFileManange::DeleteDir( const char* pDir )
{
	char szPath[1024] = "";
	int nLen = strlen(pDir);
	sprintf(szPath, "%s%s*.*", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\");
	WIN32_FIND_DATAA fd;
	HANDLE lFile;
	lFile = FindFirstFileA(szPath, &fd);

	while(lFile != INVALID_HANDLE_VALUE){
		if (FindNextFileA(lFile, &fd) == false){
			break;
		}

		if (strcmp(fd.cFileName, "..") == 0 || strcmp(fd.cFileName, ".") == 0){
			continue;
		}

		if ((fd.dwFileAttributes & 0x10) == 0x10){
			char szSubDir[1024];
			sprintf(szSubDir, "%s%s%s", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\", fd.cFileName);
			DeleteDir(szSubDir);
		}else{
			char szFile[1024];
			sprintf(szFile, "%s%s%s", pDir, (pDir[nLen - 1] == '\\' || pDir[nLen - 1] == '/') ? "" : "\\", fd.cFileName);			
			DelFile(szFile);
		}
	}	
	FindClose(lFile);
	return _rmdir(pDir);
}

long WisdomUtils::CFileManange::GetFileSize( const char* pFile )
{
	struct _stat info;
	_stat((char*)pFile, &info);
	return info.st_size;
}

//��������ȡ��ǰ��������·��
void WisdomUtils::CFileManange::GetRootDirectoryA(LPSTR pszRootDir)
{
	if(NULL != pszRootDir)
	{
		char szModuleFileName[MAX_PATH] = "";
		GetModuleFileNameA(NULL, szModuleFileName, MAX_PATH);

		char* pRchr = strrchr(szModuleFileName, '\\');
		if(NULL == pRchr)
		{
			pRchr = strrchr(szModuleFileName, '/');
		}

		if(NULL != pRchr)
		{
			pRchr++;
			*pRchr = '\0';
		}

		strcpy(pszRootDir, szModuleFileName);
	}
}


//��������ȡ��ǰ��������·��
void  WisdomUtils::CFileManange::GetRootDirectoryW(LPTSTR pszRootDir)
{
	if(NULL != pszRootDir)
	{
		TCHAR szModuleFileName[MAX_PATH] = _T("");
		GetModuleFileName(NULL, szModuleFileName, MAX_PATH);

		TCHAR* pRchr = wcsrchr(szModuleFileName, '\\');
		if(NULL == pRchr)
		{
			pRchr = wcsrchr(szModuleFileName, '/');
		}

		if(NULL != pRchr)
		{
			pRchr++;
			*pRchr = '\0';
		}

		StrCpy(pszRootDir, szModuleFileName);
	}
}

string WisdomUtils::CFileManange::GetImageHead(wstring wstrPath)
{
	string strFomat="";
	char pfile[4096];
	//std::wstring wstrPath = strPath.toStdWString();

	int nwstrPathLen = ::WideCharToMultiByte(CP_ACP, 0, (wchar_t*)wstrPath.c_str(), -1, 0, 0, 0, 0);
	if (nwstrPathLen <= 0)
	{
		strFomat = "png";
	}
	WideCharToMultiByte(CP_ACP, 0, (wchar_t*)wstrPath.c_str(), -1, pfile, nwstrPathLen, 0, 0);
	FILE *file=fopen(pfile,"rb");
	if (file)
	{
		char buf[5] ={0},buf1[5] ={0},buf2[5] ={0};		
		fread(buf,5,5,file);
		fclose(file);
		memcpy(buf1, buf, 3);
		memcpy(buf2, &buf[1], 3);
		std::string str1(buf1, 3);
		const char szJpgHead[] = {0xff, 0xd8, 0xff};
		const string strJpgHead(szJpgHead, 3);
		if (strJpgHead == str1)
		{
			strFomat = "jpg";
		}
		else if (strcmp(buf1,"GIF") == 0)
		{
			strFomat="gif";
		}
		else if (strcmp(buf2,"PNG") == 0)
		{
			strFomat="png";
		}
		else		
		{
			strFomat="bmp";
		}

	}
	return strFomat;
}