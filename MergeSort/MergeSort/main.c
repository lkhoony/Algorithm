#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

/*

# 1. Merge Sort

struct Node {
	int e;
	struct Node* next;
}typedef Node;

struct List {
	struct Node* header;
}typedef List;

struct Partition {
	Node* L1;
	Node* L2;
}typedef Partition;



Node* getNode(int e) {

	Node* node = (Node*)malloc(sizeof(Node));

	node->e = e;
	node->next = NULL;

	return node;
}


List* initList(int N) {

	List* list = (List*)malloc(sizeof(List));
	Node* header;

	int e;
	
	for (int i = 0; i < N; i++) {
		scanf("%d", &e);

		if (i == 0) {
			header = getNode(e);
			list->header = header;
		}
		else {
			header->next = getNode(e);
			header = header->next;
		}

	}

	return list;
}


Node* merge(Node* L1, Node* L2) {

	Node* node = NULL;
	Node* header = NULL;

	if (L1->e <= L2->e) {
		node = L1;
		L1 = L1->next;
	}
	else {
		node = L2;
		L2 = L2->next;
	}

	header = node;

	while (L1 != NULL && L2 != NULL) {

		if (L1->e <= L2->e) {
			node->next = L1;
			node = node->next;
			L1 = L1->next;
		}

		else {
			node->next = L2;
			node = node->next;
			L2 = L2->next;
		}
	}

	if (L1 == NULL) {
		node->next = L2;
	}
	else if (L2 == NULL) {
		node->next = L1;
	}

	return header;

}

Partition mgPartition(Node* L, int k) {
	
	Partition partition;
	Node* tmp;

	partition.L1 = L;
	partition.L2 = L;


	for (int i = 0; i < k - 1; i++) {
		partition.L2 = partition.L2->next;
	}

	tmp = partition.L2;
	partition.L2 = partition.L2->next;

	tmp->next = NULL;

	return partition;
}

void mergeSort(Node** L, int k) {

	if (k > 1 && *L != NULL) {

		Partition partition = mgPartition(*L, k / 2);

		Node* L1 = partition.L1;
		Node* L2 = partition.L2;

		mergeSort(&L1, k / 2);
		mergeSort(&L2, k - k / 2);

		*L = merge(L1, L2);
	}

}

void printList(Node* header) {

	Node* node = header;

	while (node != NULL) {
		printf(" %d", node->e);
		node = node->next;
	}

}

void freeNode(Node* node) {

	if (node->next == NULL) {
		free(node);
	}
	else {
		freeNode(node->next);
		free(node);
	}
}

void freeList(List* list) {

	freeNode(list->header);
	free(list);

}

int main() {

	int N;

	scanf("%d", &N);

	List* list = initList(N);

	mergeSort(&list->header, N);

	printList(list->header);

	freeList(list);

}


*/

/* 
* -------------------------------------------------
* 2-2. merge sort 배열로 구현하였을 때
* 
void merge(int* A, int l, int m, int r) {

	int i = l, k = l;
	int j = m + 1;
	int B[100] = { 0 };

	while (i <= m && j <= r) {
		if (A[i] <= A[j]) B[k++] = A[i++];
		else B[k++] = A[j++];
	}

	while (i <= m) {
		B[k++] = A[i++];
	}

	while (j <= r) {
		B[k++] = A[j++];
	}

	for (int k = l; k <= r; k++) {
		A[k] = B[k];
	}
}

void rMergeSort(int* A, int l, int r) {

	int m;

	if (l < r) {
		m = (l + r) / 2;
		rMergeSort(A, l, m);
		rMergeSort(A, m + 1, r);
		merge(A, l, m, r);
	}

	return;
}


void mergeSort(int* A, int N) {
	
	rMergeSort(A, 0, N - 1);

}

int main() {

	int N;
	int intArr[100] = { 0 };

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", intArr + i);
	}

	mergeSort(intArr, N);

	for (int i = 0; i < N; i++) {
		printf(" %d", *(intArr + i));
	}
}

*/


