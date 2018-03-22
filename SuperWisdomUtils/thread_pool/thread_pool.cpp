#pragma once
#pragma execution_character_set("utf-8")

#include "thread_pool.h"
#include <stdio.h>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <windows.h>
#include <iostream>
using namespace netlib;

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
	std::cout << "start" << std::endl;

	return true;
}

bool ThreadPool::stop(void)
{
	std::cout << "stop" << std::endl;
	if (m_bRunning)
	{
		m_bRunning = false;
		for (auto t : m_vecThread)
		{			
			t->join();  //ѭ���ȴ��߳���ֹ			
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
	static ThreadPool*		s_pThreadPool = NULL;

	if (NULL != s_pThreadPool)
	{
		return s_pThreadPool;
	}

	s_pThreadPool = new ThreadPool(10);
	s_pThreadPool->start();
	return s_pThreadPool;

}


/*
*	Function:		append
*	Explanation:	��ӹ���������
*	Input:			ThreadTask			����

bPriority	�Ƿ�Ҫ����ִ��

*	Return:			true �ɹ� false ʧ��
*/
bool ThreadPool::append(ThreadTask task,  bool bPriority /* = false */)
{
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
			std::lock_guard<std::mutex> guard(m_mutex);
			if (m_taskList.empty())
			{
				m_condition_empty.wait(m_mutex);  //�ȴ���������������
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
		task(); //ִ������
	}
}
