#include "Nspr.h"

#include "ApiDispatcher.h"

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
    (void)req;
    (void)cb;
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

} // namespace nspr
