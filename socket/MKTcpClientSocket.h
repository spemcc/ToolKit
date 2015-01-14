/* Created on: Mon Jul 21 22:25:01 2014 */
/* Author: smccrear */

#ifndef _MKTCPCLIENTSOCKET_
#define _MKTCPCLIENTSOCKET_

#include "MKTcpSocketImp.h"

class MKTcpClientSocket : public MKTcpSocketImp {
	public:
		MKTcpClientSocket();
		~MKTcpClientSocket();
    bool Connect(std::string ip, uint16_t portNum, bool IPV6=false);
  private:

};


#endif  /* _MKTCPCLIENTSOCKET_ */

