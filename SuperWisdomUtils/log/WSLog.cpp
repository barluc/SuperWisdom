// +----------------------------------------------------------------------
// | Green C++ Basis Components
// +----------------------------------------------------------------------
// | WSLOG		��־
// +----------------------------------------------------------------------
// | Author:	Maga
// +----------------------------------------------------------------------
// | Modify:	Maga
// +----------------------------------------------------------------------


#include "WSLOG.h"
#include "log_deffine.h"
#include "Logger.h"
#include "LogManager.h"
extern std::unique_ptr<Logger> g_logPtr;
/*
 *	Function:		_log_write
 *	Explanation:	д��־
 *	Input:			nLevel			��־�ȼ�
					pFmt			��ʽ���ַ���
 *	Return:			ʵ��д����
 */
void _log_write(WSLOG_LEVEL nLevel, const char *pFmt, ...)
{
	
	if (nLevel == WSLOG_LEVEL::LEVEL_INFO)
	{
		LOG_INFO(pFmt,...);
	}

	return ;
}


