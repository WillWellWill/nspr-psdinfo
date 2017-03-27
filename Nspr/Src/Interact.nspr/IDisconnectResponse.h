#ifndef __INTERACT_DISCONNECT_REPONSE_H__
#define __INTERACT_DISCONNECT_REPONSE_H__

#include "InteractResponse.h"

namespace Interact
{

class IDisconnectResponse : public InteractResponse
{
public:
    IDisconnectResponse(const char *sid);
    virtual ~IDisconnectResponse();
    virtual MsgType GetMsgType() { return DISCONNECT; };
    
    virtual void GetContent(uint8_t **content, size_t *contentLen);

private:
    const static int m_maxSessionIDLen = 512;
    char m_sid[m_maxSessionIDLen];
    char m_response[1024];
    size_t m_respLen;

}; // class IDisconnectResponse

} // namespace Interact



#endif // ifndef __INTERACT_DISCONNECT_REPONSE_H__

