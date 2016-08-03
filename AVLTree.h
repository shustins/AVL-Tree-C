#ifndef _AVLTree_h_
#define _AVLTree_h_

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX 1
#define MIN 0

typedef void (*Destructor)(void *);
typedef int (*Comparator)(void *, void *);
typedef void (*Printer)(void *);

typedef struct binaryNode {
	void * data;                // stored data
	int height;                 // height in tree
	struct binaryNode * parent; // parent node
	struct binaryNode * left;   // left child
	struct binaryNode * right;  // right child
} Node;

typedef struct {
	size_t dataSize;          // size of data stored in node
	Node * root;              // root of tree
	Destructor destructor;    // function to free referenced data in nodes
	Comparator comparator;    // function to compare keys of node data
	int size;                 // logical size of tree
} Tree;

                              
/* Public: ********************************************************************/

/*
 * newTree
 * IN:   *tree - pointer for caller to hold the tree struct
 *       dataSize - the size in bytes of each piece of data being held in tree
 *       comparator - function required to compare data for sorting matters
 *       destructor - function required to free data not directly stored in node
 * OUT:  return 0 on success
 *       return -1 on failure (no tree specified, non-natural data size)
 * POST: produces a tree including specified assignments
 */
int newTree(Tree * tree, size_t dataSize, Comparator comparator, 
										Destructor destructor);
/*
 * destroyTree
 * IN:   *tree - pointer to an existing tree
 * OUT:  return 0 on success
 *       return -1 on failure (no tree specified, empty tree)
 * POST: frees all memory alllocated to nodes of tree, calls external destructor
 *       if tree has one
 */
int destroyTree(Tree * tree);

/*
 * insertNode
 * IN:   *tree - pointer to an existing tree
 *       *data - pointer to data being stored
 * OUT:  return tree height on success (leaves count as 1 in this context)
 *       return -1 on failure (memory error, duplicate key exists)
 * POST: allocates memory for new node, places in sorted position and rebalances
 *       tree
 */
int insertNode(Tree * tree, void * data);

/*
 * removeNode
 * IN:   *tree - pointer to an existing tree
 *       *key - key for the item wished to be removed
 * OUT:  return tree height on success (leaves count as 1 in this context)
 *       return -1 on failure (no tree specified, empty tree, key not found)
 * POST: frees desired node and rebalances tree
 */
int removeNode(Tree * tree, void * key);

/*
 * retrieveNode
 * IN:   *tree - pointer to an existing tree
 *       *key - key for the item wished to be retrieved
 * OUT:  return desired key on success
 *       return NULL on failure (no tree specified, empty tree, key not found)
 * POST: searches tree for node with desired key and returns data inside
 */
void * retrieveNode(Tree * tree, void * key);

/*
 * printTree
 * IN:   *tree - pointer to an existing tree
 *       printer - function to print the data inside each node
 * OUT:  return 0 on success
 *       return -1 on failure (no tree specified, empty tree, no print function)
 * POST: prints each node in order, displayed at it's depth and with it's height
 *       in brackets
 */
int printTree(Tree * tree, Printer printer);


/* Private: *******************************************************************/

void destroyNode(Node * node, Destructor destructor, int recurse);

Node * newNode(void * data, size_t dataSize);

int insert(Node * node, void * data, Tree * tree);

int findRemove(Node * node, void * key, Tree * tree);

void * yank(int getMinMax, Node * node, int * newHeight, Tree * tree);

void * retrieve(Node * node, void * key, Tree * tree);

void printNode(Node * node, Printer printer, int depth);

/* AVL Tree Balancing Procedures (Private): ***********************************/

void keepBalanced(Node * node, void * data, Tree * tree, int flip);

Node * rotateFromLeft(Node * oldRoot, Tree * tree);

void doubleRotateFromLeft(Node * oldRoot, Tree * tree);

Node * rotateFromRight(Node * oldRoot, Tree * tree);

void doubleRotateFromRight(Node * oldRoot, Tree * tree);

void adjustHeight(Node * node);
		
int checkBalance(Node * node);

#endif