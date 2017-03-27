#ifndef __INTERACT_RESOURCE_H__
#define __INTERACT_RESOURCE_H__

namespace Interact
{

class InteractLog;
class InteractResource
{
public:
    InteractResource(InteractLog *log);
    InteractResource();
    ~InteractResource();

    void LogMessage(int loglevel, const char *file, const char *func, int line, const char *format, ...);

private:
    InteractLog *m_logger;
    static InteractLog *m_backupLogger;
    const static unsigned m_maxLogMessageLen = 1024;

}; // class InteractResource
} // namespace Interact


#endif // ifndef __INTERACT_RESOURCE_H__

