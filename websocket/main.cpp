//#include <iostream>
//#include "serverlistener.h"
//
//int main() {
//    ServerListener().run();
//    return 0;
//}
//


//////////////////////////////////////////////////
//
//      ����һ����С��WebServer������HTTPSЭ��
//
/////////////////////////////////////////////////////
//////////////////
//
//#include "helpFunction.h"
//
//
//// ������
//int main()
//{
//	// ��ʼ��windows socket
//	WSADATA wd;
//	SOCKET s;
//	if (WSAStartup(MAKEWORD(2, 2), &wd) < 0)
//	{
//		fprintf(stderr, "winsock startup failed\n");
//		exit(-1);
//	}
//
//	// �����������׽���
//	s = socket(AF_INET, SOCK_STREAM, 0);
//
//	// �󶨲�����
//	SOCKADDR_IN addr;
//	memset(&addr, 0, sizeof(addr));
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(827);
//	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	int ret = bind(s, (struct sockaddr*)&addr, sizeof(addr));
//	if (ret < 0)
//	{
//		fprintf(stderr, "bind failed\n");
//		closesocket(s);
//		exit(-1);
//	}
//
//	// ���м���
//	ret = listen(s, 1024);
//	if (ret < 0)
//	{
//		fprintf(stderr, "listen failed\n");
//		closesocket(s);
//		exit(-1);
//	}
//
//	char request[8000] = { 0 };  // ����
//	while (true)
//	{
//		// ���ӵ��ͻ��˵��׽���
//		SOCKET clientSocket = accept(s, 0, 0);
//
//		// ���ܿͻ��˵���Ϣ
//		recv(clientSocket, request, sizeof(request), 0);
//
//		// ���ͻ��˵���Ϣ������ն�
//		printf(request);
//
//		// ����������Ҫ���ܺ���
//		HandleRequestLine(clientSocket, request);
//	}
//
//	return 0;
//}



// webserver.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"



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


#include <tchar.h>

#include "ServerListener.h"



void handleRequestBody(const char* pBodyData, int nBodyLen)
{
	printf("------handleRequestBody----\n");
	char buff[65535] = { 0 };
	memcpy(buff, pBodyData, min(nBodyLen, 65535));
	printf_s("%s\n", buff);
}


int _tmain(int argc, _TCHAR* argv[])
{
	HTTP_SERVER->SetHttpRequestBodyCallBack(handleRequestBody);
	HTTP_SERVER->run();
	return 0;
}


