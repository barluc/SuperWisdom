#ifndef _SHA256_H
#define _SHA256_H

#include <Windows.h>


#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE	64
#define SHA256_MASK			(SHA256_BLOCK_SIZE - 1)

typedef	unsigned int	sha2_32t;
typedef unsigned char	uint8_t;

/************************************************************************/
/* ������: Sha256String                                                 */
/* ����  : szString    (in)��ɢ�е��ַ���								*/
/* ����  : pDestSha    (in/out)���SHA256 �ַ��� �Ļ�����				*/
/* ����  : iBufSz      (in) pDestSha�������Ĵ�С>=64					*/
/* ����  : ָ�򻺳��� pDestSha1 ��ָ��									*/
/************************************************************************/
TCHAR *Sha256String(LPCTSTR szString, LPTSTR pDestSha, int iBufSz=64);

/************************************************************************/
/* ������: Sha256File		                                            */
/* ����  : szFilePath  (in)��ɢ�е��ļ�·��								*/
/* ����  : pDestSha    (in/out)���SHA256 �ַ��� �Ļ�����				*/
/* ����  : iBufSz      (in) pDestSha�������Ĵ�С>=64					*/
/* ����  : ָ�򻺳��� pDestSha1 ��ָ��									*/
/************************************************************************/
TCHAR *Sha256File(LPCTSTR szFilePath, LPTSTR pDestSha, int iBufSz=64);

/************************************************************************/
/* ������: Sha256DataString                                             */
/* ����  : szString    (in)��ɢ�е��ַ���								*/
/* ����  : Digest      (in/out)���SHA1ֵ�Ļ�����						*/
/* ����  : ָ�򻺳��� Digest ��ָ��										*/
/************************************************************************/
uint8_t *Sha256DataString(LPCTSTR szString, uint8_t Digest[SHA256_DIGEST_SIZE]);

/************************************************************************/
/* ������: Sha256DataFile                                               */
/* ����  : szString    (in)��ɢ�е��ַ���								*/
/* ����  : Digest      (in/out)���SHA1ֵ�Ļ�����						*/
/* ����  : ָ�򻺳��� Digest ��ָ��										*/
/************************************************************************/
uint8_t *Sha256DataFile(LPCTSTR szFilePath, uint8_t Digest[SHA256_DIGEST_SIZE]);



/* type to hold the SHA256 context				*/
typedef struct
{
	sha2_32t count[2];
	sha2_32t hash[8];
	sha2_32t wbuf[16];
} sha256_ctx;

class CSha256
{
public:
	void sha256_begin(sha256_ctx ctx[1]);
	void sha256_hash(const unsigned char data[], unsigned long len, sha256_ctx ctx[1]);
	void sha256_end(unsigned char hval[], sha256_ctx ctx[1]);
	void sha256(unsigned char hval[32], const unsigned char data[], unsigned long len); 

private:
	void sha256_compile(sha256_ctx ctx[1]);
};

#endif
