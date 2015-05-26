/* Created on: Mon Jul 21 22:25:01 2014 */
/* Author: smccrear */

#ifndef _MKTCPCLIENTSOCKET_
#define _MKTCPCLIENTSOCKET_

#include "MKTcpSocket.h"

class MKTcpClientSocket : public MKTcpSocket 
{
	public:
		MKTcpClientSocket();
		~MKTcpClientSocket();
    bool Connect(std::string ip, uint16_t port_num, bool IPV6=false);

};


#endif  /* _MKTCPCLIENTSOCKET_ */

