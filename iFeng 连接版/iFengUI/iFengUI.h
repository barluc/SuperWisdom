
// iFengUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiFengUIApp:
// �йش����ʵ�֣������ iFengUI.cpp
//

class CiFengUIApp : public CWinApp
{
public:
	CiFengUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CiFengUIApp theApp;