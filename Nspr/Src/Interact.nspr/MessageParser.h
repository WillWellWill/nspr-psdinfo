#ifndef __INTERACT_MESSAGE_PARSER_H__
#define __INTERACT_MESSAGE_PARSER_H__

namespace Interact
{
class MessageParser : public InteractObject
{
public:
    enum MPResult
    {
        NOT_ENOUGH = -8,
        ERROR_DATA = -1,
        OK = 0,
    };
    virtual int Preparse(uint8_t *data, size_t len) = 0;

}; // class MessageParser
} // namespace Interact



#endif // ifndef __INTERACT_MESSAGE_PARSER_H__

