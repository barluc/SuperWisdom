#pragma once
#include <vector>
#include "common_def.h"


class CLspFixTool;


class CLspFixExer
{
public:
	CLspFixExer(void);
	~CLspFixExer(void);


public:
	// ö��LSPʹ�õĻص�����
	static BOOL WINAPI EnumLspCallBack( void* param,
		const LPCTSTR pszLspName, 
		const LPCTSTR pszFilePath, 
		const LPCTSTR pszClsid);

	void OnFix();
	void OnRestoreLsp();
	void InitLspList();

protected:
	BOOL EnumLsp();
	void DeleteAllLspData();

private:
	std::vector<PLSP_INFO> m_vLspInfo;
};

