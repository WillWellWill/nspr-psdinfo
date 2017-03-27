#ifndef __INTERACT_ERROR_REPONSE_H__
#define __INTERACT_ERROR_REPONSE_H__

#include "InteractResponse.h"

namespace Interact
{

class IErrorResponse : public InteractResponse
{
public:
    IErrorResponse(int error);
    IErrorResponse(uint8_t *msg, size_t len);
    virtual ~IErrorResponse();
    virtual MsgType GetMsgType() { return ERROR; };
    virtual void GetContent(uint8_t **content, size_t *contentLen) {
        *content = (uint8_t*)m_errorMsg;
        *contentLen = m_contentLength; 
    }
    int GetErrorCode() const { return m_errorCode; }

private:
    int m_errorCode;
    static const size_t MAX_LENGTH = 1024;
    char m_errorMsg[MAX_LENGTH];
    size_t m_contentLength;
}; // class IErrorResponse

} // namespace Interact



#endif // ifndef __INTERACT_ERROR_REPONSE_H__

