#include "CCodeVerify.h"
#include "CHardInfo.h"
#include "openssl/rsa.h"
#include "openssl/err.h"
#include "openssl/pem.h"
#include <iostream>
extern "C"
{
	#include "openssl/applink.c"
}
#include <cassert>
bool CCodeVerify::GetSerialNumber(const std::string strPemFile, std::string& strSerialNumber)
{
	std::string strMachineCode = CHardInfo::GetMachineCode();

	std::string strOrgNumber = EncodeRSA_PubKeyFile(strPemFile, strMachineCode);
	strSerialNumber = StrToHex(strOrgNumber);
	return true;
}

bool CCodeVerify::VerifyActiveNumber(const std::string strPemFile, const std::string strAcitveNumber, std::string& strDate, std::string& otherInfo)
{
	std::string strOrgActiveNumber = HexToStr(strAcitveNumber);
	std::string strMachineCode = DecodeRSA_PubKeyFile(strPemFile, strOrgActiveNumber);
	if (CHardInfo::VerifyMachineCode(strMachineCode))
	{
		auto valArray = CHardInfo::MachineCodeToArray(strMachineCode);
		strDate = valArray[7].substr(0, 8);
		otherInfo = valArray[7].substr(8, 8);
		return true;
	}
	else
	{
		return false;
	}
}

bool CCodeVerify::CreateActiveNumber(const std::string strPemFile, const std::string strSerialNumber, const std::string strDate, const std::string otherInfo, std::string& strAcitveNumber)
{
	std::string strOrgSerivalNumber = HexToStr(strSerialNumber);

	std::string pubKey = GenerateRSAPriKey();

	//MakeKey();
	
	std::string strOrgNumber = DecodeRSA_PriKeyFile(strPemFile, strOrgSerivalNumber);
	//std::string strOrgNumber = EncodeRSA_PriKey(strOrgSerivalNumber, pubKey);

	std::string strMachineCode = strOrgNumber.substr(0, 112) + strDate + otherInfo;
	std::string strOrgActiveNumber = EncodeRSA_PriKeyFile(strPemFile, strMachineCode);
	strAcitveNumber = StrToHex(strOrgActiveNumber);
	return true;
}


std::string CCodeVerify::EncodeRSA_PubKeyFile(const std::string& strPemFileName, const std::string& strData)
{
	if (strPemFileName.empty() || strData.empty())
	{
		assert(false);
		return "";
	}
	FILE* hPubKeyFile = nullptr;
	fopen_s(&hPubKeyFile, strPemFileName.c_str(), "rb");
	if (hPubKeyFile == NULL)
	{
		assert(false);
		return "";
	}
	std::string strRet;
	RSA* pRSAPublicKey = RSA_new();
	if (PEM_read_RSAPublicKey(hPubKeyFile, &pRSAPublicKey, 0, 0) == NULL)
	{
		assert(false);
		return "";
	}

	int nLen = RSA_size(pRSAPublicKey);
	char* pEncode = new char[nLen + 1];
	int ret = RSA_public_encrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pEncode, pRSAPublicKey, RSA_PKCS1_PADDING);
	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	RSA_free(pRSAPublicKey);
	fclose(hPubKeyFile);
	//CRYPTO_cleanup_all_ex_data();
	return strRet;
}

std::string CCodeVerify::EncodeRSA_PubKey(const std::string & strData, std::string & pubKey)
{
	return std::string();
}

std::string CCodeVerify::DecodeRSA_PriKeyFile(const std::string& strPemFileName, const std::string& strData)
{
	if (strPemFileName.empty() || strData.empty())
	{
		assert(false);
		return "";
	}
	FILE* hPriKeyFile = nullptr;
	fopen_s(&hPriKeyFile, strPemFileName.c_str(), "rb");
	if (hPriKeyFile == NULL)
	{
		assert(false);
		return "";
	}
	std::string strRet;
	RSA* pRSAPriKey = RSA_new();
	if (PEM_read_RSAPrivateKey(hPriKeyFile, &pRSAPriKey, 0, 0) == NULL)
	{
		assert(false);
		return "";
	}

	int nLen = RSA_size(pRSAPriKey);
	char* pEncode = new char[nLen + 1];
	int ret = RSA_private_decrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pEncode, pRSAPriKey, RSA_PKCS1_PADDING);
	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	RSA_free(pRSAPriKey);
	fclose(hPriKeyFile);
	//CRYPTO_cleanup_all_ex_data();
	return strRet;
}


