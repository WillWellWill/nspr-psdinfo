#include "InteractGlobal.h"
#include "ErrorCode.h"

#include "IErrorResponse.h"
#include <string.h>

//extern static const ErrorCode g_ErrorEntity[];

namespace Interact
{

IErrorResponse::IErrorResponse(int error):m_contentLength(0)
{
    if (error < ERROR_UNKNOW || error >= ERROR_UNKNOW + ERROR_COUNT) {
        m_errorCode = ERROR_UNKNOW;
    } else {
        m_errorCode = error;
    }
    snprintf(m_errorMsg, MAX_LENGTH, "error=%d\nerrmsg=%s", error, g_ErrorEntity[error - 10000].msg);
    m_contentLength = strlen(m_errorMsg);       
}

IErrorResponse::IErrorResponse(uint8_t *msg, size_t len): m_contentLength(0)
{
    if (len >=  MAX_LENGTH) {
        IError("error the error response length is too max");
        return;
    }
    char message[MAX_LENGTH];
    memcpy(message, msg, len);
    message[len] = 0;
    char* error = strstr(message,"error=");
    char* er_end = strstr(error, "\n");
    char code[30];
    int codelen = er_end - error;
    if (codelen >= 30)
        return;
    memcpy(code, error + 6, codelen);
    code[codelen] = 0;
    m_errorCode = atoi(code);

    size_t msglen = len - codelen - 2;
    if (msglen > MAX_LENGTH)
        return;
    memcpy(m_errorMsg, er_end+2, msglen);
    m_errorMsg[msglen] = 0;
}

IErrorResponse::~IErrorResponse()
{

}

} // namespace Interact

