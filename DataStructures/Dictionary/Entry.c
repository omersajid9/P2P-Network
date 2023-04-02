#include "Entry.h"

#include <stdlib.h>
#include <string.h>

struct Entry entry_constructor(void* key, void* value, unsigned long size_key, unsigned long size_value)
{
	struct Entry entry;
	entry.key = malloc(sizeof(size_key));
	entry.value = malloc(sizeof(size_value));
	memcpy(entry.key, key, size_key);
	memcpy(entry.value, key, size_value);
	return entry;
}

void entry_destructor(struct Entry* entry_to_destroy)
{
	free(entry_to_destroy->key);
	free(entry_to_destroy->value);
	free(entry_to_destroy);
}