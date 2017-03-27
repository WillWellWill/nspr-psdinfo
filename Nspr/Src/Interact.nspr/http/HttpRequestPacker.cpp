#include "InteractGlobal.h"
#include "HttpRequestPacker.h"
#include <stdio.h>
#include <string.h>

using namespace Interact;

#define CHECK_SIZE_ERROR(mem) if (strnlen(mem,COM_CONTENT_LENGTH) == 0) return INTERACT_ERROR

HttpRequestPacker::HttpRequestPacker()
    :m_length(0),
    m_sequence(0)
{
    m_url[0] = 0,
    m_contentType[0] = 0;
    strcpy(m_method, "GET");
    m_userAgent[0] = 0;
}


HttpRequestPacker::~HttpRequestPacker()
{
}

int HttpRequestPacker::SetUrl(const char* url)
{
    size_t l = strnlen(url,m_maxUrlLength);
    if (l > m_maxUrlLength) {
        return INTERACT_ERROR;
    }
    memcpy(m_url, url, l);
    m_url[l] = 0;

    size_t index = 0;
    if (!strncmp(m_url, "http://", 7)) {
        index = 7;
    }
    else if (!strncmp(m_url, "https://", 8)) {
        index = 8;
    }
    size_t url_len = strnlen(m_url, m_maxUrlLength);
    if (url_len >= m_maxUrlLength) {
        return INTERACT_ERROR;
    }
    if (index == 0) {
        memcpy(m_dir, url, url_len);
        m_dir[url_len] = 0;
        return INTERACT_OK;
    }
    const char* ind_host = m_url + index;
    const char* ind_host_last = strstr(ind_host, "/");
    size_t host_len = ind_host_last - ind_host;
    if (host_len > m_maxHostLength) {
        ind_host_last = m_url + url_len;
        host_len = ind_host_last - ind_host;
        if (host_len > m_maxHostLength) {
            return INTERACT_ERROR;
        }
    }

    memcpy(m_host, ind_host, host_len);
    m_host[host_len] = '\0';

    const char* ind_dir = ind_host + host_len;
    size_t dir_len = strnlen(ind_dir, m_maxMethodLength);
    //SAFE_ALLOC(m_dir, char, dir_len);
    if (dir_len > m_maxDirLength) {
        return INTERACT_ERROR;
    }
    else if(dir_len == 0) {
        strcpy(m_dir, "/");
    }
    else {
        memcpy(m_dir, ind_dir, dir_len);
        m_dir[dir_len] = '\0';
    }
    return INTERACT_OK;
}

int HttpRequestPacker::SetMethod(const char* method)
{
    strcpy(m_method, method);
    return INTERACT_OK;
}
int HttpRequestPacker::SetDir(const char* dir)
{
    size_t l = strnlen(dir,m_maxDirLength);
    if (l > m_maxDirLength) {
        return INTERACT_ERROR;
    }
    memcpy(m_dir, dir, l);
    m_dir[l] = 0;
    return INTERACT_OK;

}
    
int HttpRequestPacker::SetHost(const char* host)
{
    size_t l = strnlen(host,m_maxHostLength);
    if (l > m_maxHostLength) {
        return INTERACT_ERROR;
    }
    memcpy(m_host, host, l);
    m_host[l] = 0;
    return INTERACT_OK;

}

int HttpRequestPacker::PackerHead(char* data, size_t bufferSize)
{
	if (strnlen(m_dir, m_maxDirLength) == 0) return INTERACT_ERROR;
	if (strnlen(m_host, m_maxHostLength) == 0) return INTERACT_ERROR;
	if (strnlen(m_contentType, m_maxContentTypeLength) == 0) return INTERACT_ERROR;

    snprintf(data, bufferSize, "%s %s HTTP/1.1" HTTP_SPARATOR "Host:%s" HTTP_SPARATOR, m_method, m_dir, m_host);
    size_t n = strlen(data);
    if (m_userAgent[0] != 0) {
        snprintf(data + n, bufferSize - n, "User-Agent:%s" HTTP_SPARATOR, m_userAgent); 
    }
    n = strlen(data);
    snprintf(data + n, bufferSize - n,
        "Content-Type: %s" HTTP_SPARATOR
        "Content-Length: %zd" HTTP_SPARATOR
        "Sequence-Number: %zd" HTTP_SPARATOR
        HTTP_SPARATOR, m_contentType, m_length, m_sequence);
    return INTERACT_OK;
}

int HttpRequestPacker::SetContentType(const char* contenttype)
{
    size_t l = strnlen(contenttype, m_maxContentTypeLength);
    if (l > m_maxContentTypeLength) {
        return INTERACT_ERROR;
    }
    memcpy(m_contentType, contenttype, l);
    m_contentType[l] = 0;
    return INTERACT_OK;
}

int HttpRequestPacker::SetContentLength(size_t length)
{
    m_length = length;
    return INTERACT_OK;
}

int HttpRequestPacker::SetUserAgent(const char* useragent)
{
    size_t l = strnlen(useragent, m_maxUserAgentLength);
    if (l >= m_maxUserAgentLength) {
        return INTERACT_ERROR;
    }
    memcpy(m_userAgent, useragent, l);
    m_userAgent[l] = 0;
    return INTERACT_OK;
}

int HttpRequestPacker::SetSequence(size_t sequence)
{
    m_sequence = sequence;
    return INTERACT_OK;
}
