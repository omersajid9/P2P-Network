#include "HTTPRequest.h"

#include <string.h>
#include <stdlib.h>

#include "../../DataStructures/Lists/Queue.h"

void extract_request_line_fields(char* request_line, struct HTTPRequest* request);
void extract_header_fields(char* header_field, struct HTTPRequest* request);
void extract_body(char* body, struct HTTPRequest* request);



struct HTTPRequest http_request_constructor(char* request_string)
{
	struct HTTPRequest request;
	char requested[strlen(request_string)];
	strcpy(requested, request_string);

	for (int i = 0; i < strlen(requested) - 1; i++)
	{
		if (request_string[i] == '\n' && request_string[i + 1] == '\n')
		{
			requested[i + 1] = '|';
		}
	}
	char* request_line = strtok(request_string, "\n");
	char* header_fields = strtok(NULL, "|");
	char* body = strtok(NULL, "|");

	extract_request_line_fields(request_line, &request);
	extract_header_fields(header_fields, &request);
	extract_body(body, &request);
	
	return request;
}

void http_request_destructor(struct HTTPRequest* http_request)
{
	dictionary_destructor(&http_request->header_fields);
	dictionary_destructor(&http_request->request_line);
	dictionary_destructor(&http_request->body);
}


void extract_request_line_fields(char* request_line, struct HTTPRequest* request)
{
	char fields[strlen(request_line)];
	strcpy(fields, request_line);

	char* method = strtok(fields, " ");
	char* uri = strtok(NULL, " ");
	char* http_version = strtok(NULL, "\0");

	struct Dictionary request_line_dict = dictionary_constructor(compare_string_keys);
	
	request_line_dict.insert("method", method, sizeof("method"), sizeof(char[strlen(method)]), &request_line_dict);
	request_line_dict.insert("uri", uri, sizeof("uri"), sizeof(char[strlen(uri)]), &request_line_dict);
	request_line_dict.insert("http_version", http_version, sizeof("http_version"), sizeof(char[strlen(http_version)]), &request_line_dict);

	request->request_line = request_line_dict;

	if (request->request_line.search("GET", &request->request_line))
	{
		extract_body((char*)request->request_line.search("uri", &request->request_line), request);
	}
}

void extract_header_fields(char* header_field, struct HTTPRequest* request)
{
	char fields[strlen(header_field)];
	strcpy(fields, header_field);

	struct Queue headers = queue_constructor();

	char* field = strtok(fields, "\n");
	while (field)
	{
		headers.push(field, sizeof(*field), &headers);
		field = strtok(NULL, "\n");
	}

	request->header_fields = dictionary_constructor(compare_string_keys);

	char* header = (char*)headers.peek(&headers);
	while (header)
	{
		char* key = strtok(header, ":");
		char* value = strtok(NULL, "\n");

		if (value)
		{
			if (value[0] == ' ')
			{
				value++;
			}
			request->header_fields.insert(key, value, sizeof(char[strlen(key)]), sizeof(char[strlen(value)]), &request->header_fields);

		}

		headers.pop(&headers);
		header = (char*)headers.peek(&headers);
	}
	queue_destructor(&headers);
}

void extract_body(char* body, struct HTTPRequest* request)
{
	char* content_type = (char*)request->header_fields.search("Content-Type", &request->header_fields);
	if (content_type)
	{
		struct Dictionary body_fields = dictionary_constructor(compare_string_keys);
		if (strcmp(content_type, "application/x-www-form-urlencoded") == 0)
		{
			struct Queue fields = queue_constructor();
			char* field = strtok(body, "&");
			while (field)
			{
				fields.push(field, sizeof(char[strlen(field)]), &fields);
			}

			field = fields.peek(&fields);
			while (field)
			{
				char* key = strtok(field, "=");
				char* value = strtok(NULL, '\0');

				if (value[0] == ' ')
				{
					value++;
				}

				body_fields.insert(key, value, sizeof(char[strlen(key)]), sizeof(char[strlen(value)]), &body_fields);

				fields.pop(&fields);
				field = fields.peek(&fields);
			}
			queue_destructor(&fields);
		}
		else
		{
			body_fields.insert("data", body, sizeof("data"), sizeof(char[strlen(body)]), &body_fields);
		}
		request->body = body_fields;
	}
}




int method_select(char* method)
{
	if (strcmp(method, "GET") == 0)
	{
		return GET;
	}
	else if (strcmp(method, "POST") == 0)
	{
		return POST;
	}
	else if (strcmp(method, "PUT") == 0)
	{
		return PUT;
	}
	else if (strcmp(method, "HEAD") == 0)
	{
		return HEAD;
	}
	else if (strcmp(method, "PATCH") == 0)
	{
		return PATCH;
	}
	else if (strcmp(method, "DELETE") == 0)
	{
		return DELET;
	}
	else if (strcmp(method, "CONNECT") == 0)
	{
		return CONNECT;
	}
	else if (strcmp(method, "OPTIONS") == 0)
	{
		return OPTIONS;
	}
	else if (strcmp(method, "TRACE") == 0)
	{
		return TRACE;
	}
}