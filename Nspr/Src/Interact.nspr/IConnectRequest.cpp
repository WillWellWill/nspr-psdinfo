#include "InteractGlobal.h"

#include "IConnectRequest.h"
#include "SessionDescription.h"

namespace Interact
{

IConnectRequest::IConnectRequest()
{
}

IConnectRequest::~IConnectRequest()
{

}

IConnectRequestLocal::IConnectRequestLocal(Metadata *md)
    : m_sessionDesc(new SessionDescription())
{
    m_metadata = *md;
    m_content[0] = 0;
    m_contentLen = 0;
}

IConnectRequestLocal::~IConnectRequestLocal()
{
    delete m_sessionDesc;
}

void IConnectRequestLocal::GetContent(uint8_t **content, size_t *contentLen)
{
    if (m_contentLen > 0) {
        *content = m_content;
        *contentLen = m_contentLen;
        return;
    }
    m_contentLen = m_sessionDesc->AssembleBy(&m_metadata, ( char *)&m_content[0], sizeof(m_content));
    *content = m_content;
    *contentLen = m_contentLen;
    IDebug("content len = %d", m_contentLen);
}

IConnectRequestRemote::IConnectRequestRemote()
    : m_sessionDesc(new SessionDescription())
    , m_contentLen(0)
    , m_metadata(nullptr)
{
}

IConnectRequestRemote::~IConnectRequestRemote()
{
    if (m_metadata) {
        delete m_metadata;
    }
    delete m_sessionDesc;
}

int IConnectRequestRemote::InitMessage(const uint8_t *content, size_t contentLen)
{
    m_contentLen = contentLen;
    if (contentLen != 0){
        if (contentLen >= (size_t)m_maxContentLen) {
            return INTERACT_ERROR;
        }
        memcpy(m_content, content, contentLen);
        m_content[m_contentLen] = 0;
    } else
        return INTERACT_ERROR;
    return INTERACT_OK;
}
Metadata *IConnectRequestRemote::GetMetadata()
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

