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

// -----------------------------------------------------------------------------------

// # 2번

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

// -----------------------------------------------------------------------------------
// # 4번

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

/*
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

*/
// -----------------------------------------------------------------------------------
// 5-1

/*
struct treeNode {
	struct treeNode* lChild;
	struct treeNode* rChild;
	struct treeNode* parent;
	int key;
}typedef treeNode;

int isExternal(treeNode* w) {
	if (w->lChild == NULL && w->rChild == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
int isInternal(treeNode* w) {
	if (w->lChild != NULL || w->rChild != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
treeNode* inOrderSucc(treeNode* w) {
	w = w->rChild;
	if (isExternal(w)) return;
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

void printTreeNodeA(treeNode* node) {
	if (isExternal(node)) {
		return;
	}
	printf(" %d", node->key);
	printTreeNodeA(node->lChild);
	printTreeNodeA(node->rChild);
}

void printTreeNodeB(treeNode* node) {
	if (isExternal(node)) {
		return;
	}
	printTreeNodeB(node->lChild);
	printf(" %d", node->key);
	printTreeNodeB(node->rChild);
}

void printTreeNodeC(treeNode* node) {
	if (isExternal(node)) {
		return;
	}

	printTreeNodeC(node->lChild);
	printTreeNodeC(node->rChild);

	printf(" %d", node->key);
}

treeNode* initTree() {

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));

	root->lChild = NULL;
	root->rChild = NULL;
	root->parent = NULL;
	root->key = 0;
	return root;
}
treeNode* treeSearch(int k, treeNode** root) {
	treeNode* w = *root;
	while (isInternal(w)) {
		if (k == w->key) return w;
		else if (k < w->key) w = w->lChild;
		else if (k > w->key) w = w->rChild;
	}
	return w;
}
treeNode* sibling(treeNode* w) {
	if (w->parent == NULL) return;
	if (w->parent->rChild == w) return w->parent->lChild;
	else return w->parent->rChild;
}
treeNode* createExternalNode(treeNode* parent) {
	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	node->lChild = NULL;
	node->rChild = NULL;
	node->parent = parent;
	return node;
}
int findElement(int k, treeNode** root) {
	treeNode* findNode = treeSearch(k, root);
	if (isExternal(findNode)) return -1;
	else return findNode->key;
}
void insertItem(int k, treeNode** root) {
	treeNode* w = root;
	w = treeSearch(k, root);
	if (isInternal(w)) return;
	else if (isExternal(w)) {
		w->key = k;
		w->lChild = createExternalNode(w);
		w->rChild = createExternalNode(w);
	}
}
treeNode* reduceExternal(treeNode* z, treeNode** root) {
	treeNode* w = z->parent;
	treeNode* zs = sibling(z);
	if (w->parent == NULL) {
		*root = zs;
		zs->parent = NULL;
	}
	else {
		treeNode* g = w->parent;
		zs->parent = g;
		if (w == g->rChild) g->rChild = zs;
		else g->lChild = zs;
	}
	free(z);
	free(w);
	return zs;
}
int removeElement(int k, treeNode** root) {
	treeNode* removeNode = treeSearch(k, root);
	int key;
	// 1. 삭제 할 노드가 없을 경우
	if (isExternal(removeNode)) {
		//printf("case1\n");
		key = -1;
	}
	// 2. 삭제하는 노드의 자식이 모두 외부노드일 경우
	else if (isExternal(removeNode->lChild) && isExternal(removeNode->rChild)) {

		//printf("case2\n");
		// 삭제하려는 노드가 루트노드일 경우
		// 노드를 삭제하고 새로운 루트노드 생성
		if (removeNode->parent == NULL) {
			*root = initTree();
		}
		// 삭제하려는 노드가 루트노드가 아닐 경우
		else {
			if (removeNode == removeNode->parent->rChild)
				removeNode->parent->rChild = createExternalNode(removeNode->parent);
			else if (removeNode == removeNode->parent->lChild)
				removeNode->parent->lChild = createExternalNode(removeNode->parent);
		}
		key = removeNode->key;
		free(removeNode->lChild);
		free(removeNode->rChild);
		free(removeNode);
	}

	// 3. 삭제하는 노드가 내부 노드일 경우
	else if (isInternal(removeNode->lChild) && isInternal(removeNode->rChild)) {
		//printf("case3\n");
		treeNode* inOrderSuccNode = inOrderSucc(removeNode);
		//printf("remove key : %d\n", removeNode->key);
		//printf("inOrderSuccNode key : %d\n", inOrderSuccNode->key);
		if (removeNode->rChild == inOrderSuccNode) {
			;			free(inOrderSuccNode->lChild);
			inOrderSuccNode->lChild = removeNode->lChild;
			removeNode->lChild->parent = inOrderSuccNode;
		}
		else {
			free(inOrderSuccNode->lChild);
			inOrderSuccNode->parent->lChild = inOrderSuccNode->rChild;
			inOrderSuccNode->rChild->parent = inOrderSuccNode->parent;
			inOrderSuccNode->lChild = removeNode->lChild;
			inOrderSuccNode->rChild = removeNode->rChild;
			removeNode->lChild->parent = inOrderSuccNode;
			removeNode->rChild->parent = inOrderSuccNode;
		}
		// 삭제 할 노드가 루트노드가 아닐 경우
		if (removeNode->parent != NULL) {
			if (removeNode->parent->lChild == removeNode) {
				inOrderSuccNode->parent = removeNode->parent;
				removeNode->parent->lChild = inOrderSuccNode;
			}
			else {
				inOrderSuccNode->parent = removeNode->parent;
				removeNode->parent->rChild = inOrderSuccNode;
			}
		}
		else if (removeNode->parent == NULL) {
			*root = inOrderSuccNode;
			inOrderSuccNode->parent = NULL;
		}
		key = removeNode->key;
		free(removeNode);
	}
	// 4. 삭제하는 노드의 자식중 하나가 외부 노드일 경우
	else if (isExternal(removeNode->lChild) || isExternal(removeNode->rChild)) {
		//printf("case4\n");
		key = removeNode->key;
		if (isExternal(removeNode->lChild))
			reduceExternal(removeNode->lChild, root);
		else
			reduceExternal(removeNode->rChild, root);
	}
	return key;
}

int main() {
	treeNode* root = initTree();
	char operate;
	int k;
	while (1) {
		scanf("%c", &operate);
		if (operate == 'i') {
			scanf("%d", &k);
			insertItem(k, &root);
		}
		else if (operate == 'd') {
			scanf("%d", &k);
			int removeKey = removeElement(k, &root);
			if (removeKey == -1) printf("X\n");
			else printf("%d\n", removeKey);

		}
		else if (operate == 's') {
			scanf("%d", &k);
			int findKey = findElement(k, &root);
			if (findKey == -1) printf("X\n");
			else printf("%d\n", findKey);
		}
		else if (operate == 'a') {
			printTreeNodeA(root);
			printf("\n");
		}

		else if (operate == 'b') {
			printTreeNodeB(root);
			printf("\n");
		}

		else if (operate == 'c') {
			printTreeNodeC(root);
			printf("\n");
		}

		else if (operate == 'q') {
			break;
		}
		getchar();
	}
}
*/
/*
i 3
i 2
i 7
i 6
i 5
s 6
s 8
a
b
c
q
*/

