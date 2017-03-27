#include "InteractGlobal.h"

#include "InteractClient.h"
#include "InteractClientImp.h"

namespace Interact
{

InteractClient::InteractClient(char *url, InteractClientCB *cb)
    : m_imp(new InteractClientImp(url, cb))
{

}

InteractClient::~InteractClient()
{
    delete m_imp;
}

int InteractClient::DataIn(const uint8_t *data, size_t len)
{
    return m_imp->DataIn(data, len);
}
    
int InteractClient::Connect(Metadata *mdata)
{
    return m_imp->Connect(mdata);
}

int InteractClient::Play()
{
    return m_imp->Play();
}

int InteractClient::Publish()
{
    return m_imp->Publish();
}

int InteractClient::Ping()
{
    return m_imp->Ping();
}
int InteractClient::Close()
{
    return m_imp->Close();
}

} // namespace Interact

