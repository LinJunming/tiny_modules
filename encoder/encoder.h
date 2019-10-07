#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <pthread.h>
#include <iostream>

// 任务信号
typedef enum{
	TASK_NONE,		// 无任务
	TASK_ASSIGNED,	// 任务发布
	TASK_DONE		// 任务完成
} TASK_SIGNAL;

class Encoder{
public:
	Encoder(){
		m_is_running = false;
		m_read_signal = TASK_NONE;
		m_write_signal = TASK_NONE;
	}
	~Encoder(){
		delete[] m_out_buf;
		m_is_running = false;
		Close();
	}
	void Init();
	void Close();
	bool IsRunning(){
		return m_is_running;
	}
	void Sync();
	void Encode();

	void ReadWait(TASK_SIGNAL signal);
	void WriteWait(TASK_SIGNAL signal);
	void ReadNotify(TASK_SIGNAL signal);
	void WriteNotify(TASK_SIGNAL signal);

private:
	char* 		m_out_buf;
	bool 		m_is_running;
	pthread_t 	m_read_thread_id;
	pthread_t 	m_write_thread_id;
	TASK_SIGNAL	m_read_signal;	// 通过这两个变量，分别实现主线程和读线程，主线程和写线程的同步（因为每个时刻，变量的写者只可能有一个，所以不上锁）
	TASK_SIGNAL	m_write_signal;

	void 		InitReadThreadArgs();
	void 		InitWriteThreadArgs();
};

#endif
