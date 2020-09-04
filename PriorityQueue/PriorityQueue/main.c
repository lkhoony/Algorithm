#include <stdio.h>


void swap(int *x, int *y) {
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int main() {

	int intArr[100],N,minLoc,j=0,save;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", intArr + i);
	}

	// #1 Selection Sort
	
	for (int i = 0; i < N - 1; i++) {
		minLoc = i;
		for (int j = i + 1; j < N; j++) {
			if (intArr[minLoc] > intArr[j])
				minLoc = j;
		}
		swap(intArr + i, intArr + minLoc);
	}
	

	// #2 Insert Sort
	for (int i = 1; i < N; i++) {
		j = i - 1;
		save = intArr[i];
		while (j >= 0 && intArr[j] > save) {
			intArr[j + 1] = intArr[j];
			j--;
		}
		intArr[j + 1] = save;
	}
	for (int i = 0; i < N; i++)
		printf("%d ", *(intArr + i));

}