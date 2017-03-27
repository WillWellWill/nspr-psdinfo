#ifndef __poseidon_protocol_http_test__
#define __poseidon_protocol_http_test__

#include "InteractClient.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "InteractClient.h"

#include <stdio.h>
#include <string.h>


class GmockInteractClientCB  : public Interact::InteractClientCB
{
public:
    MOCK_METHOD2(DataOut, int(const uint8_t* data, size_t len));
    MOCK_METHOD2(OnStatus, int(Status status, Metadata *metadata));
    MOCK_METHOD2(Log, void(const uint8_t *logData, size_t logLen));
    
}; // class InteractClientCB

static Metadata playMetadata = {
    IC_MODE_PLAY,
    {
        512000,//int bitrate;
        IC_VIDEO_CODECID_H264,//int codecID;
        25,//int frameRate;
        IC_RES_VGA,//ICResulution resolution;
        
        50000,//int srcPort;
        50000,//int dstPort;
        166666,//int ssrc;
        0//int payloadType;
    },
    {
        32000,
        441000,//int sampleRate;
        16000,//int sampleSize;
        2,//int channelCnt;

        50002,//int srcPort;
        50002,//int dstPort;
        18888,//int ssrc;
        1//int payloadType;    
    }
};

const static int g_httpTestContentLength = 4096;
TEST(InteractClient, InteractClientTest) {
    GmockInteractClientCB *my_cb = new GmockInteractClientCB();
    InteractClient ic((char *)"http://127.0.0.1:1688/live/xyz", my_cb);
    ic.Connect(&playMetadata);
    printf("http: %s", content);
}
#endif // !__poseidon_protocol_http_test__
