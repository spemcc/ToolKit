/* Created on: Mon Jul 14 19:14:16 2014 */
/* Author: smccrear */

#ifndef _MKTCPSOCKET_
#define _MKTCPSOCKET_

#include "MKSocketInterface.h"
#include <string>

class MKTcpSocket : public MKSocketInterface {
  public:
    MKTcpSocket();
    virtual ~MKTcpSocket();
    
    virtual bool Read(std::vector<uint8_t>* output, int num_bytes);
    virtual bool Write(const std::vector<uint8_t>& data);
    virtual bool Close();
    virtual void set_socket(int socket_fd);

    virtual bool Bind(uint16_t port_num);
    virtual bool Listen();
    virtual int  Accept();
    virtual bool Connect(std::string ip, uint16_t port_num, bool IPV6=false);
 
  protected:
    int socket_fd_;
};


#endif  /* _MKTCPSOCKET_ */

