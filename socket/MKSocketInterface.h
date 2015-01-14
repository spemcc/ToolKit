/* Created on: Mon Jul 14 17:14:44 2014 */
/* Author: smccrear */

#ifndef _MKSOCKETINTERFACE_
#define _MKSOCKETINTERFACE_

#include <inttypes.h>
#include <vector>
#include <string>


class MKSocketInterface {
	
  public:
    MKSocketInterface() {}
    virtual ~MKSocketInterface() {}

    virtual bool Read(std::vector<uint8_t>* output,int numBytes) = 0;
    virtual bool Write(const std::vector<uint8_t>& data) = 0;

    virtual bool Bind(uint16_t portNum) = 0; //Server Only
    virtual bool Listen() = 0;               //Server Only
    virtual int  Accept() = 0;                //Server Only
    virtual bool Connect(std::string ip, uint16_t portNum, bool IPV6=false) =0; //Client Only

    virtual bool Close() = 0;
    virtual void SetSocket(int socketfd) = 0;

  private:

  protected:

};


#endif  /* _MKSOCKETINTERFACE_ */

