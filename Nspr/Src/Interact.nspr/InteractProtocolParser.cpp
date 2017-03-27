#include "InteractGlobal.h"

//#include "Utils.h"
#include "InteractProtocolParser.h"
#include "InteractResource.h"
#include "InteractMessage.h"
#include "IConnectRequest.h"
#include "IOperationRequest.h"
#include "IDisconnectRequest.h"
#include "IConnectResponse.h"
#include "IOperationResponse.h"
#include "IDisconnectResponse.h"
#include "IErrorResponse.h"
#include "InteractNotify.h"
#include "SessionDescription.h"
#include "HttpRequestParser.h"
#include "HttpResponseParser.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

typedef unsigned char u_char;

char* pos_strnstr(char* data, const char* match, size_t max) 
{
    if (max == 0) {
        return 0;
    }
    size_t i = 0;
    size_t j = 0;
    size_t max_m = strnlen(match, max);
    bool isMatch = true;
    while(data[i] != 0 && i < max) {
        j = 0;
        isMatch = true;
        while (j < max_m) {
            if (i + j >= max) {
                isMatch = false;
                return 0;
            }
            if (data[i + j] != match[j]) {
                isMatch = false;
                break;
            }
            j++;
        }
        if (isMatch) {
            return data + i;
        }
        i++;
    }
    return 0;
}

