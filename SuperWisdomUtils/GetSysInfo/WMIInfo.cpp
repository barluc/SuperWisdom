#include "WMIInfo.h"

#pragma comment(lib,"WbemUuid.lib")

using namespace std;




CWmiInfo::CWmiInfo(void)
{
	m_pWbemSvc = NULL;
	m_pWbemLoc = NULL;
	m_pEnumClsObj = NULL;
}

CWmiInfo::~CWmiInfo(void)
{
	m_pWbemSvc = NULL;
	m_pWbemLoc = NULL;
	m_pEnumClsObj = NULL;
}

HRESULT CWmiInfo::InitWmi()
{

	HRESULT hres;

	//һ����ʼ��COM���  
	//��ʼ��COM  
	hres = ::CoInitializeEx(0, COINIT_MULTITHREADED);
	if (SUCCEEDED(hres) || RPC_E_CHANGED_MODE == hres)
	{
		//���ý��̵İ�ȫ���𣬣�����COM���ʱ�ڳ�ʼ��COM֮��Ҫ����CoInitializeSecurity���ý��̰�ȫ���𣬷���ᱻϵͳʶ��Ϊ������  
		hres = CoInitializeSecurity(NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_PKT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE,
			NULL);


		//��������һ��WMI�����ռ�����  
		//����һ��CLSID_WbemLocator����  
		hres = CoCreateInstance(CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator,
			(LPVOID*)&m_pWbemLoc);


		//ʹ��m_pWbemLoc���ӵ�"root\cimv2"������m_pWbemSvc��ָ��  
		hres = m_pWbemLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"),
			NULL,
			NULL,
			0,
			NULL,
			0,
			0,
			&m_pWbemSvc);



		//��������WMI���ӵİ�ȫ��  
		hres = CoSetProxyBlanket(m_pWbemSvc,
			RPC_C_AUTHN_WINNT,
			RPC_C_AUTHZ_NONE,
			NULL,
			RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE);


	}
	return(hres);
}

HRESULT CWmiInfo::ReleaseWmi()
{
	HRESULT hr;

	if (NULL != m_pWbemSvc)
	{
		hr = m_pWbemSvc->Release();
	}
	if (NULL != m_pWbemLoc)
	{
		hr = m_pWbemLoc->Release();
	}
	if (NULL != m_pEnumClsObj)
	{
		hr = m_pEnumClsObj->Release();
	}

	::CoUninitialize();

	return(hr);
}

BOOL CWmiInfo::GetSingleItemInfo(std::string ClassName, std::string ClassMember, std::string &chRetValue, std::string strWhere /* = ""*/)
{

	bstr_t query("SELECT * FROM ");
	VARIANT vtProp;
	ULONG uReturn;
	HRESULT hr;
	BOOL bRet = FALSE;

	if (NULL != m_pWbemSvc)
	{
		//��ѯ��ClassName�е������ֶ�,���浽m_pEnumClsObj��  
		query += _com_util::ConvertStringToBSTR((ClassName + strWhere).c_str());
		hr = m_pWbemSvc->ExecQuery(bstr_t("WQL"), query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			0, &m_pEnumClsObj);
		if (SUCCEEDED(hr))
		{
			//��ʼ��vtPropֵ  
			VariantInit(&vtProp);

			uReturn = 0;

			//���شӵ�ǰλ����ĵ�һ������m_pWbemClsObj��  
			hr = m_pEnumClsObj->Next(WBEM_INFINITE, 1, &m_pWbemClsObj, &uReturn);
			if (SUCCEEDED(hr) && uReturn > 0)
			{
				//��m_pWbemClsObj���ҳ�ClassMember��ʶ�ĳ�Ա����ֵ,�����浽vtProp������  
				hr = m_pWbemClsObj->Get(_com_util::ConvertStringToBSTR(ClassMember.c_str()), 0, &vtProp, 0, 0);
				if (SUCCEEDED(hr))
				{
					VariantToString(&vtProp, chRetValue);
					VariantClear(&vtProp);//���vtProp  
					bRet = TRUE;
				}
			}

		}
	}
	if (NULL != m_pEnumClsObj)
	{
		hr = m_pEnumClsObj->Release();
		m_pEnumClsObj = NULL;
	}
	if (NULL != m_pWbemClsObj)
	{
		hr = m_pWbemClsObj->Release();
		m_pWbemClsObj = NULL;
	}
	return bRet;
}

