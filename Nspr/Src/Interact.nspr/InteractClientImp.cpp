#include "InteractGlobal.h"

#include "InteractClientImp.h"
#include "InteractResource.h"
#include "InteractProtocolParser.h"
#include "InteractProtocolPacker.h"
#include "InteractLiveSession.h"
#include "MessageBuffer.h"
#include "InteractRequest.h"
#include "InteractResponse.h"
#include "InteractNotify.h"
#include "InteractClient.h"
#include "IConnectResponse.h"
#include "IOperationResponse.h"
#include "IConnectRequest.h"
#include "IOperationRequest.h"
#include "IDisconnectRequest.h"
#include "IErrorResponse.h"

namespace Interact
{

InteractClientImp::InteractClientImp(char *url, InteractClientCB *cb)
    : m_ir(new InteractResource(cb))
    , m_cb(cb)
    , m_errorCode(0)
{
    m_protocolParser = new InteractProtocolParser(m_ir);
    m_protocolPacker = new InteractProtocolPacker(m_ir);
    m_session = new InteractLiveSession(url);
    m_messageBuffer = new MessageBuffer(m_ir, m_protocolParser);
}

InteractClientImp::~InteractClientImp()
{
    delete m_messageBuffer;
    delete m_session;
    delete m_protocolParser;
    delete m_protocolPacker;
    delete m_ir;
}

int InteractClientImp::DataIn(const uint8_t *data, size_t len)
{
    IDebug("data input, len = %d", len);
    if (m_messageBuffer->DataIn(data, len) != INTERACT_OK)
    {
        return INTERACT_ERROR;
    }

    uint8_t *message = nullptr;
    size_t messageLen = 0;
    int ret = m_messageBuffer->MessageOut(&message, &messageLen);
    if (INTERACT_ERROR == ret)
    {
        IError("message out error");
        return INTERACT_ERROR;
    }
    else if (INTERACT_AGAIN == ret)
    {
        IError("not enough to be one message");
        return INTERACT_AGAIN;
    }

    InteractMessage *interactMessage = nullptr;
    int r = m_protocolParser->Parse(message, ret, &interactMessage); 
    if (r == INTERACT_ERROR)
    {
        IError("parse failed, ");
        return INTERACT_ERROR;
    }
    else if (r == INTERACT_OK) {
        if (interactMessage->GetReqType() == InteractMessage::RESPONSE) {
            ProcessOutgoingStatus((InteractResponse *)interactMessage);
        } else if (interactMessage->GetReqType() == InteractMessage::NOTIFY) {
            ProcessOutgoingNotify((InteractNotify *)interactMessage);
        }
        return ret;
    }
    return INTERACT_OK;
}

void InteractClientImp::ProcessOutgoingMessage(InteractMessage *message)
{
    uint8_t *data = nullptr;
    size_t len = 0;
    assert(message->GetReqType() == InteractMessage::REQUEST);
    IDebug("session url: %s, message = %p", m_session->Url(), message);
    ((InteractRequest *)message)->SetUrl(m_session->Url());
    ((InteractRequest *)message)->SetSessionId(m_session->SessionId());
    if (m_protocolPacker->Pack(message, &data, &len) == INTERACT_OK)
    {
        m_cb->DataOut(data, len);
        return;
    }
    IError("pack failed");
}

void InteractClientImp::ProcessOutgoingStatus(InteractResponse *response)
{
    IDebug("status callback");
    switch (response->GetMsgType())
    {
        case InteractMessage::CONNECT:
            m_session->BindSessionID((char *)response->SessionId());
            m_cb->OnStatus(InteractClientCB::CONNECT_DONE, ((IConnectResponse *)response)->GetMetadata());
            break;
        case InteractMessage::OPERATION:
            if (((IOperationResponse *)response)->Operation() == IOperationResponse::PLAY)
            {
                m_cb->OnStatus(InteractClientCB::PLAYING, nullptr);
            }
            else if (((IOperationResponse *)response)->Operation() == IOperationResponse::PUBLISH)
            {
                m_cb->OnStatus(InteractClientCB::PUBLISHING, nullptr);
            }
            else if (((IOperationResponse *)response)->Operation() == IOperationResponse::PONG) {
                m_cb->OnStatus(InteractClientCB::PONG, nullptr);
            }
            break;
        case InteractMessage::DISCONNECT:
            IDebug("disconnect callback");
            m_cb->OnStatus(InteractClientCB::DESTROYED, nullptr);
            break;
        case InteractMessage::ERROR:
            m_errorCode = ((IErrorResponse*)response)->GetErrorCode();
            m_cb->OnStatus(InteractClientCB::INT_ERROR, nullptr);
            break;
        default:
            m_cb->OnStatus(InteractClientCB::INT_ERROR, nullptr);
            return;
    }
}

void InteractClientImp::ProcessOutgoingNotify(InteractNotify *notify)
{
    IDebug("status callback");

    uint8_t *content = nullptr;
    size_t len = 0;
    notify->GetContent(&content, &len);
    switch(notify->GetNotifyType()) {
        case InteractNotify::DISCONNECT:
            m_cb->OnNotify(InteractClientCB::NOTIFY_DISCONNECT, content, len);
            break;
        default:
            m_cb->OnNotify(InteractClientCB::NOTIFY_UNKNOW, content, len);
            return;
    };
}
int InteractClientImp::Connect(Metadata *metadata)
{
    IConnectRequestLocal request(metadata);
    IDebug("generate connect request");
    ProcessOutgoingMessage((InteractMessage *)&request);
    return INTERACT_OK;
}

int InteractClientImp::Play()
{
    IOperationRequest request((int)IOperationRequest::PLAY);
    ProcessOutgoingMessage((InteractMessage *)&request);
    //m_cb->OnStatus(InteractClientCB::PLAYING, nullptr);
    return INTERACT_OK;
}

int InteractClientImp::Publish()
{
    IOperationRequest request((int)IOperationRequest::PUBLISH);
    ProcessOutgoingMessage((InteractMessage *)&request);
    //m_cb->OnStatus(InteractClientCB::PUBLISHING, nullptr);
    return INTERACT_OK;
}

int InteractClientImp::Ping()
{
    IOperationRequest request((int)IOperationRequest::PING);
    ProcessOutgoingMessage((InteractMessage *)&request);
    //m_cb->OnStatus(InteractClientCB::PUBLISHING, nullptr);
    return INTERACT_OK;
}
int InteractClientImp::Close()
{
    IDisconnectRequest request;
    ProcessOutgoingMessage((InteractMessage *)&request);
    return INTERACT_OK;
}

} // namespace Interact

