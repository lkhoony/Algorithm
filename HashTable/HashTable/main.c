#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
struct Node{

	int key;
	struct Node* prev;
	struct Node* next;

}typedef Node;

Node** initHashTable(int M) {

	Node** hashTable = (Node*)malloc(sizeof(Node)*M);

	for (int i = 0; i < M; i++) {
		*(hashTable +i) = NULL;

	}
	return hashTable;

}

void insertKey(int key, int M, Node** hashTable) {

	int listIndex = key % M;

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->key = key;
	
	if (*(hashTable+listIndex) == NULL) newNode->next = NULL;
	else newNode->next = *(hashTable + listIndex);
	
	*(hashTable + listIndex) = newNode;
}

int searchHashTable(int key, int M, Node** hashTable) {

	int listIndex = key % M;
	int keyIndex = 0;

	Node* node = *(hashTable + listIndex);

	while (node != NULL) {

		keyIndex++;

		if (node->key == key)
			return keyIndex;
		
		node = node->next;
	}

	return 0;

}

int removeKey(int key, int M, Node** hashTable) {

	int listIndex = key % M;
	int keyIndex = 0;

	Node* node = *(hashTable + listIndex);
	Node* prev = NULL;

	while (node != NULL) {

		keyIndex++;

		if (node->key == key) {

			if (prev == NULL) *(hashTable + listIndex) = node->next;
			else prev->next = node->next;

			free(node);
			return keyIndex;
		}

		prev = node;
		node = node->next;
	}

	return 0;

}
void printHashTable(int M, Node** hashTable) {

	for (int i = 0; i < M; i++) {

		Node* node = *(hashTable + i);
		
		while (node != NULL) {
			printf(" %d", node->key);
			node = node->next;
		}
	}

	printf("\n");

}

void freeNode(Node* node) {

	if (node == NULL) {
		return;
	}

	freeNode(node->next);
	free(node);

}

void freeHashTable(int M, Node** hashTable) {

	for (int i = 0; i < M; i++) {
		freeNode(*(hashTable + i));
	}

}

int main() {

	int M,k,result;
	char operate;

	scanf("%d", &M);

	Node** hashTable = initHashTable(M);

	getchar();

	while (1) {

		scanf("%c", &operate);

		if (operate == 'i') {
			scanf("%d", &k);
			insertKey(k, M, hashTable);
			
		}
		else if (operate == 's') {
			scanf("%d", &k);
			result =  searchHashTable(k, M, hashTable);
			printf("%d\n", result);
		}

		else if (operate == 'd') {
			scanf("%d", &k);
			result =  removeKey(k, M, hashTable);
			printf("%d\n", result);
		}

		else if (operate == 'p') {
			printHashTable(M, hashTable);
		}

		else if (operate == 'e') {
			freeHashTable(M, hashTable);
			break;
		}

		getchar();
	}
}
*/

/*
int* initHashTable(int M) {

	int* hashTable = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < M; i++) {
		*(hashTable + i) = 0;
	}

	return hashTable;
}

void insertKey(int key, int M, int* hashTable) {

	int index = key % M;
	int i = 0;
	int getIndex;

	while (i<M) {
		
		getIndex = (index + i) % M;

		if (*(hashTable + getIndex) == 0) {
			*(hashTable + getIndex) = key;
			printf("%d\n", getIndex);
			return;
		}

		else {
			printf("C");
			i++;
		}
	}

}

void searchHashTable(int key, int M, int* hashTable) {

	int index = key % M;
	int i = 0;
	int getIndex;

	while (i < M) {

		getIndex = (index + i) % M;

		if (*(hashTable + getIndex) == key) {
			printf("%d %d\n", getIndex,*(hashTable+getIndex));
			return;
		}

		i++;
	}

	printf("%d\n", -1);
}


int main() {
	int M, k, n;
	char operate;

	scanf("%d %d", &M, &n);

	int* hashTable = initHashTable(M);

	getchar();

	while (1) {

		scanf("%c", &operate);

		if (operate == 'i') {
			scanf("%d", &k);
			insertKey(k, M, hashTable);

		}
		else if (operate == 's') {
			scanf("%d", &k);
			searchHashTable(k, M, hashTable);
		}

		else if (operate == 'e') {
			free(hashTable);
			break;
		}

		getchar();
	}
}

*/

int* initHashTable(int M) {

	int* hashTable = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < M; i++) {
		*(hashTable + i) = 0;
	}

	return hashTable;
}

void insertKey(int key, int M, int q, int* hashTable) {

	int index = key % M;
	int i = 0;
	int getIndex;
	int h = q - (key % q);

	while (i < M) {

		getIndex = (index + i * h) % M;

		if (*(hashTable + getIndex) == 0) {
			*(hashTable + getIndex) = key;
			printf("%d\n", getIndex);
			return;
		}

		else {
			printf("C");
			i++;
		}
	}

}

void searchHashTable(int key, int M, int* hashTable) {

	int index = key % M;
	int i = 0;
	int getIndex;

	while (i < M) {

		getIndex = (index + i) % M;

		if (*(hashTable + getIndex) == key) {
			printf("%d %d\n", getIndex, *(hashTable + getIndex));
			return;
		}

		i++;
	}

	printf("%d\n", -1);
}

void printHashTable(int M, int* hashTable) {

	for (int i = 0; i < M; i++) {
		printf(" %d", *(hashTable + i));
	}

	printf("\n");

}

int main() {
	int M, k, n,q;
	char operate;

	scanf("%d %d %d", &M, &n, &q);

	int* hashTable = initHashTable(M);

	getchar();

	while (1) {

		scanf("%c", &operate);

		if (operate == 'i') {
			scanf("%d", &k);
			insertKey(k, M, q, hashTable);

		}
		else if (operate == 's') {
			scanf("%d", &k);
			searchHashTable(k, M, hashTable);
		}

		else if (operate == 'p') {
			printHashTable(M, hashTable);
		}

		else if (operate == 'e') {
			printHashTable(M, hashTable);
			free(hashTable);
			break;
		}

		getchar();
	}
}
