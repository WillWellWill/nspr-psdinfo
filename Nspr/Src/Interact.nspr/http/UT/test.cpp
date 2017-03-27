#ifndef __poseidon_protocol_http_test__
#define __poseidon_protocol_http_test__

#include "InteractGlobal.h"
#include "HttpRequestPacker.h"
#include "HttpRequestParser.h"
#include "HttpResponsePacker.h"
#include "HttpResponseParser.h"
#include "gtest/gtest.h"

#include <stdio.h>
#include <string.h>

const static int g_httpTestContentLength = 4096;
TEST(HttpRequestPacker, Packer) {
    Interact::HttpRequestPacker reqpacker;
    ASSERT_EQ(INTERACT_OK,reqpacker.SetUrl("http://127.0.0.1:1688/live/xyz"));
    ASSERT_EQ(INTERACT_OK,reqpacker.SetMethod(Interact::IHttpPacker::POST));
    ASSERT_EQ(INTERACT_OK,reqpacker.SetUserAgent("windows nt"));
    ASSERT_EQ(INTERACT_OK,reqpacker.SetContentType("text/json"));
    //ASSERT_EQ(INTERACT_OK,reqpacker.SetContent((char*)"hello word!"));
    ASSERT_EQ(INTERACT_OK,reqpacker.SetContentLength(11));
    char content[g_httpTestContentLength];
    char* ch = content;
    ASSERT_EQ(INTERACT_OK,reqpacker.PackerHead(ch, g_httpTestContentLength));

    printf("http: %s", content);
}

TEST(HttpRequestParser, HttpRequestParserTest) {
    const char* str = "GET /gywm/aboutus/ HTTP/1.1\r\n"
        "Host: www.100tal.com\r\n"
        "Cache-Control: max-age=0\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "Accept-Encoding: gzip, deflate, sdch\r\n"
        "Accept-Language: zh-CN,zh;q=0.8\r\n\r\n";
    Interact::HttpRequestParser reqparser;
    ASSERT_EQ(INTERACT_OK,reqparser.Parser(str, strlen(str)));
    char *method;
    ASSERT_EQ(INTERACT_OK,reqparser.GetMethod(&method));
    ASSERT_STREQ("GET", method); 
    char *host;
    ASSERT_EQ(INTERACT_OK,reqparser.GetHost(&host));
    ASSERT_STREQ("www.100tal.com", host);
    char *contentType;
    ASSERT_EQ(INTERACT_OK,reqparser.GetContentType(&contentType));
    int length = 0;
    ASSERT_EQ(INTERACT_OK,reqparser.GetContentLength(length));
    printf("http parser \nmethod:%s\nhost:%s\ncontent-type:%s\ncontent-lenght:%d\n", method, host, contentType, length);
}

TEST(HttpResponsePacker, HttpResponsePackerTest) {
    Interact::HttpResponsePacker respacker;
    ASSERT_EQ(INTERACT_OK,respacker.SetCode(200));
    ASSERT_EQ(INTERACT_OK,respacker.SetCodeDes("OK"));
    ASSERT_EQ(INTERACT_OK,respacker.SetContentType("test/json"));
    ASSERT_EQ(INTERACT_OK,respacker.SetContentLength(11));
    //ASSERT_EQ(INTERACT_OK,respacker.SetContent((char*)"hello word!"));

    char rescontent[g_httpTestContentLength];
    char* ch = rescontent;
    ASSERT_EQ(INTERACT_OK,respacker.PackerHead(ch, g_httpTestContentLength));
    
}
    
TEST(HttpResponseParser, HttpResponseParserTest) {
        Interact::HttpResponseParser resparser;
        const char* testresponse = "HTTP/1.1 200 OK\r\n"
            "Server: nginx\r\n"
            "Date: Wed, 04 Jan 2017 02:46:05 GMT\r\n"
            "Content-Type: text/html\r\n"
            "Vary: Accept-Encoding\r\n"
            "Content-Encoding: gzip\r\n"
            "Transfer-Encoding: chunked\r\n"
            "Proxy-Connection: Close\r\n\r\n";
        ASSERT_EQ(INTERACT_OK,resparser.Parser(testresponse, strlen(testresponse)));
        int code = resparser.GetCode();
        ASSERT_EQ(200,code);
        char contentType[100];
        char *ct = contentType;
        ASSERT_EQ(INTERACT_OK,resparser.GetContentType(&ct));
        int length;
        ASSERT_EQ(INTERACT_OK,resparser.GetContentLength(length));
}

#endif // !__poseidon_protocol_http_test__
