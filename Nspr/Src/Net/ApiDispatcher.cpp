#include "Nspr.h"

#include "ApiDispatcher.h"
#include "StatisticsConnection.h"

namespace nspr
{

ApiDispatcher::ApiDispatcher()
{
    ngx_buf_t *b = new ngx_buf_t;
    ngx_memzero(b, sizeof(ngx_buf_t));
    b->pos = b->last = b->start = &m_responseStr[0];
    b->end = b->start + m_maxResponseStrLen;
    b->memory = 1;
    b->last_buf = 1;
    
    m_response = new ngx_chain_t;
    ngx_memzero(m_response, sizeof(ngx_chain_t));
    m_response->buf = b;
}

ApiDispatcher::~ApiDispatcher()
{
    delete m_response->buf;
    delete m_response;
}

int ApiDispatcher::OnRequest(ngx_http_request_t *req, nspr_http_response_cb cb)
{
    const ngx_str_t uri = req->uri;
    if (!ngx_strncmp(uri.data, "/api/statistics/query", sizeof("/api/statistics/query") - 1)) {
        return DispatcStatisticsQuery(req, cb);
    }
    return NGX_HTTP_OK;
}

int ApiDispatcher::SearchArgs(ngx_str_t a, u_char *k, size_t klen, u_char *v, size_t vlen)
{
    u_char *vb = (u_char *)ngx_strstr(a.data, k),
           *ve = (u_char *)ngx_strchr(a.data, '&');
    if (!ve || ve > a.data + a.len) {
        ve = a.data + a.len;
    }
    vb += klen;
    const int len = ve - vb;
    if (len >= (int)vlen) {
        memcpy(v, vb, vlen - 1);
    }
    else {
        memcpy(v, vb, len);
    }
    return NSPR_OK;
}
    
int ApiDispatcher::DispatcStatisticsQuery(ngx_http_request_t *r, nspr_http_response_cb cb)
{
    int len;
    if (StatisticsConnection::GetStatisticsLen() == 0) {
        len = snprintf((char *)m_responseStr, sizeof(m_responseStr), "{\"status\":\"not ready\", \"statistics\":{}}");
    }
    else {
        len = snprintf((char *)m_responseStr, sizeof(m_responseStr), "{\"status\":\"ok\", \"statistics\":%s}", StatisticsConnection::GetStatistics());
    }
    m_response->buf->pos = m_responseStr;
    m_response->buf->last = m_responseStr + len;
    cb(r, m_response);
    return NGX_HTTP_OK;
}

} // namespace nspr
