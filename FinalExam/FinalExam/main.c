#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
struct Graph* G; // ����׷��� ��������
int n, m; // n : ������ ��, m : ������ ��
int adjacent[100][100];


struct Graph {
	struct Vertex** vertexList; // ���� ����Ʈ(�迭�� ����)
	struct Edge** edgeList; // ���� ���� ����Ʈ(�迭�� ����)
}typedef Graph;

struct Vertex {

	int vName; // ���� index�� �̸�
	struct IncidentEdge* incidentEdges; // ���� ���� ����Ʈ

}typedef Vertex;
struct Edge {

	int origin; // ���� ���� �ε���
	int destination; // ���� ���� �ε���
	int weight; // ������ ����ġ

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
Graph* insertEdge(int uName, int wName, int weight, int i) {
	int u = index(uName);
	int w = index(wName);
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	edge->origin = u;
	edge->destination = w;
	edge->weight = weight;
	addFirst(G->vertexList[u]->incidentEdges, i);
	addFirst(G->vertexList[w]->incidentEdges, i);
	G->edgeList[i] = edge;

	if (u != w) {
		adjacent[u][w] = weight;
		adjacent[w][u] = weight;
	}
}

Graph* initGraph() {
	G = (Graph*)malloc(sizeof(Graph));
}

Graph* buildGraph() {
	int vName;
	int origin, dest;
	int weight;
	initGraph();
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				adjacent[i][j] = 0;
				continue;
			}
			adjacent[i][j] = -1;
		}
	}
	G->vertexList = (Vertex**)malloc(sizeof(Vertex*) * n);
	for (int i = 0; i < n; i++) {
		vName = i + 1;
		insertVertex(vName, i);
	}
	scanf("%d", &m);
	G->edgeList = (Edge**)malloc(sizeof(Edge*) * m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &origin, &dest, &weight);
		insertEdge(origin, dest, weight, i);
	}

}

int main() {

	buildGraph();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjacent[i][j] == -1)
				printf(" -");
			else
				printf(" %d", adjacent[i][j]);
		}

		printf("\n");
	}
}
*/

/*
6 8
1 2 6
1 3 3
1 4 4
1 6 3
3 2 2
4 5 1
5 1 1
5 6 3
*/
// ---------------------------------------------------------
// 2��

/*
// 1. prim �˰���
struct Graph* G; // ����׷��� ��������
int n, m; // n : ������ ��, m : ������ ��
int* T; // �ּҽ���Ʈ�� ���� �迭
int numT = 0; // �ּҽ��� Ʈ�� ������ ����
int* PQ; // �������� ��⿭(�켱���� ť)
int q_n = 0; // �켱���� ť�� ����Ǵ� ������ ��
int S; // ���� ����
int E; // ���� ����

struct Graph {
	struct Vertex** vertexList; // ���� ����Ʈ(�迭�� ����)
	struct Edge** edgeList; // ���� ���� ����Ʈ(�迭�� ����)
}typedef Graph;
struct Vertex {
	//int i; // ������ �ε���
	int distance; // ���� �������� �Ÿ�
	int vName; // ���� index�� �̸�
	int locator; // �켱���� ť������ ��ġ
	int parent; // �ּҽ��� Ʈ������ �θ� ���� ����
	struct IncidentEdge* incidentEdges; // ���� ���� ����Ʈ
}typedef Vertex;
struct Edge {
	//int i; // ������ �ε���
	int origin; // ���� ���� �ε���
	int destination; // ���� ���� �ε���
	int weight; // ������ ����ġ
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
	newVertex->distance = 1001;
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
Graph* insertEdge(int uName, int wName, int weight, int i) {
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
	int weight;
	initGraph();
	scanf("%d", &n);
	G->vertexList = (Vertex**)malloc(sizeof(Vertex*) * n);
	for (int i = 0; i < n; i++) {
		vName = i + 1;
		insertVertex(vName, i);
	}
	scanf("%d", &m);
	G->edgeList = (Edge**)malloc(sizeof(Edge*) * m);
	scanf("%d %d", &S, &E);

	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &origin, &dest, &weight);
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
	G->vertexList[index(S)]->distance = 0;
	for (int i = 0; i < n; i++) {
		insertItem(i);
	}
	while (q_n != 0) {
		u = removeMin();
		T[numT++] = u;
		printf("%d %d\n", u, index(E));
		if (u == index(E))
			break;
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
	int weightSum = 0, weight;
	int e;
	int parentEdge;
	for (int i = 0; i < numT; i++) {
		printf(" %d", G->vertexList[T[i]]->vName);
		parentEdge = G->vertexList[T[i]]->parent;
		if (parentEdge != -1) {
			weight = G->edgeList[parentEdge]->weight;
			weightSum = weightSum + weight;
		}
	}
	printf("\n");
	printf("%d\n", weightSum);
}
int main() {
	buildGraph();
	primJarnikMST();
	printMST();
}
*/
/*
6 9 1 4
1 2 3
1 3 9
1 4 6
2 3 2
2 5 7
3 4 8
3 5 5
3 6 1
4 6 4
*/

