#include <stdio.h>
#include "avformat.h"
#include "mms.h"
#include "mms_protocol.h"
#include "mmsx.h"

#define MMS_DEBUG_LEVEL 2

int gStopFFMPEG = 0;

/**
 * Public API exposed through the URLProtocol
 */

/** Open a MMST/MMSH connection */
static int ff_mms_open(URLContext *h, const char *uri, int flags)
{
    char protocol[16];
    char authorization[64];
    MMSContext *mms;
	//
#if (MMS_DEBUG_LEVEL>0)
    fprintf(stderr, "mms_open\n");
#endif
	//
    mms = av_malloc(sizeof(MMSContext));
    if (!mms)
        return AVERROR(ENOMEM);
    memset(mms, 0, sizeof(MMSContext));
    h->priv_data = mms;
    h->is_streamed = 1;

    url_split(protocol, sizeof(protocol), authorization, sizeof(authorization), mms->host, sizeof(mms->host),
              &mms->port, mms->path, sizeof(mms->path), uri);

	/*
    if(strcmp(protocol, "mmsh") == 0) {
        mms->protocol = &mmsh_mmsprotocol;
    } else if (strcmp(protocol, "mms") == 0 || strcmp(protocol, "mmst") == 0) {
        mms->protocol = &mmst_mmsprotocol;
    } else {
        goto fail;
    }
	 */

    if(mms->port<0)
	{
        //mms->port = mms->protocol->default_port;
		mms->port = 0; // set by mmsx( mmsh/mms )
	}
	mms->bandwidth = 128*1024;
	//
    if(strcmp(protocol, "mmsh") == 0)
	{
		mmsx_t *mmsx = calloc(1, sizeof(mmsx_t));

		if( mmsx )
		{
			mmsx->connection_h = mmsh_connect(NULL, NULL, uri, mms->host, mms->path, NULL, mms->port, mms->bandwidth);
			if( mmsx->connection_h == NULL )
			{
				free(mmsx);
				mmsx = NULL;
			}
		}
		mms->mms_instance = mmsx;
	}
	else
	{
		mms->mms_instance = mmsx_connect(NULL, NULL, uri, mms->host, mms->path, NULL, mms->port, mms->bandwidth);
	}
	/*
	// Qing's Patch
	if( mms->mms_instance->connection != null )
		mms->port = mms->mms_instance->connection->port;
	if( mms->mms_instance->connection != null )
		mms->port = mms->mms_instance->connection_h->port;
		*/
	//
    if( mms->mms_instance == NULL )
	{
		av_free(mms);
#if (MMS_DEBUG_LEVEL>0)
		fprintf(stderr, "mms_open failed\n");
#endif
        return AVERROR(EIO);
	}
#if (MMS_DEBUG_LEVEL>0)
	fprintf(stderr, "mms_open success\n");
#endif
    return 0;
}

static int ff_mms_close(URLContext *h)
{
    MMSContext *mms = (MMSContext *) h->priv_data;
	//
#if (MMS_DEBUG_LEVEL>0)
    fprintf(stderr, "mms_close\n");
#endif
	//
	mmsx_close(mms->mms_instance);
	//
#if (MMS_DEBUG_LEVEL>0)
    fprintf(stderr, "done with mms_close\n");
#endif
	//
    av_free(mms);
    h->priv_data = NULL;
    return 0;
}

/** Read ASF data through the protocol. */
static int ff_mms_read(URLContext *h, uint8_t *buf, int size)
{
    MMSContext *mms = h->priv_data;
    int result = 0;
	//
	result = mmsx_read(NULL, mms->mms_instance, buf, size);
	//
	if( result < 0 )
	{
#if (MMS_DEBUG_LEVEL>0)
        fprintf(stderr, "mms_read: IO Error, returning AVERROR_IO!\n");
#endif
        result = AVERROR(EIO);		
    } 
	else
	{
#if (MMS_DEBUG_LEVEL>0)
        fprintf(stderr, "mms_read: %d bytes read\n", result);
#endif
    }
    return result;
}

typedef long offset_t;

/** Seek in the ASF stream. */
static offset_t ff_mms_seek(URLContext *h, offset_t offset, int whence)
{
    MMSContext *mms = h->priv_data;
	//
	return (offset_t) mmsx_seek (NULL, mms->mms_instance, offset, whence);
}

/** Generic MMS.
 * TODO: should try mmsu, mmst, mmsh and possibly rtsp in turn
 */
URLProtocol mms_protocol = {
    "mms",
    ff_mms_open,
    ff_mms_read,
    NULL, // write
    ff_mms_seek,
    ff_mms_close,
};

URLProtocol mmsh_protocol = {
    "mmsh",
    ff_mms_open,
    ff_mms_read,
    NULL, // write
    ff_mms_seek,
    ff_mms_close,
};
