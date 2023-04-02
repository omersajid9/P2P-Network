#ifndef Dictionary_h
#define Dictionary_h

#include "../Trees/BinarySearchTree.h"
#include "Entry.h"


struct Dictionary
{
	struct BinarySearchTree tree;

	void (*insert)(void* key, void* value, unsigned long size_key, unsigned long size_value, struct Dictionary* dictionary);
	void* (*search)(void* key, struct Dictionary* dictionary);
};

struct Dictionary dictionary_constructor(int(*compare)(void* key1, void* key2));
void dictionary_destructor(struct Dictionary* dictionary_to_destroy);

int compare_string_keys(void* entry_one, void* entry_two);

#endif 