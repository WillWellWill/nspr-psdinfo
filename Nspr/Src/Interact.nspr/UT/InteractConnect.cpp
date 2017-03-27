#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "InteractConnect.h"


#define BUF_SIZE 500

using namespace std;

InteractConnect::InteractConnect()
    : m_fd(0)
    , m_status(Disconnected)
    , m_cb(nullptr)
{
    
}
InteractConnect::~InteractConnect()
{
    
}


int InteractConnect::Init()
{
    m_status = Disconnected;
    return 0;
}

int InteractConnect::Connect(const char *host, const char* port, InteractConnectCB *cb)
{
    
    if (m_status != Disconnected) {
        fprintf(stderr, "The connect has connected or closeed :%d", m_status);
        return 1;
    }
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(host, port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        m_fd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (m_fd == -1)
            continue;

        if (connect(m_fd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

        close(m_fd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        return 1;
    }
    
    freeaddrinfo(result);           /* No longer needed */
    m_status = Connected;
    m_cb = cb;
    return 0;
}

int InteractConnect::Send(char *data, size_t len)
{
    
    if (m_status != Connected) {
        fprintf(stderr, "The connect has not in connected:%d", m_status);
        return 1;
    }
    /* Send remaining command-line arguments as separate
       datagrams, and read responses from server */
    ssize_t sen = 0;
    while(sen < (ssize_t)len) {
        ssize_t sen = write(m_fd, data, len);
        if (sen == -1) {
            fprintf(stderr, "partial/failed write\n");
            return 1;
        }
    }

    return 0;
}

int InteractConnect::Loop()
{
    if (m_status != Connected) {
        fprintf(stderr, "The connect has not in connected:%d", m_status);
        return 1;
    }
    ssize_t nread;
    char buf[BUF_SIZE];
    nread = read(m_fd, buf, BUF_SIZE);
    if (nread == -1) {
        perror("read");
        return 1;
    }

    int ret = RECV_ERROR;
    if (m_cb != NULL) {
        ret = CallBack(buf, nread);
        if (ret == RECV_ERROR) {
            //parser error
            return RECV_ERROR;
        }
        else if (ret == RECV_OK || ret == RECV_AGAIN) {
            return 0;
        }
    }
    /*
     *printf("Received %zd bytes: %s\n", nread, buf);
     */
    return 0;
}


int InteractConnect::CallBack(char *data, size_t len)
{

    int ret = m_cb->OnRecv(data, len);
    if (ret == RECV_AGAIN) {
        return 0;
    }
    else if(ret == RECV_ERROR) {
        return 1;
    }
    else {
        return CallBack(data + ret, len - ret);
    }
}

int InteractConnect::Close()
{
    if (m_status != Connected) {
        fprintf(stderr, "The connect has not in connected:%d", m_status);
        return 1;
    }
    if (close(m_fd) == -1) 
        return 1;
    m_status = Closeed;
    return 0;
}
/*
 *int main(int argc, char *argv[])
 *{
 *}
 */
