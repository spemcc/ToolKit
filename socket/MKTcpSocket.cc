#include "MKTcpSocket.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cassert>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

MKTcpSocket::MKTcpSocket() : socket_fd_(0) { }

MKTcpSocket::~MKTcpSocket() {}

bool MKTcpSocket::Read(std::vector<uint8_t>* output, int num_bytes)
{
  int bytes_recieved = 0;
  int total_bytes_recieved = 0;
  while(total_bytes_recieved != num_bytes)
  {
    bytes_recieved = recv(socket_fd_, &(output->at(0)), num_bytes, 0);
    if(bytes_recieved == -1)
      return false;
    total_bytes_recieved += bytes_recieved;
  }
  return true;
}

bool MKTcpSocket::Write(const std::vector<uint8_t>& data)
{
  int num_bytes = data.size();
  int bytesSent = 0;
  int totalBytesSent= 0;

  while(totalBytesSent!= num_bytes)
  {
    bytesSent = send(socket_fd_,&(data.at(0)),num_bytes, 0);
    if(bytesSent == -1)
      return false;
    totalBytesSent += bytesSent ;
  }
  return true;
}

bool MKTcpSocket::Close()
{
  return !(close(socket_fd_));
}

void MKTcpSocket::set_socket(int socket_fd)
{
  socket_fd_ = socket_fd;
}

bool MKTcpSocket::Bind(uint16_t port_num)
{
  assert("Do not call me MKTcpServerSocket only");
  return false;
}

bool MKTcpSocket::Connect(std::string ip, uint16_t port_num, bool IPV6)
{
  assert("Do not call me MKTcpClientSocket only");
  return true; 
}

bool MKTcpSocket::Listen()
{
  assert("Do not call me MKTcpServerSocket only");
  return false;
}

int MKTcpSocket::Accept()
{
  assert("Do not call me MKTcpServerSocket only");
  return false;
}

