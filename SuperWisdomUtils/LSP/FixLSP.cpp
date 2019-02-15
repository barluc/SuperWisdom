#include "stdafx.h"


#include "FixLSP.h"

#include "LspFixExer.h"





CFixLSP::CFixLSP()
{

}

CFixLSP::~CFixLSP()
{

}

void CFixLSP::SlientFix()
{
	CLspFixExer fixer;
	fixer.InitLspList();
	fixer.OnFix();

}

void CFixLSP::Restore()
{
	CLspFixExer fixer;
	fixer.InitLspList();
	fixer.OnRestoreLsp();

}



void CFixLSP::OnFixLSP(BOOL bSlient)
{
	std::thread fixlspThread([&]()
	{
		if (bSlient)
		{
			SlientFix();
		}
		else
		{
			Restore();
		}
	});
	fixlspThread.join();
}

/*
*	Function:		IsExist
*	Explanation:	�ж��ļ���Ŀ¼�Ƿ��ļ�
*	Input:			strPath		·��
*	Return:			true ���� false ������
*/
bool IsExist(std::string strPath)
{
	unsigned long		ulAttr;

	if (strPath.empty())
	{
		return false;
	}

	ulAttr = GetFileAttributesA((char *)strPath.c_str());

	if (INVALID_FILE_ATTRIBUTES == ulAttr)
	{
		return false;
	}

	return true;
}

