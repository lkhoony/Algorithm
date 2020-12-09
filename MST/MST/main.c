#include <stdlib.h>
#include <stdio.h>
#include <limits.h> 

/*
1. prim �˰���

struct Graph* G; // ����׷��� ��������
int n, m; // n : ������ ��, m : ������ ��
int* T; // �ּҽ���Ʈ�� ���� �迭
int numT = 0; // �ּҽ��� Ʈ�� ������ ����
int* PQ; // �������� ��⿭(�켱���� ť)
int q_n = 0; // �켱���� ť�� ����Ǵ� ������ ��

struct Graph {

	struct Vertex** vertexList; // ���� ����Ʈ(�迭�� ����)
	struct Edge** edgeList; // ���� ���� ����Ʈ(�迭�� ����)

}typedef Graph;

struct Vertex {

	//int i; // ������ �ε���
	unsigned long long distance; // ���� �������� �Ÿ�
	int vName; // ���� index�� �̸�
	int locator; // �켱���� ť������ ��ġ
	int parent; // �ּҽ��� Ʈ������ �θ� ���� ����
	struct IncidentEdge* incidentEdges; // ���� ���� ����Ʈ

}typedef Vertex;

struct Edge {

	//int i; // ������ �ε���
	int origin; // ���� ���� �ε���
	int destination; // ���� ���� �ε���
	unsigned long long weight; // ������ ����ġ

}typedef Edge;

struct IncidentEdge {

	int i; // ���� ���Ⱓ�� �ε���
	struct IncidentEdge* next; // ���� ���Ⱓ��

}typedef IncidentEdge;

// incidentEdgeList�� �ʱ�ȭ
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	//incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : ���� �̸�, i : ������ �ε���
Graph* insertVertex(int vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

	newVertex->vName = vName;
	newVertex->incidentEdges = initIncidentEdgeList(); // ��� �Է�
	newVertex->distance = ULLONG_MAX;
	newVertex->parent = -1;
	newVertex->locator = -1;
	(G->vertexList)[i] = newVertex;

}

// vName : ������ �̸�
int index(int vName) {

	Vertex** vertexList = G->vertexList;

	for (int i = 0; i < n; i++) {
		if (vName == vertexList[i]->vName) {
			return i;
		}
	}
}

// ����, ���� �������� ����Ʈ�� �� �տ� ����
void addFirst(IncidentEdge* header, int i) {

	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	newEdge->i = i;
	newEdge->next = header->next;
	header->next = newEdge;

}

// vertex�� edge�� ����Ǿ��ִ� �ݴ��� vertex�� index return
int opposite(int vIndex, int eIndex) {

	Edge* edge = G->edgeList[eIndex];

	if (edge->destination == vIndex) return edge->origin;
	else return edge->destination;

}

// uName : ���� ������ �̸�
// wName : ���� ������ �̸� 
// i : Edge�� �ε���
Graph* insertEdge(int uName, int wName, unsigned long long weight, int i) {

	int u = index(uName);
	int w = index(wName);

	Edge* edge = (Edge*)malloc(sizeof(Edge));

	edge->origin = u;
	edge->destination = w;
	edge->weight = weight;

	addFirst(G->vertexList[u]->incidentEdges, i);
	addFirst(G->vertexList[w]->incidentEdges, i);

	// ((G->vertexList)[w]->inDegree)++;

	G->edgeList[i] = edge;
}

Graph* initGraph() {

	G = (Graph*)malloc(sizeof(Graph));

}

Graph* buildGraph() {

	int vName;
	int origin, dest;
	unsigned long long weight;

	initGraph();

	scanf("%d", &n);

	G->vertexList = (Vertex**)malloc(sizeof(Vertex*) * n);

	for (int i = 0; i < n; i++) {

		vName = i + 1;
		insertVertex(vName, i);

	}

	scanf("%d", &m);

	G->edgeList = (Edge**)malloc(sizeof(Edge*) * m);

	for (int i = 0; i < m; i++) {
		scanf("%d%d%llu", &origin, &dest, &weight);

		insertEdge(origin, dest, weight, i);
	}

	T = (int*)malloc(sizeof(int) * n); // �ּҽ���Ʈ�� ���� 
	PQ = (int*)malloc(sizeof(int) * (n + 1)); // �켱���� ť

}

void swapElement(int* p, int* q) {
	int tmp;
	tmp = *q;
	*q = *p;
	*p = tmp;
}

void upHeap(int i) {

	if (i == 1) {
		return;
	}

	// PQ�� ����Ǵ� �� : ������ �ε���
	//printf("%d %d\n", G->vertexList[PQ[i / 2]]->distance, G->vertexList[PQ[i]]->distance);
	if (G->vertexList[PQ[i / 2]]->distance <= G->vertexList[PQ[i]]->distance) {
		return;
	}

	G->vertexList[PQ[i]]->locator = i / 2;
	G->vertexList[PQ[i / 2]]->locator = i;

	swapElement(&PQ[i / 2], &PQ[i]);

	upHeap(i / 2);
}

void downHeap(int i) {

	int smallerIndex;

	if (i * 2 > q_n) {
		return;
	}

	smallerIndex = i * 2;

	if (i * 2 + 1 <= q_n) {
		if (G->vertexList[PQ[smallerIndex]]->distance > G->vertexList[PQ[i * 2 + 1]]->distance)
			smallerIndex = i * 2 + 1;
	}

	if (G->vertexList[PQ[i]]->distance >= G->vertexList[PQ[smallerIndex]]->distance) {

		G->vertexList[PQ[i]]->locator = smallerIndex;
		G->vertexList[PQ[smallerIndex]]->locator = i;

		swapElement(&PQ[i], &PQ[smallerIndex]);
	}

	downHeap(smallerIndex);

}

// �켱���� ť�� �Է�
void insertItem(int key) {
	q_n++;
	PQ[q_n] = key;
	G->vertexList[key]->locator = q_n;
	upHeap(q_n);

}

int removeMin() {

	int min;
	min = PQ[1];

	// ť���� ���ŵǾ����� �ǹ�
	G->vertexList[min]->locator = -1;

	PQ[1] = PQ[q_n];
	q_n--;
	downHeap(1);

	return min;

}

void primJarnikMST() {

	IncidentEdge* incidentEdge;
	int u; // remove�� index�� ���� �� ����
	int e; // u�� ���� ������ �ε����� ����� ����
	int z; // u�� e�� ���� ����

	// 0�� ° ���� : root
	G->vertexList[0]->distance = 0;

	for (int i = 0; i < n; i++) {
		insertItem(i);
	}

	while (q_n != 0) {

		u = removeMin();
		T[numT++] = u;
		incidentEdge = G->vertexList[u]->incidentEdges;

		while (incidentEdge->next != NULL) {

			incidentEdge = incidentEdge->next;
			e = incidentEdge->i;
			z = opposite(u, e);
			if ((G->vertexList[z]->locator != -1) && (G->edgeList[e]->weight < G->vertexList[z]->distance)) {
				G->vertexList[z]->distance = G->edgeList[e]->weight;
				G->vertexList[z]->parent = e;
				//E[numE++] = e;
				//printf("%d\n", G->edgeList[e]->weight);
				// ť ������
				upHeap(G->vertexList[z]->locator);

			}
		}
	}
}

void printMST() {

	unsigned long long weightSum = 0, weight;
	int e;
	int parentEdge;

	for (int i = 0; i < n; i++) {

		printf(" %d", G->vertexList[T[i]]->vName);

		parentEdge = G->vertexList[T[i]]->parent;

		if (parentEdge != -1) {

			weight = G->edgeList[parentEdge]->weight;
			weightSum = weightSum + weight;
		}
	}

	printf("\n");

	printf("%llu\n", weightSum);
}

int main() {

	buildGraph();

	primJarnikMST();
	printMST();

}
*/

