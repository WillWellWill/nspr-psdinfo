#ifndef __INTERACT_OPERATION_REPONSE_H__
#define __INTERACT_OPERATION_REPONSE_H__

#include "InteractResponse.h"

namespace Interact
{

class IOperationResponse : public InteractResponse
{
public:
    enum OpType
    {
        PLAY = 0,
        PUBLISH,
        PONG
    };

    IOperationResponse(OpType type);
    IOperationResponse(char *message, int len);
    virtual ~IOperationResponse();
    virtual MsgType GetMsgType() { return OPERATION; };

    OpType Operation() { return m_type; }

    virtual void GetContent(uint8_t **content, size_t *contentLen);
private:

    const static int m_maxMessageLength = 4096;

    char m_message[m_maxMessageLength];
    int m_len;
    OpType m_type;

    const static int m_maxSessionIDLen = 512;
    char m_response[1024];
    size_t m_respLen;
}; // class IOperationResponse

} // namespace Interact



#endif // ifndef __INTERACT_OPERATION_REPONSE_H__

