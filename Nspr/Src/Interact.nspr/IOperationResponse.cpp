#include "InteractGlobal.h"

#include "IOperationResponse.h"

namespace Interact
{

IOperationResponse::IOperationResponse(OpType type)
    :m_type(type)
{
    m_response[0] = 0;
    m_respLen = 0;
}

IOperationResponse::~IOperationResponse()
{

}
void IOperationResponse::GetContent(uint8_t **content, size_t *contentLen)
{

    const char* response = nullptr;
    if (m_type == PLAY) {
        response = "typ=play\n";
    }
    else if (m_type == PUBLISH) {
        response = "typ=publish\n";
    }
    else {
        response = "typ=pong\n";
    }
    m_respLen = strlen(response);
    strcpy(m_response, response);
    *contentLen = m_respLen;
    *content = (uint8_t *)m_response;

}

} // namespace Interact

