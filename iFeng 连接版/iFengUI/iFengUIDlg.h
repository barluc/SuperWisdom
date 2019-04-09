
// iFengUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CiFengUIDlg �Ի���
class CiFengUIDlg : public CDialogEx
{
// ����
public:
	CiFengUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IFENGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	static void OnConnectStaticFunc(HANDLE hDevice,void* pUserData);
	static void OnDisConnectStaticFunc(HANDLE hDevice,void* pUserData);

	void OnConnect(HANDLE hDevice);
	void OnDisconnect(HANDLE hDevice);
	CStatic m_lbInfo;
};