namespace Interact
{

InteractProtocolParser::InteractProtocolParser(InteractResource *ir)
    : m_ir(ir)
    //, m_content(nullptr)
    //, m_contentLen(0)
{
    m_httpRequestParser = new HttpRequestParser;
    m_httpResponseParser = new HttpResponseParser;
}
InteractProtocolParser::~InteractProtocolParser()
{
    delete m_httpRequestParser;
    delete m_httpResponseParser;
}

int InteractProtocolParser::Preparse(uint8_t *data, size_t len)
{
    char *str = (char *)data;
    char *headerEnd = pos_strnstr(str, HTTP_SPARATOR HTTP_SPARATOR, len);
    if (!headerEnd) {
        return INTERACT_AGAIN;
    }
    size_t head_len = headerEnd - (char*)data + 4;
    if (head_len >= m_maxMsgLength) {
        return INTERACT_ERROR;
    }
    int ret = ParserHead(data, head_len);
    if (ret == INTERACT_ERROR) {
        return INTERACT_ERROR;
    }
    int msgLen = ret + (int)head_len;
    if (msgLen >= (int)m_maxMsgLength) {
        return INTERACT_ERROR;
    }
    if (msgLen > (int)len) {
        return INTERACT_AGAIN;
    }
    return msgLen; 
}

int InteractProtocolParser::ParserHead(uint8_t *data, size_t len)
{
    int ret = 0;
    char* content = nullptr;
    size_t ll = 0;
    if (!strncasecmp((char *)data, "GET", 3) || !strncasecmp((char *)data, "POST", 4)) {
        ret = m_httpRequestParser->ParserHead((const char*)data, len, &content);
        if (ret == INTERACT_OK)
            m_httpRequestParser->GetContentLength(ll);
        else
            return INTERACT_ERROR;
    } else if (!strncasecmp((char *)data, "HTTP/", 5)) {
        ret = m_httpResponseParser->ParserHead((const char*)data, len, &content);
        if (ret == INTERACT_OK)
            m_httpResponseParser->GetContentLength(ll);
        else
            return INTERACT_ERROR;
    } else if (!strncasecmp((char *)data, "NOTIFY", 3)) {
        ret = m_httpRequestParser->ParserHead((const char*)data, len, &content);
        if (ret == INTERACT_OK)
            m_httpRequestParser->GetContentLength(ll);
        else
            return INTERACT_ERROR;
    } else {
        return INTERACT_ERROR;
    }
    return ll;
}
int InteractProtocolParser::Parse(uint8_t *message, size_t len, InteractMessage **interactMessage) 
{
    int ret = 0;
    char* content = nullptr;
    size_t ll = 0;
    if (!strncasecmp((char *)message, "GET", 3) || !strncasecmp((char *)message, "POST", 4)) {
        ret = m_httpRequestParser->ParserHead((const char*)message, len, &content);
        if (ret == INTERACT_OK) {
            m_httpRequestParser->GetContentLength(ll);
            char *uri = nullptr;
            char *host = nullptr;
            ((HttpRequestParser*)m_httpRequestParser)->GetDir(&uri);
            ((HttpRequestParser*)m_httpRequestParser)->GetHost(&host);
            int uriLen = strlen(uri);
            Request req = (Request)GetRequestFromUrl((uint8_t*)uri, uriLen);
            if (ParseRequest(req, (uint8_t *)content, ll, interactMessage) == INTERACT_OK) {
                ((InteractRequest *)*interactMessage)->SetUri(uri);
                ((InteractRequest *)*interactMessage)->SetHost(host);
                return INTERACT_OK; 
            }
        }
    } else if (!strncasecmp((char *)message, "HTTP/", 5)) {
        ret = m_httpResponseParser->ParserHead((const char*)message, len, &content);
        if (ret == INTERACT_OK) {
            m_httpResponseParser->GetContentLength(ll);
            if (ParseResponse((uint8_t *)content, ll, interactMessage) == INTERACT_OK)
            {
                return INTERACT_OK; 
            }
        }
    } else if (!strncasecmp((char *)message, "NOTIFY", 6)) {
        ret = m_httpRequestParser->ParserHead((const char*)message, len, &content);
        if (ret == INTERACT_OK) {
            m_httpRequestParser->GetContentLength(ll);
            if (ParseNotify((uint8_t *)content, ll, interactMessage) == INTERACT_OK) {
                return INTERACT_OK; 
            }
        }
    } 
    return INTERACT_ERROR; 
}

int InteractProtocolParser::ParseRequest(Request request, uint8_t *message, size_t len, InteractMessage **interactMessage)
{
    switch (request) {
        case InteractProtocolParser::CONNECT:
            {
                IConnectRequestRemote *interactRemote = new IConnectRequestRemote();
                if (interactRemote->InitMessage(message, len) == INTERACT_ERROR) {
                    delete interactRemote;
                    IError("Create Connect Request message error!");
                    return INTERACT_ERROR;
                }
                *interactMessage = interactRemote;
            }break;
        case InteractProtocolParser::PLAY: *interactMessage = new IOperationRequest((int)IOperationRequest::PLAY); break;
        case InteractProtocolParser::PUBLISH: *interactMessage = new IOperationRequest((int)IOperationRequest::PUBLISH); break;
        case InteractProtocolParser::PING: *interactMessage = new IOperationRequest((int)IOperationRequest::PING); break;
        case InteractProtocolParser::DISCONNECT: *interactMessage = new IDisconnectRequest(); break;
        default:
            {
                IError("Create unknow Request message error!");
                return INTERACT_ERROR;
            }
    }   
    
    char* sid = nullptr;
    size_t sidlen = 0;
    int error = GetSid(message, len, &sid, &sidlen);
    if (error == INTERACT_OK) {
        char s[1024];
        memcpy(s, sid, sidlen);
        s[sidlen] = 0;
        ((InteractRequest*)*interactMessage)->SetSessionId(s);
    }
    return INTERACT_OK;
}

int InteractProtocolParser::ParseResponse(uint8_t *message, size_t len, InteractMessage **interactMessage)
{

    SessionDescription sd;
    char tmp[4096] = {0};
    memcpy(tmp, &message[0], len < 4095 ? (tmp[len] = 0, len) : (tmp[4095] = 0, 4095));

    if (strstr(tmp, "error=")) {
        *interactMessage = new IErrorResponse(message,len);
        return INTERACT_OK;
    }
    
    size_t typeLen = 0;
    const char *type = sd.TypeOf(&tmp[0], &typeLen);
    size_t sidLen = 0;
    const char *sid = sd.SessionIdOf(&tmp[0], &sidLen);
    if (!typeLen) {
        return INTERACT_ERROR;
    }
    
    if (!strncmp(type, "connect", 7)) {
        *interactMessage = new IConnectResponseRemote(message, len);
    }
    else if (!strncmp(type, "play", 4)) {
        *interactMessage = new IOperationResponse(IOperationResponse::PLAY);
    }
    else if (!strncmp(type, "publish", 7)) {
        *interactMessage = new IOperationResponse(IOperationResponse::PUBLISH);
    }
    else if (!strncmp(type, "pong", 4)) {
        *interactMessage = new IOperationResponse(IOperationResponse::PONG);
    }
    else if (!strncmp(type, "disconnect", 10)) {
        *interactMessage = new IDisconnectResponse(sid);
    }
    return INTERACT_OK;
}

int InteractProtocolParser::ParseNotify(uint8_t *message, size_t len, InteractMessage **interactMessage)
{
    InteractNotify *interactNotify = new InteractNotify();
    if (interactNotify->InitMessage(message, len) == INTERACT_ERROR) {
        delete interactNotify;
        IError("Create Notify Request message error!");
        return INTERACT_ERROR;
    }
    *interactMessage = interactNotify;
    
    char* sid = nullptr;
    size_t sidlen = 0;
    int error = GetSid(message, len, &sid, &sidlen);
    if (error == INTERACT_OK) {
        char s[1024];
        memcpy(s, sid, sidlen);
        s[sidlen] = 0;
        ((InteractRequest*)*interactMessage)->SetSessionId(s);
    } else {
        return INTERACT_ERROR;
    }
    return INTERACT_OK;
}

int InteractProtocolParser::GetSid(uint8_t *content, size_t len, char **sid, size_t *slen)
{
    (void)len;
    char* sk = strcasestr((char *)content, "sid=");
	if (!sk)
	{
        return INTERACT_ERROR;
	}
    char* se = strcasestr(sk, "\n");
	if (!se)
	{
        *sid = sk+4;
        *slen =  strlen(sk+4); 
        return INTERACT_OK;
	}
    *sid = sk+4;
    *slen = se - *sid; 
    return INTERACT_OK;
}

int InteractProtocolParser::GetRequestFromUrl(uint8_t *url, size_t urlLen)
{
    u_char urlCpy[1024] = {0};
    memcpy(urlCpy, url, urlLen);
    u_char *requestStart = (u_char *)strrchr((char *)urlCpy, '/');
    if (!requestStart)
    {
        return INTERACT_ERROR;
    }

    requestStart += 1;
    if (!strncmp((char *)requestStart, "connect", 7))
    {
        return (int)InteractProtocolParser::CONNECT;
    }
    else if(!strncmp((char *)requestStart, "play", 4))
    {
        return (int)InteractProtocolParser::PLAY;
    }
    else if(!strncmp((char *)requestStart, "publish", 7))
    {
        return (int)InteractProtocolParser::PUBLISH;
    }
    else if(!strncmp((char *)requestStart, "ping", 4))
    {
        return (int)InteractProtocolParser::PING;
    }
    else if(!strncmp((char *)requestStart, "disconnect", 10))
    {
        return (int)InteractProtocolParser::DISCONNECT;
    }
	
    return INTERACT_ERROR;
}
int InteractProtocolParser::ParseSid(uint8_t *message, size_t len, InteractRequest *request)
{
	char* sid = nullptr;
	size_t slen = 0;
	if (GetSid(message, len, &sid, &slen))
	{
		return INTERACT_ERROR;
	}
	char ssid[128] = {0};
	if (slen >=128 )
	{
		return INTERACT_ERROR;
	}
	memcpy(&ssid[0], sid, slen);
	request->SetSessionId(&ssid[0]);
    return INTERACT_OK;
}

int InteractProtocolParser::GetValue(uint8_t *message, size_t len, const char *key, char **value, size_t *valueLen)
{
    char *pointer = strcasestr((char *)message, key);
    if (!pointer || (size_t)((uint8_t *)pointer - message) >= len)
    {
        return INTERACT_ERROR;
    }
    pointer += strlen(key);

    while (isspace((int)*pointer) || *pointer == ':')
    {
        if ((size_t)((uint8_t *)pointer - message) > len)
        {
            return INTERACT_ERROR;
        }
        ++pointer;
    }
    if (*pointer == 0)
    {
        return INTERACT_ERROR;
    }
    
    char *valuePos = pointer;
    do
    {
        if ((size_t)((uint8_t *)pointer - message) > len)
        {
            return INTERACT_ERROR;
        }
        ++pointer;
    } while (*pointer != 0 && !isspace(*pointer));

    *value = valuePos;
    *valueLen = pointer - valuePos;
    return INTERACT_OK;
}

} // namespace Interact
