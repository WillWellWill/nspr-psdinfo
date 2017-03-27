#ifndef __INTERACT_CONNECT_DEF_H__
#define __INTERACT_CONNECT_DEF_H__

#define SOCK_BUFFER_SIZE 1024

enum ICResulution
{
    IC_RES_UNKOWN = 0,
    IC_RES_180P ,
    IC_RES_360P,
    IC_RES_CIF,
    IC_RES_4CIF,
    IC_RES_VGA,
    IC_RES_720P,
    IC_RES_1080P,
};

enum ICMode
{
    IC_MODE_UNKOWN = 0,
    IC_MODE_PUBLISH,
    IC_MODE_PLAY,
};

enum ICCodeID
{
    IC_CODECID_UNKOWN = 0,
    IC_VIDEO_CODECID_H264,
    IC_VIDEO_CODECID_H265,
};

#endif
