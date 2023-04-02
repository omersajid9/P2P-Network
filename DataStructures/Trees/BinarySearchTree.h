#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "../Common/Node.h"

struct BinarySearchTree
{
	struct Node* head;

	int (*compare) (void* data1, void* data2);
	void* (*search) (void* data, struct BinarySearchTree* tree);
	void (*insert) (void* data, unsigned long size, struct BinarySearchTree* tree);
};

struct BinarySearchTree binary_search_tree_constructor(int(*compare)(void* data1, void* data2));
void binary_search_tree_destructor(struct BinarySearchTree tree);

#endif 