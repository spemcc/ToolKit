/* Created on: Mon Jul 14 17:14:44 2014 */
/* Author: smccrear */

#ifndef _TCPSOCKETINTERFACE_
#define _TCPSOCKETINTERFACE_

#include <inttypes.h>
#include <vector>
#include <string>
#include <assert.h>


namespace network {

class TcpSocketInterface {
	
  public:
    TcpSocketInterface() {}
    virtual ~TcpSocketInterface() {}

    virtual bool Read(std::vector<uint8_t>* output,uint32_t num_bytes) = 0;
    virtual bool Write(const std::vector<uint8_t>& data) = 0;
    virtual bool Close() = 0;
    virtual void set_socket_fd(int32_t socket_fd) = 0;

    /*Server Only*/ 
    virtual bool Bind(uint16_t port_num)  
    {   
      assert("Do not call me, TcpServerSocket only");
      return false;
    } 
    
    /*Server Only*/ 
    virtual bool Listen() 
    {   
      assert("Do not call me, TcpServerSocket only");
      return false;
    }

    /*Server Only*/ 
    virtual int  Accept()
    {   
      assert("Do not call me, TcpServerSocket only");
      return false;
    } 

    /*Client Only*/
    virtual bool Connect(std::string ip, uint16_t port_num, bool ip_v6=false)
    {   
      assert("Do not call me, TcpSocket only");
      return false;
    }

  protected:
    int32_t socket_fd_;
};
}

#endif  /* _TCPSOCKETINTERFACE_ */

