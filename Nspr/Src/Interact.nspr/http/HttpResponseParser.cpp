#include "InteractGlobal.h"
#include "HttpResponseParser.h"
#include <string.h>
#include <stdlib.h>

using namespace Interact;

HttpResponseParser::HttpResponseParser()
    : m_code(0),
    m_sequence(0),
    m_contentLength(0)
{
    m_contentType[0] = 0;
    m_httpVersion[0] = 0;
    m_httpDes[0] = 0;
}


HttpResponseParser::~HttpResponseParser()
{
}

void HttpResponseParser::init() {
    m_sequence = 0;
    m_contentLength = 0;
    m_code = 0;

    m_contentType[0] = 0;
    m_httpVersion[0] = 0;
}

int HttpResponseParser::ParserHead(const char* data, size_t len, char **content)
{
    if (len == 0) {
        return INTERACT_AGAIN;
    }
    init();
    //first copy the max head data to cache
    size_t cl = len >= m_maxContentLength? m_maxContentLength-1: len;
    char mes[m_maxContentLength];
    memcpy(mes, data, cl);
    mes[cl] = 0;
    //second check the \r\n\r\n chars
    const char* h_end = strstr(mes, HTTP_SPARATOR HTTP_SPARATOR);
    if (h_end == nullptr)
        return INTERACT_AGAIN;
    size_t h_len = h_end - mes;
    const char* start = mes;
    const char* end = strpbrk(mes, HTTP_SPARATOR);
    if (end == nullptr) {
        return INTERACT_ERROR;
    }
    //parser head
    *content = (char*)data + h_len + 4;
    size_t index = 0;
    while (start != end)
    {
        if (this->ParserHeadLine(index, start, end) == INTERACT_ERROR) {
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

int HttpResponseParser::GetContentType(char** contenttype)
{
    *contenttype = this->m_contentType;
    return INTERACT_OK;
}

int HttpResponseParser::GetContentLength(size_t &length)
{
    length = this->m_contentLength;
    return INTERACT_OK;
}

size_t HttpResponseParser::GetCode()
{
    return m_code;
}

int HttpResponseParser::GetSequence()
{
    return m_sequence;
}

int HttpResponseParser::ParserHeadLine(size_t index, const char* start, const char* end)
{
    size_t len = end - start;
    if (len >= m_maxLineLength) {
        return INTERACT_ERROR;
    }

    char line[m_maxLineLength];
    memcpy(line, start, len);
    line[len] = '\0';

    char* st = line;
    char* cursor;
    if (index == 0)
    {
        //version
        cursor = strpbrk(st, " \t");
        len = cursor - st;
        if (len >= m_maxHttpVersionLength || len == 0) {
            return INTERACT_ERROR;
        }
        memcpy(this->m_httpVersion, st, len);
        this->m_httpVersion[len] = '\0';
        while (*cursor == ' ' || *cursor == '\t')
        {
            cursor++;
        }
        st = cursor;
        //code
        cursor = strpbrk(st, " \t");
        len = cursor - st;
        if (len >= m_maxDesLength || len == 0) {
            return INTERACT_ERROR;
        }
        char code[m_maxDesLength];
        memcpy(code, st, len);
        code[len] = '\0';
        this->m_code = atoi(code);

        while (*cursor == ' ' || *cursor == '\t')
        {
            cursor++;
        }
        st = cursor;
        //http version
        len = strlen(cursor);
        if (len >= m_maxDesLength || len == 0) {
            return INTERACT_ERROR;
        }
        memcpy(this->m_httpDes, st, len);
        this->m_httpDes[len] = '\0';
    }
    else
    {
        cursor = strcasestr(st, "Content-Length");
        if (cursor)
        {
            size_t len;
            char length[m_maxContentTypeLength];
            if (st != cursor) {
                return INTERACT_ERROR;
            }
            cursor = strpbrk(st, ":");
            while (*(++cursor) == ' ' || *cursor == '\t');
            len = strlen(cursor);
            memcpy(length, cursor, len);
            length[len] = '\0';
            this->m_contentLength = atoi(length);
            return INTERACT_OK;
        }
        cursor = strcasestr(st, "Content-Type");
        if (cursor)
        {
            return ParserItem(st, cursor, &this->m_contentType[0]);
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
            memcpy(length, cursor, len);
            length[len] = '\0';
            m_sequence = atoi(length);
            return INTERACT_OK;
        }
    }
    return INTERACT_OK;
}

int HttpResponseParser::ParserItem(char* src, char* cursor, char* data)
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

