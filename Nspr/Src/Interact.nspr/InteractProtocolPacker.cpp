#include "InteractGlobal.h"

#include "InteractProtocolPacker.h"
#include "InteractResource.h"
#include "InteractMessage.h"
#include "InteractRequest.h"
#include "IOperationRequest.h"

namespace Interact
{

InteractProtocolPacker::InteractProtocolPacker(InteractResource *ir)
    : InteractObject(ir)
{

}
InteractProtocolPacker::~InteractProtocolPacker()
{

}

int InteractProtocolPacker::Pack(InteractMessage *message, uint8_t **data, size_t *len) 
{
    IDebug("pack message");
    if (message->GetReqType() == InteractMessage::RESPONSE) {
        char *content = nullptr;
        size_t contentLen = 0;
        message->GetContent((uint8_t **)&content, &contentLen);
        if (contentLen == 0) {
            snprintf((char *)m_response, sizeof(m_response) - 1, "HTTP/1.1 200 OK\r\n"
                                                 "Server: Poseidon\r\n"
                                                 "Content-Type: text/html\r\n"
                                                 "Content-Length: %ld\r\n"
                                                 "\r\n", contentLen);
        }
        else {
            snprintf((char *)m_response, sizeof(m_response) - 1, "HTTP/1.1 200 OK\r\n"
                                                 "Server: Poseidon\r\n"
                                                 "Content-Type: text/html\r\n"
                                                 "Content-Length: %ld\r\n"
                                                 "\r\n%s", contentLen, content);
        }
        *data = &m_response[0];
        *len = strlen((char *)m_response);

    }
    else {
        InteractRequest *request = (InteractRequest *)message;
        char *content = nullptr;
        size_t contentLen = 0;
        const char *uri = request->GetUri();
        const char *host = request->GetHost();
        IDebug("pack need host: $s,  uri:%s, request:%p", host, uri, request);
        const char* params = strstr(uri, "?");
        size_t dl = params - uri;
        char dir[1024] = {0};
        char param[1024] = {0};
        if (params) {
            memcpy(dir, uri, dl); 
            dir[dl] = 0;
            size_t pl = strlen(params);
            memcpy(param, params, pl); 
            param[pl] = 0;
        } else {
            dl = strlen(uri);
            memcpy(dir, uri, dl);
            dir[dl] = 0;
        }
/*
 *        char *pointer = (char *)strstr(url, "://");
 *        if (!pointer) {
 *            return INTERACT_ERROR;
 *        }
 *        pointer += 3;
 *        const char *hostBeg = pointer;
 *        pointer = strchr(pointer, '/');
 *        if (!pointer) {
 *            return INTERACT_ERROR;
 *        }
 *        char host[256] = {0};
 *        memcpy(host, hostBeg, pointer - hostBeg);
 *        host[pointer - hostBeg] = 0;
 *
 *        const char *uriBeg = pointer;
 *        pointer = strchr(pointer, '?');
 *        const char *paramBeg = pointer;
 *        char uri[256] = {0};
 *        char param[256] = {0};
 *        if (paramBeg) {
 *            memcpy(uri, uriBeg, paramBeg - uriBeg);
 *            uri[paramBeg - uriBeg] = 0;
 *
 *            memcpy(param, paramBeg, strlen(paramBeg));
 *            param[strlen(paramBeg)] = 0;
 *        }
 *        else {
 *            memcpy(uri, uriBeg, strlen(uriBeg));
 *            uri[strlen(uriBeg)] = 0;
 *        }
 */

        std::string actionType;
        std::string reqType;
        if (request->GetReqType() == InteractMessage::NOTIFY) {
            actionType = "notify";
            reqType = "NOTIFY";
        } else if (request->GetReqType() == InteractMessage::REQUEST) {
            reqType = "POST";
            switch (message->GetMsgType())
            {
                case InteractMessage::CONNECT: actionType = "connect"; break;
                case InteractMessage::OPERATION:
                    {
                        switch (((IOperationRequest *)request)->Operation()) {
                            case IOperationRequest::PLAY:
                                actionType = "play";
                                break;
                            case IOperationRequest::PUBLISH:
                                actionType = "publish";
                                break;
                            case IOperationRequest::PING:
                                actionType = "ping";
                                break;
                            default:
                                actionType = "unknow";
                        }
                    } break;
                case InteractMessage::DISCONNECT: actionType = "disconnect"; break;
                default: return INTERACT_ERROR;
            }
        }
        message->GetContent((uint8_t **)&content, &contentLen);
        if (contentLen == 0) {
            content = (char*)std::string("").c_str();
        }
        snprintf((char *)m_response, sizeof(m_response) - 1, "%s /%s/%s%s HTTP/1.1\r\n"
                                                 "Host: %s\r\n"
                                                 "User-Agent: Poseidon\r\n"
                                                 "Content-Type: text/html\r\n"
                                                 "Content-Length: %ld\r\n"
                                                 "\r\n%s"
                                                 , reqType.c_str(), dir, actionType.c_str(), param
                                                 , host
                                                 , contentLen, content);
        *data = &m_response[0];
        *len = strlen((char *)m_response);
    }
    return INTERACT_OK; 
}

} // namespace Interact

