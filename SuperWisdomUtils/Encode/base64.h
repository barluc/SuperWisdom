#pragma once

class CBase64
{
public:
	// input:			  ����ԭ��
	// outBuf:			  ������, ����ռ�����㹻��, ���򷵻ؿմ�
	// nBufSz:			  outBuf�Ĵ�С(��λ: Byte)
	// trimTrailingZeros: ����Ƿ���'\0'��β
	// ����ֵ:			  �����ĳ��ȣ��������Ϊ0����������Ϊ�մ���˵�������С����
	unsigned int Decode(char* input, char* outBuf, unsigned int nBufSz, bool trimTrailingZeros = true);

	// orig:		ԭ��
	// origLength:	ԭ�ĳ���
	// outBuf:		����
	// nBufSz:		�����С(��λ: Byte)
	// ����ֵ:		outBufָ��
	char* Encode(char const* orig, unsigned origLength, char* outBuf, int nBufSz);

public:
	CBase64(void)	{ haveInitedBase64DecodeTable = false; }
	~CBase64(void)	{}
protected:
	void initDecodeTable();

private:
	char base64DecodeTable[256];
	bool haveInitedBase64DecodeTable;
};
