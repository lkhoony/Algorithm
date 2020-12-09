#include <stdlib.h>
#include <stdio.h>
#include <limits.h> 

/*
1. prim 알고리즘

struct Graph* G; // 방향그래프 전역변수
int n, m; // n : 정점의 수, m : 간선의 수
int* T; // 최소신장트리 정점 배열
int numT = 0; // 최소신장 트리 정점의 개수
int* PQ; // 정점들의 대기열(우선순위 큐)
int q_n = 0; // 우선순위 큐에 저장되는 정점의 수

struct Graph {

	struct Vertex** vertexList; // 정점 리스트(배열로 구현)
	struct Edge** edgeList; // 방향 간선 리스트(배열로 구현)

}typedef Graph;

struct Vertex {

	//int i; // 정점의 인덱스
	unsigned long long distance; // 인접 정점과의 거리
	int vName; // 정점 index의 이름
	int locator; // 우선순위 큐에서의 위치
	int parent; // 최소신장 트리에서 부모를 향한 간선
	struct IncidentEdge* incidentEdges; // 진출 간선 리스트

}typedef Vertex;

struct Edge {

	//int i; // 간선의 인덱스
	int origin; // 시점 정점 인덱스
	int destination; // 종점 정점 인덱스
	unsigned long long weight; // 간선의 가중치

}typedef Edge;

struct IncidentEdge {

	int i; // 부착 방향간선 인덱스
	struct IncidentEdge* next; // 다음 방향간선

}typedef IncidentEdge;

// incidentEdgeList를 초기화
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	//incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : 정점 이름, i : 정점의 인덱스
Graph* insertVertex(int vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

	newVertex->vName = vName;
	newVertex->incidentEdges = initIncidentEdgeList(); // 헤더 입력
	newVertex->distance = ULLONG_MAX;
	newVertex->parent = -1;
	newVertex->locator = -1;
	(G->vertexList)[i] = newVertex;

}

// vName : 정점의 이름
int index(int vName) {

	Vertex** vertexList = G->vertexList;

	for (int i = 0; i < n; i++) {
		if (vName == vertexList[i]->vName) {
			return i;
		}
	}
}

// 진입, 진출 부착간선 리스트의 맨 앞에 삽입
void addFirst(IncidentEdge* header, int i) {

	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	newEdge->i = i;
	newEdge->next = header->next;
	header->next = newEdge;

}

// vertex와 edge가 연결되어있는 반대편 vertex의 index return
int opposite(int vIndex, int eIndex) {

	Edge* edge = G->edgeList[eIndex];

	if (edge->destination == vIndex) return edge->origin;
	else return edge->destination;

}

// uName : 시점 정점의 이름
// wName : 종점 정점의 이름 
// i : Edge의 인덱스
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

	T = (int*)malloc(sizeof(int) * n); // 최소신장트리 정점 
	PQ = (int*)malloc(sizeof(int) * (n + 1)); // 우선순위 큐

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

	// PQ에 저장되는 값 : 정점의 인덱스
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

// 우선순위 큐에 입력
void insertItem(int key) {
	q_n++;
	PQ[q_n] = key;
	G->vertexList[key]->locator = q_n;
	upHeap(q_n);

}

int removeMin() {

	int min;
	min = PQ[1];

	// 큐에서 제거되었음을 의미
	G->vertexList[min]->locator = -1;

	PQ[1] = PQ[q_n];
	q_n--;
	downHeap(1);

	return min;

}

void primJarnikMST() {

	IncidentEdge* incidentEdge;
	int u; // remove된 index가 저장 될 변수
	int e; // u의 부착 간선의 인덱스가 저장될 변수
	int z; // u와 e의 인접 정점

	// 0번 째 정점 : root
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
				// 큐 재정비
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

struct Graph* G; // 방향그래프 전역변수
int n, m; // n : 정점의 수, m : 간선의 수
int* E; // 최소신장트리 간선 배열
int numE = 0; // 최소신장 트리 간선의 개수
int* PQ; // 정점들의 대기열(우선순위 큐)
int q_n = 0; // 우선순위 큐에 저장되는 정점의 수
int* set;

struct Graph {

	struct Vertex** vertexList; // 정점 리스트(배열로 구현)
	struct Edge** edgeList; // 방향 간선 리스트(배열로 구현)

}typedef Graph;

struct Vertex {

	//int i; // 정점의 인덱스
	int vName; // 정점 index의 이름
	struct IncidentEdge* incidentEdges; // 진출 간선 리스트

}typedef Vertex;

struct Edge {

	//int i; // 간선의 인덱스
	int origin; // 시점 정점 인덱스
	int destination; // 종점 정점 인덱스
	unsigned long long weight; // 간선의 가중치

}typedef Edge;

struct IncidentEdge {

	int i; // 부착 방향간선 인덱스
	struct IncidentEdge* next; // 다음 방향간선

}typedef IncidentEdge;

// incidentEdgeList를 초기화
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	//incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : 정점 이름, i : 정점의 인덱스
Graph* insertVertex(int vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

	newVertex->vName = vName;
	newVertex->incidentEdges = initIncidentEdgeList(); // 헤더 입력
	(G->vertexList)[i] = newVertex;

}

// vName : 정점의 이름
int index(int vName) {

	Vertex** vertexList = G->vertexList;

	for (int i = 0; i < n; i++) {
		if (vName == vertexList[i]->vName) {
			return i;
		}
	}
}

// 진입, 진출 부착간선 리스트의 맨 앞에 삽입
void addFirst(IncidentEdge* header, int i) {

	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	newEdge->i = i;
	newEdge->next = header->next;
	header->next = newEdge;

}

// vertex와 edge가 연결되어있는 반대편 vertex의 index return
int opposite(int vIndex, int eIndex) {

	Edge* edge = G->edgeList[eIndex];

	if (edge->destination == vIndex) return edge->origin;
	else return edge->destination;

}

// uName : 시점 정점의 이름
// wName : 종점 정점의 이름 
// i : Edge의 인덱스
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

	E = (int*)malloc(sizeof(int) * (n-1)); // 최소신장트리 간선 배열
	PQ = (int*)malloc(sizeof(int) * (m + 1)); // 우선순위 큐

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

	// PQ에 저장되는 값 : 정점의 인덱스
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

// 우선순위 큐에 입력
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

	// 분리집합 초기화
	set = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		set[i] = -1; // 각각의 분리집합을 만들어줌
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