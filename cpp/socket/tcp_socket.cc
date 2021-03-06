#include "tcp_socket.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <iostream>

network::TcpSocket::TcpSocket() { }
network::TcpSocket::~TcpSocket() { }

bool network::TcpSocket::Connect(const std::string& ip,const uint16_t& port_num,const bool& ipv6)
{
  struct addrinfo hints;
  struct addrinfo* res;
  std::stringstream port_string_stream;
  port_string_stream << port_num;
  memset(&hints,0,sizeof(hints));

  if(ipv6)
    hints.ai_family = AF_INET6; 
  else
    hints.ai_family = AF_INET; 

  hints.ai_socktype = SOCK_STREAM;

  if((getaddrinfo(ip.c_str(), port_string_stream.str().c_str(), &hints, &res) == -1 ))
  {
    std::cout << "getaddrinfo failed" << std::endl;
    return false;
  }

  for(; res != NULL; res = res->ai_next) 
  {
    if ((socket_fd_ = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) 
    {
      std::cout << "socket error, trying next.." << std::endl;
      continue;
    }
    break;
  }

  if(socket_fd_ == -1)
  {
    std::cout << "socket error" << std::endl;
    freeaddrinfo(res);
    return false;
  }

  char ip_address[INET6_ADDRSTRLEN];
  void* addr;

  if(res->ai_family == AF_INET)
  {
    if(ipv6)
      assert("ipv6 flag was set true but got ipv4 socket");

    struct sockaddr_in* ipv4 = (struct sockaddr_in *) res->ai_addr;
    addr = &(ipv4->sin_addr);
  }
  else
  {
    if(!ipv6)
      assert("ipv4 flag was set true but got ipv6 socket");

    struct sockaddr_in6* ipv6 = (struct sockaddr_in6 *) res->ai_addr;
    addr = &(ipv6->sin6_addr);
  }

  //network to presentation - used to get IP address in printable form
  inet_ntop(res->ai_family, addr, ip_address, sizeof(ip_address));
  std::cout << ip_address << std::endl;

  if(connect(socket_fd_,res->ai_addr,res->ai_addrlen)== -1)
  {
    std::cerr<< "CONNECT ERROR" << std::endl;
    perror("connect");
    freeaddrinfo(res);
    return false;
  }

  return true;
}

