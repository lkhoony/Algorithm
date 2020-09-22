#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* // -----------------------------------------------------------------
// # 1. 실습시간 풀이

struct Node {
	char elem;
	struct Node* prev;
	struct Node* next;
}typedef Node;

struct List {
	struct Node* header;
	struct Node* trailer;
	int nodeNum;
}typedef List;

Node* createNode(char elem) {

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = elem;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

List* initList() {

	List* list = (List*)malloc(sizeof(List));
	list->header = createNode(0);
	list->trailer = createNode(0);
	list->nodeNum = 0;
	list->header->next = list->trailer;
	list->trailer->prev = list->header;

	return list;
}

void add(List* list, int r, char e) {

	Node* node = list->header;

	if (r<0 || r>(list->nodeNum) + 1) {
		printf("invalid position\n");
	}
	else {

		for (int i = 0; i < r; i++) node = node->next;
		Node* newNode = createNode(e);
		newNode->prev = node->prev;
		newNode->next = node;
		newNode->prev->next = newNode;
		newNode->next->prev = newNode;

		(list->nodeNum)++;
	}
}

void delete(List* list, int r) {

	Node* node = list->header;

	if (r<0 || r>list->nodeNum) {
		printf("invalid position\n");
	}

	else {

		for (int i = 0; i < r; i++) node = node->next;

		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
		(list->nodeNum)--;

	}

}
void get(List* list, int r) {

	Node* node = list->header;

	if (r<0 || r>list->nodeNum) {
		printf("invalid position\n");
	}

	else {

		for (int i = 0; i < r; i++) node = node->next;

		printf("%c\n", node->elem);
	}
}

void print(List* list) {

	Node* node = list->header;

	while (node->next) {
		node = node->next;
		printf("%c", node->elem);
	}

	printf("\n");
}

void freeNode(Node* node) {

	if (node) {
		freeNode(node->next);
		free(node);
	}
}

void freeList(List* list) {
	freeNode(list->header);
	free(list);
}

void doOperate(List* list) {

	int N, r;
	char operate, e;
	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {

		scanf("%c", &operate);

		if (operate == 'A') {
			scanf("%d %c", &r, &e);
			add(list, r, e);
		}
		else if (operate == 'D') {
			scanf("%d", &r);
			delete(list, r);
		}
		else if (operate == 'G') {
			scanf("%d", &r);
			get(list, r);
		}
		else if (operate == 'P') {
			print(list);
		}

		getchar();
	}

	freeList(list);
}

int main()
{
	doOperate(initList());

}
*/
// -----------------------------------------------------------------
// # 1. 복습풀이
/*
struct Node{
	char e;
	struct Node *prev;
	struct Node *next;
}typedef Node;

struct List {
	struct Node *header;
	struct Node *trailer;
	int nodeNum;
}typedef List;

Node* createNode(char e) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->e = e;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

List* initList() {

	List *newList = (List*)malloc(sizeof(List));
	newList->header = createNode(0);
	newList->trailer = createNode(0);
	newList->nodeNum = 0;

	newList->header->next = newList->trailer;
	newList->trailer->prev = newList->header;

	return newList;
}

void add(List *list, int r, char e) {

	Node *node = list->header;

	if (r<0 || r>(list->nodeNum) + 1)
		printf("invalid position\n");

	else {
		for (int i = 0; i < r; i++) node = node->next;
		Node* newNode = createNode(e);
		node->prev->next = newNode;
		newNode->next = node;
		newNode->prev = node->prev;
		node->prev = newNode;
		
		(list->nodeNum)++;
	}
}

void delete(List* list, int r) {

	Node* node = list->header;

	if (r<0 || r>list->nodeNum)
		printf("invalid position\n");

	else {
		for (int i = 0; i < r; i++) node = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);

		(list->nodeNum)--;
	}
}

void get(List* list, int r) {

	Node* node = list->header;

	if (r<0 || r>list->nodeNum)
		printf("invalid position\n");

	else {
		for (int i = 0; i < r; i++) node = node->next;
		printf("%c\n", node->e);
	}
}

void print(List* list) {
	Node* node = list->header;
	while (node->next != NULL) {
		node = node->next;
		printf("%c", node->e);
	}
	printf("\n");
}

void freeNode(Node* node) {
	if (node) {
		freeNode(node->next);
		free(node);
	}
}

void doOperate(List *list, int N) {

	int r;
	char operation, e;

	for (int i = 0; i < N; i++) {
		scanf("%c", &operation);
		if (operation == 'A') {
			scanf("%d %c", &r, &e);
			add(list, r, e);
		}
		else if (operation == 'D') {
			scanf("%d", &r);
			delete(list, r);
		}
		else if (operation == 'G') {
			scanf("%d", &r);
			get(list, r);
		}
		else if (operation == 'P') {
			print(list);
		}
		getchar();
	}
}

int main() {

	List* list = initList();
	int N, r;
	char operation, e;

	scanf("%d", &N);
	getchar();

	doOperate(list, N);

	free(list->header);
	free(list);
}
*/

/*
#1 Test Case
9
A 1 D
A 2 a
A 3 y
D 1
P
G 3
A 1 S
P
G 3
*/

/*
struct Node {
	struct Node* left;
	struct Node* right;
	int id;
}typedef Node;

struct Tree {
	struct Node* root;
	int nodeCnt;
	int maxNodeCnt;
}typedef Tree;

Node* createNode(int x) {

	Node* node = (Node*)malloc(sizeof(Node));
	node->id = x;
	node->left = NULL;
	node->right = NULL;
	return node;

}

Tree* initTree() {

	int maxNodeCnt;
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->nodeCnt = 0;
	tree->root = NULL;

	scanf("%d", &maxNodeCnt);
	tree->maxNodeCnt = maxNodeCnt;

	return tree;
}

Node* addNode(Tree *tree) {
	
	int x, y, z;

	if (tree->nodeCnt == tree->maxNodeCnt)
		return NULL;

	else {

		scanf("%d%d%d", &x, &y, &z);
		Node *node = createNode(x);
		(tree->nodeCnt)++;

		if (y != 0) {
			node->left = addNode(tree);
		}

		if (z != 0) {
			node->right = addNode(tree);
		}
		
		return node;
	}
}

void printId(Node* node, char *orderArr) {

	if (node != NULL) {

		printf(" %d", node->id);

		if (*orderArr == 'R') {
			printId(node->right, orderArr + 1);
		}
		else if (*orderArr == 'L') {
			printId(node->left, orderArr + 1);
		}

	}
}


void orderTree(Tree* tree) {

	int N;
	char orderArr[101];

	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {
		gets(orderArr);
		printId(tree->root, orderArr);
		printf("\n");
	}

}

void freeNode(Node* node) {

	if (node) {
		freeNode(node->left);
		freeNode(node->right);
		free(node);
	}

}
void freeTree(Tree* tree) {
	freeNode(tree->root);
	free(tree);
}

int main() {
	Tree* tree = initTree();
	tree->root = addNode(tree);
	orderTree(tree);
	freeTree(tree);
}
*/
/*
9
5 3 9
3 8 15
8 0 2
2 0 0
15 0 0
9 7 10
7 12 0
12 0 0
10 0 0
3
RLL
LL
LR
*/