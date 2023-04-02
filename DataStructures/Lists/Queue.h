#ifndef Queue_h
#define Queue_h

#include "LinkedList.h"

struct Queue
{
	struct LinkedList linked_list;

	void(*push)(void* data, unsigned long size, struct Queue* queue);
	void(*pop)(struct Queue* queue);
	void* (*peek)(struct Queue* queue);


};

struct Queue queue_constructor(void);
void queue_destructor(struct Queue* queue);


#endif 