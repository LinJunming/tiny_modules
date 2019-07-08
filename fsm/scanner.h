#ifndef __SCANNER__
#define __SCANNER__

typedef enum{
	SCAN_IDLE,
	SCAN_FOREIGN_CHANNEL,
	SCAN_HOME_CHANNEL
} scanner_state_id;

typedef enum{
	EVENT_0,
	EVENT_1,
	EVENT_2,
	EVENT_F
} scanner_event;

#endif