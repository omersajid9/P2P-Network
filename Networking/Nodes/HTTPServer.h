#ifndef HTTPServer_h
#define HTTPServer_h

#include <stdio.h>
#include "Server.h"
#include "../../DataStructures/Dictionary/Dictionary.h"
#include "../Protocols/HTTPRequest.h"


struct HTTPServer
{
	struct Server server;
	struct Dictionary routes;

	void (*register_routes)(struct HTTPServer* server, char* (*route_function)(struct HTTPServer* server, struct HTTPRequest* request), char* uri, int num_methods, ...);
	void* (*launch)(struct HTTPServer* server);
};

struct HTTPServer http_server_constructor();

char* render_template(int num_templates, ...);

#endif