BOOL CWmiInfo::GetSingleItemInfo(std::string ClassName, std::string ClassMember, std::vector<std::string>& vecRetValue, std::string strWhere /* = ""*/)
{
	bstr_t query("SELECT * FROM ");
	VARIANT vtProp, vtPropAll;
	ULONG uReturn;
	HRESULT hr;
	BOOL bRet = FALSE;

	if (NULL != m_pWbemSvc)
	{
		//��ѯ��ClassName�е������ֶ�,���浽m_pEnumClsObj��  
		query += _com_util::ConvertStringToBSTR((ClassName + strWhere).c_str());
		hr = m_pWbemSvc->ExecQuery(bstr_t("WQL"), query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			0, &m_pEnumClsObj);
		if (SUCCEEDED(hr))
		{
			//��ʼ��vtPropֵ  
			VariantInit(&vtProp);
			std::string chRetValue = "";
			uReturn = 0;
			while (m_pEnumClsObj)
			{
				//���شӵ�ǰλ����ĵ�һ������m_pWbemClsObj��  
				hr = m_pEnumClsObj->Next(WBEM_INFINITE, 1, &m_pWbemClsObj, &uReturn);
				if (0 == uReturn)
				{
					break;
				}
				if (SUCCEEDED(hr) && uReturn > 0)
				{
					//��m_pWbemClsObj���ҳ�ClassMember��ʶ�ĳ�Ա����ֵ,�����浽vtProp������  
					hr = m_pWbemClsObj->Get(_com_util::ConvertStringToBSTR(ClassMember.c_str()), 0, &vtProp, 0, 0);
					if (SUCCEEDED(hr))
					{
						VariantToString(&vtProp, chRetValue);
						vecRetValue.push_back(chRetValue);
						VariantClear(&vtProp);//���vtProp  
						bRet = TRUE;
					}
				}
			}
		}
	}
	if (NULL != m_pEnumClsObj)
	{
		hr = m_pEnumClsObj->Release();
		m_pEnumClsObj = NULL;
	}
	if (NULL != m_pWbemClsObj)
	{
		hr = m_pWbemClsObj->Release();
		m_pWbemClsObj = NULL;
	}
	return bRet;
}

VARIANT CWmiInfo::GetSingleItemInfo(std::string ClassName, std::string ClassMember)
{

	bstr_t query("SELECT * FROM ");
	VARIANT vtProp;
	ULONG uReturn;
	HRESULT hr;
	BOOL bRet = FALSE;

	if (NULL != m_pWbemSvc)
	{
		//��ѯ��ClassName�е������ֶ�,���浽m_pEnumClsObj��  
		query += _com_util::ConvertStringToBSTR(ClassName.c_str());
		hr = m_pWbemSvc->ExecQuery(bstr_t("WQL"), query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			0, &m_pEnumClsObj);
		if (SUCCEEDED(hr))
		{
			//��ʼ��vtPropֵ  
			VariantInit(&vtProp);
			uReturn = 0;

			//���شӵ�ǰλ����ĵ�һ������m_pWbemClsObj��  
			hr = m_pEnumClsObj->Next(WBEM_INFINITE, 1, &m_pWbemClsObj, &uReturn);
			if (SUCCEEDED(hr) && uReturn > 0)
			{
				//��m_pWbemClsObj���ҳ�ClassMember��ʶ�ĳ�Ա����ֵ,�����浽vtProp������  
				hr = m_pWbemClsObj->Get(_com_util::ConvertStringToBSTR(ClassMember.c_str()), 0, &vtProp, 0, 0);
				if (SUCCEEDED(hr))
				{

					//VariantClear(&vtProp);//���vtProp  
					bRet = TRUE;
				}
			}
		}
	}
	if (NULL != m_pEnumClsObj)
	{
		hr = m_pEnumClsObj->Release();
		m_pEnumClsObj = NULL;
	}
	if (NULL != m_pWbemClsObj)
	{
		hr = m_pWbemClsObj->Release();
		m_pWbemClsObj = NULL;
	}
	return vtProp;
}

