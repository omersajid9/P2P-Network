#include "Dictionary.h"
#include "Entry.h"

#include <string.h>

void insert_dic(void* key, void* value, unsigned long size_key, unsigned long size_value, struct Dictionary* dictionary);
void* search_dic(void* key, struct Dictionary* dictionary);

struct Dictionary dictionary_constructor(int(*compare)(void* key1, void* key2))
{
	struct Dictionary dictionary;
	dictionary.tree = binary_search_tree_constructor(compare);
	dictionary.insert = insert_dic;
	dictionary.search = search_dic;
	return dictionary;
}

void dictionary_destructor(struct Dictionary* dictionary_to_destroy)
{
	binary_search_tree_destructor(dictionary_to_destroy->tree);
	free(dictionary_to_destroy);
}


void* search_dic(void* key, struct Dictionary* dictionary)
{
	void* data = dictionary->tree.search(key, &dictionary->tree);
	if (data)
	{
		return ((struct Entry*)data)->value;
	}
	else
	{
		return NULL;
	}
}

void insert_dic(void* key, void* value, unsigned long size_key, unsigned long size_value, struct Dictionary* dictionary)
{
	printf("Inserting");
	struct Entry entry = entry_constructor(key, value, size_key, size_value);
	printf("entry made");
	dictionary->tree.insert(&entry, sizeof(entry), &dictionary->tree);
	printf("exting");
}

int compare_string_keys(void* entry_one, void* entry_two)
{
	int comparison = strcmp((char*)(((struct Entry*)entry_one)->key), (char*)(((struct Entry*)entry_two)->key));
	if (comparison < 0)
	{
		return -1;
	}
	else if (comparison > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}