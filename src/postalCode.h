/*
 * postalCode.h
 *
 *  Created on: 2009-feb-10
 *      Author: Johannes Wirde
 */

#ifndef POSTALCODE_H_
#define POSTALCODE_H_

#define TESTS 1000000

// printf("PCNode: %d\n", sizeof(struct PCNode)); == 44
struct PCNode {
	struct PCNode* prev;
	struct PCNode* next[10];
};

// printf("PCList: %d\n", sizeof(struct PCList)); == 8
struct PCList {
	int value;
	struct PCList* next;
};

struct PCNode* setupPCNode();
struct PCList* setupPCList();

int createPostalCode(struct PCList* in, int pcode);

int addPostalCode_list(struct PCNode* pNode, struct PCList* pNbr);
int addPostalCode_list_rec(struct PCNode* pNode, struct PCList* pNbr);
int addPostalCode_int(struct PCNode* in_pNode, int in_PC);
int addPostalCode_int_rec(struct PCNode* in_pNode, int in_PC);
int addPostalCode_int_rec_with_base(struct PCNode* in_pNode, int in_PC, int in_base);

int checkPostalCode_list(struct PCNode* pNode, struct PCList* pNbr);
int checkPostalCode_list_rec(struct PCNode* pNode, struct PCList* pNbr);
int checkPostalCode_int_rec(struct PCNode* in_pNode, int in_PC);
int checkPostalCode_int_rec_with_base(struct PCNode* in_pNode, int in_PC, int in_base);
int checkPostalCode_int(struct PCNode* in_pNode, int in_PC);

int printPostalCode(struct PCList* pNbr);

void deletePCList(struct PCList* in_pPCList);
void deletePCNode(struct PCNode* in_pPCNode);

#endif /* POSTALCODE_H_ */
