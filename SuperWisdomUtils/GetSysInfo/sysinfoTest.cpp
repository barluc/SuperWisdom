


#include "SRMGPUInfoInf.h"
#include "SRMATIGPUInfo.h"
#include <iostream>
#include "SRMNvidiaGPUInfo.h"
using namespace std;
// Application entry point
int main(int argc, char* argv[])
{

	SRMGPUInfoInf* m_pGPUInfoInf;
	m_pGPUInfoInf = SRMNvidiaGPUInfo::createGPUInfoInf();
	if (!m_pGPUInfoInf) // ATI�Կ�û���ṩ�Դ�ʹ�ö�ȡ�ӿ�
		m_pGPUInfoInf = SRMATIGPUInfo::createGPUInfoInf();

	cout << "��ȡ�Կ����ĵ�Ƶ�ʣ�" << m_pGPUInfoInf->getGPUEngineClock() << "MHZ" << endl;
	cout << "��ȡ�Կ��Դ��Ƶ�ʣ�" << m_pGPUInfoInf->getGPUMemoryClock() << "MHZ" << endl;
	cout << "��ȡ�Կ����Դ棺" << m_pGPUInfoInf->GetGPUMemorySize() << "G" << endl;
	cout << "��ȡ�Կ����ƣ�" << m_pGPUInfoInf->getGPUName() << endl;
	system("pause");
	return 0;
}