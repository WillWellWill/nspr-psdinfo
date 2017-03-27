#include "InteractGlobal.h"

#include "InteractClient.h"
#include "UT/InteractConnect.h"


namespace Interact
{

static InteractConnect *m_connect;

class MyInteractClientCB : public InteractClientCB
{
public:
    MyInteractClientCB() {}
    virtual ~MyInteractClientCB() {}
    virtual int DataOut(const uint8_t *data, size_t len);
    virtual int OnStatus(Status status, Metadata *data);
    virtual int OnNotify(Notify status, const uint8_t *data, size_t len);
    virtual void Log(const uint8_t *logData, size_t logLen);

};

class MyDataRecv: public InteractConnectCB
{
public:
    MyDataRecv(InteractClient *ic){ this->m_ic = ic; };
    ~MyDataRecv(){};
    virtual int OnRecv(char *data, size_t len);

private:
    InteractClient *m_ic;
};

int MyInteractClientCB::DataOut(const uint8_t *data, size_t len)
{
    m_connect->Send((char *)data, len);
    return INTERACT_OK;
}

int MyInteractClientCB::OnStatus(Status status, Metadata *data)
{
    printf("OnStatus:%d\n", status);
    return INTERACT_OK;
}

int MyInteractClientCB::OnNotify(Notify status, const uint8_t *data, size_t len)
{
    printf("OnNotify:%d\n", status);
    return INTERACT_OK;
}
void MyInteractClientCB::Log(const uint8_t *logData, size_t logLen)
{
    printf("%s\n", (char *)logData);
}

int MyDataRecv::OnRecv(char* data, size_t len)
{
    return this->m_ic->DataIn((const uint8_t *)data, len);
}
}

using namespace Interact;

static Metadata playMetadata = {
    IC_MODE_PLAY,
    {
        512000,//int bitrate;
        IC_VIDEO_CODECID_H264,//int codecID;
        25,//int frameRate;
        IC_RES_VGA,//ICResulution resolution;
        
        50000,//int srcPort;
        50000,//int dstPort;
        166666,//int ssrc;
        0//int payloadType;
    },
    {
        32000,
        IC_CODECID_UNKOWN,
        441000,//int sampleRate;
        16000,//int sampleSize;
        2,//int channelCnt;
        50002,//int srcPort;
        50002,//int dstPort;
        18888,//int ssrc;
        1//int payloadType;    
    }
};

static InteractClient *m_ic;

int singalShoot(int i)
{
    switch (i) {
        case 1:
            m_ic->Connect(&playMetadata);
            break;
        case 2:
            m_ic->Publish();
            break;
        case 3:
            m_ic->Ping();
            break;
        case 4:
            m_ic->Close();
            break;
        default:
            break;
    }
    return 0;
}

int mainloop()
{
    int i = 0, ind = 0;
    m_connect = new InteractConnect();
    m_connect->Init();
    MyInteractClientCB *my_cb = new MyInteractClientCB();
    m_ic = new InteractClient((char *)"http://127.0.0.1:1688/live/xyz", my_cb);
    while (true) {
        usleep(40*1000);
        i++;
        if (i % 50 == 0) {
            ind ++;
            singalShoot(ind);
        }
    }
    delete m_ic;
    delete m_connect;
    return 0;
}

int main()
{
    mainloop();
    return 0;
}

