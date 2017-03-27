#ifndef __INTERACT_DISCONNECT_REQUEST_H__
#define __INTERACT_DISCONNECT_REQUEST_H__

#include "InteractRequest.h"

namespace Interact
{

class IDisconnectRequest : public InteractRequest
{
public:
    IDisconnectRequest();
    IDisconnectRequest(const uint8_t *msg, size_t len);
    virtual ~IDisconnectRequest();

    virtual MsgType GetMsgType() { return DISCONNECT; };

private:

}; // class IDisconnectRequest

} // namespace Interact

#endif // ifndef __INTERACT_DISCONNECT_REQUEST_H__

