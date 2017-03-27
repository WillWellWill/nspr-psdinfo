#ifndef __INTERACT_LIVE_SESSION_H__
#define __INTERACT_LIVE_SESSION_H__

namespace Interact
{
class InteractLiveSession : public InteractObject
{
public:
    InteractLiveSession(char *url);
    virtual ~InteractLiveSession();

    const char *Url() { return &m_url[0]; }
    const char *AppName() { return &m_app[0]; }
    const char *LiveID() { return &m_liveID[0]; }
    const char *Host() { return &m_host[0]; }
    const char *SessionId() { return &m_sessionID[0]; }
    int BindSessionID(char *sid);
    void UpdateMedata(Metadata *metadata);
    void UpdateMedata(char *metadata);

private:
    const static int MAX_URL_LEN = 4096;
    const static int MAX_APPNAME_LEN = 1024;
    const static int MAX_LIVE_ID_LEN = 1024;
    const static int MAX_HOST_LEN = 128;
    const static int MAX_SESSION_ID_LEN = 128;

    char m_url[MAX_URL_LEN];
    char m_app[MAX_APPNAME_LEN];
    char m_liveID[MAX_LIVE_ID_LEN];
    char m_host[MAX_HOST_LEN];
    char m_sessionID[MAX_SESSION_ID_LEN];
    Metadata m_metadata;

private:

}; // class InteractLiveSession
} // namespace Interact


#endif // ifndef __INTERACT_LIVE_SESSION_H__

