/*
 * postalCode.c
 *
 *  Created on: 2009-feb-10
 *      Author: johwi
 */

#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "postalCode.h"
#include "postalCodeAssert.h"

struct PCNode* setupPCNode() {
/*
	struct PCNode* tmp = (struct PCNode*)malloc(sizeof(struct PCNode));
	tmp->prev = NULL;

	int i = 0;
	while (i < sizeof(tmp->next)/sizeof(struct PCNode*)) {
		tmp->next[i] = NULL;
		i++;
	}
*/
	struct PCNode* tmp_pPCNode = (struct PCNode*)calloc(1, sizeof(struct PCNode));
	return tmp_pPCNode;
}

struct PCList* setupPCList() {
	//struct PCList* tmp_pPCList = (struct PCList*)malloc(sizeof(struct PCList));
	struct PCList* tmp_pPCList = (struct PCList*)calloc(1, sizeof(struct PCList));
	//tmp_pPCList->value = 0;
	//tmp_pPCList->next = NULL;

	return tmp_pPCList;
}

int addPostalCode_list(struct PCNode* in_pNode, struct PCList* in_pPCList) {
	CHECKPTR(in_pNode);
	CHECKPTR(in_pPCList);

	while (in_pPCList != NULL) {
		if (in_pNode->next[in_pPCList->value] == NULL) { // Create new node and attach
			// Create new
			in_pNode->next[in_pPCList->value] = setupPCNode();

			// Move to next
			in_pNode->next[in_pPCList->value]->prev = in_pNode;
			in_pNode = in_pNode->next[in_pPCList->value];
			in_pPCList = in_pPCList->next;
		}
		else {
			in_pNode = in_pNode->next[in_pPCList->value];
			in_pPCList = in_pPCList->next;
		}
	}

	return OK;
}

int addPostalCode_list_rec(struct PCNode* in_pNode, struct PCList* in_pPCList) {
	CHECKPTR(in_pNode);
	CHECKPTR(in_pPCList);

	if (in_pNode->next[in_pPCList->value] == NULL) { // Create new node and attach
		in_pNode->next[in_pPCList->value] = setupPCNode();
		in_pNode->next[in_pPCList->value]->prev = in_pNode;
	}

	// Move to next or return
	if (in_pPCList->next != NULL)
		addPostalCode_list_rec(in_pNode->next[in_pPCList->value], in_pPCList->next);

	return OK;
}

/*
int addPostalCode_int(struct PCNode* in_pNode, int in_PC) {
	int tmp_base = 0;
	int tmp_val = 0;

	if (in_PC < 10) tmp_base = 1;
	else if (in_PC < 100) tmp_base = 10;
	else if (in_PC < 1000) tmp_base = 100;
	else if (in_PC < 10000) tmp_base = 1000;
	else tmp_base = 10000;

	tmp_val = (in_PC - (in_PC % tmp_base)) / tmp_base;
	in_PC -= tmp_val * tmp_base;

	if (in_pNode->next[tmp_val] == NULL) { // Create new node
		in_pNode->next[tmp_val] = setupPCNode();
	}

	if (tmp_base == 1) return OK;
	else return addPostalCode_int(in_pNode->next[tmp_val], in_PC);

	return OK;
}
*/

int addPostalCode_int(struct PCNode* in_pNode, int in_PC) {
	CHECKPTR(in_pNode);
	ASSERTFALSE(in_PC < 10000);
	int tmp_PC[5];
	int i = 0;

	for (i = 4; i >= 0; i--) {
		tmp_PC[i] = in_PC % 10;
		in_PC -= tmp_PC[i];
		in_PC /= 10;
	}

	for (i = 0; i <= 4; i++) {
		if (i != 4) { // If we are not on the last digit of "in_PC"
			if (in_pNode->next[tmp_PC[i]] == NULL)
				in_pNode->next[tmp_PC[i]] = setupPCNode();
			in_pNode = in_pNode->next[tmp_PC[i]];
		}
		else {
			if (in_pNode->next[tmp_PC[i]] == NULL)
				in_pNode->next[tmp_PC[i]] = setupPCNode();
		}
	}

	return OK;
}

int createPostalCode(struct PCList* in_pPCList, int in_PC) {
	CHECKPTR(in_pPCList);
	ASSERTTRUE(9999 < in_PC && in_PC < 100000);

	int tmp_base = 10000;
	int tmp_val = 0;

	while (tmp_base >= 1) {
		tmp_val = (in_PC - (in_PC % tmp_base)) /  tmp_base; // Left most digit of "in_PC" gets extracted (handles leading zeros)
		in_PC -= tmp_val * tmp_base;
		tmp_base /= 10;

		in_pPCList->value = tmp_val;
		if (tmp_base != 0) { // If we are not on the last digit of "in_PC"
			if (in_pPCList->next == NULL)
				in_pPCList->next = setupPCList();
			in_pPCList = in_pPCList->next;
		}

	}

	return OK;
}

