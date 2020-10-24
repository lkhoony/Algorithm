#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int solution(int n, int *callNum) {
//	
//	(*callNum)++;
//
//	if (n == 0) {
//		return 1;
//	}
//
//
//	return solution(n / 2,callNum) + solution(n / 3,callNum);
//	 
//}
//
//int main() {
//	
//	int n, callNum = 0;
//	
//	scanf("%d", &n);
//
//	int result = solution(n, &callNum);
//
//	printf("%d %d", result, callNum);
//
//}

// # 2¹ø

//int H[101];
//int Hmin[101];
//int n = 0;
//int n_min = 0;
//
//void swapElement(int *p, int *q) {
//	int tmp;
//	tmp = *q;
//	*q = *p;
//	*p = tmp;
//}
//
//void upMinHeap(int i) {
//
//	
//	if (i == 1) {
//		return;
//	}
//
//	if (Hmin[i / 2] < Hmin[i]) {
//		return;
//	}
//
//	swapElement(&Hmin[i / 2], &Hmin[i]);
//	upMinHeap(i / 2);
//}
//
//void upMaxHeap(int i) {
//
//
//	if (i == 1) {
//		return;
//	}
//
//	if (H[i / 2] > H[i]) {
//		return;
//	}
//
//	swapElement(&H[i / 2], &H[i]);
//	upMaxHeap(i / 2);
//}
//
//void downMaxHeap(int i) {
//
//	int biggerIndex;
//
//	if (i * 2 > n) {
//		return;
//	}
//
//	biggerIndex = i * 2;
//
//	if (i * 2 + 1 <= n) {
//		if (H[biggerIndex] < H[i * 2 + 1]) 
//			biggerIndex = i * 2 + 1;	
//	}
//
//	if (H[i] < H[biggerIndex]) {
//		swapElement(&H[i], &H[biggerIndex]);
//	}
//
//	downMaxHeap(biggerIndex);
//	
//}
//
//void downMinHeap(int i) {
//
//	int minIndex;
//
//	if (i * 2 > n_min) {
//		return;
//	}
//
//	minIndex = i * 2;
//
//	if (i * 2 + 1 <= n_min) {
//		if (Hmin[minIndex] > Hmin[i * 2 + 1])
//			minIndex = i * 2 + 1;
//	}
//
//	if (Hmin[i] > Hmin[minIndex]) {
//		swapElement(&Hmin[i], &Hmin[minIndex]);
//	}
//
//	downMinHeap(minIndex);
//
//}
//
//void insertItem(int key) {
//	n++;
//	H[n] = key;
//	upMaxHeap(n);
//	// printf("0\n");
//}
//
//void inserMintItem(int key) {
//	n_min++;
//	Hmin[n_min] = key;
//	upMinHeap(n_min);
//	// printf("0\n");
//}
//
//void removeMax() {
//
//	printf("%d ", H[1]);
//	H[1] = H[n];
//	n--;
//	downMaxHeap(1);
//}
//
//void removeMin() {
//
//	printf("%d", Hmin[1]);
//	Hmin[1] = Hmin[n_min];
//	n_min--;
//	downMinHeap(1);
//}
//
//
//int main() {
//
//	int N,key;
//
//	scanf("%d", &N);
//
//	for (int i = 0; i < N; i++) {
//		scanf("%d", &key);
//		insertItem(key);
//		inserMintItem(key);
//	}
//
//	while (n != 0) {
//
//		for (int i = 1; i <= n; i++) {
//			printf(" %d", H[i]);
//		}
//
//		printf("\n");
//
//		for (int i = 1; i <= n_min; i++) {
//			printf(" %d", Hmin[i]);
//		}
//		printf("\n");
//
//		removeMax();
//
//		removeMin();
//
//		printf("\n");
//	}
//}

// # 4¹ø

