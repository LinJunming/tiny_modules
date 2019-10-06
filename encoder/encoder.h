#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <pthread.h>
#include <iostream>

class Encoder{
public:
	Encoder(){
		m_read_condition = false;
		m_write_condition = false;
	}
	~Encoder(){
		delete[] m_out_buf;
		m_read_condition = false;
		m_write_condition = false;
		Close();
	}
	void Init();
	void Close();
	bool IsReadThreadRunning(){
		return m_read_condition;
	}
	bool IsWriteThreadRunning(){
		return m_write_condition;
	}
private:
	char* 		m_out_buf;
	bool 		m_read_condition;
	bool 		m_write_condition;
	pthread_t 	m_read_thread_id;
	pthread_t 	m_write_thread_id;

	void 		InitReadThreadArgs();
	void 		InitWriteThreadArgs();
};

#endif