int checkPostalCode_list(struct PCNode* in_pNode, struct PCList* in_pPCList) {
	while (in_pPCList != NULL) {
		if (in_pNode->next[in_pPCList->value] != NULL) {
			in_pNode = in_pNode->next[in_pPCList->value];
			in_pPCList = in_pPCList->next;
		}
		else {
			return ERROR;
		}
	}

	return OK;
}

int checkPostalCode_list_rec(struct PCNode* in_pNode, struct PCList* in_pPCList) {
	if (in_pNode->next[in_pPCList->value] == NULL) return ERROR;
	if (in_pPCList->next == NULL && in_pNode->next[in_pPCList->value] != NULL) return OK;

	return checkPostalCode_list_rec(in_pNode->next[in_pPCList->value], in_pPCList->next);
}

int checkPostalCode_int_rec(struct PCNode* in_pNode, int in_PC) {
	CHECKPTR(in_pNode);
	ASSERTTRUE(9999 < in_PC);
	ASSERTTRUE(in_PC < 100000);

	return checkPostalCode_int_rec_with_base(in_pNode, in_PC, 10000);
}

int checkPostalCode_int_rec_with_base(struct PCNode* in_pNode, int in_PC, int in_base) {
	CHECKPTR(in_pNode);
	ASSERTFALSE(in_base <= 0);

	int tmp_val = (in_PC - (in_PC % in_base)) /  in_base; // Left most digit of "in_PC" gets extracted (handles leading zeros)
	in_PC -= tmp_val * in_base;
	in_base /= 10;

	if (in_pNode->next[tmp_val] != NULL && in_base == 1) return OK; // Found and at last digit of postal code
	if (in_pNode->next[tmp_val] == NULL) return ERROR; // Not found and at last digit of postal code

	return checkPostalCode_int_rec_with_base(in_pNode->next[tmp_val], in_PC, in_base); // Found but not at last digit, continue search
}

int checkPostalCode_int(struct PCNode* in_pNode, int in_PC) {
	CHECKPTR(in_pNode);
	ASSERTFALSE(in_PC < 10000);

	int tmp_PC[5];
	int tmp_PC_pos = 0;

	for (tmp_PC_pos = 4; tmp_PC_pos >= 0; tmp_PC_pos--) {
		tmp_PC[tmp_PC_pos] = in_PC % 10;
		in_PC -= tmp_PC[tmp_PC_pos];
		in_PC /= 10;
	}

	for (tmp_PC_pos = 0;tmp_PC_pos <= 4; tmp_PC_pos++) {
		if (in_pNode->next[tmp_PC[tmp_PC_pos]] != NULL && tmp_PC_pos == 4) return OK; // Found and at last digit
		if (in_pNode->next[tmp_PC[tmp_PC_pos]] == NULL) return ERROR; // Not found

		in_pNode = in_pNode->next[tmp_PC[tmp_PC_pos]];
	}

	return ERROR;
}

int addPostalCode_int_rec(struct PCNode* in_pNode, int in_PC) {
	CHECKPTR(in_pNode);
	ASSERTTRUE(9999 < in_PC);
	ASSERTTRUE(in_PC < 100000);

	return addPostalCode_int_rec_with_base(in_pNode, in_PC, 10000);
}

int addPostalCode_int_rec_with_base(struct PCNode* in_pNode, int in_PC, int in_base) {
	CHECKPTR(in_pNode);
	ASSERTFALSE(in_base <= 0);

	int tmp_val = (in_PC - (in_PC % in_base)) /  in_base; // Left most digit of "in_PC" gets extracted (handles leading zeros)
	in_PC -= tmp_val * in_base;
	in_base /= 10;

	if (in_pNode->next[tmp_val] == NULL)
		in_pNode->next[tmp_val] = setupPCNode();

	if (in_base == 0) return OK;
	return addPostalCode_int_rec_with_base(in_pNode->next[tmp_val], in_PC, in_base); // Found but not at last digit, continue search
}
int printPostalCode(struct PCList* in_pPCList) {
	CHECKPTR(in_pPCList);

	printf("Postal code: ");
	while (in_pPCList != NULL) {
		printf("%d", in_pPCList->value);
		in_pPCList = in_pPCList->next;
	}

	printf("\n");

	return OK;
}

void deletePCList(struct PCList* in_pPCList) {
	CHECKPTR(in_pPCList);

	if (in_pPCList->next != NULL)
		deletePCList(in_pPCList->next);

	free(in_pPCList);
}

void deletePCNode(struct PCNode* in_pPCNode) {
	CHECKPTR(in_pPCNode);
	int i = 0;

	for (i = 0; i < 10; i++ )
		if (in_pPCNode->next[i] != NULL)
			deletePCNode(in_pPCNode->next[i]);

	free(in_pPCNode);
}
