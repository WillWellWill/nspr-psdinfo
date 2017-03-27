#include "InteractGlobal.h"


#include "InteractResource.h"
#include "InteractLog.h"


namespace Interact
{

InteractLog *InteractResource::m_backupLogger = nullptr;
InteractResource::InteractResource(InteractLog *cb)
    : m_logger(cb)
{
    if (!m_backupLogger) {
        m_backupLogger = cb;
    }
}
    
InteractResource::InteractResource()
    : m_logger(nullptr)
{
}

InteractResource::~InteractResource()
{
    m_backupLogger = nullptr;
}

void InteractResource::LogMessage(int loglevel, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args; 
    va_start(args, format);
    char logBuffer[256] = {0};
    size_t len = 0;

    len += snprintf(logBuffer + len, sizeof(logBuffer) - 1 - len, "[%s.%d]: ", file, line);
    len += vsnprintf(logBuffer + len, sizeof(logBuffer) - 1 - len, format, args); 
    len += snprintf(logBuffer + len, sizeof(logBuffer) - 1 - len, "\n");
    va_end(args);
    
    if (m_logger) {
        (m_logger->Log)((const uint8_t *)logBuffer, len);
    }
    else if (m_backupLogger) {
        (m_backupLogger->Log)((const uint8_t *)logBuffer, len);
    }
}

}


