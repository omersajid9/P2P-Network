#include "Node.h"

#include <string.h>

struct Node node_constructor(void* data, unsigned long size)
{
	if (size < 1)
	{
		printf("Invalid data size for node construction ...");
		exit(9);
	}
	printf(" Node creation start");
	struct Node node;
	node.data = malloc((size_t) size);
	memcpy(node.data, data, size);

	node.next = NULL;
	node.previous = NULL;
	printf(" Node creation finish");

	return node;
}

void node_destructor(struct Node* node_to_destroy)
{
	free(node_to_destroy->data);
	free(node_to_destroy);
}