#pragma once

#include <Windows.h>

#include <vector>
#include <iostream>
using namespace  std;


class CpuServer
{
public:
	CpuServer(int nPid);
	~CpuServer(){};

  int getWin_CpuUseage();

  int getPid(){return m_nPid;}

  unsigned getWin_CoreCount();
private:
	int m_nCpuUseage;

	int m_nPid;

	//cpu����
	 int processor_count_ ;
	//��һ�ε�ʱ��
	 __int64 last_time_ ;
	 __int64 last_system_time_ ;
	
};


class Secretary
{
public:  
    void Add(CpuServer ob) { m_observers.push_back(ob); } 
 
    void Remove(int pid);

	bool find(int pid);

	void Remove();

    int Notify();
  
private:  
    vector<CpuServer> m_observers;  
};





class CGetWinInfo
{
public:
	CGetWinInfo();
	~CGetWinInfo();

public:
	/*****************/
	//Cpuʹ����
	/*****************/
	double getWin_CpuUseage();


	/*****************/
	//Cpuʹ����
	/*****************/
	int getWin_CpuUseage(int pid);

	/*****************/
	//��ȡwindows �ڴ� ʹ����
	/*****************/
	DWORD getWin_MemUsage();


	/*****************/
	//��ȡCpu����ʹ����
	/*****************/
	DWORD getWin_MaxCpuUseage();

	/*****************/
	//�ж�CPU �Ƿ񳬹���ֵ
	/*****************/
	bool  Check_CpuAvg(int nMax=0);

	/*****************/
	//��ȡCPU ����
	/*****************/
	unsigned getWin_CoreCount();

	/*****************/
	//��ȡʣ���ڴ��С
	/*****************/
	DWORDLONG getWin_FreeMem();

	/*****************/
	//��ȡʣ���ڴ��С
	/*****************/
	float getWin_FreeMemory();

	/*****************/
	//�жϾ����Ƿ��
	/*****************/
	bool Check_HvmUser();


   
private:
	FILETIME m_preidleTime;
	FILETIME m_prekernelTime;
	FILETIME m_preuserTime;


};