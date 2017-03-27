#ifndef __INTERACT_PROC_H__
#define __INTERACT_PROC_H__

namespace Interact
{
class InteractMessage;
class ProcAsync;
class InteractProc
{
public:
    InteractProc(ProcAsync *procAsync) : m_procAsync(procAsync) { }
    virtual ~InteractProc() {}

    virtual int OnProcess(InteractMessage *message) = 0;

protected:
    ProcAsync *GetAsync() { return m_procAsync; }

private:
    ProcAsync *m_procAsync;

}; // class InteractProc
} // namespace Interact


#endif // ifndef __INTERACT_PROC_H__