BOOL CWmiInfo::GetGroupItemInfo(std::string ClassName, std::string ClassMember[], int n, std::string &chRetValue)
{
	_bstr_t query("SELECT * FROM ");
	std::string result, info;
	VARIANT vtProp;
	ULONG uReturn;
	HRESULT hr;
	int i;
	BOOL bRet = FALSE;
	if (NULL != m_pWbemSvc)
	{
		query += _bstr_t(ClassName.c_str());
		hr = m_pWbemSvc->ExecQuery(_bstr_t("WQL"), query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 0, &m_pEnumClsObj);
		if (SUCCEEDED(hr))
		{
			VariantInit(&vtProp); //��ʼ��vtProp����  
			if (m_pEnumClsObj)
			{
				Sleep(10);
				uReturn = 0;
				hr = m_pEnumClsObj->Next(WBEM_INFINITE, 1, &m_pWbemClsObj, &uReturn);
				if (SUCCEEDED(hr) && uReturn > 0)
				{
					for (i = 0; i < n; ++i)
					{
						hr = m_pWbemClsObj->Get(_bstr_t(ClassMember[i].c_str()), 0, &vtProp, 0, 0);
						if (SUCCEEDED(hr))
						{
							VariantToString(&vtProp, info);
							chRetValue += info + "\t";
							VariantClear(&vtProp);
							bRet = TRUE;
						}
					}
					chRetValue += "\r\n";
				}
			}
		}
	}

	if (NULL != m_pEnumClsObj)
	{
		hr = m_pEnumClsObj->Release();
		m_pEnumClsObj = NULL;
	}
	if (NULL != m_pWbemClsObj)
	{
		hr = m_pWbemClsObj->Release();
		m_pWbemClsObj = NULL;
	}
	return bRet;
}

void CWmiInfo::VariantToString(const LPVARIANT pVar, std::string &chRetValue) const
{
	_bstr_t HUGEP* pBstr;
	BYTE HUGEP* pBuf;
	LONG low, high, i;
	HRESULT hr;
	char  szRetValue[256];
	switch (pVar->vt)
	{
	case VT_BSTR:
	{
		chRetValue = _com_util::ConvertBSTRToString(pVar->bstrVal);


	}
	break;
	case VT_BOOL:
	{
		if (VARIANT_TRUE == pVar->boolVal)
			chRetValue = "true";
		else
			chRetValue = "false";
	}
	break;
	case VT_I4:
	{
		sprintf_s(szRetValue, 256, "%u", pVar->uintVal);

		chRetValue = szRetValue;
	}
	break;
	case VT_UI1:
	{
		sprintf_s(szRetValue, 256, "%u", pVar->uintVal);
		chRetValue = szRetValue;
	}
	break;
	case VT_UI4:
	{
		sprintf_s(szRetValue, 256, "%u", pVar->uintVal);
		chRetValue = szRetValue;
	}
	break;

	case VT_BSTR | VT_ARRAY:
	{
		hr = SafeArrayAccessData(pVar->parray, (void HUGEP**)&pBstr);
		hr = SafeArrayUnaccessData(pVar->parray);

		sprintf_s(szRetValue, "%s", pBstr);
		chRetValue = szRetValue;
	}
	break;

	case VT_I4 | VT_ARRAY:
	{
		SafeArrayGetLBound(pVar->parray, 1, &low);
		SafeArrayGetUBound(pVar->parray, 1, &high);

		hr = SafeArrayAccessData(pVar->parray, (void HUGEP**)&pBuf);
		hr = SafeArrayUnaccessData(pVar->parray);
		std::string strTmp;
		high = min(high, MAX_PATH * 2 - 1);
		for (i = low; i <= high; ++i)
		{
			sprintf_s(szRetValue, 256, "%02X", pBuf[i]);
			chRetValue += szRetValue;
		}
	}
	break;
	default:
		break;
	}
}