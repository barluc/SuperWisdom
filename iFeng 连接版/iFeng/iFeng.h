#ifndef IFENG_EXPORTS_H
#define IFENG_EXPORTS_H

#ifdef IFENG_EXPORTS_H
#define IFENG_API __declspec(dllexport)
#else
#define IFENG_API __declspec(dllimport)
#endif

#if (defined WIN32 || defined Win64)
#include <windows.h>
#endif


#include "iTunesApi.h"



#ifdef __cplusplus
extern "C"
{
#endif

	/*��ʼ�����*/
	//��ʼ��
	IFENG_API UINT IOSInitialize(void);
	//�ͷ�
	IFENG_API BOOL IOSDispose(void);

	/*�������*/
	//ע�����ӻص�����
	IFENG_API BOOL IOSRegisterOnConnectListener(pConnecttion callback,void* pUserData);
	//ע��Ͽ��ص�����
	IFENG_API BOOL IOSRegisterOnDisConnectListener(pConnecttion callback,void* pUserData);
	//��ʼ����
	IFENG_API BOOL IOSStartListen();

	/*�豸���*/
	//���豸
	IFENG_API BOOL IOSDeviceOpen(HANDLE hDevice);
	//�����豸��״̬
	IFENG_API BOOL IOSDeviceKeepConnect(HANDLE hDevice);
	//�ر��豸
	IFENG_API BOOL IOSDeviceClose(HANDLE hDevice);
	//��ȡ�豸������Ϣ
	IFENG_API BOOL IOSGetDeviceInformation(HANDLE hDevice,DeviceProperty* info);
#ifdef __cplusplus
};
#endif

#endif