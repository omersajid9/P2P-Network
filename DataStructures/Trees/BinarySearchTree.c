#include "BinarySearchTree.h"
#include "../Common/Node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Node* create_node_bst(void* data, unsigned long size);
void destroy_node_bst(struct Node* node_to_destroy);

void insert_bst(void* data, unsigned long size, struct BinarySearchTree* tree);
void* search_bst(void* data, struct BinarySearchTree* tree);
struct Node* iterate_bst(struct Node* cursor, void* data, int* direction, struct BinarySearchTree* tree);

void recursive_tree_destruction(struct Node* node);

struct BinarySearchTree binary_search_tree_constructor(int (*compare) (void* data1, void* data2))
{
	struct BinarySearchTree tree;
	tree.compare = compare;
	tree.search = search_bst;
	tree.insert = insert_bst;
	tree.head = NULL;
	return tree;
}

void binary_search_tree_destructor(struct BinarySearchTree tree)
{
	recursive_tree_destruction(tree.head);
}

void recursive_tree_destruction(struct Node* node)
{
	if (node->previous)
	{
		recursive_tree_destruction(node->previous);
	}
	if (node->next)
	{
		recursive_tree_destruction(node->next);
	}
	destroy_node_bst(node);
}

struct Node* create_node_bst(void* data, unsigned long size)
{
	printf("BST node creation");
	printf(":");
	//printf("%d\n", a);
	printf("H");
	//struct Node* new_node = malloc(sizeof(struct Node));
	printf("BST node creation allocate");
	struct Node new_node = node_constructor(data, size);
	printf("BST node creation end");

	return &new_node;
}

void destroy_node_bst(struct Node* node_to_destroy)
{
	node_destructor(node_to_destroy);
}

struct Node* iterate_bst(struct Node* cursor, void* data, int* direction, struct BinarySearchTree* tree)
{
	int comp = tree->compare(cursor->data, data);
	if (comp > 0)
	{
		if (cursor->next)
		{
			return iterate_bst(cursor->next, data, direction, tree);
		}
		else
		{
			*direction = 1;
			return cursor;
		}
	}
	else if (comp < 0)
	{
		if (cursor->previous)
		{
			return iterate_bst(cursor->previous, data, direction, tree);
		}
		else
		{
			*direction = -1;
			return cursor;
		}
	}
	else
	{
		*direction = 0;
		return cursor;
	}
}


void* search_bst(void* data, struct BinarySearchTree* tree)
{
	int* direction = NULL;
	struct Node* cursor = iterate_bst(tree->head, data, direction, tree);
	if (*direction == 0)
	{
		return cursor->data;
	}
	else
	{
		return NULL;
	}
}

void insert_bst(void* data, unsigned long size, struct BinarySearchTree* tree)
{
	printf("BSt insert start");
	if (tree->head == NULL)
	{
		printf("BSt insert first");
		tree->head = create_node_bst(data, size);
	}
	else
	{
		printf("BSt insert else");

		int* direction = 0;
		struct Node* cursor = iterate_bst(tree->head, data, direction, tree);
		if (*direction > 0)
		{
			cursor->next = create_node_bst(data, size);
		}
		else if (*direction < 0)
		{
			cursor->previous = create_node_bst(data, size);
		}
	}
	printf("BSt insert finish");

}