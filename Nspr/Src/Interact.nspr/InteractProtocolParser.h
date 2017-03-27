#ifndef __INTERACT_PROTOCOL_PARSER_H__
#define __INTERACT_PROTOCOL_PARSER_H__

#include "MessageParser.h"

namespace Interact
{

class IHttpParser;
class InteractResource;
class InteractMessage;
class InteractRequest;
class InteractProtocolParser : public MessageParser
{
public:
    InteractProtocolParser(InteractResource *ir);
    virtual ~InteractProtocolParser();

    virtual int Preparse(uint8_t *data, size_t len);

    int Parse(uint8_t *message, size_t len, InteractMessage **interactMessage);
    
    virtual InteractResource *IR() { return m_ir; }

private:
    InteractResource *m_ir;
    IHttpParser *m_httpRequestParser;
    IHttpParser *m_httpResponseParser;
    static const size_t m_maxMsgLength = 4096;
    enum Request
    {
        CONNECT = 1,
        PLAY,
        PUBLISH,
        PING,
        DISCONNECT
    };
    enum NotifyType
    {
        NOTIFY_DISCONNECT
    };
//    uint8_t *m_content;
//    size_t  m_contentLen;


private:
    int ParserHead(uint8_t *data, size_t len);
    int ParseRequest(Request req, uint8_t *message, size_t len, InteractMessage **interactMessage);
    int ParseNotify(uint8_t *message, size_t len, InteractMessage **interactMessage);
    int ParseResponse(uint8_t *message, size_t len, InteractMessage **interactMessage);
    int ParseSid(uint8_t *message, size_t len, InteractRequest *interactMessage);
    int GetRequestFromUrl(uint8_t *url, size_t urlLen);
    int GetValue(uint8_t *message, size_t len, const char *key, char **value, size_t *valueLen);
    int GetSid(uint8_t *content, size_t len, char **sid, size_t *slen);

}; // class InteractProtocolParser
} // namespace Interact


#endif // ifndef __INTERACT_PROTOCOL_PARSER_H__

