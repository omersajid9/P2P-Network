#ifndef Entry_h
#define Entry_h

struct Entry
{
	void* key;
	void* value;
};

struct Entry entry_constructor(void* key, void* value, unsigned long size_key, unsigned long size_value);
void entry_destructor(struct Entry* entry_to_destroy);


#endif 