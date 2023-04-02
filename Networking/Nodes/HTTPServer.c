#include "HTTPServer.h"
#include "../../System/ThreadPool.h"


#include <stdarg.h>
#include <string.h>
#include <stdlib.h>



void* launch_http(struct HTTPServer* server);
void* handler(void* arg);
void register_routes(struct HTTPServer* server, char* (*route_function)(struct HTTPServer* server, struct HTTPRequest* request), char* uri, int num_methods, ...);


struct ClientServer
{
	int client;
	struct HTTPServer* server;
};

struct Route
{
	int methods[9];
	char* uri;
	char* (*route_function)(struct HTTPServer* server, struct HTTPRequest* request);
};

struct HTTPServer http_server_constructor()
{
	struct HTTPServer server;
	server.server = server_constructor(AF_INET, SOCK_STREAM, 0, ADDR_ANY, 80, 255);
	server.routes = dictionary_constructor(compare_string_keys);
	server.register_routes = register_routes;
	server.launch = launch_http;
	return server;
}

void register_routes(struct HTTPServer* server, char* (*route_function)(struct HTTPServer* server, struct HTTPRequest* request), char* uri, int num_methods, ...) 
{

	printf("Start route");
	struct Route route;
	va_list methods;
	printf("Mid route");
	va_start(methods, num_methods);
	for (int i = 0; i < num_methods; i++)
	{
		route.methods[i] = va_arg(methods, int);
	}
	const int a = strlen(uri);
	char* buffer[sizeof(char[a])];
	route.uri = buffer;
	strcpy(route.uri, uri);
	route.route_function = route_function;
	server->routes.insert(uri, &route, sizeof(char[strlen(uri)]), sizeof(route), &server->routes);
	printf("End route");

}

void* launch_http(struct HTTPServer* server)
{
	struct ThreadPool thread_pool = thread_pool_constructor(3);
	struct sockaddr* sockaddress = (struct sockaddr*)&server->server.address;
	int address_length = sizeof(server->server.address);
	while (1)
	{
		struct ClientServer* client_server = malloc(sizeof(struct ClientServer));
		client_server->client = accept(server->server.sock, sockaddress, &address_length);
		client_server->server = server;
		struct ThreadJob job = thread_job_constructor(handler, client_server);
		thread_pool.add_work(&thread_pool, job);
	}
}


void* handler(void* arg)
{
	struct ClientServer* client_server = (struct ClientServer*)arg;
	char request_string[30000];
	recv(client_server->client, request_string, 30000, 0);
	struct HTTPRequest request = http_request_constructor(request_string);
	char* uri = request.request_line.search("uri", &request.request_line);
	struct Route* route = client_server->server->routes.search(uri, &client_server->server->routes);
	char* response = route->route_function(client_server->server, &request);
	send(client_server->client, response, sizeof(char[strlen(response)]), 0);
	free(arg);
	http_request_destructor(&request);
	return NULL;

}

char* render_template(int num_templates, ...)
{
	printf("Render enter");
	char* buffer = malloc(30000);
	int buffer_position = 0;
	char c;
	FILE* file;


	va_list files;
	va_start(files, num_templates);


	for (int i = 0; i < num_templates; i++)
	{
		char* path = va_arg(files, char*);
		file = fopen(path, "r");
		while ((c = fgetc(file)) != EOF)
		{
			buffer[buffer_position] = c;
			buffer_position += 1;
		}
	}
	va_end(files);
	return buffer;
}


//#include <unistd.h>
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <WS2tcpip.h>
/*void retrieve_page(int socket, struct HTTPRequest request);

void launch(struct Server* server)
{
	int addrlen = sizeof(server->address);
	long valread;

	while (1)
	{
		printf("===Waiting===");
		int new_socket = accept(server->sock, (struct sockaddr*)&server->address, (struct socklen_t*)&addrlen);
		char buffer[30000];

		valread = recv(new_socket, buffer, 30000);
		struct HTTPRequest request = http_request_constructor(buffer);

		retrieve_page(new_socket, request);
		closesocket(new_socket);
		
	}
}

void retrieve_page(int socket, struct HTTPRequest request)
{
	char path[300000] = { 0 };

	char* url = strtok(request.request_line.search("uri", &request->request_line), "?");
	char* vars = strtok(NULL, "\0");

	strcpy(path, " C:/Users/HP/OneDrive/Desktop");
	if (strcmp(url, "/test") == 0)
	{
		strcat(path, url);
	}
	else
	{
		strcat(path, "/index");
	}
	strcat(path, ".html");

	FILE f = *fopen(path, 'r');
	fseek(&f, 0, SEEK_END);
	long fsize = ftell(&f);
	fseek(&f, 0, SEEK_SET);

	char* buffer = malloc(fsize + 1);
	fread(buffer, 1, fsize, &f);
	fclose(&f);

	char response[30000] = { 0 };
	strcpy(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
	strcat(response, buffer);

	send(socket, response, strlen(response));
}*/