#include "InteractGlobal.h"

#include "SessionDescription.h"


namespace Interact
{

SessionDescription::SessionDescription()
{
}

SessionDescription::~SessionDescription()
{
}


const char *SessionDescription::SessionIdOf(char *sessionDesc, size_t *len)
{
    char tmp[4096] = {0};
    memcpy(&tmp[0], sessionDesc, strlen(sessionDesc) < 4095 ? strlen(sessionDesc) : (tmp[4095] = 0 , 4095));
    const char *valueBeg = strstr(tmp, "sid=");
	if (valueBeg) {
		const char *valueEnd = strchr(valueBeg, '\n');
		if (valueBeg && valueEnd) {
			*len = valueEnd - (valueBeg + 4);
			return sessionDesc + (valueBeg + 4 - tmp);
		}
	}
    *len = 0;
    return "";
}

const char *SessionDescription::TypeOf(char *sessionDesc, size_t *len)
{
    char tmp[4096] = {0};
    memcpy(&tmp[0], sessionDesc, strlen(sessionDesc) < 4095 ? strlen(sessionDesc) + 1 : (tmp[4095] = 0 , 4095));
    const char *valueBeg = strstr(tmp, "typ=");
    if (valueBeg) {
   		const char *valueEnd = strchr(valueBeg, '\n');
    	if (valueEnd) {
        	*len = valueEnd - (valueBeg + 4);
        	return sessionDesc + (valueBeg + 4 - tmp);
    	}
	}
    *len = 0;
    return "";
}

const char *SessionDescription::MediaDescOf(char *sessionDesc, size_t *len)
{
    char tmp[4096] = {0};
    memcpy(&tmp[0], sessionDesc, strlen(sessionDesc) < 4095 ? strlen(sessionDesc) + 1 : (tmp[4095] = 0 , 4095));
    const char *mediaBeg = strstr(tmp, "m=");
    if (mediaBeg) {
        *len = strlen(mediaBeg);
        return sessionDesc + (mediaBeg - tmp);
    }
    *len = 0;
    return "";
}

void SessionDescription::MediaDescOf(const char *sessionDesc, Metadata *metadata)
{
    char tmp[4096] = {0};
    memcpy(&tmp[0], sessionDesc, strlen(sessionDesc) < 4095 ? strlen(sessionDesc) + 1 : (tmp[4095] = 0 , 4095));
    const char *mediaBeg = strstr(tmp, "m=");
    if (!mediaBeg) {
        return;
    }
    int numbers[sizeof(Metadata)/sizeof(int)] = {0};
    char *p = (char *)mediaBeg;
    for (int i = 0, j = 0; i < (int)(sizeof(numbers) / sizeof(int) + 2); i++) {
        char *vb = (char *)strchr(p, '=');
        char *ve = (char *)strchr(p, '\n');
        if (!vb || !ve) {
            return;
        }
        if (*(vb - 1) == 'v' || *(vb - 1) == 'a') {
            p = ve + 1;
            continue;
        }
        ++vb;
        *ve = 0;
        numbers[j++] = atoi(vb);
        p = ve + 1;
    }
    memcpy(metadata, &numbers[0], sizeof(Metadata));
}

void SessionDescription::AssembleMetadata(Metadata *metadata, char *container, size_t size)
{
    Metadata &m = *metadata;
    snprintf(container + strlen(container), size - strlen(container) - 1, "m=%d\n"
                                           "v=%d\nbr=%d\ncid=%d\nfr=%d\nres=%d\nsp=%d\ndp=%d\nss=%d\npt=%d\n"
                                           "a=%d\nbr=%d\ncid=%d\nsr=%d\nsas=%d\ncc=%d\nsp=%d\ndp=%d\nss=%d\npt=%d\n"
                                         , m.mode
                                         , 0, m.v.bitrate, m.v.codecID, m.v.frameRate, m.v.resolution
                                         ,    m.v.srcPort, m.v.dstPort, m.v.ssrc, m.v.payloadType
                                         , 0, m.a.bitrate, m.a.codecID, m.a.sampleRate, m.a.sampleSize, m.a.channelCnt
                                         ,    m.a.srcPort, m.a.dstPort, m.a.ssrc, m.a.payloadType);
}

size_t SessionDescription::AssembleBy(Metadata *metadata, char *container, size_t size)
{
    container[0] = 0;
    AssembleMetadata(metadata, container, size);
    return strlen(container);
}

size_t SessionDescription::AssembleBy(const char *sid, const char *type, Metadata *metadata, char *container, size_t size)
{
    snprintf(container, size, "sid=%s\ntyp=%s\n", sid, type);
    AssembleMetadata(metadata, container, size);
    return strlen(container);
}

} // namespace Interact




