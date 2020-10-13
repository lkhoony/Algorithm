#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* 
* # 1. 재귀적인 방법으로 사전 구현
* 
int* initDictionary(int N) {

	int* dictionary;
	
	dictionary = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", dictionary + i);
	}

	return dictionary;

}

int findElement(int* dictionary, int l, int r, int k) {

	int mid;

	
	if (l > r) {
		if (r < 0) {
			return -1;
		}
		else {
			return r;
		}
	}

	mid = (l + r) / 2;

	if (*(dictionary + mid) == k) {
		return mid;
	}

	else if (*(dictionary+mid)>k) findElement(dictionary, l, mid - 1, k);

	else if (*(dictionary + mid) < k) findElement(dictionary, mid+1, r, k);

}

int main() {

	int N,K;
	scanf("%d%d", &N,&K);

	printf(" %d", findElement(initDictionary(N), 0, N - 1, K));

}

*/

/*
int* initDictionary(int N) {

	int* dictionary;

	dictionary = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", dictionary + i);
	}

	return dictionary;

}

int findElement(int* dictionary, int left, int right, int k) {

	int l = left;
	int r = right;
	int mid,index=0, N = right - left + 1;


	while (l <= r) {

		mid = (l + r) / 2;

		if (*(dictionary + mid) == k) {
			index = mid;
			break;
		}
		else {
			if (*(dictionary + mid) > k) r = mid - 1;
			else l = mid + 1;
		}
	}

	if (l > r) {
		if (l > N) {
			index = -1;
		}
		else {
			index = l;
		}
	}

	return index;

}

int main() {

	int N, K;
	scanf("%d%d", &N, &K);

	printf(" %d", findElement(initDictionary(N), 0, N - 1, K));

}

/*
* 
* #2. 비재귀적인 방법으로 구현
* 
int* initDictionary(int N) {

	int* dictionary;

	dictionary = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", dictionary + i);
	}

	return dictionary;

}

int findElement(int* dictionary, int left, int right, int k) {

	int l = left;
	int r = right;
	int mid,index=0, N = right - left + 1;


	while (l <= r) {

		mid = (l + r) / 2;

		if (*(dictionary + mid) == k) {
			index = mid;
			break;
		}
		else {
			if (*(dictionary + mid) > k) r = mid - 1;
			else l = mid + 1;
		}
	}

	if (l > r) {
		if (l > N) {
			index = -1;
		}
		else {
			index = l;
		}
	}

	return index;

}

int main() {

	int N, K;
	scanf("%d%d", &N, &K);

	printf(" %d", findElement(initDictionary(N), 0, N - 1, K));

}

*/

int* initDictionary(int A, int B) {

	int* dictionary;
	int N = B - A;
	dictionary = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i <=  N; i++) {
		*(dictionary+i) = A+i;
	}

	return dictionary;

}

int findElement(int* dictionary, int stringNum, int A, int B) {

	int ansIndex=0, aIndex = 0, bIndex = B-A;
	char ch;


	for (int i = 0; i < stringNum; i++) {

		scanf("%c", &ch);

		if (ch == 'N') {
			bIndex = (aIndex + bIndex) / 2;
		}
		else if (ch == 'Y') {
			aIndex = (aIndex + bIndex) / 2 + 1;

		}
	}

	ansIndex = (aIndex + bIndex) / 2;

	return *(dictionary + ansIndex);

}

int main() {

	int A,B,stringNum;
	int* dictionary;

	scanf("%d%d%d", &A, &B,&stringNum);
	getchar();

	dictionary = initDictionary(A, B);

	printf("%d", findElement(dictionary, stringNum, A, B));
}