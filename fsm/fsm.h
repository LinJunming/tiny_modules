#ifndef __FSM__
#define __FSM__

typedef struct
{
	int stateId;
	void (*stateEvent)(void);
	void (*entry)(void);
	void (*exit)(void);
} state_info;

typedef struct fsm_handler
{
	const char* name;
	state_info* stateInfo;
	int stateNum;
	int curState;
} h_fsm;

h_fsm* fsm_create(const char* name, state_info* stateInfo, int stateNum);
void fsm_dispatch(h_fsm* hFsm, int event);
void fsm_transit(h_fsm* hFsm, int state);
void fsm_destroy(h_fsm* hFsm);

#endif