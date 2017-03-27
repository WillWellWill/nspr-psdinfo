#ifndef __INTERACT_SESSION_DESCRIPTION_H__
#define __INTERACT_SESSION_DESCRIPTION_H__

namespace Interact
{

class SessionDescription
{
public:
    SessionDescription();
    virtual ~SessionDescription();

    const char *SessionIdOf(char *sessionDesc, size_t *len);
    const char *TypeOf(char *sessionDesc, size_t *len);
    const char *MediaDescOf(char *sessionDesc, size_t *len);
    void MediaDescOf(const char *sessionDesc, Metadata *metadata);

    size_t AssembleBy(Metadata *metadata, char *container, size_t size);
    size_t AssembleBy(const char *sid, const char *type, Metadata *metadata, char *container, size_t size);

private:
    void AssembleMetadata(Metadata *metadata, char *container, size_t size);

}; // class SessionDescription

} // namespace Interact



#endif // ifndef __INTERACT_SESSION_DESCRIPTION_H__

