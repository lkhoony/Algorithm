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
	int e; // ������ Ű�� �Էµ� ����

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

	// 1. �����Ϸ��� ��尡 �ܸ� ����� ���
	if (w->left == NULL && w->right == NULL) { // �ڽĳ�� �˻�

		if (w == parent->right) {
			parent->right = NULL;
		}else{
			parent->left = NULL;
		}
	}

	// 2. �����Ϸ��� ��尡 �ϳ��� ����Ʈ���� ���� ���

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


	// 3. �� ��尡 ��� ����Ʈ���� ������ ���
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

		w->key = tmp->key; // w�ڸ��� key�� �Ű��ְ� �������� ����ڸ� free
		w = tmp;
	}

	free(w);
}


int main() {

}