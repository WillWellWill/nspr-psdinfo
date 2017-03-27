#ifndef __NSPR_STREAM_PROC_FACTORY_H_INCLUDED_H__
#define __NSPR_STREAM_PROC_FACTORY_H_INCLUDED_H__

#include <map>

namespace nspr
{

class StreamProc;
class StreamProcFactory
{
public:
    StreamProcFactory();
    virtual ~StreamProcFactory();

    StreamProc *GetStreamProc(char *url);
    StreamProc *GetStreamProc(int port, const char *desc);

    StreamProc *ProcessPortRange(int port);

private:
    std::map<std::string, StreamProc *> m_log;
    std::map<std::string, StreamProc *> m_src;
    std::map<std::string, StreamProc *> m_stream;

    static const int m_logFixedPort = 60001;
    
}; // class StreamProcFactory

} // namespace nspr

#endif // ifndef __NSPR_STREAM_PROC_FACTORY_H_INCLUDED_H__

