#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode* right;
}typedef TreeNode;

TreeNode* searchTree(TreeNode* node, int key) {

	if (node == NULL) {
		return NULL;
	}

	if (key == node->key) {
		return node;
	}

	else if (key > node->key) {
		search(node->right, key);
	}
	else
		search(node->left, key);

}

void insertNode(TreeNode** root, int key) {

	TreeNode* parent, *tmp;
	
	tmp = *root;
	parent = NULL;

	while (tmp != NULL) {
		
		if (key == tmp->key) return;

		parent = tmp;

		if (key > parent->key) tmp = parent->right;
		else tmp = parent->left;

	}

	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = NULL;
	node->right = NULL;
	node->key = key;

	if (parent != NULL) {
		if (key > parent->key) parent->right = node;
		else parent->left = node;
	}

	else *root = node;

}

void deleteNode(TreeNode** root, int key) {

	TreeNode* parent, * w, *tmp, *tmpParent;

	parent = NULL;
	w = *root;
	int e; // 삭제될 키가 입력될 변수

	while (w != NULL && w->key != key) {
		parent = w;
		if (w->key > key) {
			w = w->right;
		}
		else
			w = w->left;
	}

	if (w == NULL) {
		printf("No Such Key");
		return;
	}

	// 1. 삭제하려는 노드가 단말 노드일 경우
	if (w->left == NULL && w->right == NULL) { // 자식노드 검사

		if (w == parent->right) {
			parent->right = NULL;
		}else{
			parent->left = NULL;
		}
	}

	// 2. 삭제하려는 노드가 하나의 서브트리만 가진 경우

	else if (w->left == NULL || w->right == NULL) {


		if (w->left == NULL) {
			tmp = w->right;
		}
		else {
			tmp = w->left;
		}

		if (parent->left == w) {
			parent->left = tmp;
		}
		else {
			parent->right = tmp;
		}
	}


	// 3. 두 노드가 모두 서브트리를 가지는 경우
	else {

		tmpParent = w;
		tmp = w->right;

		while (tmp->left != NULL) {
			tmpParent = tmp;
			tmp = tmp->left;
		}

		if (tmpParent->left == tmp) {
			tmpParent->left = tmp->right;
		}
		else {
			tmpParent->right = tmp->right;
		}

		w->key = tmp->key; // w자리에 key를 옮겨주고 중위수식 계승자를 free
		w = tmp;
	}

	free(w);
}


int main() {

}