#include "InteractGlobal.h"

#include "IConnectResponse.h"
#include "SessionDescription.h"

namespace Interact
{

IConnectResponse::IConnectResponse()
{

}

IConnectResponse::~IConnectResponse()
{

}

IConnectResponseLocal::IConnectResponseLocal(const char *sid, Metadata *metadata)
    : m_sessionDesc(new SessionDescription())
{
    memcpy(m_sid, sid, strlen(sid) + 1 < sizeof(m_sid) ? strlen(sid) + 1 : sizeof(m_sid) - 1);
    m_metadata = *metadata;
    m_contentLen = 0;
}

IConnectResponseLocal::~IConnectResponseLocal()
{
    delete m_sessionDesc;
}
    
void IConnectResponseLocal::GetContent(uint8_t **content, size_t *contentLen)
{
    if (m_contentLen > 0) {
        *content = m_content;
        *contentLen = m_contentLen;
        return;
    }
    m_contentLen = m_sessionDesc->AssembleBy((const char *)&m_sid[0], "connect", &m_metadata, (char *)&m_content[0], sizeof(m_content));
    *content = m_content;
    *contentLen = m_contentLen;
}

IConnectResponseRemote::IConnectResponseRemote(const uint8_t *content, size_t contentLen)
    : m_sessionDesc(new SessionDescription())
    , m_contentLen(contentLen)
    , m_metadata(nullptr)
{
    m_sid[0] = 0;
    memcpy(m_content, content, contentLen);
    m_content[m_contentLen] = 0;
}

IConnectResponseRemote::~IConnectResponseRemote()
{
    if (m_metadata) {
        delete m_metadata;
    }
    delete m_sessionDesc;
}
    
const char *IConnectResponseRemote::SessionId()
{
    if (m_sid[0]) {
        return (const char *)&m_sid[0];
    }
    size_t sidLen = 0;
    const char *sid = m_sessionDesc->SessionIdOf((char *)m_content, &sidLen);
    if (sidLen) {
        memcpy(m_sid, sid, sidLen);
        m_sid[sidLen] = 0;
    }
    return (const char *)&m_sid[0];
}

Metadata *IConnectResponseRemote::GetMetadata()
{
    if (m_metadata) {
        return m_metadata;
    }
    m_metadata = new Metadata();
    memset(m_metadata, 0, sizeof(Metadata));
    m_sessionDesc->MediaDescOf((char *)&m_content[0], m_metadata);
    return m_metadata;
}

} // namespace Interact

