#ifndef __INTERACT_CLIENT_IMP_H__
#define __INTERACT_CLIENT_IMP_H__

namespace Interact
{

class InteractResource;
class InteractProtocolParser;
class InteractProtocolPacker;
class InteractLiveSession;
class MessageBuffer;
class InteractMessage;
class InteractRequest;
class InteractResponse;
class InteractClientCB;
class InteractNotify;
class InteractClientImp
{
public:
    InteractClientImp(char *url, InteractClientCB *cb);
    virtual ~InteractClientImp();

    int DataIn(const uint8_t *data, size_t len);

    int Connect(Metadata *mdata);
    int Play();
    int Publish();
    int Ping();
    int Close();
    
    virtual InteractResource *IR() { return m_ir; }
    int GetErrorCode() { return m_errorCode; }

private:
    InteractResource *m_ir;
    InteractProtocolParser *m_protocolParser;
    InteractProtocolPacker *m_protocolPacker;
    InteractLiveSession *m_session;
    MessageBuffer *m_messageBuffer;
    
    InteractClientCB *m_cb;
    int m_errorCode;

private:
    void ProcessOutgoingMessage(InteractMessage *message);
    void ProcessOutgoingStatus(InteractResponse *response);
    void ProcessOutgoingNotify(InteractNotify *notify);

}; // class InteractClientImp

} // namespace Interact


#endif // ifndef __INTERACT_CLIENT_IMP_H__

