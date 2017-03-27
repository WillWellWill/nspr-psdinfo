#ifndef __TEST_INTERACT_CONNECTION_H__
#define __TEST_INTERACT_CONNECTION_H__

#define RECV_OK 0
#define RECV_AGAIN -1
#define RECV_ERROR -2

class InteractConnectCB{
public:
    virtual int OnRecv(char *data, size_t len) = 0;
};
class InteractConnect
{
public:
    InteractConnect();
    ~InteractConnect();

    enum ConnectStatus{
        Disconnected,
        Connected,
        Closeed
    };

    int Init();

    int Connect(const char *host, const char* port, InteractConnectCB *cb);

    int Send(char *data, size_t len);

    int Close();

    int Loop();
private:
    int CallBack(char *data, size_t len);
    

    int m_fd;
    ConnectStatus m_status;
    InteractConnectCB *m_cb;

};
#endif
