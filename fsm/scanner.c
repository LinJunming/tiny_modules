#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h> 
#include "scanner.h"
#include "fsm.h"

typedef struct timer_list os_timer_t;

#define OS_SET_TIMER(timer, _expires, _data) do {\
			timer.expires = msecs_to_jiffies(_expires)+jiffies;\
			timer.data = (unsigned long)_data;\
			mod_timer(&timer, timer.expires);\
		} while(0);
#define SCANNER_PRINT(fmt, arg...) printk(KERN_EMERG fmt, arg)
#define HOME_CHANNEL_DWELL 		1000
#define FOREIGN_CHANNEL_DWELL 	1000
#define IDLE_TIME			 	6000
static const char* scannerName = "ScannerSM";

int scanner_destroy(void);

typedef struct scanner
{
	h_fsm* scannerFsm;
	os_timer_t scannerTimer;
} scanner;

scanner ieee80211_2g_scanner;

void scanner_idle_event(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);	
}
void scanner_home_channel_entry(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
	OS_SET_TIMER(ieee80211_2g_scanner.scannerTimer, HOME_CHANNEL_DWELL, EVENT_0);
}
void scanner_home_channel_event(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);	
}
void scanner_home_channel_exit(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);	
}
void scanner_foreign_channel_entry(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);	
	OS_SET_TIMER(ieee80211_2g_scanner.scannerTimer, FOREIGN_CHANNEL_DWELL, EVENT_1);
}
void scanner_foreign_channel_event(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);	
}
void scanner_foreign_channel_exit(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);	
}

void scanner_event_handler(unsigned long event)
{
	SCANNER_PRINT("EVENT RECVD:%lu\n", event);
	switch (event)
	{
	case EVENT_0:
		SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
		fsm_transit(ieee80211_2g_scanner.scannerFsm, SCAN_FOREIGN_CHANNEL);
		break;
	case EVENT_1:
		SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
		fsm_transit(ieee80211_2g_scanner.scannerFsm, SCAN_HOME_CHANNEL);
		break;
	case EVENT_F:
		SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
		scanner_destroy();
		break;
	default:
	break;
	}
}

static state_info scannerStateInfo[] = {
	{
		SCAN_IDLE,
		scanner_idle_event,
		NULL,
		NULL,
	},
	{
		SCAN_FOREIGN_CHANNEL,
		scanner_foreign_channel_event,
		scanner_foreign_channel_entry,
		scanner_foreign_channel_exit,
	},
	{
		SCAN_HOME_CHANNEL,
		scanner_home_channel_event,
		scanner_home_channel_entry,
		scanner_home_channel_exit,
	}
};

int scanner_start(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
	OS_SET_TIMER(ieee80211_2g_scanner.scannerTimer, IDLE_TIME, EVENT_0);
	return 0;
}

int scanner_init(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
	ieee80211_2g_scanner.scannerFsm = fsm_create(scannerName, scannerStateInfo, sizeof(scannerStateInfo)/sizeof(state_info));
	if (ieee80211_2g_scanner.scannerFsm != NULL)
	{
		ieee80211_2g_scanner.scannerFsm->curState = SCAN_IDLE;
	}
	init_timer(&ieee80211_2g_scanner.scannerTimer);
	ieee80211_2g_scanner.scannerTimer.function = scanner_event_handler;
	add_timer(&ieee80211_2g_scanner.scannerTimer);
	// ieee80211_2g_scanner.scannerTimer.data = 0;
	// ieee80211_2g_scanner.scannerTimer.expires = jiffies+5000;
	scanner_start();
	return 0;
}

int scanner_destroy(void)
{
	SCANNER_PRINT("[%s:%d]\n", __func__, __LINE__);
	del_timer(&ieee80211_2g_scanner.scannerTimer);
	fsm_destroy(ieee80211_2g_scanner.scannerFsm);
	ieee80211_2g_scanner.scannerFsm = NULL;
	return 0;
}

module_init(scanner_init);
module_exit(scanner_destroy);