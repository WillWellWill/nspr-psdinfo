#include "Nspr.h"

#include "StreamProcFactory.h"
#include "LogStreamProc.h"
#include "Utility.h"

namespace nspr
{

StreamProcFactory::StreamProcFactory()
{
    m_log[std::string("haha")] = new LogStreamProc();
}

StreamProcFactory::~StreamProcFactory()
{

}

StreamProc *StreamProcFactory::GetStreamProc(char *url)
{
    if (!ngx_strncmp(url, "log://", 6)) {
        return m_log[std::string("haha")];
    }
    return new EmptyStreamProc();
}

StreamProc *StreamProcFactory::GetStreamProc(int port, const char *desc)
{
	(void)desc;
    switch (port) {
    case m_logFixedPort:
        return m_log[std::string("haha")];
    default:
        return ProcessPortRange(port);
    }
    return nullptr;
}

StreamProc *StreamProcFactory::ProcessPortRange(int port)
{
	char portStr[64] = {0};
	snprintf(portStr, sizeof(portStr), "localport-%d", port);
	std::map<std::string, StreamProc *>::iterator it = m_src.find(std::string(portStr));
	if (it == m_src.end()) {
		return nullptr;
	}
	//NsprInfo("find proc %p, with port %d", it->second, port);
    return it->second;
}

} // namespace nspr

