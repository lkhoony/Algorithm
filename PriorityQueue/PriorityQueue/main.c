#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void swap(int *x, int *y) {
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void selectionSort(int* intArr, int n) {

	int minLoc;

	for (int i =  0; i < n-1; i++) {
		minLoc = i;
		for (int j = i + 1; j < n ; j++) {
			if (*(intArr + j) < * (intArr + minLoc)) {
				minLoc = j;
			}
		}
		if (minLoc!=i) {
			swap(intArr + i, intArr + minLoc);
		}
	}
}

// 내림차순으로 정렬하는 함수
void selectionRevSort(int* intArr, int n) {

	int maxLoc;

	for (int i = 0; i < n - 1; i++) {
		maxLoc = i;
		for (int j = i + 1; j < n; j++) {
			if (*(intArr + j) > *(intArr + maxLoc)) {
				maxLoc = j;
			}
		}
		if (maxLoc != i) {
			swap(intArr + i, intArr + maxLoc);
		}
	}

	//for (int i = 0; i < n; i++) {
	//	printf(" %d", intArr[i]);
	//}
}

void insertSort(int* intArr, int n){

	int j,save;

	for (int i = 1; i < n; i++) {
		j = i - 1;
		save = intArr[i];
		while (j >= 0 && intArr[j] > save) {
			intArr[j + 1] = intArr[j];
			j--;
		}
		intArr[j + 1] = save;
	}

}
int main() {

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int n, num;
	int* selectionArr, * insertArr;
	QueryPerformanceFrequency(&ticksPerSec);
	// ==========================================================
	// 
	// A. 각 정렬의 입력으로 정렬이 안 된 데이터가 주어지는 경우
	//
	// n = 100000 -> 선택정렬 : 약 11 sec , 삽입정렬 : 약 6sec 
	// n = 200000 -> 선택정렬 : 약 46 sec , 삽입정렬 : 약 24sec 
	// n = 300000 -> 선택정렬 : 약 118 sec , 삽입정렬 : 약 55sec
	//
	// => 선택정렬보단 삽입정렬이 정렬속도가 빠름, 입력 데이터의 크기가 N배로 증가할 때마다 실행 시간은 N^2배로 증가하는 경향을 보임

	srand(time(NULL));
	printf("A. 각 정렬의 입력으로 정렬이 안 된 데이터가 주어지는 경우\n\n");
	for (int i = 0; i < 3; i++) {

		printf(" * n 입력 : ");
		scanf("%d", &n);
		selectionArr = (int*)malloc(sizeof(int) * n);
		insertArr = (int*)malloc(sizeof(int) * n);

		for (int j = 0; j < n; j++) {
			num = rand();
			selectionArr[j] = num;
			insertArr[j] = num;
		}
		
		// # 결과
		printf("  * n의 크기가 %d일 때 경과시간\n",n);
		// -----------------------------------------------------
		// # 선택정렬
		QueryPerformanceCounter(&start);
		selectionSort(selectionArr,n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("   - 선택정렬: %.12f sec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		// -----------------------------------------------------
		// # 삽입정렬
		QueryPerformanceCounter(&start);
		insertSort(insertArr, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("   - 삽입정렬: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		free(selectionArr);
		free(insertArr);
	}

	// ==========================================================
	// 
	// B. 각 정렬의 입력으로 정렬 된 데이터가 주어지는 경우
	//
	// n = 100000 -> 선택정렬 : 약 11 sec , 삽입정렬 : 약 0.0005sec 
	// n = 200000 -> 선택정렬 : 약 47 sec , 삽입정렬 : 약 0.00075sec 
	// n = 300000 -> 선택정렬 : 약 115 sec , 삽입정렬 : 약 0.0012sec
	//
	// => 정렬이 되어있는 데이터지만 선택정렬은 순회를 해야하기 때문에 실행시간이 오래걸림, 
	//		입력 데이터의 크기가 N배 증가할 때마다 실행시간은 N^2배로 증가하는 경향을 보임
	// => 삽입 정렬은 데이터를 한번만 순회하기 때문에 실행시간이 짧고 입력 데이터의 크기가 N배 증가할 때 마다 실행시간은 N배로 증가하는 경향

	printf("B. 각 정렬의 입력으로 정렬 된 데이터가 주어지는 경우\n\n");

	for (int i = 0; i < 3; i++) {

		printf(" * n 입력 : ");
		scanf("%d", &n);

		insertArr = (int*)malloc(sizeof(int) * n);
		selectionArr = (int*)malloc(sizeof(int) * n);

		for (int j = 0; j < n; j++) {
			num = rand();
			selectionArr[j] = num;
			insertArr[j] = num;
		}

		// 삽입정렬을 사용하여 각각 정렬

		insertSort(selectionArr, n);
		insertSort(insertArr, n);

		// # 결과
		printf("  * n의 크기가 %d일 때 경과시간\n", n);
		// -----------------------------------------------------
		// # 선택정렬
		QueryPerformanceCounter(&start);
		selectionSort(selectionArr, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("   - 선택정렬: %.12f sec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		// -----------------------------------------------------
		// # 삽입정렬
		QueryPerformanceCounter(&start);
		insertSort(insertArr, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("   - 삽입정렬: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		free(selectionArr);
		free(insertArr);
	}

	// ==========================================================
	// 
	// C. 각 정렬의 입력으로 역순으로 정렬 된 데이터가 주어지는 경우
	//
	// n = 100000 -> 선택정렬 : 약 18 sec , 삽입정렬 : 약 12sec 
	// n = 200000 -> 선택정렬 : 약 65 sec , 삽입정렬 : 약 48sec 
	// n = 300000 -> 선택정렬 : 약 131 sec , 삽입정렬 : 약 111sec
	//
	// => 선택정렬, 삽입정렬 모두 입력 데이터의 크기가 N배로 증가할 때마다 실행 시간은 N^2배로 증가하는 경향을 보임

	printf("C. 각 정렬의 입력으로 역순으로 정렬 된 데이터가 주어지는 경우\n\n");
	for (int i = 0; i < 3; i++) {

		printf(" * n 입력 : ");
		scanf("%d", &n);

		insertArr = (int*)malloc(sizeof(int) * n);
		selectionArr = (int*)malloc(sizeof(int) * n);

		for (int j = 0; j < n; j++) {
			num = rand();
			selectionArr[j] = num;
			insertArr[j] = num;
		}

		// 역순으로 정렬
		selectionRevSort(selectionArr, n);
		selectionRevSort(insertArr, n);

		// # 결과

		printf("  * n의 크기가 %d일 때 경과시간\n", n);
		// -----------------------------------------------------
		// # 선택정렬
		QueryPerformanceCounter(&start);
		selectionSort(selectionArr, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("   - 선택정렬: %.12f sec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		// -----------------------------------------------------
		// # 삽입정렬
		QueryPerformanceCounter(&start);
		insertSort(insertArr, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("   - 삽입정렬: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

		free(selectionArr);
		free(insertArr);
	}

}