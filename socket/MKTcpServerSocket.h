#ifndef _MKTCPSERVERSOCKET_
#define _MKTCPSERVERSOCKET_

#include "MKTcpSocket.h"

class MKTcpServerSocket : public MKTcpSocket
{
  public: 
    MKTcpServerSocket();
    ~MKTcpServerSocket();

    bool Bind(uint16_t portNum);
    int Accept();
    bool Listen();
    
  private:

};

#endif /* _MKTCPSERVERSOCKET_ */
