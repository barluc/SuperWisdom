#pragma once

/*
���Է�ʽ(���������������һ�����ݽ��в�ͬ���εĲ���) :
127.0.0.1 : 9988
127.0.0.1 : 9988 / hehe.html
127.0.0.1 : 9988 / login.html
127.0.0.1 : 9988 / haha ? x = 10 & y = 20

Ҳ��������fiddler���߽��и�ȫ���ģ�����!


1��֧��GET / POST����
2��֧��CGI
3��֧�ִ��󷵻�
4��֧��chunked���ݵĽ���

ȱ�� :
1��֧�ֵķ�������ȫ��
2��CGIʵ�ֲ�����ѧ�����Գ���ʹ��FASTCGI
3����֧��https
4����֧�ֻ�Ӧchunked����

*/
#include <atomic>
#include <mutex>
#include <map>
#include <thread>
#include <memory>
#include <WinSock2.h>
#include "HttpServer.h"
class CServerListener
{
public:

	CServerListener(int nPort = 9988);

	~CServerListener();

public:

	/**
	* ��ʼ��windows socket
	*
	* @param port Port on which the server will be listening for connections
	* @param buffer_size Size of the buffer used to retrieve data from sockets
	*/
	int Init(int  nPort);


	/**
	* Start listening for connections.
	* @param client_acceptation_error_callback The function receiving the ClientAcceptationException object when a problem with acceptation of new connection occurs
	*/
	//void run(std::function<void(ClientAcceptationException)> client_acceptation_error_callback = [](ClientAcceptationException) {});
	void run();
	/**
	* Stop listening for connections (close listening socket).
	*
	* @warning It could be run only from the different thread, as start() is blocking
	*/
	void stop();

	void  SetHttpRequestBodyCallBack(HttpRequestBodyCallBack callBackFunc);

	//�ͻ��˲����߳�
	 void clientHandler(SOCKET client_socket);

	 //���������ͻ��˷�����Ϣ
	 void send2client(SOCKET socketValue, const char* pResponseBuf, int nSendLen);

public:
	// ��ȡhttp������ʵ��
	static CServerListener* GetInstance();

	//�˳�����ʱ���ڴ��ͷ�
	static void Destory()
	{
		if (nullptr != s_pServerListener)
		{
			delete s_pServerListener;
			s_pServerListener = nullptr;
		}
	};
public:

	static CServerListener*		s_pServerListener;

	std::mutex m_mutex;

	HttpRequestBodyCallBack m_requestBodyCallBackFunc;

	SOCKET listen_socket = INVALID_SOCKET;

	std::atomic<BOOL>	   m_bRunning_Server;		 //��ǰ״̬
};


#define HTTP_SERVER CServerListener::GetInstance()