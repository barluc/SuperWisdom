

#include "WSJson.h"

#include <fstream>
#include <stdexcept>
#include <memory>
#include <iostream>




/*
*	Function:		StrTrim
*	Explanation:	ȥ���ַ������߳��ֵ��ַ�(��strChars�г��ֵĶ�ɾ��)
*	Input:			strBuf		�ַ���
strChars	��Ҫȥ�����ַ�
*	Output:			strBuf		ȥ������ַ���
*	Return:			ȥ�����ַ����Ĵ�С
*/
int StrTrim(std::string &strBuf, std::string strChars /* = " " */)
{
	std::string::iterator				Iter;		// ���������
	std::string::reverse_iterator		reIter;		// ���������

	if (strBuf.empty())
	{
		return strBuf.size();
	}

	for (size_t sIndex = 0; sIndex < strBuf.size(); sIndex++)
	{
		Iter = strBuf.begin();

		if (NULL != strchr((char *)strChars.c_str(), *Iter))
		{
			strBuf.erase(Iter);
			continue;
		}

		break;
	}

	for (size_t sIndex = 0; sIndex < strBuf.size(); sIndex++)
	{
		reIter = strBuf.rbegin();

		if (NULL != strchr((char *)strChars.c_str(), *reIter))
		{
			strBuf.erase(strBuf.begin() + strBuf.size() - 1);
			continue;
		}

		break;
	}

	return strBuf.size();
}









/*
 *	Function:		GSJsonObject
 *	Explanation:	���캯��
 */
WSJsonObject::WSJsonObject()
{

}

/*
 *	Function:		~GSJsonObject
 *	Explanation:	��������
 */
WSJsonObject::~WSJsonObject()
{

}

/*
 *	Function:		_GetValue
 *	Explanation:	��ȡJson::Value����
 *	Return:			Json::Value����
 */
Json::Value WSJsonObject::_GetValue()
{
	return m_Obj;
}

/*
 *	Function:		_SetValue
 *	Explanation:	����Json::Value
 *	Input:			Value
 *  Output:			���
 *	Return:			TRUE �ɹ� FALSE ʧ��
 */
void WSJsonObject::_SetValue(Json::Value Value)
{
	m_Obj = Value;
}

/*
 *	Function:		Put
 *	Explanation:	�������
 *	Input:			Key			��
					Value		ֵ
 */
void WSJsonObject::Put(std::string Key, int Value, bool Isbool /* = false */)
{
	if (!Isbool)
	{
		m_Obj[Key] = Value;
	}
	else
	{
		if (0 == Value)
		{
			m_Obj[Key] = false;
		}
		else
		{
			m_Obj[Key] = true;
		}
	}
	
}

void WSJsonObject::Put(std::string Key, unsigned int Value)
{
	m_Obj[Key] = Value;
}

void WSJsonObject::Put(std::string Key, __int64 Value)
{
	m_Obj[Key] = Value;
}

void WSJsonObject::Put(std::string Key, unsigned __int64 Value)
{
	m_Obj[Key] = Value;
}

void WSJsonObject::Put(std::string Key, double Value)
{
	m_Obj[Key] = Value;
}

void WSJsonObject::Put(std::string Key, float Value)
{
	m_Obj[Key] = Value;
}

void WSJsonObject::Put(std::string Key, std::string Value)
{
	m_Obj[Key] = Value;
}

void WSJsonObject::Put(std::string Key, WSJsonObject JsonObj)
{
	m_Obj[Key] = JsonObj.Value;
}

void WSJsonObject::Put(std::string Key, WSJsonArray JsonArr)
{
	m_Obj[Key] = JsonArr.Value;
}

/*
 *	Function:		IsInt
 *	Explanation:	�ж�ָ������ֵ������
 *	Input:			Key			��
 *	Return:			true �� false ����
 */
bool WSJsonObject::IsInt(std::string Key)
{
	return m_Obj[Key].isInt();
}

