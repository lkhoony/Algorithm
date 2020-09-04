#include <stdio.h>
#include <stdlib.h>

struct Element {
	int key;
}typedef Element;

struct HeapType {
	Element heap[100];
	int heapSize;
}typedef HeapType;

void insertMaxHeap(HeapType* heapType, Element element) {

	int i;
	i = ++(heapType->heapSize);

	while (i > 0 && element.key > heapType->heap[i / 2].key) {
		heapType->heap[i] = heapType->heap[i / 2];
		i = i / 2;
	}

	heapType->heap[i] = element;
}

Element deleteMaxHeap(HeapType* heapType) {

	Element maxElement = heapType->heap[1];
	heapType->heap[1] = heapType->heap[(heapType->heapSize)--];
	Element element = heapType->heap[1];

	int i = 1;

	while (2 * i <= heapType->heapSize) {

		if (2 * i + 1 <= heapType->heapSize) {
			if (element.key > heapType->heap[2 * i].key && element.key > heapType->heap[2 * i + 1].key)
				break;
			else {
				if (heapType->heap[2 * i].key >= heapType->heap[2 * i + 1].key) {
					heapType->heap[i] = heapType->heap[2 * i];
					i = i * 2;
				}
				else {
					heapType->heap[i] = heapType->heap[2 * i + 1];
					i = i * 2 + 1;
				}
			}
		}
		else {
			if (element.key <= heapType->heap[2 * i].key) {
				heapType->heap[i] = heapType->heap[2 * i];
				i = i * 2;
			}
		}

	}
	heapType->heap[i] = element;

	return maxElement;
}

Element* createElement(int key) {
	Element* element = (Element*)malloc(sizeof(Element));
	element->key = key;
	return element;
}

HeapType* createHeap() {
	int N;
	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));
	scanf("%d", &N);
	heap->heapSize = N;
	for (int i = 1; i <= heap->heapSize; i++) {
		scanf("%d", &N);
		insertMaxHeap(heap, *createElement(N));
	}
}

void printHeap(HeapType* heap) {
	for (int i = 1; i <= heap->heapSize; i++) {
		printf(" %d", heap->heap[i].key);
	}
}

