#ifndef __INTERACT_CLIENT_H__
#define __INTERACT_CLIENT_H__

#include "InteractLog.h"

namespace Interact
{

class InteractClientImp;

class InteractClientCB : public InteractLog
{
public:
    virtual ~InteractClientCB() {}
    enum Status
    {
        INT_ERROR = -1,
        CONNECT_DONE = 0,
        PLAYING,
        PUBLISHING,
        DESTROYED,
        PONG
    };

    enum Notify{
        NOTIFY_UNKNOW = -1,
        NOTIFY_DISCONNECT
    };

    virtual int DataOut(const uint8_t *data, size_t len) = 0;
    virtual int OnStatus(Status status, Metadata *metadata) = 0;
    virtual int OnNotify(Notify status, const uint8_t *msg, size_t len) = 0;
    virtual void Log(const uint8_t *logData, size_t logLen) = 0;
    
}; // class InteractClientCB

class InteractClient
{
public:
    InteractClient(char *url, InteractClientCB *cb);
    ~InteractClient();

    int DataIn(const uint8_t *data, size_t len);

    int Connect(Metadata *mdata);
    int Play();
    int Publish();
    int Ping();
    int Close();

private:
    InteractClientImp *m_imp;
}; // class InteractClient

} // namespace Interact


#endif // ifndef __INTERACT_CLIENT_H__

