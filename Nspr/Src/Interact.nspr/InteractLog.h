#ifndef __INTERACT_LOG_H__
#define __INTERACT_LOG_H__

namespace Interact
{

#define INTLOG_DEBUG 100
#define INTLOG_INFO 101
#define INTLOG_WARN 102
#define INTLOG_ERROR 103

#ifndef WIN32
#define ILog(loglevel, format, args...) IR()->LogMessage(loglevel, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define IDebug(format, args...) ILog(INTLOG_DEBUG, format, ##args)
#define IInfo(format, args...) ILog(INTLOG_INFO, format, ##args)
#define IWarn(format, args...) ILog(INTLOG_WARN, format, ##args)
#define IError(format, args...) ILog(INTLOG_ERROR, format, ##args)
#else
#define ILog(loglevel, format, ...) IR()->LogMessage(loglevel, __FILE__, __FUNCTION__, __LINE__, format, __VA_ARGS__)
#define IDebug(format, ...) ILog(INTLOG_DEBUG, format, __VA_ARGS__)
#define IInfo(format, ...) ILog(INTLOG_INFO, format, __VA_ARGS__)
#define IWarn(format, ...) ILog(INTLOG_WARN, format, __VA_ARGS__)
#define IError(format, ...) ILog(INTLOG_ERROR, format, __VA_ARGS__)
#endif

class InteractLog
{
public:
    virtual void Log(const uint8_t *logData, size_t logLen) = 0;

}; // class InteractLog

} // namespace Interact




#endif // ifndef __INTERACT_LOG_H__

