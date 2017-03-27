#ifndef __POSEIDON_PROTOCOL_HTTPREQUESTPACKER_H__
#define __POSEIDON_PROTOCOL_HTTPREQUESTPACKER_H__

#include "IHttpPacker.h"
#include "InteractGlobal.h"

namespace Interact {

    class HttpRequestPacker :public IHttpPacker
    {
    public:
        HttpRequestPacker();
        ~HttpRequestPacker();

        int SetUrl(const char* url);

        int SetUserAgent(const char* useragent);

        int SetDir(const char* dir);
    
        int SetHost(const char* host);

        int SetMethod(const char* method);

        int SetSequence(size_t sequence);

        virtual int PackerHead(char* data, size_t bufferSize) override;

        virtual int SetContentType(const char* contenttype) override;

        virtual int SetContentLength(size_t length) override;

    private:
        
        static const size_t m_maxUrlLength = 1024;
        static const size_t m_maxContentTypeLength = 100;
        static const size_t m_maxMethodLength = 20;
        static const size_t m_maxUserAgentLength = 128;
        static const size_t m_maxHostLength = 128;
        static const size_t m_maxDirLength = 1024;
            
        char m_url[m_maxUrlLength]; 
        char m_host[m_maxHostLength];
        char m_dir[m_maxDirLength];
        char m_contentType[m_maxContentTypeLength];
        char m_method[m_maxMethodLength];
        char m_userAgent[m_maxUserAgentLength];
        size_t m_length;
        size_t m_sequence;
    };

}
#endif