/*
5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6

5 7
1 2 2147483641
1 4 2147483642
1 5 2147483644
2 5 2147483647
4 5 2147483643
3 5 2147483645
2 3 2147483646

2147483647
*/

struct Graph* G; // ����׷��� ��������
int n, m; // n : ������ ��, m : ������ ��
int* E; // �ּҽ���Ʈ�� ���� �迭
int numE = 0; // �ּҽ��� Ʈ�� ������ ����
int* PQ; // �������� ��⿭(�켱���� ť)
int q_n = 0; // �켱���� ť�� ����Ǵ� ������ ��
int* set;

struct Graph {

	struct Vertex** vertexList; // ���� ����Ʈ(�迭�� ����)
	struct Edge** edgeList; // ���� ���� ����Ʈ(�迭�� ����)

}typedef Graph;

struct Vertex {

	//int i; // ������ �ε���
	int vName; // ���� index�� �̸�
	struct IncidentEdge* incidentEdges; // ���� ���� ����Ʈ

}typedef Vertex;

struct Edge {

	//int i; // ������ �ε���
	int origin; // ���� ���� �ε���
	int destination; // ���� ���� �ε���
	unsigned long long weight; // ������ ����ġ

}typedef Edge;

struct IncidentEdge {

	int i; // ���� ���Ⱓ�� �ε���
	struct IncidentEdge* next; // ���� ���Ⱓ��

}typedef IncidentEdge;

// incidentEdgeList�� �ʱ�ȭ
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	//incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : ���� �̸�, i : ������ �ε���
Graph* insertVertex(int vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

	newVertex->vName = vName;
	newVertex->incidentEdges = initIncidentEdgeList(); // ��� �Է�
	(G->vertexList)[i] = newVertex;

}

// vName : ������ �̸�
int index(int vName) {

	Vertex** vertexList = G->vertexList;

	for (int i = 0; i < n; i++) {
		if (vName == vertexList[i]->vName) {
			return i;
		}
	}
}

