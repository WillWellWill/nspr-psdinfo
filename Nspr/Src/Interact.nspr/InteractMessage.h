#ifndef __INTERACT_MESSAGE_H__
#define __INTERACT_MESSAGE_H__

namespace Interact
{
class InteractResource;
class InteractMessage : public InteractObject
{
public:
    InteractMessage() {}
    virtual ~InteractMessage() {}
    enum ReqType{
        UNKNOWN_REQ,
        REQUEST,
        RESPONSE,
        NOTIFY
    };
    enum MsgType
    {
        UNKNOWN = -1,
        CONNECT = 0,
        OPERATION,
        DISCONNECT,
        ERROR
    };

    
    virtual ReqType GetReqType() { return UNKNOWN_REQ; }
    virtual MsgType GetMsgType()  { return UNKNOWN; }
    
    virtual const char *GetUri() { return (const char *)"/live/abc"; }
    virtual const char *GetHost() { return (const char *)"127.0.0.1:1688"; }

    virtual void GetContent(uint8_t **content, size_t *contentLen) { (void)content; *contentLen = 0; }

protected:
}; // class InteractMessage
} // namespace Interact

#endif // ifndef __INTERACT_MESSAGE_H__

