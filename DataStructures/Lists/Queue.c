#include "Queue.h"


void push(void* data, unsigned long size, struct Queue* queue)
{
	queue->linked_list.insert(queue->linked_list.length, data, size, &queue->linked_list);
}

void pop(struct Queue* queue)
{
	queue->linked_list.remove(0, &queue->linked_list);
}

void* peek(struct Queue* queue)
{
	return queue->linked_list.retrieve(0, &queue->linked_list);
}


struct Queue queue_constructor()
{
	struct Queue queue;
	queue.linked_list = linked_list_constructor();

	queue.pop = pop;
	queue.push = push;
	queue.peek = peek;

	return queue;
}

void queue_destructor(struct Queue* queue)
{
	linked_list_destructor(&queue->linked_list);
	free(queue);
}