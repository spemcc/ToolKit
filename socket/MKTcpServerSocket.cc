
#include "MKTcpServerSocket.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include <sstream>

MKTcpServerSocket::MKTcpServerSocket() { }
MKTcpServerSocket::~MKTcpServerSocket() { }

bool MKTcpServerSocket::Bind(uint16_t portNum)
{
  struct addrinfo hints;
  struct addrinfo* res;
  char name[128];
  std::stringstream portStringStream;
  portStringStream << portNum;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if(gethostname(name, sizeof(name)) == -1)
  {
    perror("gethostname");
    return false;
  }
  struct hostent* hostName = gethostbyname(name);
  if((getaddrinfo(hostName->h_name, portStringStream.str().c_str(), &hints, &res)) == -1)
  {
    perror("getaddrinfo");
    return false;
  }

  for(; res != NULL; res = res->ai_next) 
  {
    if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) 
    {
      std::cout << "socket error, trying next.." << std::endl;
      continue;
    }
    break;
  }
  if(socketfd == -1)
  {
    perror("socket");
    freeaddrinfo(res);
    return false;
  }

  if(::bind(socketfd, res->ai_addr, res->ai_addrlen))
  {
    perror("bind");
    std::cout << "bind on port " << portNum << " failed. " << std::endl;
    freeaddrinfo(res);
    return false;
  }
 
  freeaddrinfo(res);

  return true;
}

int MKTcpServerSocket::Accept()
{
  struct sockaddr_storage storeAddr;
  socklen_t clientSocketLenght = sizeof(storeAddr);

  int clientfd = accept(socketfd, (struct sockaddr*)&storeAddr, &clientSocketLenght);
  if(clientfd == -1)
  {
    perror("accept");
    return -1;
  }
  return clientfd;
}

bool MKTcpServerSocket::Listen()
{
  if(listen(socketfd, 1) == -1)
  {
    perror("listen");
    return false;
  }
  return true;
}


