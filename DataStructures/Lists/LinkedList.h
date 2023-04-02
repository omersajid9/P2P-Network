#ifndef LinkedList_h
#define LinkedList_h

#include "../Common/Node.h"

struct LinkedList
{
	struct Node* head;
	int length;

	void (*insert)(int index, void* data, unsigned long size, struct LinkedList* linked_list);
	void (*remove)(int index, struct LinkedList* linked_list);
	void* (*retrieve)(int index, struct LinkedList* linked_list);

};

struct LinkedList linked_list_constructor();
void linked_list_destructor(struct LinkedList* linked_list);

#endif 