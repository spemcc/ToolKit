#include "tcp_server_socket.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include <sstream>

network::TcpServerSocket::TcpServerSocket() { }
network::TcpServerSocket::~TcpServerSocket() { }

bool network::TcpServerSocket::Bind(const uint16_t& port_num)
{
  struct addrinfo hints;
  struct addrinfo* res;
  char name[128];
  std::stringstream port_string_stream;
  port_string_stream << port_num;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if(gethostname(name, sizeof(name)) == -1)
  {
    perror("gethostname");
    return false;
  }
  struct hostent* hostName = gethostbyname(name);
  if((getaddrinfo(hostName->h_name, port_string_stream.str().c_str(), &hints, &res)) == -1)
  {
    perror("getaddrinfo");
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
    perror("socket");
    freeaddrinfo(res);
    return false;
  }

  if(::bind(socket_fd_, res->ai_addr, res->ai_addrlen))
  {
    perror("bind");
    std::cout << "bind on port " << port_num << " failed. " << std::endl;
    freeaddrinfo(res);
    return false;
  }
  std::cout << "Bind Success: " << name << ":" << port_num << std::endl;
 
  freeaddrinfo(res);

  return true;
}

int network::TcpServerSocket::Accept()
{
  struct sockaddr_storage store_addr;
  socklen_t client_socket_length = sizeof(store_addr);

  int client_fd = accept(socket_fd_, (struct sockaddr*)&store_addr, &client_socket_length);
  if(client_fd == -1)
  {
    perror("accept");
    return -1;
  }
  return client_fd;
}

bool network::TcpServerSocket::Listen()
{
  if(listen(socket_fd_, 1) == -1)
  {
    perror("listen");
    return false;
  }
  return true;
}


