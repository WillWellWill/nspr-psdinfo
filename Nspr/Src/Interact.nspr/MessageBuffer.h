#ifndef __INTERACT_MESSAGE_BUFFER_H__
#define __INTERACT_MESSAGE_BUFFER_H__


namespace Interact
{
class MessageParser;
class InteractResource;
class MessageBuffer : public InteractObject
{
public:
    MessageBuffer(InteractResource *ir, MessageParser *messageParser);
    virtual ~MessageBuffer();

    int DataIn(const uint8_t *data, size_t len);
    int MessageOut(uint8_t **message, size_t *len);

private:
    const static size_t m_maxBufferLen = 4096;
    uint8_t m_buffer[m_maxBufferLen];
    size_t m_len;
    MessageParser *m_messagePraer;

}; // class MessageBuffer

} // namespace Interact


#endif // ifndef __INTERACT_MESSAGE_BUFFER_H__

