#include <stdio.h>
#include <stdlib.h>

// # 힙생성 알고리즘 
// # 힙 정렬 전에 최대 힙 구조를 만들어 주는 과정
// ---------------------------------------------------------
// 문제 1

//int H[100];
//int n = 0;
//
//void swapElement(int *p, int *q) {
//	int tmp;
//	tmp = *q;
//	*q = *p;
//	*p = tmp;
//}
//
//void upHeap(int i) {
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
//	upHeap(i / 2);
//}
//
//void downHeap(int i) {
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
//	downHeap(biggerIndex);
//	
//}
//
//void insertItem(int key) {
//	n++;
//	H[n] = key;
//	upHeap(n);
//	printf("0\n");
//}
//
//void removeMax() {
//
//	printf("%d\n", H[1]);
//	H[1] = H[n];
//	n--;
//	downHeap(1);
//}
//
//void printHeap() {
//
//	for (int i = 1; i <= n; i++) {
//		printf(" %d", H[i]);
//	}
//	printf("\n");
//}
//int main() {
//
//	int key;
//	char operation;
//
//	
//	while (1) {
//
//		scanf("%c", &operation);
//
//
//		if (operation == 'i') {
//			scanf("%d", &key);
//			insertItem(key);
//		}
//		else if (operation == 'd') {
//			removeMax(key);
//		}
//
//		else if (operation == 'p') {
//			printHeap(key);
//		}
//
//		else if (operation == 'q') {
//			break;
//		}
//
//		getchar();
//
//	}
//
//}

// ----------------------------------------------
// 문제2번 > 재귀방식을 oj에 업로드

//int H[100];
//int n = 0;
//
//void swapElement(int *p, int *q) {
//	int tmp;
//	tmp = *q;
//	*q = *p;
//	*p = tmp;
//
//}
//
//void downHeap(int i) {
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
//	downHeap(biggerIndex);
//}
//
//
//void rBuildHeap(int i) {
//
//	if (i > n) {
//		return;
//	}
//
//	rBuildHeap(2 * i);
//	rBuildHeap(2 * i + 1);
//	downHeap(i);
//}
//
//void buildHeap() {
//	for (int i = n / 2; i >= 1; i--) {
//		downHeap(i);
//	}
//}
//
//void printHeap() {
//
//	for (int i = 1; i <= n; i++) {
//		printf(" %d", H[i]);
//	}
//	printf("\n");
//
//}
//
//
//int main() {
//
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++) {
//		scanf("%d", &H[i]);
//	}
//	rBuildHeap(1);
//	printHeap();
//
//}

// ----------------------------------------------
// # 제자리 힙 정렬 구현
// # 만들어진 힙 구조를 가지고 배열을 정렬하는 과정

// # 문제 1 : 유일 키 - 값이 중복되는 키가 없을 경우

//int H[100];
//int n = 0;
//
//void swapElement(int* p, int* q) {
//	int tmp;
//	tmp = *q;
//	*q = *p;
//	*p = tmp;
//
//}
//
//void downHeap(int i) {
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
//	downHeap(biggerIndex);
//}
//
//
//void rBuildHeap(int i) {
//
//	if (i > n) {
//		return;
//	}
//
//	rBuildHeap(2 * i);
//	rBuildHeap(2 * i + 1);
//	downHeap(i);
//}
//
//void buildHeap() {
//	for (int i = n / 2; i >= 1; i--) {
//		downHeap(i);
//	}
//}
//
//
//void printHeap() {
//
//	for (int i = 1; i <= n; i++) {
//		printf(" %d", H[i]);
//	}
//	printf("\n");
//
//}
//
//void inPlaceHeapSort() {
//
//
//	int i = n;
//
//	while (n > 0) {
//
//		swapElement(&H[1], &H[n]);
//
//		n--;
//
//		downHeap(1);
//
//	}
//
//	n = i;
//}
//
//
//int main() {
//
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++) {
//		scanf("%d", &H[i]);
//	}
//	rBuildHeap(1);
//	inPlaceHeapSort();
//	printHeap();
//
//}


// ----------------------------------------------
// # 문제 2 : 중복 키 - 값이 중복되는 키가 있을 경우

int H[100];
int n = 0;

void swapElement(int* p, int* q) {
	int tmp;
	tmp = *q;
	*q = *p;
	*p = tmp;

}

void downHeap(int i) {

	int biggerIndex;

	if (i * 2 > n) {
		return;
	}

	biggerIndex = i * 2;

	if (i * 2 + 1 <= n) {
		if (H[biggerIndex] < H[i * 2 + 1])
			biggerIndex = i * 2 + 1;
	}

	if (H[i] < H[biggerIndex]) {
		swapElement(&H[i], &H[biggerIndex]);
	}

	downHeap(biggerIndex);
}


void rBuildHeap(int i) {

	if (i > n) {
		return;
	}

	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
}


void printHeap() {

	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");

}

void inPlaceHeapSort() {


	int i = n;

	while (n > 0) {

		swapElement(&H[1], &H[n]);

		n--;

		downHeap(1);

	}

	n = i;
}


int main() {

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	rBuildHeap(1);
	inPlaceHeapSort();
	printHeap();

}
