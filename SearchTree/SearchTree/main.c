#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

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

void printTreeNode(treeNode* node) {

	if (isExternal(node)) {
		return;
	}

	printf(" %d", node->key);
	printTreeNode(node->lChild);
	printTreeNode(node->rChild);
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

treeNode* createExternalNode(treeNode *parent) {

	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	node->lChild = NULL;
	node->rChild = NULL;
	node->parent = parent;

	return node;
}
int findElement(int k,treeNode **root) {

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

treeNode* reduceExternal(treeNode* z, treeNode **root) {

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
		if (removeNode->parent!= NULL) {

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

			if (findKey==-1) printf("X\n");
			else printf("%d\n", findKey);

		}

		else if (operate == 'p') {
			printTreeNode(root);
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
i 5
i 8
i 3
i 4
p
d 2
d 13
p
q

*/

// AVL 트리 삽입 구현

/*
struct treeNode {

	struct treeNode* lChild;
	struct treeNode* rChild;
	struct treeNode* parent;
	int key;
	int height;

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

void printTreeNode(treeNode* node) {

	if (isExternal(node)) {
		return;
	}

	printf(" %d", node->key);
	printTreeNode(node->lChild);
	printTreeNode(node->rChild);
}


treeNode* initTree() {

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));

	root->lChild = NULL;
	root->rChild = NULL;
	root->parent = NULL;
	root->key = 0;
	root->height = 0;

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
	node->key = 0;
	node->height = 0;

	return node;
}
int findElement(int k, treeNode** root) {

	treeNode* findNode = treeSearch(k, root);

	if (isExternal(findNode)) return -1;
	else return findNode->key;
}

int getHeightDiff(treeNode* node) {

	return node->lChild->height - node->rChild->height;

}

void updateHeight(treeNode* node) {

	if (node->lChild->height >= node->rChild->height) node->height = node->lChild->height + 1;
	else node->height = node->rChild->height + 1;

}

void rotateLL(treeNode* node, treeNode **root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->lChild;
	//x = y->lChild;
	zParent = z->parent;

	z->lChild = y->rChild;
	y->rChild->parent = z;
	y->rChild = z;
	z->parent = y;

	y->parent = zParent;

	if (zParent == NULL) 
		*root = y;
	else {
		if (zParent->lChild == z) {
			y->parent = zParent;
			zParent->lChild = y;
		}
		else {
			y->parent = zParent;
			zParent->rChild = y;
		}
	}

	updateHeight(z);
	updateHeight(y);
}

void rotateRR(treeNode* node, treeNode** root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->rChild;
	//x = y->lChild;
	zParent = z->parent;

	z->rChild = y->lChild;
	y->lChild->parent = z;
	y->lChild = z;
	z->parent = y;

	y->parent = zParent;

	if (zParent == NULL)
		*root = y;
	else {
		if (zParent->lChild == z) zParent->lChild = y;
		else zParent->rChild = y;
		
	}

	updateHeight(z);
	updateHeight(y);
}

void rotateLR(treeNode *node, treeNode **root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->lChild;
	x = y->rChild;
	zParent = z->parent;

	// 1. 첫 번째 회전
	z->lChild = x;
	x->parent = z;

	y->rChild = x->lChild;
	x->lChild->parent = y;

	x->lChild = y;
	y->parent = x;

	// 2. 두 번째 회전
	z->lChild = x->rChild;
	x->rChild->parent = z;

	x->rChild = z;
	z->parent = x;
	
	x->parent = zParent;

	if (zParent == NULL)
		*root = x;
	else {
		if (zParent->lChild == z) {
			x->parent = zParent;
			zParent->lChild = x;
		}
		else {
			x->parent = zParent;
			zParent->rChild = x;
		}
	}

	updateHeight(y);
	updateHeight(z);
	updateHeight(x);

}

void rotateRL(treeNode* node, treeNode **root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->rChild;
	x = y->lChild;
	zParent = z->parent;

	// 1. 첫 번째 회전
	z->rChild = x;
	x->parent = z;

	y->lChild = x->rChild;
	x->rChild->parent = y;

	x->rChild = y;
	y->parent = x;

	// 2. 두 번째 회전
	z->rChild = x->lChild;
	x->lChild->parent = z;

	x->lChild = z;
	z->parent = x;

	x->parent = zParent;

	if (zParent == NULL)
		*root = x;
	else {
		if (zParent->lChild == z) {
			x->parent = zParent;
			zParent->lChild = x;
		}
		else {
			x->parent = zParent;
			zParent->rChild = x;
		}
	}

	updateHeight(y);
	updateHeight(z);
	updateHeight(x);
}

void rotateTree(treeNode* node, treeNode** root) {
	
	int diff;

	diff = getHeightDiff(node);

	// 1. 노드의 왼쪽 자식에서 불균형 발생
	if (diff == 2) {

		// LL회전
		if (getHeightDiff(node->lChild) > 0) {
			rotateLL(node,root);
		}
		// LR회전
		else if (getHeightDiff(node->lChild) < 0) {
			rotateLR(node,root);
		}
		
	}

	// 2. 노드의 오른쪽 자식에서 불균형 발생
	else if(diff==-2){

		// RL회전
		if (getHeightDiff(node->rChild) > 0) {
			rotateRL(node, root);
		}
		// RR회전
		else if (getHeightDiff(node->rChild) < 0) {
			rotateRR(node, root);
		}

	}
}

// node의 자식들의 높이를 체크하는 함수
void checkHeightDiff(treeNode* node, treeNode** root) {

	int diff;

	while (node != NULL) {

		diff = getHeightDiff(node);

		if (diff < -1 || diff >1) {
			rotateTree(node, root);
			return;
		}

		updateHeight(node);

		node = node->parent;
	}
}

void insertItem(int k, treeNode** root) {

	treeNode* w = root;
	treeNode* pw; // 개조를 위한 노드 저장을 위한 변수

	int diff; // 높이 차이를 저장하기 위한 변수

	w = treeSearch(k, root);
	if (isInternal(w)) return;

	else if (isExternal(w)) {

		w->key = k;
		w->lChild = createExternalNode(w);
		w->rChild = createExternalNode(w);

		checkHeightDiff(w,root);

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

		else if (operate == 'p') {
			printTreeNode(root);
			printf("\n");
		}

		else if (operate == 'q') {
			break;
		}

		getchar();
	}
}
*/

// AVL트리 삭제 구현

struct treeNode {

	struct treeNode* lChild;
	struct treeNode* rChild;
	struct treeNode* parent;
	int key;
	int height;

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

void printTreeNode(treeNode* node) {

	if (isExternal(node)) {
		return;
	}

	printf(" %d", node->key);
	printTreeNode(node->lChild);
	printTreeNode(node->rChild);
}


treeNode* initTree() {

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));

	root->lChild = NULL;
	root->rChild = NULL;
	root->parent = NULL;
	root->key = 0;
	root->height = 0;

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
	node->key = 0;
	node->height = 0;

	return node;
}
int findElement(int k, treeNode** root) {

	treeNode* findNode = treeSearch(k, root);

	if (isExternal(findNode)) return -1;
	else return findNode->key;
}

int getHeightDiff(treeNode* node) {

	return node->lChild->height - node->rChild->height;

}

void updateHeight(treeNode* node) {

	if (node->lChild->height >= node->rChild->height) node->height = node->lChild->height + 1;
	else node->height = node->rChild->height + 1;

}

treeNode* rotateLL(treeNode* node, treeNode** root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->lChild;
	zParent = z->parent;

	z->lChild = y->rChild;
	y->rChild->parent = z;
	y->rChild = z;
	z->parent = y;

	y->parent = zParent;

	if (zParent == NULL)
		*root = y;
	else {
		if (zParent->lChild == z) {
			y->parent = zParent;
			zParent->lChild = y;
		}
		else {
			y->parent = zParent;
			zParent->rChild = y;
		}
	}

	updateHeight(z);
	updateHeight(y);

	return y;
}

treeNode* rotateRR(treeNode* node, treeNode** root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->rChild;
	zParent = z->parent;

	z->rChild = y->lChild;
	y->lChild->parent = z;
	y->lChild = z;
	z->parent = y;

	y->parent = zParent;

	if (zParent == NULL)
		*root = y;
	else {
		if (zParent->lChild == z) zParent->lChild = y;
		else zParent->rChild = y;

	}

	updateHeight(z);
	updateHeight(y);

	return y;
}

treeNode* rotateLR(treeNode* node, treeNode** root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->lChild;
	x = y->rChild;
	zParent = z->parent;

	// 1. 첫 번째 회전
	z->lChild = x;
	x->parent = z;

	y->rChild = x->lChild;
	x->lChild->parent = y;

	x->lChild = y;
	y->parent = x;

	// 2. 두 번째 회전
	z->lChild = x->rChild;
	x->rChild->parent = z;

	x->rChild = z;
	z->parent = x;

	x->parent = zParent;

	if (zParent == NULL)
		*root = x;
	else {
		if (zParent->lChild == z) {
			x->parent = zParent;
			zParent->lChild = x;
		}
		else {
			x->parent = zParent;
			zParent->rChild = x;
		}
	}

	updateHeight(y);
	updateHeight(z);
	updateHeight(x);

	return x;

}

treeNode* rotateRL(treeNode* node, treeNode** root) {

	treeNode* z;
	treeNode* y;
	treeNode* x;
	treeNode* zParent;

	z = node;
	y = node->rChild;
	x = y->lChild;
	zParent = z->parent;

	// 1. 첫 번째 회전
	z->rChild = x;
	x->parent = z;

	y->lChild = x->rChild;
	x->rChild->parent = y;

	x->rChild = y;
	y->parent = x;

	// 2. 두 번째 회전
	z->rChild = x->lChild;
	x->lChild->parent = z;

	x->lChild = z;
	z->parent = x;

	x->parent = zParent;

	if (zParent == NULL)
		*root = x;
	else {
		if (zParent->lChild == z) {
			x->parent = zParent;
			zParent->lChild = x;
		}
		else {
			x->parent = zParent;
			zParent->rChild = x;
		}
	}

	updateHeight(y);
	updateHeight(z);
	updateHeight(x);

	return x;
}

treeNode* rotateTree(treeNode* node, treeNode** root) {

	int diff;
	treeNode* w;
	diff = getHeightDiff(node);

	// 1. 노드의 왼쪽 자식에서 불균형 발생
	if (diff == 2) {

		// LL회전
		if (getHeightDiff(node->lChild) >= 0) {
			w = rotateLL(node, root);
		}
		// LR회전
		else if (getHeightDiff(node->lChild) < 0) {
			w = rotateLR(node, root);
		}

	}

	// 2. 노드의 오른쪽 자식에서 불균형 발생
	else if (diff == -2) {

		// RL회전
		if (getHeightDiff(node->rChild) > 0) {
			w = rotateRL(node, root);
		}
		// RR회전
		else if (getHeightDiff(node->rChild) <= 0) {
			w = rotateRR(node, root);
		}

	}
}

// node의 자식들의 높이를 체크하는 함수
void checkHeightDiff(treeNode* node, treeNode** root) {

	int diff;

	while (node != NULL) {

		diff = getHeightDiff(node);

		if (diff < -1 || diff >1) {
			node = rotateTree(node, root);
			node = node->parent;
			//return;
		}
		else {
			updateHeight(node);
			node = node->parent;
		}
	}
}

void insertItem(int k, treeNode** root) {

	treeNode* w = root;
	treeNode* pw; // 개조를 위한 노드 저장을 위한 변수

	int diff; // 높이 차이를 저장하기 위한 변수

	w = treeSearch(k, root);
	if (isInternal(w)) return;

	else if (isExternal(w)) {

		w->key = k;
		w->lChild = createExternalNode(w);
		w->rChild = createExternalNode(w);

		checkHeightDiff(w, root);

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
	treeNode* z;
	treeNode* zs;
	treeNode* y;

	int key;

	
	// 1. 삭제 할 노드가 없을 경우
	if (isExternal(removeNode)) {
		//printf("case1\n");
		key = -1;
		return key;
	}

	key = removeNode->key;
	z = removeNode->lChild;

	if (!isExternal(z)) z = removeNode->rChild;

	if (isExternal(z)) zs = reduceExternal(z,root);

	else {
		y = inOrderSucc(removeNode);
		z = y->lChild;

		removeNode->key = y->key;
		
		zs = reduceExternal(z,root);
	}

	checkHeightDiff(zs->parent, root);

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

		else if (operate == 'p') {
			printTreeNode(root);
			printf("\n");
		}

		else if (operate == 'q') {
			break;
		}

		getchar();
	}
}