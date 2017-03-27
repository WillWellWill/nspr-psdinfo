#include "InteractGlobal.h"
#include "InteractNotify.h"

namespace Interact {
InteractNotify::InteractNotify(NotifyType type)
{ 
    m_notifyType = type; 
}

InteractNotify::InteractNotify()
    : m_notifyType(UNKNOWN)
{
}

InteractNotify::~InteractNotify()
{
}
int InteractNotify::InitMessage(uint8_t *msg, size_t len)
{
    if (len >= (size_t)m_contentLen) {
        return INTERACT_ERROR;
    }
    memcpy(m_content, msg, len);
    m_content[len] = 0;
    char *start = strstr((char*)msg, "sid=");
    char *end = strstr(start, "\n");
    int s_len = end - start - 4;
    memcpy(m_sessionId, start + 4, s_len);
    m_sessionId[s_len] = 0;
    
    char type[30];
    start = strstr((char*)msg, "nty=");
    end = strstr(start, "\n");
    s_len = end - start - 4;
    if (s_len >= 30) {
        return INTERACT_ERROR;
    }
    memcpy(type, start + 4, s_len);
    type[s_len] = 0;
    if (!strncmp(type, "disconnect", 10)) {
        m_notifyType = DISCONNECT;
    }
    else {
        m_notifyType = UNKNOWN;
    }
    return INTERACT_OK;
}

void InteractNotify::GetContent(uint8_t **content, size_t *contentLen) {
    std::string actionType;
    switch (m_notifyType)
    {
        case DISCONNECT: actionType = "disconnect"; break;
        default: actionType = "unknown";
    }
    snprintf(&m_content[0], m_contentLen, "sid=%s\nnty=%s", m_sessionId, actionType.c_str());
    *content = (uint8_t *)m_content;
    *contentLen = strnlen(m_content, m_contentLen-1);
}

}
