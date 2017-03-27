#include "InteractGlobal.h"
#include "HttpResponsePacker.h"
#include <string.h>
#include <stdio.h>
using namespace Interact;

HttpResponsePacker::HttpResponsePacker()
    : m_code(0),
    m_length(0)
{
    m_httpDes[0] = 0;
    m_contentType[0] = 0;
}


HttpResponsePacker::~HttpResponsePacker()
{
}

int HttpResponsePacker::PackerHead(char* data, size_t bufferSize)
{
    snprintf(data, bufferSize, "HTTP/1.1 %zd %s" HTTP_SPARATOR
        "Content_Type: %s" HTTP_SPARATOR
        "Content-Length: %zd" HTTP_SPARATOR
        "Sequence-Number: %zd" HTTP_SPARATOR
        HTTP_SPARATOR, m_code, &m_httpDes[0], &m_contentType[0], m_length, m_sequence);
    return INTERACT_OK;
}

int HttpResponsePacker::SetContentType(const char* contenttype)
{
    int l = strnlen(contenttype, m_maxContentTypeLength);
    if (l >= m_maxContentTypeLength) {
        return INTERACT_ERROR;
    }
    memcpy(&m_contentType[0], contenttype, l);
    m_contentType[l] = 0;
    return INTERACT_OK;
}

int HttpResponsePacker::SetContentLength(size_t length)
{
    m_length = length;
    return INTERACT_OK;
}

int HttpResponsePacker::SetCode(size_t code)
{
    m_code = code;
    return INTERACT_OK;
}

int HttpResponsePacker::SetCodeDes(const char* des)
{
    int l = strnlen(des, m_maxDesLength);
    if (l >= m_maxDesLength) {
        return INTERACT_ERROR;
    }
    memcpy(&m_httpDes[0], des, l);
    m_httpDes[l] = 0;
    return INTERACT_OK;
}

int HttpResponsePacker::SetSequence(size_t sequence)
{
    m_sequence = sequence;
    return INTERACT_OK;
}
