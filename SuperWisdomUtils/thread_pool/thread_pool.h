#pragma once
#pragma execution_character_set("utf-8")

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <memory>
#include <functional>



namespace netlib
{
	class ThreadPool
	{
	public:
		typedef std::function<void(void )> ThreadTask;

		ThreadPool(int threadNumber);

		~ThreadPool();

		//������������������
		bool append(ThreadTask task, bool bPriority = false);

		//�����̳߳�
		bool start(void);

		//ֹͣ�̳߳�
		bool stop(void);

		// �̳߳��Ƿ�������
		bool IsRunning();


		// ��ȡ�̳߳�ʵ��
		static ThreadPool* GetInstance();

private:
		//�߳���ִ�еĹ�������
		void threadWork(void);

private:
		std::mutex m_mutex;                                        //������

		bool m_bRunning;                                           //�̳߳��Ƿ�������
		int m_nThreadNumber;                                       //�߳���

		std::condition_variable_any m_condition_empty;             //���������Ϊ��ʱ����������
		std::list<ThreadTask> m_taskList;                          //�������
		std::vector<std::shared_ptr<std::thread>> m_vecThread;     //���������̶߳���ָ��
	};
}

#define GSThreadPool_AddFun(x)	netlib::ThreadPool::GetInstance()->append(x)
#define GSThreadPool_Run()	netlib::ThreadPool::GetInstance()->start()