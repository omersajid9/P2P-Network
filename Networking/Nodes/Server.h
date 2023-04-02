#ifndef Server_h
#define Server_h

#include <winsock2.h>
#include <stdlib.h>


struct Server
{
	int domain;
	int service;
	int protocol;
	u_long interFace;
	int port;
	int backlog;

	int sock;
	int bind;
	int listen;

	struct sockaddr_in address;
};

struct Server server_constructor(int domain, int service, int protocol, u_long interFace, int port, int backlog);

#endif