/*
// * ------------------------------------------------------------------------
// * 2. 퀵 정렬
// * 
struct Partition {
	int a;
	int b;
}typedef Partition;

void swap(int *a, int *b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

}

int* initList(int N) {

	int* list = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", list + i);
	}

	return list;
}

int findFivotIndex(int* L, int l, int r) {

	int medianIndex = l;


	if (r - l + 1 >= 3) {
		if (L[l] >= L[l + 1]) {
			if (L[l+1] >= L[l + 2]) {
				medianIndex = l + 1;
			}
			else {
				if (L[l] >= L[l + 2]) {
					medianIndex = l + 2;
				}
				else {
					medianIndex = l;
				}
			}
		}
		else {
			if (L[l+1] <= L[l+2]) {
				medianIndex = l + 1;
			}
			else {
				if (L[l] <= L[l + 2]) {
					medianIndex = l + 2;
				}
				else {
					medianIndex = l;
				}
			}
		}
	}

	return medianIndex;
}


Partition inPlacePartition(int* L, int l, int r, int k) {

	int p = *(L+k);
	Partition partition;

	swap((L + k), (L + r));

	int i = l;
	int j = r - 1;

	while (i <= j) {

		while (i <= j && *(L + i) <= p) {
			i++;
		}

		while (i <= j && *(L + j) >= p) {
			j--;
		}

		if (i < j) {
			swap(L + i, L + j);
		}
	}

	swap(L + i, L + r);

	partition.a = i - 1;
	partition.b = i + 1;

	return partition;

}

void inPlaceQuickSort(int *L, int l, int r) {

	if (l >= r) {
		return;
	}

	int k = findFivotIndex(L, l, r);

	Partition partition = inPlacePartition(L, l, r, k);
	inPlaceQuickSort(L, l, partition.a);
	inPlaceQuickSort(L, partition.b,r);

}


void printList(int* L,int N) {

	for (int i = 0; i < N; i++) {
		printf(" %d", *(L + i));
	}

}


int main() {

	int* list = NULL;
	int N;

	scanf("%d", &N);

	list = initList(N);

	inPlaceQuickSort(list, 0, N - 1);

	printList(list,N);

	free(list);
}

*/



// # 2.2 퀵정렬 중복값 고려

/*
struct Partition {
	int a;
	int b;
}typedef Partition;

void swap(int* a, int* b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

}

int* initList(int N) {

	int* list = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", list + i);
	}

	return list;
}

int findFivotIndex(int* L, int l, int r) {

	int medianIndex = l;


	if (r - l + 1 >= 3) {
		if (L[l] >= L[l + 1]) {
			if (L[l+1] >= L[l + 2]) {
				medianIndex = l + 1;
			}
			else {
				if (L[l] >= L[l + 2]) {
					medianIndex = l + 2;
				}
				else {
					medianIndex = l;
				}
			}
		}
		else {
			if (L[l+1] <= L[l+2]) {
				medianIndex = l + 1;
			}
			else {
				if (L[l] <= L[l + 2]) {
					medianIndex = l + 2;
				}
				else {
					medianIndex = l;
				}
			}
		}
	}

	return medianIndex;
}


Partition inPlacePartition(int* L, int l, int r, int k) {

	int p = *(L + k);
	Partition partition;

	int lt = l, i = l;
	int gt = r;

	while (i <= gt) {

		if (*(L + i) < p) {
			swap((L + i), (L + lt));
			lt++;
			i++;
		}
		else if (*(L + i) > p) {
			swap((L + i), (L + gt));
			gt--;
		}
		else if (*(L + i) == p) {
			i++;
		}
	}

	partition.a = lt - 1;
	partition.b = gt + 1;

	return partition;

}

void inPlaceQuickSort(int* L, int l, int r) {

	if (l >= r) {
		return;
	}

	int k = findFivotIndex(L, l, r);

	Partition partition = inPlacePartition(L, l, r, k);
	inPlaceQuickSort(L, l, partition.a);
	inPlaceQuickSort(L, partition.b, r);

}


void printList(int* L, int N) {

	for (int i = 0; i < N; i++) {
		printf(" %d", *(L + i));
	}

}


int main() {

	int* list = NULL;
	int N;

	scanf("%d", &N);

	list = initList(N);

	inPlaceQuickSort(list, 0, N - 1);

	printList(list, N);

	free(list);
}

*/
