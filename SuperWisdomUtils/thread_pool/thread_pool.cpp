#pragma once


#include "thread_pool.h"
#include <stdio.h>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <windows.h>
#include <iostream>
using namespace netlib;



ThreadPool* ThreadPool::s_pThreadPool = nullptr;

ThreadPool::ThreadPool(int threadNumber)
:m_nThreadNumber(threadNumber),
m_bRunning(true),
m_vecThread(m_nThreadNumber)
{
	m_vecThread.clear();
}

ThreadPool::~ThreadPool()
{
	if (m_bRunning)
	{
		stop();
	}
}

bool ThreadPool::start(void)
{
	for (int i = 0; i < m_nThreadNumber; i++)
	{
		m_vecThread.push_back(std::make_shared<std::thread>(std::bind(&ThreadPool::threadWork, this)));//ѭ�������߳�       
	}
	return true;
}

bool ThreadPool::stop(void)
{
	if (m_bRunning)
	{
		m_bRunning = false;
		m_condition_empty.notify_all();
		for (auto t : m_vecThread)
		{
			if (t->joinable())
			{
				t->join();  //ѭ���ȴ��߳���ֹ		
			}
		}
	}
	return true;
}

bool ThreadPool::IsRunning()
{
	return m_bRunning;
}

ThreadPool * netlib::ThreadPool::GetInstance()
{

	if (NULL != s_pThreadPool)
	{
		return s_pThreadPool;
	}

	s_pThreadPool = new ThreadPool(3);
	s_pThreadPool->start();
	//atexit(Destory);
	return s_pThreadPool;


}


/*
*	Function:		append
*	Explanation:	��ӹ���������
*	Input:			ThreadTask			����

bPriority	�Ƿ�Ҫ����ִ��

*	Return:			true �ɹ� false ʧ��
*/
bool ThreadPool::append(ThreadTask task, bool bPriority /* = false */)
{
	if (m_bRunning == false)
	{
		return false;
	}
	std::lock_guard<std::mutex> guard(m_mutex);
	m_taskList.push_front(task);   //������������������
	m_condition_empty.notify_one();//����ĳ���߳���ִ�д�����
	return true;
}

void ThreadPool::threadWork(void)
{
	ThreadTask task = nullptr;
	while (m_bRunning)
	{
		{
			std::unique_lock<std::mutex> _lock(m_mutex);
			task = nullptr;
			if (m_taskList.empty())
			{
				m_condition_empty.wait(_lock);  //�ȴ���������������

			}
			if (!m_taskList.empty())
			{
				task = m_taskList.front();  //����������л�ȡ�ʼ����
				m_taskList.pop_front();     //��ȡ�ߵ����񵯳��������			
			}
			else
			{
				continue;
			}
		}
		if (task != nullptr && m_bRunning)
		{
			task(); //ִ������
		}
	}
	return;
}
