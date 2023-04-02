#include "Server.h"
#include <stdio.h>


struct Server server_constructor(int domain, int service, int protocol, u_long interFace, int port, int backlog)
{
	struct Server server;
	server.domain = domain;
	server.service = service;
	server.protocol = protocol;
	server.interFace = interFace;
	server.port = port;
	server.backlog = backlog;

	server.address.sin_family = domain;
	server.address.sin_port = htons(port);
	server.address.sin_addr.s_addr = htonl(interFace);

	server.sock = socket(domain, service, protocol);
	if (server.sock == 0)
	{
		perror("Failed to connect to socket....\n");
		exit(-1);
	}

	server.bind = bind(server.sock, (struct sockaddr*)&server.address, sizeof(server.address));
	if (server.bind < 0)
	{
		perror("Failed to bind to socket....\n");
		printf("%s\n", WSAGetLastError());
		exit(-1);
	}

	server.listen = listen(server.sock, server.backlog);
	if (server.listen < 0)
	{
		perror("Failed to listen to socket....\n");
		exit(-1);
	}
	
	return server;
}

