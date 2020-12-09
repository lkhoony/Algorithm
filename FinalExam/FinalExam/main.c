#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS


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