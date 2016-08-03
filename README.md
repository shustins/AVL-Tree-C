*******************************************************************************
AVL Tree (C) - Shawn Hustins
*******************************************************************************

1. Description
2. Usage {
	2.1 Initialization 
	2.2 Insertion 
	2.3 Removal 
	2.4 Retrievals 
	2.5 Termination 
}
3. Secure Usage {
	3.1 Testing 
	3.2 Bugs
}
4. References

****************
1.0 Description:
****************

	This class contains procedures for containing data in a AVL tree. An AVL
	tree is a binary tree that is dynamically balanced on each access. The
	method was developed by Russian mathematicians Georgii Adelson-Velsky and 
	Evgenii Mikhailovich Landis, hence the name A-V-L. The method allows for
	a near perfect balance at all times and a worst case access time of
	log2(n) + 1 where n is the logical size of the tree. The important AVL tree
	invariant is that each node will never have a height difference of more than
	1 between each child (height is defined by longest path to leaves), meaning
	that the maximum depth can only ever be at most 1 greater than all other
	leaves.
	
**********
2.0 Usage:
**********

	The following section outlines usage of the public AVL tree procedures with
	brief examples of each used on a list of primitive and referenced types. 
	Usage is also demonstrated in test.c, longer descriptions of procedures can
	be found in AVLTree.h.
	
	Struct used in examples:
	typedef struct {
		int ID; // unique
		char * name;
	} TestForm;
	
*******************
2.1 Initialization:
*******************

	newTree(Tree * tree, size_t dataSize, Comparator comparator, 
	Destructor destructor);
	// *tree - pointer for caller to hold the tree struct
	// dataSize - the size in bytes of each piece of data being held in tree
	// comparator - function required to compare data for sorting matters
	// destructor - function required to free data not directly stored in node
	
	Note: comparator should always have same function signature and should
		  return 0 if A=B, return > 0 if A>B, or return < 0 if A<B
	
	Note: destructor should only be specified if storing referenced data
	
Primitive Example:

	Tree intTree;
	newTree(&intTree, sizeof(int), compNum, NULL);
	
	...
	
	int compNum(void * A, void * B) {
		return *((int *)A) - *((int *)B);
	}
	
Reference Example:

	Tree formTree;
	newTree(&formTree, sizeof(TestForm), compID, freeString);
	
	...
	
	int compID(void * A, void * B) {
		return ((*TestForm)A)->ID - ((*TestForm)B)->ID;
	}
	
	void freeString(void * A) {
		free(A->name);
	}
	
**************
2.2 Insertion:
**************

	insertNode(Tree * tree, void * data);
	// *tree - pointer to an existing tree
	// *data - pointer to data being stored
	
Primitive Example:

	int num = 10;
	insertNode(&intTree, &num);
	
Reference Example:

	int ID = 123;
	char * name = calloc(6, sizeof(char));
	strcpy(name, "Shawn");
	TestForm form = {.ID = ID, .name = name};
	
	insertNode(&formTree, &form);
	
************
2.3 Removal:
************

	removeNode(Tree * tree, void * key);
	// *tree - pointer to an existing tree
	// *key - key for item wished to be removed
	
Primitive Example:

	removeNode(&intTree, &num);
	
Reference Example:

	removeNode(&formTree, &form);
	
	Note: form could be composed of empty entries aside from the entries used
	      for comparison, in this instance, form.ID
	
**************
2.4 Retrieval:
**************

	retrieveNode(Tree * tree, void * key);
	// *tree - pointer to an existing tree
	// *key - key for item wished to be retrieved
	
Primitive Example:

	int newNum = *(int *)retrieveNode(&intTree, &num);
	
Reference Example:

	TestForm newForm = *(TestForm *)retrieveNode(&formTree, &form);
	
	Note: form could be composed of empty entries aside from the entries used
	      for comparison, in this instance, form.ID
	      
****************
2.5 Termination:
****************

	destroyTree(Tree * tree);
	// *tree - pointer to an existing tree

Primitive Example:

	destroyTree(&intTree);
	
Reference Example:

	destroyTree(&formTree);
	
*****************
3.0 Secure Usage:
*****************

	All procedures contain built in error handling. To ensure expected
	behaviour, return values of each function should be tested.
	
	Initialization, Insertion, Removal & Termination:
		return >= 0 on success
		return -1 on failure
		
	Retrieval:
		return pointer to data on success
		return NULL on failure
		
	Causes of errors are outlined in detail in AVLTree.h
	
************
3.1 Testing:
************

	Insertions and removals both return the updated maximum height on successful
	returns. This allows for the AVL tree invariant to be easily asserted:
	
		int rc = insert/delete(&tree, ...);
		
		if ((log10(tree.size) / log10(2.0)) + 1 > height)
			// not balanced
			
*********
3.2 Bugs:
*********

	There is still at least one and the code is still a little messy. I have yet
	to pin point the bug but it involves some sort of self referential set of
	nodes, which cause infinite recursion when accessed. The bug is somewhere in
	the removal procedures.
			
***************
4.0 References:
***************

	dbg.h - (modified) taken from:
	Title: Zed's Awesome Debug Macros
	Author: Zed A. Shaw
	Date: 2015
	Version: 1.0
	Availability: Learn C the Hard Way (text Publication)

*******************************************************************************