#ifndef __POSEIDON_PROTOCOL_HTTPRESPONSEPARSER_H__
#define __POSEIDON_PROTOCOL_HTTPRESPONSEPARSER_H__

#include "IHttpParser.h"
#include "InteractGlobal.h"
namespace Interact {

    class HttpResponseParser : public IHttpParser
    {
    public:
        HttpResponseParser();
        ~HttpResponseParser();


        virtual int ParserHead(const char* head, size_t len, char **data) override;

        virtual int GetContentType(char** contenttype) override;

        virtual int GetContentLength(size_t &length) override;

        void init();

        size_t GetCode();
        
        int GetSequence();
    private:
        int ParserHeadLine(size_t index, const char* start, const char* end);
        int ParserItem(char* src, char* cursor, char* data);

        static const size_t m_maxSequenceLength = 20;
        static const size_t m_maxContentTypeLength = 100;
        static const size_t m_maxHttpVersionLength = 128;
        static const size_t m_maxContentLength = 4096;
        static const size_t m_maxDesLength = 1024;
        static const size_t m_maxLineLength = 1024;

        size_t m_code;
        size_t m_sequence;
        size_t m_contentLength;
        char m_contentType[m_maxContentTypeLength];
        char m_httpVersion[m_maxHttpVersionLength];
        char m_httpDes[m_maxDesLength];
    };
}
#endif
