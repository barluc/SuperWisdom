#ifndef SRMNVIDIAGPUINFO_H_B9DFEF68_12C7_4604_A025_8E75E8BA74B6
#define SRMNVIDIAGPUINFO_H_B9DFEF68_12C7_4604_A025_8E75E8BA74B6

/********************************************************************
 Nvidia�Կ���Ϣ����Ҫ�õ� nvapi64.lib
 GPU��Ϣ��ȡ������һ������
*********************************************************************/
#include <Windows.h>
#include "SRMGPUInfoInf.h"
#include "NvAPI\nvapi.h"



// �ඨ��
class SRMNvidiaGPUInfo : public SRMGPUInfoInf
{
public:
	static SRMGPUInfoInf* createGPUInfoInf();
public:
	SRMNvidiaGPUInfo();
	~SRMNvidiaGPUInfo();
public:

	//��ȡ�Կ���Ƶ��
	virtual long getGPUEngineClock() override;

	//��ȡ�Դ�Ƶ��
	virtual long  getGPUMemoryClock() override;

	//��ȡ�Դ�
	virtual float   GetGPUMemorySize() override;

	//��ȡ�Կ�����
	virtual  std::string getGPUName() override;


	 int getGPUCount() ;
	 long getMemRate(int nIndex);
	 int getTemperature(int nIndex) ;
private:
	void init();
	void unInit();
private:
	bool m_bIsValid;
    NvU32               m_nGPUCount;                            // �Կ�����
    NvPhysicalGpuHandle m_hGPUHandles[NVAPI_MAX_PHYSICAL_GPUS]; // �Կ���Ϣ
   	int m_nIndex;
};
#endif //SRMNVIDIAGPUINFO_H_B9DFEF68_12C7_4604_A025_8E75E8BA74B6