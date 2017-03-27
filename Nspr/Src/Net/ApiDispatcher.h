#ifndef __NSPR_API_DISPATCHER_H_INCLUDED__
#define __NSPR_API_DISPATCHER_H_INCLUDED__

namespace nspr
{
class ApiDispatcher
{
public:
    ApiDispatcher();
    ~ApiDispatcher();

    int OnRequest(ngx_http_request_t *r, nspr_http_response_cb cb);
    
private:
    const static int m_maxResponseStrLen = 64 * 1024;
    u_char m_responseStr[m_maxResponseStrLen];
    ngx_chain_t *m_response;
    
private:
    int SearchArgs(ngx_str_t a, u_char *k, size_t klen, u_char *v, size_t vlen);

}; // class ApiDispatcher


} // namespace nspr

#endif // ifndef __NSPR_API_DISPATCHER_H_INCLUDED__

