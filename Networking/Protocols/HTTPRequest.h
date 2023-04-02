#ifndef HTTPRequest_h
#define HTTPRequest_h

#include "../../DataStructures/Dictionary/Dictionary.h"

enum HTTPMethods
{
	GET,
	POST,
	PUT,
	HEAD,
	PATCH,
	DELET,
	CONNECT,
	OPTIONS,
	TRACE
};

struct HTTPRequest
{
	struct Dictionary request_line;
	struct Dictionary header_fields;
	struct Dictionary body;

};

struct HTTPRequest http_request_constructor(char * request_string);
void http_request_destructor(struct HTTPRequest* http_request);


#endif