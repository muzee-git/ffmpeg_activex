#ifndef FF_MMS_PROTOCOL_H
#define FF_MMS_PROTOCOL_H

#include "mmsx.h"

struct MMSProtocol;
typedef struct MMSProtocol MMSProtocol;

typedef struct
{
	mmsx_t *mms_instance;
    char path[512];
    char host[256];
	char query[256];
    int port;
	int bandwidth;
	//
    URLContext *mms_hd;
	//
} MMSContext;

#endif
