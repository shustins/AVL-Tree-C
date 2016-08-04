#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"
#include "dbg.h"

int compNum(void * A, void * B);

void printNum(void * A);


int main(int argc, char * argv[]) {
	
	check(argc > 1, "USAGE: ./program {integer dataset}");
	
	int num;
	Tree tree; 
	newTree(&tree, sizeof(int), compNum, NULL);
	
	printf("\n-------------------------------------------------------------\n"
		   "Inserting set into AVL tree.\n"
		   "-------------------------------------------------------------\n\n");
	
	for (int i = 1; i < argc; ++i) {
		num = atoi(argv[i]);
		printf("----------------------\n");
		printf("Next insert: (%d)\n", num);
		printf("----------------------\n");
		int rc = insertNode(&tree, &num);
		check(rc >= 0, "Failure.");
		printTree(&tree, printNum);
	}
	
	printf("\n-------------------------------------------------------------\n"
		   "Test retrieval from AVL tree.\n"
		   "-------------------------------------------------------------\n\n");
	
	printf("Insert a key to retrieve or NaN to skip test: ");
	
	while (scanf("%d", &num) == 1) {
		void * rc = retrieveNode(&tree, &num);
		if (rc) {
			printf("%d retrieved.\n", *((int *)rc));
		} else {
			printf("%d not found.\n", num);
		}
		printf("Insert another key to retrieve or NaN to end test: ");
	}
	
	printf("\n-------------------------------------------------------------\n"
		   "Test removals from AVL tree.\n"
		   "-------------------------------------------------------------\n\n");
	
	for (int i = 1; i < argc; ++i) {
		num = atoi(argv[i]);
		printf("----------------------\n");
		printf("Next removal: (%d)\n", num);
		printf("----------------------\n");
		int rc = removeNode(&tree, &num);
		check(rc >= 0, "Failure.");
		printTree(&tree, printNum);
	}
	
	printf("\n-------------------------------------------------------------\n"
		   "Tests ran successfully.\n"
		   "-------------------------------------------------------------\n\n");
	
	destroyTree(&tree);
	
	return 0;
	
error:

	printf("\n-------------------------------------------------------------\n"
		   "Tests aborting after error.\n"
		   "-------------------------------------------------------------\n\n");

	destroyTree(&tree);
	
	return -1;
}


int compNum(void * A, void * B) {
	
	return *((int *)A) - *((int *)B);
}


void printNum(void * A) {
	
	printf("(%d)", *((int *)A));
}