#ifndef _TELEMCONFIG_PAGE_H_
#define _TELEMCONFIG_PAGE_H_
#include "telemetry.h"
struct telemconfig_page {
    guiObject_t *valueObj[TELEM_NUM_ALARMS];
    char str[25];
};
#endif
