#ifndef __INTERACT_RESPONSE_H__
#define __INTERACT_RESPONSE_H__

#include "InteractMessage.h"

namespace Interact
{

class InteractResource;
class InteractResponse : public InteractMessage
{
public:
    InteractResponse() {}
    virtual ~InteractResponse() {}

    virtual MsgType GetMsgType() = 0;

    virtual ReqType GetReqType() { return RESPONSE; }
    virtual const char *SessionId() { return "ABCD-ABCD-0123-0123-4567-4567-ABCD-ABCD"; }

}; // class InteractResponse
} // namespace Interact

#endif // ifndef __INTERACT_RESPONSE_H__

