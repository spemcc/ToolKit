/* Created on: Mon Jul 14 17:14:44 2014 */
/* Author: smccrear */

#ifndef _TCPSOCKETINTERFACE_
#define _TCPSOCKETINTERFACE_

#include <assert.h>
#include <inttypes.h>
#include <string>
#include <sys/socket.h>
#include <vector>

namespace network {

class TcpSocketInterface {
	
  public:
    TcpSocketInterface() {}
    virtual ~TcpSocketInterface() {}

    virtual bool Read(std::vector<uint8_t>* output,const uint32_t& num_bytes)
    {
      int32_t bytes_recieved = 0;
      int32_t total_bytes_recieved = 0;

      while(total_bytes_recieved != static_cast<int32_t>(num_bytes))
      {
        bytes_recieved = recv(socket_fd_, &(output->at(0)), num_bytes, 0);
        if(bytes_recieved == -1)
          return false;
        total_bytes_recieved += bytes_recieved;
      }
      return true;
    }

    virtual bool Write(const std::vector<uint8_t>& data)
    {
      int32_t num_bytes = data.size();
      int32_t bytesSent = 0;
      int32_t totalBytesSent= 0;

      while(totalBytesSent!= num_bytes)
      {
        bytesSent = send(socket_fd_,&(data.at(0)),num_bytes, 0);
        if(bytesSent == -1)
          return false;
        totalBytesSent += bytesSent ;
      }
      return true;
    }

    virtual bool Close()
    {
      return !(close(socket_fd_));
    }

    virtual void set_socket_fd(const int32_t& socket_fd) { socket_fd_ = socket_fd; }

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
    virtual bool Connect(const std::string& ip, 
                         const uint16_t& port_num,
                         const bool& ip_v6=false)
    {   
      assert("Do not call me, TcpSocket only");
      return false;
    }

  protected:
    int32_t socket_fd_;
};
}

#endif  /* _TCPSOCKETINTERFACE_ */

