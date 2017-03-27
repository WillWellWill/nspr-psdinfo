#include "InteractGlobal.h"
#include "HttpRequestParser.h"
#include <string.h>
#include <stdlib.h>

using namespace Interact;


HttpRequestParser::HttpRequestParser()
    :m_contentLength(0)
{
    m_dir[0] = 0;
    m_host[0] = 0;
    m_contentType[0] = 0;
    m_method[0] = 0;
    m_userAgent[0] = 0;
    m_httpVersion[0] = 0;
}


HttpRequestParser::~HttpRequestParser()
{
}

void HttpRequestParser::init()
{
    m_contentLength = 0;
    m_dir[0] = 0;
    m_host[0] = 0;
    m_contentType[0] = 0;
    m_method[0] = 0;
    m_userAgent[0] = 0;
    m_httpVersion[0] = 0;
    
}

int HttpRequestParser::ParserHead(const char* data, size_t len, char** content)
{
    
    if (len == 0) {
        return INTERACT_AGAIN;
    }
    init();
    char mes[m_maxContentLength];
    size_t cl = len >= m_maxContentLength? m_maxContentLength-1: len;
    memcpy(mes, data, cl);
    mes[cl] = 0;
    const char* h_end = strstr(mes, HTTP_SPARATOR HTTP_SPARATOR);
    if (h_end == nullptr) {
        if (cl == m_maxContentLength - 1) {
            IError("The head is too max!");
            return INTERACT_ERROR;
        }
        return INTERACT_AGAIN;
    }
    const size_t h_len = h_end - mes;
    //the h_len is never more than len
    const char* start = mes;
    const char* end = strpbrk(mes, HTTP_SPARATOR);
    *content = (char*)data + h_len + 4;
    //parser head
    size_t index = 0;
    while (start != end)
    {
        if (ParserHeadLine(index, start, end) == INTERACT_ERROR) {
            return INTERACT_ERROR;
        }
        end++;
        if (end > mes + len)
        {
            break;
        }
        if (*end == '\r' || *end == '\n')
        {
            end++;
        }
        start = end;
        end = strpbrk(start, HTTP_SPARATOR);
        if (end == nullptr)
            end = mes + len;
        index++;
    }
    return INTERACT_OK;
}

int HttpRequestParser::GetContentType(char** contenttype)
{
    *contenttype = m_contentType;
    return INTERACT_OK;
}

int HttpRequestParser::GetDir(char** dir)
{
    *dir = m_dir;
    return INTERACT_OK;
}

int HttpRequestParser::GetHost(char** host)
{
    *host = m_host;
    return INTERACT_OK;
}

int HttpRequestParser::GetMethod(char** method)
{
    *method = m_method;
    return INTERACT_OK;
}

int HttpRequestParser::GetContentLength(size_t &length)
{
    length = m_contentLength;
    return INTERACT_OK;
}
int HttpRequestParser::ParserHeadLine(size_t index, const char* start, const char* end)
{
    size_t len = end - start;
    if (len >= m_maxUrlLength) {
        IError("The head line length is too long!");
        return INTERACT_ERROR;
    }

    char line[m_maxUrlLength];
    memcpy(line, start, len);
    line[len] = '\0';

    char* st = line;
    char* cursor;
    if (index == 0 )
    {
        //method
        cursor = strpbrk(st, " \t");
        len = cursor - st;
        if (len >= m_maxMethodLength|| len == 0) {
            IError("The method length is too long!");
            return INTERACT_ERROR;
        }
        memcpy(m_method, st, len);
        m_method[len] = '\0';
        while (*cursor == ' ' || *cursor =='\t')
        {
            cursor++;
        }
        st = cursor;
        //dir
        cursor = strpbrk(st, " \t");
        len = cursor - st;
        if (len >= m_maxDirLength || len == 0) {
            return INTERACT_ERROR;
        }
        memcpy(m_dir, st, len);
        m_dir[len] = '\0';
        while (*cursor == ' ' || *cursor == '\t')
        {
            cursor++;
        }
        st = cursor;
        //http version
        len = strnlen(st, m_maxHttpVersionLength);
        if (len >= m_maxHttpVersionLength|| len == 0) {
            return INTERACT_ERROR;
        }
        memcpy(m_httpVersion, st, len);
        m_httpVersion[len] = '\0';
    }
    else
    {
        cursor = strcasestr(st, "Host");
        if (cursor) {
            char* data = m_host;
            return ParserItem(st, cursor, data);
        }
        cursor = strcasestr(st, "User-Agent");
        if (cursor) {
            char* data = m_userAgent;
            return ParserItem(st, cursor, data);
        }
        cursor = strcasestr(st, "Content-Length");
        if (cursor) {
            size_t len;
            char length[m_maxContentLength];
            if (st != cursor) {
                return INTERACT_ERROR;
            }
            cursor = strpbrk(st, ":");
            while (*(++cursor) == ' ' || *cursor == '\t');
            len = strlen(cursor);
            if (len >= m_maxContentLength)
                return INTERACT_ERROR;
            memcpy(length, cursor, len);
            length[len] = '\0';
            m_contentLength = atoi(length);
            return true;
        }
        cursor = strcasestr(st, "Content-Type");
        if (cursor) {
            char* data = m_contentType;
            return ParserItem(st, cursor, data);
        }
        cursor = strcasestr(st, "Sequence-Number");
        if (cursor)
        {
            size_t len;
            char length[m_maxSequenceLength];
            if (st != cursor) {
                return INTERACT_ERROR;
            }
            cursor = strpbrk(st, ":");
            while (*(++cursor) == ' ' || *cursor == '\t');
            len = strlen(cursor);
            if (len >= m_maxSequenceLength)
                return INTERACT_ERROR;
            memcpy(length, cursor, len);
            length[len] = '\0';
            m_sequence = atoi(length);
            return INTERACT_OK;
        }
    }
    return INTERACT_OK;
}

int HttpRequestParser::ParserItem(char* src, char* cursor, char* data)
{
    size_t len;
    if (src != cursor) {
        return INTERACT_ERROR;
    }
    cursor = strpbrk(src, ":");
    while (*(++cursor) == ' ' || *cursor == '\t');
    len = strlen(cursor);
    memcpy(data, cursor, len);
    data[len] = '\0';
    return INTERACT_OK;
}

