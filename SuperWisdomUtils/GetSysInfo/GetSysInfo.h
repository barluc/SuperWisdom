#pragma once

#include <windows.h>

#include "WMIInfo.h"

//
//
//GetSysInfo info;
//int  nversion = info.GetWinOSVersion();
//cout << "CPU �� Ƶ: " << info.GetCpuFreq() << " GHZ" << endl;
//cout << "CPU �� ��: " << info.GetCpuType() << endl;
//cout << "ϵͳ��: " << info.GetWinOSName() << endl;
//cout << "�Կ�����: " << info.GetDisplayCard() << endl;
//cout << "�Կ��ڴ�: " << info.GetDisplayRAM() << " G" << endl;
//cout << "�Կ�Ƶ��: " << info.GetDisplayFreq() << " G" << endl;
//cout << "Ӳ�̴�С : " << info.GetDiskTotal() << " G" << endl;
//cout << "�ڴ��С : " << info.GetMemory() << " G" << endl;
//cout << "�ڴ���Ƶ : " << info.GetMemoryFreq() << "Mhz " << endl;

//����ϵͳ
enum SYSTEMTYPE
{

	SYSTEM_UNKNOWN = 0,       //δ֪�汾
	SYSTEM_XP = 1,       //xpϵͳ
	SYSTEM_XP_64 = 2,       //xp  64ϵͳ
	SYSTEM_VISTA_32 = 3,      //vista 32λϵͳ
	SYSTEM_VISTA_64 = 4,    //vista 64λϵͳ
	SYSTEM_WIN7_32 = 5,		//win7 32λϵͳ
	SYSTEM_WIN7_64 = 6,			//win7 64λϵͳ
	SYSTEM_WIN8_32 = 7,		//win8 32λϵͳ
	SYSTEM_WIN8_64 = 8,		//win8 64λϵͳ
	SYSTEM_WIN8_1_32 = 9,		//win8.1 32λϵͳ
	SYSTEM_WIN8_1_64 = 10,		//win8.1 64λϵͳ
	SYSTEM_WIN10_32 = 11,		//win10 32λϵͳ
	SYSTEM_WIN10_64 = 12,		//win10 64λϵͳ
	SYSTEM_SERVER_2003 = 13,	    //winServer2003
	SYSTEM_SERVER_2008 = 14	    //winServer2008

};

class GetSysInfo
{
public:
	GetSysInfo();
	~GetSysInfo();

	BOOL IsWow64();


	//����ϵͳ�汾 ���忴SYSTEMTYPE��ö��
	int GetWinOSVersion();

	//����ϵͳ����
	std::string  GetWinOSName();

	// ��ȡCPUƵ��,��λ: GHZ
	float	GetCpuFreq();

	//CPU �� ��
	std::string GetCpuType();

	// ��ȡCPU ��������Ŀ
	int	GetCpuCoresCount();

	// ��ȡCPU�߳���
	float	GetCpuThreadCount();

	//��ȡ�ڴ��С����λ:GB��
	float GetMemory();

	//��ȡ�ڴ���Ƶ
	float GetMemoryFreq();

	//Ӳ���ܴ�С��λ��G
	float GetDiskTotal();

	// ��ȡ�Կ�����
	std::string	GetDisplayCard();

	//��ȡ�Դ�
	float  GetDisplayRAM();

	//��ȡ�Դ���Ƶ  (δ���)
	float  GetDisplayFreq();


	void GetGPUInfo(std::string &strName, float &fMemorySize , float &fEngineClock, float &fMemoryClock);
public:

	CWmiInfo wmi;
};