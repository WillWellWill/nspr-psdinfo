#ifndef __ERROR_CODE_H__
#define __ERROR_CODE_H__

typedef struct {
	int code;
	const char* msg;
} ErrorCode;

const int ERROR_UNKNOW = 10000;
const int ERROR_ID_INVALID = 10001;
const int ERROR_MEDIA = 10002;
const int ERROR_RESOURCES_LOW = 10003;
const int ERROR_PARAM_ERROR = 10004;
const int ERROR_COUNT = 5;

static const ErrorCode g_ErrorEntity[ERROR_COUNT]={
	{ERROR_UNKNOW, "Unknow error!"},
	{ERROR_ID_INVALID, "The live id not exist!"},
	{ERROR_MEDIA, "Media Error!"},
	{ERROR_RESOURCES_LOW, "The resources is low!"},
	{ERROR_PARAM_ERROR, "Param error!"}
};

#endif // __APP_CORE_H__

