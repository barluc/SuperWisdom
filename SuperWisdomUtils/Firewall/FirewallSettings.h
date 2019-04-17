

#pragma once


#include <netfw.h>


//
//CFirewallSettings firewallSettings;
//HRESULT hr = S_OK;
//TCHAR	szModPath[MAX_PATH];
//GetModuleFileName(NULL, szModPath, MAX_PATH);
//
//hr = firewallSettings.WindowsFirewallAddApp(
//	szModPath,
//	L"FrogPlay"
//);
//// Add TCP::80 to list of globally open ports.
//hr = firewallSettings.WindowsFirewallPortAdd(554, NET_FW_IP_PROTOCOL_TCP, L"WWW");

class  CFirewallSettings
{
public:
	CFirewallSettings();

	virtual ~CFirewallSettings();

public:
	
	bool FirewallAddApp(LPCTSTR lpFilePath, LPCTSTR lpShowName);

	
	bool FirewallRemoveApp(LPCTSTR lpFileName);

	HRESULT WindowsFirewallPortAdd(
		IN LONG portNumber,
		IN NET_FW_IP_PROTOCOL ipProtocol,
		IN const wchar_t* name
	);
	HRESULT WindowsFirewallPortIsEnabled(
		IN INetFwProfile* fwProfile,
		IN LONG portNumber,
		IN NET_FW_IP_PROTOCOL ipProtocol,
		OUT BOOL* fwPortEnabled
	);
	//��ӷ���ǽ����ĳ���Ͷ˿�
	HRESULT WindowsFirewallAddApp(
		IN const wchar_t* fwProcessImageFileName,
		IN const wchar_t* fwName
	);
	HRESULT WindowsFirewallAppIsEnabled(
		IN INetFwProfile* fwProfile,
		IN const wchar_t* fwProcessImageFileName,
		OUT BOOL* fwAppEnabled
	);
	HRESULT WindowsFirewallTurnOff(IN INetFwProfile* fwProfile);

	HRESULT WindowsFirewallTurnOn(IN INetFwProfile* fwProfile);

	HRESULT WindowsFirewallIsOn(IN INetFwProfile* fwProfile, OUT BOOL* fwOn);

	void WindowsFirewallCleanup(IN INetFwProfile* fwProfile);
	//����ǽ�ӿڳ�ʼ��
	HRESULT WindowsFirewallInitialize(OUT INetFwProfile** fwProfile);
	//�Ƴ�����ǽ����ĳ���Ͷ˿�

private:
	//��ʼ��
	void Initialize();
	
private:

	HRESULT m_ComInit ;
	INetFwProfile* m_pfwProfile ;

};




















