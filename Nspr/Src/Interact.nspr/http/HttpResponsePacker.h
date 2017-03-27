#ifndef __POSEIDON_PROTOCOL_HTTPRESPONSEPACKER_H__
#define __POSEIDON_PROTOCOL_HTTPRESPONSEPACKER_H__
#include "IHttpPacker.h"
#include "InteractGlobal.h"

namespace Interact {

    class HttpResponsePacker:public IHttpPacker
    {
    public:
        HttpResponsePacker();
        ~HttpResponsePacker();

        virtual int PackerHead(char* data, size_t bufferSize) override;

        virtual int SetContentType(const char* contenttype) override;

        virtual int SetContentLength(size_t length) override;

        int SetCode(size_t code);

        int SetCodeDes(const char* des);

        int SetSequence(size_t sequence);
    private:
        
        static const int m_maxContentTypeLength = 100;
        static const int m_maxDesLength = 1024;

        size_t m_code;
        size_t m_sequence;
        char m_contentType[m_maxContentTypeLength];
        size_t m_length;
        char m_httpDes[m_maxDesLength];
    };
}
#endif
