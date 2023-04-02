#include "Networking/Nodes/HTTPServer.h"
#include <stdio.h>


#include <winsock2.h>

char* home(struct HTTPServer* server, struct HTTPRequest* request)
{
	char* x = render_template(2, "C:/Users/HP/web3-projects/serverProject/header.html", "C:/Users/HP/web3-projects/serverProject/index.html");
	return x;
}

int main()
{
	printf("Here");
	WSADATA wsaData;
	int iResult;
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	printf("Here");

	struct HTTPServer server = http_server_constructor();
	printf("Here");

	char* h = "/home";

	server.register_routes(&server, home, h, 0);
	printf("Here");

	server.launch(&server);
	printf("Double");
	printf("Abc %f", WSAGetLastError());
}





//void launch(struct Server* server)
//{
//	char buffer[30000];
//	const char* hello = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Sun, 05 Feb 2023 22:06:53 GMT\nContent-Type:text/html\nConnection:Closed\n\n<html><body><h1>Hello World</h1></body></html>";
//	int addr_len = sizeof(server->address);
//	int new_socket;
//	while (1)
//	{
//		printf("===== Waiting for connection =====\n");
//		new_socket = accept(server->sock, (struct sockaddr*)&server->address, &addr_len);
//		recv(new_socket, buffer, 30000, 0);
//		printf("%s\n", buffer);
//		send(new_socket, hello, strlen(hello), 0);
//		closesocket(new_socket);
//		printf("===== Done! =====\n");
//	}
//}
//
//int main()
//{
//	WSADATA wsaData;
//	int iResult;
//
//	// Initialize Winsock
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) 
//	{
//		printf("WSAStartup failed: %d\n", iResult);
//		return 1;
//	}
//	
//	//std::cout << "Hello" << std::endl;
//	struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
//	server.launch(&server);
//	//std::cout << "Success!" << std::endl;
//
//}