std::string CCodeVerify::EncodeRSA_PriKeyFile(const std::string& strPemFileName, const std::string& strData)
{
	if (strPemFileName.empty() || strData.empty())
	{
		assert(false);
		return "";
	}
	FILE* hPriKeyFile = nullptr;
	fopen_s(&hPriKeyFile, strPemFileName.c_str(), "rb");
	if (hPriKeyFile == NULL)
	{
		assert(false);
		return "";
	}
	std::string strRet;
	RSA* pRSAPriKey = RSA_new();
	if (PEM_read_RSAPrivateKey(hPriKeyFile, &pRSAPriKey, 0, 0) == NULL)
	{
		assert(false);
		return "";
	}
	int nLen = RSA_size(pRSAPriKey);
	char* pDecode = new char[nLen + 1];
	// ����  
	int ret = RSA_private_encrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pDecode, pRSAPriKey, RSA_PKCS1_PADDING);
	if (ret >= 0)
	{
		strRet = std::string((char*)pDecode, ret);
	}
	delete[] pDecode;
	RSA_free(pRSAPriKey);
	fclose(hPriKeyFile);
	//CRYPTO_cleanup_all_ex_data();
	return strRet;
}

//���ܹ�Կ
std::string CCodeVerify::DecodeRSA_PubKeyFile(const std::string& strPemFileName, const std::string& strData)
{
	if (strPemFileName.empty() || strData.empty())
	{
		assert(false);
		return "";
	}
	FILE* hPubKeyFile = nullptr;
	fopen_s(&hPubKeyFile, strPemFileName.c_str(), "rb");
	if (hPubKeyFile == NULL)
	{
		assert(false);
		return "";
	}
	std::string strRet;
	RSA* pRSAPublicKey = RSA_new();
	if (PEM_read_RSA_PUBKEY(hPubKeyFile, &pRSAPublicKey, 0, 0) == NULL)
	{
		assert(false);
		return "";
	}

	int nLen = RSA_size(pRSAPublicKey);
	char* pEncode = new char[nLen + 1];
	int ret = RSA_public_decrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pEncode, pRSAPublicKey, RSA_PKCS1_PADDING);
	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}
	delete[] pEncode;
	RSA_free(pRSAPublicKey);
	fclose(hPubKeyFile);
	//CRYPTO_cleanup_all_ex_data();
	return strRet;
}

std::string CCodeVerify::DecodeRSA_PubKey(const std::string & strData, std::string & pubKey)
{
	std::string strRet;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	//keybio = BIO_new_mem_buf((unsigned char *)strPublicKey.c_str(), -1);  
	// �˴������ַ���  
	// 1, ��ȡ�ڴ������ɵ���Կ�ԣ��ٴ��ڴ�����rsa  
	// 2, ��ȡ���������ɵ���Կ���ı��ļ����ڴ��ڴ�����rsa  
	// 3��ֱ�ӴӶ�ȡ�ļ�ָ������rsa  
	//RSA* pRSAPublicKey = RSA_new();  
	RSA* rsa = RSA_new();
	rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);
	if (!rsa)
	{
		BIO_free_all(keybio);
		return std::string("");
	}

	int len = RSA_size(rsa);
	//int len = 1028;
	char *encryptedText = (char *)malloc(len + 1);
	memset(encryptedText, 0, len + 1);

	//����
	int ret = RSA_public_decrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	// �ͷ��ڴ�  
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

