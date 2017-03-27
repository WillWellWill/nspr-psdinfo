#ifndef __INTERACT_GLOBAL_H__
#define __INTERACT_GLOBAL_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <string>
#include <stdarg.h>

#ifndef WIN32
#ifndef override
#define override
#endif // !override

#ifndef nullptr
#define nullptr NULL
#endif

#endif

#ifdef WIN32
#define strncasecmp _strnicmp
#define strcasestr strstr
#endif // WIN32

#include "InteractResource.h"
#include "InteractObject.h"
#include "Metadata.h"
#include "InteractLog.h"

#define INTERACT_OK 0
#define INTERACT_ERROR -1
#define INTERACT_AGAIN -8

#define InteractCopy(dst, dstSize, src)  \
    memcpy((dst), (src), strlen(src) + 1 < (dstSize) ? strlen(src) + 1 : (dst[dstSize - 1] = 0, (dstSize) - 1));


#define INTERACT_HANDLE_ERROR(op) if(op == INTERACT_ERROR) return NGX_ERROR

#define INTERACT_HANDLE_ERROR_AGAIN(OP) if (op != INTERACT_OK) return NGX_ERROR


#endif // ifndef __INTERACT_GLOBAL_H__

