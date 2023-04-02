#ifndef Node_h
#define Node_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct Node
{
	void * data;
	struct Node* next;
	struct Node* previous;

};

struct Node node_constructor(void* data, unsigned long size);
void node_destructor(struct Node* node_to_destroy);


#endif 