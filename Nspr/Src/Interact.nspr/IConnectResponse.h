#ifndef __INTERACT_CONNECT_REPONSE_H__
#define __INTERACT_CONNECT_REPONSE_H__

#include "InteractResponse.h"

namespace Interact
{

class SessionDescription;
class IConnectResponse : public InteractResponse
{
public:
    IConnectResponse();
    virtual ~IConnectResponse();
    virtual MsgType GetMsgType() { return CONNECT; };
    virtual Metadata *GetMetadata() = 0;

private:

}; // class IConnectResponse

class IConnectResponseLocal : public IConnectResponse
{
public:
    IConnectResponseLocal(const char *sid, Metadata *metadata);
    virtual ~IConnectResponseLocal();

    virtual Metadata *GetMetadata() { return &m_metadata; }
    virtual void GetContent(uint8_t **content, size_t *contentLen);
    virtual const char *SessionId() { return (const char *)&m_sid[0]; }

private:
    const static int m_maxContentLen = 4096;
    const static int m_maxSessionIdLen = 256;
    SessionDescription *m_sessionDesc;
    Metadata m_metadata;
    uint8_t m_content[m_maxContentLen];
    size_t m_contentLen;
    uint8_t m_sid[m_maxSessionIdLen];

}; // class IConnectResponseLocal

class IConnectResponseRemote : public IConnectResponse
{
public:
    IConnectResponseRemote(const uint8_t *content, size_t contentLen);
    virtual ~IConnectResponseRemote();

    virtual Metadata *GetMetadata();
    virtual void GetContent(uint8_t **content, size_t *contentLen) { *content = &m_content[0]; *contentLen = m_contentLen; }
    const char *SessionId();

private:
    const static int m_maxContentLen = 4096;
    const static int m_maxSessionIdLen = 256;
    SessionDescription *m_sessionDesc;
    uint8_t m_content[m_maxContentLen];
    const size_t m_contentLen;
    uint8_t m_sid[m_maxSessionIdLen];

    Metadata *m_metadata;

}; // class IConnectResponseRemote

} // namespace Interact


#endif // ifndef __INTERACT_CONNECT_REPONSE_H__

