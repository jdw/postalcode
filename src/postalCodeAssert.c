/*
 * assert.c
 *
 *  Created on: 2009-feb-10
 *      Author: Johannes Wirde
 */

#include <stdio.h>
#include "postalCodeAssert.h"
#include "postalCode.h"

void runAssertionTests() {
	struct PCNode* pRootList = setupPCNode();
	struct PCNode* pRootInt = setupPCNode();

	struct PCList* pList = setupPCList();
	int i = 0;

	// Testing with empty nodes
	for (i = 10000; i < 99999; i++) {
		createPostalCode(pList, i);
		ASSERTFALSE(!checkPostalCode_list(pRootList, pList));
		ASSERTFALSE(!checkPostalCode_list_rec(pRootList, pList));
		ASSERTFALSE(!checkPostalCode_int(pRootList, i));
		ASSERTFALSE(!checkPostalCode_int_rec(pRootList, i));
	}

	for (i = 10000; i < 99999; i++) {
		ASSERTFALSE(!checkPostalCode_list(pRootInt, pList));
		ASSERTFALSE(!checkPostalCode_list_rec(pRootInt, pList));
		ASSERTFALSE(!checkPostalCode_int(pRootInt, i));
		ASSERTFALSE(!checkPostalCode_int_rec(pRootInt, i));
	}

	// Fill half way
	for (i = 10000; i < 50000; i++) {
		createPostalCode(pList, i);
		addPostalCode_list(pRootList, pList);
	}

	for (i = 10000; i < 35000; i++) {
		addPostalCode_int(pRootInt, i);
	}

	for (i = 35000; i < 50000; i++) {
		addPostalCode_int_rec(pRootInt, i);
	}

	// Testing half way
	for (i = 10000; i < 50000; i++) {
		createPostalCode(pList, i);
		ASSERTTRUE(!checkPostalCode_list(pRootList, pList));
		ASSERTTRUE(!checkPostalCode_list_rec(pRootList, pList));
		ASSERTTRUE(!checkPostalCode_int(pRootList, i));
		ASSERTTRUE(!checkPostalCode_int_rec(pRootList, i));
	}

	for (i = 10000; i < 50000; i++) {
		ASSERTTRUE(!checkPostalCode_list(pRootInt, pList));
		ASSERTTRUE(!checkPostalCode_list_rec(pRootInt, pList));
		ASSERTTRUE(!checkPostalCode_int(pRootInt, i));
		ASSERTTRUE(!checkPostalCode_int_rec(pRootInt, i));
	}

	for (i = 50000; i < 99999; i++) {
		createPostalCode(pList, i);
		ASSERTFALSE(!checkPostalCode_list(pRootList, pList));
		ASSERTFALSE(!checkPostalCode_list_rec(pRootList, pList));
		ASSERTFALSE(!checkPostalCode_int(pRootList, i));
		ASSERTFALSE(!checkPostalCode_int_rec(pRootList, i));
	}

	for (i = 50000; i < 99999; i++) {
		ASSERTFALSE(!checkPostalCode_list(pRootInt, pList));
		ASSERTFALSE(!checkPostalCode_list_rec(pRootInt, pList));
		ASSERTFALSE(!checkPostalCode_int(pRootInt, i));
		ASSERTFALSE(!checkPostalCode_int_rec(pRootInt, i));
	}

	// Fill rest of the way
	for (i = 10000; i < 99999; i++) {
		createPostalCode(pList, i);
		addPostalCode_list_rec(pRootList, pList);
	}

	for (i = 10000; i < 99999; i++) {
		addPostalCode_int(pRootInt, i);
	}
	// Test rest of the way
	for (i = 10000; i < 99999; i++) {
		createPostalCode(pList, i);
		ASSERTTRUE(!checkPostalCode_list(pRootList, pList));
		ASSERTTRUE(!checkPostalCode_list_rec(pRootList, pList));
		ASSERTTRUE(!checkPostalCode_int(pRootList, i));
		//ASSERTTRUE(!checkPostalCode_int_rec(---, i));
	}

	for (i = 10000; i < 99999; i++) {
		ASSERTTRUE(!checkPostalCode_list(pRootInt, pList));
		ASSERTTRUE(!checkPostalCode_list_rec(pRootInt, pList));
		ASSERTTRUE(!checkPostalCode_int(pRootInt, i));
		//ASSERTTRUE(!checkPostalCode_int_rec(---, i));
	}

	deletePCNode(pRootList);
	deletePCNode(pRootInt);
	deletePCList(pList);
}
