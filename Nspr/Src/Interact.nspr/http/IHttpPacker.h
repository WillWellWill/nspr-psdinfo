#ifndef __POSEIDON_PROTOCOL_HTTPPAKCER_H__
#define __POSEIDON_PROTOCOL_HTTPPAKCER_H__
namespace Interact {

    class IHttpPacker : public InteractObject
    {
    public:
        virtual ~IHttpPacker(){}
        virtual int PackerHead(char* data, size_t bufferSize) = 0;
        virtual int SetContentType(const char* contenttype) = 0;
        virtual int SetContentLength(size_t length) = 0;
    };

}
#endif
