#ifndef __NSPR_STATISTICS_CONNECTION_H_INCLUDED__
#define __NSPR_STATISTICS_CONNECTION_H_INCLUDED__

#include "MsgConnection.h"

namespace nspr
{

void timerRunFunc(ngx_event_t *ev);

class StatisticsConnection : public MsgConnection
{
public:
	StatisticsConnection(ngx_connection_t *c);
	virtual ~StatisticsConnection();

	virtual int OnRecv(const u_char *msg, size_t len);

    static const u_char *GetStatistics() { return &m_statistics[0]; }
    static int GetStatisticsLen() { return m_statisticsLen; }

private:
    ngx_event_t m_timer;
    const static int m_defaultStatisticsGap = 2000;
    const static int m_defaultMaxStatisticsLen = 800 * 1024;
    static u_char m_statistics[m_defaultMaxStatisticsLen];
    static int m_statisticsLen;

private:
    void TimerStart();
    void RequestStatistics();
    friend void timerRunFunc(ngx_event_t *ev);
}; // class StatisticsConnection

} // namespace nspr

#endif // ifndef __NSPR_STATISTICS_CONNECTION_H_INCLUDED__