bool WSJsonObject::IsUInt(std::string Key)
{
	return m_Obj[Key].isUInt();
}

bool WSJsonObject::IsInt64(std::string Key)
{
	return m_Obj[Key].isInt64();
}

bool WSJsonObject::IsUInt64(std::string Key)
{
	return m_Obj[Key].isUInt64();
}

bool WSJsonObject::IsBool(std::string Key)
{
	return m_Obj[Key].isBool();
}

bool WSJsonObject::IsDouble(std::string Key)
{
	return m_Obj[Key].isDouble();
}

bool WSJsonObject::IsString(std::string Key)
{
	return m_Obj[Key].isString();
}

bool WSJsonObject::IsObject(std::string Key)
{
	return m_Obj[Key].isObject();
}

bool WSJsonObject::IsArray(std::string Key)
{
	return m_Obj[Key].isArray();
}

/*
 *	Function:		GetBool
 *	Explanation:	��ȡֵ
 *	Input:			Key			��
 *	Return:			��Ӧ��ֵ����
 */
bool WSJsonObject::GetBool(std::string Key)
{
	if (IsNull(Key))
	{
		throw std::invalid_argument("key not exist");
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultBool(Key);
	}

	return m_Obj[Key].asBool();
}

int WSJsonObject::GetInt(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultInt(Key);
	}

	return m_Obj[Key].asInt();
}

unsigned int WSJsonObject::GetUInt(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultInt(Key);
	}

	return m_Obj[Key].asUInt();
}

__int64 WSJsonObject::GetInt64(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultInt(Key);
	}

	return m_Obj[Key].asInt64();
}

unsigned __int64 WSJsonObject::GetUInt64(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultInt(Key);
	}

	return m_Obj[Key].asUInt64();
}

double WSJsonObject::GetDouble(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultFloat(Key);
	}

	return m_Obj[Key].asDouble();
}

float WSJsonObject::GetFloat(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultFloat(Key);
	}

	return m_Obj[Key].asFloat();
}

std::string WSJsonObject::GetString(std::string Key)
{
	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultString(Key);
	}

	return m_Obj[Key].asString();
}

WSJsonObject WSJsonObject::Get(std::string Key)
{
	WSJsonObject			Obj;

	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultObject(Key);
	}

	Obj.Value = m_Obj[Key];

	return Obj;
}

WSJsonArray WSJsonObject::GetArr(std::string Key)
{
	WSJsonArray			Arr;

	if (IsNull(Key))
	{
		//_THROW(std::invalid_argument, "key not exist");
		return _GetDefaultArray(Key);
	}

	Arr.Value = m_Obj[Key];

	return Arr;
}

/*
 *	Function:		OptGetBool
 *	Explanation:	��ȡֵ��Key��Ӧ�ļ�ֵ���Բ����ڣ�
 *	Input:			Key			��
					Default		Ĭ��ֵ
 *	Return:			ֵ
 */
bool WSJsonObject::OptGetBool(std::string Key, bool Default /* = false */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asBool();
}

int WSJsonObject::OptGetInt(std::string Key, int Default /* = 0 */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asInt();
}

unsigned int WSJsonObject::OptGetUInt(std::string Key, unsigned int Default /* = 0 */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asUInt();
}

__int64 WSJsonObject::OptGetInt64(std::string Key, __int64 Default /* = 0 */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asInt64();
}

unsigned __int64 WSJsonObject::OptGetUInt64(std::string Key, unsigned __int64 Default /* = 0 */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asUInt64();
}

double WSJsonObject::OptGetDouble(std::string Key, double Default /* = 0 */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asDouble();
}

float WSJsonObject::OptGetFloat(std::string Key, float Default /* = 0 */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asFloat();
}

std::string WSJsonObject::OptGetString(std::string Key, std::string Default /* = "" */)
{
	if (IsNull(Key))
	{
		return Default;
	}

	return m_Obj[Key].asString();
}