// ����, ���� �������� ����Ʈ�� �� �տ� ����
void addFirst(IncidentEdge* header, int i) {

	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	newEdge->i = i;
	newEdge->next = header->next;
	header->next = newEdge;

}

// vertex�� edge�� ����Ǿ��ִ� �ݴ��� vertex�� index return
int opposite(int vIndex, int eIndex) {

	Edge* edge = G->edgeList[eIndex];

	if (edge->destination == vIndex) return edge->origin;
	else return edge->destination;

}

// uName : ���� ������ �̸�
// wName : ���� ������ �̸� 
// i : Edge�� �ε���
Graph* insertEdge(int uName, int wName, unsigned long long weight, int i) {

	int u = index(uName);
	int w = index(wName);

	Edge* edge = (Edge*)malloc(sizeof(Edge));

	edge->origin = u;
	edge->destination = w;
	edge->weight = weight;

	addFirst(G->vertexList[u]->incidentEdges, i);
	addFirst(G->vertexList[w]->incidentEdges, i);

	// ((G->vertexList)[w]->inDegree)++;

	G->edgeList[i] = edge;
}

Graph* initGraph() {

	G = (Graph*)malloc(sizeof(Graph));

}

Graph* buildGraph() {

	int vName;
	int origin, dest;
	unsigned long long weight;

	initGraph();

	scanf("%d", &n);

	G->vertexList = (Vertex**)malloc(sizeof(Vertex*) * n);

	for (int i = 0; i < n; i++) {

		vName = i + 1;
		insertVertex(vName, i);

	}

	scanf("%d", &m);

	G->edgeList = (Edge**)malloc(sizeof(Edge*) * m);

	for (int i = 0; i < m; i++) {
		scanf("%d%d%llu", &origin, &dest, &weight);

		insertEdge(origin, dest, weight, i);
	}

	E = (int*)malloc(sizeof(int) * (n-1)); // �ּҽ���Ʈ�� ���� �迭
	PQ = (int*)malloc(sizeof(int) * (m + 1)); // �켱���� ť

}

void swapElement(int* p, int* q) {
	int tmp;
	tmp = *q;
	*q = *p;
	*p = tmp;
}

void upHeap(int i) {

	if (i == 1) {
		return;
	}

	// PQ�� ����Ǵ� �� : ������ �ε���
	//printf("%d %d\n", G->vertexList[PQ[i / 2]]->distance, G->vertexList[PQ[i]]->distance);
	if (G->edgeList[PQ[i / 2]]->weight <= G->edgeList[PQ[i]]->weight) {
		return;
	}

	swapElement(&PQ[i / 2], &PQ[i]);

	upHeap(i / 2);
}

void downHeap(int i) {

	int smallerIndex;

	if (i * 2 > q_n) {
		return;
	}

	smallerIndex = i * 2;

	if (i * 2 + 1 <= q_n) {
		if (G->edgeList[PQ[smallerIndex]]->weight > G->edgeList[PQ[i * 2 + 1]]->weight)
			smallerIndex = i * 2 + 1;
	}

	if (G->edgeList[PQ[i]]->weight >= G->edgeList[PQ[smallerIndex]]->weight) {

		swapElement(&PQ[i], &PQ[smallerIndex]);
	}

	downHeap(smallerIndex);

}

// �켱���� ť�� �Է�
void insertItem(int key) {
	q_n++;
	PQ[q_n] = key;
	upHeap(q_n);
}

int removeMin() {

	int min;
	min = PQ[1];

	PQ[1] = PQ[q_n];
	q_n--;
	downHeap(1);

	return min;

}

int findSet(int i) {

	while (set[i] != -1) {
		i = set[i];
	}
	
	return i;

}

void kruskalMST() {

	int i,u,v;
	Edge* edge;

	// �и����� �ʱ�ȭ
	set = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		set[i] = -1; // ������ �и������� �������
	}
	// printf("init set completed\n");
	for (i = 0; i < m; i++) {
		insertItem(i);
	}

	// printf("insert completed\n");

	while (numE < n - 1) {

		int min = removeMin();
		// printf("min : %d\n", min);
		edge = G->edgeList[min];
		u = edge->origin;
		v = edge->destination;

		// printf("%d %d\n", findSet(u), findSet(v));

		if (findSet(u) != findSet(v) ){
			E[numE++] = min;
			
			set[findSet(v)] = findSet(u);
			
		}
	}
}

void printMST() {

	unsigned long long weightSum = 0;
	
	for (int i = 0; i < numE; i++) {
		printf(" %llu", G->edgeList[E[i]]->weight);
		weightSum = weightSum + G->edgeList[E[i]]->weight;
	}

	printf("\n");

	printf("%llu", weightSum);
}

int main() {

	buildGraph();
	kruskalMST();
	printMST();

}

/*
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37
*/