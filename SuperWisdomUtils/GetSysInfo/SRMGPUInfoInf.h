#pragma once

/************************************************************************/
/* �Կ����ݶ�ȡ�ӿڶ���                                                                     */
/************************************************************************/

#include <string>
#include <windows.h>
using namespace std;

class SRMGPUInfoInf
{
public:
	//��ȡ�Կ���Ƶ��
	virtual long getGPUEngineClock() = 0;

	//��ȡ�Դ�Ƶ��
	virtual long  getGPUMemoryClock() = 0;

	//��ȡ�Դ�
	virtual float   GetGPUMemorySize() = 0;

	//��ȡ�Կ�����
	virtual  std::string getGPUName() = 0;


};

