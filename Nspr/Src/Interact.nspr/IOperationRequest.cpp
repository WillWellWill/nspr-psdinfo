#include "InteractGlobal.h"

#include "IOperationRequest.h"


namespace Interact
{

IOperationRequest::IOperationRequest(int optype)
    : m_opType((OpType)optype)
{

}

IOperationRequest::IOperationRequest(const uint8_t *msg, size_t len)
{

}

IOperationRequest::~IOperationRequest()
{

}

} // namespace Interact