// ˽Կ����
std::string CCodeVerify::EncodeRSA_PriKey(const std::string &clearText, std::string &pubKey)
{
	std::string strRet;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	// �˴������ַ���  
	// 1, ��ȡ�ڴ������ɵ���Կ�ԣ��ٴ��ڴ�����rsa  
	// 2, ��ȡ���������ɵ���Կ���ı��ļ����ڴ��ڴ�����rsa  
	// 3��ֱ�ӴӶ�ȡ�ļ�ָ������rsa  
	//RSA* pRSAPublicKey = RSA_new();  
	RSA* rsa = RSA_new();
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	if (!rsa)
	{
		BIO_free_all(keybio);
		return std::string("");
	}

	int len = RSA_size(rsa);
	//int len = 1028;
	char *encryptedText = (char *)malloc(len + 1);
	memset(encryptedText, 0, len + 1);

	// ����  
	int ret = RSA_private_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	// �ͷ��ڴ�  
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

#define KEY_LENGTH  1024               // ��Կ����  
#define PUB_KEY_FILE "pubkey.pem"    // ��Կ·��  
#define PRI_KEY_FILE "prikey.pem"    // ˽Կ·��  
int CCodeVerify::MakeKey()
{

	// ��˽��Կ��    
	size_t pri_len;
	size_t pub_len;
	char *pri_key = NULL;
	char *pub_key = NULL;
	std::string strKey[2];
	// ������Կ��    
	RSA *keypair = RSA_generate_key(KEY_LENGTH, RSA_F4, NULL, NULL);

	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keypair);

	// ��ȡ����    
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	// ��Կ�Զ�ȡ���ַ���
	pri_key = (char *)malloc(pri_len + 1);
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	// �洢��Կ��    
	strKey[0] = pub_key;
	strKey[1] = pri_key;

	// �洢�����̣����ַ�ʽ�洢����begin rsa public key/ begin rsa private key��ͷ�ģ�  
	FILE *pubFile = fopen(PUB_KEY_FILE, "w");
	if (pubFile == NULL)
	{
		assert(false);
		return -1;
	}
	fputs(pub_key, pubFile);
	fclose(pubFile);

	FILE *priFile = fopen(PRI_KEY_FILE, "w");
	if (priFile == NULL)
	{
		assert(false);
		return -1;
	}
	fputs(pri_key, priFile);
	fclose(priFile);

	// �ڴ��ͷ�  
	RSA_free(keypair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);



	std::string pubKey, prikey;
	//������Կ��
	RSA *r = RSA_new();
	int bits = 512;
	BIGNUM *e = BN_new();
	BN_set_word(e, 65537);
	RSA_generate_key_ex(r, bits, e, NULL);
	char data[] = "Hello World";
	RSA_print_fp(stdout, r, 0);
	BIO *out;
	out = BIO_new_mem_buf((unsigned char *)prikey.c_str(), -1);
	int ret = PEM_write_bio_RSAPublicKey(out, r);
	printf("writepub:%d\n", ret);

	BUF_MEM *bptr;
	BIO_get_mem_ptr(out, &bptr);
	BIO_set_close(out, BIO_NOCLOSE); /* BIO_free() ���ͷ�BUF_MEM�ṹ */


	BIO_flush(out);
	//BIO_free(out);

	BN_free(e);
	RSA_free(r);


	/*if (access(g_pPubFile,0) != 0 || access(g_pPriFile,0) != 0)
	{
	 return 0;
	}*/
	//����key,����������1024����ζ�������Ա����1024/8-11=117���ֽڣ�
	//RSA_F4Ϊ��Կָ����һ�������ʹ��RSA_F4���ɣ�
	//��������������������ΪNULL
	RSA *pRsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
	if (pRsa == NULL)
	{
	
		return -1;
	}

	BIO *pBio = BIO_new_file("D://pubkey.pem", "wb");
	if (pBio == NULL)
	{
	
		return -2;
	}
	if (PEM_write_bio_RSAPublicKey(pBio, pRsa) == 0)
	{

		return -3;
	}
	BIO_free_all(pBio);


	pBio = BIO_new_mem_buf((unsigned char *)prikey.c_str(), -1);
	if (pBio == NULL)
	{

		return -4;
	}
	if (PEM_write_bio_RSAPrivateKey(pBio, pRsa, NULL, NULL, 0, NULL, NULL) == 0)
	{

		return -5;
	}
	BIO_free_all(pBio);
	RSA_free(pRsa);


	return 0;
}

std::string CCodeVerify::GenerateRSAPubKey(std::string strPemFileName)
{
	std::string strKey;
	// ��˽��Կ��    
	size_t pub_len;
	char *pub_key = NULL;

	// ������Կ��    
	RSA *keypair = RSA_generate_key(KEY_LENGTH, RSA_F4, NULL, NULL);

	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPublicKey(pub, keypair);

	// ��ȡ����    
	pub_len = BIO_pending(pub);

	// ��Կ�Զ�ȡ���ַ���
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pub, pub_key, pub_len);

	pub_key[pub_len] = '\0';

	// �洢��Կ��    
	strKey = pub_key;
	if (strPemFileName.length() > 0)
	{
		// �洢�����̣����ַ�ʽ�洢����begin rsa public key/ begin rsa private key��ͷ�ģ�  
		FILE *pubFile = fopen(strPemFileName.c_str(), "w");
		if (pubFile == NULL)
		{
			assert(false);
			return strKey;
		}
		fputs(pub_key, pubFile);
		fclose(pubFile);
	}
	// �ڴ��ͷ�  
	RSA_free(keypair);
	BIO_free_all(pub);
	free(pub_key);
	return strKey;	

}

std::string CCodeVerify::GenerateRSAPriKey(std::string strPemFileName)
{
	std::string strKey;
	// ��˽��Կ��    
	size_t pri_len;

	char *pri_key = NULL;

	// ������Կ��    
	RSA *keypair = RSA_generate_key(KEY_LENGTH, RSA_F4, NULL, NULL);
	BIO *pri = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);

	// ��ȡ����    
	pri_len = BIO_pending(pri);

	// ��Կ�Զ�ȡ���ַ���
	pri_key = (char *)malloc(pri_len + 1);

	BIO_read(pri, pri_key, pri_len);

	pri_key[pri_len] = '\0';
	

	// �洢��Կ��    
	strKey = pri_key;
	if (strPemFileName.length() > 0)
	{
		// �洢�����̣����ַ�ʽ�洢����begin rsa public key/ begin rsa private key��ͷ�ģ�  
		FILE *priFile = fopen(strPemFileName.c_str(), "w");
		if (priFile == NULL)
		{
			assert(false);
			return strKey;
		}
		fputs(pri_key, priFile);
		fclose(priFile);
	}	

	// �ڴ��ͷ�  
	RSA_free(keypair);
	BIO_free_all(pri);
	free(pri_key);
	return strKey;

}
