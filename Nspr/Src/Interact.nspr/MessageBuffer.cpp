#include "InteractGlobal.h"

#include "MessageBuffer.h"
#include "MessageParser.h"
#include "InteractResource.h"

namespace Interact
{

MessageBuffer::MessageBuffer(InteractResource *ir, MessageParser *messageParser)
    : m_len(0)
{
    m_messagePraer = messageParser;
}

MessageBuffer::~MessageBuffer()
{

}

int MessageBuffer::DataIn(const uint8_t *data, size_t len)
{
    size_t ml = len >= m_maxBufferLen ? m_maxBufferLen -1: len;
    memcpy(m_buffer, data, ml);
    m_buffer[ml] = 0;
    m_len = ml;
    return INTERACT_OK;
}

int MessageBuffer::MessageOut(uint8_t **message, size_t *len)
{
    if (!m_len)
    {
        return INTERACT_AGAIN;
    }
    int ret = m_messagePraer->Preparse(m_buffer, m_len);
    *message = m_buffer;
    *len = m_len;
    m_len = 0;
    return ret;
}


} // namespace Interact



