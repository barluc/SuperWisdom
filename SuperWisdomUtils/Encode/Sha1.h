#ifndef _SHA1_H_ 
#define _SHA1_H_ 

//#include <stdint.h> 
/* 
* If you do not have the ISO standard stdint.h header file, then you 
* must typdef the following: 
* name meaning 
* uint32_t unsigned 32 bit integer 
* uint8_t unsigned 8 bit integer (i.e., unsigned char) 
* int_least16_t integer of > = 16 bits 
* 
*/ 

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef int int_least16_t;
#define SHA1HashSize 20 


#ifndef _SHA_enum_ 
#define _SHA_enum_ 
enum 
{ 
	shaSuccess = 0, 
	shaNull,			/* Null pointer parameter */ 
	shaInputTooLong,	/* input data too long */ 
	shaStateError		/* called Input after Result */ 
}; 
#endif 

/* 
* This structure will hold context information for the SHA-1 
* hashing operation 
*/ 
typedef struct SHA1Context 
{ 
	uint32_t		Intermediate_Hash[SHA1HashSize/4];	/* Message Digest */
	uint32_t		Length_Low;							/* Message length in bits */ 
	uint32_t		Length_High;						/* Message length in bits */ 	
	int_least16_t	Message_Block_Index;				/* Index into message block array */ 
	uint8_t			Message_Block[64];					/* 512-bit message blocks */ 
	int				Computed;							/* Is the digest computed? */ 
	int				Corrupted;							/* Is the message digest corrupted? */ 
} SHA1Context; 

/*
* ��Ϣ��󳤶�Ϊ  2GB  
*/

/************************************************************************/
/* ������: Sha1String                                                   */
/* ����  : szString    (in)��ɢ�е��ַ���								*/
/* ����  : pDestSha1   (in/out)���SHA1 �ַ��� �Ļ�����					*/
/* ����  : iBufSz      (in) pDestSha1�������Ĵ�С>=40					*/
/* ����  : ָ�򻺳��� pDestSha1 ��ָ��									*/
/************************************************************************/
TCHAR *Sha1String(LPCTSTR szString, LPTSTR pDestSha1, int iBufSz=40);

/************************************************************************/
/* ������: Sha1File		                                                */
/* ����  : szFilePath  (in)��ɢ�е��ļ�·��								*/
/* ����  : pDestSha1   (in/out)���SHA1 �ַ��� �Ļ�����					*/
/* ����  : iBufSz      (in) pDestSha1�������Ĵ�С>=40					*/
/* ����  : ָ�򻺳��� pDestSha1 ��ָ��									*/
/************************************************************************/
TCHAR *Sha1File(LPCTSTR szFilePath, LPTSTR pDestSha1, int iBufSz=40);

/************************************************************************/
/* ������: Sha1DataString                                               */
/* ����  : szString    (in)��ɢ�е��ַ���								*/
/* ����  : Digest      (in/out)���SHA1ֵ�Ļ�����						*/
/* ����  : ָ�򻺳��� Digest ��ָ��										*/
/************************************************************************/
uint8_t *Sha1DataString(LPCTSTR szString, uint8_t Digest[SHA1HashSize]);

/************************************************************************/
/* ������: Sha1DataFile                                                 */
/* ����  : szString    (in)��ɢ�е��ַ���								*/
/* ����  : Digest      (in/out)���SHA1ֵ�Ļ�����						*/
/* ����  : ָ�򻺳��� Digest ��ָ��										*/
/************************************************************************/
uint8_t *Sha1DataFile(LPCTSTR szFilePath, uint8_t Digest[SHA1HashSize]);



class CSha1
{
public:
	int SHA1Reset( SHA1Context *); 
	int SHA1Input( SHA1Context *, const uint8_t *, unsigned int); 
	int SHA1Result( SHA1Context *, uint8_t Message_Digest[SHA1HashSize]);

private:
	void SHA1PadMessage(SHA1Context *); 
	void SHA1ProcessMessageBlock(SHA1Context *); 
};

#endif
