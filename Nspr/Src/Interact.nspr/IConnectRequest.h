#ifndef __INTERACT_CONNECT_REQUEST_H__
#define __INTERACT_CONNECT_REQUEST_H__

#include "InteractRequest.h"

namespace Interact
{

class SessionDescription;
class IConnectRequest : public InteractRequest
{
public:
    IConnectRequest();
    virtual ~IConnectRequest();

    virtual MsgType GetMsgType() { return CONNECT; };
    virtual Metadata *GetMetadata() = 0;

private:

}; // class IConnectRequest

class IConnectRequestLocal : public IConnectRequest
{
public:
    IConnectRequestLocal(Metadata *metadata);
    virtual ~IConnectRequestLocal();

    virtual Metadata *GetMetadata() { return &m_metadata; }
    virtual void GetContent(uint8_t **content, size_t *contentLen);

private:
    SessionDescription *m_sessionDesc;
    Metadata m_metadata;
    const static int m_maxContentLen = 4096;
    uint8_t m_content[m_maxContentLen];
    size_t m_contentLen;
}; // class IConnectRequestLocal

class IConnectRequestRemote : public IConnectRequest
{
public:
    IConnectRequestRemote();
    virtual ~IConnectRequestRemote();
    
    virtual int InitMessage(const uint8_t *content, size_t contentLen);
    virtual Metadata *GetMetadata();
    virtual void GetContent(uint8_t **content, size_t *contentLen) { *content = &m_content[0]; *contentLen = m_contentLen; }

private:
    SessionDescription *m_sessionDesc;
    const static int m_maxContentLen = 4096;
    uint8_t m_content[m_maxContentLen];
    size_t m_contentLen;

    Metadata *m_metadata;

}; // class IConnectRequestRemote

} // namespace Interact

#endif // ifndef __INTERACT_CONNECT_REQUEST_H__

