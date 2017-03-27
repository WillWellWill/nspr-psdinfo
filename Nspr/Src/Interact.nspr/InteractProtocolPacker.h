#ifndef __INTERACT_PROTOCOL_PACKER_H__
#define __INTERACT_PROTOCOL_PACKER_H__

namespace Interact
{

class InteractResource;
class InteractMessage;
class InteractProtocolPacker : public InteractObject
{
public:
    InteractProtocolPacker(InteractResource *ir);
    virtual ~InteractProtocolPacker();

    int Pack(InteractMessage *message, uint8_t **data, size_t *len);

private:
    static const int m_maxResponseLen = 4096;
    uint8_t m_response[m_maxResponseLen];

}; // class InteractProtocolPacker
} // namespace Interact


#endif // ifndef __INTERACT_PROTOCOL_PACKER_H__