WSJsonObject WSJsonObject::OptGet(std::string Key, WSJsonObject Default /* = GSJsonObj_NULL */)
{
	WSJsonObject			Obj;

	if (IsNull(Key))
	{
		return Default;
	}

	Obj.Value = m_Obj[Key];

	return Obj;
}

/*
*	Function:		IsNull
*	Explanation:	�ж�ָ������ֵ�Ƿ�Ϊ��(��NameΪ�����жϵ�ǰ����)
*	Input:			Key			��
*	Return:			true �� false �ǿ�
*/
bool WSJsonObject::IsNull(std::string Key /* = "" */)
{
	if (Key.empty())
	{
		return m_Obj.isNull();
	}
	else
	{
		return !m_Obj.isMember(Key);
	}
}

/*
 *	Function:		GetKeys
 *	Explanation:	��ȡ����Key
 *	Return:			Key�б�
 */
std::vector<std::string> WSJsonObject::GetKeys()
{
	std::vector<std::string>		vecList;
	Json::Value::Members	memList;

	memList = m_Obj.getMemberNames();

	for (size_t stIndex = 0; stIndex < memList.size(); stIndex ++)
	{
		vecList.push_back(memList[stIndex]);
	}

	return vecList;
}

/*
 *	Function:		Remove
 *	Explanation:	�Ƴ���ֵ��
 *	Input:			Key			��
 */
void WSJsonObject::Remove(std::string Key)
{
	if (IsNull(Key))
	{
		return;
	}

	m_Obj.removeMember(Key);
}

/*
 *	Function:		Size
 *	Explanation:	��ȡ��ֵ������
 *	Return:			��ֵ������
 */
unsigned int WSJsonObject::Size()
{
	return m_Obj.size();
}

/*
 *	Function:		Compare
 *	Explanation:	�Ƚ�����Obj
 *	Input:			����
 *  Output:			���
 *	Return:			TRUE �ɹ� FALSE ʧ��
 */
int WSJsonObject::Compare(WSJsonObject JsonObj)
{
	return m_Obj.compare(JsonObj.Value);
}

/*
 *	Function:		Clear
 *	Explanation:	���
 */
void WSJsonObject::Clear()
{
	m_Obj.clear();
}

/*
 *	Function:		ToString
 *	Explanation:	��ȡJson��ʽ�ַ���
 *	Return:			Json��ʽ�ַ���
 */
std::string WSJsonObject::ToString(bool bStyled /* = true */)
{
	if (bStyled)
	{
		return m_Obj.toStyledString();
	}

	Json::StreamWriterBuilder wbuilder;
	std::string jsonStr = Json::writeString(wbuilder, m_Obj);
	StrTrim(jsonStr, "\n");
	return jsonStr;
}

/*
 *	Function:		ToArray
 *	Explanation:	ת����GSJsonArray
 *	Return:			GSJsonArray
 */
WSJsonArray WSJsonObject::ToArray()
{
	WSJsonArray			JsonArr;

	JsonArr.Value = m_Obj;

	return JsonArr;
}

bool WSJsonObject::_GetDefaultBool(std::string key)
{
	//WSLOG_WARN("key %s not exist", key.c_str());
	return false;
}

int WSJsonObject::_GetDefaultInt(std::string key)
{
	//WSLOG_WARN("key %s not exist", key.c_str());
	return 0;
}

float WSJsonObject::_GetDefaultFloat(std::string key)
{
	//WSLOG_WARN("key %s not exist", key.c_str());
	return 0.0;
}

std::string WSJsonObject::_GetDefaultString(std::string key)
{
	//WSLOG_WARN("key %s not exist", key.c_str());
	return "";
}

WSJsonObject WSJsonObject::_GetDefaultObject(std::string key)
{
	//WSLOG_WARN("key %s not exist", key.c_str());
	return WSJsonObject();
}