//struct Partition {
//	int a;
//	int b;
//}typedef Partition;
//
//void swap(int* a, int* b) {
//	int tmp;
//	tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
//
//char* initList(int N) {
//
//	char* list = (char*)malloc(sizeof(char) * N);
//	for (int i = 0; i < N; i++) {
//		scanf("%c", list + i);
//	}
//	return list;
//}
//
//int findFivotIndex(int* L, int l, int r, char p) {
//	int medianIndex = l;
//	if (r - l + 1 >= 3) {
//		if (L[l] >= L[l + 1]) {
//			if (L[l + 1] >= L[l + 2]) {
//				medianIndex = l + 1;
//			}
//			else {
//				if (L[l] >= L[l + 2]) {
//					medianIndex = l + 2;
//				}
//				else {
//					medianIndex = l;
//				}
//			}
//		}
//		else {
//			if (L[l + 1] <= L[l + 2]) {
//				medianIndex = l + 1;
//			}
//			else {
//				if (L[l] <= L[l + 2]) {
//					medianIndex = l + 2;
//				}
//				else {
//					medianIndex = l;
//				}
//			}
//		}
//	}
//	return medianIndex;
//}
//Partition inPlacePartition(int* L, int l, int r, int k) {
//	int p = *(L + k);
//	Partition partition;
//	swap((L + k), (L + r));
//	int i = l;
//	int j = r - 1;
//	while (i <= j) {
//		while (i <= j && *(L + i) <= p) {
//			i++;
//		}
//		while (i <= j && *(L + j) >= p) {
//			j--;
//		}
//		if (i < j) {
//			swap(L + i, L + j);
//		}
//	}
//	swap(L + i, L + r);
//	partition.a = i - 1;
//	partition.b = i + 1;
//	return partition;
//}
//void inPlaceQuickSort(int* L, int l, int r,char p) {
//
//	if (l >= r) {
//		return;
//	}
//
//	//int k = findFivotIndex(L, l, r);
//	//Partition partition = inPlacePartition(L, l, r, k);
//
//	Partition partition = inPlacePartition(L, l, r, p);
//	inPlaceQuickSort(L, l, partition.a,p);
//	inPlaceQuickSort(L, partition.b, r,p);
//}
//void printList(char* L, int N) {
//	for (int i = 0; i < N; i++) {
//		printf(" %c", *(L + i));
//	}
//}
//int main() {
//	int* list = NULL;
//	int N;
//	scanf("%d", &N);
//	getchar();
//
//	list = initList(N);
//	printList(list, N);
//}

struct Partition {
	int a;
	int b;
}typedef Partition;

void swap(char* a, char* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


char* initList(int N) {

	char* list = (char*)malloc(sizeof(char) * N);

	for (int i = 0; i < N; i++) {
		scanf("%c", list + i);
	}

	getchar();

	return list;
}


Partition inPlacePartition(char* L, int l, int r, char* cList) {
	
	Partition partition;
	int lt = l, i = l;
	int gt = r;

	char first= *cList;
	char second = *(cList+1);
	char third = *(cList+2);

	printf("%c %c %c\n",first,second,third);

	for (int i = 0; i <= r; i++) {
		printf("%c\n", *(L + i));
	}
	while (i <= gt) {
		if (*(L + i) == first) {
			swap((L + i), (L + lt));
			lt++;
			i++;
		}
		else if (*(L + i) ==third) {
			swap((L + i), (L + gt));
			gt--;
		}
		else if (*(L + i) == second) {
			i++;
		}
	}
}


void printList(char* L, int N) {
	for (int i = 0; i < N; i++) {
		printf(" %c", *(L + i));
	}
}

int main() {

	int N;
	int score = 0;

	
	scanf("%d", &N);
	getchar();

	char* copyList = (char*)malloc(sizeof(char) * N);
	char* aList = (char*)malloc(sizeof(char) * 3);
	char* cList = (char*)malloc(sizeof(char) * N);

	scanf("%s", aList);
	getchar();

	scanf("%s", cList);

	strcpy(copyList, cList);

	inPlacePartition(copyList, 0, N-1, aList);

	printf("%s\n", cList);
	printf("%s\n", copyList);

	for (int i = 0; i < N; i++) {
		if (cList[i] == 'R' && copyList[i] == 'S') {
			score++;
		}
		else if (cList[i] == 'R' && copyList[i] == 'P') {
			score--;
		}
		else if (cList[i] == 'S' && copyList[i] == 'P') {
			score++;
		}
		else if (cList[i] == 'S' && copyList[i] == 'R') {
			score--;
		}
		else if (cList[i] == 'P' && copyList[i] == 'R') {
			score++;
		}
		else if (cList[i] == 'P' && copyList[i] == 'S') {
			score--;
		}
	}

	printf("%d", score);

}