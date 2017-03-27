#ifndef __POSEIDON_PROTOCOL_HTTPPARSE_H__
#define __POSEIDON_PROTOCOL_HTTPPARSE_H__
namespace Interact {

    class IHttpParser : public InteractObject
    {
    public:
        virtual ~IHttpParser() {}
        virtual int ParserHead(const char* head, size_t len, char **data) = 0;
        virtual int GetContentType(char** contenttype) = 0;
        virtual int GetContentLength(size_t &length) = 0;
    };

}

#endif