WSJsonArray WSJsonObject::_GetDefaultArray(std::string key)
{
	//WSLOG_WARN("key %s not exist", key.c_str());
	return WSJsonArray();
}





/*
 *	Function:		GSJsonArray
 *	Explanation:	���캯��
 */
WSJsonArray::WSJsonArray() : m_Obj(Json::arrayValue)
{
}

WSJsonArray::WSJsonArray(const std::vector<int> &vectList)
{
	for (auto item : vectList)
	{
		m_Obj.append(item);
	}
}

WSJsonArray::WSJsonArray(const std::vector<std::string> &vectList)
{
	for (auto item : vectList)
	{
		m_Obj.append(item);
	}
}

/*
 *	Function:		~GSJsonArray
 *	Explanation:	��������
 */
WSJsonArray::~WSJsonArray()
{

}

/*
*	Function:		_GetValue
*	Explanation:	��ȡJson::Value����
*	Return:			Json::Value����
*/
Json::Value WSJsonArray::_GetValue()
{
	return m_Obj;
}

/*
*	Function:		_SetValue
*	Explanation:	����Json::Value
*	Input:			Value
*  Output:			���
*	Return:			TRUE �ɹ� FALSE ʧ��
*/
void WSJsonArray::_SetValue(Json::Value Value)
{
	m_Obj = Value;
}

/*
 *	Function:		IsNull
 *	Explanation:	�Ƿ�Ϊ�ն���
 *	Return:			true �� false ����
 */
bool WSJsonArray::IsNull()
{
	return m_Obj.isNull();
}

/*
 *	Function:		Size
 *	Explanation:	�������
 *	Return:			�������
 */
unsigned int WSJsonArray::Size()
{
	return m_Obj.size();
}

/*
 *	Function:		Get
 *	Explanation:	��ȡGSJsonObject
 *	Input:			unIndex		����
 *	Return:			GSJsonObject
 */
WSJsonObject WSJsonArray::Get(unsigned int unIndex)
{
	WSJsonObject			JsonObj;

	if (!m_Obj.isValidIndex(unIndex))
	{
		throw std::invalid_argument("beyond the index");
		//_THROW(std::invalid_argument, "beyond the index");
	}
	else
	{
		JsonObj.Value = m_Obj[unIndex];
	}
	
	return JsonObj;
}

std::string WSJsonArray::GetString(unsigned int unIndex)
{
	std::string				strValue;

	if (!m_Obj.isValidIndex(unIndex))
	{
		throw std::invalid_argument("beyond the index");
		//_THROW(std::invalid_argument, "beyond the index");
	}
	else
	{
		strValue = m_Obj[unIndex].asString();
	}

	return strValue;
}

int WSJsonArray::GetInt(unsigned int unIndex)
{
	int						nValue;

	if (!m_Obj.isValidIndex(unIndex))
	{
		throw std::invalid_argument("beyond the index");
		//_THROW(std::invalid_argument, "beyond the index");
	}
	else
	{
		nValue = m_Obj[unIndex].asInt();
	}

	return nValue;
}

bool WSJsonArray::GetBool(unsigned int unIndex)
{
	bool					bValue;

	if (!m_Obj.isValidIndex(unIndex))
	{
		throw std::invalid_argument("beyond the index");
		//_THROW(std::invalid_argument, "beyond the index");
	}
	else
	{
		bValue = m_Obj[unIndex].asBool();
	}

	return bValue;
}

/*
 *	Function:		Add
 *	Explanation:	���
 *	Input:			JsonObj		json����
 */
void WSJsonArray::Add(WSJsonObject JsonObj)
{
	if (!m_Obj.isArray())
	{
		return;
	}

	m_Obj.append(JsonObj.Value);
}

void WSJsonArray::AddInt(int nValue)
{
	m_Obj.append(nValue);
}