// -----------------------------------------------------------------------------------
// 5-2
/*
struct treeNode {
	struct treeNode* lChild;
	struct treeNode* rChild;
	struct treeNode* parent;
	int key;
}typedef treeNode;

int isExternal(treeNode* w) {
	if (w->lChild == NULL && w->rChild == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
int isInternal(treeNode* w) {
	if (w->lChild != NULL || w->rChild != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
treeNode* inOrderSucc(treeNode* w) {
	w = w->rChild;
	if (isExternal(w)) return;
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

void printTreeNodeA(treeNode* node) {
	if (isExternal(node)) {
		return;
	}
	printf(" %d", node->key);
	printTreeNodeA(node->lChild);
	printTreeNodeA(node->rChild);
}

void printTreeNodeB(treeNode* node) {
	if (isExternal(node)) {
		return;
	}
	printTreeNodeB(node->lChild);
	printf(" %d", node->key);
	printTreeNodeB(node->rChild);
}

void printTreeNodeC(treeNode* node) {
	if (isExternal(node)) {
		return;
	}

	printTreeNodeC(node->lChild);
	printTreeNodeC(node->rChild);

	printf(" %d", node->key);
}

treeNode* initTree() {

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));

	root->lChild = NULL;
	root->rChild = NULL;
	root->parent = NULL;
	root->key = 0;
	return root;
}
treeNode* treeSearch(int k, treeNode** root) {
	treeNode* w = *root;
	while (isInternal(w)) {
		printf("%d", w->key);
		if (k == w->key) return w;
		else if (k < w->key) w = w->lChild;
		else if (k > w->key) w = w->rChild;
	}
	return w;
}
treeNode* sibling(treeNode* w) {
	if (w->parent == NULL) return;
	if (w->parent->rChild == w) return w->parent->lChild;
	else return w->parent->rChild;
}
treeNode* createExternalNode(treeNode* parent) {
	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	node->lChild = NULL;
	node->rChild = NULL;
	node->parent = parent;
	return node;
}
int findElement(int k, treeNode** root) {
	treeNode* findNode = treeSearch(k, root);
	if (isExternal(findNode)) return -1;
	else return findNode->key;
}
void insertItem(int k, treeNode** root) {
	treeNode* w = root;
	w = treeSearch(k, root);
	if (isInternal(w)) return;
	else if (isExternal(w)) {
		w->key = k;
		w->lChild = createExternalNode(w);
		w->rChild = createExternalNode(w);
	}
}
treeNode* reduceExternal(treeNode* z, treeNode** root) {
	treeNode* w = z->parent;
	treeNode* zs = sibling(z);
	if (w->parent == NULL) {
		*root = zs;
		zs->parent = NULL;
	}
	else {
		treeNode* g = w->parent;
		zs->parent = g;
		if (w == g->rChild) g->rChild = zs;
		else g->lChild = zs;
	}
	free(z);
	free(w);
	return zs;
}
int removeElement(int k, treeNode** root) {
	treeNode* removeNode = treeSearch(k, root);
	int key;
	// 1. 삭제 할 노드가 없을 경우
	if (isExternal(removeNode)) {
		//printf("case1\n");
		key = -1;
	}
	// 2. 삭제하는 노드의 자식이 모두 외부노드일 경우
	else if (isExternal(removeNode->lChild) && isExternal(removeNode->rChild)) {

		//printf("case2\n");
		// 삭제하려는 노드가 루트노드일 경우
		// 노드를 삭제하고 새로운 루트노드 생성
		if (removeNode->parent == NULL) {
			*root = initTree();
		}
		// 삭제하려는 노드가 루트노드가 아닐 경우
		else {
			if (removeNode == removeNode->parent->rChild)
				removeNode->parent->rChild = createExternalNode(removeNode->parent);
			else if (removeNode == removeNode->parent->lChild)
				removeNode->parent->lChild = createExternalNode(removeNode->parent);
		}
		key = removeNode->key;
		free(removeNode->lChild);
		free(removeNode->rChild);
		free(removeNode);
	}

	// 3. 삭제하는 노드가 내부 노드일 경우
	else if (isInternal(removeNode->lChild) && isInternal(removeNode->rChild)) {
		//printf("case3\n");
		treeNode* inOrderSuccNode = inOrderSucc(removeNode);
		//printf("remove key : %d\n", removeNode->key);
		//printf("inOrderSuccNode key : %d\n", inOrderSuccNode->key);
		if (removeNode->rChild == inOrderSuccNode) {
			;			free(inOrderSuccNode->lChild);
			inOrderSuccNode->lChild = removeNode->lChild;
			removeNode->lChild->parent = inOrderSuccNode;
		}
		else {
			free(inOrderSuccNode->lChild);
			inOrderSuccNode->parent->lChild = inOrderSuccNode->rChild;
			inOrderSuccNode->rChild->parent = inOrderSuccNode->parent;
			inOrderSuccNode->lChild = removeNode->lChild;
			inOrderSuccNode->rChild = removeNode->rChild;
			removeNode->lChild->parent = inOrderSuccNode;
			removeNode->rChild->parent = inOrderSuccNode;
		}
		// 삭제 할 노드가 루트노드가 아닐 경우
		if (removeNode->parent != NULL) {
			if (removeNode->parent->lChild == removeNode) {
				inOrderSuccNode->parent = removeNode->parent;
				removeNode->parent->lChild = inOrderSuccNode;
			}
			else {
				inOrderSuccNode->parent = removeNode->parent;
				removeNode->parent->rChild = inOrderSuccNode;
			}
		}
		else if (removeNode->parent == NULL) {
			*root = inOrderSuccNode;
			inOrderSuccNode->parent = NULL;
		}
		key = removeNode->key;
		free(removeNode);
	}
	// 4. 삭제하는 노드의 자식중 하나가 외부 노드일 경우
	else if (isExternal(removeNode->lChild) || isExternal(removeNode->rChild)) {
		//printf("case4\n");
		key = removeNode->key;
		if (isExternal(removeNode->lChild))
			reduceExternal(removeNode->lChild, root);
		else
			reduceExternal(removeNode->rChild, root);
	}
	return key;
}

int main() {
	treeNode* root = initTree();
	char operate;
	int k;
	while (1) {
		scanf("%c", &operate);
		if (operate == 'i') {
			scanf("%d", &k);
			insertItem(k, &root);
		}
		else if (operate == 'd') {
			scanf("%d", &k);
			int removeKey = removeElement(k, &root);
			if (removeKey == -1) printf("X\n");
			else printf("%d\n", removeKey);

		}
		else if (operate == 's') {
			scanf("%d", &k);
			int findKey = findElement(k, &root);
			if (findKey == -1) printf("X\n");
			else printf("O\n");
		}
		else if (operate == 'a') {
			printTreeNodeA(root);
			printf("\n");
		}

		else if (operate == 'b') {
			printTreeNodeB(root);
			printf("\n");
		}

		else if (operate == 'c') {
			printTreeNodeC(root);
			printf("\n");
		}

		else if (operate == 'q') {
			break;
		}
		getchar();
	}
}
*/
/*
i 9
i 2
i 15
i 1
i 7
i 11
s 2
s 16
s 9
a
b
c
q
*/