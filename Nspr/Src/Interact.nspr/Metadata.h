#ifndef __INTERACT_METADATA_h__
#define __INTERACT_METADATA_h__
#include "def.h"

namespace Interact{
struct Metadata
{
    int mode;
    struct
    {
        int bitrate;
        int codecID;
        int frameRate;
        int resolution;
        
        int srcPort;
        int dstPort;
        int ssrc;
        int payloadType;
    } v;

    struct
    {
        int bitrate;
        int codecID;
        int sampleRate;
        int sampleSize;
        int channelCnt;

        int srcPort;
        int dstPort;
        int ssrc;
        int payloadType;
    } a;
};
}

#endif
