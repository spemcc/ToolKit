#ifndef _MKTCPSERVERSOCKET_
#define _MKTCPSERVERSOCKET_

#include "MKTcpSocketImp.h"

class MKTcpServerSocket : public MKTcpSocketImp 
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
