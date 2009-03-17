/*
 * main.c
 *
 *
 *  Created on: 2009-feb-09
 *      Author: Johannes Wirde
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common.h"
#include "postalCode.h"
#include "postalCodeAssert.h"

void insertListReuse() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode = setupPCList();
	int i = 0;
	clock_t start, end;

	printf("\t... with list (reusing): ");
	start = clock();
	for (i = 0; i < TESTS; ++i) {
		createPostalCode(pCode, 12345);
		addPostalCode_list(pRoot, pCode);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCList(pCode);
}

void insertListCreDel() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode;
	int i = 0;
	clock_t start, end;

	printf("\t... with list (creating/deleting): ");
	start = clock();
	for (i = 0; i < TESTS; ++i) {
		pCode = setupPCList();
		createPostalCode(pCode, 12345);
		addPostalCode_list(pRoot, pCode);
		deletePCList(pCode);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void insertListRecReuse() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode = setupPCList();
	int i = 0;
	clock_t start, end;

	printf("\t... with recursive list (reuse): ");
	start = clock();
	for (i = 0; i < TESTS; ++i) {
		createPostalCode(pCode, 12345);
		addPostalCode_list_rec(pRoot, pCode);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCList(pCode);
	deletePCNode(pRoot);
}

void insertListRecCreDel() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode;
	int i = 0;
	clock_t start, end;

	printf("\t... with recursive list (creating/deleting): ");
	start = clock();
	for (i = 0; i < TESTS; ++i) {
		pCode = setupPCList();
		createPostalCode(pCode, 12345);
		addPostalCode_list_rec(pRoot, pCode);
		deletePCList(pCode);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void insertInt() {
	struct PCNode* pRoot = setupPCNode();
	int i = 0;
	clock_t start, end;

	printf("\t... with integer: ");
	start = clock();
	for (i = 0; i < TESTS; ++i) {
		addPostalCode_int(pRoot, 12345);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void insertIntRec() {
	struct PCNode* pRoot = setupPCNode();
	int i = 0;
	clock_t start, end;

	printf("\t... with recursive integer: ");
	start = clock();
	for (i = 0; i < TESTS; ++i) {
		addPostalCode_int_rec(pRoot, 12345);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void searchIntRec() {
	struct PCNode* pRoot = setupPCNode();
	int i = 0;
	clock_t start, end;

	addPostalCode_int(pRoot, 12345);

	printf("\t... with recursive integer: ");
	start = clock();
	for (i = 0; i < TESTS; i++) {
		ASSERTTRUE(!checkPostalCode_int_rec(pRoot, 12345));
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void searchListRecReuse() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode = setupPCList();
	int i = 0;
	clock_t start, end;

	addPostalCode_int(pRoot, 12345);

	printf("\t... with recursive list (reuse): ");
	start = clock();
	for (i = 0; i < TESTS; i++) {
		createPostalCode(pCode, 12345);
		ASSERTTRUE(!checkPostalCode_list_rec(pRoot, pCode));
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
	deletePCList(pCode);
}

void searchListRecCreDel() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode;
	int i = 0;
	clock_t start, end;

	addPostalCode_int(pRoot, 12345);

	printf("\t... with recursive list (creating/deleting): ");
	start = clock();
	for (i = 0; i < TESTS; i++) {
		pCode = setupPCList();
		createPostalCode(pCode, 12345);
		ASSERTTRUE(!checkPostalCode_list_rec(pRoot, pCode));
		deletePCList(pCode);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void searchInt() {
	struct PCNode* pRoot = setupPCNode();
	int i = 0;
	clock_t start, end;

	addPostalCode_int(pRoot, 12345);

	printf("\t... with integer: ");
	start = clock();
	for (i = 0; i < TESTS; i++) {
		ASSERTTRUE(!checkPostalCode_int(pRoot, 12345));
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void searchListReuse() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode = setupPCList();
	int i = 0;
	clock_t start, end;

	addPostalCode_int(pRoot, 12345);

	printf("\t... with list (reusing): ");
	start = clock();
	for (i = 0; i < TESTS; i++) {
		createPostalCode(pCode, 12345);
		ASSERTTRUE(!checkPostalCode_list(pRoot, pCode));
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
	deletePCList(pCode);
}

void searchListCreDel() {
	struct PCNode* pRoot = setupPCNode();
	struct PCList* pCode = setupPCList();
	int i = 0;
	clock_t start, end;

	addPostalCode_int(pRoot, 12345);

	printf("\t... with list (creating/deleting): ");
	start = clock();
	for (i = 0; i < TESTS; i++) {
		pCode = setupPCList();
		createPostalCode(pCode, 12345);
		ASSERTTRUE(!checkPostalCode_list(pRoot, pCode));
		deletePCList(pCode);
	}
	end = clock();
	printf("%f sec\n", (float)(end - start) / (float)CLOCKS_PER_SEC);

	deletePCNode(pRoot);
}

void runSynteticTests() {
	printf("Insert testing:\n");
	insertListReuse();
	insertListCreDel();

	insertListRecReuse();
	insertListRecCreDel();

	insertInt();
	insertIntRec();

	printf("Search testing:\n");
	searchListReuse();
	searchListCreDel();

	searchListRecReuse();
	searchListRecCreDel();

	searchInt();
	searchIntRec();
}

int main () {
	runAssertionTests(); // Starting with testing
	runSynteticTests();

	return 0;
}
