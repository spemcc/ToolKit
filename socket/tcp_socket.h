/* Created on: Mon Jul 21 22:25:01 2014 */
/* Author: smccrear */

#ifndef _TCPSOCKET_
#define _TCPSOCKET_

#include "tcp_socket_interface.h"

namespace network {

class TcpSocket : public TcpSocketInterface
{
	public:
		TcpSocket();
		~TcpSocket();
    bool Connect(const std::string& ip,const uint16_t& port_num,const bool& ipv6=false);

};
}

#endif  /* _TCPSOCKET_ */
