#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include "fsm.h"

#define SM_PRINT(fmt, arg...) printk(KERN_EMERG fmt, arg)

h_fsm* fsm_create(const char* name, state_info* stateInfo, int stateNum)
{
	SM_PRINT("[%s:%d]\n", __func__, __LINE__);
	h_fsm*  hFsm = (h_fsm *)kmalloc(sizeof(h_fsm), GFP_KERNEL);
	if (hFsm)
	{
		hFsm->name = name;
		hFsm->stateInfo = stateInfo;
		hFsm->stateNum = stateNum;
	}
	return hFsm;
}

void fsm_dispatch(h_fsm* hFsm, int event)
{
	SM_PRINT("[%s:%d]\n", __func__, __LINE__);
}

void fsm_transit(h_fsm* hFsm, int state)
{
	SM_PRINT("[%s:%d]next state:%d\n", __func__, __LINE__, state);
	if (hFsm->stateInfo[hFsm->curState].exit != NULL)
	{
		hFsm->stateInfo[hFsm->curState].exit();	
	}
	else
	{
		SM_PRINT("State %d's exit func is null\n", hFsm->curState);	
	}

	hFsm->curState = state;
	
	if (hFsm->stateInfo[hFsm->curState].entry != NULL)
	{
		hFsm->stateInfo[hFsm->curState].entry();	
	}
	else
	{
		SM_PRINT("State %d's entry func is null\n", hFsm->curState);	
	}
}

void fsm_destroy(h_fsm* hFsm)
{
	SM_PRINT("[%s:%d]\n", __func__, __LINE__);
	if(hFsm)
	{
		kfree(hFsm);
	}
}