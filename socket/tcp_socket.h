/* Created on: Mon Jul 21 22:25:01 2014 */
/* Author: smccrear */

#ifndef _TCPSOCKET_
#define _TCPSOCKET_

#include "tcp_socket_interface.h"

class TcpSocket : public TcpSocketInterface
{
	public:
		TcpSocket();
		~TcpSocket();
    bool Connect(std::string ip, uint16_t port_num, bool IPV6=false);

};

#endif  /* _TCPSOCKET_ */
