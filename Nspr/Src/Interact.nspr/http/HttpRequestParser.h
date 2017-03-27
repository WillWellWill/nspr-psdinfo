#ifndef __POSEIDON_PROTOCOL_HTTPREQUESTPARSER_H__
#define __POSEIDON_PROTOCOL_HTTPREQUESTPARSER_H__

#include "IHttpParser.h"
#include "InteractGlobal.h"

namespace Interact {

    class HttpRequestParser :public IHttpParser
    {
    public:
        HttpRequestParser();
        ~HttpRequestParser();

        virtual int ParserHead(const char* head, size_t len, char** data) override;

        virtual int GetContentType(char** contenttype) override;

        virtual int GetContentLength(size_t &length) override;

        void init();

        int GetDir(char** dir);

        int GetHost(char** host);

        int GetMethod(char** method);

        size_t GetSequence();

    private:
        int ParserHeadLine(size_t index, const char* start, const char* end);
        int ParserItem(char* src, char* cursor, char* data);

        static const size_t m_maxSequenceLength = 20;
        static const size_t m_maxUrlLength = 1024;
        static const size_t m_maxContentTypeLength = 100;
        static const size_t m_maxMethodLength = 20;
        static const size_t m_maxUserAgentLength = 128;
        static const size_t m_maxHttpVersionLength = 128;
        static const size_t m_maxContentLength = 4096;
        static const size_t m_maxHostLength = 128;
        static const size_t m_maxDirLength = 1024;

        char m_dir[m_maxDirLength];
        char m_host[m_maxHostLength];
        char m_contentType[m_maxContentTypeLength];
        char m_method[m_maxMethodLength];
        char m_userAgent[m_maxUserAgentLength];
        char m_httpVersion[m_maxHttpVersionLength];
        size_t m_contentLength;
        size_t m_sequence;
    };
}
#endif
