#include "MKTcpSocketImp.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cassert>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

MKTcpSocketImp::MKTcpSocketImp() : socketfd(0) { }

MKTcpSocketImp::~MKTcpSocketImp() {}

bool MKTcpSocketImp::Read(std::vector<uint8_t>* output, int numBytes)
{
  int bytesRecieved = 0;
  int totalBytesRecieved = 0;
  while(totalBytesRecieved != numBytes)
  {
    bytesRecieved = recv(socketfd, &(output->at(0)), numBytes, 0);
    if(bytesRecieved == -1)
      return false;
    totalBytesRecieved += bytesRecieved;
  }
  return true;
}

bool MKTcpSocketImp::Write(const std::vector<uint8_t>& data)
{
  int numBytes = data.size();
  int bytesSent = 0;
  int totalBytesSent= 0;

  while(totalBytesSent!= numBytes)
  {
    bytesSent = send(socketfd,&(data.at(0)),numBytes, 0);
    if(bytesSent == -1)
      return false;
    totalBytesSent += bytesSent ;
  }
  return true;
}

bool MKTcpSocketImp::Close()
{
  return !(close(socketfd));
}

void MKTcpSocketImp::SetSocket(int _socketfd)
{
  socketfd = _socketfd;
}

bool MKTcpSocketImp::Bind(uint16_t portNum)
{
  assert("Do not call me MKTcpServerSocket only");
  return false;
}

bool MKTcpSocketImp::Connect(std::string ip, uint16_t portNum, bool IPV6)
{
  assert("Do not call me MKTcpClientSocket only");
  return true; 
}

bool MKTcpSocketImp::Listen()
{
  assert("Do not call me MKTcpServerSocket only");
  return false;
}

int MKTcpSocketImp::Accept()
{
  assert("Do not call me MKTcpServerSocket only");
  return false;
}

