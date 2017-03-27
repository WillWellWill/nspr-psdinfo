#include "InteractGlobal.h"

#include "InteractLiveSession.h"

namespace Interact
{

InteractLiveSession::InteractLiveSession(char *url)
{
    m_app[0] = 0;
    m_liveID[0] = 0;
    m_host[0] = 0;
    m_sessionID[0] = 0;
    sscanf(url, "http://%s/%s/%s", m_host, m_app, m_liveID);
    InteractCopy(m_url, sizeof(m_url), url);
}

InteractLiveSession::~InteractLiveSession()
{
}
    
int InteractLiveSession::BindSessionID(char *sid)
{
    int l = strnlen(sid, MAX_SESSION_ID_LEN - 1);
    memcpy(&m_sessionID[0], sid, l);
    m_sessionID[l] = 0;
    return INTERACT_OK;
}

void InteractLiveSession::UpdateMedata(Metadata *metadata)
{
    if (!metadata)
        return;
    m_metadata = *metadata;
}
    
void InteractLiveSession::UpdateMedata(char *metadata)
{
}

} // namespace Interact

