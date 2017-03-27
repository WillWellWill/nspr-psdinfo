#ifndef __INTERACT_OPERATION_REQUEST_H__
#define __INTERACT_OPERATION_REQUEST_H__

#include "InteractRequest.h"

namespace Interact
{

class IOperationRequest : public InteractRequest
{
public:
    IOperationRequest(int type);
    IOperationRequest(const uint8_t *msg, size_t len);
    virtual ~IOperationRequest();

    virtual MsgType GetMsgType() { return OPERATION; };

    enum OpType
    {
        PLAY = 0,
        PUBLISH,
        PING
    };
    OpType Operation() { return m_opType; }
    void SetOpType(OpType type) { m_opType = type; }
private:
    OpType m_opType;

}; // class IOperationRequest

} // namespace Interact

#endif // ifndef __INTERACT_OPERATION_REQUEST_H__

