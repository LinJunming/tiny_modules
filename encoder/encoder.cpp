#include "encoder.h"
#include <iostream>
#include <unistd.h>

void* ReadThread(void* args)
{
	Encoder* encoder = (Encoder*) args;
	while(encoder->IsRunning())
	{
		encoder->ReadWait(TASK_ASSIGNED);
		if (!encoder->IsRunning())
			break;

		std::cout << "ReadThread got signal..." << std::endl;

		std::cout << "ReadThread is working..." << std::endl;
		sleep(1);

		encoder->ReadNotify(TASK_DONE);
	}
	std::cout << "ReadThread stopped normally." << std::endl;
	return NULL;
}

void* WriteThread(void* args)
{
	Encoder* encoder = (Encoder*) args;
	while(encoder->IsRunning())
	{
    	encoder->WriteWait(TASK_ASSIGNED);
		if (!encoder->IsRunning())
			break;
		std::cout << "WriteThread got signal..." << std::endl;

		std::cout << "WriteThread is working..." << std::endl;
		sleep(1);

    	encoder->WriteNotify(TASK_DONE);
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
	m_is_running = true; // 允许运行
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

void Encoder::Sync()
{
    std::cout << "Syncing..." << std::endl;
	ReadNotify(TASK_ASSIGNED);

	ReadWait(TASK_DONE);
    std::cout << "Synced..." << std::endl;
}
void Encoder::Encode()
{
	std::cout << "Encoding..." << std::endl;
	WriteNotify(TASK_ASSIGNED);
	
	WriteWait(TASK_DONE);
	std::cout << "Encoded..." << std::endl;
}

void Encoder::ReadWait(TASK_SIGNAL signal){
	while(m_read_signal != signal && m_is_running);
	m_read_signal = TASK_NONE;
}

void Encoder::WriteWait(TASK_SIGNAL signal){
	while(m_write_signal != signal && m_is_running);
	m_write_signal = TASK_NONE;
}

void Encoder::ReadNotify(TASK_SIGNAL signal){
	m_read_signal = signal;
}

void Encoder::WriteNotify(TASK_SIGNAL signal){
	m_write_signal = signal;
}