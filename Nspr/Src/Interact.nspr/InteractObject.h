#ifndef __INTERACT_OBJECT_H__
#define __INTERACT_OBJECT_H__

#define HTTP_SPARATOR "\r\n"
namespace Interact
{

class InteractResource;
class InteractObject
{
public:
    InteractObject(InteractResource *ir)
        : m_ir(ir)
        , m_interalIR(nullptr) {}
    InteractObject()
        : m_ir(nullptr)
        , m_interalIR(new InteractResource()) { m_ir = m_interalIR; }
    virtual ~InteractObject() { delete m_interalIR; }
    virtual InteractResource *IR() { return m_ir; }

private:
    InteractResource *m_ir;
    InteractResource *m_interalIR;

}; // class InteractObject


} // namespace nspr


#endif // ifndef __INTERACT_OBJECT_H__

