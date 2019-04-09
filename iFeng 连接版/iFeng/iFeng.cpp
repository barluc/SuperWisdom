#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <shellapi.h>
#include <direct.h>
#include "iFeng.h"
#include "iTunesApi.h"
#include "CommonHelper.h"
#include "IOSConnect.h"
#include "IOSDevice.h"


#ifdef __cplusplus
extern "C"
{
#endif
	//��ʼ��
	IFENG_API UINT IOSInitialize(void){
		return iTunesApi::InitApi();
	}
	//�ͷ�
	IFENG_API BOOL IOSDispose(void){
		return iTunesApi::ReleaseApi();
	}

	//ע�����ӻص�����
	IFENG_API BOOL IOSRegisterOnConnectListener(pConnecttion callback,void* pUserData){
		IOSConnect::OnConnect = callback;
		IOSConnect::OnConnectUserData = pUserData;
		return TRUE;
	}
	//ע��Ͽ��ص�����
	IFENG_API BOOL IOSRegisterOnDisConnectListener(pConnecttion callback,void* pUserData){
		IOSConnect::OnDisConnect = callback;
		IOSConnect::OnDisconnectUserData = pUserData;
		return TRUE;
	}
	//��ʼ����
	IFENG_API BOOL IOSStartListen(){
		HANDLE hDevice;
		iTunesApi::AMDeviceNotificationSubscribe(IOSConnect::DeviceOnConnection,0,0,0,&hDevice);
		return TRUE;
	}

	//���豸
	IFENG_API BOOL IOSDeviceOpen(HANDLE hDevice){
		UINT ret = 0;
		if((ret = iTunesApi::AMDeviceConnect(hDevice)) != 0)
			return FALSE;
		if((ret = iTunesApi::AMDeviceIsPaired(hDevice)) != 1)
			return FALSE;
		if((ret = iTunesApi::AMDeviceValidatePairing(hDevice)) != 0)
			return FALSE;
		if((ret = iTunesApi::AMDeviceStartSession(hDevice)) != 0)
			return FALSE;
		return TRUE;
	}
	//�����豸��״̬
	IFENG_API BOOL IOSDeviceKeepConnect(HANDLE hDevice){
		WCHAR wcSN[MAX_PATH];
		UINT ret = 0;
		IOSDevice::GetDeviceSerialNumber(hDevice,wcSN);
		if ((ret = iTunesApi::AMDeviceStartSession(hDevice))!=0)
		{
			if((ret = iTunesApi::AMDeviceDisconnect(hDevice)) != 0)
				return FALSE;
			if((ret = iTunesApi::AMDeviceConnect(hDevice)) != 0)
				return FALSE;
			if((ret = iTunesApi::AMDeviceIsPaired(hDevice)) != 1)
				return FALSE;
			if((ret = iTunesApi::AMDeviceValidatePairing(hDevice)) != 0)
				return FALSE;
			if((ret = iTunesApi::AMDeviceStartSession(hDevice)) != 0)
				return FALSE;
		}
		return TRUE;
	}
	//�ر��豸
	IFENG_API BOOL IOSDeviceClose(HANDLE hDevice){
		iTunesApi::AMDeviceStopSession(hDevice);
		iTunesApi::AMDeviceDisconnect(hDevice);
		return TRUE;
	}
	//��ȡ�豸������Ϣ
	IFENG_API BOOL IOSGetDeviceInformation(HANDLE hDevice,DeviceProperty* info){
		IOSDevice::GetDeviceName(hDevice,info->Name);
		IOSDevice::GetDeviceID(hDevice,info->IdentifyNumber);
		IOSDevice::GetDeviceProductType(hDevice,info->ProductType);
		IOSDevice::GetDeviceSerialNumber(hDevice,info->SerialNumber);
		return TRUE;
	}
#ifdef __cplusplus
};
#endif
