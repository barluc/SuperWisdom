#include <Windows.h>
#include <iostream>  
#include <DXGI.h>  
#include <vector>  

using namespace std;
std::string WStringToString(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}
#include "HttpClientLib/HttpClient.h"



int main()
{

	CHttpClient http;

	http.AddReqHeaders(_T("Accept-Language: zh-cn \r\nContent-Type: application/x-www-form-urlencoded\r\n"));
	http.OpenRequest(_T("http://127.0.0.1:9988"), REQ_METHOD_POST);

	CHAR lpData[128] = {"zhe ge shi yi ge ce shi cheng xu"};
	http.SendRequest(lpData, 128);
	http.CloseRequest();

	// ��������  
	IDXGIFactory * pFactory;
	IDXGIAdapter * pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;            // �Կ�  


	// �Կ�������  
	int iAdapterNum = 0;


	// ����һ��DXGI����  
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	if (FAILED(hr))
		return -1;

	// ö��������  
	while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		++iAdapterNum;
	}

	// ��Ϣ���   
	cout << "===============��ȡ��" << iAdapterNum << "���Կ�===============" << endl;
	for (size_t i = 0; i < vAdapters.size(); i++)
	{
		// ��ȡ��Ϣ  
		DXGI_ADAPTER_DESC adapterDesc;
		vAdapters[i]->GetDesc(&adapterDesc);
		wstring aa(adapterDesc.Description);
		std::string bb = WStringToString(aa);
		// ����Կ���Ϣ  
		cout << "ϵͳ��Ƶ�ڴ�:" << adapterDesc.DedicatedSystemMemory / 1024 / 1024 << "M" << endl;
		cout << "ר����Ƶ�ڴ�:" << adapterDesc.DedicatedVideoMemory / 1024 / 1024 << "M" << endl;
		cout << "����ϵͳ�ڴ�:" << adapterDesc.SharedSystemMemory / 1024 / 1024 << "M" << endl;
		cout << "�豸����:" << bb.c_str() << endl;
		cout << "�豸ID:" << adapterDesc.DeviceId << endl;
		cout << "PCI ID�����汾:" << adapterDesc.Revision << endl;
		cout << "��ϵͳPIC ID:" << adapterDesc.SubSysId << endl;
		cout << "���̱��:" << adapterDesc.VendorId << endl;

		// ����豸  
		IDXGIOutput * pOutput;
		std::vector<IDXGIOutput*> vOutputs;
		// ����豸����  
		int iOutputNum = 0;
		while (vAdapters[i]->EnumOutputs(iOutputNum, &pOutput) != DXGI_ERROR_NOT_FOUND)
		{
			vOutputs.push_back(pOutput);
			iOutputNum++;
		}

		cout << "-----------------------------------------" << endl;
		cout << "��ȡ��" << iOutputNum << "����ʾ�豸:" << endl;
		cout << endl;

		for (size_t n = 0; n < vOutputs.size(); n++)
		{
			// ��ȡ��ʾ�豸��Ϣ  
			DXGI_OUTPUT_DESC outputDesc;
			vOutputs[n]->GetDesc(&outputDesc);

			// ��ȡ�豸֧��  
			UINT uModeNum = 0;
			DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
			UINT flags = DXGI_ENUM_MODES_INTERLACED;

			vOutputs[n]->GetDisplayModeList(format, flags, &uModeNum, 0);
			DXGI_MODE_DESC * pModeDescs = new DXGI_MODE_DESC[uModeNum];
			vOutputs[n]->GetDisplayModeList(format, flags, &uModeNum, pModeDescs);

			cout << "��ʾ�豸����:" << outputDesc.DeviceName << endl;
			cout << "��ʾ�豸��ǰ�ֱ���:" << outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left << "*" << outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top << endl;
			cout << endl;

			// ��֧�ֵķֱ�����Ϣ  
			cout << "�ֱ�����Ϣ:" << endl;
			for (UINT m = 0; m < uModeNum; m++)
			{
				cout << "== �ֱ���:" << pModeDescs[m].Width << "*" << pModeDescs[m].Height << "     ˢ����" << (pModeDescs[m].RefreshRate.Numerator) / (pModeDescs[m].RefreshRate.Denominator) << endl;
			}
		}
		vOutputs.clear();

	}
	vAdapters.clear();

	system("pause");
	return 0;
}