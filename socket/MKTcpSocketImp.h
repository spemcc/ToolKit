/* Created on: Mon Jul 14 19:14:16 2014 */
/* Author: smccrear */

#ifndef _MKTCPSOCKETIMP_
#define _MKTCPSOCKETIMP_

#include "MKSocketInterface.h"
#include <string>

class MKTcpSocketImp : public MKSocketInterface {
  public:
    MKTcpSocketImp();
    virtual ~MKTcpSocketImp();
    
    virtual bool Read(std::vector<uint8_t>* output, int numBytes);
    virtual bool Write(const std::vector<uint8_t>& data);
    virtual bool Close();
    virtual void SetSocket(int socketfd);

    virtual bool Bind(uint16_t portNum);
    virtual bool Listen();
    virtual int  Accept();
    virtual bool Connect(std::string ip, uint16_t portNum, bool IPV6=false);
 
  protected:
    int socketfd;
};


#endif  /* _MKTCPSOCKETIMP_ */

