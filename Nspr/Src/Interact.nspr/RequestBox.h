#ifndef __INTERACT_REQUEST_BOX_H__
#define __INTERACT_REQUEST_BOX_H__

namespace Interact
{

class InteractRequest;
class RequestBox
{
public:
    RequestBox();
    ~RequestBox();

    int Add(InteractRequest *req) { return INTERACT_OK; }
    InteractRequest *Popup() { return nullptr; }

}; // class RequestBox

} // namespace Interact



#endif // ifndef __INTERACT_REQUEST_BOX_H__

