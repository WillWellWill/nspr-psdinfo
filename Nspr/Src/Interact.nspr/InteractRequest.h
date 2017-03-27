#ifndef __INTERACT_REQUEST_H__
#define __INTERACT_REQUEST_H__

#include "InteractMessage.h"

namespace Interact
{

class InteractResource;
class InteractRequest : public InteractMessage
{
public:
    InteractRequest() {}
    virtual ~InteractRequest() {}

    virtual ReqType GetReqType() { return REQUEST; }
    virtual void GetContent(uint8_t **content, size_t *contentLen) {
        snprintf(&m_content[0], m_contentLen, "sid=%s", m_sessionId);
        *content = (uint8_t *)m_content;
        *contentLen = strnlen(m_content, m_contentLen-1);
    }

    virtual const char *GetHost() { return m_host; }
    virtual const char *GetUri() { return &m_uri[0]; }
    virtual const char *GetSessionId() { return &m_sessionId[0]; }

    void SetHost(const char* host) { strcpy(m_host, host); }
    void SetUri(const char *uri) { strcpy(m_uri, uri); }
    void SetUrl(const char *url) { 
        char *pointer = (char *)strstr(url, "://");
        assert(pointer);
        pointer += 3;
        char *host_end = (char *)strstr(pointer, "/");
        assert(host_end);
        size_t hl = host_end - pointer;
        assert(hl < m_maxUriLen - 1);
        memcpy(m_host, pointer, hl);
        m_host[hl] = 0;
        pointer = pointer + hl + 1;
        size_t ul = strnlen(pointer, m_maxUriLen);
        assert(ul < m_maxUriLen - 1);
        memcpy(m_uri, pointer, ul);
        m_uri[ul] = 0;
    }

    void SetSessionId(const char *sessionid) { memcpy(m_sessionId, sessionid, strlen(sessionid) + 1); }
protected:
    const static int m_maxUriLen = 1024;
    const static int m_contentLen = 1024;
    char m_url[m_maxUriLen];
    char m_uri[m_maxUriLen];
    char m_host[m_maxUriLen];
    char m_sessionId[m_maxUriLen];
    char m_content[m_contentLen];

}; // class InteractRequest
} // namespace Interact

#endif // ifndef __INTERACT_REQUEST_H__

