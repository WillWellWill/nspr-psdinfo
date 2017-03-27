#ifndef __INTERACT_NOTIFY_H__
#define __INTERACT_NOTIFY_H__

#include "InteractRequest.h"

namespace Interact
{

class InteractNotify : public InteractRequest
{
public:
    enum NotifyType{
        UNKNOWN,
        DISCONNECT,
    };

    InteractNotify(NotifyType type);
    InteractNotify(); 

    virtual int InitMessage(uint8_t *msg, size_t len);
    virtual ~InteractNotify();

    virtual ReqType GetReqType() { return NOTIFY; }
    virtual NotifyType GetNotifyType()  { return m_notifyType; }
    virtual void GetContent(uint8_t **content, size_t *contentLen);
private:
    NotifyType m_notifyType;
}; // class InteractRequest
} // namespace Interact

#endif // ifndef __INTERACT_NOTIFY_H__

