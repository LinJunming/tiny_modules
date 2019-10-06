#include "encoder.h"
#include <iostream>
#include <unistd.h>

void* ReadThread(void* args)
{
	Encoder* encoder = (Encoder*) args;
	while(encoder->IsReadThreadRunning())
	{
		std::cout << "ReadThread is working..." << std::endl;
		sleep(1);
	}
	std::cout << "ReadThread stopped normally." << std::endl;
	return NULL;
}

void* WriteThread(void* args)
{
	Encoder* encoder = (Encoder*) args;
	while(encoder->IsWriteThreadRunning())
	{
		std::cout << "WriteThread is working..." << std::endl;
		sleep(1);
	}
	std::cout << "WriteThread stopped normally." << std::endl;
	return NULL;
}

void Encoder::Init()
{
	m_out_buf = new char[128];
	if (m_out_buf == nullptr){
		std::cout << "Failed to malloc output buffer" << std::endl;
	}
	// 创建两个线程
	m_read_condition = true; // 允许运行
	m_write_condition = true;
	pthread_create(&m_read_thread_id, NULL, ReadThread, (void*)this);
	pthread_create(&m_write_thread_id, NULL, WriteThread, (void*)this);
	std::cout << "Init encoder Successfully." << std::endl;
}

void Encoder::Close()
{
	std::cout << "Closing encoder..." << std::endl;
	pthread_join(m_read_thread_id, NULL);
	pthread_join(m_write_thread_id, NULL);
	std::cout << "Closed encoder." << std::endl;
}