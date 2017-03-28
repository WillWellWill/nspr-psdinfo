#include "Nspr.h"

#include "StatisticsConnection.h"


namespace nspr
{

u_char StatisticsConnection::m_statistics[m_defaultMaxStatisticsLen];
int StatisticsConnection::m_statisticsLen = 0;
StatisticsConnection::StatisticsConnection(ngx_connection_t *c)
    : MsgConnection(c)
{
    NsprInfo("statistics connection created");
    TimerStart();
}

StatisticsConnection::~StatisticsConnection()
{
    NsprInfo("statistics connection destroyed");
    ngx_del_timer(&m_timer);
}

int StatisticsConnection::OnRecv(const u_char *msg, size_t len)
{
    if (len < 4) {
        return NSPR_AGAIN;
    }

    uint32_t const msgLen = *(uint32_t *)msg;
    if (len < msgLen) {
        return NSPR_AGAIN;
    }
    int const dataLen = msgLen - 4;
    assert(m_defaultMaxStatisticsLen > dataLen);
    ngx_memcpy(m_statistics, msg + 4, dataLen);
    m_statistics[dataLen] = 0;
    m_statisticsLen = dataLen;

	return len - msgLen;
}

void StatisticsConnection::TimerStart()
{
    ngx_memzero(&m_timer, sizeof(m_timer));
    m_timer.handler = timerRunFunc;
    m_timer.log = ngx_cycle->log;
    m_timer.data = this;
    ngx_add_timer(&m_timer, m_defaultStatisticsGap);
}
    
void StatisticsConnection::RequestStatistics()
{
    const u_char *request = (const u_char *)"hello";
    Send(request, 5);
    ngx_add_timer(&m_timer, m_defaultStatisticsGap);
}

void timerRunFunc(ngx_event_t *ev)
{
    StatisticsConnection *sc = (StatisticsConnection *)ev->data;
    sc->RequestStatistics();
}

} // namespace nspr


