#include "InteractGlobal.h"

#include "IDisconnectResponse.h"

namespace Interact
{

IDisconnectResponse::IDisconnectResponse(const char *sid)
    : m_respLen(0)
{
    memcpy(m_sid, sid, strlen(sid));
}

IDisconnectResponse::~IDisconnectResponse()
{
}

void IDisconnectResponse::GetContent(uint8_t **content, size_t *contentLen)
{
    const char* response = "typ=disconnect\n";
    m_respLen = strlen(response);
    strcpy(m_response, response);
    m_response[m_respLen] = 0;
    *contentLen = m_respLen;
    *content = (uint8_t *)m_response;
}

} // namespace Interact