void WSJsonArray::AddString(std::string strValue)
{
	m_Obj.append(strValue);
}

/*
 *	Function:		Remove
 *	Explanation:	�Ƴ�
 *	Input:			unIndex		����
 */
void WSJsonArray::Remove(unsigned int unIndex)
{
	m_Obj.removeIndex(unIndex, NULL);
}

/*
 *	Function:		Clear
 *	Explanation:	���
 */
void WSJsonArray::Clear()
{
	m_Obj.clear();
}

/*
 *	Function:		ToObject
 *	Explanation:	ת����GSJsonObject
 *	Return:			GSJsonObject
 */
WSJsonObject WSJsonArray::ToObject()
{
	WSJsonObject			JsonObj;

	JsonObj.Value = m_Obj;

	return JsonObj;
}

/*
 *	Function:		ToString
 *	Explanation:	��ȡJson��ʽ�ַ���
 *	Return:			Json��ʽ�ַ���
 */
std::string WSJsonArray::ToString(bool bStyled /* = true */)
{
	if (bStyled)
	{
		return m_Obj.toStyledString();
	}
	Json::StreamWriterBuilder wbuilder;
	std::string out = Json::writeString(wbuilder, m_Obj) ;
	StrTrim(out, "\n");
	return out;
}



/*
 *	Function:		GSJson
 *	Explanation:	���캯��
 */
GSJson::GSJson()
{

}

/*
 *	Function:		~GSJson
 *	Explanation:	��������
 */
GSJson::~GSJson()
{

}

/*
 *	Function:		ParseStr
 *	Explanation:	����Json��ʽ�ַ���
 *	Input:			strJson		
 *	Return:			GSJsonObject
 */
WSJsonObject GSJson::ParseStr(std::string strJson)
{
	WSJsonObject			JsonObj;
	Json::CharReaderBuilder builder;
	Json::Value				jsonItem;

	if (strJson.empty())
	{
		return JsonObj;
	}

	builder["collectComments"] = false;
	JSONCPP_STRING errs;
	Json::CharReader* reader = builder.newCharReader();
	if (!reader->parse(strJson.data(), strJson.data() + strJson.size(), &jsonItem, &errs)) //��jsonStr�ж�ȡ���ݵ�jsonRoot
	{
		
		return  JsonObj;
	}
	JsonObj.Value = jsonItem;
	return JsonObj;
}

/*
 *	Function:		ParaseFile
 *	Explanation:	��ȡ�ļ�������json
 *	Input:			strFile		�ļ�·��
 *	Return:			GSJsonObject
 */
WSJsonObject GSJson::ParaseFile(std::string strFile)
{
	WSJsonObject			JsonObj;
	Json::Value				jsonItem;
	std::ifstream			Stream; //��׼������


	Stream.open((char *)strFile.c_str(), std::ios::binary);
	if (false == Stream.is_open())
	{
		return JsonObj;
	}

	jsonItem.clear();

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, Stream, &jsonItem, &errs)) //��ifs�ж�ȡ���ݵ�jsonRoot
	{
		JsonObj.Value = jsonItem;
		Stream.close();
		return JsonObj;
	}
	JsonObj.Value = jsonItem;
	Stream.close();
	return JsonObj;
}



/*
 *	Function:		SaveToFile
 *	Explanation:	���浽�ļ�
 *	Input:			strFile		�ļ�·��
					JsonObj		Json����
 *	Return:			true �ɹ� false ʧ��
 */
bool GSJson::SaveToFile(std::string strFile, WSJsonObject JsonObj)
{
	std::string				strJson;
	std::ofstream			Stream;

	strJson = JsonObj.ToString();
	Stream.open((char *)strFile.c_str(), std::ios::binary | std::ios::trunc);

	if (false == Stream.is_open())
	{
		return false;
	}

	Stream.write((char *)strJson.c_str(), strJson.size());
	Stream.close();
	return true;
}