struct DiGraph* G; // ����׷��� ��������
int n, m; // n : ������ ��, m : ������ ��
int* in; // ������ �������� �迭
int* topOrder; // ������ ������� �迭
int* Q; // �������� ��⿭

struct DiGraph {

	struct Vertex** vertexList; // ���� ����Ʈ(�迭�� ����)
	struct DirectedEdge** directedEdgeList; // ���� ���� ����Ʈ(�迭�� ����)

}typedef DiGraph;

struct Vertex {

	int i; // ������ �ε���
	int inDegree; // ���� ����
	char vName; // ���� index�� �̸�
	struct IncidentEdge* outEdges; // ���� ���� ����Ʈ
	struct IncidentEdge* inEdges; // ���� ���� ����Ʈ

}typedef Vertex;

struct DirectedEdge {

	int i; // ������ �ε���
	int origin; // ���� ����
	int destination; // ���� ����

}typedef DirectedEdge;

struct IncidentEdge {

	int i; // ���� ���Ⱓ�� �ε���
	struct IncidentEdge* next; // ���� ���Ⱓ��

}typedef IncidentEdge;

// incidentEdgeList�� �ʱ�ȭ
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : ���� �̸�, i : ������ �ε���
DiGraph* insertVertex(char vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

	newVertex->vName = vName;
	newVertex->outEdges = initIncidentEdgeList(); // ��� �Է�
	newVertex->inEdges = initIncidentEdgeList(); // ��� �Է�
	newVertex->inDegree = 0;

	(G->vertexList)[i] = newVertex;

}

// vName : ������ �̸�
int index(char vName) {

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


// uName : ���� ������ �̸�
// wName : ���� ������ �̸� 
// i : DirectedEdge�� �ε���
DiGraph* insertDirectedEdge(char uName, char wName, int i) {

	int u = index(uName);
	int w = index(wName);

	DirectedEdge* directedEdge = (DirectedEdge*)malloc(sizeof(DirectedEdge));

	directedEdge->origin = u;
	directedEdge->destination = w;

	addFirst((G->vertexList)[u]->outEdges, i);
	addFirst((G->vertexList)[w]->inEdges, i);

	((G->vertexList)[w]->inDegree)++;

	G->directedEdgeList[i] = directedEdge;
}

DiGraph* initGraph() {

	G = (DiGraph*)malloc(sizeof(DiGraph));
	G->vertexList = (Vertex**)malloc(sizeof(Vertex*) * 99);
	G->directedEdgeList = (DirectedEdge**)malloc(sizeof(DirectedEdge*) * 999);

}

DiGraph* buildGraph() {

	char vName;
	char edge[4];

	initGraph();

	scanf("%d %d", &n, &m);

	getchar();

	for (int i = 0; i < n; i++) {

		scanf("%c", &vName);
		insertVertex(vName, i);
		getchar();

	}

	for (int i = 0; i < m; i++) {
		gets(edge);
		insertDirectedEdge(edge[0], edge[2], i);
	}

	in = (int*)malloc(sizeof(int) * n);
	topOrder = (int*)malloc(sizeof(int) * (n + 1));

}

void topologicalSort() {

	Q = (int*)malloc(sizeof(int) * n);

	int front = 0;
	int rear = -1;
	int u, w;

	for (int i = 0; i < n; i++) {
		in[i] = (G->vertexList)[i]->inDegree;
		if (in[i] == 0) Q[++rear] = i;
	}

	int t = 1;

	while (front <= rear) {

		u = Q[front++];
		topOrder[t] = u;
		t++;

		IncidentEdge* outEdge = (G->vertexList)[u]->outEdges;
		while (outEdge->next != NULL) {
			outEdge = outEdge->next;

			w = (G->directedEdgeList)[outEdge->i]->destination;
			in[w] = in[w] - 1;
			if (in[w] == 0) Q[++rear] = w;
		}

	}

	if (t <= n) topOrder[0] = 0;
	else topOrder[0] = 1;

}
int main() {

	buildGraph();

	topologicalSort();

	if (topOrder[0] == 0)
		printf("-1\n");
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", G->vertexList[topOrder[i]]->vName);
		}
	}
}

/*
3 3
A B C
A B
C A
C B

4 6
A B C D
A B
C A
C B
A D
B D
D C

6 7
A B C D E F
A B
B C
D B
E B
E C
E D
E F
*/