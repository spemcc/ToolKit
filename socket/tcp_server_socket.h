#ifndef _TCPSERVERSOCKET_
#define _TCPSERVERSOCKET_

#include "tcp_socket_interface.h"

namespace network {

class TcpServerSocket : public TcpSocketInterface
{
  public: 
    TcpServerSocket();
    ~TcpServerSocket();

    bool Bind(uint16_t port_num);
    int Accept();
    bool Listen();
    
  private:

};
}

#endif /* _TCPSERVERSOCKET_ */
